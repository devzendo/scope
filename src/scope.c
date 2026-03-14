/*******************************************************************************
***
*** Filename         : scope.c
*** Purpose          : Simple RS232-C Line Monitor/Analyser, uses special serial
***                    cable.
*** Author           : Matt J. Gumbley
*** Last updated     : 20/02/02
***
********************************************************************************
***
*** Modification Record
*** 20/02/02 MJG Build fixed for RH7.x, from a patch by Grant Edwards.
***
*******************************************************************************/

#include <sys/ioctl.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <signal.h>
#include <stdlib.h>

#include "global.h"
#include "util.h"
#include "asy.h"

static int quit = FALSE;
static char *progname;
static char *defports[] = { "/dev/ttyS0", "/dev/ttyS1" };
static int defbps=B19200;
#define PORTMAX 64
static char ports[2][PORTMAX];
static char portfds[2];
static int portstats[2];
static int lastportstats[2];
#define BAUDMAX 10
static char baudstr[BAUDMAX];
static int verbose = FALSE;
static int continuous = FALSE;
static int justdata = FALSE;
static int animate = FALSE;

void sighandler(int signal)
{
  quit=TRUE;
}

static void banner()
{
  printf("scope v%2.2f - a simple serial line analyser\n", VERSION);
  printf("(C) 1999,2000,2002 Matt J. Gumbley, matt@gumbley.demon.co.uk\n");
  printf("http://www.gumbley.demon.co.uk/scope.html\n\n");
}

static void usage()
{
  banner();
  printf("Syntax:\n");
  printf("  %s [options]\n", progname);
  printf("Options:\n");
  printf("  -b<speed> Set port speed. <speed> is 300 to 115200 [19200]\n");
  printf("  -p1<port> Set rx port. <port> is something like /dev/ttyS0.\n");
  printf("            Default is %s.\n", defports[0]);
  printf("  -p2<port> Set tx port. <port> is something like /dev/ttyS0.\n");
  printf("            Default is %s.\n", defports[1]);
  printf("  -v        Enable verbose operation\n");
  printf("  -c        Enable continuous monitoring (lots of output)\n");
  printf("            This produces time frames even when data is\n");
  printf("            not present, and can help track down timing\n");
  printf("            problems, but can eat your disk.\n");
  printf("  -d        Just the data, Ma'am. Don't monitor control\n");
  printf("            and status lines.\n");
  printf("  -a        Animate a spinner on stderr when data is received.\n");
  printf("            Useful when redirecting to a file to see that\n");
  printf("            something is happening.\n");
  exit(1);
}

static void spinner()
{
static char chars[]="\\-/|";
static int c=0;
  fprintf(stderr,"%c  \r",chars[c++]);
  c&=3;
}

int main(int argc, char *argv[])
{
int i, rxchar;
int portch;
static char *spaces="    ";
static char *spaces3="   ";
static char rxcharbuf[2][5];
char *p;
int bps;
struct timeval tv;
long startsecs;
int anything;
int result;
char *RTS=spaces3;
char *CTS=spaces3;
char *DSR=spaces3;
char *DCD=spaces3;
char *DTR=spaces3;

  /* Initialise sensible defaults, etc. */
  progname = argv[0];
  for (i=0; i<2; i++) {
    strncpy(ports[i], defports[i], PORTMAX);
    strcpy(rxcharbuf[i], spaces);
  }
  bps=defbps;
  strcpy(baudstr,"19200");

  /* Process command line options */
  for (i=1; i<argc; i++) {
    if (argv[i][0]=='-') {
      p=&argv[i][2];
      switch (argv[i][1]) {
        case 'a':
          animate = TRUE;
          break;
        case 'd':
          justdata = TRUE;
          break;
        case 'c':
          continuous = TRUE;
          break;
        case 'v':
          verbose = TRUE;
          break;
        case 'b':
          strncpy(baudstr, p, BAUDMAX);
          if (strcmp(p, "300")==0)
            bps=B300;
          else if (strcmp(p, "600")==0)
            bps=B600;
          else if (strcmp(p, "1200")==0)
            bps=B1200;
          else if (strcmp(p, "2400")==0)
            bps=B2400;
          else if (strcmp(p, "4800")==0)
            bps=B4800;
          else if (strcmp(p, "9600")==0)
            bps=B9600;
          else if (strcmp(p, "19200")==0)
            bps=B19200;
          else if (strcmp(p, "38400")==0)
            bps=B38400;
          else if (strcmp(p, "57600")==0)
            bps=B57600;
          else if (strcmp(p, "115200")==0)
            bps=B115200;
          else
            usage();
          break;
        case 'p':
          portch=argv[i][2];
          if (portch!='1' && portch!='2')
            usage();
          portch-='1';
          strncpy(ports[portch], ++p, PORTMAX);
          /* XXX: check existence, deviceness? */
          break;
        default:
          usage();
      }
    }
    else
      usage();
  }

  /* Trap CTRL-C */
  signal(SIGINT, &sighandler);

  /* Open ports */
  for (i=0; i<2; i++) {
    if ((portfds[i]=asy_open(ports[i], bps)) == -1) {
      printf("port %s open failed\n", ports[i]);
      exit(-1);
    }
  }

  if (verbose) {
    printf("rx port: %s at %s baud\n", ports[0], baudstr);
    printf("tx port: %s\n", ports[1]);
  }

  signal(SIGINT, &sighandler);
  
  /* Record incoming data and control/status line changes */
  gettimeofday(&tv,NULL);
  startsecs = tv.tv_sec;
  while (!quit) {
    anything = continuous;
    for (i=0; i<2; i++) {
      strcpy(&rxcharbuf[i][0], spaces);
      if (asy_test(portfds[i])) {
        anything = TRUE;
        rxchar=asy_getc(portfds[i]);
        rxcharbuf[i][0]=hexdig((rxchar&0xf0)>>4);
        rxcharbuf[i][1]=hexdig(rxchar&0x0f);
        rxcharbuf[i][3]=isprint(rxchar) ? rxchar : '.';
      }
      else {
        rxcharbuf[i][0]=rxcharbuf[i][1]=rxcharbuf[i][3]=' ';
      }
      if (!justdata) {
        /* Get port status */
        if ((result=ioctl(portfds[i], TIOCMGET, &portstats[i])) < 0)
          printf("Couldn't get port stats, error %d\n", result);
      }
        
    }
    if (!justdata) {
      /* Process line flags from first port */
      CTS = (portstats[0] & TIOCM_CTS) ? "CTS" : spaces3;
      DSR = (portstats[0] & TIOCM_DSR) ? "DSR" : spaces3;
      DCD = (portstats[0] & TIOCM_CD)  ? "DCD" : spaces3;
      /* Process line flags from second port */
      RTS = (portstats[1] & TIOCM_CTS) ? "RTS" : spaces3;
      DTR = (portstats[1] & TIOCM_CD)  ? "DTR" : spaces3;
      if (portstats[0] != lastportstats[0] ||
          portstats[1] != lastportstats[1])
        anything = TRUE;
      for (i=0; i<2; i++)
        lastportstats[i]=portstats[i];
    }

    /* Set anything if anything has changed */
    if (anything) {
      if (animate)
        spinner();
      gettimeofday(&tv,NULL);
      if (justdata) {
              /* time      RD TD */
        printf("%6ld.%06ld|%s|%s\n", tv.tv_sec - startsecs, 
               tv.tv_usec, rxcharbuf[0], rxcharbuf[1]);
      }
      else {
              /* time      RD TD CT DS DC RT DT */
        printf("%6ld.%06ld|%s|%s|%s|%s|%s|%s|%s\n", tv.tv_sec - startsecs, 
               tv.tv_usec, rxcharbuf[0], rxcharbuf[1],
               CTS, DSR, DCD, RTS, DTR);
      }
    }
  }
  printf("\n");

  /* Finished */
  for (i=0; i<2; i++)
    asy_close(portfds[i]);

  return 0;
}

