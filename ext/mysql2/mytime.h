#ifndef _TIME_H_
#define _TIME_H_

#include <time.h>
#include <sys/time.h>
#include <stdint.h>

static inline uint64_t
rdtsc()
{
  uint64_t ret;
#if defined _LP64
  asm volatile
    (
     "rdtsc\n\t"
     "mov $32, %%rdx\n\t"
     "orq %%rdx, %%rax\n\t"
     "mov %%rax, %0\n\t"
     :"=m"(ret)
     :
     :"%rax", "%rdx"
     );
#else
  asm volatile
    (
     "rdtsc\n\t"
     "mov %%eax, %0\n\t"
     "mov %%edx, %1\n\t"
     :"=m"(((uint32_t*)&ret)[0]), "=m"(((uint32_t*)&ret)[1])
     :
     :"%eax", "%edx"
     );
#endif
  return ret;
}

static inline double
gettimeofday_sec()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + (double)tv.tv_usec*1e-6;
}

#endif /* _TIME_H_ */
