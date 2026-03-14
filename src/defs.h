/*******************************************************************************
***
*** Filename         : defs.h
*** Purpose          : Preprocessor Definitions for SIBO Comms/NCP
*** Author           : Matt J. Gumbley, borrowed heavily from Michael and SDK
*** Created          : 08/01/99
*** Last updated     : 08/01/99
***
********************************************************************************
***
*** Modification Record
***
*******************************************************************************/

#ifndef DEFS_H
#define DEFS_H

#define E_MAX_NAME 12

/* Asynchronous comms definitions */

/* Serial port characteristics */
typedef struct
{
  unsigned char tbaud; /* transmit Baud rate selector */ 
  unsigned char rbaud; /* receive Baud rate selector */ 
  unsigned char frame; /* number of data,parity and stop bits */ 
  unsigned char parity; /* parity selector */ 
  unsigned char hand; /* handshake flags */ 
  unsigned char xon; /* XON character */ 
  unsigned char xoff; /* XOFF character */ 
  unsigned char flags; /* ignore parity errors/dont drive DTR changing chars */ 
  unsigned long int tmask; /* terminator mask */ 
} P_SRCHAR;

/* Baud rates */
#define P_BAUD_50  0x01
#define P_BAUD_75  0x02
#define P_BAUD_110  0x03
#define P_BAUD_134  0x04
#define P_BAUD_150  0x05
#define P_BAUD_300  0x06
#define P_BAUD_600  0x07
#define P_BAUD_1200 0x08
#define P_BAUD_1800 0x09
#define P_BAUD_2000 0x0A
#define P_BAUD_2400 0x0B
#define P_BAUD_3600 0x0C
#define P_BAUD_4800 0x0D
#define P_BAUD_7200 0x0E
#define P_BAUD_9600 0x0F
#define P_BAUD_19200 0x10
#define P_BAUD_38400 0x11
#define P_BAUD_56000 0x12
#define P_BAUD_115000 0x13
/* allocation of frame bits */
#define P_DATA_FRM 0x0f /* number of data bits mask */ 
#define P_DATA_5 0 /* 5 data bits */ 
#define P_DATA_6 1 /* 6 data bits */ 
#define P_DATA_7 2 /* 7 data bits */ 
#define P_DATA_8 3 /* 8 data bits */ 
#define P_TWOSTOP 0x10 /* 2 stop bits if set,1 if clear */ 
#define P_PARITY 0x20 /* 1 parity bit if set,0 if clear */ 
/* parity - ignored unless P_PARITY is set */
#define P_PAR_EVEN 1 /* even parity */ 
#define P_PAR_ODD 2 /* odd parity */ 
#define P_PAR_MARK 3 /* mark parity */ 
#define P_PAR_SPACE 4 /* space parity */ 
/* handshaking control */
#define P_OBEY_XOFF 0x01 /* respond to received XOFF (and XON) if set */ 
#define P_SEND_XOFF 0x02 /* send XOFF/XON to control receive buffer if set */ 
#define P_IGN_CTS 0x04 /* ignore the state of CTS if set */ 
#define P_OBEY_DSR 0x08 /* obey the state of DSR if set */ 
#define P_FAIL_DSR 0x10 /* fail if DSR goes OFF if set */ 
#define P_OBEY_DCD 0x20 /* obey the state of DCD if set */ 
#define P_FAIL_DCD 0x40 /* fail if DCD goes OFF if set */ 
/* flags control */
#define P_IGNORE_PARITY 0x01  /* ignore parity errors */ 
/* For P_FCTRL function */
#define P_SRCTRL_CTS 0x01
#define P_SRCTRL_DSR 0x02
#define P_SRCTRL_DCD 0x04
#define P_SRCTRL_RTS 0x08
#define P_SRCTRL_DTR 0x10
#define P_SRDTR_ON 1 /* to set DTR to MARK */ 
#define P_SRDTR_OFF 2 /* to set DTR to SPACE */ 
/* Bit masks for P_FINQ function */
#define P_SRINQ_50  0x0001
#define P_SRINQ_75  0x0002
#define P_SRINQ_110  0x0004
#define P_SRINQ_134  0x0008
#define P_SRINQ_150  0x0010
#define P_SRINQ_300  0x0020
#define P_SRINQ_600  0x0040
#define P_SRINQ_1200 0x0080
#define P_SRINQ_1800 0x0100
#define P_SRINQ_2000 0x0200
#define P_SRINQ_2400 0x0400
#define P_SRINQ_3600 0x0800
#define P_SRINQ_4800 0x1000
#define P_SRINQ_7200 0x2000
#define P_SRINQ_9600 0x4000
#define P_SRINQ_19200 0x8000
/* second baud rate word */
#define P_SRINQ_38400 0x0001
#define P_SRINQ_56000 0x0002
/* 2nd set of info */
#define P_SRINQ_DATA5 0x0001 /* supports 5 data bits */ 
#define P_SRINQ_DATA6 0x0002 /* supports 6 data bits */ 
#define P_SRINQ_DATA7 0x0004 /* supports 7 data bits */ 
#define P_SRINQ_DATA8 0x0008 /* supports 8 data bits */ 
#define P_SRINQ_STOP2 0x0010 /* supports 2 stop bits (as well as 1) */ 
#define P_SRINQ_PAREVEN 0x0020 /* supports even parity */ 
#define P_SRINQ_PARODD 0x0040 /* supports odd parity */ 
#define P_SRINQ_PARMARK 0x0080 /* supports mark parity */ 
#define P_SRINQ_PARSPACE 0x0100 /* supports space parity */ 
#define P_SRINQ_SETDTR 0x0200 /* can set DTR */ 
#define P_SRINQ_SPLIT 0x400 /* supports split Baud rates */ 
#define P_SRINQ_XONXOFF 0x800 /* Supports soft xon/xoff characters */ 

/* what options are selected */
#define P_MDM_TONE 0x01 /* as opposed to PULSE dialling (default) */ 
#define P_MDM_BELL 0x02 /* as opposed to CCITT (default) */ 
#define P_MDM_NO_MODULATION 0x04 /* as opposed to CCITT or BELL */ 
#define P_MDM_CONSTANT_SPEED 0x08 /* modem has constant speed interface */ 
/* Error correction types */
#define P_MDM_ERRCORRECT_NONE  0  /* NO error correction */ 
#define P_MDM_ERRCORRECT    1  /* some form of error correction (ARQ)*/ 
#define P_MDM_ERRCORRECT_MNP  2  /* MNP error correction being used */ 
#define P_MDM_ERRCORRECT_V42  3  /* V42 error correction being used */ 
typedef struct
{
  unsigned short int supported;  /* what baud rates are supported by modem */ 
  unsigned short int options;   /* flags which options are selected */ 
  unsigned short int baudrate;   /* baud rate currently running at/to run at */ 
  unsigned char chand;    /* connected handshaking */ 
  unsigned char ichand;    /* incoming call handshaking */ 
} P_MDMCHR;

/* PLP Protocol */

/* Packet types (high nibble of type byte) */
#define PLP_MSG_ACKNOWLEDGE  0x00
#define PLP_MSG_DISCONNECT   0x10
#define PLP_MSG_LINK_REQUEST 0x20
#define PLP_MSG_DATA         0x30

#define PLP_MSG_MASK         0xF0
#define PLP_SEQUENCE_MASK    0x0F

/* NCP Protocol */

#define NCP_VERSION_NUMBER      2       /* We're just a v2 - what's the diff? */
#define NCLINK_VERSION_NUMBER   3       /* As returned by the 3c */
#define NCLINK_MINOR_VERNO      1

/* Informational data obtained by supervisory reads */
#define PHYS_LINK_FAILED        0       /* Link layer has failed*/
#define PHYS_CONNECT_FAILED     1       /* Waiting for connection failed */
#define PHYS_CHARS_FAILED       2       /* Setting serial characteristics failed */
#define PHYS_INIT_FAILED        3       /* Initialization of modem failed */
#define PHYS_DIAL_FAILED        4       /* Dialling phone number failed */
#define PHYS_MDMCONFIG_FAILED   5       /* additional modem config failed */
#define PHYS_PHYS_LINK_ESTABLISHED 6    /* A physical link established */
#define PHYS_WAITING_FOR_CALL   7       /* Physical layer waiting for call */
#define PHYS_DIALLING_NUMBER    8       /* Physical layer dialling */
#define PHYS_CONFIGURING_MODEM  9       /* configuring modem */
#define PHYS_NCP_LINK_ESTAB_OK  10       /* Ncp link established OK */
#define PHYS_NCP_LINK_ESTAB_NEW_NCP 11  /* Talking to different Ncp */
#define PHYS_NCP_LINK_ESTAB_INVALID_VER  12 /* Remote NCP is V1.0 !!*/
#define PHYS_NCP_LINK_END 13            /* remote NCP is terminating */
#define PHYS_SERCONFIG_FAILED   14      /* serial port not there */

#define MAX_DVR_NAME    10   /* Max device driver name size (incl zero term) */
#define MAX_PHONE_NO    40   /* Max phone number length */
#define MAX_MODEM_CMD   40   /* Max extra modem config */

/* Control functions to perform */
#define NCLINK_CTRL_RETRY   0
#define NCLINK_CTRL_EXIT    1
#define NCLINK_CTRL_NEWNCP_OK   2
#define NCLINK_CTRL_NEW_CONFIG  3

typedef struct
{
  P_SRCHAR sch;
  P_MDMCHR mch;
  WORD16 errcorrect;           /* what sort of error correction modem using */
  WORD16 connectbaud;          /* baud rate at which connected */
  BYTE serdvr[MAX_DVR_NAME];
  BYTE mdmdvr[MAX_DVR_NAME];
  BYTE masdvr[MAX_DVR_NAME];
  BYTE lnkdvr[MAX_DVR_NAME];
  BYTE phoneno[MAX_PHONE_NO];
  BYTE mdmconf[MAX_MODEM_CMD];
} DVRS;

typedef struct
{
  WORD16 vers;      /* Remote NCP sofware version */
  WORD32 id;           /* Remote NCP id */
} REM_NCP;

typedef union
{
  REM_NCP remncp;     /* Remote NCP info */
  DVRS dvrs;          /* Driver names, phone number */
} PHY_INFO;

typedef struct          /* Physical layer status information */
{
  WORD16 cmdtype;      /* Info type */
  WORD16 errnum;         /* Error number if applicable to type */
  PHY_INFO p;         /* Physical layer info */
} NCLINK_INFO;

typedef struct          /* Network sense data struct */
{
  WORD16 chanused;     /* True if channel being used else False */
  WORD32 xmitK;        /* number K bytes transmitted */
  WORD32 recvK;        /* number K bytes received */
  BYTE procname[E_MAX_NAME+2]; /* Process name that owns channel */
} NCLINK_SREC;

/* Inter controller message types */
#define NCON_MSG_DATA_XOFF     1
#define NCON_MSG_DATA_XON      2
#define NCON_MSG_CONNECT_TO_SERVER 3
#define NCON_MSG_CONNECT_RESPONSE  4
#define NCON_MSG_CHANNEL_CLOSED   5
#define NCON_MSG_NCP_INFO      6    /* MUST BE 6 for older versions */ 
#define NCON_MSG_CHANNEL_DISCONNECT 7
#define NCON_MSG_NCP_END      8


/* RFSV Protocol */

/* Packet types */
#define RFSV_FOPEN 0
#define RFSV_FCLOSE 2
#define RFSV_FREAD 4
#define RFSV_FDIRREAD 6
#define RFSV_FDEVICEREAD 8
#define RFSV_FWRITE 10
#define RFSV_FSEEK 12
#define RFSV_FFLUSH 14
#define RFSV_FSETEOF 16
#define RFSV_RENAME 18
#define RFSV_DELETE 20
#define RFSV_FINFO 22
#define RFSV_SFSTAT 24
#define RFSV_PARSE 26
#define RFSV_MKDIR 28
#define RFSV_OPENUNIQUE 30
#define RFSV_STATUSDEVICE 32
#define RFSV_PATHTEST 34
#define RFSV_STATUSSYSTEM 36
#define RFSV_CHANGEDIR 38
#define RFSV_SFDATE 40
#define RFSV_RESPONSE 42

/* Open mode flags */
#define P_FOPEN 0x0000 /* Open i/o service */ 
#define P_FCREATE 0x0001 /* Create file */ 
#define P_FREPLACE 0x0002 /* Replace file */ 
#define P_FAPPEND 0x0003 /* Append records */ 
#define P_FUNIQUE 0x0004 /* Unique file open */ 
#define P_FSER_MASK 0x000f /* File service mask */ 
#define P_FSTREAM 0x0000 /* Stream access to a binary file */ 
#define P_FSTREAM_TEXT 0x0010 /* Stream access to a text file */ 
#define P_FTEXT 0x0020 /* Record access to a text file */ 
#define P_FDIR 0x0030 /* Record access to a directory file */ 
#define P_FFORMAT 0x0040 /* Format a device */
#define P_FDEVICE 0x0050 /* Record access to device name list */ 
#define P_FNODE 0x0060 /* Record access to node name list */ 
#define P_FMT_MASK 0x00f0 /* File format mask */ 
#define P_FUPDATE 0x0100 /* Read and write access */ 
#define P_FRANDOM 0x0200 /* Random access */ 
#define P_FSHARE 0x0400 /* File can be shared */ 
#define P_FACC_MASK 0x0f00 /* mask for access types */ 
#define P_FLOWDENSITY  0x1000

/* p_io/p_iow function constants */
/* Generic I/O functions */
#define P_FPANIC 0 /* Panic the device */ 
#define P_FREAD 1 /* Read */ 
#define P_FWRITE 2 /* Write */ 
#define P_FCLOSE 3 /* Close */ 
#define P_FCANCEL 4 /* Cancel io */ 
#define P_FATTACH 5 /* attach this pseudo device */ 
#define P_FDETACH 6 /* detach this pseudo device */ 
#define P_FSET 7 /* set channel characteristics */ 
#define P_FSENSE 8 /* sense channel characteristics */ 
#define P_FFLUSH 9 /* Flush buffers */ 

/* Now follows the device specific functions */
/* Timer device driver */
#define P_FRELATIVE P_FREAD /* Relative timer */ 
#define P_FABSOLUTE P_FWRITE /* Absolute timer */ 
/* Files */
#define P_FSEEK 10 /* Seek */ 
#define P_FSETEOF 11 /* Set end of file */ 
/* Data Link I/O + wserv */
#define P_FCONNECT 10 /* Queue a link connect request */ 
#define P_FDISCONNECT 11 /* Disconnect the link */ 
/* wserv functions */
#define P_FWRITE_REPLY 12 /* P_FWRITE + read a reply from the server */ 
/* Serial/llmac */
#define P_FTEST 10 /* return no. of bytes in serial receieve buffer */ 
#define P_FCTRL 11 /* serial port control lines */ 
#define P_FINQ 12 /* inquire of device capabilities */ 
#define P_FRSUPER 13 /* read a supervisory frame (p_llmac) */ 
#define P_FSTOP 14 /* stop LLMAC mode */ 
#define P_FSTART 15 /* start LLMAC mode */ 
/* Serial LDD to Serial PDD I/O defines */
#define P_FENABLE 16 /* Enable transmit interrupts */ 
#define P_FSETINT 17 /* set the serial Interrupt code ptrs */
/* modem functions */
#define P_FMINIT 16 /* modem initialization function */ 
#define P_FMDIAL 17 /* modem dial function */ 
#define P_FMWAITCALL 18 /* wait for an incoming call */ 
#define P_FMSENSE 19 /* Sense Modem characteristics */ 
#define P_FMSET 20 /* Set Modem characteristics */ 
#define P_FMCANCEL 21 /* Cancel outstanding mode request */ 
#define P_FMWRITE 22 /* Write a configuration string to modem with timeout */ 
/* p_seek() mode constants */
#define P_FABS 1 /* Position absolute in the file */ 
#define P_FEND 2 /* Position relative from the end of file */ 
#define P_FCUR 3 /* Position relative to the current pos */ 
#define P_FRSENSE 4 /* Sense the record position */ 
#define P_FRSET 5 /* Set the record position */ 
#define P_FREWIND 6 /* Rewind a text file */ 


/* file errors */
#define ExistsErr    (-32)
#define NotExistsErr  (-33)
#define WriteErr    (-34)
#define ReadErr     (-35)
#define EofErr     (-36)
#define FullErr     (-37)
#define NameErr     (-38)
#define AccessErr    (-39)
#define LockedErr    (-40)
#define DeviceErr    (-41)
#define DirErr     (-42)
#define RecordErr    (-43)
#define ReadOnlyErr   (-44)
#define IoInvalidErr  (-45)
#define PendingErr   (-46)
#define VolumeErr    (-47)
#define CancelErr    (-48)
#define IoAllocErr   (-10)    /* E_GEN_NOMEMORY */ 
#define DisconnectErr  (-50)
#define ConnectErr   (-51)
#define ReTransmitErr  (-52)
#define LineErr     (-53)
#define InActivityErr  (-54)
#define ParityErr    (-55)
#define FrameErr    (-56)
#define OverrunErr   (-57)
#define ModemConnectErr (-58)
#define ModemBusyErr  (-59)
#define ModemNoAnswerErr (-60)
#define ModemBlacklistErr (-61)
#define NotReadyErr   (-62)
#define UnknownErr   (-63)
#define DirFullErr   (-64)
#define WriteProtectErr (-65)
#define CorruptMediaErr (-66)
#define AbortErr    (-67)
#define EraseErr    (-68)
#define InvalidFileErr (-69)
#define NO_ERROR 0
#define E_FILE_EXIST ExistsErr     /* File already exists */ 
#define E_FILE_NXIST NotExistsErr    /* File does not exist */ 
#define E_FILE_WRITE WriteErr      /* Write to file failed */ 
#define E_FILE_READ ReadErr       /* Read from file failed */ 
#define E_FILE_EOF EofErr        /* Read past end of file */ 
#define E_FILE_FULL FullErr       /* Disk/serial read buffer full */ 
#define E_FILE_NAME NameErr       /* Invalid file name */ 
#define E_FILE_ACCESS AccessErr     /* Access denied */ 
#define E_FILE_LOCKED LockedErr     /* Record or file locked */ 
#define E_FILE_DEVICE DeviceErr     /* Device does not exist */ 
#define E_FILE_DIR DirErr        /* Directory does not exist */ 
#define E_FILE_RECORD RecordErr     /* Record too large */ 
#define E_FILE_RDONLY ReadOnlyErr    /* File has read only access */ 
#define E_FILE_INV IoInvalidErr     /* Invalid I/O operation */ 
#define E_FILE_PENDING PendingErr    /* I/O pending (not yet completed) */ 
#define E_FILE_VOLUME VolumeErr     /* Invalid volume */ 
#define E_FILE_CANCEL CancelErr     /* Async operation was cancelled */ 
#define E_FILE_ALLOC IoAllocErr     /* No memory for control block */ 
#define E_FILE_DISC DisconnectErr    /* link is disconnected */ 
#define E_FILE_CONNECT ConnectErr    /* link already connected */ 
#define E_FILE_RETRAN ReTransmitErr   /* Retransmission threshold exceeded */ 
#define E_FILE_LINE LineErr       /* Physical link failure */ 
#define E_FILE_INACT InActivityErr   /* Inactivity timer expired */ 
#define E_FILE_PARITY ParityErr     /* Serial parity error */ 
#define E_FILE_FRAME FrameErr      /* Serial framing error */ 
#define E_FILE_OVERRUN OverrunErr    /* Serial overrun error */ 
#define E_MDM_CONFAIL ModemConnectErr  /* modem can't connect to remote modem */ 
#define E_MDM_BUSY ModemBusyErr     /* remote number busy */ 
#define E_MDM_NOANS ModemNoAnswerErr  /* there was no answer */ 
#define E_MDM_BLACKLIST ModemBlacklistErr /* number blacklisted by the modem*/ 
#define E_FILE_NOTREADY NotReadyErr   /* Drive not ready error */ 
#define E_FILE_UNKNOWN UnknownErr    /* Unknown media in drive */ 
#define E_FILE_DIRFULL DirFullErr    /* Root dir full error */ 
#define E_FILE_PROTECT WriteProtectErr /* Device write protect */ 
#define E_FILE_CORRUPT CorruptMediaErr /* Media is corrupt */ 
#define E_FILE_ABORT AbortErr /* User aborted operation error */ 
#define E_FILE_ERASE EraseErr /* Failed to Erase Flash pack */ 
#define E_FILE_INVALID InvalidFileErr /* Invalid file for DBF system */ 
/* defines for changing directories */
#define P_CD_ROOT 0   /* goto root directory */ 
#define P_CD_PARENT 1  /* goto parent directory */ 
#define P_CD_SUBDIR 2  /* goto subdirectory */ 
/* masks for status flag of P_INFO */
#define P_FAWRITE 0x01 /* can the file be written to? */ 
#define P_FAHIDDEN 0x02 /* set if file is hidden */ 
#define P_FASYSTEM 0x04 /* set if file is a system file */ 
#define P_FAVOLUME 0x08 /* set if the name is a volume name */ 
#define P_FADIR  0x10 /* set if file is a directory file */ 
#define P_FAMOD  0x20 /* has the file been modified? */ 
#define P_FAREAD  0x100 /* can the file be read? */ 
#define P_FAEXEC  0x200 /* is the file executable? */ 
#define P_FASTREAM 0x400 /* is the file a byte stream file? */ 
#define P_FATEXT  0x800 /* is it a text file? */ 
/* File system File information - p_finfo() */
typedef struct {
unsigned short int version; /* for future expansion */ 
unsigned short int status; /* status bits */ 
unsigned long int size; /* size of the file */ 
unsigned long int modst; /* system time of last modification */ 
unsigned char spare[4]; /* spare bytes for future expansion */ 
} P_INFO;
#define P_VOLUMENAME  32
#define P_FMEDIA_UNKNOWN 0
#define P_FMEDIA_FLOPPY 1
#define P_FMEDIA_HARDDISK 2
#define P_FMEDIA_FLASH 3
#define P_FMEDIA_RAM 4
#define P_FMEDIA_ROM 5
#define P_FMEDIA_WRITEPROTECTED 6
#define P_FMEDIA_COMPRESSIBLE 0x8000 /* Worth compressing deleted records */ 
#define P_FMEDIA_DYNAMIC 0x4000 /* Media size is dynamic */ 
#define P_FMEDIA_INTERNAL 0x2000 /* Media is internal */ 
#define P_FMEDIA_DUAL_DENSITY 0x1000
#define P_FMEDIA_FORMATTABLE 0x800
/* File System Device information - p_dinfo() */
typedef struct {
unsigned short int version; /* for future expansion */ 
unsigned short int mediatype; /* what type of device is this */ 
unsigned short int removable; /* is device removable or not */ 
unsigned long int size; /* size of the device */ 
unsigned long int free; /* amount of device still free */ 
char name[P_VOLUMENAME]; /* the volume name of the device */ 
short int batterystate; /* Device battery status */ 
unsigned char spare[16]; /* spare bytes for future expansion */ 
} P_DINFO;
#define P_FSYSTYPE_FLAT 0
#define P_FSYSTYPE_HIER 1
/* File System Node information - p_ninfo() */
typedef struct {
unsigned short int version; /* for future expansion */ 
unsigned short int type; /* file system type (flat/hierarchical...) */ 
unsigned short int formattable; /* TRUE if node supports format cmds else FALSE */ 
unsigned char spare[26]; /* spare bytes for future expansion */ 
} P_NINFO;
/* Flag defines for p_fparse */
#define P_PWILD_ANY 0x01 /* contains one or more wildcards */ 
#define P_PWILD_NAME 0x02 /* the name field contains wildcards */ 
#define P_PWILD_EXT 0x04 /* the extension contains wildcards */ 
/* Full file system parse - p_fparse() */
#define P_FSYSNAMESIZE 5
typedef struct {
unsigned char system; /* file system name length */ 
unsigned char device; /* device name length */ 
unsigned char path; /* path name length */ 
unsigned char name; /* name length */ 
unsigned char ext; /* extension length */ 
unsigned char flags; /* information on the presence of wildcards */ 
} P_FPARSE;
#define P_FBLKSHIFT 9 /* Block shift factor */ 
#define P_FBLKSIZE 0x200 /* Block size */ 
#define P_FMAXRSIZE 0x100 /* Maximum text record size */ 
#define P_FMAXSSIZE 0x4000 /* Maximum stream read/write length */ 
#define P_FSIZRPOS sizeof(long int) /* array size for storing r/w position */ 
#define P_MAXDEV 128 /* Maximum device name size */ 
#define P_MAXPATH 128 /* Maximum path size */ 
#define P_MAXNAME 128 /* Maximum name size */ 
#define P_MAXEXTN 128 /* Maximum extension size */ 
#define P_FNAMESIZE 128 /* Maximum file name size */ 
/* BINARY FILE SIGNATURE FOR APPLICATION FILES */
typedef struct
{
char app_id[3]; /* application id */ 
unsigned char chk_sum; /* application id checksum */ 
unsigned char file_vn; /* file version number */ 
unsigned char app_vn; /* application version number */ 
} P_FSIG;

/* LINK Protocol */

#define LNKMSG_NONCP 2 /* If NCP dies this msg sent */
#define LNKMSG_TERMINATE 3 /* Terminate everything */
#define LNKMSG_LOADREMOTE 4 /* Load a remote process */
#define LNKMSG_CONFIG 5 /* Re-configure serial channel */


#endif /* DEFS_H */

