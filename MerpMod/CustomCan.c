/*
	Copyright (C) 2017-2017 Johnny Lloyd Wall jlwall@gmail.com
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/


#include "EcuHacks.h"
#if CAN_HACKS

unsigned long shC[24] CANDATA = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4192304,8388608};

void setupMailBoxStruct(CanMessageSetupStruct* cs)
{
	unsigned short* ptr;	
	ptr = (unsigned short*)(0xFFFFD100+ 0x800*(unsigned short)(cs->bus&0x01) + 0x20*(unsigned short)(cs->mailBox&0x1F));
	if(cs->ext == 0) //11-bit, not extended
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
	ptr[2] = (((unsigned short)cs->mcs<<8)&0x700) + ((unsigned short)cs->dlc&0x0F);	
}

void updateCanDT(unsigned char dt)
{
	unsigned long addrtemp;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	if(cmDTaddr[dt] >= 0xFFFF0000)
	{		
		addrtemp = 0xFFFFD108;
		//addrtemp += 0x800*(unsigned long)(ccmGroup[cmDTccm[dt]].bus&0x01);		
		addrtemp += 0x020*(unsigned long)(ccmGroup[cmDTccm[dt]].mailBox&0x1F);
		//addrtemp += 0x08;
		addrtemp += (unsigned long)cmDTpos[dt]&0x07;			
		switch(cmDTtypeIn[dt])
		{
		case 1: 
			{
			unsigned char* ptrSource = (unsigned char*)cmDTaddr[dt];
			unsigned char* ptrSink = (unsigned char*)addrtemp;		
			ptrSink[0] = ptrSource[0];			
			}
			break;
		case 2: 
			{			
			if(((addrtemp%2) ==0) && ((cmDTaddr[dt]%2) ==0))
				{
				unsigned short* ptrSource = (unsigned short*)cmDTaddr[dt];
				unsigned short* ptrSink = (unsigned short*)addrtemp;	
				ptrSink[0] = ptrSource[0];
				}
			}
			break;		
		case 3: 
			{				
			if(((addrtemp%4) ==0) && ((cmDTaddr[dt]%4) ==0))
				{
				unsigned long* ptrSource = (unsigned long*)cmDTaddr[dt];
				unsigned long* ptrSink = (unsigned long*)addrtemp;
				ptrSink[0] = ptrSource[0];
				}
			}
			break;	
		case 4:
			switch(cmDTtypeOut[dt])
			{
				case 1: 
				{
					float var = *(float*)cmDTaddr[dt];
					if(cmDToffset[dt] != 0)
						var += cmDToffset[dt];
					if(cmDTscale[dt] != 0)
						var *= cmDTscale[dt];
					//unsigned char* ptrSource = (unsigned cha*)cmDTaddr[dt];
					unsigned char* ptrSink = (unsigned char*)addrtemp;		
					ptrSink[0] = limit_u8(var);//ptrSource[0];			
				}
				break;
				case 2: 
				{			
					if(((addrtemp%2) ==0) && ((cmDTaddr[dt]%2) ==0))
					{
						float var = *(float*)cmDTaddr[dt];
						if(cmDToffset[dt] != 0)
							var += cmDToffset[dt];
						if(cmDTscale[dt] != 0)
							var *= cmDTscale[dt];
						//unsigned char* ptrSource = (unsigned cha*)cmDTaddr[dt];
						unsigned short* ptrSink = (unsigned short*)addrtemp;		
						ptrSink[0] = limit_u16(var);//ptrSource[0];		
					}
				}
				break;		
				case 3: 
				{				
					if(((addrtemp%4) ==0) && ((cmDTaddr[dt]%4) ==0))
					{
						float var = *(float*)cmDTaddr[dt];
						if(cmDToffset[dt] != 0)
							var += cmDToffset[dt];
						if(cmDTscale[dt] != 0)
							var *= cmDTscale[dt];
						//unsigned char* ptrSource = (unsigned cha*)cmDTaddr[dt];
						unsigned long* ptrSink = (unsigned long*)addrtemp;		
						ptrSink[0] = limit_u32(var);//ptrSource[0];		
					}
				}
				break;
				case 4: 
				{				
					if(((addrtemp%4) ==0) && ((cmDTaddr[dt]%4) ==0))
					{
						float* ptrSource = (float*)cmDTaddr[dt];
						float* ptrSink = (float*)addrtemp;
						ptrSink[0] = ptrSource[0];
						if(cmDToffset[0] != 0)
							ptrSink[0] += cmDToffset[0];
						if(cmDTscale[0] != 0)
							ptrSink[0] *= cmDTscale[0];
					}
				}
				break;
			}
			break;		
		default: 
			break;	
		}		
	}
}

void memCopyProtected(unsigned long src, unsigned long dest, unsigned char type)
{
	switch(type)
	{
		case 1: 			
			{
				unsigned char* ptrSource = (unsigned char*)src;
				unsigned char* ptrSink = (unsigned char*)dest;		
				ptrSink[0] = ptrSource[0];			
			}
			break;
		case 2: 
			{				
			if(((src%2) ==0) && ((dest%2) ==0))
				{
				unsigned short* ptrSource = (unsigned short*)src;
				unsigned short* ptrSink = (unsigned short*)dest;
				ptrSink[0] = ptrSource[0];
				}
			}
			break;		
		case 3: 
			{			
			if(((src%4) ==0) && ((dest%4) ==0))
				{
				unsigned long* ptrSource = (unsigned long*)src;
				unsigned long* ptrSink = (unsigned long*)dest;	
				ptrSink[0] = ptrSource[0];
				}
			}
			break;				
		default: 
			break;	
	}	
}

void updateCanRaw(unsigned long src, unsigned char type, unsigned char ccm, unsigned char bytePos)
{
	unsigned long dest;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	if(src >= 0xFFFF0000 || src < 0x000FFFFF)
	{		
		dest = 0xFFFFD100;
		if(ccmGroup[ccm].bus == 0x01)
			dest += 0x800;
		dest += 0x020*(unsigned long)(ccmGroup[ccm].mailBox&0x1F);
		dest += 0x08; //Move to Data Field
		dest += (unsigned long)bytePos&0x07;	//Offset in Data Field
		memCopyProtected(src,dest,type);	
	}
}

void sendCanMessage(unsigned char ccm)
{
	unsigned short* ptr;
	unsigned char* ptrMB;	
	unsigned short tmp;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	ptrMB = (unsigned char*)(0xFFFFD100 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x20*(ccmGroup[ccm].mailBox&0x1f) + 0x04);			
	if((ptrMB[0]&0x07) == 0x00) //Check if Mailbox is a TX
	{		
		if(ccmGroup[ccm].mailBox>=16)
			{
			tmp = (unsigned short)ccmGroup[ccm].mailBox-16;
			ptr = (unsigned short*)(0xFFFFD000 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x20);	//This is 	TXPR1
			}
		else
			{
			tmp = (unsigned short)ccmGroup[ccm].mailBox;
			ptr = (unsigned short*)(0xFFFFD000 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x22);	//This is 	TXPR0	
			}
		ptr[0] = shC[tmp];
	}
}

void recieveCanMessage(unsigned char ccm)
{
	unsigned short* ptr;
	unsigned char* ptrMB;	
	unsigned short tmp;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	ptrMB = (unsigned char*)(0xFFFFD100 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x20*(ccmGroup[ccm].mailBox&0x1f) + 0x04);			
	if((ptrMB[0]&0x07) == 0x03) //Check if Mailbox is a TX
	{		
		if(ccmGroup[ccm].mailBox>=16)
		{
			tmp = (unsigned short)ccmGroup[ccm].mailBox-16;
			ptr = (unsigned short*)(0xFFFFD000 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x40);	//This is 	RXPR1
		}
		else
		{
			tmp = (unsigned short)ccmGroup[ccm].mailBox;
			ptr = (unsigned short*)(0xFFFFD000 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x42);	//This is 	RXPR0	
		}	
		if((ptr[0] & shC[tmp]) >0)//returnShifter(tmp)) >0)
		{	
			ptr[0] = shC[tmp];
				
			if(ccmGroup[ccm].callback >0)
			{
				ptrMB = (unsigned char*)(0xFFFFD100 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x20*(ccmGroup[ccm].mailBox&0x1f) + 0x08);		
				if(ccmGroup[ccm].callback%4 == 0) //Only call it if its U32 alligned
				{
					void (*callbackPtr)(unsigned char*) = (void*)ccmGroup[ccm].callback;
					(*callbackPtr)(ptrMB);					
				}
			}			
		}		
	}
}






void canCallbackRamTune(unsigned char* data)
{
	unsigned char* ptrC;
	unsigned short* ptrS;
	unsigned long* ptrL;
	unsigned long addr;
	switch(data[0]&0xF0)
	{
		case 0x50 :	//RAM Write	
		{
			unsigned long retWord = 0;
			addr = 0xFFFF0000;
			addr += (unsigned long)data[1]*256;
			addr += (unsigned long)data[2];						
			switch(data[3])
			{			
				case 1:		// Write to 1 byte
					if((addr%1)==0)
					{
						ptrC = (unsigned char*)addr;
						ptrC[0] = data[4];	
						retWord = addr&0x00FFFFFF+0xD1000000;								
					}
					break;
				case 2:		// Write to 2 byte
					if((addr%2)==0)
					{
						ptrS = (unsigned short*)addr;
						ptrS[0] = (unsigned short)(data[4]*256+data[5]);			
						retWord = addr&0x00FFFFFF+0xD2000000;								
					}
					break;
				case 3:		// Write to 4 byte
					if((addr%4)==0)
					{
						ptrL = (unsigned long*)addr;
						ptrL[0] = (unsigned long)(data[4]*256*256*256+data[5]*256*256+data[6]*256+data[7]);			
						retWord = addr&0x00FFFFFF+0xD3000000;										
					}
					break;
				default :
					break;				
			}
			updateCanRaw((unsigned long)&retWord, dtLong, RAMETUNE_RESPONSE_CCM, 0);										
			sendCanMessage(RAMETUNE_RESPONSE_CCM);	
		}		
		break;
		case 0x60 :		//RAM Read
		{
			unsigned long retWord = 0;
			addr = (unsigned long)(0xFFFF0000 + (unsigned long)data[1]*256 + (unsigned long)data[2]);
			switch(data[3])
			{	
				unsigned long retWord;				
				case 1:		// Write to 1 byte
					if((addr%1)==0)
					{	
						retWord = addr&0x00FFFFFF+0xE1000000;										
						updateCanRaw(addr, dtChar, RAMETUNE_RESPONSE_CCM, 4);						
					}
					break;
				case 2:		// Write to 2 byte
					if((addr%2)==0)
					{
						retWord = addr&0x00FFFFFF+0xE1000000;								
						updateCanRaw(addr, dtShort, RAMETUNE_RESPONSE_CCM, 4);						
					}
					break;
				case 3:		// Write to 4 byte
					if((addr%4)==0)
					{
						retWord = addr&0x00FFFFFF+0xE1000000;								
						updateCanRaw(addr, dtLong, RAMETUNE_RESPONSE_CCM, 4);
					}
				break;
				default: break;
			}
			updateCanRaw((unsigned long)&retWord, dtLong, RAMETUNE_RESPONSE_CCM, 0);				
			sendCanMessage(RAMETUNE_RESPONSE_CCM);	
		}												
		break;
		case 0x70 :		//Flash Read
		{
			unsigned long retWord = 0;
			addr = (unsigned long)(0x00000000 + (unsigned long)(data[0]&0x0F)*256*256 + (unsigned long)data[1]*256 + (unsigned long)data[2]);
			switch(data[3])
			{
				case 1:		// Write to 1 byte
					if((addr%1)==0)
					{			
						retWord = addr+0xF1000000;								
						updateCanRaw(addr, dtChar, RAMETUNE_RESPONSE_CCM, 4);			
					}
					break;
				case 2:		// Write to 2 byte
					if((addr%2)==0)
					{
						retWord = addr+0xF2000000;								
						updateCanRaw(addr, dtShort, RAMETUNE_RESPONSE_CCM, 4);			
					}
					break;
				case 3:		// Write to 4 byte
					if((addr%4)==0)
					{
						retWord = addr+0xF3000000;								
						updateCanRaw(addr, dtLong, RAMETUNE_RESPONSE_CCM, 4);			
					}
				break;
				default: break;
			}
			updateCanRaw((unsigned long)&retWord, dtLong, RAMETUNE_RESPONSE_CCM, 0);
			sendCanMessage(RAMETUNE_RESPONSE_CCM);													
		}
		default: break;
	}
}
 
////////////////////
// *** Setup Function to load Mailbox settings to CPU Can Mailboxes
//////////////////// 
void CanSetup()
{
	unsigned char i = 0;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);	
	while(i< ccmCount)
	{
		if(ccmGroup[i].mcs <= 7)
		{
			setupMailBoxStruct(&ccmGroup[i]);
		}	
		i++;
	}
	pRamVariables.initFunctionRun = 1;
	//#if RACEGRADE_KEYPAD_HACKS
	//	//SETUP the CANOPN Broadcast Packet to start the RaceGrade Module
	//	unsigned short setupCOP = 0x010A;
	//	updateCanRaw((unsigned long)&setupCOP,dtShort,RACEGRADE_CANOPEN_START,0);
	//#endif
}


////////////////////
// *** needs to be called every 1mSec
// Checks each Transmit slot to see if it needs to be sent
// Check every Receive slow to see if there is new data
// Calls the RX Callback in case it is configured to run
////////////////////
void CustomCanService()
{
	unsigned char i = 0;
	unsigned char j = 0;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	unsigned char* ptrMB = (unsigned char*)(0xFFFFD100 + 0x800*(ccmGroup[0].bus&0x01) + 0x20*(ccmGroup[0].mailBox&0x1f) + 0x04);		
	
	//Run Can Setup in Case the Init has not run, in case the first mailbox is not setup
	if((pRamVariables.initFunctionRun != 1) || (ccmGroup[0].mcs != (ptrMB[0]&0x07)))
	{
		CanSetup();
	}

	//Send all Possible Messages
	i=0;
	while(i<ccmCount)
	{
		if((ccmGroup[i].mcs == mcsTrans) && (ccmGroup[i].rate>0)) //Send if MCS is set to 0, and has a periodic rate greater than 0
		{
			if(++pRamVariables.ccmSendTimers[i] >= ccmGroup[i].rate) //Send message once 1mSec timer has rolled up
			{
				////////////
				//Update all possible DataTransfers, stop when list is seen to be not configured	
				j=0;
				while(j<cmDTCount)
				{
					if(cmDTtypeIn[j] > 0) //update if a Type is defined
					{
						if(cmDTccm[j] == i)	//update DT if it needs to be sent
							updateCanDT(j);
					}
					else
					{
						break;
					}
					j++;
				}
				
				/////////////
				sendCanMessage(i);
				pRamVariables.ccmSendTimers[i] = 0; //rest timer
			}
		}			
		else if(ccmGroup[i].mcs == mcsReceive) //recieve
		{
			recieveCanMessage(i);	
		}
		i++;
	}
	
	#ifdef RCP_CAN
	if(rcpStreamEnabled==1)
		rcp_frame_manager();
	#endif
}
#endif