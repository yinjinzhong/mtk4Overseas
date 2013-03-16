#pragma once

#ifndef __TDA7419_DATA_H__
#define __TDA7419_DATA_H__

#ifdef __cplusplus
extern "C"
{
#endif

	BYTE TDA7419_Para[18];
	BYTE TDA7741_Init_Data[18]={ 
		0x8f,//Main Selector 默认dvd通道
		0x00,//Main Loudness
		0x00|0x00|0x00|0x02|0x00,//Soft Mute/Clock Generator//xxxxxx
		//0x80|0x70|0x0C|0x00|0x01,//Soft Mute/Clock Generator
		
        //0xff,
		0x7F,//Volume
		0xa0,//Treble
		0xC0,//Middle
		0x80,//Bass
		//0x05,
		0x7d,//Second Source Selector
		0xFC,//Subwoofer/Middle/Bass
		0xF7,//Mixing/Gain Effect
		0x00,//Speaker Attenuator LF
		0x00,//Speaker Attenuator RF
		0x00,//Speaker Attenuator LR
		0x00,//Speaker Attenuator RR
		0x00,//Mixing Level Control
		0x00,//Subwoofer Attenuator
		0x1c,//Spectrum Analyzer / Clock Source / AC Mode
		0x00//Testing Audio Processor
		//0x81,0x00,0xfd,0x80,0x80,0xC0,0x80,0x01,0xFC,0xff,0x80,0x80,0x80,0x80,0x80,0x80,0x1c,0x00
	};

//	const BYTE VolumeMask[65] = {//0~60(-59~0)转(0~59)
//		0x7F,//MUTE
//		/*0x50,0x4f,0x4e,0x4d,0x4c,*/
//		0x4b,0x4a,0x49,0x48,/*0x47,*/0x46,0x45,0x44,0x43,//0x42,//1~10
//		0x41,0x40,0x3f,0x3e,/*0x3D,*/0x3C,0x3B,0x3A,0x39,//0x38,//11~20
//		0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30,0x2f,//0x2e,//21~30
//		0x2d,0x2c,0x2b,0x2a,/*0x29,*/0x28,0x27,0x26,0x25,//0x24,//31~40
//		0x23,0x22,0x21,0x20,0x1f,0x1e,0x1d,0x1c,0x1b,//0x1a,//41~50
//		0x19,0x18,0x17,0x16,/*0x15,*/0x14,0x13,0x12,0x11,//0x10,//51~60
//		0x00,/*0x01,*/0x02,/*0x03,*/0x04,0x05,
//		0x06,0x07,0x08,0x09,0x0a,
//		0x0b,0x0c,0x0d,0x0e,0x0f
//	};


	const BYTE VolumeMask[65] = {//0~60(-59~0)转(0~59)
		0x7F,//MUTE
		0x43,0x42,//1~10
		0x41,0x40,0x3f,0x3e,0x3D,0x3C,0x3B,0x3A,0x39,0x38,//11~20
		0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30,0x2f,0x2e,//21~30
		0x2d,0x2c,0x2b,0x2a,0x29,0x28,0x27,0x26,0x25,0x24,//31~40
		0x23,0x22,0x21,0x20,0x1f,0x1e,0x1d,0x1c,0x1b,0x1a,//41~50
		0x19,0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x11,0x10,//51~60
		0x00,0x01,0x02,0x03,0x04,0x05,
		0x06,0x07,0x08,0x09,0x0a,
		0x0b
	};

	/*const BYTE VolumeMask_Mix[71] = {//0~60(-59~0)转(0~59)
		0x7F,//MUTE
		0x7F,0x7F,0x7F,//0x3e,0x3D,0x3C,0x3B,0x3A,0x39,//0x38,//11~20
		0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30,0x2f,//0x2e,//21~30
		0x2d,0x2c,0x2b,0x2a,0x29,0x28,0x27,0x26,0x25,//0x24,//31~40
		0x23,0x22,0x21,0x20,0x1f,0x1e,0x1d,0x1c,0x1b,//0x1a,//41~50
		0x19,0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x11,//0x10,//51~60
		0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,

		0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x0f,0x0f,
		0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f
	};*/

		const BYTE VolumeMask_Mix[65] = {//0~60(-59~0)转(0~59)
		0x7F,//MUTE
		0x3A,0x39,0x38,0x37,0x36,0x35,0x34,0x33,//01~10
		0x32,0x31,0x30,0x2f,0x2e,0x2d,0x2c,0x2b,0x2a,0x29,//11~20
		0x28,0x27,0x26,0x25,0x24,0x23,0x22,0x21,0x20,0x1f,//21~30
		0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18,0x17,0x16,0x15,//31~40
		0x14,0x13,0x12,0x11,0x10,0x00,0x01,0x02,0x03,0x04,//41~50
		0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0f,//51~60
		0x0f,0x0f,0x0f,0xf,0xf

	};
	const BYTE Treble_Middle_Bass_Mask_Normal[11] = { //0~10中间值5
		0x0F,
		//			0x0E,
		//			0x0D,
		0x0C,
		//			0x0B,
		//			0x0A,
		0x09,
		//			0x08,
		//			0x07,
		0x06,
		//			0x05,
		//			0x04,
		0x03,
		//			0x02,
		//			0x01,
		0x00,
		//			0x10,
		//			0x11,
		//			0x12,
		0x12,
		//			0x14,
		//			0x15,
		0x16,
		//			0x17,
		//			0x18,
		0x16,     //0x19,
		//			0x1A,
		//			0x1B,
		0x16,     //0x1C,
		//			0x1D,
		//			0x1E,
		0x16
	};

	const BYTE Treble_Middle_Bass_Mask_Radio_Tre[11] = { //0~10中间值5
		0x0F,
					0x0E,
					0x0D,
		0x0C,
					0x0B,
					0x0A,
		0x09,
					0x08,
					0x07,
		0x06,
					0x05,
		//			0x04,
		//0x03,
		////			0x02,
		////			0x01,
		//0x00,
		////			0x10,
		////			0x11,
		////			0x12,
		//0x12,
		////			0x14,
		////			0x15,
		//0x16,
		////			0x17,
		////			0x18,
		//0x16,     //0x19,
		////			0x1A,
		////			0x1B,
		//0x16,     //0x1C,
		////			0x1D,
		////			0x1E,
		//0x16
	};

	const BYTE Treble_Middle_Bass_Mask_Radio_Mid[11] = { //0~10中间值5
		0x0F,
		//			0x0E,
		//			0x0D,
		0x0C,
		//			0x0B,
		//			0x0A,
		0x09,
		//			0x08,
		//			0x07,
		0x06,
		//			0x05,
		//			0x04,
		0x03,
		//			0x02,
		//			0x01,
		0x00,
		//			0x10,
		//			0x11,
		//			0x12,
		0x12,
		//			0x14,
		//			0x15,
		0x16,
		//			0x17,
		//			0x18,
		0x16,     //0x19,
		//			0x1A,
		//			0x1B,
		0x16,     //0x1C,
		//			0x1D,
		//			0x1E,
		0x16
	};

	const BYTE Treble_Middle_Bass_Mask_Radio_Bass[11] = { //0~10中间值5
		0x0F,
		//			0x0E,
		//			0x0D,
		0x0C,
		//			0x0B,
		//			0x0A,
		0x09,
		//			0x08,
		//			0x07,
		0x06,
		//			0x05,
		//			0x04,
		0x03,
		//			0x02,
		//			0x01,
		0x00,
		//			0x10,
		//			0x11,
		//			0x12,
		0x12,
		//			0x14,
		//			0x15,
		0x16,
		//			0x17,
		//			0x18,
		0x16,     //0x19,
		//			0x1A,
		//			0x1B,
		0x16,     //0x1C,
		//			0x1D,
		//			0x1E,
		0x16
	};

	const BYTE Loud_Mask[11] =
	{
		0x0,
		0x1,
		//0x2,
		0x3,
		0x4,
		//	0x5,
		0x6,
		0x7,
		//	0x8,
		0x9,
		0xa,
		//	0xb,
		0xc,
		0xd,
		0xe,
		//	0xf	
	};

	const BYTE Balance_Fader_Mask[11] = {//
		//0x10,0x18,0x20,0x28,0x30,0x38,0x40,0x48,0x50,0x58,0x60

		0x10,0x14,0x18,0x1B,0x1F,0x24,0x28,0x2B,0x2F,0x32,0x7F

	/*	0x10,0x12,0x14,0x16,0x18,
		0x1A,0x1C,0x1E,0x20,0x22,
		0x7F*/
	};
	//enum audio_source{Init=0,MediaCD,CDC,RADIO,AUX,IPOD,TV,MediaMP3,SRADIO,BT,EXT_TEL,GR_AUDIO,BACK,GPS};
	const BYTE audioChannelGainTab[17]={//0~16
		0,//Init
		0,//MediaCD
		0,//CDC
		3,//RADIO
		1,//AUX
		1,//IPOD
		4,//TV
		1,//MediaMP3
		1,//SRADIO
		1,//A2DP
		0,//EXT_TEL
		0,//GR_AUDIO
		6,//BT
		0,//BACK
		0,//GPS
		0,
		0};







#ifdef __cplusplus
}
#endif

#endif// __TDA7419_DATA_H__
