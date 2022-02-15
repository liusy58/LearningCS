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
    "siyu liu",
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
#define INITCHUNKSIZE (1<<6)
#define CHUNKSIZE (1<<12)

#define LISTLIMIT    20
#define REALLOC_BUFFER  (1<<7)



#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIX(x,y) ((x)<(y)?(x):(y))

// pack a size and allocated bit into a word
#define PACK(size,alloc) ((size) | (alloc))

//read and write a word at address p
#define GET(p) (*(unsigned int*)p)
// put a value with its previous tag
#define PUT(p,val) (*(unsigned int*)(p) = (val)|(GET_TAG(p)))
#define PUT_NOTAG(p,val) (*(unsigned int*)(p) = (val))

//store predcessor or successor pointer for free blocks
#define SET_PTR(p,ptr) (*(unsigned int*)(p) = (unsigned int)(ptr))

// read the size and alllcation bit from address p
#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define GET_TAG(p) (GET(p) & 0x2)
#define SET_RATAG(p) (GET(p) |= 0x2)
#define RM_RATAG(p) (GET(p) &= ~0x2)

// address of block's header and footer
#define HDRP(ptr) ((char*)(ptr) - WSIZE)
#define FTRP(ptr) ((char*)(ptr) + GET_SIZE(HDRP(ptr)) - DSIZE)


// Address of (physically) next and previous blocks
#define NEXT_BLKP(ptr) ((char *)(ptr) + GET_SIZE((char *)(ptr) - WSIZE))
#define PREV_BLKP(ptr) ((char *)(ptr) - GET_SIZE((char *)(ptr) - DSIZE))

// Address of free block's predecessor and successor entries
#define PRED_PTR(ptr) ((char *)(ptr))
#define SUCC_PTR(ptr) ((char *)(ptr) + WSIZE)

// Address of free block's predecessor and successor on the segregated list
#define PRED(ptr) (*(char **)(ptr))
#define SUCC(ptr) (*(char **)(SUCC_PTR(ptr)))

// Global var
void *segregated_free_lists[LISTLIMIT];


// Functions
static void *extend_heap(size_t size);
static void *coalesce(void *ptr);
static void *place(void *ptr, size_t asize);
static void insert_node(void *ptr, size_t size);
static void delete_node(void *ptr);




void insert_node(void *ptr, size_t size){
    int index = 0;
    void search_ptr = ptr;
    void insert_ptr = NULL;

    while( (index < LISTLIMIT - 1) && (size > 1) ){
        size >>= 1;
        index++;
    }
    search_ptr = segregated_free_lists[index];

    while()
}


void *extend_heap(size_t size){
    void *ptr;
    size_t  asize = ALIGN(size);

    if((ptr = mem_sbrk(asize)) == (void*)-1){
        return NULL;
    }

    // set header and footer

    PUT_NOTAG(HDRP(ptr), PACK(asize,0));
    PUT_NOTAG(FTRP(ptr), PACK(asize,0));
    PUT_NOTAG(HDRP(NEXT_BLKP(ptr)), PACK(0,1)); // ?
    insert_node(ptr,asize);

    return coalesce(ptr);
}


/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    int index ;
    char * heap_start;

    for(index=0;index<LISTLIMIT;++index){
        segregated_free_lists[index] = NULL;
    }
    if((heap_start = mem_sbrk(4 * WSIZE) ) == (void*)-1){
        return -1;
    }
    PUT_NOTAG(head_start + (0 * WSIZE), 0);
    PUT_NOTAG(head_start + (1 * WSIZE), PACK(DSIZE, 1));
    PUT_NOTAG(head_start + (2 * WSIZE), PACK(DSIZE, 1));
    PUT_NOTAG(head_start + (3 * WSIZE), PACK(0, 1));
    if(extend_heap(INITCHUNKSIZE) == NULL){
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














