/*!
******************************************************************************
\file   TestLib.cpp
\brief  Various functions for testing


\mainpage

<b>Purpose</b>

GSM 11.17 conformance test

<b>Files/Directories</b>

<b>Test List</b>

\ref Test_6_3_1 GSM 11.17 Section 6.3.1 \n
\ref Test_6_3_2 GSM 11.17 Section 6.3.2 \n

<b>Test General Flow</b>


\dot
digraph G {

subgraph cluster1 {
  //node [style=filled,color=white];
  style=filled;
  color=lightgrey;
  label = "Main";
  Card_InitReader
  Test_XX
}

subgraph cluster2 {
  //node [style=filled,color=white];
  style=filled;
  color=lightgrey;
  label = "Test_XX";
  Log_Open
  Log_Close
  Card_Reset
  Card_SendAPDU
}

subgraph cluster3 {
  //node [style=filled,color=white];
  style=filled;
  color=lightgrey;
  label = "Card_SendAPDU";
  PrintCompareResult
  Log_RecordError
}

Card_InitReader    [style=filled color=white URL="\ref Card_InitReader"];
Card_Reset         [style=filled color=white URL="\ref Card_Reset"];
Card_SendAPDU      [style=filled color=white URL="\ref Card_SendAPDU"];
PrintCompareResult [style=filled color=white URL="\ref PrintCompareResult"];
Log_Open           [style=filled color=white URL="\ref Log_Open"];
Log_RecordError    [style=filled color=white URL="\ref Log_RecordError"];
Log_Close          [style=filled color=white URL="\ref Log_Close"];

Card_InitReader -> Test_XX;
Test_XX -> Log_Open -> Card_Reset -> Card_SendAPDU -> Log_Close 
Card_SendAPDU -> Card_SendAPDU
Card_SendAPDU -> PrintCompareResult -> Log_RecordError

}
\enddot



<b>Test Libraries</b>


\dot

digraph G {

subgraph cluster3 {
  //node [style=filled,color=white];
  style=filled;
  color=lightgrey;
  label = "Test";
  Test_XX
  Test_YY
}

subgraph cluster4 {
  //node [style=filled,color=white];
  style=filled;
  color=lightgrey;
  label = "Log.cpp";
  Log_Open
  Log_Close
  Log_RecordError
  printt
}

subgraph cluster5 {
  //node [style=filled,color=white];
  style=filled;
  color=lightgrey;
  label = "TestLib.cpp";
  PrintCompareResult
}

subgraph cluster0 {
  label = "CardInterface.cpp";
  //node [style=filled,color=white];
  style=filled;
  color=lightgrey;
  Card_Reset 
  Card_SendAPDU
}

subgraph cluster1 {
  label = "Reader Interface";

  subgraph cluster11 {
    label = "TCPIPInterface.cpp";
    //node [style=filled,color=white];
    style=filled;
    color=lightgrey;
    TCPIP_GetATR
    TCPIP_SendAPDU
    //TCPIP_Open
    //TCPIP_Close
}
 
subgraph cluster12 {
   label = "PCSCInterface.cpp";
   //node [style=filled,color=white];
   style=filled;
   color=lightgrey;
   PCSC_GetATR
   PCSC_SendAPDU
}

Card_Reset         [style=filled color=white URL="\ref Card_Reset"];
Card_SendAPDU      [style=filled color=white URL="\ref Card_SendAPDU"];
PrintCompareResult [style=filled color=white URL="\ref PrintCompareResult"];
Log_Open           [style=filled color=white URL="\ref Log_Open"];
Log_RecordError    [style=filled color=white URL="\ref Log_RecordError"];
Log_Close          [style=filled color=white URL="\ref Log_Close"];
printt             [style=filled color=white URL="\ref printt"];

TCPIP_GetATR       [style=filled color=white URL="\ref TCPIP_GetATR"];
PCSC_GetATR        [style=filled color=white URL="\ref PCSC_GetATR"];
TCPIP_SendAPDU     [style=filled color=white URL="\ref TCPIP_SendAPDU"];
PCSC_SendAPDU      [style=filled color=white URL="\ref PCSC_SendAPDU"];

}

Test_XX -> Card_Reset
Test_XX -> Card_SendAPDU
Test_XX -> Log_Open
Test_XX -> Log_Close
Test_XX -> printt

Card_Reset -> TCPIP_GetATR
Card_Reset -> PCSC_GetATR
Card_SendAPDU -> TCPIP_SendAPDU
Card_SendAPDU -> PCSC_SendAPDU
Card_SendAPDU -> Log_RecordError
Card_SendAPDU -> PrintCompareResult
}

\enddot

<b>Code example</b>
\code
	#if 0 // Example only : MODE_STANDALONE_SIMULATION
	  g_OSSim = MODE_SIMULATION_ONLY;
	  Perso();
	  GsmSim_Main();
	#endif // MODE_STANDALONE_SIMULATION

	#if 0 // Example only : MODE_SEND_CARD_NO_SIMULATION
	  g_OSSim = MODE_SEND_CARD_NO_SIMULATION;
	  Card_InitReader(argc, argv);
	  Card_Reset();
	  Card_SendAPDU("A0A4000002 3F00", "", __LINE__);
	  Card_SendAPDU("A0C0000022", "", __LINE__);
	  Card_Reset();
	  Card_SendAPDU("A0A4000002 3F00", "9F22", __LINE__);
	  Card_SendAPDU("A0C0000022", "", __LINE__);

	#endif

	#if 0 // Example only : MODE_SEND_CARD_COMPARE_SIMULATION
	  g_OSSim = MODE_SEND_CARD_COMPARE_SIMULATION;
	  Card_InitReader(argc, argv);
	  Perso();
	  Card_Reset();
	  Card_SendAPDU("A0A4000002 3F00", "", __LINE__);
	  Card_SendAPDU("A0C0000022", "", __LINE__);
	#endif // MODE_SEND_CARD_COMPARE_SIMULATION

	#if 0 // Example only : RUNMODE::TWO_CARD
	  g_OSSim = RUNMODE::TWO_CARD;
	  Card_InitReader(argc, argv);
	  Card_Reset();
	  Card_SendAPDU("A0A4000002 3F00", "", __LINE__);
	  Card_SendAPDU("A0C0000022", "", __LINE__);
	  Card_SendAPDU("A0A4000002 2FE2", "", __LINE__);
	  Card_SendAPDU("A0C000000F", "", __LINE__);
	#endif // RUNMODE::TWO_CARD
\endcode
******************************************************************************
*/

#include "stdafx.h"
#include <ctype.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>

#include "TestLib.h"


/*!
OS simulation mode, 1: Enable+Send to card, 2: Enable+simulation only,  0 simulation disabled, semd to card
*/
/*
MODE_SEND_CARD_NO_SIMULATION
MODE_SEND_CARD_COMPARE_SIMULATION
MODE_SIMULATION_ONLY
*/
BYTE g_OSSim = RUNMODE::ONE_CARD;
int	g_OSCard = CARD_ANONIMOUS;              // init mode if we want to compare with another cards
int g_ChipType = 0;
int g_OnlineAccount = 0;

int g_NormalTest = 1;

int g_PersoVersion = PERSO_VERS_01;
/*!
Check result: 1: Check, 0 otherwise
*/
//int g_CheckResult = 0;

/*!
- Jump buffer used when error is found and need to exit test
*/
jmp_buf g_jmpSTART;

/*!
Expected response data in hex string 
*/
char g_szExpRecv[800];
/*!
PrintCompareResult last return value
*/
WORD g_wPrintCompareResult;

/*!
- Max test counter loop for Random test
*/
DWORD g_dwTestLoop = 1000;

BYTE g_bWIBFlag = 0;
/*!
******************************************************************************
\section  StrFilterHex
\brief    Helper function to filter hex only character
\return   length of the string after processing
\author
\verbatim
\endverbatim
******************************************************************************
*/
WORD StrFilterHex(
  char *pszStr /*! A string */
  )
{
  WORD wLen = (WORD)strlen(pszStr);
  WORD i, j;
  char c;
  char *pszTmp = (char*)malloc(wLen+1);
  //char pszTmp[2000];
  strcpy(pszTmp, pszStr);
  
  for (i = 0, j = 0; i < wLen; i++) {
    c = toupper(pszTmp[i]);
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c == 'X') || (c == '.')) {
      pszStr[j++] = c;
    }
  }
  pszStr[j] = 0x00;
  free(pszTmp);
  return j;
}

WORD StrRemoveSpaces(
  char * pszStr
  )
{
  WORD wLen = (WORD)strlen(pszStr);
  WORD i, j;
  char c;
  char *pszTmp = (char*)malloc(wLen+1);
  //char pszTmp[2000];
  strcpy(pszTmp, pszStr);
  
  for (i = 0, j = 0; i < wLen; i++) {
    c = pszTmp[i];
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
      continue;
    }
    pszStr[j++] = c;
  }
  pszStr[j] = 0x00;
  free(pszTmp);
  return j;
}

/*!
******************************************************************************
\section  CharNibbleToNibble 
\brief    Helper function to convert a nibble in char to nibble in BYTE
\return   a nibble
\author
\verbatim
\endverbatim
******************************************************************************
*/
static BYTE CharNibbleToNibble(
  char c  /*! A nibble represented in a character string */
) 
{
  c = toupper(c);
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 'A' + 0x0A;
  return 0;
}

/*!
******************************************************************************
\section  CharNibbleToNibble 
\brief    Helper function to convert a nibble in char to nibble in BYTE
\return   a nibble
\author
\verbatim
\endverbatim
******************************************************************************
*/
BYTE StrByteToByte(
  char *pszByte /*! A byte represented in string */
  )
{
  return (CharNibbleToNibble(pszByte[0]) << 4) | (CharNibbleToNibble(pszByte[1]));
}

/*!
******************************************************************************
\section  StrByteArrayToByteArray 
\brief    Helper function to string byte arrat to byte array
\return   a nibble
\author
\verbatim
\endverbatim
******************************************************************************
*/
WORD StrByteArrayToByteArray(
    char *pszStrByteArray  /*! Byte array in string */
  , BYTE *pabByteArray     /*! Byte arra output     */
  )
{
  char * szStrByteArray = (char*)malloc(strlen(pszStrByteArray) + 1);
  //char szStrByteArray[2000];
  strcpy(szStrByteArray, pszStrByteArray);
  WORD wLen = StrFilterHex(szStrByteArray);
  WORD i, j;

  for (i = 0, j = 0; i < wLen; i += 2) {
    pabByteArray[j++] = StrByteToByte(&szStrByteArray[i]);
  }
  free(szStrByteArray);
  return j;
}

/*!
******************************************************************************
\section  ByteArrayToStrByteArray
\brief    Helper function byte array to string byte array
\return   a nibble
\author
\verbatim
\endverbatim
******************************************************************************
*/
WORD ByteArrayToStrByteArray(
    BYTE * pabByteArray    /*! Byte array               */
  , WORD wLen              /*! Length of byte array     */
  , char *pszStrByteArray  /*! Output string byte array */
  )
{
  WORD i;
  char szTmp[5];
  pszStrByteArray[0] = 0x00;

  for (i = 0; i < wLen; i++) {
    sprintf(szTmp, "%02X", pabByteArray[i]);
    strcat(pszStrByteArray, szTmp);
  }
  return (WORD)strlen(pszStrByteArray);
}

/*!
******************************************************************************
\section  StrHexToWord
\brief    Convert hex string to word
\return   -
\author
\verbatim
\endverbatim
******************************************************************************
*/
WORD StrHexToWord(
  char * pszHex /*! Hex string to be converted */
  )
{
  WORD wRet;
  char *szTmp = (char*)malloc(strlen(pszHex)+1);
  //char szTmp[10];
  strcpy(szTmp, pszHex);
  StrFilterHex(szTmp);
  wRet = ((WORD)StrByteToByte(&szTmp[0]) << 8) | StrByteToByte(&szTmp[2]);
  free(szTmp);
  return wRet;
}



/*!
******************************************************************************
\section  StrHexToByte
\brief    Convert hex string to byte
\return   -
\author
\verbatim
\endverbatim
******************************************************************************
*/
BYTE StrHexToByte(
    char * pszHex /*! Hex string to be converted */
  , BYTE bPos     /*! Byte position in the hex string to be converted, starts from 0 */
  )
{
  char *szTmp = (char*)malloc(strlen(pszHex)+1);
  //char szTmp[10];
  BYTE bRet;
  strcpy(szTmp, pszHex);
  if (StrFilterHex(szTmp) == 0) {
    free(szTmp);
    return 0;
  }
  bRet = StrByteToByte(&szTmp[bPos * 2]);
  free(szTmp);
  return bRet;
}

/*!
******************************************************************************
\section  StrHexToDialNo
\brief    Generate dial number
\return   -
\author
\verbatim
\endverbatim
******************************************************************************
*/
BYTE StrHexToDialNo(char *StrHex, BYTE *DialNo)
{
   BYTE i, j;
   BYTE bLen = (BYTE)strlen(StrHex);
   char *StrTmp;
   BYTE bTmp[100];

   StrTmp = (char*)malloc(strlen(StrHex) + 2);
   strcpy(StrTmp, StrHex);

   bLen = (BYTE)StrFilterHex(StrTmp);
   
   // Determine TON/NPI
   if (StrTmp[0] == '+') {
      DialNo[0] = 0x91;
      j = 1;
      bLen--;
   }
   else  {
      DialNo[0] = 0x81;
      j = 0;
   }

   if (bLen % 2) {
      // Pading 'F'
      strcat(StrTmp, "F");
      bLen++;
   }

   // Convert to hex
   for (i = 0; j < bLen; i++, j += 2) {
      bTmp[i] = StrByteToByte(&StrTmp[j]);
   }

   free(StrTmp);

   // Swap bytes
   bLen = i;
   for (i = 0; i < bLen; i++) {
      j = bTmp[i];
      bTmp[i] = (BYTE) ((0xF0 & (j << 4)) | (0x0F & (j >> 4)));
   }

   // copy to DialNo
   for (i = 0; i < bLen; i++) {
      DialNo[i + 1] = bTmp[i];
   }


   return i + 1; // 1 = TON/NPI
}

/*!
******************************************************************************
\section  StrTextToStrByteArray 
\brief    Convert text to string byte array
\return   -
\author
\verbatim

e.g. StrTextToStrByteArray("ABC", szOut);

     szOut = "414243";

\endverbatim
******************************************************************************
*/
WORD StrTextToStrByteArray(
    IN  char *pszText          /*! Text */
  , OUT char *pszStrByteArray  /*! String byte array */
  )
{
  char szTmp[5];
  WORD i;
  pszStrByteArray[0] = 0x00;
  
  for (i = 0; i < (WORD)strlen(pszText); i++) {
    sprintf(szTmp, "%02X", pszText[i]);
    strcat(pszStrByteArray, szTmp);
  }

  return (WORD)strlen(pszStrByteArray);
}

/*!
******************************************************************************
\section  PrintSend 
\brief    Helper print apdu to be sent
\return   -
\author
\verbatim
\endverbatim
******************************************************************************
*/
void PrintSend(void)
{
  WORD i;
#if 1
  char szTmp[1000];
  char szTmp2[5];
  strcpy(szTmp, "=> : ");
  for (i = 0; i < g_wSend; i++) {
    sprintf(szTmp2, "%02X", g_abSend[i]);
    strcat(szTmp, szTmp2);
  }
  strcat(szTmp, "\n");
  printt(szTmp);
#else
  printt("=> : ");
  for (i = 0; i < g_wSend; i++) {
    printt("%02X", g_abSend[i]);
  }
  printt("\n");
#endif
}

/*!
******************************************************************************
\section  PrintRecv 
\brief    Helper print response
\return   -
\author
\verbatim
\endverbatim
******************************************************************************
*/
void PrintRecv(void)
{
  WORD i;
#if 1
  char szTmp[1000];
  char szTmp2[5];
  strcpy(szTmp, "<= : ");
  for (i = 0; i < g_wRecv; i++) {
    sprintf(szTmp2, "%02X", g_abRecv[i]);
    strcat(szTmp, szTmp2);
  }
  strcat(szTmp, "\n");
  printt(szTmp);
#else
  printt("<= : ");
  for (i = 0; i < g_wRecv; i++) {
    printt("%02X", g_abRecv[i]);
  }
  printt("\n");
#endif
}

/*!
******************************************************************************
\section  GetByteStringSet 
\brief    Get a subset of string bytes 
\return   -
\author
\verbatim
\endverbatim
******************************************************************************
*/
void GetByteStringSet(
    char * pszSrc /*! Source string */
  , char * pszDst /*! Output */
  , WORD wStart   /*! The byte start position */
  , WORD wLen     /*! Length */
  )
{
  StrFilterHex(pszSrc);
  memcpy(pszDst, &pszSrc[wStart * 2], (wLen * 2));
  pszDst[wLen * 2] = 0x00;
}

void Interpret_SW1SW2(WORD wSW1SW2, char *szPrint)
{
  switch (wSW1SW2) {
  case SW_OK: //     0x9000 // '90''00'      normal ending of the command
    strcpy(szPrint, "OK");
    break;
  // 9.4.2    Responses to commands which are postponed
  case SW_POSTPONE: // 0x9300 // '93'    '00'         SIM Application Toolkit is busy. Command cannot be executed at present, further normal commands are allowed.
    strcpy(szPrint, "SIM Application Toolkit is busy. Command cannot be executed at present, further normal commands are allowed.");
    break;
  // 9.4.3    Memory management
  case SW_OK_RETRY: // 0x920F // '92'    '0X'         command successful but after using an internal update retry routine 'X' times
    strcpy(szPrint, "command successful but after using an internal update retry routine 'X' times");
    break;
  case SW_ERR_MEM: // 0x9240      // '92' '40'         memory problem
    strcpy(szPrint, "memory problem");
    break;
  // 9.4.4    Referencing management
  case SW_ERR_NOEFSEL: // 0x9400 // '94''00'         no EF selected
    strcpy(szPrint, "no EF selected");
    break;
  case SW_ERR_RANGE: //   0x9402 // '94''02'         out of range (invalid address)
    strcpy(szPrint, "out of range (invalid address)");
    break;
  case SW_ERR_NOTFOUND: // 0x9404 // '94''04'         file ID not found     pattern not found
    strcpy(szPrint, "file ID not found, pattern not found");
    break;
  case SW_ERR_INCONS: //  0x9408 // '94''08'         file is inconsistent with the command
    strcpy(szPrint, "file is inconsistent with the command");
    break;
  // 9.4.5    Security management
  case SW_ERR_NOCHV: // 0x9802 // '98''02'         no CHV initialized
    strcpy(szPrint, "no CHV initialized");
    break;
  case SW_ERR_ACC: //   0x9804 // '98''04'         access condition not fulfilled
                               // unsuccessful CHV verification, at least one attempt left
                               // unsuccessful UNBLOCK CHV verification, at least one attempt left
                               // authentication failed 
    strcpy(szPrint, "access condition not fulfilled");
    break;
  case SW_ERR_CHVSTAT: //  0x9808 // '98''08'         in contradiction with CHV status
    strcpy(szPrint, "in contradiction with CHV status");
    break;
  case SW_ERR_INVSTAT: //  0x9810 // '98''10'         in contradiction with invalidation status
    strcpy(szPrint, "in contradiction with invalidation status");
    break;
  case SW_ERR_CHVBLOCK: // 0x9840 // '98''40'         unsuccessful CHV verification, no attempt left
                                  // unsuccessful UNBLOCK CHV verification, no attempt left
                                  // CHV blocked
                                  // UNBLOCK CHV blocked
    strcpy(szPrint, "unsuccessful CHV verification, no attempt left");
    break;
  case SW_ERR_INCR: //    0x9850  // '98''50'         increase cannot be performed, Max value reached
                               // NOTE:    A Phase 1 SIM may send this error code after the third consecutive unsuccessful CHV verification attempt or the tenth consecutive unsuccessful unblocking attempt.
    strcpy(szPrint, "increase cannot be performed, Max value reached");
    break;
  default:
    switch ((BYTE)(wSW1SW2 >> 8))
    {
    case ((BYTE)(SW_STK >> 8)): //    0x9100 // '91''XX'      
      sprintf(szPrint, "normal ending of the command, with extra information from the proactive SIM containing a command for the ME. Length '%02X' of the response data", (BYTE)wSW1SW2);
      break;
    case ((BYTE)(SW_ERR_DDL >> 8)): // 0x9E00 // '9E''XX'      length 'XX' of the response data given in case of a SIM data download error '9F''XX'      length 'XX' of the response data
      sprintf(szPrint, "length '%02X' of the response data given in case of a SIM data download error '9F''XX' length 'XX' of the response data", (BYTE)wSW1SW2);
      break;
    case ((BYTE)(SW_RESP >> 8)): //    0x9F00 // '9F''XX'      length 'XX' of the response data
      sprintf(szPrint, "length '%02X' of the response data", (BYTE)wSW1SW2);
      break;
    // 9.4.6    Application independent errors
    case ((BYTE)(SW_ERR_P3 >> 8)):  //    0x6700    // '67''XX'         incorrect parameter P3 (see note)
      strcpy(szPrint, "incorrect parameter P3");
      break;
    case ((BYTE)(SW_ERR_P1P2 >> 8)) : //  0x6B00    // '6B''XX'#         incorrect parameter P1 or P2 (see ##)
      strcpy(szPrint, "incorrect parameter P1 or P2");
      break;
    case ((BYTE)(SW_ERR_INS >> 8)) : //   0x6D00    // '6D''XX'#         unknown instruction code given in the command
      strcpy(szPrint, "unknown instruction code given in the command");
      break;
    case ((BYTE)(SW_ERR_CLA >> 8)): //   0x6E00    // '6E''XX'#         wrong instruction class given in the command
      strcpy(szPrint, "wrong instruction class given in the command");
      break;
    case ((BYTE)(SW_ERR_TECH >> 8)):  // 0x6F00    // '6F''XX'#         technical problem with no diagnostic given
     strcpy(szPrint, "technical problem with no diagnostic given");
    default:
      sprintf(szPrint, "Uknown SW1SW2");
    }
  }
}


/*!
******************************************************************************
\section  PrintDirectCompareResult 
\brief    Helper to compare result & expected
\return   -
\author
\verbatim
\endverbatim
******************************************************************************
*/
WORD PrintDirectCompareResult(
    char *pszRes  /*! Result */
  , char *pszExp  /*! Expected */
  )
{
  WORD i;
  g_wPrintCompareResult = 1;
  
  char *pszStr1 = (char*)malloc(strlen(pszRes) + 1);
  char *pszStr2 = (char*)malloc(strlen(pszExp) + 1);

  strcpy(pszStr1, pszRes);
  strcpy(pszStr2, pszExp);
  WORD wLen1 = StrFilterHex(pszStr1);
  WORD wLen2 = StrFilterHex(pszStr2);

  printt("Res: ");
  for (i = 0; i < wLen1; i++) {
    printt("%C", pszStr1[i]);
  }
  printt("\n");

  printt("Exp: ");
  for (i = 0; i < wLen2; i++) {
    printt("%C", pszStr2[i]);
  }
  printt("\n");

  printt("     ");
  for (i = 0; i < wLen2; i++) {
    if (pszStr2[i] == '.') {
      break;
    }
    else if ((pszStr1[i] != pszStr2[i]) && (toupper(pszStr2[i]) != 'X')) {
      printt("^");
      g_wPrintCompareResult = 0;
    }
    else {
      printt(" ");
    }
  }

  char szTmp[700];
  strcpy(szTmp,"Please check compare with remark\n");
  
  printt("--> %s\n", szTmp);

  free(pszStr1);
  free(pszStr2);

  return g_wPrintCompareResult;;
}


/*!
******************************************************************************
\section  PrintCompareResult 
\brief    Helper to compare result & expected
\return   -
\author
\verbatim
\endverbatim
******************************************************************************
*/
WORD PrintCompareResult(
    char *pszRes  /*! Result */
  , char *pszExp  /*! Expected */
  )
{
  WORD i;
  g_wPrintCompareResult = 1;
  
  char *pszStr1 = (char*)malloc(strlen(pszRes) + 1);
  char *pszStr2 = (char*)malloc(strlen(pszExp) + 1);
  //char pszStr1[1000];
  //char pszStr2[1000];
  char szTmp[1000];
  char szTmp2[5];

  strcpy(pszStr1, pszRes);
  strcpy(pszStr2, pszExp);
  WORD wLen1 = StrFilterHex(pszStr1);
  WORD wLen2 = StrFilterHex(pszStr2);
#if 1
  strcpy(szTmp, "Res: ");
  //for (i = 0; i < wLen1-4; i++) {
  for (i = 0; i < wLen1; i++) {
    sprintf(szTmp2, "%C", pszStr1[i]);
    strcat(szTmp, szTmp2);
  }
  strcat(szTmp, "\n");
  printt(szTmp);
#else
  printt("Res: ");
  //for (i = 0; i < wLen1-4; i++) {
  for (i = 0; i < wLen1; i++) {
    printt("%C", pszStr1[i]);
  }
  printt("\n");
#endif
  //printt(" %s\n", &pszStr1[wLen1-4]);

#if 1
  strcpy(szTmp, "Exp: ");
  for (i = 0; i < wLen2; i++) {
    sprintf(szTmp2, "%C", pszStr2[i]);
    strcat(szTmp, szTmp2);
  }
  strcat(szTmp, "\n");
  printt(szTmp);
#else
  printt("Exp: ");
  //for (i = 0; i < wLen2-4; i++) {
  for (i = 0; i < wLen2; i++) {
    printt("%C", pszStr2[i]);
  }
  //printt(" %s\n", &pszStr2[wLen2-4]);
  printt("\n");
#endif
  printt("     ");
  for (i = 0; i < wLen2; i++) {
    //if (i == (wLen2-4)) {
    //  printt(" ");
    //}
    if (pszStr2[i] == '.') {
      break;
    }
    else if ((pszStr1[i] != pszStr2[i]) && (toupper(pszStr2[i]) != 'X')) {
      printt("^");
      g_wPrintCompareResult = 0;
    }
    else {
      printt(" ");
    }
  }

  //char szTmp[700];
  BYTE bSW1 = StrByteToByte(&pszStr1[strlen(pszStr1)-4]);
  BYTE bSW2 = StrByteToByte(&pszStr1[strlen(pszStr1)-2]);
  Interpret_SW1SW2((WORD)(bSW1 << 8) + bSW2, szTmp);

  printt("--> %s\n", szTmp);

  free(pszStr1);
  free(pszStr2);

  return g_wPrintCompareResult;;
}

void PrintFileCharacteristic(BYTE bTmp1)
{
  BYTE bTmp2;
    /*
      Detail 1: File characteristics
		      b8	b7	b6	b5	B4	b3	b2	b1
										                  Clock stop (see below)
										              For running the authentication algorithm, or the ENVELOPE command for SIM Data Download, 
                                  a frequency is required of at least 13/8 MHz if b2=0 and 13/4 MHz if b2=1
										      Clock stop (see below)
										  for coding (see GSM 11.12 [28])
							RFU
			    b8=0: CHV1 enabled; b8=1: CHV1 disabled

      The coding of the conditions for stopping the clock is as follows:
      Bit b1	Bit b3	Bit b4	
      1	0	0	clock stop allowed, no preferred level
      1	1	0	clock stop allowed, high level preferred
      1	0	1	clock stop allowed, low level preferred
      0	0	0	clock stop not allowed
      0	1	0	clock stop not allowed, unless at high level
      0	0	1	clock stop not allowed, unless at low level

    */
    if (bTmp1 & 0x80) {
      printt("              1 : b8 CHV 1 disabled\n");
    }
    else {
      printt("              0 : b8 CHV 1 enabled\n");
    }
    if (bTmp1 & 0x10) {
      printt("              1 : b5\n");
    }
    else {
      printt("              0 : b5\n");
    }

    if (bTmp1 & 0x02) {
      printt("              1 : Run auth. algo. or the ENVELOPE requires frequency at least 13/4 MHz\n");
    }
    else {
      printt("              0 : Run auth. algo. or the ENVELOPE requires frequency at least 13/8 MHz\n");
    }

    bTmp2 = ((bTmp1 & 0x01) << 2) | ((bTmp1 & 0x04) >> 1) | ((bTmp1 & 0x08) >> 3);  //    (bTmp1 >> 2) & 0x03) | ((bTmp1 << 2) & 0x04);
    switch (bTmp2) {
    case 0x04 : 
      printt("              1 0 0 clock stop allowed, no preferred level\n"); break;
    case 0x06 : 
      printt("              1	1	0	clock stop allowed, high level preferred\n"); break;
    case 0x05 : 
      printt("              1	0	1	clock stop allowed, low level preferred\n"); break;
    case 0x00 : 
      printt("              0	0	0	clock stop not allowed\n"); break;
    case 0x02 : 
      printt("              0	1	0	clock stop not allowed, unless at high level\n"); break;
    case 0x01 : 
      printt("              0	0	1	clock stop not allowed, unless at low level\n"); break;
    }
}

WORD PrintCompareGetResponse(
    BYTE *pabRes1
  , WORD wLen1
  , BYTE *pabRes2
  , WORD wLen2
  )
{
  BYTE bTmp1, bTmp2;
//  WORD i;
  WORD wLen = wLen1 > wLen2 ? wLen2 : wLen1;
  switch (pabRes1[6]) {
  case FILE_TYPE_MF:
  case FILE_TYPE_DF:
    // 1   2	  RFU	2
    //GetByteStringSet(szRes, szPrint, 0, 2);
    printt("\n%02X%02X : %02X%02X : \t\tRFU\n", pabRes1[0], pabRes1[1], pabRes2[0], pabRes2[1]);
    // 3   4	  Total amount of memory of the selected directory which is not allocated to any of the DFs or EFs under the selected directory	2    
    //GetByteStringSet(szRes, szPrint, 2, 2);
    printt("%02X%02X : %02X%02X : \t\tFree memory\n", pabRes1[2], pabRes1[3], pabRes2[2], pabRes2[3]);
    // 5   6	  File ID	2
    //GetByteStringSet(szRes, szPrint, 4, 2);
    printt("%02X%02X : %02X%02X : \t\tFile Id\n", pabRes1[4], pabRes1[5], pabRes2[4], pabRes2[5]);
    // 7	      Type of file (see subclause 9.3)
    //GetByteStringSet(szRes, szPrint, 6, 1);
    printt("%02X : %02X : \t\tType of file = ", pabRes1[6], pabRes2[6]);
    switch (pabRes1[6]) {
    case FILE_TYPE_MF: printt("MF\n"); break;
    case FILE_TYPE_DF: printt("DF\n"); break;
    case FILE_TYPE_EF: printt("EF\n"); break;
    default: printt("UNKNOWN\n");
    }
    // 8  12	  RFU	5
    //GetByteStringSet(szRes, szPrint, 7, 5);
    printt("%02X%02X%02X%02X%02X : %02X%02X%02X%02X%02X : \t\tRFU\n", 
           pabRes1[7], pabRes1[8], pabRes1[9], pabRes1[10], pabRes1[11],
           pabRes2[7], pabRes2[8], pabRes2[9], pabRes2[10], pabRes2[11]
           );
    // 13	    Length of the following data (byte 14 to the end)	1
    //GetByteStringSet(szRes, szPrint, 12, 1);
    printt("%02X : %02X : \t\tLength of following bytes\n", pabRes1[12], pabRes2[12]);
    // 14	File characteristics (see detail 1)	1
    //GetByteStringSet(szRes, szPrint, 13, 1);
    printt("%02X : %02X : \t\tFile characteristics\n", pabRes1[13], pabRes2[13]);
    bTmp1 = pabRes1[13];
    bTmp2 = pabRes2[13];
    PrintFileCharacteristic(bTmp1);
    if (bTmp1 != bTmp2) {
      printt("--------------------------\n");
      PrintFileCharacteristic(bTmp2);
    }

    // 15	Number of DFs which are a direct child of the current directory	1
    //GetByteStringSet(szRes, szPrint, 14, 1);
    printt("%02X : %02X : \t\tNumber of DF\n", pabRes1[14], pabRes2[14]);
    // 16	Number of EFs which are a direct child of the current directory	1
    //GetByteStringSet(szRes, szPrint, 15, 1);
    printt("%02X : %02X : \t\tNumber of EF\n", pabRes1[15], pabRes2[15]);
    // 17	Number of CHVs, UNBLOCK CHVs and administrative codes	1
    //GetByteStringSet(szRes, szPrint, 16, 1);
    printt("%02X : %02X : \t\tCHVs, UNBLOCK CHVs and administrative codes\n", pabRes1[16], pabRes2[16]);
    // 18	RFU	1
    //GetByteStringSet(szRes, szPrint, 17, 1);
    printt("%02X : %02X : \t\tRFU\n", pabRes1[17], pabRes2[17]);
    // 19	CHV1 status (see detail 2)	1
    //GetByteStringSet(szRes, szPrint, 18, 1);
    printt("%02X : %02X : \t\tCHV1 status\n", pabRes1[18], pabRes2[18]);
    // 20	UNBLOCK CHV1 status (see detail 2)	1
    //GetByteStringSet(szRes, szPrint, 19, 1);
    printt("%02X : %02X : \t\tUNBLOCK CHV1 status\n", pabRes1[19], pabRes2[19]);
    // 21	CHV2 status (see detail 2)	1
    //GetByteStringSet(szRes, szPrint, 20, 1);
    printt("%02X : %02X : \t\tCHV2 status\n", pabRes1[20], pabRes2[20]);
    // 22	UNBLOCK CHV2 status (see detail 2)	1
    //GetByteStringSet(szRes, szPrint, 21, 1);
    printt("%02X : %02X : \t\tUNBLOCK CHV2 status\n", pabRes1[21], pabRes2[21]);
    // 23	RFU	1
    // 24   34	Reserved for the administrative management	0 = lgth = 11

    break;
#if 1
  case FILE_TYPE_EF:
    // 1   2	RFU	2
    //GetByteStringSet(szRes, szPrint, 0, 2);
    printt("\n%02X%02X : %02X%02X : \t\tRFU\n", pabRes1[0], pabRes1[1], pabRes2[0], pabRes2[1]);
    // 3   4	File size
    //GetByteStringSet(szRes, szPrint, 2, 2);
    printt("%02X%02X : %02X%02X : \t\tFile size\n", pabRes1[2], pabRes1[3], pabRes2[2], pabRes2[3]);
    // 5   6	File ID	2
    //GetByteStringSet(szRes, szPrint, 4, 2);
    printt("%02X%02X : %02X%02X: \t\tFile Id\n", pabRes1[4], pabRes1[5], pabRes2[4], pabRes2[5]);
    // 7	Type of file (see 9.3)
    //GetByteStringSet(szRes, szPrint, 6, 1);
    printt("%02X : %02X : \t\tType of file = ", pabRes1[6], pabRes2[6]);
    switch (pabRes1[6]) {
    case FILE_TYPE_MF: printt("MF\n"); break;
    case FILE_TYPE_DF: printt("DF\n"); break;
    case FILE_TYPE_EF: printt("EF\n"); break;
    default: printt("UNKNOWN\n");
    }
    // 8	see detail 3	1
    //Detail 3: Byte 8
	  //For transparent and linear fixed EFs this byte is RFU. For a cyclic EF all bits except bit 7 are RFU; b7=1 indicates that the INCREASE command is allowed on the selected cyclic file.
    // Get structure of EF
    //GetByteStringSet(szRes, szPrint, 13, 1);
    bTmp1 = pabRes1[13];
    // Get 
    //GetByteStringSet(szRes, szPrint, 7, 1);
    bTmp2 = pabRes1[7];
    if (bTmp1 = FILE_STRUCT_CYC) {
      if (0x80 & bTmp2) {
        printt("%02X : %02X : \t\tIncrease allowed\n", pabRes1[7], pabRes2[7]);
      }
      else {
        printt("%02X : %02X : \t\tIncrease NOT allowed\n", pabRes1[7], pabRes2[7]);
      }
    }
    else {
      printt("%02X : %02X : \t\tRFU\n", pabRes1[7], pabRes2[7]);
    }

    // 9   11	Access conditions (see 9.3)
    //GetByteStringSet(szRes, szPrint, 8, 3);
    printt("%02X%02X%02X : %02X%02X%02X : \t\tURS, RI, INRE access condition\n", 
      pabRes1[8], pabRes1[9], pabRes1[10], pabRes2[8], pabRes2[9], pabRes2[10]);

    // 12	File status (see 9.3)
    //GetByteStringSet(szRes, szPrint, 11, 1);
    bTmp1 = pabRes1[11];
    printt("%02X : %02X : \t\tFile status =", pabRes1[11], pabRes2[11]);
    if (bTmp1 & 0x01)  {
      printt(" Not invalidated");
    }
    else {
      printt(" Invalidated");
    }
    if (bTmp1 & 0x04) {
      printt(", readable and updatable when invalidated\n");
    }
    else {
      printt(", not readable and updatable when invalidated\n");
    }
    // 14	Structure of EF (see 9.3)	1
    //GetByteStringSet(szRes, szPrint, 12, 1);
    printt("%02X : %02X : Length of the following data (byte 14 to the end)\n", pabRes1[12], pabRes2[12]);
    // 14	Structure of EF (see 9.3)	1
    //GetByteStringSet(szRes, szPrint, 13, 1);
    bTmp1 = pabRes1[13];
    printt("%02X : %02X : \t\tStructure of EF = ", pabRes1[13], pabRes2[13]);
    switch (bTmp1) {
    case FILE_STRUCT_TRANSP:
      printt("Transparent\n");
      break;
    case FILE_STRUCT_LINFIX:
      printt("Linear fix\n");
      break;
    case FILE_STRUCT_CYC:
      printt("Cyclic\n");
      break;
    }
    // 15	Length of a record (see detail 4)	1
    //GetByteStringSet(szRes, szPrint, 14, 1);
    bTmp1  = pabRes1[14];
    if ((bTmp1 == FILE_STRUCT_LINFIX) || (bTmp1 == FILE_STRUCT_CYC)) {
      printt("%02X : %02X : \t\tLength of a record\n", pabRes1[14], pabRes2[14]);
    }
    else {
      printt("%02X : %02X : \t\tRFU\n", pabRes1[14], pabRes2[14]);
    }
    break;
#endif
  default:
    break;
  }

  return 0;
}

WORD PrintCompareResult(
    BYTE bCmd
  , BYTE *pabRes1
  , WORD wLen1
  , BYTE *pabRes2
  , WORD wLen2)
{
  WORD i;
  WORD wRet = 0;
  WORD wLen = wLen1 > wLen2 ? wLen2 : wLen1;
  if (wLen1 != wLen2) {
    printt("Different length %d != %d\n", wLen1, wLen2);
  }

  printt("    : ");
  for (i = 0; i < wLen1; i++) {
    printt("%02d ", i);
  }
  printt("\n");
  printt("Res1: ");
  for (i = 0; i < wLen1; i++) {
    printt("%02X ", pabRes1[i]);
  }
  printt("\n");
  printt("Res2: ");
  for (i = 0; i < wLen2; i++) {
    printt("%02X ", pabRes2[i]);
  }
  printt("\n");
  printt("    : ");
  for (i = 0; i < wLen; i++) {
    if (pabRes1[i] != pabRes2[i]) {
      printt("^^ ");
      wRet = 1;
    }
    else {
    printt("   ", pabRes2[i]);
    }
  }
  printt("\n");

  switch (bCmd)
  {
  case INS_GET_RESPONSE:
    //PrintCompareGetResponse(pabRes1, wLen1, pabRes2, wLen2);
    break;
  default:
    break;
  }

  if (g_iDebugBreak) {
    if (wLen1 == 2) {
      if (pabRes1[0] != pabRes2[0]) {
        // Incorrect SW1SW2
        if (g_iDebugBreak) {
        __debugbreak();
        }
      }
    }
    else {
      if (wRet == 1) {
        // Incorrect data
        __debugbreak();
        //longjmp(g_jmpSTART, 1);
      }
    }
  }
  
  return wRet;
}

static clock_t m_clockStart;
static clock_t m_clockEnd;

void ClockStart()
{
  m_clockStart = clock();
}

void ClockStop()
{
  double duration;
  m_clockEnd = clock();
  duration = (double)(m_clockEnd - m_clockStart) / CLOCKS_PER_SEC;
  printt("\n=====================================================================");
  printt("\n===> Elapsed time : %2.1f seconds", duration );
  printt("\n=====================================================================\n");
}