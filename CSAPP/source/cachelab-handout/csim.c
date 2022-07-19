

#define  _GNU_SOURCE
#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

typedef struct cache_item{
    bool valid;
    int tag; //
    struct cache_item*prev;
    struct  cache_item*next;
}cache_item;


// head->next is the last referenced item.
typedef struct cache_set{
    cache_item*tail;
    cache_item*head;
    int size;
}cache_set;


typedef struct cache_simulator{
    cache_set* sets;
}cache_simulator;

bool verbose = false;
int s = -1;
int E = -1; 
int b = -1;
char *tracefile = NULL;
int hits=0 ,misses = 0,  evictions=0;
int bytes_per_cache_intem = -1, sets_num = -1;
cache_simulator cache;

#define GET_TAG(address) (address>>(b+s))
#define GET_SET_INDEX(address) ((((1<<(b+s))-1)&address)>>b)
#define GET_ADDRESS_BASE(address) ((address>>b)<<b)

cache_item* new_cache_item(cache_item*prev,cache_item*next,int tag,bool valid ){
    cache_item* item = malloc(sizeof(cache_item));
    item->prev = prev;
    item->next = next;
    if(prev!=NULL){
        prev->next = item;
    }
    if(next!=NULL){
        next->prev = item;
    }
    item->tag = tag;
    item->valid = valid;
    return item;
}


void initialize_cache_set(cache_set *set){
    set->head =  new_cache_item(NULL,NULL,-1,false);
    set->tail =  new_cache_item(NULL,NULL,-1,false);
    set->head->next = set->tail;
    set->tail->prev = set->head;
    set->size = 0;
}


void initialize_cache(){
    cache.sets = malloc(sizeof(cache_set)*sets_num);
    for(int i=0;i<sets_num;i++){
        initialize_cache_set(&(cache.sets[i]));
    }
}



void delete_item(cache_item* item) {
    item->prev->next = item->next;
    item->next->prev = item->prev;
    free(item);
}



cache_item* find_item(uintptr_t address){

    int tag = GET_TAG(address);
    int set_index = GET_SET_INDEX(address);
    cache_item* item = cache.sets[set_index].head->next;
    cache_item* tail = cache.sets[set_index].tail;
    while(item!=tail){
        if(item->valid && item->tag == tag){
            // delete_item(item);
            // cache.sets[set_index].size -= 1;
            // cache_item*found =  new_cache_item(head,head->next,tag,true);
            // cache.sets[set_index].size += 1;
            // return found;
            return item;
        }
        item=item->next;
    }
    return NULL;
}

void push_to_front(cache_item*item,uintptr_t address){
    int set_index = GET_SET_INDEX(address);
    cache_item* head = cache.sets[set_index].head;
    int sz = cache.sets[set_index].size;
    if(sz <= 1){
        return;
    }
    item->prev->next = item->next;
    item->next->prev = item->prev;


    item->prev = head;
    item->next = head->next;
    head->next->prev = item;
    head->next = item;
}

void help(){
    printf("Usage: ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
}


void parse_command_line(int argc, char * argv[]){
    int opt;
    while((opt = getopt(argc, argv, "h:v:s:E:b:t:"))!= -1){
        switch(opt){
            case 'h' : {
                help();
                return;
            }
            case 'v' : {
                verbose = true;
                break;
            }
            case 's' : {
                s = atoi(optarg);
                // printf("parse s = %s \n",optarg);
                break;
            }
            case 'E' : {
                E = atoi(optarg);
                // printf("parse E = %d \n",E);
                break;
            }
            case 'b' : {
                b = atoi(optarg);
                // printf("parse b = %d \n",b);
                break;
            }
            case 't' : {
                // printf("parse tracefile = %s \n",optarg);
                tracefile = optarg;
                break;
            }
            default:{
                printf("wrong argument!!!\n");
                break;
            }
        }
    }
}

void replace(uintptr_t address){
    int set_index = GET_SET_INDEX(address);
    int tag = GET_TAG(address);
    int sz = cache.sets[set_index].size;
    cache_item* tail = cache.sets[set_index].tail;
    cache_item* head = cache.sets[set_index].head;
    if(sz < E){
        new_cache_item(head,head->next,tag,true);
        cache.sets[set_index].size += 1;
    }else {
        evictions++;
        delete_item(tail->prev);
        (void*)new_cache_item(head,head->next,tag,true);
    }
}



void load_data(uintptr_t address, int size){
    uintptr_t base = GET_ADDRESS_BASE(address);
    uintptr_t end = address + size;
    cache_item*item = NULL;
    while(base < end){
        if((item=find_item(base))!=NULL){
            hits++;
            push_to_front(item,base);
        }else{
            misses += 1;
            replace(base);
        }
        base += bytes_per_cache_intem;
    }
}



void store_data(uintptr_t address, int size){
    uintptr_t base = GET_ADDRESS_BASE(address);
    uintptr_t end = address + size;
    cache_item*item = NULL;
    while(base < end){
        if((item=find_item(base))!=NULL){
            hits++;
            push_to_front(item,base);
        }else{
            misses += 1;
            replace(base);
        }
        base += bytes_per_cache_intem;
    }
}

void modify_data(uintptr_t address, int size){
    load_data(address,size);
    store_data(address,size);
}



//“I” denotes an instruction load, “L” a data load, “S” a data store, and “M” a data modify
void parse_file(const char *filename){
    // printf("filename = %s\n", filename);
    FILE*fp = fopen (filename, "r");
    
    char operation;
    uintptr_t address;
    int size;
    size_t len;
    char * line = NULL;
    while(getline(&line, &len,fp )!=-1){
        if(line[0] != ' '){
            continue;
        }
        
        sscanf(line," %c %lx,%d",&operation,&address,&size);
        // printf("%s",line);
        printf("parse result :  %c %lx,%d\n",operation,address,size);
        switch(operation){
            case 'M' :{
                // printf("--M\n");
                modify_data(address,size);
                break;
            }
            case 'L' :{
                // printf("--L\n");
                load_data(address,size);
                break;
            }
            case 'S' :{
                // printf("--S\n");
                store_data(address,size);
                break;
            }
            default:{
                break;
            }
        }

    }

}


void free_cache_set(cache_set *set){
    cache_item* item = set->head;
    while(item!=NULL){
        cache_item* temp = item;
        item = item->next;
        free(temp);
    }
}

void free_cache_simulator(){
    for(int i=0;i<sets_num;++i){
        free_cache_set(&(cache.sets[i]));
    }
    free(cache.sets);
}

int main(int argc, char* argv[])
{
    parse_command_line(argc, argv);
    if(s==-1||b==-1||E==-1||tracefile == NULL) {
        printf("wrong argument\n");
        return 0;
    }
    sets_num = pow(2,s);
    bytes_per_cache_intem = pow(2,b);
    initialize_cache();
    parse_file(tracefile);
    printSummary(hits, misses, evictions);
    free_cache_simulator();

    return 0;
}
