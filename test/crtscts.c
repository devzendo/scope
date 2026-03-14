#include <termios.h>
#include <stdio.h>
void main()
{
  printf("CS8     is 0x%lx 0%lo\n", CS8, CS8);
  printf("CRTSCTS is 0x%lx 0%lo\n", CRTSCTS, CRTSCTS);
}

