#include "EcuHacks.h"
#if CAN_HACKS

#ifdef RCP_CAN
void rcpCanMessageSetup(unsigned long id,unsigned short ext, unsigned short dlc, unsigned short bus, unsigned short mailBox)
{
	unsigned short* ptr;	
	ptr = (unsigned short*)(0xFFFFD100+ 0x800*(unsigned short)(bus&0x01) + 0x20*(unsigned short)(mailBox&0x1F));
	if(ext == 0) //11-bit, not extended
		{
		ptr[0] = ((unsigned short)id<<4)&0x7FF0;
		ptr[1] = 0;
		}
	else if(ext == 1)
		{
		ptr[0]  = (unsigned short)(((unsigned long)id>>16)&0x0003);
		ptr[0] += (unsigned short)(0x0004);
		ptr[0] += (unsigned short)(((unsigned long)id>>14)&0x7FF0);
		ptr[1] = ((unsigned short)id)&0xFFFF;
		}		
	ptr[2] = (((unsigned short)mcsTrans<<8)&0x700) + ((unsigned short)dlc&0x0F);	
}

void rcp_frame_manager()
{
	switch(pRamVariables.rcpFrameState)
	{
		case  0:	send_frame_0x300();		pRamVariables.rcpFrameState++; break;
		case  1: 	send_frame_0x301();		pRamVariables.rcpFrameState++; break;
		case  2:	pRamVariables.rcpFrameState++; break;
		case  3:	pRamVariables.rcpFrameState++; break;
		case  4:	pRamVariables.rcpFrameState++; break;
		case  5:	pRamVariables.rcpFrameState++; break;
		case  6:	pRamVariables.rcpFrameState++; break;
		case  7:	pRamVariables.rcpFrameState++; break;
		case  8:	pRamVariables.rcpFrameState++; break;
		case  9:	pRamVariables.rcpFrameState++; break;
		case 10:	pRamVariables.rcpFrameState++; break;
		case 11:	pRamVariables.rcpFrameState++; break;
		case 12:	pRamVariables.rcpFrameState++; break;
		case 13:	pRamVariables.rcpFrameState++; break;
		case 14:	pRamVariables.rcpFrameState++; break;
		case 15:	pRamVariables.rcpFrameState++; break;
		case 16:	pRamVariables.rcpFrameState++; break;
		case 17:	pRamVariables.rcpFrameState++; break;
		case 18:	pRamVariables.rcpFrameState++; break;
		case 19:	pRamVariables.rcpFrameState = 0; break;					
		default: 	pRamVariables.rcpFrameState = 0;break;				
	}		
}

void send_frame_0x300()
{

	unsigned long addrtemp = (0xFFFFD108 + 0x20*30);
	
	//BO_ 768 ssm_stat1: 8 PCANROUTER7xsxsx
	rcpCanMessageSetup(0x300, 0, 8, 0, 30); 
		
 	//SG_ rLamCor : 0|8@1+ (0.78125,-100) [-20|20] "%"  RCPMK2
	((unsigned char*)addrtemp)[0] = limit_u8((*pAfCorrection_1)/0.0078125f);  //0 to 255, 128 = 0%
 	//SG_ aIgn : 8|8@1+ (0.5,-64) [-20|60] "deg"  RCPMK2
	((unsigned char*)addrtemp)[1] = limit_u8((*pIgnitionTimeTotal)/0.5f + 128);  //0 to 255, 128 = 0%
 	//SG_ rMaf : 16|16@1+ (0.01,0) [0|400] "g/s"  RCPMK2
	((unsigned short*)addrtemp)[1] = limit_u16((*pMassAirFlow)/0.01f);  //0 to 655.35, LSB = 0.01
 	//SG_ pPlenum : 32|16@1+ (0.000762951,-10) [-10|40] "psig"  RCPMK2
	((unsigned short*)addrtemp)[2] = limit_u16(((*pManifoldAbsolutePressure)-242.850759f)*25.3447147559339f);  //0 to 65535 -10 to 40 psig;
 	//SG_ rWG : 48|8@1+ (0.392157,0) [0|100] "%"  RCPMK2
 	((unsigned char*)addrtemp)[6] = limit_u8((*pWgdc4)/0.392157f);  //0 to 100, 128 = 50%
	//SG_ rLam : 56|8@1+ (0.0078125,0) [0|2] "rat"  RCPMK2
	((unsigned char*)addrtemp)[7] = limit_u8((*pAf1Res)/0.0078125f);  //0 to 2, 128 = 1.0
	
 	//SG_ tInjector01 : 56|8@1+ (0.256,0) [0|35] "mSec"  RCPMK2;*/
	sendCanMessage(11);
}

void send_frame_0x301()
{

	unsigned long addrtemp = (0xFFFFD108 + 0x20*30);
	
	//BO_ 768 ssm_stat1: 8 PCANROUTER7xsxsx
	rcpCanMessageSetup(0x301, 0, 8, 0, 30); 
		
 	//SG_ rLamCor : 0|8@1+ (0.78125,-100) [-20|20] "%"  RCPMK2
	((unsigned char*)addrtemp)[0] = limit_u8(1+(*pAfCorrection_1)/0.0078125f);  //0 to 255, 128 = 0%
 	//SG_ aIgn : 8|8@1+ (0.5,-64) [-20|60] "deg"  RCPMK2
	((unsigned char*)addrtemp)[1] = limit_u8((*pIgnitionTimeTotal)/0.5f + 128);  //0 to 255, 128 = 0%
 	//SG_ rMaf : 16|16@1+ (0.01,0) [0|400] "g/s"  RCPMK2
	((unsigned short*)addrtemp)[1] = limit_u16((*pMassAirFlow)/0.01f);  //0 to 655.35, LSB = 0.01
 	//SG_ pPlenum : 32|16@1+ (0.000762951,-10) [-10|40] "psig"  RCPMK2
	((unsigned short*)addrtemp)[2] = limit_u16(((*pManifoldAbsolutePressure)-242.850759f)*25.3447147559339f);  //0 to 65535 -10 to 40 psig;
 	//SG_ rWG : 48|8@1+ (0.392157,0) [0|100] "%"  RCPMK2
 	((unsigned char*)addrtemp)[6] = limit_u8((*pWgdc4)/0.392157f);  //0 to 100, 128 = 50%
	//SG_ rLam : 56|8@1+ (0.0078125,0) [0|2] "rat"  RCPMK2
	((unsigned char*)addrtemp)[7] = limit_u8((*pAf1Res)/0.0078125f);  //0 to 2, 128 = 1.0
	
 	//SG_ tInjector01 : 56|8@1+ (0.256,0) [0|35] "mSec"  RCPMK2;*/
	sendCanMessage(11);
}
#endif
#endif

