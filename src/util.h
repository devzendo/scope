/*******************************************************************************
***
*** Filename         : util.h
*** Purpose          : Definitions of utility functions
*** Author           : Matt J. Gumbley
*** Created          : 20/01/97
*** Last updated     : 08/02/99
***
********************************************************************************
***
*** Modification Record
***
*******************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#define CCITT_CRC_GEN 0x1021

extern char *diagchar(int);
extern char hexdig(int);
extern void hexdump(unsigned char *, long);
extern word16 read_word16(byte *);
extern word32 read_word32(byte *);
extern void write_word16(byte *, word16);
extern void write_word32(byte *, word32);
extern word16 crc(byte *, int);

#endif /* UTIL_H */
