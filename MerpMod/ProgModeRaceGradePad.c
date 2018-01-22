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

#include "EcuHacks.h"

#if PROG_MODE
// Constants need to be declared as 'extern' with their values defined in the 
// function body or in an external asm file.  This is a convoluted way to 
// declare and define variables, but the standard approach causes the compiler
// to generate references to addresses in another segment, which makes it 
// harder to stitch this code into the ECU code.  
// 
// I suspect that turning on compiler optimizations might might cause the 
// compiler to generate the sort of code we want for constants and RAM 
// variables, however other optimizations also make the code harder to verify
// when stepping through it one instruction at a time.  For now I'd much 
// rather have code that's very easy to verify (and verify with the highest
// possible confidence), but at some point it might be worthwhile to turn on
// optimizations and see what happens.

// This is the function that will use speed-density math to compute the MAF
// value that will be returned to the rest of the ECU.  The function needs to
// be declared with the section attribute before it is actually defined, in 
// order to tell the compiler and linker which segment (address range) to put
// it in.

// ProgModeMain function
// This is hooked on a fixed timer that runs all the time immediately after powering up the car
//
/*

	Menu Items:
	//TODO IMPLEMENT VALET MODE FIRST!1: Valet Mode Select
	2: Map Switching
	3: Map Blending
	4: LC Adjust
	//TODO9: ECU Reset
	//TODO: Injector hack

	//LOW PRIORITY STUFF
	6: LC Timing Retard Adjust
	8: SD Mode Select

	*/

#define LED_STEP 24
#define PROG_MODE_COUNT 6

#define BLEND_MAX 1.0f
#define BLEND_MIN 0.0f

#define IAM_MIN 0
#ifdef pIam4
#define IAM_MAX 1.0f
#define IAM_STEP 0.125
#else
#define IAM_MAX 16
#define IAM_STEP 2
#endif

void raceGradeKeyPadCallback(unsigned char* data)
{
	unsigned char i = 0;
	unsigned char statenew = 0;
	while(i < (rgButtonCount-1)) //9th button is a holder for a null button
	{
		statenew = ((data[0]&shC[i]) == shC[i]) ? 1 : 0;
		if(statenew>pRamVariables.buttons[i].state)
		{
			pRamVariables.buttons[i].edgeDetect = edgeRising;
		}
		else if(statenew < pRamVariables.buttons[i].state)
		{
			pRamVariables.buttons[i].edgeDetect = edgeFailing;
		}
		else
		{
			pRamVariables.buttons[i].edgeDetect = edgeNA;
		}
		pRamVariables.buttons[i].state = statenew;
		pRamVariables.buttons[i].led = 0;
		i++;	
	}
	
	#if PROG_MODE
		ProgModeMain();
	#endif
	
	unsigned long leds = 0;
	unsigned long ledTemp = 0;
	i=0;
	while(i<(rgButtonCount-1))
	{
		ledTemp = ((unsigned long)(pRamVariables.buttons[i].led&0x07)*shC[i*3]);
		leds += ledTemp;
		i++;	
	}
	
	//endian Swap the LED fields
	ledTemp = ((leds&0xFF)<<24) + ((leds>>8&0xFF)<<16) + ((leds>>16&0xFF)<<8);
	updateCanRaw((unsigned long)&ledTemp,dtLong,RACEGRADE_LED_CCM,0);
	sendCanMessage(RACEGRADE_LED_CCM);
}

void ProgModeButtonToggled(unsigned char toggle)
{
	if(toggle==1)
	{
		pRamVariables.ProgModeCurrentMode++;
		if(pRamVariables.ProgModeCurrentMode > PROG_MODE_COUNT)
			pRamVariables.ProgModeCurrentMode = 0;
	}

}

void ProgMode_Button_Blend()
{
	if(pRamVariables.buttons[rgButtonEthanolSource].edgeDetect == 1)
	{	
		pRamVariables.BlendMode ^= 0x01;
	}
	if(pRamVariables.BlendMode == 0) 
		pRamVariables.buttons[rgButtonEthanolSource].led = 1; 
	else 
		pRamVariables.buttons[rgButtonEthanolSource].led = 0;
}

void ProgMode_Button_Valet()
{
	//Button 1 - Valet Mode
	if(pRamVariables.buttons[rgButtonValetSource].edgeDetect == 1)
	{
		pRamVariables.ValetMode ^= 0x01;
	}
	if(pRamVariables.ValetMode == ValetModeDisabled) 
		pRamVariables.buttons[rgButtonValetSource].led = 0;
	else 
		pRamVariables.buttons[rgButtonValetSource].led = 4;	
}

void ProgMode_Button_PLSL()
{
//Button 6 - PLSL Mode
	if(pRamVariables.buttons[rgButtonPLSLSource].edgeDetect == 1)
	{		
		if((pRamVariables.bPLSLRequest == 0) && (*pVehicleSpeed < NPLSL_RequestMax))
			pRamVariables.bPLSLRequest = 1;
		else			
			pRamVariables.bPLSLRequest = 0;			
	}
	if(pRamVariables.bPLSLRequest == 1) 
		if(pRamVariables.bPLSLcutting ==1)
			pRamVariables.buttons[rgButtonPLSLSource].led = 5; //Active and Cutting
		else
			pRamVariables.buttons[rgButtonPLSLSource].led = 1;	//Active
	else 
		pRamVariables.buttons[rgButtonPLSLSource].led = 0;	
}

void ProgMode_Button_CutTestPattern()
{
//Button 9 - CutTest Mode
	if(pRamVariables.buttons[rgButtonCutTestSource].edgeDetect == 1)
	{		
		if(pRamVariables.cutPatternAsk == 0)
			pRamVariables.cutPatternAsk = 1;
		else			
			pRamVariables.cutPatternAsk = 0;			
	}
	if(pRamVariables.nINJCutPattern != 0) 		
		pRamVariables.buttons[rgButtonCutTestSource].led = 4; //Active and Cutting		
	else 
		pRamVariables.buttons[rgButtonCutTestSource].led = 0;	
}

void ProgMode_Button_FFS()
{
#if REVLIM_HACKS
	//Button 4 - Flat Foot Shift Mode pRamVariables.FlatFootShiftMode
	if(pRamVariables.buttons[rgButtonFFSSource].edgeDetect == 1)
	{			
		if(pRamVariables.FlatFootShiftMode<2)
			pRamVariables.FlatFootShiftMode += 0x01;
		else
			pRamVariables.FlatFootShiftMode = 0;
	}	
	if(pRamVariables.FlatFootShiftMode == 0) 
		pRamVariables.buttons[rgButtonFFSSource].led = 0; 
	else if(pRamVariables.FlatFootShiftMode == 1) 
		pRamVariables.buttons[rgButtonFFSSource].led = 1;
	else if(pRamVariables.FlatFootShiftMode == 2) 
		pRamVariables.buttons[rgButtonFFSSource].led = 2;
			
	//Light up 3rd LED when FFS is engaged	
	if(pRamVariables.FFSEngaged >= 1)
		pRamVariables.buttons[rgButtonFFSSource].led |= 0x04;
#endif
}


void ProgMode_Button_Failsafe()
{		
	//Button 5 - Failsafe Button
	if(pRamVariables.buttons[rgButtonFailsafeSource].edgeDetect == 1)	
	{
		*pIAM = IAM_MIN;
#if REVLIM_HACKS
		pRamVariables.FlatFootShiftMode = 0;
#endif
		pRamVariables.bPLSLRequest = 0;
#if SWITCH_HACKS
		pRamVariables.MapSwitch = DefaultMapSwitch;
		pRamVariables.MapBlendRatio = DefaultMapBlendRatio;
		pRamVariables.BlendMode = 1; //Manual Mode
		pRamVariables.VPLSL_Adjust = 0;
		pRamVariables.AFRSource = AFRModeStock;
#endif
		pRamVariables.buttons[rgButtonFailsafeSource].led = 7; 
	}
	else
		pRamVariables.buttons[rgButtonFailsafeSource].led = 0; 
}

void ProgModeMain()
{
	pRamVariables.ProgModeEnable = 1;
	
	//Button 0,0 - Blend Overide Mode
	ProgMode_Button_Blend();
	
	//Button 0,1 - Valet Mode
	ProgMode_Button_Valet();
	
	//Button 1,0 - FFS Mode
	ProgMode_Button_FFS();
	
	//Button 1,1 - Failsafge Mode
	ProgMode_Button_Failsafe();
	
	//Button 1,2 - PLSL Mode
	ProgMode_Button_PLSL();
	
	//Button 1,4 - CutTest Mode
	ProgMode_Button_CutTestPattern();
	
			
	//Button 0,2 - Mod Select Toggle	
	ProgModeButtonToggled(pRamVariables.buttons[rgButtonModeSource].edgeDetect);
	switch(pRamVariables.ProgModeCurrentMode)
	{
		case 0:
			asm("nop");
		break;
		
		case 1:			
			ProgModeBlendAdjust();
			pRamVariables.buttons[rgButtonEthanolSource].led = 7;
		break;
		
		case 2:			
			ProgModeAFRSource();
		break;
		
		case 3:
			ProgModeLCAdjust();
			pRamVariables.buttons[rgButtonFFSSource].led = 7;
		break;
		
		case 4:
			ProgModeIAMAdjust();
			pRamVariables.buttons[rgButtonFailsafeSource].led = 7;
		break;	
		
		case 5:
			ProgModePLSLAdjust();
			pRamVariables.buttons[rgButtonPLSLSource].led = 7;
		break;
		
		case 6:
			ProgModeRaceGradeBackLight();
		break;
		
		default:
			pRamVariables.ProgModeCurrentMode = 0;
		break;
	}	
	
	pRamVariables.buttons[rgButtonModeSource].led = pRamVariables.ProgModeCurrentMode;
	if(pRamVariables.ProgModeCurrentMode>0)
	{
		pRamVariables.buttons[rgButtonUpSource].led = pRamVariables.ProgModeValueFlashes&0x07;
		pRamVariables.buttons[rgButtonDownSource].led = pRamVariables.ProgModeValueFlashes/8;
	}
	else
	{
		pRamVariables.buttons[rgButtonUpSource].led = 0;
		pRamVariables.buttons[rgButtonDownSource].led = 0;
	}	
}

void ProgModeAFRSource()
{
	if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
	{	
		if(pRamVariables.AFRSource >= AFRModeWide)
			pRamVariables.AFRSource = AFRModeWide;
		else
			pRamVariables.AFRSource++;
	}
	else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
	{
		if(pRamVariables.AFRSource == AFRModeStock )
			pRamVariables.AFRSource = AFRModeStock;
		else
			pRamVariables.AFRSource--;
	}	
	pRamVariables.ProgModeValue = pRamVariables.AFRSource+1;
	pRamVariables.ProgModeValueFlashes = pRamVariables.AFRSource;
}

void ProgModeMapSwitch()
{
#if SWITCH_HACKS
	if(MapSwitchInput == InputModeRaceGradePad)
	{	
		if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
		{	
			if(pRamVariables.MapSwitch >= 3)
				pRamVariables.MapSwitch = 3;
			else
				pRamVariables.MapSwitch++;
		}
		else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
		{
			if(pRamVariables.MapSwitch == 1 )
				pRamVariables.MapSwitch = 1;
			else
				pRamVariables.MapSwitch--;
		}
	}
	pRamVariables.ProgModeValue = pRamVariables.MapSwitch;
	pRamVariables.ProgModeValueFlashes = pRamVariables.MapSwitch;
#else
	pRamVariables.ProgModeValue = 0.0f;
	pRamVariables.ProgModeValueFlashes = 0;
#endif
}

void ProgModeBlendAdjust()
{
#if SWITCH_HACKS
	if(pRamVariables.BlendMode == 1)
	{
		if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
		{	
			if(pRamVariables.MapBlendRatio > (BLEND_MAX - rgBLEND_STEP - 0.01f))
				pRamVariables.MapBlendRatio = BLEND_MAX;
			else
				pRamVariables.MapBlendRatio+= rgBLEND_STEP;
		}
		else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
		{
			if(pRamVariables.MapBlendRatio < (BLEND_MIN + rgBLEND_STEP + 0.01f))
				pRamVariables.MapBlendRatio = BLEND_MIN;//Hard limit, does not cycle to top again.
			else
				pRamVariables.MapBlendRatio-= rgBLEND_STEP;
		}
	}
	pRamVariables.ProgModeValue = pRamVariables.MapBlendRatio + 1;
	pRamVariables.ProgModeValueFlashes = (unsigned char)(pRamVariables.MapBlendRatio*8);
#else
	pRamVariables.ProgModeValue = 0.0f;
	pRamVariables.ProgModeValueFlashes = 0;
#endif
}

void ProgModeBlendMode()
{
	if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
	{	
		if(pRamVariables.BlendMode <=0)
			pRamVariables.BlendMode = 1;
	}
	else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
	{
		if(pRamVariables.BlendMode >= 1 )
			pRamVariables.BlendMode = 0;
	}
	pRamVariables.ProgModeValue = pRamVariables.BlendMode;
	pRamVariables.ProgModeValueFlashes = pRamVariables.BlendMode;
}

void ProgModeLCAdjust()
{
#if REVLIM_HACKS
#if !AUTO_TRANS
	if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
	{	
		if(pRamVariables.LaunchControlCut < pRamVariables.RedLineCut)
			pRamVariables.LaunchControlCut+= rgLC_STEP;
	}
	else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
	{
		if(pRamVariables.LaunchControlCut > rgLC_MIN)
			pRamVariables.LaunchControlCut-= rgLC_STEP;//Hard limit, does not cycle to top again.
		else
			pRamVariables.LaunchControlCut = rgLC_MIN;
	}
	
	pRamVariables.ProgModeValue = pRamVariables.LaunchControlCut;
	pRamVariables.ProgModeValueFlashes = (unsigned char)((pRamVariables.LaunchControlCut / rgLC_STEP) - (unsigned char)(rgLC_MIN / rgLC_STEP));
#else
	pRamVariables.ProgModeValue = 0.0f;
	pRamVariables.ProgModeValueFlashes = 0;
#endif
#endif
}

void ProgModePLSLAdjust()
{
#if REVLIM_HACKS
	if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
	{	
		if((pRamVariables.VPLSL_Adjust + rgPLSL[1]) <= rgPLSL[2])
			pRamVariables.VPLSL_Adjust += rgPLSL[1];
		else
			pRamVariables.VPLSL_Adjust = rgPLSL[2];
	}
	else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
	{
		if((pRamVariables.VPLSL_Adjust - rgPLSL[1]) >= rgPLSL[0])
			pRamVariables.VPLSL_Adjust -= rgPLSL[1];//Hard limit, does not cycle to top again.
		else
			pRamVariables.VPLSL_Adjust = rgPLSL[0];
	}
	
	pRamVariables.ProgModeValue = pRamVariables.LaunchControlCut;
	pRamVariables.ProgModeValueFlashes = (unsigned char)((pRamVariables.LaunchControlCut / rgLC_STEP) - (unsigned char)(rgLC_MIN / rgLC_STEP));
#else
	pRamVariables.ProgModeValue = 0.0f;
	pRamVariables.ProgModeValueFlashes = 0;
#endif
}

void ProgModeIAMAdjust()
{
	if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
	{	
		if(*pIAM < IAM_MAX - IAM_STEP)
			*pIAM += IAM_STEP;
		else
			*pIAM = IAM_MAX;
	}
	else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
	{
		if(IAM > IAM_MIN + IAM_STEP)
			*pIAM -= IAM_STEP;
		else
			*pIAM = IAM_MIN;
	}
	pRamVariables.ProgModeValue = *pIAM;
	pRamVariables.ProgModeValueFlashes = (unsigned char)(*pIAM*8);
}

void ProgModeValetMode()
{
	if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
	{	
		if(pRamVariables.ValetMode <=0)
			pRamVariables.ValetMode = 1;
	}
	else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
	{
		if(pRamVariables.ValetMode >= 1 )
			pRamVariables.ValetMode = 0;
	}
	pRamVariables.ProgModeValue = pRamVariables.ValetMode;
	pRamVariables.ProgModeValueFlashes = pRamVariables.ValetMode;
}


void ProgModeRaceGradeBackLight()
{
	if(pRamVariables.buttons[rgButtonUpSource].edgeDetect == 1)
	{	
		if(pRamVariables.rgBackLight < (255-LED_STEP))
			pRamVariables.rgBackLight += LED_STEP;
		else
			pRamVariables.rgBackLight = 255;
	}
	else if(pRamVariables.buttons[rgButtonDownSource].edgeDetect == 1)
	{
		if(pRamVariables.rgBackLight > LED_STEP)
			pRamVariables.rgBackLight-= LED_STEP;//Hard limit, does not cycle to top again.
		else
			pRamVariables.rgBackLight = 0;
	}
	pRamVariables.ProgModeValue = pRamVariables.rgBackLight;
	pRamVariables.ProgModeValueFlashes = (unsigned char)(pRamVariables.rgBackLight/32);
}
#endif