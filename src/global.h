/*******************************************************************************
***
*** Filename         : global.h
*** Purpose          : Some global definitions
*** Author           : Matt J. Gumbley
*** Created          : 19/01/97
*** Last updated     : 26/01/97
***
********************************************************************************
***
*** Modification Record
***
*******************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef LINUX
typedef unsigned char  byte;
typedef unsigned short word16;
typedef signed short sword16;
typedef unsigned int   word32;
#define BYTE byte
#define WORD16 word16
#define SWORD16 sword16
#define WORD32 word32
#endif

#endif /* GLOBAL_H */

