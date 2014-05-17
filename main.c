#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define KB 1024
#define MB 1024*1024
#define MLN 1000000

#define TWICE(x) x x
#define US 1000
#define NS 1000000

static inline uint64_t get_cycles()
{
  uint64_t t;
  __asm volatile ("rdtsc" : "=A"(t));
  return t;
}


void shuffle(void **p, size_t len) {
	size_t i;
	for (i = 0; i < len; i += step) {
                size_t x = rand() % len;
		*(p + i) = p + x;
	}
}

int main(int argc, char *argv[])
{
	bool random_access = false;
	if (argc > 1 && !strcmp(argv[1], "-r")) random_access = true;

	int step = 256/sizeof(void *);
	
	unsigned long long array_size_bytes;
	for (array_size_bytes = sizeof(void *) * KB;
		 array_size_bytes <= MB; array_size_bytes += sizeof(void *) * KB)  {	
		
		void **p = (void **)malloc(array_size_bytes);
		int array_size = array_size_bytes/sizeof(void *);
		if (!p) {
			printf("Memory allocating failed.\n");
			return -1;
		}	

		int i;
		for (i = 0; i < array_size; i += step){
			*(p + i) = p + i + step;
		}
		p[i - step] = p;
		if (random_access) shuffle(p, array_size);
		unsigned long long k;
		void **t = p;

		uint64_t cycles;
		cycles = get_cycles();
		for (k = 0; k <= MLN / 256; k++){ 
			TWICE(TWICE(TWICE(TWICE(TWICE(TWICE(TWICE(TWICE( t = (void**)*t; ))))))))
		}
		cycles = get_cycles() - cycles;

		uint64_t time_usec  = cycles;
		printf("%llu %d: %d\n", array_size_bytes/KB, time_usec,t );
		free(p);
	}
	return 0;
}
