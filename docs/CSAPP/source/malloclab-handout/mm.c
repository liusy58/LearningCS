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

#include "mm.h"
#include "memlib.h"

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


#define SIZE(ptr) (((unsigned int*)ptr) & ~0x7)
#define TAG(ptr) (((unsigned int*)ptr) & 0x1)
#define PUT(ptr,value) (((unsigned int*)ptr) = ((unsigned int)value))
#define PACK(size,tag) ((size) | (tag))
#define HDPTR(ptr) (((char*)(ptr) - WSIZE))
#define FTPTR(ptr) (((char*)(ptr) + SIZE(HDPTR(ptr)) - DSIZE))
#define GETSIZE(ptr) (SIZE(HDPTR(ptr)))
// physically

#define PREVBLOCK(ptr) (((char*)(ptr)) - SIZE((char*)(ptr) - DSIZE))
#define NEXTBLOCK(ptr) ((char*)(ptr) + SIZE(HDPTR(ptr)))
#define NEXTBLOCKHEADPTR(ptr) (((char*)(ptr) + SIZE(HDPTR(ptr)) - WSIZE))

#define SETPTR(ptr,val) ((unsigned int*)(ptr) = val)

#define NEXTBLOCKINFREELIST(ptr) ((char*)(ptr) + WSIZE)
#define PREVBLOCKINFREELIST(ptr) ((char*)(ptr))


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

void *place(void *ptr, size_t asize){
    size_t before_size = SIZE(HDPTR(ptr));
    if(before_size - asize < MINBLOCKSIZE){
        SETPTR(HDPTR(ptr), PACK(before_size,ALLOCATED));
        delete_node(ptr);
        return ptr;
    }
    size_t new_size = before_size - asize;
    SETPTR(HDPTR(ptr),PACK(asize,ALLOCATED));
    SETPTR(FTPTR(ptr),PACK(asize,ALLOCATED));
    SETPTR(HDPTR(NEXTBLOCK(ptr)),new_size);
    SETPTR(FTPTR(NEXTBLOCK(ptr)),new_size);
    delete_node(ptr);
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
    char* prev = NULL, *current = segregated_free_lists[index];
    while(current != NULL && current != ptr){
        prev = current;
        current = NEXTBLOCKINFREELIST(current);
    }

    char* next = NEXTBLOCKINFREELIST(ptr);
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

    if(!prev_need_coalesce && !next_need_coalesce){
        return ptr;
    }else if(!prev_need_coalesce && next_need_coalesce){
        char* new_header = HDPTR(ptr);
        char* new_footer = FTPTR(NEXTBLOCK(ptr));
        size_t new_size = size + next_block_size;
        SETPTR(new_header,size);
        SETPTR(new_footer,size);
        delete_node(NEXTBLOCK(ptr));
        delete_node(ptr);
        insert_node(new_header,new_size);
    }else if(prev_need_coalesce && !next_need_coalesce){
        char* new_header = HDPTR(PREVBLOCK(ptr));
        char* new_footer = FTPTR(ptr);
        size_t new_size = size + prev_block_size;
        SETPTR(new_header,size);
        SETPTR(new_footer,size);
        delete_node(PREVBLOCK(ptr));
        delete_node(ptr);
        insert_node(new_header,new_size);
    }else {
        char* new_header = HDPTR(PREVBLOCK(ptr));
        char* new_footer = FTPTR(NEXTBLOCK(ptr));
        size_t new_size = size + next_block_size + prev_block_size;
        SETPTR(new_header,size);
        SETPTR(new_footer,size);
        delete_node(PREVBLOCK(ptr));
        delete_node(ptr);
        delete_node(NEXTBLOCK(ptr));
        insert_node(new_header,new_size);
    }
    return NULL;
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
        current = NEXTBLOCKINFREELIST(current);
    }
    if(current == NULL){
        if(prev == NULL){
            segregated_free_lists[index] = ptr;
            SETPTR(PREVBLOCKINFREELIST(ptr),NULL);
            SETPTR(NEXTBLOCKINFREELIST(ptr),NULL);
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
}

void *extend_heap(size_t size){
    char* ptr;
    if((ptr = mem_sbrk(size)) == (void)-1){
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
    if((heap_start_pointer = mem_sbrk(4 * WSIZE)) == (void)-1){
        return -1;
    }
    PUT(heap_start_pointer + 0 * WSIZE, 0);
    PUT(heap_start_pointer + 1 * WSIZE, 0);
    PUT(heap_start_pointer + 2 * WSIZE, 0);
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
//    int newsize = ALIGN(size + SIZE_T_SIZE);
//    void *p = mem_sbrk(newsize);
//    if (p == (void *)-1)
//        return NULL;
//    else {
//        *(size_t *)p = size;
//        return (void *)((char *)p + SIZE_T_SIZE);
//    }
    if( size == 0){
        return NULL;
    }

    size_t new_size = MAX(MINBLOCKSIZE, ALIGN(size + DSIZE));
    int index = 0;
    size_t sz = new_size;
    while(sz > 1){
        index++;
        sz >>= 1;
    }
    char * ptr = NULL;
    while(index < LISTSZ){
        char * ptr = segregated_free_lists[index];
        while(ptr!=NULL && new_size > SIZE(HDPTR(ptr))){
            ptr = NEXTBLOCKINFREELIST(ptr);
        }
        if(ptr != NULL){
            break;
        }
        ++index;
    }
    if(ptr != NULL){
        return place(ptr,new_size);
    }else{
        printf("error");
    }
    return NULL;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
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
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
        return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
        copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}



