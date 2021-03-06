/************************************************************************/
/* FLYAUDIO SAF7541                                                     */
/************************************************************************/
#pragma once

#ifndef _FLYAUDIO_SAF7541_RADIO_H_
#define _FLYAUDIO_SAF7541_RADIO_H_

#include <windows.h>
#include <basetsd.h>
#include "flyshmlib.h"
#include "flygpio.h"

#if !SOFT_VERSION_FOR_OVERSEAS
#error "This software version is for china!!!"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define NORMAL_I2C_FREQ		100000  

#define RADIO_RDS 1
#define RADIO_RDS_DEBUG_MSG 0

#define RADIO_RDS_DISPLAY_DEBUG	0

#define RADIORDS_ID_TA				0x30
#define RADIORDS_ID_PS				0x21
#define RADIORDS_ID_RT				0x22
#define RADIORDS_ID_PTY				0x23

#define GROUP_A     0
#define GROUP_B     1

#define TDA7541_ID					0x03

#define TDA7541_ADDR_R				0xC5
#define TDA7541_ADDR_W				0xC4
#define AUTO_INCREMENT_MODE			0x20

#define EEPROM_ADDR_R				0xA1
#define EEPROM_ADDR_W				0xA0

//#define EEPROM_ADDR_R				0xC5
//#define EEPROM_ADDR_W				0xC4

#define IO_SSTOP_IN
#define FM_SUM						141
#define AM_SUM						142
#define AN_SUM						143
#define INIT_DATA_SIZE				144

#define TUNER_SEEK_MUTE_CTROL_ADDR0_0			0,0
#define TUNER_PARA_AREA_ADDR0_23				0,23
#define TUNER_TESTING_CTROL_ADDR24_31			24,31


#define	TDA7541_ADDR0_REG			0,0
#define	TDA7541_ADDR1_REG			1,1
#define	TDA7541_ADDR2_REG			2,2
#define	TDA7541_ADDR3_REG			3,3
#define	TDA7541_ADDR4_REG			4,4
#define	TDA7541_ADDR5_REG			5,5
#define	TDA7541_ADDR10_REG			10,10
#define	TDA7541_ADDR11_REG			11,11
#define	TDA7541_ADDR13_REG			13,13
#define	TDA7541_ADDR14_REG			14,14
#define	TDA7541_ADDR15_REG			15,15
#define	TDA7541_ADDR16_REG			16,16
#define	TDA7541_ADDR17_REG			17,17
#define	TDA7541_ADDR18_REG			18,18
#define	TDA7541_ADDR19_REG			19,19
#define	TDA7541_ADDR25_REG			25,25

#define FM_REG_OFFSET		10
#define AM_REG_OFFSET		34
#define OIRT_EU_ANUM		58
#define JPN_ANUM			59
#define EU_FREQ_OFFSET		60
#define OIRT_FREQ_OFFSET	68
#define JAPAN_FREQ_OFFSET	76
#define EU_TV_OFFSET		84
#define OIRT_TV_OFFSET		92
#define JAPAN_TV_OFFSET		100
#define EU_SM_OFFSET		108
#define OIRT_SM_OFFSET		116
#define JAPAN_SM_OFFSET     124
#define OIRT_IQ_OFFESET		132
#define OIRT_TVOP			134
#define OIRT_SEP			135

#define TV					0
#define SMETER				1
#define IF 					10700

//====================================================//
//================ TDA7541 register bit define========//
//====================================================//
//For Tun_Buff[0]
//Bit2~0
#define TDA7541_ADDR0_REG_ICP					0,2
#define TDA7541_PLL_HICURRENT_0MA       		0x00
#define TDA7541_PLL_HICURRENT_0_5mA     		0x01
#define TDA7541_PLL_HICURRENT_1MA       		0x02
#define TDA7541_PLL_HICURRENT_1_5mA     		0x03
#define TDA7541_PLL_HICURRENT_2MA       		0x04
#define TDA7541_PLL_HICURRENT_2_5mA     		0x05
#define TDA7541_PLL_HICURRENT_3MA       		0x06
#define TDA7541_PLL_HICURRENT_3_5mA     		0x07
//Bit3
#define TDA7541_ADDR0_REG_LDENA					3,3
#define TDA7541_PLL_LOCK_DISABLE				0x00
#define TDA7541_PLL_LOCK_ENABLE					0x08
//Bit4
#define TDA7541_ADDR0_REG_SDM					4,4
#define TDA7541_STEREO_MUTE_DISABLE				0x00
#define TDA7541_STEREO_MUTE_ENABLE				0x10
//Bit5
#define TDA7541_ADDR0_REG_LM					5,5
#define TDA7541_LOCAL_DISABLE					0x00
#define TDA7541_LOCAL_ENABLE					0x20
//Bit6
#define TDA7541_ADDR0_REG_ASFC					6,6
#define TDA7541_ASFC_NORMAL						0x00//weak signal mute and AGC normal mode in FM
#define TDA7541_ASFC_HOLD						0x40//weak signal mute and AGC on hold in FM
//Bit7
#define TDA7541_ADDR0_REG_SEEK					7,7
#define TDA7541_SEEK_OFF						0x00
#define TDA7541_SEEK_ON							0x80

//TPLL COUNTER1 LSB Tun_Buff[1]	 VALUE = 0~255
#define TDA7541_ADDR1_REG_PC_LSB				0,7
//TPLL COUNTER1 MSB Tun_Buff[2]	 VALUE = 0~255
#define TDA7541_ADDR2_REG_PC_MSB				0,7
//TV Tun_Buff[3]
#define TDA7541_ADDR3_REG_TV					0,7

//Sample time and IFC   Tun_Buff[4]
//Bit0
#define TDA7541_ADDR4_REG_TVM					0,0
#define TDA7541_PLL_TV_TRACK					0x00
#define TDA7541_PLL_TV_INDEPEDENT				0x01
//Bit1
#define TDA7541_ADDR4_REG_TVO					1,1
#define TDA7541_PLL_TVOFFSET_DISABLE			0x00
#define TDA7541_PLL_TVOFFSET_ENABLE				0x02
//Bit2
#define TDA7541_ADDR4_REG_ISSENA				2,2
#define TDA7541_ISS_ENABLE                      0x04
#define TDA7541_ISS_DISABLE                     0x00
//Bit4~3  与ADDR25_d6 组合
#define TDA7541_ADDR4_REG_IFS					3,4
#define TDA7541_PLL_TSAMPLE_FM20_48_AM128		0x00
#define TDA7541_PLL_TSAMPLE_FM10_24_AM64		0x08
#define TDA7541_PLL_TSAMPLE_FM5_12_AM32			0x10
#define TDA7541_PLL_TSAMPLE_FM2_56_AM16			0x18
//---expand mode for sampling time
#define TDA7541_PLL_TSAMPLE_FM1_28_AM8			0x00
#define TDA7541_PLL_TSAMPLE_FM0_64_AM4			0x08
#define TDA7541_PLL_TSAMPLE_FM0_32_AM2			0x10
#define TDA7541_PLL_TSAMPLE_FM0_16_AM1			0x18

//Bit6~5 与ADDR25_d7 组合
#define TDA7541_ADDR4_REG_EW					5,6
#define TDA7541_PLL_IFC_EW_FM12_5_AM2K			0x00
#define TDA7541_PLL_IFC_EW_FM25_AM4K			0x20
#define TDA7541_PLL_IFC_EW_FM50_AM8K			0x40
#define TDA7541_PLL_IFC_EW_FM100_AM16K			0x60
//---expand mode for error window
#define TDA7541_PLL_IFC_EW_FM6_25_AM1K			0x60
//Bit7
#define TDA7541_ADDR4_REG_FMON					7,7
#define TDA7541_AMMODE							0x00
#define TDA7541_FMMODE							0x80


//VCO & Pll reference freqency Tun_Buff[5]
//Bit1~0
#define TDA7541_ADDR5_REG_VCOD					0,1
#define TDA7541_VCO_DIVIDER_NOTVALID			0x00
#define TDA7541_VCO_DIVIDER_2					0x01
#define TDA7541_VCO_DIVIDER_3					0x02
#define TDA7541_VCO_DIVIDER_ORIGINAL			0x03
//Bit2
#define TDA7541_ADDR5_REG_VCOI					2,2
#define TDA7541_VCO_PHASE_0						0x00
#define TDA7541_VCO_PHASE_180					0x04
//Bit5~3
#define TDA7541_ADDR5_REG_RC					3,5
#define TDA7541_PLL_REFERECE_2KHz				0x18
#define TDA7541_PLL_REFERECE_9KHz				0x20
#define TDA7541_PLL_REFERECE_10KHz				0x28
#define TDA7541_PLL_REFERECE_25KHz				0x30
#define TDA7541_PLL_REFERECE_50KHz				0x38
//Bit7~6
#define TDA7541_ADDR5_REG_AMD					6,7
#define TDA7541_AM_PREDIVIDER_10				0x00
#define TDA7541_AM_PREDIVIDER_8					0x40
#define TDA7541_AM_PREDIVIDER_6					0x80
#define TDA7541_AM_PREDIVIDER_4					0xc0

//For SSTOP threshold Tun_Buff[10]
//Bit0~1
#define TDA7541_ADDR10_REG_MUX					0,1
 
//Bit4~7
#define TDA7541_ADDR10_REG_SSTH					4,7
#define TDA7541_SSTOP_IFC						0x00
#define TDA7541_SSTOP_IFC_FM0_5_AM1_1			0x10
#define TDA7541_SSTOP_IFC_FM0_7_AM1_4			0x20
#define TDA7541_SSTOP_IFC_FM0_9_AM1_7			0x30
#define TDA7541_SSTOP_IFC_FM1_1_AM2_0			0x40
#define TDA7541_SSTOP_IFC_FM1_3_AM2_3			0x50
#define TDA7541_SSTOP_IFC_FM1_5_AM2_6			0x60
#define TDA7541_SSTOP_IFC_FM1_7_AM2_9			0x70
#define TDA7541_SSTOP_IFC_FM1_9_AM3_2			0x80
#define TDA7541_SSTOP_IFC_FM2_1_AM3_5			0x90
#define TDA7541_SSTOP_IFC_FM2_3_AM3_8			0xA0
#define TDA7541_SSTOP_IFC_FM2_5_AM4_1			0xB0
#define TDA7541_SSTOP_IFC_FM2_7_AM4_4			0xC0
#define TDA7541_SSTOP_IFC_FM2_9_AM4_7			0xD0
#define TDA7541_SSTOP_IFC_FM3_1_AM5_0			0xE0
#define TDA7541_SSTOP_IFC_FM3_2_AM5_3			0xF0

//Tun_Buff[11]
#define TDA7541_ADDR11_WNON						1,1
#define TDA7541_WB_DISABLE						0x00
#define TDA7541_WB_ENABLE						0x02
#define TDA7541_ADDR11_WMTH                     2,4
#define TDA7541_WMTH_STARTMUTE_0                0X00
#define TDA7541_WMTH_STARTMUTE_1                0X04
#define TDA7541_WMTH_STARTMUTE_2                0X08
#define TDA7541_WMTH_STARTMUTE_3                0X0C
#define TDA7541_WMTH_STARTMUTE_4                0X10
#define TDA7541_WMTH_STARTMUTE_5                0X14
#define TDA7541_WMTH_STARTMUTE_6                0X18
#define TDA7541_WMTH_STARTMUTE_7                0X1C

//Tun_Buff[13]
#define TDA7541_ADDR13_REG_XTAL					    0,4
#define TDA7541_XTAL_24_75PF                        0x11
//Bit7~5
#define TDA7541_ADDR13_REG_SMETER					5,7
#define TDA7541_REG_SMETER_SLOPE_090V_20DB			0x00
#define TDA7541_REG_SMETER_SLOPE_095V_20DB			0x20
#define TDA7541_REG_SMETER_SLOPE_100V_20DB			0x40
#define TDA7541_REG_SMETER_SLOPE_105V_20DB			0x60
#define TDA7541_REG_SMETER_SLOPE_110V_20DB			0x80
#define TDA7541_REG_SMETER_SLOPE_115V_20DB			0xA0
#define TDA7541_REG_SMETER_SLOPE_120V_20DB			0xC0
#define TDA7541_REG_SMETER_SLOPE_125V_20DB			0xE0

//Tun_Buff[14]
//Bit3~0
#define  TDA7541_ADDR14_IF2A                    0,3
#define  TDA7541_IF2A_22PF                      0x0A
#define  TDA7541_IF2A_30_8PF                    0x0E
//Bit5~4
#define TDA7541_ADDR14_IF2Q						4,5
#define TDA7541_IF2Q_NOR_AMQ28_FMQ28			0x00
#define TDA7541_IF2Q_R5k_FMQ3					0x10
#define TDA7541_IF2Q_R4_1k_FMQ2_5				0x20
#define TDA7541_IF2Q_R3_3k_FMQ2_05				0x30
//Bit7~6
#define TDA7541_ADDR14_IF1G						6,7
#define TDA7541_IF2_GAIN_9						0x00
#define TDA7541_IF2_GAIN_12						0x40
#define TDA7541_IF2_GAIN_17						0x80
#define TDA7541_IF2_GAIN_21						0xC0

//Tun_Buff[15]
//Bit3~0
#define TDA7541_ADDR15_PH                       0,3
#define TDA7541_PH_3_DEGREE                     0x0A
//Bit7~4
#define	TDA7541_ADDR15_ORT_IQ					4,7

//Tun_Buff[18]
//Bit2~0
#define TDA7541_ADDR18_SBC						0,2
#define TDA7541_SBC_29_PERSENT					0x00
#define TDA7541_SBC_33_PERSENT					0x01
#define TDA7541_SBC_38_PERSENT					0x02
#define TDA7541_SBC_42_PERSENT					0x03
#define TDA7541_SBC_46_PERSENT					0x04
#define TDA7541_SBC_50_PERSENT					0x05
#define TDA7541_SBC_54_PERSENT					0x06
#define TDA7541_SBC_58_PERSENT					0x07


//Tun_Buff[19]
//Bit2~1---MAX_HIGH CUT
#define TDA7541_ADDR19_HIGH_CUT_MAX				1,2
#define TDA7541_HIGH_CUT_MAX_10DB				0x00
#define TDA7541_HIGH_CUT_MAX_5_5DB				0x01
#define TDA7541_HIGH_CUT_MAX_7_5DB				0x02
#define TDA7541_HIGH_CUT_MAX_8_5DB				0x03

// Bit7---DEEMP
#define TDA7541_ADDR19_DEEMP					7,7
#define TDA7541_DEEMP_50US						0x00
#define TDA7541_DEEMP_75US						0x80

//Tun_Buff[20]
//Bit6---MP FAST
#define TDA7541_ADDR20_MPFAST					6,6
#define TDA7541_MPTC_ENABLE						0x00
#define TDA7541_MPTC_DISABLE					0x40

//Tun_Buff[23]
//Bit5
#define TDA7541_ADDR23_VCON						5,5
#define TDA7541_STD_VCO_OFF						0x00
#define TDA7541_STD_VCO_ON						0x20

//Tun_Buff[25]
//Bit4
#define TDA7541_ADDR25_44						4,4


//#define 	EU			0
//#define		USA_WB		1
//#define 	OIRT		2
//#define 	JAPAN		3
//#define		SAM			4
enum enumRadioMode{FM1=0,FM2,AM};
enum enumRadioArea{AREA_EU=0,AREA_USA_WB,AREA_OIRT,AREA_JAPAN,AREA_SAM};
enum enumRadioStepDirection{STEP_BACKWARD=0,STEP_FORWARD,STEP_NONE};
enum enumRadioStepMode{STEP_MANUAL=0,STEP_SCAN};

#define DATA_BUFF_LENGTH	1024

typedef struct _FLY_RADIO_INFO
{
	UINT iFreqFMMin;
	UINT iFreqFMMax;
	UINT iFreqFMManualStep;
	UINT iFreqFMScanStep;

	UINT iFreqAMMin;
	UINT iFreqAMMax;
	UINT iFreqAMManualStep;
	UINT iFreqAMScanStep;

	enumRadioMode ePreRadioMode;
	enumRadioMode eCurRadioMode;
	enumRadioArea ePreRadioArea;
	enumRadioArea eCurRadioArea;
	UINT iPreRadioFreqFM1;
	UINT iCurRadioFreqFM1;
	UINT iPreRadioFreqFM2;
	UINT iCurRadioFreqFM2;
	UINT iPreRadioFreqAM;
	UINT iCurRadioFreqAM;

	UINT *pPreRadioFreq;
	UINT *pCurRadioFreq;

	BOOL bPreScaning;
	BOOL bCurScaning;
	enumRadioStepDirection eScanDirection;
	BOOL bScanRepeatFlag;

	BOOL bPreStepButtomDown;
	//BOOL bCurStepButtomDown;
	enumRadioStepDirection eButtomStepDirection;
	UINT iButtomStepCount;
}FLY_RADIO_INFO, *P_FLY_RADIO_INFO;

typedef struct _FLY_RDS_INFO
{
	BOOL RadioRDSAFControlOn;
	BOOL RadioRDSTAControlOn;

	UINT16 BaseReferencePI;
	UINT16 rdsdec_flag_recv[2];// 表示 正在播出的节目的GROUP 标志位 比如节目发了 0A 和 3B 组 此时rdsdec_flag_recv[0]的第一位置1 rdsdec_flag_recv[1]的第四位置1 		
	UINT16 rdsdec_flag_pi;	 //Programme Identification 每个节目只有唯一的PI 前四位是 地区编码
	//B15-B12	Country code
	//B11-B8	Programme type in terms of area coverage
	//B7-B0		Programme reference number
	BYTE  rdsdec_flag_pty; //0表示none，节目类型
	BYTE  rdsdec_flag_tp;	  //0表示没有携带，Traffic Programme (TP) Flag	 表示 节目带有 交通信息
	BYTE  rdsdec_flag_ms;	  //0语言类，1音乐类， music/speech 表示正在播出的节目是 音乐还是语音节目
	BYTE  rdsdec_flag_di[4];	 //	  Decoder Identification 解码标志位 暂时没有用到
	BYTE  rdsdec_flag_ta;	  //0表示无， Traffic Announcement (TP) Flag //TP 和 TA 同时为 1，表示Traffic report in progress on this service，此时关掉其他动作 听此报告

	BYTE  rdsdec_flag_eon;  //0表示无，表示有无Enhanced Other Networks (EON) 节目 暂时没有 做深入解码
	/* DEF_SUPPORT_0 */
	UINT16   rds_ecc;	    // Extended Country Code  根据它确定 某个国家 因为PI的前四位 可能是一些国家共用的
	UINT16   rds_language_code;	  //语言编码

	/* DEF_SUPPORT_0 */
	BYTE rdsdec_ps[2][8];   //Programme Service (PS) Name  节目名字
	BYTE rdsdec_ps_dis[8];
	//其实只有一组有效，当改变时往另一数组写数
	BYTE rdsdec_af[8];      //Alternative Frequency List—AF
	/* DEF_SUPPORT_2 */
	BYTE rdsdec_rt_a[2][64]; //RadioText (RT) 这是 GROUP_A的 TEXT_A 和 TEXT_B
	BYTE rdsdec_rt_a_dis[64];
	//其实只有一组有效，当改变时往另一数组写数
	BYTE rdsdec_rt_b[32]; // for Decode RadioText (RT) 这是 GROUP_B的 TEXT_A 和 TEXT_B
	//其实只有一组有效，当改变时往另一数组写数

	/* DEF_SUPPORT_4 */	   //以下是 RDS 的时间 校正
	UINT16 rds_clock_year;
	BYTE  rds_clock_month;
	BYTE  rds_clock_day;
	BYTE  rds_clock_wd; // weekday 1~7
	BYTE  rds_clock_hour;
	BYTE  rds_clock_min;
	BYTE  rds_clock_ofs;

	BYTE rdsdec_ptyn[2][8];   // for Decode 可编程的节目类型名
	//其实只有一组有效，当改变时往另一数组写数
}FLY_RDS_INFO, *P_FLY_RDS_INFO;

typedef struct _FLY_TDA7541_IO_INFO
{
	ULONG nowTimer;
	ULONG lastTimer;
	UINT iSSTOPDecCount;
}FLY_TDA7541_IO_INFO, *P_FLY_TDA7541_IO_INFO;

typedef struct _FLY_TDA7541_RADIO_INFO
{
	BOOL bOpen;
	BOOL bPowerUp;
	BOOL bPowerSpecialUp;

	BYTE buffToUser[DATA_BUFF_LENGTH];
	UINT buffToUserHx;
	UINT buffToUserLx;
	HANDLE hBuffToUserDataEvent;
	CRITICAL_SECTION hCSSendToUser;

	BOOL bPreMute;
	BOOL bCurMute;

	HANDLE hMsgQueueToRadioCreate;

	HANDLE	TDA7541RadioMainThreadHandle;
	BOOL bKillDispatchMainThread;
	HANDLE hDispatchMainThreadEvent;

	HANDLE	TDA7541RadioScanThreadHandle;
	BOOL bKillDispatchScanThread;
	HANDLE hDispatchScanThreadEvent;

	HANDLE	TDA7541RadioRDSRecThreadHandle;
	BOOL bKillDispatchRDSRecThread;

	HANDLE	TDA7541RadioI2CHandle;

	BYTE mParameterTable[INIT_DATA_SIZE];

	HANDLE hInterruptEventSSTOP;
	BOOL bInterruptEventSSTOPRunning;
	FLY_TDA7541_IO_INFO TDA7541_IO_info;

	FLY_RADIO_INFO radioInfo;
	FLY_RDS_INFO RDSInfo;

	//PFLY_DRIVER_GLOBAL pFlyDriverGlobalInfo;
	volatile shm_t *pFlyShmGlobalInfo;
	HANDLE hHandleGlobalGlobalEvent;
}FLY_TDA7541_RADIO_INFO, *P_FLY_TDA7541_RADIO_INFO;

#if RADIO_RDS
DWORD WINAPI TDA7541RadioRDSRecThread(LPVOID pContext);
void RDSParaInit(P_FLY_TDA7541_RADIO_INFO pTDA7541RadioInfo);
#endif


#define MSG_ENABLE_FLAG (pTDA7541RadioInfo->pFlyShmGlobalInfo->sFlyDriverGlobalInfo.FlySystemRunningInfo.bDebugMsgEnable)

#if (FLY_DEBUG_7541 && GLOBAL_DEBUG)
#define DBGE(string) RETAILMSG(1,string)//重要错误
#define DBGW(string) if (MSG_ENABLE_FLAG) RETAILMSG(1,string)//警告
#define DBGI(string) if (MSG_ENABLE_FLAG) RETAILMSG(1,string)//信息
#define DBGD(string) if (MSG_ENABLE_FLAG) RETAILMSG(1,string) //调试信息
#else
#define DBGE(string) RETAILMSG(1,string)//重要错误
#define DBGW(string) DEBUGMSG(1,string) //警告
#define DBGI(string) DEBUGMSG(1,string) //信息
#define DBGD(string) DEBUGMSG(1,string) //调试信息
#endif


#ifdef __cplusplus
}
#endif



#endif// _FLYAUDIO_SAF7541_H_