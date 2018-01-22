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
		case  9:	pRamVariables.rcpFrameState++; break;	
		case 10:	send_frame_0x708();		pRamVariables.rcpFrameState++; break;
		case 11:	pRamVariables.rcpFrameState++; break;
		case 12:	send_frame_0x709();		pRamVariables.rcpFrameState++; break;
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
	rcpCanMessageSetup(rcpCAN_ID_m0, 0, 8, 0, RPCBUF); 		 	
	((unsigned char*)addrtemp)[0] = limit_u8((*pAfCorrection_1)/0.0078125f);
	((unsigned char*)addrtemp)[1] = limit_u8((*pIgnitionTimeTotal)/0.5f + 128);
	((unsigned short*)addrtemp)[1] = limit_u16((*pMassAirFlow)/0.01f);
	((unsigned short*)addrtemp)[2] = limit_u16(((*pManifoldAbsolutePressure)-242.850759f)*25.3447147559339f);
 	((unsigned char*)addrtemp)[6] = limit_u8((*pWgdc4)/0.392157f);
	((unsigned char*)addrtemp)[7] = limit_u8((pRamVariables.kFuelPressure / 0.0078125));
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
	rcpCanMessageSetup(rcpCAN_ID_m1, 0, 8, 0, RPCBUF); 	
 	((unsigned char*)addrtemp)[0] = limit_u8((*pIam4)*16); 		
	((unsigned char*)addrtemp)[1] = *pFbkc1; 		
	((unsigned char*)addrtemp)[2] = *pkclearn1; 
	((unsigned char*)addrtemp)[3] = *pCLOL;			
	((unsigned char*)addrtemp)[4] = *pKnockSum1; 		
	((unsigned char*)addrtemp)[5] = *pKnockSum2; 		
	((unsigned char*)addrtemp)[6] = *pKnockSum3; 		
	((unsigned char*)addrtemp)[7] = *pKnockSum4; 		

	
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
	if(pRamVariables.rcp0x702_tick == 0)
	{
		unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);	
		rcpCanMessageSetup(rcpCAN_ID_m2, 0, 8, 0, RPCBUF); 	 		
		((unsigned char*)addrtemp)[0] = *pNRough_C1; 	
		((unsigned char*)addrtemp)[1] = *pNRough_C2; 		
	 	((unsigned char*)addrtemp)[2] = *pNRough_C3;		
		((unsigned char*)addrtemp)[3] = *pNRough_C4;	
	 	((unsigned char*)addrtemp)[4] = limit_u8((*pAVCSIntakeRight * 2) + 128);
	 	((unsigned char*)addrtemp)[5] = limit_u8((*pAVCSIntakeLeft * 2) + 128);
	 	((unsigned char*)addrtemp)[6] = limit_u8((*pAVCSExhaustRight * 2) + 128);
		((unsigned char*)addrtemp)[7] = limit_u8((*pAVCSExhaustLeft * 2) + 128);
		sendCanMessage(11);
		pRamVariables.rcp0x702_tick = 1;
	}
	else
		pRamVariables.rcp0x702_tick--;
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
		SG_ bCutArray : 56|8@1+ (1,0) [0|255] ""  RCPMK2 	
	*/
	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);	
	unsigned char bitArray = 0;	
	rcpCanMessageSetup(rcpCAN_ID_m3, 0, 8, 0, RPCBUF); 
	#if BOOST_HACKS	 
		((unsigned short*)addrtemp)[0] = limit_u16((pRamVariables.TargetBoost-242.850759f)*25.3447147559339f);
	#endif
	((unsigned char*)addrtemp)[2] = limit_u8(pRamVariables.MapBlendRatio * 255);
	((unsigned char*)addrtemp)[3] = limit_u8((*pAFLearning_1)/0.0078125f + 128);
	((unsigned char*)addrtemp)[4] = limit_u8((*pBatteryVoltage)/0.08);
	((unsigned char*)addrtemp)[5] = limit_u8((*pTD_wg_prop*5)+128);
	((unsigned char*)addrtemp)[6] = limit_u8((*pTD_wg_int*5)+128);
	if(pRamVariables.FFSEngaged==1) bitArray |= 0x01;
	if(pRamVariables.FlatFootShiftMode>0) bitArray |= 0x02;
	if(pRamVariables.LCEngaged==1) bitArray |= 0x04;
	if(pRamVariables.BlendMode==1) bitArray |= 0x08;
	if(pRamVariables.ValetMode==1) bitArray |= 0x10;
	if(pRamVariables.bPLSLRequest==1) bitArray |= 0x20;
	if(pRamVariables.bPLSLcutting==1) bitArray |= 0x40;
	if((*pFlagsRevLim&0x01)>0) bitArray |= 0x80;
	((unsigned char*)addrtemp)[7] = bitArray;	
	
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
	rcpCanMessageSetup(rcpCAN_ID_m4, 0, 8, 0, RPCBUF); 	 	
	#if POLF_HACKS
		((unsigned short*)addrtemp)[0] = limit_u16(1000/(1+pRamVariables.PolfOutput));	
		((unsigned char*)addrtemp)[2] = limit_u8((pRamVariables.TargetedStoich-8)*36);
	#endif
	((unsigned char*)addrtemp)[3] = limit_u8((*pAf1Res)/0.0078125f);	
	((unsigned char*)addrtemp)[4] = limit_u8((*prLamLearnA*200) + 128);
 	((unsigned char*)addrtemp)[5] = limit_u8((*prLamLearnB*200) + 128);
 	((unsigned char*)addrtemp)[6] = limit_u8((*prLamLearnC*200) + 128);
	((unsigned char*)addrtemp)[7] = limit_u8((*prLamLearnD*200) + 128); 
	sendCanMessage(11);
}

void send_frame_0x708()
{
	/*BO_ 1800 ecm_slow1: 8 ECM
 SG_ nRevLimCut : 7|12@0+ (2,0) [0|8000] "rpm"  RCP
 SG_ nRevLimResume : 11|12@0+ (2,0) [0|8000] "rpm"  RCP
 SG_ nLaunchControlCut : 31|12@0+ (2,0) [0|8000] "rpm"  RCP
 			SG_ rMapBlendRatio : 35|8@0+ (0.3921568627,0) [0|100] "%"  RCP
 SG_ MapSwitch : 42|2@1+ (1,0) [0|1] "x"  RCP
 SG_ rMafFromSpeedDensity : 55|16@0+ (0.01,0) [0|400] "g/s"  RCP*/
 
	if(pRamVariables.rcp0x708_tick == 0)
	{
	 	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);	
		unsigned short vtemp = 0;
		rcpCanMessageSetup(0x708, 0, 8, 0, RPCBUF); 	 	
	
		vtemp = (unsigned short)( pRamVariables.RevLimCut/2);
		((unsigned char*)addrtemp)[0] = (vtemp>>4)&0xFF;
		((unsigned char*)addrtemp)[1] = (vtemp<<4)&0xF0;
	
		vtemp = (unsigned short)( pRamVariables.RevLimResume/2);
		((unsigned char*)addrtemp)[1] += ((vtemp>>8)&0x0F);
		((unsigned char*)addrtemp)[2] = ((vtemp)&0xFF);
	
		vtemp = (unsigned short)( 2707090 / pRamVariables.InjectorScaling*2);
		((unsigned char*)addrtemp)[3] = (vtemp>>4)&0xFF;
		((unsigned char*)addrtemp)[4] = (vtemp<<4)&0xF0;
	
		vtemp = (unsigned short)limit_u8( pRamVariables.MapBlendRatio*255);
		((unsigned char*)addrtemp)[4] += ((vtemp>>4)&0x0F);
		((unsigned char*)addrtemp)[5] = ((vtemp<<4)&0xF0);
	
		((unsigned char*)addrtemp)[5] += ((pRamVariables.MapSwitch<<2)&0x0C);
	
		((unsigned short*)addrtemp)[3] = limit_u16((pRamVariables.MafFromSpeedDensity)*100);
		sendCanMessage(11);
		pRamVariables.rcp0x708_tick = 1;
	}
	else
		pRamVariables.rcp0x708_tick--;
}

void send_frame_0x709()
{
	if(pRamVariables.rcp0x709_tick == 0)
	{
	 	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF);			
		rcpCanMessageSetup(0x709, 0, 8, 0, RPCBUF); 	 	
			
		((unsigned char*)addrtemp)[0] = pRamVariables.nINJCutCTR;
		((unsigned char*)addrtemp)[1] = pRamVariables.nINJFuncCTR;		
		((unsigned short*)addrtemp)[1] = pRamVariables.nINJCutPattern;
		((unsigned char*)addrtemp)[4] = limit_u8(*pInjCompC1*128); 
		((unsigned char*)addrtemp)[5] = limit_u8(*pInjCompC2*128); 
		((unsigned char*)addrtemp)[6] = limit_u8(*pInjCompC3*128); 
		((unsigned char*)addrtemp)[7] = limit_u8(*pInjCompC4*128); 
		
		sendCanMessage(11);
		pRamVariables.rcp0x709_tick = 1;
	}
	else
		pRamVariables.rcp0x709_tick--;
}

#endif
#endif

