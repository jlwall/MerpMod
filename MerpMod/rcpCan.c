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
		case  0:	send_frame_0x700();		pRamVariables.rcpFrameState++; break;
		case  1:	pRamVariables.rcpFrameState++; break;
		case  2: 	send_frame_0x701();		pRamVariables.rcpFrameState++; break;
		case  3:	pRamVariables.rcpFrameState++; break;
		case  4:	send_frame_0x702();		pRamVariables.rcpFrameState++; break;
		case  5:	pRamVariables.rcpFrameState++; break;
		case  6:	send_frame_0x703();		pRamVariables.rcpFrameState++; break;
		case  7:	pRamVariables.rcpFrameState++; break;
		case  8:	send_frame_0x704();		pRamVariables.rcpFrameState++; break;
		case  9:	send_frame_0x705();		pRamVariables.rcpFrameState = 0; break;		
		default: 	pRamVariables.rcpFrameState = 0;break;				
	}		
}
#define RPCBUF 30
void send_frame_0x700()
{
	/*
	BO_ 1792 ecm_stat1: 8 ECM
 		SG_ rLamCor : 0|8@1+ (0.78125,-100) [-20|20] "%"  RCPMK2
 		SG_ aIgn : 8|8@1+ (0.5,-64) [-20|60] "deg"  RCPMK2
 		SG_ rMaf : 16|16@1+ (0.01,0) [0|400] "g/s"  RCPMK2
 		SG_ pPlenum : 32|16@1+ (0.000762951,-10) [-10|40] "psig"  RCPMK2
 		SG_ rWG : 48|8@1+ (0.392157,0) [0|100] "%"  RCPMK2
 		SG_ rLam : 56|8@1+ (0.0078125,0) [0|2] "rat"  RCPMK2
	*/
	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);	
	rcpCanMessageSetup(0x700, 0, 8, 0, RPCBUF); 		 	
	((unsigned char*)addrtemp)[0] = limit_u8((*pAfCorrection_1)/0.0078125f);
	((unsigned char*)addrtemp)[1] = limit_u8((*pIgnitionTimeTotal)/0.5f + 128);
	((unsigned short*)addrtemp)[1] = limit_u16((*pMassAirFlow)/0.01f);
	((unsigned short*)addrtemp)[2] = limit_u16(((*pManifoldAbsolutePressure)-242.850759f)*25.3447147559339f);
 	((unsigned char*)addrtemp)[6] = limit_u8((*pWgdc4)/0.392157f);
	((unsigned char*)addrtemp)[7] = limit_u8((*pAf1Res)/0.0078125f);
	sendCanMessage(11);
}

void send_frame_0x701()
{
	/*
	BO_ 1793 ecm_stat2: 8 ECM
 		SG_ iam : 0|8@1+ (0.0625,0) [0|0] ""  RCPMK2
 		SG_ aKnockFeed : 8|8@1+ (0.351563,-45) [0|0] ""  RCPMK2
 		SG_ aKnockFine : 16|8@1+ (0.351563,-45) [0|0] ""  RCPMK2
		SG_ CLOL : 24|8@1+ (1,0) [0|125] ""  RCPMK2
 		SG_ nRoughC1 : 32|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ nRoughC2 : 40|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ nRoughC3 : 48|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ nRoughC4 : 56|8@1+ (1,0) [0|255] ""  RCPMK2
 		
 	*/
	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);	
	rcpCanMessageSetup(0x701, 0, 8, 0, RPCBUF); 	
 	((unsigned char*)addrtemp)[0] = limit_u8((*pIam4)*16); 		
	((unsigned char*)addrtemp)[1] = *pFbkc1; 		
	((unsigned char*)addrtemp)[2] = *pkclearn1; 
	((unsigned char*)addrtemp)[3] = *pCLOL;			
	((unsigned char*)addrtemp)[4] = *pNRough_C1; 		
	((unsigned char*)addrtemp)[5] = *pNRough_C2; 		
	((unsigned char*)addrtemp)[6] = *pNRough_C3; 		
	((unsigned char*)addrtemp)[7] = *pNRough_C4; 		

	
	sendCanMessage(11);
}

void send_frame_0x702()
{
	/*
	BO_ 1794 ecm_stat3: 8 ECM
 		SG_ nKnockC1 : 0|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ nKnockC2 : 8|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ nKnockC3 : 16|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ nKnockC4 : 24|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ aCamInR : 32|8@1+ (1,-50) [-50|50] ""  RCPMK2
 		SG_ aCamInL : 40|8@1+ (1,-50) [-50|50] ""  RCPMK2
 		SG_ aCamExR : 48|8@1+ (1,-50) [-50|50] ""  RCPMK2
 		SG_ aCamExL : 56|8@1+ (1,-50) [-50|50] ""  RCPMK2
 	*/
	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);	
	rcpCanMessageSetup(0x702, 0, 8, 0, RPCBUF); 	 		
	((unsigned char*)addrtemp)[0] = *pKnockSum1; 	
	((unsigned char*)addrtemp)[1] = *pKnockSum2; 		
 	((unsigned char*)addrtemp)[2] = *pKnockSum3;		
	((unsigned char*)addrtemp)[3] = *pKnockSum4;	
 	((unsigned char*)addrtemp)[4] = *pAVCSIntakeRight;
 	((unsigned char*)addrtemp)[5] = *pAVCSIntakeLeft;
 	((unsigned char*)addrtemp)[6] = *pAVCSExhaustRight;
	((unsigned char*)addrtemp)[7] = *pAVCSExhaustLeft; 	
	sendCanMessage(11);
}

void send_frame_0x703()
{
	/*
	BO_ 1795 ecm_stat4: 8 PCANROUTER 		
 		SG_ pPlenumTarg : 0|16@1+ (0.000762951,-10) [-10|40] "psig" RCPMK2
		SG_ rBlendFuel : 16|8@1+ (0.3921568627,0) [0|100] "%"  RCPMK2
 		SG_ rLamLearn : 24|8@1+ (0.78125,-100) [-20|20] "%"  RCPMK2
 		SG_ vBattery : 32|8@1+ (0.08,0) [0|20] "V"  RCPMK2
 		SG_ rTDprop : 40|8@1+ (0.2,-25.6) [-25|25] "%"  RCPMK2
 		SG_ rTDint : 48|8@1+ (0.2,-25.6) [-25|25] "%"  RCPMK2 		
	*/
	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);		
	rcpCanMessageSetup(0x703, 0, 8, 0, RPCBUF); 	 
	((unsigned short*)addrtemp)[0] = limit_u16((pRamVariables.TargetBoost-242.850759f)*25.3447147559339f);
	((unsigned char*)addrtemp)[2] = limit_u8(pRamVariables.MapBlendRatio * 255);
	((unsigned char*)addrtemp)[3] = limit_u8((*pAFLearning_1)/0.0078125f);
	((unsigned char*)addrtemp)[4] = limit_u8((*pBatteryVoltage)/0.08);
	((unsigned char*)addrtemp)[5] = limit_u8((*pTD_wg_prop*5)+128);
	((unsigned char*)addrtemp)[6] = limit_u8((*pTD_wg_int*5)+128);
	sendCanMessage(11);
}

void send_frame_0x704()
{
	/*
	BO_ 1796 ecm_stat5: 8 PCANROUTER
		SG_ rLambdaTarget : 0|16@1+ (0.001,0) [0|65535] "rat"  RCPMK2
		SG_ rLambdaStoich : 18|8@1+ (0.02777777778,8) [8|15] "afr"  RCPMK2
		SG_ kpFuel : 24|8@1+ (0.0078125,0) [0|2] "x"  RCPMK2
 		SG_ rLamLearnA : 32|8@1+ (0.01,-128) [-100|100] "%"  RCPMK2
 		SG_ rLamLearnB : 40|8@1+ (0.01,-128) [-100|100] "%"  RCPMK2
 		SG_ rLamLearnC : 48|8@1+ (0.01,-128) [-100|100] "%"  RCPMK2
 		SG_ rLamLearnD : 56|8@1+ (0.01,-128) [-100|100] "%"  RCPMK2
	*/
	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);	
	rcpCanMessageSetup(0x704, 0, 8, 0, RPCBUF); 	 	
	
	((unsigned short*)addrtemp)[0] = limit_u16(pRamVariables.PolfOutput * 1000);
	((unsigned char*)addrtemp)[2] = limit_u8((pRamVariables.TargetedStoich-8)*36);
	((unsigned char*)addrtemp)[3] = limit_u8((pRamVariables.kFuelPressure / 0.0078125));
	((unsigned char*)addrtemp)[4] = limit_u8((*prLamLearnA*100) + 128);
 	((unsigned char*)addrtemp)[5] = limit_u8((*prLamLearnB*100) + 128);
 	((unsigned char*)addrtemp)[6] = limit_u8((*prLamLearnC*100) + 128);
	((unsigned char*)addrtemp)[7] = limit_u8((*prLamLearnD*100) + 128); 
	sendCanMessage(11);
}

void send_frame_0x705()
{
	/*
	BO_ 1797 ecm_stat6: 8 PCANROUTER
  		SG_ xOdometer : 0|32@1+ (0.1,0) [0|65535.] "km"  RCPMK2
		SG_ pFuel : 32|16@1+ (0.01,0) [0|65.55] "psig"  RCPMK2
		SG_ pFuelAbs : 48|16@1+ (0.01,0) [0|65.55] "psia"  RCPMK2
	*/
	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);	
	rcpCanMessageSetup(0x705, 0, 8, 0, RPCBUF); 	
	((unsigned long*)addrtemp)[0] = limit_u32(*pEstimatedOdometer * 10);
	((unsigned short*)addrtemp)[2] = limit_u16((pRamVariables.pFuelCanRel*100));
	((unsigned short*)addrtemp)[3] = limit_u16((pRamVariables.pFuelCan*100));
	sendCanMessage(11);
}
#endif
#endif

