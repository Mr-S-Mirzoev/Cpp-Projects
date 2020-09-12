#include <stdio.h>
#include <stdlib.h>
#include "functdef.h"

struct a
{
  int c;
  long d;
  char y;
  unsigned x;
  long long t;
};

FUNCTION_START(void, helloworld, int a, int b)
    printf("%d %d\n", a, b);
    return;
}

int main(int argc, char *argv[])
{
    struct a *current = (struct a*) malloc(sizeof(struct a));
    current->c = 13;
    current->d = 4;
    current->y = 'c';
#ifdef CAST
    helloworld(current);
#else
    helloworld(3, 5);
#endif
    return 0;
}