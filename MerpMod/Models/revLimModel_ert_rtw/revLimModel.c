#include "revLimModel.h"

#include "EcuHacks.h"

D_Work rtDWork __attribute__ ((section ("RamHole")));


D_Work rtDWork;
void revLimModel_custom()
{
  boolean_T rtb_mem;
  real32_T rtb_valetOrReg;
  pRamVariables.vPLSLerror = (*pVehicleSpeed - NPLSL_Limit) +
    pRamVariables.VPLSL_Adjust;
  if (pRamVariables.bPLSLRequest)
  {
    if (pRamVariables.vPLSLerror >= 5.0F)
    {
      pRamVariables.nINJCutPattern = MAX_uint16_T;
    }
    else if (pRamVariables.vPLSLerror >= 2.0F)
    {
      pRamVariables.nINJCutPattern = 31694U;
    }
    else if (pRamVariables.vPLSLerror >= 0.0F)
    {
      pRamVariables.nINJCutPattern = 23644U;
    }
    else if (pRamVariables.vPLSLerror >= -2.0F)
    {
      pRamVariables.nINJCutPattern = 4680U;
    }
    else
    {
      pRamVariables.nINJCutPattern = 0U;
    }
  }
  else
  {
    pRamVariables.nINJCutPattern = 0U;
  }

  pRamVariables.nPLSLCutRatio = pRamVariables.nINJCutPattern;
  pRamVariables.bPLSLcutting = ((int32_T)pRamVariables.nINJCutPattern > 0);
  pRamVariables.bFFSallowed = (((int32_T)pRamVariables.bFFSenabled) &&
    (*pVehicleSpeed >= DefaultFlatFootShiftSpeedThreshold));
  rtb_mem = (boolean_T)(*pAccelPedalAngle >= FFSMinimumThrottle);
  rtDWork.mem_PreviousInput = (boolean_T)((((int32_T)*pClutchFlags > (int32_T)
    rtDWork.Memory_PreviousInput_d) && ((int32_T)rtb_mem)) || (!((!(int32_T)
    rtDWork.mem_PreviousInput) || ((!((int32_T)*pClutchFlags != 0)) ||
    (!(int32_T)rtb_mem) || (*pEngineSpeed - rtDWork.Memory_PreviousInput <=
    nFFSdeltaBite)))));
  pRamVariables.bFFSengaged = (((int32_T)pRamVariables.bFFSallowed) && ((int32_T)
    rtDWork.mem_PreviousInput));
  if (pRamVariables.bFFSengaged)
  {
    if (1 > (int32_T)rtDWork.Memory_PreviousInput_j)
    {
      rtDWork.nEngineNextGearTarget_f = *pEngineSpeed * (GearRatios
        [*pCurrentGear] / GearRatios[(int32_T)*pCurrentGear - 1]);
      rtDWork.vCar_j = *pVehicleSpeed;
    }

    rtDWork.Divide2_e = rtDWork.nEngineNextGearTarget_f / rtDWork.vCar_j *
      *pVehicleSpeed;
  }

  rtb_mem = (boolean_T)(pRamVariables.rBrake >= RMDSminBrake);
  rtDWork.mem_PreviousInput_g = (boolean_T)((((int32_T)*pClutchFlags > (int32_T)
    rtDWork.Memory_PreviousInput_h) && ((int32_T)rtb_mem)) || (!((!(int32_T)
    rtDWork.mem_PreviousInput_g) || ((!((int32_T)*pClutchFlags != 0)) ||
    (!(int32_T)rtb_mem)))));
  pRamVariables.bRMDSengaged = (((int32_T)pRamVariables.bFFSallowed) &&
    ((int32_T)rtDWork.mem_PreviousInput_g));
  if (pRamVariables.bRMDSengaged)
  {
    if (1 > (int32_T)rtDWork.Memory_PreviousInput_f)
    {
      rtDWork.nEngineNextGearTarget = *pEngineSpeed * (GearRatios[(int32_T)
        *pCurrentGear - 1] / GearRatios[*pCurrentGear]);
      rtDWork.vCar = *pVehicleSpeed;
    }

    rtDWork.Divide2 = rtDWork.nEngineNextGearTarget / rtDWork.vCar *
      *pVehicleSpeed;
  }

  if ((int32_T)pRamVariables.bValetMode > 0)
  {
    rtb_valetOrReg = ValetModeRevLim;
  }
  else
  {
    rtb_valetOrReg = DefaultRedLineCut;
  }

  pRamVariables.bLCengaged = ((*pVehicleSpeed <= DefaultLaunchControlSpeedMax) &&
    ((int32_T)*pClutchFlags != 0) && (*pAccelPedalAngle >= LCMinimumThrottle));
  if (pRamVariables.bRMDSengaged)
  {
    pRamVariables.RevLimResume = rtDWork.Divide2;
  }
  else if (pRamVariables.bLCengaged)
  {
    pRamVariables.RevLimResume = pRamVariables.LaunchControlCut;
  }
  else if (pRamVariables.bFFSengaged)
  {
    pRamVariables.RevLimResume = rtDWork.Divide2_e + nFFSdelta;
  }
  else
  {
    pRamVariables.RevLimResume = rtb_valetOrReg;
  }

  if (rtb_valetOrReg < pRamVariables.RevLimResume)
  {
    pRamVariables.RevLimResume = rtb_valetOrReg;
  }

  if (pRamVariables.RevLimResume > 6800.0F)
  {
    pRamVariables.RevLimResume = 6800.0F;
  }
  else
  {
    if (pRamVariables.RevLimResume < 2100.0F)
    {
      pRamVariables.RevLimResume = 2100.0F;
    }
  }

  pRamVariables.RevLimCut = pRamVariables.RevLimResume;
  rtb_mem = (boolean_T)(*pEngineSpeed >= pRamVariables.RevLimResume);
  pRamVariables.RevLimResume = pRamVariables.RevLimResume - DefaultRedLineHyst;
  rtDWork.mem_PreviousInput_h = (boolean_T)(((int32_T)rtb_mem) || (!((!(int32_T)
    rtDWork.mem_PreviousInput_h) || (*pEngineSpeed < pRamVariables.RevLimResume))));
  if (rtDWork.mem_PreviousInput_h)
  {
    *pFlagsRevLim = (uint8_T)((int32_T)*pFlagsRevLim | 1);
  }
  else
  {
    *pFlagsRevLim = (uint8_T)~(int32_T)(uint8_T)((int32_T)(uint8_T)~(int32_T)
      *pFlagsRevLim | 1);
  }

  rtDWork.Memory_PreviousInput_d = *pClutchFlags;
  rtDWork.Memory_PreviousInput = rtDWork.Divide2_e;
  rtDWork.Memory_PreviousInput_j = pRamVariables.bFFSengaged;
  rtDWork.Memory_PreviousInput_h = *pClutchFlags;
  rtDWork.Memory_PreviousInput_f = pRamVariables.bRMDSengaged;
}

void revLimModel_initialize(void)
{
 
}
