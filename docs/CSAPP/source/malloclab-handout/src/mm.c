/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "../include/mm.h"
#include "../include/memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
        /* Team name */
        "ateam",
        /* First member's full name */
        "Siyu Liu",
        /* First member's email address */
        "liusy58@smail.nju.edu.cn",
        /* Second member's full name (leave blank if none) */
        "",
        /* Second member's email address (leave blank if none) */
        ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))


#define WSIZE 4
#define DSIZE 8

#define LISTSZ 20

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
#define INITCHUNKSZ (1<<6)
#define MINBLOCKSIZE 16



static char *segregated_free_lists[LISTSZ];
static char *heap_start_pointer;


#define ALLOCATED 1
#define FREE 0
#define MINBLOCKSIZE 16

#define CHUNKSIZE (1<<12)
#define SIZE(ptr) ((*(unsigned int*)ptr) & ~0x7)
#define TAG(ptr) ((*(unsigned int*)ptr) & 0x1)
#define PUT(ptr,value) ((*(unsigned int*)(ptr)) = (unsigned int)value)
#define PACK(size,tag) ((size) | (tag))
#define HDPTR(ptr) ((unsigned int*)((char*)(ptr) - WSIZE))
#define FTPTR(ptr) ((unsigned int*)((char*)(ptr) + SIZE(HDPTR(ptr)) - DSIZE))
#define GETSIZE(ptr) (SIZE(HDPTR(ptr)))
// physically

#define PREVBLOCK(ptr) (((char*)(ptr)) - SIZE(((char*)(ptr) - DSIZE)))
#define NEXTBLOCK(ptr) ((char*)(ptr) + SIZE(HDPTR(ptr)))
#define NEXTBLOCKHEADPTR(ptr) (((char*)(ptr) + SIZE(HDPTR(ptr)) - WSIZE))

#define SETPTR(ptr,val) (*(unsigned int*)(ptr) = (val))

#define NEXTBLOCKINFREELIST(ptr) ((unsigned int*)((char*)(ptr) + WSIZE))
#define PREVBLOCKINFREELIST(ptr) ((unsigned int*)((ptr)))


// helper functions
static void *extend_heap(size_t size);
static void *coalesce(void *ptr);
static void *place(void *ptr, size_t asize);
static void insert_node(void *ptr, size_t size);
static void delete_node(void *ptr);

/*               <- ptr
 * |            |
 * |            |
 * |            |
 * |            |
 * |            |
 *               ________: footer pointer
 * |            |
 *               ________: header pointer
 * |            |
 *               --------: ptr + sz
 */

static void show_free_list(){
    for(int i = 0;i < LISTSZ; ++i){
        char *head_ptr = segregated_free_lists[i];
        if(head_ptr != NULL){
//            printf("i = %d ptr = %p  %d NEXTBLOCKINFREELIST(ptr) = %p ---\n", i,ptr, SIZE(HDPTR(ptr)),NEXTBLOCKINFREELIST(ptr));
            while(head_ptr != NULL){
                printf("i = %d ptr = %p size = %d NEXTBLOCKINFREELIST(ptr) = %p ---\n", i,head_ptr, SIZE(HDPTR(head_ptr)),*(unsigned int*)NEXTBLOCKINFREELIST(head_ptr));
//                printf("[%p]\n",ptr);
//                printf("~~~ ptr = %p HDPTR(ptr) =%p SIZE(HDPTR(ptr) = %d\n",ptr,HDPTR(ptr), SIZE(HDPTR(ptr)));
                head_ptr = *(unsigned int*)NEXTBLOCKINFREELIST(head_ptr);
            }
        }
    }
}


void *place(void *ptr, size_t asize){
    size_t before_size = SIZE(HDPTR(ptr));
    if(before_size - asize < MINBLOCKSIZE){
        SETPTR(HDPTR(ptr), PACK(before_size,ALLOCATED));
        delete_node(ptr);
        return ptr;
    }
    size_t new_size = before_size - asize;
    delete_node(ptr);

    if(asize >= 100){
        SETPTR(HDPTR(ptr), PACK(new_size,0));
        SETPTR(FTPTR(ptr), PACK(new_size,0));
        SETPTR(HDPTR(NEXTBLOCK(ptr)), PACK(asize,1));
        SETPTR(FTPTR(NEXTBLOCK(ptr)),PACK(asize,1));
        insert_node(ptr,new_size);
        return NEXTBLOCK(ptr);
    }

    SETPTR(HDPTR(ptr),PACK(asize,ALLOCATED));
    SETPTR(FTPTR(ptr),PACK(asize,ALLOCATED));
    SETPTR(HDPTR(NEXTBLOCK(ptr)),new_size);
    SETPTR(FTPTR(NEXTBLOCK(ptr)),new_size);
    insert_node(NEXTBLOCK(ptr),new_size);
    return ptr;
}

void delete_node(void *ptr){
    size_t sz = SIZE(HDPTR(ptr));
    int index = 0;
    while(sz > 1){
        index++;
        sz >>= 1;
    }

    index = MIN(index,LISTSZ-1);
    char* prev = NULL, *current = segregated_free_lists[index];
    while(current != NULL && current != ptr){
        prev = current;
        current = *(unsigned int*)NEXTBLOCKINFREELIST(current);
    }

    char* next = *(unsigned int*)NEXTBLOCKINFREELIST(current);
    if(prev == NULL){
        if(next == NULL){
            segregated_free_lists[index] = NULL;
        }else{
            segregated_free_lists[index] = next;
            SETPTR(PREVBLOCKINFREELIST(next) ,NULL);
        }
    }else{
        if(next == NULL){
            SETPTR(NEXTBLOCKINFREELIST(prev),NULL);
        }else{
            SETPTR(NEXTBLOCKINFREELIST(prev),next);
            SETPTR(PREVBLOCKINFREELIST(next),prev);
        }
    }
}

void *coalesce(void *ptr){
    size_t prev_block_size = SIZE(HDPTR(PREVBLOCK(ptr)));
    int prev_block_allocated = TAG(HDPTR(PREVBLOCK(ptr)));


    size_t next_block_size = SIZE(HDPTR(NEXTBLOCK(ptr)));
    int next_block_allocated = TAG(HDPTR(NEXTBLOCK(ptr)));

    int prev_need_coalesce = (!prev_block_allocated) && (prev_block_size > 0);
    int next_need_coalesce = (!next_block_allocated) && (next_block_size > 0);

    size_t size = SIZE(HDPTR(ptr));
    char*new_ptr= NULL;
    if(!prev_need_coalesce && !next_need_coalesce){
        return ptr;
    }else if(!prev_need_coalesce && next_need_coalesce){
        char* new_header = HDPTR(ptr);
        char* new_footer = FTPTR(NEXTBLOCK(ptr));
        size_t new_size = size + next_block_size;
        delete_node(NEXTBLOCK(ptr));
        delete_node(ptr);
        SETPTR(new_header,new_size);
        SETPTR(new_footer,new_size);
        new_ptr = new_header + WSIZE;
        insert_node(new_ptr,new_size);
    }else if(prev_need_coalesce && !next_need_coalesce){
        char* new_header = HDPTR(PREVBLOCK(ptr));
        char* new_footer = FTPTR(ptr);
        size_t new_size = size + prev_block_size;
        delete_node(PREVBLOCK(ptr));
        delete_node(ptr);
        SETPTR(new_header,new_size);
        SETPTR(new_footer,new_size);
        new_ptr = new_header + WSIZE;
        insert_node(new_ptr,new_size);
    }else {
        char* new_header = HDPTR(PREVBLOCK(ptr));
        char* new_footer = FTPTR(NEXTBLOCK(ptr));
        size_t new_size = size + next_block_size + prev_block_size;
        delete_node(PREVBLOCK(ptr));
        delete_node(ptr);
        delete_node(NEXTBLOCK(ptr));
        SETPTR(new_header,new_size);
        SETPTR(new_footer,new_size);
        new_ptr = new_header + WSIZE;
        insert_node(new_ptr,new_size);
    }
    return new_ptr;
}

void insert_node(void *ptr, size_t size){
    int index = 0;
    size_t sz = size;
    while(sz > 1){
        index++;
        sz >>= 1;
    }
    index = MIN(index,LISTSZ-1);
    char* prev = NULL, *current = segregated_free_lists[index];
    while(current != NULL && size > GETSIZE(current)){
        prev = current;
        current = *(unsigned int*)NEXTBLOCKINFREELIST(current);
    }
    if(current == NULL){
        if(prev == NULL){
            segregated_free_lists[index] = ptr;
            char* prev_ptr =  PREVBLOCKINFREELIST(ptr);
            char* next_ptr =  NEXTBLOCKINFREELIST(ptr);
            SETPTR(prev_ptr,NULL);
            SETPTR(next_ptr,NULL);
        }else{
            SETPTR(NEXTBLOCKINFREELIST(prev),ptr);
            SETPTR(NEXTBLOCKINFREELIST(ptr),NULL);
            SETPTR(PREVBLOCKINFREELIST(ptr),prev);
        }
    }else {
        if(prev == NULL){
            segregated_free_lists[index] = ptr;
            SETPTR(NEXTBLOCKINFREELIST(ptr),current);
            SETPTR(PREVBLOCKINFREELIST(ptr),NULL);
            SETPTR(PREVBLOCKINFREELIST(current),ptr);
        }else{
            SETPTR(NEXTBLOCKINFREELIST(prev),ptr);
            SETPTR(PREVBLOCKINFREELIST(ptr),prev);
            SETPTR(PREVBLOCKINFREELIST(current),ptr);
            SETPTR(NEXTBLOCKINFREELIST(ptr),current);
        }
    }
//    printf("After insertion\n");
//    show_free_list();
//    printf("\n");

}

void *extend_heap(size_t size){
    char* ptr;
    if((ptr = mem_sbrk(size)) == (void*)-1){
        return NULL;
    }

    PUT(HDPTR(ptr), size);
    PUT(FTPTR(ptr), size);
    PUT(NEXTBLOCKHEADPTR(ptr),0);
    insert_node(ptr,size);
    return coalesce(ptr);
}


/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    for(int i = 0;i<LISTSZ;++i){
        segregated_free_lists[i] = NULL;
    }
    if((heap_start_pointer = mem_sbrk(4 * WSIZE)) == (void*)-1){
        return -1;
    }
//    printf("After mm_init heap_start_pointer = %p\n",heap_start_pointer);
    PUT(heap_start_pointer + 0 * WSIZE, 0);
    PUT(heap_start_pointer + 1 * WSIZE, PACK(8,1));
    PUT(heap_start_pointer + 2 * WSIZE, PACK(8,1));
    PUT(heap_start_pointer + 3 * WSIZE, 0);

    if(extend_heap(INITCHUNKSZ) == NULL){
        return -1;
    }

    return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    if(size == 0){
        return NULL;
    }
    size_t new_size = MAX(MINBLOCKSIZE, ALIGN(size + DSIZE));
//    printf("Now malloc size = %u\n",new_size);
//    show_free_list();
    int index = 0;
    size_t sz = new_size;
    while(sz > 1){
        index++;
        sz >>= 1;
    }
    char * ptr = NULL;
    while(index < LISTSZ){
        ptr = segregated_free_lists[index];
        while(ptr!=NULL && new_size > SIZE(HDPTR(ptr))){
            ptr = *(unsigned int*)NEXTBLOCKINFREELIST(ptr);
        }
        if(ptr != NULL){
            break;
        }
        ++index;
    }
    char*res_ptr = NULL;
    if(ptr != NULL){
        res_ptr = place(ptr,new_size);
    }else{
        size_t extendsize = MAX(new_size,CHUNKSIZE);
        if( (ptr = extend_heap(extendsize)) != NULL){
            res_ptr = place(ptr,new_size);
        }else{
            printf("error\n");
        }
    }
//    printf("in malloc res_pr = %p size = %d\n",res_ptr,new_size);
    return res_ptr;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
//    printf("now free ptr = %p size = %d\n",ptr,SIZE(HDPTR(ptr)));
    size_t size = SIZE(HDPTR(ptr));
    PUT(HDPTR(ptr),size);
    PUT(FTPTR(ptr),size);
    insert_node(ptr,size);
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    if(size == 0){
        return NULL;
    }
    size_t new_size = MAX(ALIGN(size+DSIZE),2*DSIZE);
    size_t current_block_size = SIZE(HDPTR(ptr));
//    printf("now in realloc %p old_size = %d size = %d\n",ptr,current_block_size,new_size);
    char*new_ptr ;
    if(current_block_size >= new_size){
        return ptr;
    }

    size_t next_block_size = SIZE(HDPTR(NEXTBLOCK(ptr)));
    int next_block_allocated = TAG(HDPTR(NEXTBLOCK(ptr)));
    char *next_block_ptr = NEXTBLOCK(ptr);

    // cannot combine the prev block because memcpy will overlap

    if(!next_block_allocated && next_block_size > 0){
        size_t size_combined = current_block_size + next_block_allocated;
        if(size_combined >= new_size){
            delete_node(next_block_ptr);
            PUT(HDPTR(ptr), PACK(size_combined,1));
            PUT(FTPTR(next_block_ptr),PACK(size_combined,1));
            place(ptr,new_size);
            return ptr;
        }
    }
    new_ptr = mm_malloc(new_size);
    if(new_ptr == NULL){
        return NULL;
    }
    memcpy(new_ptr,ptr,MIN(current_block_size,size));
    mm_free(ptr);
    return new_ptr;
}



