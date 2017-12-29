
#include "EcuHacks.h"


RamVariables pRamVariables  __attribute__ ((section ("RamHole")));
/////////////////
//Constants
/////////////////
#if CAN_HACKS

unsigned char rgButtonEthanolSource CANDATA = 0;
unsigned char rgButtonValetSource CANDATA = 1;
unsigned char rgButtonFFSSource CANDATA = 4;
unsigned char rgButtonBailSource CANDATA = 5;
unsigned char rgButtonModeSource CANDATA = 2;
unsigned char rgButtonUpSource CANDATA = 3;
unsigned char rgButtonDownSource CANDATA = 7;

float rgLC_MIN CANDATA = 2000.0f;
float rgLC_STEP CANDATA = 250.0f;
float rgBLEND_STEP CANDATA = 0.025f;

CanMessageSetupStruct ccm00 CANDATA = {.id = 0x506, .ext = 0,	.dlc = 3,	.bus = 0,	.mailBox = 19,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&raceGradeKeyPadCallback};
CanMessageSetupStruct ccm01 CANDATA = {.id = 0x507,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 20,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0}; //RaceGrade Keypad LEDS
CanMessageSetupStruct ccm02 CANDATA = {.id = 0x508,	.ext = 0,	.dlc = 4,	.bus = 0,	.mailBox = 21,	.mcs = mcsTrans, 	.nmc = 0, .rate = 200, .callback = 0}; //RaceGrade BackLights
CanMessageSetupStruct ccm03 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 2,	.bus = 0,	.mailBox = 22,	.mcs = mcsTrans,    .nmc = 0, .rate =1000, .callback = 0}; //RaceGrade Keypad INIT CANOPEN
CanMessageSetupStruct ccm04 CANDATA = {.id = 0x720,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 23,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackRamTune};
CanMessageSetupStruct ccm05 CANDATA = {.id = 0x728,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 24,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0};
CanMessageSetupStruct ccm06 CANDATA = {.id = 0x180, .ext = 1,	.dlc = 8,	.bus = 0,	.mailBox = 25,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackAEMwideband};
CanMessageSetupStruct ccm07 CANDATA = {.id = 0x710,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 26,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackMK3e85Packet};
CanMessageSetupStruct ccm08 CANDATA = {.id = 0x708,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 27,	.mcs = mcsTrans, 	.nmc = 0, .rate =  50, .callback = 0};
CanMessageSetupStruct ccm09 CANDATA = {.id = 0x709,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 28,	.mcs = mcsTrans, 	.nmc = 0, .rate =  10, .callback = 0};
CanMessageSetupStruct ccm10 CANDATA = {.id = 0x70A,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 29,	.mcs = mcsTrans, 	.nmc = 0, .rate =  10, .callback = 0};
CanMessageSetupStruct ccm11 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 30,	.mcs = mcsTrans,    .nmc = 0, .rate =   0, .callback = 0};
//CanMessageSetupStruct *ccmGroup[8] CANDATA;// = {&ccm00,&ccm01,&ccm02,&ccm03,&ccm04,&ccm05,&ccm06,&ccm07};

unsigned char dataLinkedInRam  __attribute__ ((section ("RamHole")));


unsigned long cmDTaddr[cmDTCount] CANDATA = {
	(unsigned long)&pRamVariables.rgBackLight,(unsigned long)&pRamVariables.rgBackLight,
	(unsigned long)&pRamVariables.FFSEngaged, (unsigned long)&pRamVariables.FlatFootShiftMode, (unsigned long)&pRamVariables.RevLimCut, (unsigned long)&pRamVariables.RevLimResume, (unsigned long)&pRamVariables.LCEngaged,
	(unsigned long)&pRamVariables.BlendMode, (unsigned long)&pRamVariables.ValetMode, (unsigned long)&pRamVariables.LaunchControlCut, (unsigned long)&pRamVariables.MapBlendRatio, (unsigned long)&pRamVariables.MapSwitch, (unsigned long)&pRamVariables.MafFromSpeedDensity,
	(unsigned long)&pRamVariables.InjectorScaling};
	
unsigned char cmDTtypeIn[cmDTCount] CANDATA = {
	dtChar,dtChar,
	dtChar,dtChar,dtFloat,dtFloat,dtChar,
	dtChar,dtChar,dtFloat,dtFloat,dtChar,dtFloat,
	dtFloat};

unsigned char cmDTtypeOut[cmDTCount] CANDATA = {
	dtChar,dtChar,
	dtChar,dtChar,dtShort,dtShort,dtChar,
	dtChar,dtChar,dtShort,dtChar,dtChar,dtShort,
	dtShort};
	
unsigned char cmDTccm[cmDTCount] CANDATA = {
	2,2,
	8,8,8,8,8,
	9,9,9,9,9,9,
	10};
	
unsigned char cmDTpos[cmDTCount] CANDATA = {
	0,2,
	0,1,2,4,6,
	0,1,2,4,5,6,
	0};
	
float cmDTscale[cmDTCount] CANDATA = {
	0,0,
	0,0,4,4,0,
	0,0,4,2.55,0,10,
	0};
	
float cmDToffset[cmDTCount] CANDATA = {
	0,0,
	0,0,0,0,0,
	0,0,0,0,0,0,
	0};

#endif