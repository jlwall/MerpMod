/*
	Copyright (C) 2012-2013 Merrill A. Myers III merrillamyersiii@gmail.com
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

//Tests for CEL Flashing Code
//TODO test for normal/severe knock behavior, implement interrupt when lowknock -> hi
#include "EcuHacks.h"
// Test the rev limiter hack.
#if CAN_HACKS

void TestCustomCan(int c) __attribute__ ((section ("Misc")));
void TestCustomCan(int c)
{
	int i;
	for(i = 0;i<c;i++)
	{
	//	CustomCan();
	}
}

unsigned long getMailBoxId(unsigned short mailbox, unsigned short bus) __attribute__ ((section ("Misc")));
unsigned long getMailBoxId(unsigned short mailbox, unsigned short bus)
{
	unsigned short* ptr;	
	ptr = (unsigned short*)(0xFFFFD100+ 0x800*bus + 0x20*(unsigned short)mailbox);
/*	if(cs->ext == 0) //11-bit, not extended
		{
		ptr[0] = ((unsigned short)cs->id<<4)&0x7FF0;
		ptr[1] = 0;
		}
	else if(cs->ext == 1)
		{
		ptr[0]  = (unsigned short)(((unsigned long)cs->id>>16)&0x0003);
		ptr[0] += (unsigned short)(0x0004);
		ptr[0] += (unsigned short)(((unsigned long)cs->id>>14)&0x7FF0);
		ptr[1] = ((unsigned short)cs->id)&0xFFFF;
		}		
	//ptr[2] = (((unsigned short)cs->mcs<<8)&0x700) + ((unsigned short)cs->dlc&0x0F);	*/
	unsigned short ddd = ptr[0]&0x04;
	unsigned long id = 0xffffffff;
	if(ddd == 0x04)
	{
		id = (unsigned long)ptr[1];
		id += (unsigned long)(ptr[0]&0x02)<<16;
		id += (unsigned long)(ptr[0]&0x7FF0)<<14;		
	}
	else
	{
		id = (ptr[0]>>4)&0x7FF;		
	}
	return id;
}



void CustomCanUnitTests() __attribute__ ((section ("Misc")));
void CustomCanUnitTests()
{

unsigned char dt1[8];
unsigned char dt2[8];
unsigned char dt3[8];
unsigned char dtAEM[8];
unsigned char dte85[8];

	PopulateRamVariables();
	
	//Test E85 Stuff
	*pAfCorrection_1 = 0.25f;	
	*pIgnitionTimeTotal = 31.223f;	
	*pMassAirFlow = 1.29f;
	*pManifoldAbsolutePressure = (12.45f)*51.71492410239613f + 760; //12.45 psig to mmHG
	*pWgdc4 = 4;
	pRamVariables.kFuelPressure = 1.1f;
		/*
	BO_ 1792 ecm_stat1: 8 ECM
 		SG_ rLamCor : 0|8@1+ (0.78125,-100) [-20|20] "%"  RCPMK2
 		SG_ aIgn : 8|8@1+ (0.5,-64) [-20|60] "deg"  RCPMK2
 		SG_ rMaf : 16|16@1+ (0.01,0) [0|400] "g/s"  RCPMK2
 		SG_ pPlenum : 32|16@1+ (0.000762951,-10) [-10|40] "psig"  RCPMK2
 		SG_ rWG : 48|8@1+ (0.392157,0) [0|100] "%"  RCPMK2
 		SG_ rLam : 56|8@1+ (0.0078125,0) [0|2] "rat"  RCPMK2
		((unsigned char*)addrtemp)[0] = limit_u8((*pAfCorrection_1)/0.0078125f);
		((unsigned char*)addrtemp)[1] = limit_u8((*pIgnitionTimeTotal)/0.5f + 128);
		((unsigned short*)addrtemp)[1] = limit_u16((*pMassAirFlow)/0.01f);
		((unsigned short*)addrtemp)[2] = limit_u16(((*pManifoldAbsolutePressure)-242.850759f)*25.3447147559339f);
		((unsigned char*)addrtemp)[6] = limit_u8((*pWgdc4)/0.392157f);
		((unsigned char*)addrtemp)[7] = limit_u8((*pAf1Res)/0.0078125f);
	*/
	send_frame_0x700();
	
	unsigned long addrtemp = (0xFFFFD108 + 0x20*RPCBUF1);
	
	Assert( ((unsigned char*)addrtemp)[0] == 0x20	,"CAN 0x700 d0");
	Assert( ((unsigned char*)addrtemp)[1] == 190	,"CAN 0x700 d1");
	Assert( ((unsigned short*)addrtemp)[1] == 129	,"CAN 0x700 d2.d3");
	Assert( ((unsigned short*)addrtemp)[2] == 29425	,"CAN 0x700 d4.d5");
	Assert( ((unsigned char*)addrtemp)[6] == 10	,"CAN 0x700 d6");
	Assert( ((unsigned char*)addrtemp)[7] == 141 ,"CAN 0x700 d7");
	
	
		/*
	BO_ 1793 ecm_stat2: 8 ECM
 		SG_ iam : 0|8@1+ (0.0625,0) [0|0] ""  RCPMK2
 		SG_ aKnockFeed : 8|8@1+ (0.351563,-45) [0|0] ""  RCPMK2
 		SG_ aKnockFine : 16|8@1+ (0.351563,-45) [0|0] ""  RCPMK2
		SG_ CLOL : 24|8@1+ (1,0) [0|125] ""  RCPMK2
 		SG_ pKnockSum1 : 32|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ pKnockSum2 : 40|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ pKnockSum3 : 48|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ pKnockSum4 : 56|8@1+ (1,0) [0|255] ""  RCPMK2
 		

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
	 	*/
	*pIam4 = 0.5;
	*pFbkc1 = 2;
	*pkclearn1 = 3;
	*pCLOL = 4;
	
	*pKnockSum1 = 1;
	*pKnockSum2 = 2;
	*pKnockSum3 = 3;
	*pKnockSum4 = 4;
	
		
	send_frame_0x701();
	
	addrtemp = (0xFFFFD108 + 0x20*RPCBUF2);
	Assert( ((unsigned char*)addrtemp)[0] == 8	,"CAN 0x701 d0");
	Assert( ((unsigned char*)addrtemp)[1] == 2	,"CAN 0x701 d1");
	Assert( ((unsigned char*)addrtemp)[2] == 3	,"CAN 0x701 d2");
	Assert( ((unsigned char*)addrtemp)[3] == 4	,"CAN 0x701 d3");
	Assert( ((unsigned char*)addrtemp)[4] == 1	,"CAN 0x701 d4");
	Assert( ((unsigned char*)addrtemp)[5] == 2	,"CAN 0x701 d5");
	Assert( ((unsigned char*)addrtemp)[6] == 3  ,"CAN 0x701 d6");
	Assert( ((unsigned char*)addrtemp)[7] == 4  ,"CAN 0x701 d7");
	
		/*
	BO_ 1794 ecm_stat3: 8 ECM
 		SG_ pNRough_C1 : 0|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ pNRough_C2 : 8|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ pNRough_C3 : 16|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ pNRough_C4 : 24|8@1+ (1,0) [0|255] ""  RCPMK2
 		SG_ aCamInR : 32|8@1+ (1,-50) [-50|50] ""  RCPMK2
 		SG_ aCamInL : 40|8@1+ (1,-50) [-50|50] ""  RCPMK2
 		SG_ aCamExR : 48|8@1+ (1,-50) [-50|50] ""  RCPMK2
 		SG_ aCamExL : 56|8@1+ (1,-50) [-50|50] ""  RCPMK2
 
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
		*/
		
	*pNRough_C1 = 1;
	*pNRough_C2 = 2;
	*pNRough_C3 = 3;
	*pNRough_C4 = 4;
	
	*pAVCSIntakeRight = -40;
	*pAVCSIntakeLeft = -20;
	*pAVCSExhaustRight = 0;
	*pAVCSExhaustLeft = 20;
		
	send_frame_0x702();
	
	addrtemp = (0xFFFFD108 + 0x20*RPCBUF1);
	Assert( ((unsigned char*)addrtemp)[0] == 1	,"CAN 0x702 d0");
	Assert( ((unsigned char*)addrtemp)[1] == 2	,"CAN 0x702 d1");
	Assert( ((unsigned char*)addrtemp)[2] == 3	,"CAN 0x702 d2");
	Assert( ((unsigned char*)addrtemp)[3] == 4	,"CAN 0x702 d3");
	Assert( ((unsigned char*)addrtemp)[4] == 48	,"CAN 0x702 d4");
	Assert( ((unsigned char*)addrtemp)[5] == 88	,"CAN 0x702 d5");
	Assert( ((unsigned char*)addrtemp)[6] == 128,"CAN 0x702 d6");
	Assert( ((unsigned char*)addrtemp)[7] == 168,"CAN 0x702 d7");
	
	
		/*
	BO_ 1795 ecm_stat4: 8 PCANROUTER 		
 		SG_ pPlenumTarg : 0|16@1+ (0.000762951,-10) [-10|40] "psig" RCPMK2
		SG_ rBlendFuel : 16|8@1+ (0.3921568627,0) [0|100] "%"  RCPMK2
 		SG_ rLamLearn : 24|8@1+ (0.78125,-100) [-20|20] "%"  RCPMK2
 		SG_ vBattery : 32|8@1+ (0.08,0) [0|20] "V"  RCPMK2
 		SG_ rTDprop : 40|8@1+ (0.2,-25.6) [-25|25] "%"  RCPMK2
 		SG_ rTDint : 48|8@1+ (0.2,-25.6) [-25|25] "%"  RCPMK2 	
		SG_ bCutArray : 56|8@1+ (1,0) [0|255] ""  RCPMK2 	
	((unsigned short*)addrtemp)[0] = limit_u16((pRamVariables.TargetBoost-242.850759f)*25.3447147559339f);
	((unsigned char*)addrtemp)[2] = limit_u8(pRamVariables.MapBlendRatio * 255);
	((unsigned char*)addrtemp)[3] = limit_u8((*pAFLearning_1)/0.0078125f);
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
	
	sendCanMessage(11);*/
	*pTargetBoostCommand = ((13.5 * 51.71492510510006) + 760);
	pRamVariables.MapBlendRatio = 0.44;
	*pAFLearning_1 = 0.1;
	*pBatteryVoltage = 14.5;
	*pTD_wg_prop = 1.2;
	*pTD_wg_int = 2.4;
	
	pRamVariables.bFFSengaged = 0;
	pRamVariables.bFFSenabled = 0;
	pRamVariables.bLCengaged = 0;
	pRamVariables.BlendMode = 0;
	pRamVariables.bValetMode = 0;
	pRamVariables.bPLSLRequest = 0;
	pRamVariables.bPLSLcutting = 0;
	*pFlagsRevLim = 0;
		
	send_frame_0x703();
	
	addrtemp = (0xFFFFD108 + 0x20*RPCBUF2);
	Assert( ((unsigned char*)addrtemp)[0] == 0x78	,"CAN 0x703 d0");
	Assert( ((unsigned char*)addrtemp)[1] == 0x51	,"CAN 0x703 d1");
	Assert( ((unsigned char*)addrtemp)[2] == 112,"CAN 0x703 d2");
	Assert( ((unsigned char*)addrtemp)[3] == 141,"CAN 0x703 d3");
	Assert( ((unsigned char*)addrtemp)[4] == 181,"CAN 0x703 d4");
	Assert( ((unsigned char*)addrtemp)[5] == 134,"CAN 0x703 d5");
	Assert( ((unsigned char*)addrtemp)[6] == 140,"CAN 0x703 d6");
	Assert( ((unsigned char*)addrtemp)[7] == 0  ,"CAN 0x703 d7");
	
	pRamVariables.bFFSengaged = 1; send_frame_0x703(); 
	Assert( ((unsigned char*)addrtemp)[7] == 1  ,"CAN 0x703 FFSEngaged");
	
	pRamVariables.bFFSenabled = 1; send_frame_0x703(); 

	Assert( ((unsigned char*)addrtemp)[7] == 3  ,"CAN 0x703 FlatFootShiftMode");
	
	pRamVariables.bLCengaged = 1; send_frame_0x703(); 
	Assert( ((unsigned char*)addrtemp)[7] == 7  ,"CAN 0x703 LCEngaged");
	
	pRamVariables.BlendMode = 1; send_frame_0x703(); 
	Assert( ((unsigned char*)addrtemp)[7] == 15  ,"CAN 0x703 BlendMode");
	
	pRamVariables.bValetMode = 1; send_frame_0x703(); 
	Assert( ((unsigned char*)addrtemp)[7] == 31  ,"CAN 0x703 ValetMode");
	
	pRamVariables.bPLSLRequest = 1; send_frame_0x703(); 
	Assert( ((unsigned char*)addrtemp)[7] == 63  ,"CAN 0x703 bPLSLRequest");
	
	pRamVariables.bPLSLcutting = 1; send_frame_0x703();
	Assert( ((unsigned char*)addrtemp)[7] == 127  ,"CAN 0x703 bPLSLcutting");
	
	*pFlagsRevLim = 1; send_frame_0x703(); 
	Assert( ((unsigned char*)addrtemp)[7] == 255 ,"CAN 0x703 pFlagsRevLim");
	
	
	
	
	
		
	pRamVariables.RevLimCut = 6402;
	pRamVariables.RevLimResume = 6300;
	
	pRamVariables.InjectorScaling = 2707090 /1065.5;
	
	pRamVariables.MapBlendRatio = 0.5;
	
	pRamVariables.MapSwitch = 2;
	pRamVariables.MafFromSpeedDensity = 10.23;
	
		
	send_frame_0x708();
	
	addrtemp = (0xFFFFD108 + 0x20*RPCBUF2);
	Assert( ((unsigned char*)addrtemp)[0] == 0xc8	,"CAN 0x702 d0");
	Assert( ((unsigned char*)addrtemp)[1] == 0x1C	,"CAN 0x702 d1");
	Assert( ((unsigned char*)addrtemp)[2] == 0x4E	,"CAN 0x702 d2");
	Assert( ((unsigned char*)addrtemp)[3] == 0x85	,"CAN 0x702 d3");
	Assert( ((unsigned char*)addrtemp)[4] == 0x28	,"CAN 0x702 d4");
	Assert( ((unsigned char*)addrtemp)[5] == 0x08	,"CAN 0x702 d5");
	Assert( ((unsigned char*)addrtemp)[6] == 0x03	,"CAN 0x702 d6");
	Assert( ((unsigned char*)addrtemp)[7] == 0xFF	,"CAN 0x702 d7");

	
	
	
	CanSetup();	
	//Test to make sure CanSetup puts the right info into the Mailboxes
	Assert(getMailBoxId(ccm00.mailBox, ccm00.bus) == ccm00.id, "CAN ID 0 is not set Correctly");
	Assert(getMailBoxId(ccm01.mailBox, ccm01.bus) == ccm01.id, "CAN ID 1 is not set Correctly");
	Assert(getMailBoxId(ccm02.mailBox, ccm02.bus) == ccm02.id, "CAN ID 2 is not set Correctly");
	Assert(getMailBoxId(ccm03.mailBox, ccm03.bus) == ccm03.id, "CAN ID 3 is not set Correctly");
	Assert(getMailBoxId(ccm04.mailBox, ccm04.bus) == ccm04.id, "CAN ID 4 is not set Correctly");
	Assert(getMailBoxId(ccm05.mailBox, ccm05.bus) == ccm05.id, "CAN ID 5 is not set Correctly");
	Assert(getMailBoxId(ccm06.mailBox, ccm06.bus) == ccm06.id, "CAN ID 6 is not set Correctly");
	
	dtAEM[0] = 32;
	dtAEM[1] = 1;
	dtAEM[2] = 5;
	dtAEM[3] = 2;
	canCallbackAEMwideband(&dtAEM[0]);
	
	Assert(Abs(pRamVariables.aemLambda - 0.8193f) < 0.0001, "aem lambda Fault Failed");
	Assert(Abs(pRamVariables.aemOxygen - 1.282f) < 0.0001, "aem oxygen Fault Failed");
	
	dtAEM[6]  = 0x80;
	canCallbackAEMwideband(&dtAEM[0]);
	Assert(pRamVariables.aemDataValid == 1, "aem Data Valid Failed");
	
	dtAEM[7]  = 0x40;
	canCallbackAEMwideband(&dtAEM[0]);
	Assert(pRamVariables.aemSensorFault == 1, "aem Sensor Fault Failed");	

	dtAEM[6]  = 0x00;
	canCallbackAEMwideband(&dtAEM[0]);
	Assert(pRamVariables.aemDataValid == 0, "aem Data Valid Failed");
	
	dtAEM[7]  = 0x00;
	canCallbackAEMwideband(&dtAEM[0]);
	Assert(pRamVariables.aemSensorFault == 0, "aem Sensor Fault Failed");
	
	
	
	////////CHECK e85 Packet
	dte85[0] = 0x31;	
	dte85[1] = 45; 
	dte85[2] = 0x54; //1.65 Volts
	dte85[3] = 0x7A;	
	dte85[4] = 0x38;	
	dte85[5] = 0x52;	
	*pManifoldAbsolutePressure = (-2.27*51.71492510510006)+760;	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	canCallbackMK3e85Packet(&dte85[0]);	
	
	/*
		pRamVariables.rEthanolCAN = (float)(data[0])*0.003921568627; 		//0 to 255 for 0 to 100% 1/255 LSB/%	
	pRamVariables.tFuelCAN = (float)(data[1])-40;	//0 to 165 for -40 to 125C
	updateFuelPressure((unsigned short)((unsigned short)data[2]*256 + (unsigned short)data[3]));
	pRamVariables.pFuelCanRel = pRamVariables.pFuelCan - (*pManifoldAbsolutePressure-760)/51.71492510510006;
	*/
	Assert(Abs(pRamVariables.rEthanolCAN - 0.1921569) <0.001f, "mk3 rEthanolCAN failed");
	Assert(Abs(pRamVariables.tFuelCAN - 5) <0.001f, "mk3 tFuelCAN failed");
	//Assert(Abs(pRamVariables.vFuelPressureRel - 1.65) <0.001f, "mk3 vFuelPressure failed");
	Assert(Abs(pRamVariables.pFuelCan - 22.105) <0.01f, "mk3 pFuelTest failed");
	Assert(Abs(pRamVariables.pFuelCanRel - (22.105 + 2.27)) <0.001f, "mk3 pFuelCanRel failed");
	
	//Try all DT types, 1,2,3 U8,U16,U32
	cmDTccm[0] = 0;	
	cmDTaddr[0] = 0xFFFF0000;	
	ccm00.mailBox = 19; //Force to Mailbox 19 for now
	cmDTtypeIn[0] = 1;
	cmDTtypeOut[0] = 1;
	*((unsigned char*)cmDTaddr[0]) = 0x55;
	updateCanDT(0);
	Assert(*(unsigned char*)(0xFFFFD100+0x08+19*0x20) == 0x55, "DT U8 Check Failed");
	
	cmDTtypeIn[0] = 2;
	cmDTtypeOut[0] = 2;
	*((unsigned short*)cmDTaddr[0]) = 0x1234;
	updateCanDT(0);
	Assert(*(unsigned short*)(0xFFFFD100+0x08+19*0x20) == 0x1234, "DT U16 Check Failed");
	
	cmDTtypeIn[0] = 3;
	cmDTtypeOut[0] = 3;
	*((unsigned long*)cmDTaddr[0]) = 0x87654321;
	updateCanDT(0);
	Assert(*(unsigned long*)(0xFFFFD100+0x08+19*0x20) == 0x87654321, "DT U32 Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 4;
	*((float*)cmDTaddr[0]) = 3.1415f;
	updateCanDT(0);
	Assert(*(float*)(0xFFFFD100+0x08+19*0x20) == 3.1415f, "DT float Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 4;
	cmDTscale[0] = 3;
	cmDToffset[0] = 0;
	*((float*)cmDTaddr[0]) = 3.1415f;
	updateCanDT(0);
	Assert(*(float*)(0xFFFFD100+0x08+19*0x20) == 3.1415f*3, "DT float scale Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 4;
	cmDTscale[0] = 3;
	cmDToffset[0] = 2.25f;
	*((float*)cmDTaddr[0]) = 3.1415f;
	updateCanDT(0);
	Assert(*(float*)(0xFFFFD100+0x08+19*0x20) == ((2.25f + 3.1415f)*3), "DT float scale offset Check Failed");
	
	
	//Float to U8
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 1;
	*((float*)cmDTaddr[0]) = 3.1415f;
	cmDTscale[0] = 1;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned char*)(0xFFFFD100+0x08+19*0x20) == 3, "DT float u8 Check Failed");
	
	//this should round up
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 1;
	*((float*)cmDTaddr[0]) = 3.50001f;
	cmDTscale[0] = 1;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned char*)(0xFFFFD100+0x08+19*0x20) == 4, "DT float u8 Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 1;
	cmDTscale[0] = 3;
	cmDToffset[0] = 0;
	*((float*)cmDTaddr[0]) = 3.1415f;
	updateCanDT(0);
	Assert(*(unsigned char*)(0xFFFFD100+0x08+19*0x20) == 9, "DT float u8 scale Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 1;
	cmDTscale[0] = 4;
	cmDToffset[0] = 2;
	*((float*)cmDTaddr[0]) = 3;
	updateCanDT(0);
	Assert(*(unsigned char*)(0xFFFFD100+0x08+19*0x20) == 20, "DT float u8 scale offset Check Failed");
	
		//Float to U16
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 2;
	*((float*)cmDTaddr[0]) = 257.49;
	cmDTscale[0] = 1;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned short*)(0xFFFFD100+0x08+19*0x20) == 257, "DT float u16 Check Failed");
	
	//this should round up
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 2;
	*((float*)cmDTaddr[0]) = 257.501;
	cmDTscale[0] = 1;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned short*)(0xFFFFD100+0x08+19*0x20) == 258, "DT float u16 Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 2;
	cmDTscale[0] = 3;
	cmDToffset[0] = 0;
	*((float*)cmDTaddr[0]) = 100;
	updateCanDT(0);
	Assert(*(unsigned short*)(0xFFFFD100+0x08+19*0x20) == 300, "DT float u16 scale Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 2;
	cmDTscale[0] = 4;
	cmDToffset[0] = 2;
	*((float*)cmDTaddr[0]) = 100;
	updateCanDT(0);
	Assert(*(unsigned short*)(0xFFFFD100+0x08+19*0x20) == 408, "DT float u16 scale offset Check Failed");
	
	//Float to U8 OVERFLOWS
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 1;
	*((float*)cmDTaddr[0]) = -3;
	cmDTscale[0] = 0;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned char*)(0xFFFFD100+0x08+19*0x20) == 0, "DT float u8 Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 1;
	*((float*)cmDTaddr[0]) = 300;
	cmDTscale[0] = 0;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned char*)(0xFFFFD100+0x08+19*0x20) == 255, "DT float u8 Check Failed");
	
	//Float to U16 OVERFLOWS
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 2;
	*((float*)cmDTaddr[0]) = -3;
	cmDTscale[0] = 0;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned short*)(0xFFFFD100+0x08+19*0x20) == 0, "DT float u8 Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 2;
	*((float*)cmDTaddr[0]) = 65536;
	cmDTscale[0] = 0;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned short*)(0xFFFFD100+0x08+19*0x20) == 65535, "DT float u8 Check Failed");
	
	//Float to U32 OVERFLOWS
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 3;
	*((float*)cmDTaddr[0]) = -3;
	cmDTscale[0] = 0;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned long*)(0xFFFFD100+0x08+19*0x20) == 0, "DT float u8 Check Failed");
	
	cmDTtypeIn[0] = 4;
	cmDTtypeOut[0] = 3;
	*((float*)cmDTaddr[0]) = 0xFFFFFFFF;
	cmDTscale[0] = 0;
	cmDToffset[0] = 0;
	updateCanDT(0);
	Assert(*(unsigned long*)(0xFFFFD100+0x08+19*0x20) == 0xFFFFFFFF, "DT float u8 Check Failed");
	
	CustomCanService();
	
	#if RACEGRADE_KEYPAD_HACKS
		dt1[4] = 0;
		raceGradeKeyPadCallback(&dt1[0]);
		dt1[4] = 1;
		raceGradeKeyPadCallback(&dt1[0]);
		dt1[4] = 2;
		raceGradeKeyPadCallback(&dt1[0]);
		dt1[4] = 3;
		raceGradeKeyPadCallback(&dt1[0]);
		dt1[4] = 4;
		//raceGradeKeyPadCallback(&dt1[0]);
		dt1[4] = 5;
		//raceGradeKeyPadCallback(&dt1[0]);
	#endif

	pRamVariables.initFunctionRun = 0;	
	CustomCanService();



	
	
	//Check it is still on
//	TestCustomCan(20);
//	Assert(pRamVariables.CelSignal == 1, "OEM cel popped, 20 cycles later, Cel Signal should stay on");

}	
	
#endif
