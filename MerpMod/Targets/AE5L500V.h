#define MOD_IDENTIFIER STRI(AE5L500V.MeRpMoD.Switch.v18.2.17.590.352113855)
#define MOD_ECUID 8ECBBEEF33
#define MOD_DATE 18.2.17.590.352113855
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Release
#define MOD_RELEASE 1
#define ECU_CALIBRATION_ID AE5L500V
#define ECU_IDENTIFIER 8A12784007
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002004)
#define dEcuId (0x000DAD80)
#define dRomHoleStart (0x000E1000)
#define pRamHoleStart (0xFFFFB9A0)
#define pRamHoleEnd (0xFFFFBE8F)
#define sPull2DFloat (0x000BE7F4)
#define sPull3DFloat (0x000BE8A8)
#define sPull2D_U8 (0x000BE838)
#define sPull2D_U16 (0x000BE870)
#define sPull2D_U8_U32Axis (0x000BE850)
#define sPull2D_U16_U32Axis (0x000BE888)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive (0xFFFF5DB6)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF4018)
#define pTGVRightVoltage ((unsigned short*)0xFFFF401C)
#define sShortToFloat (0x000BE55C)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x0004B694)
#define sRevLimStart (0x0003BF84)
#define sRevLimEnd (0x0003BFC4)
#define pFlagsRevLim ((unsigned char*)0xFFFF7CE4)
#define RevLimBitMask (0x01)

/////////////////////
// CAN Recieves
/////////////////////

#define vCar_FL ((unsigned short*)0xFFFFD288)
#define vCar_FR ((unsigned short*)0xFFFFD28A)
#define vCar_RL ((unsigned short*)0xFFFFD28C)
#define vCar_RR ((unsigned short*)0xFFFFD28E)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x00004A88)
#define sMafCalc (0x00004A2C)
#define hAFRSensorScaling (0x00049804)
#define sAFRSensorScaling (0x00059286)
#define tAFRSensorScaling (0x000B328C)
#define subFuncCalcIgnitionDwell (0x00008948)
#define subFuncCalcInjectorTrims (0x00039628)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000CCB64)
#define hInjectorScaling (0x00030C18)
#define pInjCompC1 ((float*)0xFFFF7B98)
#define pInjCompC2 ((float*)0xFFFF7B9C)
#define pInjCompC3 ((float*)0xFFFF7BA0)
#define pInjCompC4 ((float*)0xFFFF7BA4)
#define pInjectorLastPulse ((float*)0xFFFF7350)
#define hInjectorTrims (0x0004B6C4)
#define sInjectorTrims (0x00039628)
#define TabInjCompC1 (0x000B1530)
#define TabInjCompC2 (0x000B154C)
#define TabInjCompC3 (0x000B1568)
#define TabInjCompC4 (0x000B1584)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x000A1E00)
#define hCelSignal (0x000A1E84)
#define pCelSignalOem ((unsigned char*)0xFFFFAFC2)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00013AF0)
#define hTableTargetBoost (0x00013AEC)
#define tTargetBoost (0x000AE7EC)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x00013FD4)
#define hWgdc (0x0004AF48)
#define sWgdc (0x0001383C)
#define hTableWgdcInitial (0x00013FD0)
#define tWgdcInitial (0x000AE7D0)
#define hTableWgdcMax (0x00013FF0)
#define tWgdcMax (0x000AE7B4)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define hPull3DPolf (0x00036B28)
#define hPolf (0x0004B6B8)
#define sPolf (0x000368D4)
#define tPolfKcaAlt (0x000B14DC)
#define hTablePolfKcaAlt (0x00036B40)
#define tPolfKcaBLo (0x000B14C0)
#define hTablePolfKcaBLo (0x00036B3C)
#define tPolfKcaBHi (0x000B146C)
#define hTablePolfKcaBHi (0x00036B24)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x0004B778)
#define sBaseTiming (0x00040988)
#define hPull3DTiming (0x00040C28)
#define tBaseTimingPCruise (0x000B210C)
#define hTableBaseTimingPCruise (0x00040C24)
#define tBaseTimingPNonCruise (0x000B2128)
#define hTableBaseTimingPNonCruise (0x00040C30)
#define tBaseTimingRCruiseAvcs (0x000B2144)
#define hTableBaseTimingRCruiseAvcs (0x00040C2C)
#define tBaseTimingRNonCruiseAvcs (0x000B2160)
#define hTableBaseTimingRNonCruiseAvcs (0x00040C34)
#define pKcaIam (0xFFFF8250)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF5FCF)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF5FCE)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF5FD0)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF65F8)
#define ClutchBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF68A3)
#define pFbkc4 ((float*)0xFFFF821C)
#define pIam1 ((unsigned char*)0xFFFF68A5)
#define pIam4 ((float*)0xFFFF329C)
#define pEngineSpeed ((float*)0xFFFF664C)
#define pVehicleSpeed ((float*)0xFFFF6628)
#define pCoolantTemp ((float*)0xFFFF4144)
#define pAtmoPress ((float*)0xFFFF68C8)
#define pManifoldAbsolutePressure ((float*)0xFFFF6218)
#define pIntakeAirTemp ((float*)0xFFFF4128)
#define pMassAirFlow ((float*)0xFFFF63CC)
#define pMafSensorVoltage ((short*)0xFFFF4024)
#define pEngineLoad ((float*)0xFFFF6400)
#define pReqTorque ((float*)0xFFFF8584)
#define pThrottlePlate ((float*)0xFFFF62E8)
#define pWgdc4 ((float*)0xFFFF5C98)
#define pCurrentGear ((unsigned char*)0xFFFF6839)
#define pIgnitionTimeTotal ((float*)0xFFFF7EBC)
#define pEstimatedOdometer ((float*)0xFFFF31A8)
#define pAfCorrection_1 ((float*)0xFFFF7700)
#define pAFLearning_1 ((float*)0xFFFF78A4)
#define pkclearn1 ((char*)0xFFFF68A6)
#define pNRough_C1 ((char*)0xFFFFA1E5)
#define pNRough_C2 ((char*)0xFFFFA1E6)
#define pNRough_C3 ((char*)0xFFFFA1E7)
#define pNRough_C4 ((char*)0xFFFFA1E8)
#define pKnockSum1 ((char*)0xFFFF81D9)
#define pKnockSum2 ((char*)0xFFFF81DA)
#define pKnockSum3 ((char*)0xFFFF81DB)
#define pKnockSum4 ((char*)0xFFFF81DC)
#define pCLOL ((char*)0xFFFFB1E9)
#define pAVCSIntakeLeft ((float*)0xFFFF9190)
#define pAVCSIntakeRight ((float*)0xFFFF918C)
#define pAVCSExhaustLeft ((float*)0xFFFF9368)
#define pAVCSExhaustRight ((float*)0xFFFF9364)
#define pLambdaFinal ((float*)0xFFFF6564)
#define prLamLearnA ((float*)0xFFFF31D4)
#define prLamLearnB ((float*)0xFFFF31DC)
#define prLamLearnC ((float*)0xFFFF31E4)
#define prLamLearnD ((float*)0xFFFF31EC)
#define pTD_wg_prop ((float*)0xFFFF5CAC)
#define pTD_wg_int ((float*)0xFFFF5CB0)
#define pBatteryVoltage ((float*)0xFFFF4130)
#define pEngineSpeedDwell ((float*)0xFFFF4150)
#define pIgnitionDwellTiming ((float*)0xFFFF4220)
#define pInjectorLastPulse ((float*)0xFFFF7350)
#define pAFRConverted4 ((float*)0xFFFF8E08)
#define pAFRsensedCurrent ((float*)0xFFFF40E0)
#define pAf1Res ((float*)0xFFFF40C8)

/////////////////////
// OBD Experimental stuff
/////////////////////


/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C2D68)
#define dLoadSmoothingB (0x000C2D64)
#define dLoadSmoothingAlt (0x000C2D60)
#define dLoadSmoothingFinal (0x000C2D74)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x00010290)
#define hMemoryReset (0x0000FCE8)
#define pMemoryResetLimit (0xFFFFBF9F)
#define hMemoryResetLimit (0x00011CE8)

