/* On Mac OS (aka OS X) the ucontext.h functions are deprecated and requires the
   following define.
*/
#define _XOPEN_SOURCE 700

/* On Mac OS when compiling with gcc (clang) the -Wno-deprecated-declarations
   flag must also be used to suppress compiler warnings.
*/

#include <signal.h>   /* SIGSTKSZ (default stack size), MINDIGSTKSZ (minimal
                         stack size) */
#include <stdio.h>    /* puts(), printf(), fprintf(), perror(), setvbuf(), _IOLBF,
                         stdout, stderr */
#include <stdlib.h>   /* exit(), EXIT_SUCCESS, EXIT_FAILURE, malloc(), free() */
#include <ucontext.h> /* ucontext_t, getcontext(), makecontext(),
                         setcontext(), swapcontext() */
#include <stdbool.h>  /* true, false */

#include "sthreads.h"

/* Stack size for each context. */
#define STACK_SIZE SIGSTKSZ*100
#define MAX_THREADS 10
#define FREE 0

/*******************************************************************************
                             Global data structures

                Add data structures to manage the threads here.
********************************************************************************/
thread_t *ctcb_main, *curr_thread;

static thread_t thread_pool[MAX_THREADS];
static thread_t thread_sched;
static uint curr_thread_id;



/*******************************************************************************
                             Auxiliary functions

                      Add internal helper functions here.
********************************************************************************/
uint curr_thread(){

  return curr_thread_id;
}

static void thread_wrapper(Func passing_func, void *arg, uint *status){
  passing_func(arg);
  *status = FREE;
}


void init_context_main(){
  ctcb_main = (thread_t *) malloc(sizeof(thread_t));
  ctcb_main->ctx = (ucontext_t *) malloc(sizeof(ucontext_t));

  ctcb_main->state = RUNNING;
  ctcb_main->tid = -1;

  curr_thread = ctcb_main;
}



/*******************************************************************************
                    Implementation of the Simple Threads API
********************************************************************************/


int  init(){

  init_context_main();
  return 1;
}

static void thread_make(thread_t* thr){
  getcontext(&thr->ctx);
  thr->ctx.uc_stack.ss_sp = uthread->stack;
  thr->ctx.uc_stack.ss_size = STACK_SIZE;
  thr->ctx.uc_stack.ss_flags = 0;
  thr->ctx.uc_link = NULL;
  thr->status = READY;
}

/*
tid_t spawn(ucontext_t *ctx_new, void (*start)(), ucontext_t *ctx_nxt){

  //ucontext_t *thread_ctxt = (ucontext_t *) malloc(sizeof(ucontext_t));
  void *new_stack = malloc(STACK_SIZE);

  if(new_stack == NULL){
    perror("Allocating stack");
    exit(EXIT_FAILURE);
  }

  if(getcontext(ctx_new) < 0){
    perror("getcontext");
    exit(EXIT_FAILURE);
  }

  ctx_new->uc_link            = ctx_nxt;
  ctx_new->uc_stack.ss_sp     = new_stack;
  ctx_new->uc_stack.ss_size   = STACK_SIZE;
  ctx_new->uc_stack.ss_flags  = 0;

  thread_t *ntcb = (thread_t *) malloc(sizeof(thread_t));
  if(ntcb == NULL){
    perror("\nError allocating memory");
    exit(EXIT_FAILURE);
  }

  ntcb->ctx = ctx_new;
  ntcb->state = READY;
  ntcb->tid = curr_thrd_id++;

  makecontext(ctx_new, start, 0);

  return ntcb->tid;
  //return -1;
}*/

tid_t spawn(uint* tid, void (*start)(), void* arg){

  uint i;
  for(i = 0; i<MAX_THREADS; ++i)
    if(thread_pool[i] == FREE);
      break;

  *tid = i;
  printf("thread tid %u created\n", *tid);
  thread_make(&thread_pool[i]);
  thread_pool[i].ctx.uc_link = 

}


void yield(){

  //if(curr_thrd_id > 0){

  switch(1){
    case 1:
      swapcontext(&ctx_1, &ctx_2);
      break;
    case 2:
      swapcontext(&ctx_2, &ctx_3);
      break;
    case 3:
      swapcontext(&ctx_3, &ctx_1);
      break;
    default:
      //swapcontext(&(ctx_1->ctx), ctxt_main);
      perror("yield error");
      break;
  }
//}

}

void  done(){
}

tid_t join() {
  return -1;
}
