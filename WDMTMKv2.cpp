/*****************************************************************************/
/*    WDMTMK API v4.08 for Microsoft Windows. ELCUS, 1998, 2011.             */
/*    Interface to driver TMK1553B.SYS v4.08                                 */
/*    for Windows 98/ME/2000/XP/Vista/7 (32/64 bit)                          */
/*****************************************************************************/

//#ifndef _TMK1553B_
//#define _TMK1553B_

#include "wdmtmkv2.h"

#pragma warning (disable: 4244)
#pragma warning (disable: 4700)
#pragma warning (disable: 4715)
#pragma warning (disable: 4996)

int tmkError;
HANDLE _ahVTMK4Event[MAX_TMK_NUMBER+1];
HANDLE _hVTMK4VxD[MAX_TMK_NUMBER+1];
int _VTMK4tmkMaxNum = 0;
int _VTMK4mrtMaxNum = 0;
int _VTMK4tmkCurNum = 0;

DWORD TmkOpen()
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  int iTMK;
  int nTMK = -1;
  int nMRT = -1;
  char tmkName[32];
  char cc = 0x5c;
  int badver = 0;

  for (iTMK = 0; iTMK <= MAX_TMK_NUMBER; ++iTMK)
  {
    sprintf (tmkName,"%c%c.%cTMK1553BDevice%d",cc,cc,cc,iTMK);
    _hVTMK4VxD[iTMK] = CreateFileA(tmkName,
                  GENERIC_READ | GENERIC_WRITE,
                  0,
                  NULL,
                  OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL,
                  NULL
                  );
    if (_hVTMK4VxD[iTMK] != INVALID_HANDLE_VALUE)
    {
      if (!DeviceIoControl(_hVTMK4VxD[iTMK], (DWORD)IOCTL_TMK_GetVersion, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL) ||
              _awVTMK4OutBuf[0] < TMK_VERSION_MIN)
      {
        badver = 1;
      }
      nTMK = iTMK;
      if (iTMK < 8)
        nMRT = iTMK;
      CloseHandle(_hVTMK4VxD[iTMK]);
    }
    _ahVTMK4Event[iTMK] = 0;
    _hVTMK4VxD[iTMK] = 0;
  }

  if (badver)
    return VTMK_BAD_VERSION;
  if (nTMK == -1)
    return 1;

  _VTMK4tmkMaxNum = nTMK;
  _VTMK4mrtMaxNum = nMRT;

  return 0;
}

void TmkClose()
{
  int iTMK;
  for (iTMK = 0; iTMK <= _VTMK4tmkMaxNum; ++iTMK)
  {
    if (_hVTMK4VxD[iTMK])
      CloseHandle(_hVTMK4VxD[iTMK]);
    _ahVTMK4Event[iTMK] = 0;
    _hVTMK4VxD[iTMK] = 0;
  }
}

int tmkgetmaxn()
{
  return _VTMK4tmkMaxNum;
}

int tmkconfig(int tmkNumber)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  char tmkName[32];

  if (tmkNumber < 0 || tmkNumber > _VTMK4tmkMaxNum)
    return TMK_BAD_NUMBER;
  if (_hVTMK4VxD[tmkNumber] != 0)
     return TMK_BAD_NUMBER;

  sprintf (tmkName,"%c%c.%cTMK1553BDevice%d",0x5c,0x5c,0x5c,tmkNumber);
  _hVTMK4VxD[tmkNumber] = CreateFileA(tmkName,
                                     GENERIC_READ | GENERIC_WRITE,
                                     0,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL
                                     );
  if (_hVTMK4VxD[tmkNumber] == INVALID_HANDLE_VALUE)
  {
    _hVTMK4VxD[tmkNumber] = 0;
    return TMK_BAD_NUMBER;
  }

  else
  {
    _awVTMK4InBuf[0] = (WORD)tmkNumber;
    DeviceIoControl(_hVTMK4VxD[tmkNumber], (DWORD)IOCTL_TMK_tmkconfig, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
    if (_awVTMK4OutBuf[0] != 0)
    {
      CloseHandle (_hVTMK4VxD[tmkNumber]);
      _hVTMK4VxD[tmkNumber] = 0;
    }
    _VTMK4tmkCurNum = tmkNumber;
    return (int)_awVTMK4OutBuf[0];
  }
}

int tmkdone(int tmkNumber)
{
/*
WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
DWORD _cbVTMK4Ret;
_awVTMK4InBuf[0] = (WORD)tmkNumber;
return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkdone, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL))?0:GetLastError();
*/

  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  int iTMK;

  if (tmkNumber == ALL_TMKS)
  {
    for (iTMK = 0; iTMK <= _VTMK4tmkMaxNum; ++iTMK)
    {
      if (_hVTMK4VxD[iTMK] == 0)
        continue;
      _awVTMK4InBuf[0] = (WORD)iTMK;
      DeviceIoControl(_hVTMK4VxD[iTMK], (DWORD)IOCTL_TMK_tmkdone, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);

      _ahVTMK4Event[iTMK] = 0;
      CloseHandle(_hVTMK4VxD[iTMK]);
      _hVTMK4VxD[iTMK] = 0;
    }
  }
  else if (tmkNumber >= 0 && tmkNumber <= _VTMK4tmkMaxNum && _hVTMK4VxD[tmkNumber] != 0)
  {
    _awVTMK4InBuf[0] = (WORD)tmkNumber;
    DeviceIoControl(_hVTMK4VxD[tmkNumber], (DWORD)IOCTL_TMK_tmkdone, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);

    _ahVTMK4Event[tmkNumber] = 0;
    CloseHandle(_hVTMK4VxD[tmkNumber]);
    _hVTMK4VxD[tmkNumber] = 0;
  }
  return 0;
}

int tmkselect(int tmkNumber)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;

  if (tmkNumber < 0 || tmkNumber > _VTMK4tmkMaxNum)
    return TMK_BAD_NUMBER;
  if ((_hVTMK4VxD[tmkNumber] != INVALID_HANDLE_VALUE) && (_hVTMK4VxD[tmkNumber] != 0))
  {
    _VTMK4tmkCurNum = tmkNumber;

     //**************добавлено для поддержки двухканальных плат**********************************************************
    _awVTMK4InBuf[0] = _VTMK4tmkCurNum;
    DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkselect, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
    return _awVTMK4OutBuf[0];
    //*******************************************************************************************************************
    //return 0;
  }
  else
    return TMK_BAD_NUMBER;
}

int tmkselected()
{
  return _VTMK4tmkCurNum;
}
TMK_DATA tmkgetmode()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetmode, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void tmksetcwbits(TMK_DATA tmkSetControl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkSetControl;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmksetcwbits, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
void tmkclrcwbits(TMK_DATA tmkClrControl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkClrControl;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkclrcwbits, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
TMK_DATA tmkgetcwbits()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetcwbits, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void tmkdefevent(HANDLE hEvent, BOOL fEventSet)
{
#ifdef _WIN64
  WORD _awVTMK4InBuf[8], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _ahVTMK4Event[_VTMK4tmkCurNum] = hEvent;
  _awVTMK4InBuf[0] = 0; //LOWORD(hVxDEvent);
  _awVTMK4InBuf[1] = 0; //HIWORD(hVxDEvent);
  _awVTMK4InBuf[2] = LOWORD(fEventSet);
  _awVTMK4InBuf[3] = HIWORD(fEventSet);
  *((HANDLE*)(_awVTMK4InBuf+4)) = hEvent;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkdefevent, _awVTMK4InBuf, 16, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#else
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DWORD hVxDEvent;
/*
  int iTMK;
  if (hEvent != 0)
  {
    for (iTMK = 0; iTMK <= MAX_TMK_NUMBER; ++iTMK)
    {
      if (hEvent == _ahVTMK4Event[iTMK])
        break;
    }
    if (iTMK > MAX_TMK_NUMBER)
    {
      hVxDEvent = (DWORD)hEvent;
      _ahVTMK4Event[_VTMK4tmkCurNum] = hEvent;
    }
  }
  else
  {
    hVxDEvent = 0;
    _ahVTMK4Event[_VTMK4tmkCurNum] = 0;
  }
*/
  hVxDEvent = (DWORD)hEvent;
  _ahVTMK4Event[_VTMK4tmkCurNum] = hEvent;
  _awVTMK4InBuf[0] = LOWORD(hVxDEvent);
  _awVTMK4InBuf[1] = HIWORD(hVxDEvent);
  _awVTMK4InBuf[2] = LOWORD(fEventSet);
  _awVTMK4InBuf[3] = HIWORD(fEventSet);
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkdefevent, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#endif
}
void tmkgetevd(TTmkEventData *pEvD)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[6];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetevd, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 12, &_cbVTMK4Ret, NULL);
  pEvD->nInt = ((DWORD*)(_awVTMK4OutBuf))[0];
  switch (pEvD->wMode = _awVTMK4OutBuf[2])
  {
  case BC_MODE:
    switch (pEvD->nInt)
    {
    case 1:
      pEvD->sub.bc.wResult = _awVTMK4OutBuf[3];
      break;
    case 2:
      pEvD->sub.bc.wResult = _awVTMK4OutBuf[3];
      pEvD->sub.bc.wAW1 = _awVTMK4OutBuf[4];
      pEvD->sub.bc.wAW2 = _awVTMK4OutBuf[5];
      break;
    case 3:
      pEvD->sub.bcx.wResultX = _awVTMK4OutBuf[3];
      pEvD->sub.bcx.wBase = _awVTMK4OutBuf[4];
      break;
    case 4:
      pEvD->sub.bcx.wBase = _awVTMK4OutBuf[3];
      break;
    }
    break;
  case MT_MODE:
    switch (pEvD->nInt)
    {
    case 3:
      pEvD->sub.mt.wResultX = _awVTMK4OutBuf[3];
      pEvD->sub.mt.wBase = _awVTMK4OutBuf[4];
      break;
    case 4:
      pEvD->sub.mt.wBase = _awVTMK4OutBuf[3];
      break;
    }
    break;
  case RT_MODE:
    switch (pEvD->nInt)
    {
    case 1:
      pEvD->sub.rt.wCmd = _awVTMK4OutBuf[3];
      break;
    case 2:
    case 3:
      pEvD->sub.rt.wStatus = _awVTMK4OutBuf[3];
      break;
    }
    break;
  case UNDEFINED_MODE:
    switch (pEvD->nInt)
    {
    case 5:
      pEvD->sub.tmk.wRequest = _awVTMK4OutBuf[3];
//      pEvD->tmk.dwTimer = *((DWORD*)(&_awVTMK4OutBuf[4]));
      break;
    }
    break;
  }
}
void tmkgetinfo(TTmkConfigData *pConfD)
{
#ifdef _WIN64
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
//  _awVTMK4InBuf[0] = LOWORD(pConfD);
//  _awVTMK4InBuf[1] = HIWORD(pConfD);
  *((TTmkConfigData**)(_awVTMK4InBuf)) = pConfD;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetinfo, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#else
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = LOWORD(pConfD);
  _awVTMK4InBuf[1] = HIWORD(pConfD);
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetinfo, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#endif
}
int bcreset()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcreset, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
void bc_def_tldw(TMK_DATA wTLDW)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = wTLDW;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bc_def_tldw, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
void bc_enable_di()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bc_enable_di, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
void bc_disable_di()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bc_disable_di, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
int bcdefirqmode(TMK_DATA bcIrqMode)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcIrqMode;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcdefirqmode, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA bcgetirqmode()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetirqmode, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
TMK_DATA bcgetmaxbase()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetmaxbase, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int bcdefbase(TMK_DATA bcBasePC)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBasePC;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcdefbase, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA bcgetbase()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetbase, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void bcputw(TMK_DATA bcAddr, TMK_DATA bcData)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  _awVTMK4InBuf[1] = bcData;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcputw, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
TMK_DATA bcgetw(TMK_DATA bcAddr)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetw, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD bcgetansw(TMK_DATA bcCtrlCode)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcCtrlCode;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetansw, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
void bcputblk(TMK_DATA bcAddr, void *pcBuffer, TMK_DATA cwLength)
{
#ifdef _WIN64
  WORD _awVTMK4InBuf[8], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  _awVTMK4InBuf[1] = 0; //(WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = 0; //(WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  *((PUSHORT*)(_awVTMK4InBuf+4)) = (PUSHORT)pcBuffer;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcputblk, _awVTMK4InBuf, 16, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#else
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  _awVTMK4InBuf[1] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcputblk, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#endif
}
void bcgetblk(TMK_DATA bcAddr, void *pcBuffer, TMK_DATA cwLength)
{
#ifdef _WIN64
  WORD _awVTMK4InBuf[8], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  _awVTMK4InBuf[1] = 0; //(WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = 0; //(WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  *((PUSHORT*)(_awVTMK4InBuf+4)) = (PUSHORT)pcBuffer;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetblk, _awVTMK4InBuf, 16, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#else
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcAddr;
  _awVTMK4InBuf[1] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetblk, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#endif
}
int bcdefbus(TMK_DATA bcBus)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBus;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcdefbus, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA bcgetbus()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetbus, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int bcstart(TMK_DATA bcBase, TMK_DATA bcCtrlCode)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBase;
  _awVTMK4InBuf[1] = bcCtrlCode;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcstart, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
int bcstartx(TMK_DATA bcBase, TMK_DATA bcCtrlCode)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBase;
  _awVTMK4InBuf[1] = bcCtrlCode;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcstartx, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
int bcdeflink(TMK_DATA bcBase, TMK_DATA bcCtrlCode)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = bcBase;
  _awVTMK4InBuf[1] = bcCtrlCode;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcdeflink, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
DWORD bcgetlink()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetlink, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
TMK_DATA bcstop()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcstop, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD bcgetstate()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetstate, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
int rtreset()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtreset, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
int rtdefirqmode(TMK_DATA rtIrqMode)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtIrqMode;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefirqmode, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA rtgetirqmode()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetirqmode, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int rtdefmode(TMK_DATA rtMode)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtMode;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefmode, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA rtgetmode()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetmode, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
TMK_DATA rtgetmaxpage()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetmaxpage, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int rtdefpage(TMK_DATA rtPage)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtPage;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefpage, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA rtgetpage()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetpage, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int rtdefpagepc(TMK_DATA rtPagePC)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtPagePC;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefpagepc, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
int rtdefpagebus(TMK_DATA rtPageBus)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtPageBus;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefpagebus, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA rtgetpagepc()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetpagepc, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
TMK_DATA rtgetpagebus()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetpagebus, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int rtdefaddress(TMK_DATA rtAddress)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddress;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefaddress, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA rtgetaddress()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetaddress, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void rtdefsubaddr(TMK_DATA rtDir, TMK_DATA rtSubAddr)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtDir;
  _awVTMK4InBuf[1] = rtSubAddr;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtdefsubaddr, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
TMK_DATA rtgetsubaddr()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetsubaddr, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void rtputw(TMK_DATA rtAddr, TMK_DATA rtData)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  _awVTMK4InBuf[1] = rtData;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputw, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
TMK_DATA rtgetw(TMK_DATA rtAddr)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetw, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void rtputblk(TMK_DATA rtAddr, void *pcBuffer, TMK_DATA cwLength)
{
#ifdef _WIN64
  WORD _awVTMK4InBuf[8], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  _awVTMK4InBuf[1] = 0; //(WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = 0; //(WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  *((PUSHORT*)(_awVTMK4InBuf+4)) = (PUSHORT)pcBuffer;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputblk, _awVTMK4InBuf, 16, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#else
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  _awVTMK4InBuf[1] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputblk, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#endif
}
void rtgetblk(TMK_DATA rtAddr, void *pcBuffer, TMK_DATA cwLength)
{
#ifdef _WIN64
  WORD _awVTMK4InBuf[8], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  _awVTMK4InBuf[1] = 0; //(WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = 0; //(WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  *((PUSHORT*)(_awVTMK4InBuf+4)) = (PUSHORT)pcBuffer;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetblk, _awVTMK4InBuf, 16, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#else
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtAddr;
  _awVTMK4InBuf[1] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[2] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[3] = cwLength;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetblk, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#endif
}
void rtsetanswbits(TMK_DATA rtSetControl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtSetControl;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtsetanswbits, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
void rtclranswbits(TMK_DATA rtClrControl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtClrControl;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtclranswbits, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
TMK_DATA rtgetanswbits()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetanswbits, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void rtgetflags(void *pcBuffer, TMK_DATA rtDir, TMK_DATA rtFlagMin, TMK_DATA rtFlagMax)
{
#ifdef _WIN64
  WORD _awVTMK4InBuf[12], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = 0; //(WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[1] = 0; //(WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[2] = rtDir;
  _awVTMK4InBuf[3] = rtFlagMin;
  _awVTMK4InBuf[4] = rtFlagMax;
  _awVTMK4InBuf[5] = 0;
  _awVTMK4InBuf[6] = 0;
  _awVTMK4InBuf[7] = 0;
  *((PUSHORT*)(_awVTMK4InBuf+8)) = (PUSHORT)pcBuffer;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetflags, _awVTMK4InBuf, 24, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#else
  WORD _awVTMK4InBuf[5], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[1] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[2] = rtDir;
  _awVTMK4InBuf[3] = rtFlagMin;
  _awVTMK4InBuf[4] = rtFlagMax;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetflags, _awVTMK4InBuf, 10, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#endif
}
void rtputflags(void *pcBuffer, TMK_DATA rtDir, TMK_DATA rtFlagMin, TMK_DATA rtFlagMax)
{
#ifdef _WIN64
  WORD _awVTMK4InBuf[12], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = 0; //(WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[1] = 0; //(WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[2] = rtDir;
  _awVTMK4InBuf[3] = rtFlagMin;
  _awVTMK4InBuf[4] = rtFlagMax;
  _awVTMK4InBuf[5] = 0;
  _awVTMK4InBuf[6] = 0;
  _awVTMK4InBuf[7] = 0;
  *((PUSHORT*)(_awVTMK4InBuf+8)) = (PUSHORT)pcBuffer;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputflags, _awVTMK4InBuf, 24, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#else
  WORD _awVTMK4InBuf[5], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = (WORD)(LOWORD(pcBuffer));
  _awVTMK4InBuf[1] = (WORD)(HIWORD(pcBuffer));
  _awVTMK4InBuf[2] = rtDir;
  _awVTMK4InBuf[3] = rtFlagMin;
  _awVTMK4InBuf[4] = rtFlagMax;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputflags, _awVTMK4InBuf, 10, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
#endif
}
void rtsetflag()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtsetflag, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
void rtclrflag()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtclrflag, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
TMK_DATA rtgetflag(TMK_DATA rtDir, TMK_DATA rtSubAddr)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtDir;
  _awVTMK4InBuf[1] = rtSubAddr;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetflag, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
TMK_DATA rtgetstate()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetstate, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
TMK_DATA rtbusy()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtbusy, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void rtlock(TMK_DATA rtDir, TMK_DATA rtSubAddr)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtDir;
  _awVTMK4InBuf[1] = rtSubAddr;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtlock, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
void rtunlock()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtunlock, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
TMK_DATA rtgetcmddata(TMK_DATA rtBusCommand)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtBusCommand;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetcmddata, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void rtputcmddata(TMK_DATA rtBusCommand, TMK_DATA rtData)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtBusCommand;
  _awVTMK4InBuf[1] = rtData;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtputcmddata, _awVTMK4InBuf, 4, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
int mtreset()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mtreset, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA mtgetsw()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mtgetsw, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

TMK_DATA rtenable(TMK_DATA rtEnable)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = rtEnable;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtenable, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}

int mrtgetmaxn()
{
  return _VTMK4mrtMaxNum;
/*
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtgetmaxn, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return ((int)(_awVTMK4OutBuf[0]));
*/
}
DWORD mrtconfig(int mrtNumber)
{
  WORD _awVTMK4InBuf[2], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DWORD RTN,RT0,iRT;
  int err;
  char tmkName[32];


  if (_hVTMK4VxD[mrtNumber] != 0)
    return 0;

  sprintf (tmkName,"%c%c.%cTMK1553BDevice%d",0x5c,0x5c,0x5c,mrtNumber);
  _hVTMK4VxD[mrtNumber] = CreateFileA(tmkName,
                                     GENERIC_READ | GENERIC_WRITE,
                                     0,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL
                                    );
  if (_hVTMK4VxD[mrtNumber] == INVALID_HANDLE_VALUE)
  {
    _hVTMK4VxD[mrtNumber] = 0;
    return 0;
  }

  _awVTMK4InBuf[0] = (WORD)mrtNumber;
  DeviceIoControl(_hVTMK4VxD[mrtNumber], (DWORD)IOCTL_TMK_mrtconfig, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  err = 0;
  if (_awVTMK4OutBuf[0] != 0 && _awVTMK4OutBuf[1] != 0)
  {
    RT0 = (DWORD)_awVTMK4OutBuf[0];
    RTN = (DWORD)_awVTMK4OutBuf[1] + RT0 - 1;
    //открыть виртуальные устройства
    for (iRT = RT0; iRT <= RTN; ++iRT)
    {
      if (_hVTMK4VxD[iRT] != 0)
      {
        err = 1;
        break;
      }
      sprintf (tmkName,"%c%c.%cTMK1553BDevice%d",0x5c,0x5c,0x5c,iRT);
      _hVTMK4VxD[iRT] = CreateFileA(tmkName,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
                        );
      if (_hVTMK4VxD[iRT] == INVALID_HANDLE_VALUE)
      {
        _hVTMK4VxD[iRT] = 0;
        err = 1;
        break;
      }
    }//for(iRT = RT0; iRT <= RTN; ++iRT)
    if (err)
    {
      for (--iRT; iRT >= RT0; --iRT)
      {
        CloseHandle(_hVTMK4VxD[iRT]);
        _hVTMK4VxD[iRT] = 0;
      }
    }
  }//if(_awVTMK4OutBuf[0] != 0 && _awVTMK4OutBuf[1] != 0)
  else
  {
    err = 1;
  }
  if (err)
  {
    CloseHandle(_hVTMK4VxD[mrtNumber]);
    _hVTMK4VxD[mrtNumber] = 0;
    return 0;
  }
  return (_awVTMK4OutBuf[0] + (_awVTMK4OutBuf[1]<<16));
}
int mrtselected()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtselected, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return ((int)(_awVTMK4OutBuf[0]));
}
TMK_DATA mrtgetstate()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtgetstate, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
void mrtdefbrcsubaddr0()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtdefbrcsubaddr0, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL);
}
int mrtreset()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtreset, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA tmktimer(TMK_DATA tmkTimerCtrl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkTimerCtrl;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmktimer, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD tmkgettimer()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgettimer, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
TMK_DATA tmkgettimerl()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgettimerl, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD bcgetmsgtime()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_bcgetmsgtime, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
DWORD rtgetmsgtime()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_rtgetmsgtime, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
TMK_DATA tmkgethwver()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgethwver, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD tmkgetevtime()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetevtime, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
TMK_DATA tmkswtimer(TMK_DATA tmkTimerCtrl)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkTimerCtrl;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkswtimer, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
DWORD tmkgetswtimer()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[2];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmkgetswtimer, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 4, &_cbVTMK4Ret, NULL);
  return (((DWORD*)(_awVTMK4OutBuf))[0]);
}
TMK_DATA tmktimeout(TMK_DATA tmkTimeOut)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = tmkTimeOut;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_tmktimeout, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int mrtdefbrcpage(TMK_DATA mrtBrcPage)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = mrtBrcPage;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtdefbrcpage, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA mrtgetbrcpage()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mrtgetbrcpage, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int mbcinit(TMK_DATA mbcId)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = mbcId;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mbcinit, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
int mbcpreparex(TMK_DATA mbcId, TMK_DATA bcBase, TMK_DATA bcCtrlCode, TMK_DATA mbcDelay)
{
  WORD _awVTMK4InBuf[4], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = mbcId;
  _awVTMK4InBuf[1] = bcBase;
  _awVTMK4InBuf[2] = bcCtrlCode;
  _awVTMK4InBuf[3] = mbcDelay;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mbcpreparex, _awVTMK4InBuf, 8, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
int mbcstartx(TMK_DATA mbcId)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = mbcId;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mbcstartx, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}
TMK_DATA mbcalloc()
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mbcalloc, _awVTMK4InBuf, 0, _awVTMK4OutBuf, 2, &_cbVTMK4Ret, NULL);
  return _awVTMK4OutBuf[0];
}
int mbcfree(TMK_DATA mbcId)
{
  WORD _awVTMK4InBuf[1], _awVTMK4OutBuf[1];
  DWORD _cbVTMK4Ret;
  _awVTMK4InBuf[0] = mbcId;
  return (DeviceIoControl(_hVTMK4VxD[_VTMK4tmkCurNum], (DWORD)IOCTL_TMK_mbcfree, _awVTMK4InBuf, 2, _awVTMK4OutBuf, 0, &_cbVTMK4Ret, NULL))?0:GetLastError();
}

#pragma warning (default: 4244)
#pragma warning (default: 4700)
#pragma warning (default: 4715)
#pragma warning (default: 4996)

//#endif
