/*****************************************************************************/
/*    WDMTMK API v4.08 for Microsoft Windows. ELCUS, 1998, 2011.             */
/*    Interface to driver TMK1553B.SYS v4.08                                 */
/*    for Windows 98/ME/2000/XP/Vista/7 (32/64 bit)                          */
/*****************************************************************************/

//#ifndef _TMK1553B_
//#define _TMK1553B_
#include <windows.h>
#include <winnt.h>
#include <windef.h>
#include <stdio.h>

#define TMK_DATA unsigned short

#ifndef _TMK1553B_MRT
#define _TMK1553B_MRT
#endif

#define TMK_VERSION_MIN 0x0406 /* v4.06 */
#define TMK_VERSION 0x0408     /* v4.08 */

#ifdef _TMK1553B_MRT
#define MAX_TMK_NUMBER (8+64-1)
#else
#define MAX_TMK_NUMBER (8-1)
#endif //def TMK1553B_MRT

#define MIN_TMK_TYPE 2
#define MAX_TMK_TYPE 12

#define TMK400 2
#define TMKMPC 3
#define RTMK400 4
#define TMKX 5
#define TMKXI 6
#define MRTX 7
#define MRTXI 8
#define TA 9
#define TAI 10
#define MRTA 11
#define MRTAI 12

#define ALL_TMKS 0x00FF

#define MBC_ALLOC_FAIL 0xFFFF

#define GET_TIMEOUT 0xFFFF

#define SWTIMER_OFF   0x0000
#define SWTIMER_ON    0x2400
#define SWTIMER_EVENT 0x8000
#define SWTIMER_RESET 0xFBFF

#define GET_SWTIMER_CTRL 0xFFFF

#define TIMER_RESET 0xFBFF
#define TIMER_OFF   0x0000
#define TIMER_16BIT 0x3400
#define TIMER_32BIT 0x2400
#define TIMER_1US   0x0000
#define TIMER_2US   0x0080
#define TIMER_4US   0x0100
#define TIMER_8US   0x0180
#define TIMER_16US  0x0200
#define TIMER_32US  0x0280
#define TIMER_64US  0x0300
#define TIMER_STOP  0x0380
#define TIMER_SYN   0x0040
#define TIMER_SYND  0x0020
#define TIMER_SA    0x001F

#define TIMER_NOSTOP 0x2000

#define TIMER_MASK  0x37FF
#define TIMER_STEP  0x0380
#define TIMER_BITS  0x3400

#define GET_TIMER_CTRL 0xFFFF

#define DATA_BC_RT 0x00
#define DATA_BC_RT_BRCST 0x08
#define DATA_RT_BC 0x01
#define DATA_RT_RT 0x02
#define DATA_RT_RT_BRCST 0x0A
#define CTRL_C_A 0x03
#define CTRL_C_BRCST 0x0B
#define CTRL_CD_A 0x04
#define CTRL_CD_BRCST 0x0C
#define CTRL_C_AD 0x05

#define CC_FMT_1 0x00
#define CC_FMT_2 0x01
#define CC_FMT_3 0x02
#define CC_FMT_4 0x03
#define CC_FMT_5 0x05
#define CC_FMT_6 0x04
#define CC_FMT_7 0x08
#define CC_FMT_8 0x0A
#define CC_FMT_9 0x0B
#define CC_FMT_10 0x0C

#define BUS_A 0
#define BUS_B 1
#define BUS_1 0
#define BUS_2 1

#define S_ERAO_MASK 0x01
#define S_MEO_MASK 0x02
#define S_IB_MASK 0x04
#define S_TO_MASK 0x08
#define S_EM_MASK 0x10
#define S_EBC_MASK 0x20
#define S_DI_MASK 0x40
#define S_ELN_MASK 0x80
#define S_G1_MASK 0x1000
#define S_G2_MASK 0x2000

#define NWORDS_MASK 0x001F
#define CMD_MASK 0x041F
#define SUBADDR_MASK 0x03E0
#define CI_MASK 0x03E0
#define HBIT_MASK 0x0200
#define RT_DIR_MASK 0x0400
#define ADDRESS_MASK 0xF800
#define RTFL_MASK 0x0001
#define DNBA_MASK 0x0002
#define SSFL_MASK 0x0004
#define BUSY_MASK 0x0008
#define BRCST_MASK 0x0010
#define NULL_MASK 0x00E0
#define SREQ_MASK 0x0100
#define ERROR_MASK 0x0400

#define SREQ 0x01
#define BUSY 0x02
#define SSFL 0x04
#define RTFL 0x08
#define DNBA 0x10

#define CWB0 0x20
#define CWB1 0x40

#define BC_MODE 0x00
#define RT_MODE 0x80
#define MT_MODE 0x100
#define MRT_MODE 0x280
#define UNDEFINED_MODE 0xFFFF

#define RT_TRANSMIT 0x0400
#define RT_RECEIVE 0x0000

#define RT_ERROR_MASK 0x4000

#define RT_FLAG 0x8000
#define RT_FLAG_MASK 0x8000

#define RT_HBIT_MODE 0x0001
#define RT_FLAG_MODE 0x0002
#define RT_BRCST_MODE 0x0004
#define RT_DATA_BL 0x2000
#define RT_GENER1_BL 0x0004
#define RT_GENER2_BL 0x4000
#define BC_GENER1_BL 0x0004
#define BC_GENER2_BL 0x4000
#define MT_GENER1_BL 0x0004
#define MT_GENER2_BL 0x4000
#define TMK_IRQ_OFF 0x8000

#define CX_CC_MASK 0x000F
#define CX_CONT_MASK 0x0010
#define CX_BUS_MASK 0x0020
#define CX_SIG_MASK 0x8000
#define CX_INT_MASK 0x0020

#define CX_CONT 0x0010
#define CX_STOP 0x0000
#define CX_BUS_0 0x0000
#define CX_BUS_A 0x0000
#define CX_BUS_1 0x0020
#define CX_BUS_B 0x0020
#define CX_NOSIG 0x0000
#define CX_SIG 0x8000
#define CX_INT 0x0000
#define CX_NOINT 0x0020

#define SX_NOERR 0
#define SX_MEO 1
#define SX_TOA 2
#define SX_TOD 3
#define SX_ELN 4
#define SX_ERAO 5
#define SX_ESYN 6
#define SX_EBC 7

#define SX_ERR_MASK 0x0007
#define SX_IB_MASK 0x0008
#define SX_G1_MASK 0x0010
#define SX_G2_MASK 0x0020
#define SX_K2_MASK 0x0100
#define SX_K1_MASK 0x0200
#define SX_SCC_MASK 0x3C00
#define SX_ME_MASK 0x4000
#define SX_BUS_MASK 0x8000

#define SX_BUS_0 0x0000
#define SX_BUS_A 0x0000
#define SX_BUS_1 0x8000
#define SX_BUS_B 0x8000

#define GET_IO_DELAY 0xFFFF

#define RT_ENABLE 0x0000
#define RT_DISABLE 0x001F
#define RT_GET_ENABLE 0xFFFF

#define CW(ADDR,DIR,SUBADDR,NWORDS) ((TMK_DATA)(((ADDR)<<11)|(DIR)|((SUBADDR)<<5)|((NWORDS)&0x1F)))
#define CWM(ADDR,COMMAND) ((TMK_DATA)(((ADDR)<<11)|(CI_MASK)|(COMMAND)))
#define CWMC(ADDR,CI,COMMAND) ((TMK_DATA)(((ADDR)<<11)|((CI)&0x03E0)|(COMMAND)))

/*#define CMD_ILLEGAL 0x000*/
#define CMD_DYNAMIC_BUS_CONTROL 0x400
#define CMD_SYNCHRONIZE 0x401
#define CMD_TRANSMIT_STATUS_WORD 0x402
#define CMD_INITIATE_SELF_TEST 0x403
#define CMD_TRANSMITTER_SHUTDOWN 0x404
#define CMD_OVERRIDE_TRANSMITTER_SHUTDOWN 0x405
#define CMD_INHIBIT_TERMINAL_FLAG_BIT 0x406
#define CMD_OVERRIDE_INHIBIT_TERMINAL_FLAG_BIT 0x407
#define CMD_RESET_REMOTE_TERMINAL 0x408
#define CMD_TRANSMIT_VECTOR_WORD 0x410
#define CMD_SYNCHRONIZE_WITH_DATA_WORD 0x011
#define CMD_TRANSMIT_LAST_COMMAND_WORD 0x412
#define CMD_TRANSMIT_BUILT_IN_TEST_WORD 0x413

#define TMK_ERROR_0      0xE0040000
#define TMK_BAD_TYPE     (1 + TMK_ERROR_0)
#define TMK_BAD_IRQ      (2 + TMK_ERROR_0)
#define TMK_BAD_NUMBER   (3 + TMK_ERROR_0)
#define BC_BAD_BUS       (4 + TMK_ERROR_0)
#define BC_BAD_BASE      (5 + TMK_ERROR_0)
#define BC_BAD_LEN       (6 + TMK_ERROR_0)
#define RT_BAD_PAGE      (7 + TMK_ERROR_0)
#define RT_BAD_LEN       (8 + TMK_ERROR_0)
#define RT_BAD_ADDRESS   (9 + TMK_ERROR_0)
#define RT_BAD_FUNC      (10 + TMK_ERROR_0)
#define BC_BAD_FUNC      (11 + TMK_ERROR_0)
#define TMK_BAD_FUNC     (12 + TMK_ERROR_0)
#define VTMK_BAD_VERSION (13 + TMK_ERROR_0)

#define VTMK_tmkconfig 2
#define VTMK_tmkdone 3
#define VTMK_tmkgetmaxn 4
#define VTMK_tmkselect 5
#define VTMK_tmkselected 6
#define VTMK_tmkgetmode 7
#define VTMK_tmksetcwbits 8
#define VTMK_tmkclrcwbits 9
#define VTMK_tmkgetcwbits 10
#define VTMK_tmkdefevent 11
#define VTMK_tmkgetevd 12

#define VTMK_bcreset 13
#define VTMK_bc_def_tldw 14
#define VTMK_bc_enable_di 15
#define VTMK_bc_disable_di 16
#define VTMK_bcdefirqmode 17
#define VTMK_bcgetirqmode 18
#define VTMK_bcgetmaxbase 19
#define VTMK_bcdefbase 20
#define VTMK_bcgetbase 21
#define VTMK_bcputw 22
#define VTMK_bcgetw 23
#define VTMK_bcgetansw 24
#define VTMK_bcputblk 25
#define VTMK_bcgetblk 26
#define VTMK_bcdefbus 27
#define VTMK_bcgetbus 28
#define VTMK_bcstart 29
#define VTMK_bcstartx 30
#define VTMK_bcdeflink 31
#define VTMK_bcgetlink 32
#define VTMK_bcstop 33
#define VTMK_bcgetstate 34

#define VTMK_rtreset 35
#define VTMK_rtdefirqmode 36
#define VTMK_rtgetirqmode 37
#define VTMK_rtdefmode 38
#define VTMK_rtgetmode 39
#define VTMK_rtgetmaxpage 40
#define VTMK_rtdefpage 41
#define VTMK_rtgetpage 42
#define VTMK_rtdefpagepc 43
#define VTMK_rtdefpagebus 44
#define VTMK_rtgetpagepc 45
#define VTMK_rtgetpagebus 46
#define VTMK_rtdefaddress 47
#define VTMK_rtgetaddress 48
#define VTMK_rtdefsubaddr 49
#define VTMK_rtgetsubaddr 50
#define VTMK_rtputw 51
#define VTMK_rtgetw 52
#define VTMK_rtputblk 53
#define VTMK_rtgetblk 54
#define VTMK_rtsetanswbits 55
#define VTMK_rtclranswbits 56
#define VTMK_rtgetanswbits 57
#define VTMK_rtgetflags 58
#define VTMK_rtputflags 59
#define VTMK_rtsetflag 60
#define VTMK_rtclrflag 61
#define VTMK_rtgetflag 62
#define VTMK_rtgetstate 63
#define VTMK_rtbusy 64
#define VTMK_rtlock 65
#define VTMK_rtunlock 66
#define VTMK_rtgetcmddata 67
#define VTMK_rtputcmddata 68

#define VTMK_mtreset 69
#define VTMK_mtdefirqmode 70
#define VTMK_mtgetirqmode 71
#define VTMK_mtgetmaxbase 72
#define VTMK_mtdefbase 73
#define VTMK_mtgetbase 74
#define VTMK_mtputw 75
#define VTMK_mtgetw 76
#define VTMK_mtgetsw 77
#define VTMK_mtputblk 78
#define VTMK_mtgetblk 79
#define VTMK_mtstartx 80
#define VTMK_mtdeflink 81
#define VTMK_mtgetlink 82
#define VTMK_mtstop 83
#define VTMK_mtgetstate 84

#define VTMK_tmkgetinfo 85
#define VTMK_GetVersion 86

#define VTMK_rtenable 87

#define VTMK_mrtgetmaxn 88
#define VTMK_mrtconfig 89
#define VTMK_mrtselected 90
#define VTMK_mrtgetstate 91
#define VTMK_mrtdefbrcsubaddr0 92
#define VTMK_mrtreset 93

#define VTMK_tmktimer 94
#define VTMK_tmkgettimer 95
#define VTMK_tmkgettimerl 96
#define VTMK_bcgetmsgtime 97
#define VTMK_mtgetmsgtime 98
#define VTMK_rtgetmsgtime 99

#define VTMK_tmkgethwver 100

#define VTMK_tmkgetevtime 101
#define VTMK_tmkswtimer 102
#define VTMK_tmkgetswtimer 103

#define VTMK_tmktimeout 104

#define VTMK_mrtdefbrcpage 105
#define VTMK_mrtgetbrcpage 106

#define VTMK_mbcinit 107
#define VTMK_mbcpreparex 108
#define VTMK_mbcstartx 109
#define VTMK_mbcalloc 110
#define VTMK_mbcfree 111

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)


#define METHOD_BUFFERED                 0
#define METHOD_IN_DIRECT                1
#define METHOD_OUT_DIRECT               2
#define METHOD_NEITHER                  3
#define FILE_ANY_ACCESS                 0
#define FILE_READ_ACCESS          ( 0x0001 )    // file & pipe
#define FILE_WRITE_ACCESS         ( 0x0002 )    // file & pipe
#define TMK_KRNLDRVR 0x8000
#define IOCTL_TMK_tmkconfig CTL_CODE(TMK_KRNLDRVR, VTMK_tmkconfig+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkdone CTL_CODE(TMK_KRNLDRVR, VTMK_tmkdone+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkgetmaxn CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgetmaxn+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkselect CTL_CODE(TMK_KRNLDRVR, VTMK_tmkselect+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkselected CTL_CODE(TMK_KRNLDRVR, VTMK_tmkselected+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkgetmode CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgetmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmksetcwbits CTL_CODE(TMK_KRNLDRVR, VTMK_tmksetcwbits+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkclrcwbits CTL_CODE(TMK_KRNLDRVR, VTMK_tmkclrcwbits+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkgetcwbits CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgetcwbits+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkdefevent CTL_CODE(TMK_KRNLDRVR, VTMK_tmkdefevent+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkgetevd CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgetevd+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcreset CTL_CODE(TMK_KRNLDRVR, VTMK_bcreset+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bc_def_tldw CTL_CODE(TMK_KRNLDRVR, VTMK_bc_def_tldw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bc_enable_di CTL_CODE(TMK_KRNLDRVR, VTMK_bc_enable_di+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bc_disable_di CTL_CODE(TMK_KRNLDRVR, VTMK_bc_disable_di+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcdefirqmode CTL_CODE(TMK_KRNLDRVR, VTMK_bcdefirqmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetirqmode CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetirqmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetmaxbase CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetmaxbase+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcdefbase CTL_CODE(TMK_KRNLDRVR, VTMK_bcdefbase+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetbase CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetbase+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcputw CTL_CODE(TMK_KRNLDRVR, VTMK_bcputw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetw CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetansw CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetansw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcputblk CTL_CODE(TMK_KRNLDRVR, VTMK_bcputblk+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetblk CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetblk+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcdefbus CTL_CODE(TMK_KRNLDRVR, VTMK_bcdefbus+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetbus CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetbus+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcstart CTL_CODE(TMK_KRNLDRVR, VTMK_bcstart+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcstartx CTL_CODE(TMK_KRNLDRVR, VTMK_bcstartx+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcdeflink CTL_CODE(TMK_KRNLDRVR, VTMK_bcdeflink+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetlink CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetlink+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcstop CTL_CODE(TMK_KRNLDRVR, VTMK_bcstop+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetstate CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetstate+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_rtreset CTL_CODE(TMK_KRNLDRVR, VTMK_rtreset+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtdefirqmode CTL_CODE(TMK_KRNLDRVR, VTMK_rtdefirqmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetirqmode CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetirqmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtdefmode CTL_CODE(TMK_KRNLDRVR, VTMK_rtdefmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetmode CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetmaxpage CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetmaxpage+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtdefpage CTL_CODE(TMK_KRNLDRVR, VTMK_rtdefpage+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetpage CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetpage+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtdefpagepc CTL_CODE(TMK_KRNLDRVR, VTMK_rtdefpagepc+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtdefpagebus CTL_CODE(TMK_KRNLDRVR, VTMK_rtdefpagebus+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetpagepc CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetpagepc+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetpagebus CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetpagebus+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtdefaddress CTL_CODE(TMK_KRNLDRVR, VTMK_rtdefaddress+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetaddress CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetaddress+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtdefsubaddr CTL_CODE(TMK_KRNLDRVR, VTMK_rtdefsubaddr+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetsubaddr CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetsubaddr+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtputw CTL_CODE(TMK_KRNLDRVR, VTMK_rtputw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetw CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtputblk CTL_CODE(TMK_KRNLDRVR, VTMK_rtputblk+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetblk CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetblk+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtsetanswbits CTL_CODE(TMK_KRNLDRVR, VTMK_rtsetanswbits+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtclranswbits CTL_CODE(TMK_KRNLDRVR, VTMK_rtclranswbits+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetanswbits CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetanswbits+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetflags CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetflags+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtputflags CTL_CODE(TMK_KRNLDRVR, VTMK_rtputflags+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtsetflag CTL_CODE(TMK_KRNLDRVR, VTMK_rtsetflag+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtclrflag CTL_CODE(TMK_KRNLDRVR, VTMK_rtclrflag+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetflag CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetflag+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetstate CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetstate+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtbusy CTL_CODE(TMK_KRNLDRVR, VTMK_rtbusy+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtlock CTL_CODE(TMK_KRNLDRVR, VTMK_rtlock+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtunlock CTL_CODE(TMK_KRNLDRVR, VTMK_rtunlock+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetcmddata CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetcmddata+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtputcmddata CTL_CODE(TMK_KRNLDRVR, VTMK_rtputcmddata+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_mtreset CTL_CODE(TMK_KRNLDRVR, VTMK_mtreset+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtdefirqmode CTL_CODE(TMK_KRNLDRVR, VTMK_mtdefirqmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetirqmode CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetirqmode+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetmaxbase CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetmaxbase+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtdefbase CTL_CODE(TMK_KRNLDRVR, VTMK_mtdefbase+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetbase CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetbase+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtputw CTL_CODE(TMK_KRNLDRVR, VTMK_mtputw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetw CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetsw CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetsw+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtputblk CTL_CODE(TMK_KRNLDRVR, VTMK_mtputblk+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetblk CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetblk+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtstartx CTL_CODE(TMK_KRNLDRVR, VTMK_mtstartx+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtdeflink CTL_CODE(TMK_KRNLDRVR, VTMK_mtdeflink+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetlink CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetlink+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtstop CTL_CODE(TMK_KRNLDRVR, VTMK_mtstop+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetstate CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetstate+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_tmkgetinfo CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgetinfo+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_GetVersion CTL_CODE(TMK_KRNLDRVR, VTMK_GetVersion+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_rtenable CTL_CODE(TMK_KRNLDRVR, VTMK_rtenable+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_mrtgetmaxn CTL_CODE(TMK_KRNLDRVR, VTMK_mrtgetmaxn+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mrtconfig CTL_CODE(TMK_KRNLDRVR, VTMK_mrtconfig+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mrtselected CTL_CODE(TMK_KRNLDRVR, VTMK_mrtselected+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mrtgetstate CTL_CODE(TMK_KRNLDRVR, VTMK_mrtgetstate+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mrtdefbrcsubaddr0 CTL_CODE(TMK_KRNLDRVR, VTMK_mrtdefbrcsubaddr0+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mrtreset CTL_CODE(TMK_KRNLDRVR, VTMK_mrtreset+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_tmktimer CTL_CODE(TMK_KRNLDRVR, VTMK_tmktimer+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkgettimer CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgettimer+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkgettimerl CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgettimerl+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_bcgetmsgtime CTL_CODE(TMK_KRNLDRVR, VTMK_bcgetmsgtime+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mtgetmsgtime CTL_CODE(TMK_KRNLDRVR, VTMK_mtgetmsgtime+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_rtgetmsgtime CTL_CODE(TMK_KRNLDRVR, VTMK_rtgetmsgtime+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_tmkgethwver CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgethwver+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_tmkgetevtime CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgetevtime+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkswtimer CTL_CODE(TMK_KRNLDRVR, VTMK_tmkswtimer+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_tmkgetswtimer CTL_CODE(TMK_KRNLDRVR, VTMK_tmkgetswtimer+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_tmktimeout CTL_CODE(TMK_KRNLDRVR, VTMK_tmktimeout+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_mrtdefbrcpage CTL_CODE(TMK_KRNLDRVR, VTMK_mrtdefbrcpage+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mrtgetbrcpage CTL_CODE(TMK_KRNLDRVR, VTMK_mrtgetbrcpage+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

#define IOCTL_TMK_mbcinit CTL_CODE(TMK_KRNLDRVR, VTMK_mbcinit+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mbcpreparex CTL_CODE(TMK_KRNLDRVR, VTMK_mbcpreparex+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mbcstartx CTL_CODE(TMK_KRNLDRVR, VTMK_mbcstartx+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mbcalloc CTL_CODE(TMK_KRNLDRVR, VTMK_mbcalloc+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TMK_mbcfree CTL_CODE(TMK_KRNLDRVR, VTMK_mbcfree+0x800, METHOD_NEITHER, FILE_ANY_ACCESS)

typedef struct
{
  short nType;
  char szName[10];
  unsigned short wPorts1;
  unsigned short wPorts2;
  unsigned short wIrq1;
  unsigned short wIrq2;
  unsigned short wIODelay;
} TTmkConfigData;

typedef struct
{
  unsigned short wResult;
  unsigned short wAW1;
  unsigned short wAW2;
} TBc;
typedef struct
{
  unsigned short wBase;
  unsigned short wResultX;
} TBcx;
typedef struct
{
  unsigned short wStatus;
  unsigned short wCmd;
} TRt;
typedef struct
{
  unsigned short wBase;
  unsigned short wResultX;
} TMt;
typedef struct
{
  unsigned short wStatus;
} TMrt;
typedef struct
{
  unsigned short wRequest;
//  DWORD dwTimer;
} TTmk;


typedef union
  {
    TBc bc;
    TBcx bcx;
    TRt rt;
    TMt mt;
    TMrt mrt;
    TTmk tmk;
  } TSub;
typedef struct
{
  int nInt;
  unsigned short wMode;
  TSub sub;
} TTmkEventData;

DWORD TmkOpen();
void TmkClose();
void tmkgetinfo(TTmkConfigData *pConfD);
void tmkgetevd(TTmkEventData *pEvD);
void tmkdefevent(HANDLE hEvent, BOOL fEventSet);
int tmkgetmaxn();
int tmkconfig(int tmkNumber);
int tmkdone(int tmkNumber);
int tmkselect(int tmkNumber);
int tmkselected();
TMK_DATA tmkgetmode();
void tmksetcwbits(TMK_DATA tmkSetControl);
void tmkclrcwbits(TMK_DATA tmkClrControl);
TMK_DATA tmkgetcwbits();
int bcreset();
void bc_def_tldw(TMK_DATA wTLDW);
void bc_enable_di();
void bc_disable_di();
int bcdefirqmode(TMK_DATA bcIrqMode);
TMK_DATA bcgetirqmode();
TMK_DATA bcgetmaxbase();
int bcdefbase(TMK_DATA bcBasePC);
TMK_DATA bcgetbase();
void bcputw(TMK_DATA bcAddr, TMK_DATA bcData);
TMK_DATA bcgetw(TMK_DATA bcAddr);
DWORD bcgetansw(TMK_DATA bcCtrlCode);
void bcputblk(TMK_DATA bcAddr, void *pcBuffer, TMK_DATA cwLength);
void bcgetblk(TMK_DATA bcAddr, void *pcBuffer, TMK_DATA cwLength);
int bcdefbus(TMK_DATA bcBus);
TMK_DATA bcgetbus();
int bcstart(TMK_DATA bcBase, TMK_DATA bcCtrlCode);
int bcstartx(TMK_DATA bcBase, TMK_DATA bcCtrlCode);
int bcdeflink(TMK_DATA bcBase, TMK_DATA bcCtrlCode);
DWORD bcgetlink();
TMK_DATA bcstop();
DWORD bcgetstate();
int rtreset();
int rtdefirqmode(TMK_DATA rtIrqMode);
TMK_DATA rtgetirqmode();
int rtdefmode(TMK_DATA rtMode);
TMK_DATA rtgetmode();
TMK_DATA rtgetmaxpage();
int rtdefpage(TMK_DATA rtPage);
TMK_DATA rtgetpage();
int rtdefpagepc(TMK_DATA rtPagePC);
int rtdefpagebus(TMK_DATA rtPageBus);
TMK_DATA rtgetpagepc();
TMK_DATA rtgetpagebus();
int rtdefaddress(TMK_DATA rtAddress);
TMK_DATA rtgetaddress();
void rtdefsubaddr(TMK_DATA rtDir, TMK_DATA rtSubAddr);
TMK_DATA rtgetsubaddr();
void rtputw(TMK_DATA rtAddr, TMK_DATA rtData);
TMK_DATA rtgetw(TMK_DATA rtAddr);
void rtputblk(TMK_DATA rtAddr, void *pcBuffer, TMK_DATA cwLength);
void rtgetblk(TMK_DATA rtAddr, void *pcBuffer, TMK_DATA cwLength);
void rtsetanswbits(TMK_DATA rtSetControl);
void rtclranswbits(TMK_DATA rtClrControl);
TMK_DATA rtgetanswbits();
void rtgetflags(void *pcBuffer, TMK_DATA rtDir, TMK_DATA rtFlagMin, TMK_DATA rtFlagMax);
void rtputflags(void *pcBuffer, TMK_DATA rtDir, TMK_DATA rtFlagMin, TMK_DATA rtFlagMax);
void rtsetflag();
void rtclrflag();
TMK_DATA rtgetflag(TMK_DATA rtDir, TMK_DATA rtSubAddr);
TMK_DATA rtgetstate();
TMK_DATA rtbusy();
void rtlock(TMK_DATA rtDir, TMK_DATA rtSubAddr);
void rtunlock();
TMK_DATA rtgetcmddata(TMK_DATA rtBusCommand);
void rtputcmddata(TMK_DATA rtBusCommand, TMK_DATA rtData);
int mtreset();
TMK_DATA mtgetsw();
#define mtdefirqmode bcdefirqmode
#define mtgetirqmode bcgetirqmode
#define mtgetmaxbase bcgetmaxbase
#define mtdefbase bcdefbase
#define mtgetbase bcgetbase
#define mtputw bcputw
#define mtgetw bcgetw
#define mtputblk bcputblk
#define mtgetblk bcgetblk
#define mtstartx bcstartx
#define mtdeflink bcdeflink
#define mtgetlink bcgetlink
#define mtstop bcstop
#define mtgetstate bcgetstate

TMK_DATA rtenable(TMK_DATA rtEnable);

int mrtgetmaxn();
DWORD mrtconfig(int tmkNumber);
int mrtselected();
TMK_DATA mrtgetstate();
void mrtdefbrcsubaddr0();
int mrtreset();

TMK_DATA tmktimer(TMK_DATA tmkTimerCtrl);
DWORD tmkgettimer();
TMK_DATA tmkgettimerl();
DWORD bcgetmsgtime();
#define mtgetmsgtime bcgetmsgtime
DWORD rtgetmsgtime();
TMK_DATA tmkgethwver();

DWORD tmkgetevtime();
TMK_DATA tmkswtimer(TMK_DATA tmkTimerCtrl);
DWORD tmkgetswtimer();

TMK_DATA tmktimeout(TMK_DATA tmkTimeOut);

int mrtdefbrcpage(TMK_DATA mrtBrcPage);
TMK_DATA mrtgetbrcpage();

int mbcinit(TMK_DATA mbcId);
int mbcpreparex(TMK_DATA mbcId, TMK_DATA bcBase, TMK_DATA bcCtrlCode, TMK_DATA mbcDelay);
int mbcstartx(TMK_DATA mbcId);
TMK_DATA mbcalloc();
int mbcfree(TMK_DATA mbcId);

//#endif
