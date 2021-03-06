#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <myth/myth.h>

void * f(void * x) {
  long y = (long)x;
  return (void *)(y * y);
}

#define nthreads 100
int main() {
  myth_thread_t th[nthreads];
  long i;
  for (i = 0; i < nthreads; i++) {
    th[i] = myth_create(f, (void *)i);
  }
  for (i = 0; i < nthreads; i++) {
    void * ret[1];
    myth_join(th[i], ret);
    if (ret[0] != (void *)(i * i)) {
      printf("NG\n");
      return 1;
    }
  }
  printf("OK\n");
  return 0;
}

