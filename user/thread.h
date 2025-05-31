struct lock_t {
  uint locked; // 1 if the lock is held, 0 otherwise
};

typedef struct lock_t lock_t;

int thread_create(void *(start_routine)(void *), void *arg);
void lock_init(struct lock_t *lock);
void lock_acquire(struct lock_t *lock);
void lock_release(struct lock_t *lock);
