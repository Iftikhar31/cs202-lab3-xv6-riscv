#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/riscv.h"
#include "user/thread.h"

int thread_create(void *(start_routine)(void *), void *arg) {
  // Allocate a stack of PGSIZE bytes for the thread
  void *stack = malloc(PGSIZE);
  if (stack == 0) {
    return -1;
  }

  // Call clone with the allocated stack
  int tid = clone(stack);
  if (tid < 0) {
    free(stack);
    return -1;
  }

  // For the child thread, execute the start_routine with the argument arg
  if (tid == 0) {
    start_routine(arg);
    exit(0);
  }

  // For the parent thread, return 0 on success
  return 0;
}

void lock_init(struct lock_t *lock) {
  lock->locked = 0; // Unlocked
}

void lock_acquire(struct lock_t *lock) {
  // __sync_lock_test_and_set assigns &lock->locked to 1
  // and returns the previous value. If the previous value was 1,
  // the lock is already held, so we spin until it becomes 0.
  while (__sync_lock_test_and_set(&lock->locked, 1) == 1) {
    // weeeeeee
  }
}

void lock_release(struct lock_t *lock) {
  // set lock->locked to 0 atomically
  __sync_lock_release(&lock->locked);
}
