/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008 MediaTek Inc.
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*******************************************************************************
*
* Filename:
* ---------
* file MSDK_AVIN.h
*
* Project:
* --------
*   CNB
*
* Description:
* ------------
*
*
* Author:
* -------
*
*
*------------------------------------------------------------------------------
* $Revision: #2 $
* $Modtime:$
* $Log:$
*
*******************************************************************************/

#ifndef _MSDK_AVIN_H_
#define _MSDK_AVIN_H_

#include <MSDK_Defs.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    MSDK_AVIN_FLIP_NONE,
	MSDK_AVIN_FLIP_H,
	MSDK_AVIN_FLIP_V,
	MSDK_AVIN_FLIP_HnV
} MSDK_AVIN_MIRROR_E;

typedef enum
{
    MSDK_AVIN_SIGNAL_PAL=1,
    MSDK_AVIN_SIGNAL_NTSC,
    MSDK_AVIN_SIGNAL_SECAM,
    MSDK_AVIN_SIGNAL_UNSTABLE,
    MSDK_AVIN_SIGNAL_NONE,
}MSDK_AVIN_SIGNAL_MODE_T;

MRESULT     AvinCtrl_SetHue(HMEDIAGRAPH hMediaGraph, GUINT32 u4Hue);
MRESULT     AvinCtrl_SetBrightness(HMEDIAGRAPH hMediaGraph, GUINT32 u4Brightness);
MRESULT     AvinCtrl_SetSaturation(HMEDIAGRAPH hMediaGraph, GUINT32 u4Saturation);
MRESULT     AvinCtrl_SetMirror(HMEDIAGRAPH hMediaGraph, MSDK_AVIN_MIRROR_E eMirror);
MRESULT AvinInfo_GetSignalMode(HMEDIAGRAPH hMediaGraph,MSDK_AVIN_SIGNAL_MODE_T *eSignalMode);




#ifdef __cplusplus
}
#endif

#endif //_MSDK_AVIN_H_

