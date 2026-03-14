#include "system.h"
#include "global.h"

void main()
{
#ifdef __LITTLE_ENDIAN
  printf("This is a Little-Endian machine\n");
#else
  printf("This is a Big-Endian machine\n");
#endif
  printf("sizeof byte is %d\n",sizeof(byte));
  printf("sizeof word16 is %d\n",sizeof(word16));
  printf("sizeof word32 is %d\n",sizeof(word32));
  printf("sizeof unsigned int is %d\n",sizeof(unsigned int));
}

