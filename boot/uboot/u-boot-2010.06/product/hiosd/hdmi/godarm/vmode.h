/***********************************************************************************/
/*  Copyright (c) 2002-2006, Silicon Image, Inc.  All rights reserved.             */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1060 East Arques Avenue, Sunnyvale, California 94085                           */
/***********************************************************************************/
#include "typedefs.h"
#include "timer.h"
//#include "optm_m_disp.h"
#include "hi_vo_wrap.h"

//                  Aspect ratio
#define _4     0  // 4:3
#define _4or16 1  // 4:3 or 16:9
#define _16    2  // 16:9

#define NSM    0 // no sub. mode

#define PC_BASE 60

#define NMODES 44+48

void GetVModeData(HI_U8, HI_U8 *);
HI_U8 VideoModeDetection(HI_U8 *);
void VMode_Handler(void);
HI_U16 GetPixelClock( HI_U8 );

//----------------------------------------------------------
typedef struct {
        HI_U8 FPixTMDS;
        HI_U16 Fs[3];
} PixPerSPDIFType;
//----------------------------------------------------------
typedef struct {
        HI_U16 FPixTMDS;
        HI_U32 Fs[7];

} NValType;
//----------------------------------------------------------

typedef struct {
   HI_U8 Mode_C1;
   HI_U8 Mode_C2;
   HI_U8 SubMode;
   HI_HDMI_VIDEO_FMT_E  enUNFFmt_C1;
   HI_HDMI_VIDEO_FMT_E  enUNFFmt_C2;
}ModeIdType;

typedef struct {
   HI_U16 Pixels;
   HI_U16 Lines;
} PxlLnTotalType;

typedef struct {
   HI_U16 H;
   HI_U16 V;
} HVPositionType;

typedef struct {
   HI_U16 H;
   HI_U16 V;
} HVResolutionType;

typedef struct{
   HI_U8 RefrTypeVHPol;
   HI_U16 VFreq;
   PxlLnTotalType Total;
} TagType;

typedef struct {
  HI_U8 IntAdjMode;
  HI_U16 HLength;
  HI_U16 VLength;
  HI_U16 Top;
  HI_U16 Dly;
  HI_U16 HBit2HSync;
  HI_U16 VBit2VSync;
  HI_U16 Field2Offset;

}  _656Type;

typedef struct {
   ModeIdType ModeId;
   HI_U16 PixClk;
   TagType Tag;
   HVPositionType Pos;
   HVResolutionType Res;
   HI_U8 AspectRatio;
   _656Type _656;
   HI_U8 PixRep;
} VModeInfoType;

typedef struct {
   HVPositionType HVPos;
   HVResolutionType HVRes;
} DEType;
//--------------------------------------------------------------------
typedef struct {

   HI_U16 CapHalfLineCnt;
   HI_U16 PreEqPulseCnt;
   HI_U16 SerratedCnt;
   HI_U16 PostEqPulseCnt;
   HI_U8 Field2BackPorch;

} InterlaceCSyncType;

extern const VModeInfoType VModeTables[NMODES];


