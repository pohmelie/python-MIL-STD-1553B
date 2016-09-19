# 1 "ltmk.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "ltmk.h"
# 251 "ltmk.h"
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
  int nInt;
  unsigned short wMode;
  union
  {
    struct
    {
      unsigned short wResult;
      unsigned short wAW1;
      unsigned short wAW2;
    } bc;
    struct
    {
      unsigned short wBase;
      unsigned short wResultX;
    } bcx;
    struct
    {
      unsigned short wStatus;
      unsigned short wCmd;
    } rt;
    struct
    {
      unsigned short wBase;
      unsigned short wResultX;
    } mt;
    struct
    {
      unsigned short wStatus;
    } mrt;
    struct
    {
      unsigned short wRequest;
    } tmk;
  };
} TTmkEventData;
# 560 "ltmk.h"
int TmkOpen(void);
void TmkClose(void);

int tmkgetmaxn(void);
int tmkconfig(int tmkNumber);
int tmkdone(int tmkNumber);
int tmkselect(int tmkNumber);
int tmkselected(void);
unsigned short tmkgetmode(void);
void tmksetcwbits(unsigned short tmkSetControl);
void tmkclrcwbits(unsigned short tmkClrControl);
unsigned short tmkgetcwbits(void);
void tmkgetevd(TTmkEventData *pEvD);
int tmkwaitevents(int maskEvents, int fWait);







int bcreset(void);



int bcdefirqmode(unsigned short bcIrqMode);
unsigned short bcgetirqmode(void);
unsigned short bcgetmaxbase(void);
int bcdefbase(unsigned short bcBasePC);
unsigned short bcgetbase(void);
void bcputw(unsigned short bcAddr, unsigned short bcData);
unsigned short bcgetw(unsigned short bcAddr);
unsigned int bcgetansw(unsigned short bcCtrlCode);
void bcputblk(unsigned short bcAddr, void *pcBuffer, unsigned short cwLength);
void bcgetblk(unsigned short bcAddr, void *pcBuffer, unsigned short cwLength);
int bcdefbus(unsigned short bcBus);
unsigned short bcgetbus(void);
int bcstart(unsigned short bcBase, unsigned short bcCtrlCode);
int bcstartx(unsigned short bcBase, unsigned short bcCtrlCode);
int bcdeflink(unsigned short bcBase, unsigned short bcCtrlCode);
unsigned int bcgetlink(void);
unsigned short bcstop(void);
unsigned int bcgetstate(void);






int rtreset(void);
int rtdefirqmode(unsigned short rtIrqMode);
unsigned short rtgetirqmode(void);
int rtdefmode(unsigned short rtMode);
unsigned short rtgetmode(void);
unsigned short rtgetmaxpage(void);
int rtdefpage(unsigned short rtPage);
unsigned short rtgetpage(void);
int rtdefpagepc(unsigned short rtPagePC);
int rtdefpagebus(unsigned short rtPageBus);
unsigned short rtgetpagepc(void);
unsigned short rtgetpagebus(void);
int rtdefaddress(unsigned short rtAddress);
unsigned short rtgetaddress(void);
void rtdefsubaddr(unsigned short rtDir, unsigned short rtSubAddr);
unsigned short rtgetsubaddr(void);
void rtputw(unsigned short rtAddr, unsigned short rtData);
unsigned short rtgetw(unsigned short rtAddr);
void rtputblk(unsigned short rtAddr, void *pcBuffer, unsigned short cwLength);
void rtgetblk(unsigned short rtAddr, void *pcBuffer, unsigned short cwLength);
void rtsetanswbits(unsigned short rtSetControl);
void rtclranswbits(unsigned short rtClrControl);
unsigned short rtgetanswbits(void);
void rtgetflags(void *pcBuffer, unsigned short rtDir, unsigned short rtFlagMin, unsigned short rtFlagMax);
void rtputflags(void *pcBuffer, unsigned short rtDir, unsigned short rtFlagMin, unsigned short rtFlagMax);
void rtsetflag(void);
void rtclrflag(void);
unsigned short rtgetflag(unsigned short rtDir, unsigned short rtSubAddr);
unsigned short rtgetstate(void);
unsigned short rtbusy(void);
void rtlock(unsigned short rtDir, unsigned short rtSubAddr);
void rtunlock(void);
unsigned short rtgetcmddata(unsigned short rtBusCommand);
void rtputcmddata(unsigned short rtBusCommand, unsigned short rtData);





int mtreset(void);







unsigned short mtgetsw(void);







unsigned short rtenable(unsigned short rtEnable);

int mrtgetmaxn(void);
unsigned int mrtconfig(int tmkNumber);
int mrtselected(void);
unsigned short mrtgetstate(void);
void mrtdefbrcsubaddr0(void);
int mrtreset(void);


unsigned short tmktimer(unsigned short tmkTimerCtrl);
unsigned int tmkgettimer(void);
unsigned short tmkgettimerl(void);
unsigned int bcgetmsgtime(void);

unsigned int rtgetmsgtime(void);

unsigned short tmkgethwver(void);

unsigned int tmkgetevtime(void);
unsigned short tmkswtimer(unsigned short tmkSwTimerCtrl);
unsigned int tmkgetswtimer(void);

unsigned short tmktimeout(unsigned short tmkTimeOut);


int mrtdefbrcpage(unsigned short rtPage);
unsigned short mrtgetbrcpage(void);
