
#include "EcuHacks.h"


RamVariables pRamVariables  __attribute__ ((section ("RamHole")));
/////////////////
//Constants
/////////////////
#if CAN_HACKS

unsigned char rgButtonEthanolSource CANDATA = 0;
unsigned char rgButtonValetSource CANDATA = 1;
unsigned char rgButtonFFSSource CANDATA = 4;
unsigned char rgButtonFailsafeSource CANDATA = 5;
unsigned char rgButtonPLSLSource CANDATA = 6;
unsigned char rgButtonModeSource CANDATA = 2;
unsigned char rgButtonUpSource CANDATA = 3;
unsigned char rgButtonDownSource CANDATA = 7;


unsigned char rcpStreamEnabled CANDATA = 1;

unsigned long rcpCAN_ID_m0 CANDATA = 0x700;
unsigned long rcpCAN_ID_m1 CANDATA = 0x701;
unsigned long rcpCAN_ID_m2 CANDATA = 0x702;
unsigned long rcpCAN_ID_m3 CANDATA = 0x703;
unsigned long rcpCAN_ID_m4 CANDATA = 0x704;
unsigned long rcpCAN_ID_m5 CANDATA = 0x705;

#if REVLIM_HACKS
	float rgPLSL[3] CANDATA = {-30.0f, 2.0f,30.0f};
#endif

#if BOOST_HACKS
	float rgBoost[3] CANDATA = {-155.25, 25.875,155.25};
	float rWGmod[3] CANDATA = {-.3, 0.1, 1};	
#endif

float rgLC_MIN CANDATA = 2000.0f;
float rgLC_STEP CANDATA = 250.0f;
float rgBLEND_STEP CANDATA = 0.025f;

CanMessageSetupStruct ccm00 CANDATA = {.id = 0x506, .ext = 0,	.dlc = 3,	.bus = 0,	.mailBox = 19,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&raceGradeKeyPadCallback};
CanMessageSetupStruct ccm01 CANDATA = {.id = 0x507,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 20,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0}; //RaceGrade Keypad LEDS
CanMessageSetupStruct ccm02 CANDATA = {.id = 0x508,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 21,	.mcs = mcsTrans, 	.nmc = 0, .rate = 200, .callback = 0}; //RaceGrade BackLights
#if CAN_BRAKE_PEDAL
	CanMessageSetupStruct ccm03 CANDATA = {.id = 0x511,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 22,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackBUIbrakes};
	CanMessageSetupStruct ccm04 CANDATA = {.id = 0x080,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 23,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackVDCaccel};
#else
	CanMessageSetupStruct ccm03 CANDATA = {.id = 0x720,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 22,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackRamTune};
	CanMessageSetupStruct ccm04 CANDATA = {.id = 0x728,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 23,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0}; //Ram Response Message
#endif
CanMessageSetupStruct ccm05 CANDATA = {.id = 0x180, .ext = 1,	.dlc = 8,	.bus = 0,	.mailBox = 24,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackAEMwideband};
CanMessageSetupStruct ccm06 CANDATA = {.id = 0x710,	.ext = 0,	.dlc = 4,	.bus = 0,	.mailBox = 25,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackMK3e85Packet};
//CanMessageSetupStruct *ccmGroup[8] CANDATA;// = {&ccm00,&ccm01,&ccm02,&ccm03,&ccm04,&ccm05,&ccm06,&ccm07};

unsigned char dataLinkedInRam  __attribute__ ((section ("RamHole")));


unsigned long cmDTaddr[cmDTCount] CANDATA = {
	(unsigned long)&pRamVariables.rgBackLight,(unsigned long)&pRamVariables.rgBackLight,(unsigned long)pCrankFuelFirstSetorSecond,(unsigned long)pCrankFuelABC,(unsigned long)pCrankFuelPulse
	};
	
unsigned char cmDTtypeIn[cmDTCount] CANDATA = {
	dtChar,dtChar,dtChar,dtChar,dtFloat};

unsigned char cmDTtypeOut[cmDTCount] CANDATA = {
	dtChar,dtChar,dtChar,dtChar,dtShort};
	
unsigned char cmDTccm[cmDTCount] CANDATA = {
	2,2,2,2,2};
	
unsigned char cmDTpos[cmDTCount] CANDATA = {
	0,2,4,5,6};
	
float cmDTscale[cmDTCount] CANDATA = {
	0,0,0,0,0.1};
	
float cmDToffset[cmDTCount] CANDATA = {
	0,0,0,0,0};

#endif