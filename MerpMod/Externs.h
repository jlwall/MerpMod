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

#include "enums.h"
#include "revLimModel.h"

//////////////////////////
//Function Prototypes
//////////////////////////

#if PORT_LOGGER
void PortLogger() ROMCODE;
#endif



unsigned char TestBrakeSwitch()	ROMCODE;
unsigned char TestClutchSwitch() ROMCODE;
unsigned char TestCruiseResumeSwitch() ROMCODE;
unsigned char TestCruiseCoastSwitch() ROMCODE;
void TestCruiseControlToggles() ROMCODE;

void Initializer()	ROMCODE;
void ClearRamVariables()	ROMCODE;
void PopulateRamVariables()	ROMCODE;
void ResetRamVariables() ROMCODE;
void InitRamVariables() ROMCODE;

void EcuHacksMain() ROMCODE;
void RevLimHook() ROMCODE;

#if INJECTOR_HACKS
void InjectorTrims() ROMCODE;
#endif

float ComputeMassAirFlow(TwoDTable* MafScalingTable, float MafVoltage)  ROMCODE;
float CallSpeedDensityHook()  ROMCODE;
#if CEL_HACKS
void CelDoubleRepeat(unsigned char * CelFlashes1, unsigned char Speed1, unsigned char * CelFlashes2, unsigned char Speed2, unsigned char Delay1, unsigned char Delay2)  ROMCODE;
void CelFlashStart(unsigned char CelFlashes, unsigned char Speed, unsigned char Delay, unsigned char Interrupt)  ROMCODE;
void CelFlash()	ROMCODE;
#endif

#if CAN_HACKS
void CanSetup()	ROMCODE;
void setupMailBox(unsigned char bus, unsigned char mailBox, unsigned short id, unsigned char mcs, unsigned char dlc) ROMCODE;
void updateCanRaw(unsigned long src, unsigned char type, unsigned char ccm, unsigned char bytePos) ROMCODE;
void sendRamTuneMemoryReadRequest(unsigned char type, unsigned long addr) ROMCODE;
void setupMailBoxStruct(CanMessageSetupStruct* cs) ROMCODE;
void sendCanMessage(unsigned char ccm) ROMCODE;
void sendCanMessageDirect(unsigned char buff) ROMCODE;
void recieveCanMessage(unsigned char ccm) ROMCODE;
void updateCanDT(unsigned char dt) ROMCODE;
void CustomCanService() ROMCODE;
//unsigned short returnShifter(unsigned char c) ROMCODE;
void memCopyProtected(unsigned long src, unsigned long dest, unsigned char type) ROMCODE;
void rcpCanMessageSetup(unsigned long id,unsigned short ext, unsigned short dlc, unsigned short bus, unsigned short mailBox) ROMCODE;
#endif

#if RCP_CAN
#define RPCBUF1 26
#define RPCBUF2 27
#define RPCBUF3 28
#define RPCBUF4 29
#define RPCBUF5 30
#define RPCBUF6 31

void rcp_frame_manager() ROMCODE;
void send_frame_0x700() ROMCODE;
void send_frame_0x701() ROMCODE;
void send_frame_0x702() ROMCODE;
void send_frame_0x703() ROMCODE;
void send_frame_0x704() ROMCODE;
void send_frame_0x705() ROMCODE;

void send_frame_0x708() ROMCODE;
void send_frame_0x709() ROMCODE;
void send_frame_0x70A() ROMCODE;

#if CAN_BRAKE_PEDAL
	void canCallbackBUIbrakes(unsigned char* data) ROMCODE;
	void canCallbackVDCaccel(unsigned char* data) ROMCODE;
#endif

extern unsigned long rcpCAN_ID_m0;
extern unsigned long rcpCAN_ID_m1;
extern unsigned long rcpCAN_ID_m2;
extern unsigned long rcpCAN_ID_m3;
extern unsigned long rcpCAN_ID_m4;
extern unsigned long rcpCAN_ID_m5;
#endif

void UpdateInjectorFlow(void) ROMCODE;
void WideBandScaling(void) ROMCODE;
void WGDCHack(void) ROMCODE;
void TargetBoostHack(void) ROMCODE;
void POLFHack()  ROMCODE;
float TimingHack()  ROMCODE;
float Pull2DRamHook(float* table, float xLookup) ROMCODE;
float Pull3DRamHook(float* table, float xLookup, float yLookup) ROMCODE;
void VinCheck() ROMCODE;

void ProgModeMain()  ROMCODE;
void ProgModeButtonToggled(unsigned char) ROMCODE;

extern unsigned char modeMap[];
extern unsigned char modeMapMax;
void ProgModeMapSwitch()  ROMCODE;
void ProgModeBlendAdjust()  ROMCODE;
void ProgModeBlendMode() ROMCODE;
void ProgModeLCAdjust()  ROMCODE;
void ProgModePLSLAdjust() ROMCODE;
void ProgModeIAMAdjust() ROMCODE;
void ProgModeBoostAdjust() ROMCODE;
void ProgModeWGAdjust() ROMCODE;
void ProgModeValetMode() ROMCODE;
void ProgModeAFRSource() ROMCODE;
void ProgModeRaceGradeBackLight() ROMCODE;

void ProgMode_Button_Blend() ROMCODE;
void ProgMode_Button_Valet() ROMCODE;

void ProgMode_Button_FFS() ROMCODE;
void ProgMode_Button_Failsafe() ROMCODE;
void ProgMode_Button_PLSL() ROMCODE;

void LCAdjustCruiseToggled(unsigned char) ROMCODE;

#if !AUTO_TRANS
void SetClutch(int value) __attribute__ ((section ("Misc")));
#endif
void SetBrake(int value) __attribute__ ((section ("Misc")));

float sqrt(float input) ROMCODE;
float Abs(float input) ROMCODE;
unsigned char limit_u8(float input) ROMCODE;
unsigned short limit_u16(float input) ROMCODE;
unsigned long limit_u32(float input) ROMCODE;
float LowPass(float input, float limit) ROMCODE;
float HighPass(float input, float limit) ROMCODE;
unsigned short HighPassShort(unsigned short input, unsigned short limit) ROMCODE;
float BandPass(float input, float lowlim, float highlim) ROMCODE;
int BandPassInt(int input, int lowlim, int highlim) ROMCODE;
unsigned short BandPassShort(unsigned short input, unsigned short lowlim, unsigned short highlim) ROMCODE;
float Smooth(float smoothingFactor, float input, float previous) ROMCODE;


void RevLimCode(void) ROMCODE;
void RevLimReset(void) ROMCODE;

void revLimModel_custom(void) ROMCODE;
void revLimModel_initialize(void) ROMCODE;
uint32_T plook_u32u8_evenckan(uint8_T u, uint8_T bp0, uint8_T bpSpace, uint32_T maxIndex) ROMCODE;

float BlendAndSwitch(TableGroup tg, float xLookup, float yLookup) ROMCODE;
float SwitchSelect(TableSubSet tss, float xLookup, float yLookup) ROMCODE;
void InputUpdate() ROMCODE;
void MapSwitchThresholdCheck(float input) ROMCODE;

//////////////////////////
//Extern Function Pointers
//////////////////////////
extern float (*Pull3DHooked)(ThreeDTable* table, float xLookup, float yLookup);
extern float (*Pull2DHooked)(TwoDTable* table, float xLookup);
extern unsigned char (*Pull2DHookedU8)(TwoDTable* table, float xLookup);
extern unsigned short (*Pull2DHookedU16)(TwoDTable* table, float xLookup);
extern unsigned char (*Pull2DHookedU8fp)(TwoDTableU8* table, unsigned long xLookup);
extern unsigned short (*Pull2DHookedU16fp)(TwoDTableU16* table, unsigned long xLookup);


extern float (*ShortToFloatHooked)(unsigned short input, float grad, float offs);
extern void (*RevLimDeleteHooked) ();

#define MafVoltageToInternalUnits 13107.20005368709

// Test utility functions.
void TestFailed(unsigned char *message) __attribute__ ((section ("Misc")));
void Assert(int condition, unsigned char *message) __attribute__ ((section ("Misc")));
int AreCloseEnough(float actual, float expected) __attribute__ ((section ("Misc")));


////////////////////
//TABLES
////////////////////

extern TableGroup VETableGroup;
extern ThreeDTable VolumetricEfficiencyTable1;
extern ThreeDTable VolumetricEfficiencyTable2;
extern ThreeDTable VolumetricEfficiencyRamTable;
extern ThreeDTable TemperatureCompensationTable;
extern ThreeDTable AtmosphericCompensationTable;
extern ThreeDTable SDBlendingTable;

extern float ValetModeMaxBoost;
extern float BaseGasolineAFR;
extern float BaseInjectorFlowPressureRelative;
extern float xFuelPressureFilter;
extern TwoDTable TableEthanolToBlend;
extern TwoDTable FlexFuelStoichTable;
extern TwoDTableU16 FuelCutTable;
extern TwoDTable PLSL_CutRatioTable;
extern unsigned char DefaultkPFuelPressureEnabled;
extern unsigned char DefaultFlexFuelSensorEnabled;
extern unsigned char DefaultPolfHackEnabled;
extern TableGroup FuelTableGroup;
extern ThreeDTable FuelTable1i;
extern ThreeDTable FuelTable2i;
extern ThreeDTable FuelTable1s;
extern ThreeDTable FuelTable2s;
extern ThreeDTable FuelTable1ss;
extern ThreeDTable FuelTable2ss;
extern ThreeDTable LCFuelEnrichTable;
extern unsigned char DefaultLCFuelMode;
extern float DefaultLCFuelLock;
extern float DefaultLCFuelEnrichMultiplier;

extern TableGroup PGWGTableGroup;
extern ThreeDTable PGWGTable1i;
extern ThreeDTable PGWGTable2i;
extern ThreeDTable PGTBTable1s;
extern ThreeDTable PGTBTable2s;
extern ThreeDTable PGWGTable1ss;
extern ThreeDTable PGWGTable2ss;

extern TableGroup PGTBTableGroup;
extern ThreeDTable PGTBTable1i;
extern ThreeDTable PGTBTable2i;
extern ThreeDTable PGWGTable1s;
extern ThreeDTable PGWGTable2s;
extern ThreeDTable PGTBTable1ss;
extern ThreeDTable PGTBTable2ss;

extern TableGroup TargetBoostTableGroup;
extern ThreeDTable TargetBoostTable1i;
extern ThreeDTable TargetBoostTable2i;
extern ThreeDTable TargetBoostTable1s;
extern ThreeDTable TargetBoostTable2s;
extern ThreeDTable TargetBoostTable1ss;
extern ThreeDTable TargetBoostTable2ss;

extern ThreeDTable tInitialWasteGate;
extern ThreeDTable tMaximumWasteGate;
/*
extern TableGroup WGDCInitialTableGroup;
extern ThreeDTable WGDCInitialTable1i;
extern ThreeDTable WGDCInitialTable2i;
extern ThreeDTable WGDCInitialTable1s;
extern ThreeDTable WGDCInitialTable2s;
extern ThreeDTable WGDCInitialTable1ss;
extern ThreeDTable WGDCInitialTable2ss;

extern TableGroup WGDCMaxTableGroup;
extern ThreeDTable WGDCMaxTable1i;
extern ThreeDTable WGDCMaxTable2i;
extern ThreeDTable WGDCMaxTable1s;
extern ThreeDTable WGDCMaxTable2s;
extern ThreeDTable WGDCMaxTable1ss;
extern ThreeDTable WGDCMaxTable2ss;*/

extern ThreeDTable PGWGRamTable;
//extern ThreeDTable WGDCInitialRamTable;
//extern ThreeDTable WGDCMaxRamTable;

extern float rgBoost[]; 
extern float rWGmod[];

extern unsigned char DefaultTimingHackEnabled;
extern TableGroup TimingTableGroup;
extern ThreeDTable TimingTable1i;
extern ThreeDTable TimingTable2i;
extern ThreeDTable TimingTable1s;
extern ThreeDTable TimingTable2s;
extern ThreeDTable TimingTable1ss;
extern ThreeDTable TimingTable2ss;

extern TableGroup KnockCorrectionRetardTableGroup;
extern ThreeDTable KnockCorrectionRetardTable1i;
extern ThreeDTable KnockCorrectionRetardTable2i;
extern ThreeDTable KnockCorrectionRetardTable1s;
extern ThreeDTable KnockCorrectionRetardTable2s;
extern ThreeDTable KnockCorrectionRetardTable1ss;
extern ThreeDTable KnockCorrectionRetardTable2ss;

extern ThreeDTable LCTimingRetardTable;


extern float RPMLockWGDC;
extern float ThrottleLockWGDC;

extern float GearRatios[];

extern float FFSMinimumThrottle;
extern float LCMinimumThrottle;

#if SD_DMAP
extern ThreeDTable SDDeltaMapTable;
#endif

extern float CelsiusToKelvin;
extern float Displacement;
extern float SpeedDensityConstant;
extern unsigned char DefaultMafMode;

extern unsigned char DefaultLCTimingMode;
extern float DefaultLCTimingLock;
extern float DefaultLCTimingRetardMultiplier;
extern float DefaultMaxSubtractiveKCA;

extern float DefaultInjectorScaling;

extern float RPMLockWGDC;
extern float ThrottleLockWGDC;

extern float DefaultBlend;
extern int IAMFailSafe;

//Spark Cut defaults
extern char* LCSparkCutFlag;
extern char* LCSparkEventsToCut;
extern char* LCSparkEventsCutFrom;
extern unsigned char DefaultLCSparkEventsToCut;
extern unsigned char DefaultLCSparkEventsCutFrom;

//CEL flahs defaults
#if CEL_HACKS
extern unsigned char FBKCLoFlashes;
extern unsigned char FBKCLoFlashSpeed;
extern unsigned char FBKCHiFlashes;
extern unsigned char FBKCHiFlashSpeed;
extern unsigned char EGTFlashes;
extern unsigned char EGTFlashSpeed;
extern unsigned char IAMFlashSpeed;
extern unsigned char IAMFlashes;
extern float IAMFlashThreshold;
extern unsigned char ECTFlashes;
extern unsigned char ECTFlashSpeed;
extern float ECTFlashThreshold;
extern float FBKCLoThreshold;
extern float FBKCHiThreshold;
extern float FBKCLoadThreshold;
extern float EGTCelLoadThreshold;
extern float EGTResistanceThreshold;
#endif

//Rev Limiter Defaults
extern unsigned char DefaultRevLimMode;
extern unsigned char DefaultFlatFootShiftMode;
extern float DefaultRedLineCut;
extern float DefaultRedLineHyst;
extern float DefaultLaunchControlSpeedMax;
extern float DefaultLaunchControlCut;
extern float DefaultLaunchControlHyst;
extern float DefaultFlatFootShiftAutoDelta;
extern float DefaultFlatFootShiftStaticDelta;
extern float DefaultFlatFootShiftHyst;
extern float DefaultFlatFootShiftSpeedThreshold;
extern float DefaultFlatFootShiftRpmThreshold;
extern float LCAdjustStep;
extern float ValetModeRevLim;
extern float NPLSL_RequestMax;
extern float NPLSL_Limit;
extern float NPLSL_Hyst;
extern float rgPLSL[];
extern float nFFSdelta;
extern float nFFSdeltaBite;
extern float RMDSminBrake;

#if CAN_HACKS
#define ccmCount 7
#define RACEGRADE_LED_CCM 1
#define RAMETUNE_RESPONSE_CCM 4
extern unsigned char rgButtonEthanolSource;
extern unsigned char rgButtonValetSource;
extern unsigned char rgButtonFFSSource;
extern unsigned char rgButtonFailsafeSource;
extern unsigned char rgButtonPLSLSource;
extern unsigned char rgButtonModeSource;
extern unsigned char rgButtonUpSource;
extern unsigned char rgButtonDownSource;
extern unsigned char rcpStreamEnabled;
extern float rgLC_MIN;
extern float rgLC_STEP;
extern float rgBLEND_STEP;
extern CanMessageSetupStruct ccm00;
extern CanMessageSetupStruct ccm01;
extern CanMessageSetupStruct ccm02;
extern CanMessageSetupStruct ccm03;
extern CanMessageSetupStruct ccm04;
extern CanMessageSetupStruct ccm05;
extern CanMessageSetupStruct ccm06;

extern unsigned long shC[];

extern unsigned char dataLinkedInRam;

#define cmDTCount 32
extern unsigned long cmDTaddr[];
extern unsigned char cmDTtypeIn[];
extern unsigned char cmDTtypeOut[];
extern unsigned char cmDTccm[];
extern unsigned char cmDTpos[];
extern float cmDTscale[];
extern float cmDToffset[];



#define rgButtonCount 9
void raceGradeKeyPadCallback(unsigned char* data) ROMCODE;
void canCallbackRamTune(unsigned char* data) ROMCODE;
void canCallbackAEMwideband(unsigned char* data) ROMCODE;
void canCallbackMK3e85Packet(unsigned char* data) ROMCODE;

#endif

#if VIN_HACKS
extern const VinBlockStruct VinBlock;
extern unsigned char Licensee[];
#endif

#if SWITCH_HACKS
extern unsigned char DefaultMapSwitch;
extern float DefaultMapBlendRatio;
extern TwoDTable TGVLeftScaling;
extern TwoDTable TGVRightScaling;
extern float MapSwitchThresholdLo;
extern float MapSwitchThresholdHi;
extern unsigned char BlendRatioInput;
extern unsigned char MapSwitchInput;
#endif

extern long RomHoleEndMarker;
extern unsigned char ModIdentifier[];