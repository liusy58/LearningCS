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

static char *segregated_free_lists[LISTSZ];
static char *heap_start_pointer;


#define ALLOCATED 1
#define FREE 0

#define SIZE(ptr) (((unsigned int*)ptr) & ~0x7)
#define PUT(ptr,value) (((unsigned int*)ptr) = ((unsigned int)value))
#define PACK(size,tag) ((size) | (tag))
#define HDPTR(ptr) (((char*)(ptr) - WSIZE))
#define FTPTR(ptr) (((char*)(ptr) + SIZE(HDPTR(ptr)) - DSIZE))
#define GETSIZE(ptr) (SIZE(HDPTR(ptr)))
// physically
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

void *coalesce(void *ptr){
    
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
    int newsize = ALIGN(size + SIZE_T_SIZE);
    void *p = mem_sbrk(newsize);
    if (p == (void *)-1)
        return NULL;
    else {
        *(size_t *)p = size;
        return (void *)((char *)p + SIZE_T_SIZE);
    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{

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



