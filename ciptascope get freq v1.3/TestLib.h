#ifndef __TESTLIB_H__
#define __TESTLIB_H__

/*!
******************************************************************************
\file   TestLib.h
\brief  Header file for TestLib.h
******************************************************************************
*/

#include <windows.h>

#include <setjmp.h>

#define __RESET_COMMAND__ // Reset command for TCP/IP to speed up test

// static class to ease use of g_OSSim
// e.g g_OSSim = OSSim::SEND_CARD_NO_SIMULATION
class RUNMODE {
public:
  static const BYTE ONE_CARD = 0; // Run to 1 card only
  static const BYTE TWO_CARD = 1; // Run to 2 cards
};

#define CARD_ANONIMOUS				0
#define CARD_OURS					1
#define CARD_FROM_LOGOS				2
extern int	g_OSCard;              // init mode if we want to compare with another cards


extern BYTE g_OSSim;

#define S3FC9CC 0 // Samsung
#define S3FC9AD 0 // Samsung
#define TG97_3  1  // EMI
#define THC20BD 2  // Tong Fang
#define S3FC9BC 3  // Samsung
extern int g_ChipType;
extern int g_NormalTest;

#define PERSO_VERS_01  1
#define PERSO_VERS_02  2
#define PERSO_VERS_03  3
#define PERSO_VERS_04  4
#define PERSO_VERS_05  5
extern int g_PersoVersion;

#define DUMMY_ACCOUNT   0
#define MENTARI_085814812863 1
#define MENTARI_085814812854 2
#define IM3_085759190727     3
#define IM3_085759191029     4
#define IM3_085759191859     5
#define MENTARI_081574980630 6
#define XL_KSI               7

#define NTS_00               8

#define NTS_01               9
#define NTS_02               10
#define NTS_03               11
#define NTSELOAD_TEST        15

#define MENTARI_085881899691 12

#define MENTARI_08159977905  100
#define MENTARI_085888358125 101
extern int g_OnlineAccount;

// Prepaid registration TP-DA
#define SENDTO_OWN_NUMBER          0
#define SENDTO_FERRO_08159977905   1
#define SENDTO_MARCELL_08159272905 2
extern BYTE g_bSendTo;

#define LoByte(x) (BYTE)((x) & 0x00FF)
#define HiByte(x) (BYTE)((x >> 8) & 0x00FF)


extern jmp_buf g_jmpSTART;
extern char g_szExpRecv[];
extern WORD g_wPrintCompareResult;

extern DWORD g_dwTestLoop;

extern BYTE g_bWIBFlag;
#define _WIB12   0x00
#define _WIB13   0x01
#define WIB13  (g_bWIBFlag & _WIB13)

WORD StrFilterHex(
  char *pszStr /*! A string */
  );
WORD StrRemoveSpaces(
  char * pszStr
  );
BYTE StrByteToByte(
  char *pszByte /*! A byte represented in string */
  );
WORD StrByteArrayToByteArray(
    char *pszStrByteArray  /*! Byte array in string */
  , BYTE *pabByteArray     /*! Byte arra output     */
  );
WORD ByteArrayToStrByteArray(
    BYTE * pabByteArray    /*! Byte array               */
  , WORD wLen              /*! Length of byte array     */
  , char *pszStrByteArray  /*! Output string byte array */
  );

WORD StrHexToWord(
  char * pszHex /*! Hex string to be converted */
  );
BYTE StrHexToByte(
    char * pszHex /*! Hex string to be converted */
  , BYTE bPos     /*! Byte position in the hex string to be converted, starts from 0 */
  );
BYTE StrHexToDialNo(char *StrHex, BYTE *DialNo);
WORD StrTextToStrByteArray(
    IN  char *pszText          /*! Text */
  , OUT char *pszStrByteArray  /*! String byte array */
  );

void PrintSend(void);
void PrintRecv(void);

WORD PrintCompareResult(
    char *pszRes  /*! Result */
  , char *pszExp  /*! Expected */
  );

WORD PrintCompareResult(
    BYTE bCmd
  , BYTE *pabRes1
  , WORD wLen1
  , BYTE *pabRes2
  , WORD wLen2);

void GetByteStringSet(
    char * pszSrc /*! Source string */
  , char * pszDst /*! Output */
  , WORD wStart   /*! The byte start position */
  , WORD wLen     /*! Length */
  );


WORD PrintDirectCompareResult(
    char *pszRes  /*! Result */
  , char *pszExp  /*! Expected */
  );

void DumpVar(BYTE *pVar, WORD wLen);

void ClockStart();
void ClockStop();

void Comp128_3(
    BYTE *   Ki_
  , BYTE * pRes
  );

WORD Interpret_SMSPP_APDU(
  char *psAPDU      /*! APDU */
  , char *psOTAKey    /*! OTA Key */
  , char * psResult /*! Result */
  , BYTE *pabSPIKICKID
  , BYTE *pabTAR
  , BYTE *pabCNTR
  , BYTE *pabCMD
  );

#ifdef __cplusplus
extern "C" {
#endif
void file_uncompress(char *file); // ZLib
#ifdef __cplusplus
}
#endif


#endif // #ifndef __TESTLIB_H__

