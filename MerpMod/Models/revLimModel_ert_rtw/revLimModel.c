#include "revLimModel.h"

#include "EcuHacks.h"

D_Work rtDWork __attribute__ ((section ("RamHole")));

#define prBrake ((float*)0xFFFF821C)

D_Work rtDWork;
void revLimModel_custom()
{
  boolean_T rtb_Memory_j;
  real32_T rtb_valetOrReg;
  if (pRamVariables.bPLSLRequest)
  {
    if (!(int32_T)rtDWork.Subsystem_MODE)
    {
      rtDWork.Subsystem_MODE = true;
    }

    pRamVariables.vPLSLerror = (*pVehicleSpeed - NPLSL_Limit) +
      pRamVariables.VPLSL_Adjust;
    if (pRamVariables.vPLSLerror >= 5.0F)
    {
      rtDWork.Switch = MAX_uint16_T;
    }
    else if (pRamVariables.vPLSLerror >= 2.0F)
    {
      rtDWork.Switch = 31694U;
    }
    else if (pRamVariables.vPLSLerror >= 0.0F)
    {
      rtDWork.Switch = 23644U;
    }
    else if (pRamVariables.vPLSLerror >= -2.0F)
    {
      rtDWork.Switch = 4680U;
    }
    else
    {
      rtDWork.Switch = 0U;
    }

    pRamVariables.nPLSLCutRatio = rtDWork.Switch;
  }
  else
  {
    if (rtDWork.Subsystem_MODE)
    {
      rtDWork.Switch = 0U;
      rtDWork.Subsystem_MODE = false;
    }
  }

  pRamVariables.nINJCutPattern = rtDWork.Switch;
  pRamVariables.bFFSallowed = (((int32_T)pRamVariables.bFFSenabled) &&
    (*pVehicleSpeed >= DefaultFlatFootShiftSpeedThreshold));
  if (pRamVariables.bFFSallowed)
  {
    if (!(int32_T)rtDWork.FFSdetect_MODE)
    {
      rtDWork.FFSdetect_MODE = true;
    }

    rtb_Memory_j = (boolean_T)(*pThrottlePlate >= FFSMinimumThrottle);
    rtDWork.set = (boolean_T)((((int32_T)*pClutchFlags > (int32_T)
      rtDWork.Memory_PreviousInput_l) && ((int32_T)rtb_Memory_j)) ||
      (!((!(int32_T)rtDWork.mem_PreviousInput_h) || (((int32_T)*pClutchFlags <
      (int32_T)rtDWork.Memory_PreviousInput_g) || (!(int32_T)rtb_Memory_j) ||
      (*pEngineSpeed - rtDWork.Memory_PreviousInput <= nFFSdeltaBite)))));
    pRamVariables.bFFSengaged = rtDWork.set;
    rtb_Memory_j = (boolean_T)(*prBrake >= RMDSminBrake);
    rtDWork.set_c = (boolean_T)((((int32_T)*pClutchFlags > (int32_T)
      rtDWork.Memory_PreviousInput_o) && ((int32_T)rtb_Memory_j)) ||
      (!((!(int32_T)rtDWork.mem_PreviousInput_b) || (((int32_T)*pClutchFlags <
      (int32_T)rtDWork.Memory_PreviousInput_gg) || (!(int32_T)rtb_Memory_j)))));
    pRamVariables.bRMDSengaged = rtDWork.set_c;
    if (rtDWork.set)
    {
      if ((int32_T)rtDWork.set > (int32_T)rtDWork.Memory_PreviousInput_j)
      {
        rtDWork.nEngineNextGearTarget_f = *pEngineSpeed * (GearRatios
          [*pCurrentGear] / GearRatios[(int32_T)*pCurrentGear - 1]);
        rtDWork.vCar_j = *pVehicleSpeed;
      }

      rtDWork.Divide2_e = rtDWork.nEngineNextGearTarget_f / rtDWork.vCar_j *
        *pVehicleSpeed;
    }

    rtDWork.Add = rtDWork.Divide2_e + nFFSdelta;
    if (rtDWork.set_c)
    {
      if ((int32_T)rtDWork.set_c > (int32_T)rtDWork.Memory_PreviousInput_f)
      {
        rtDWork.nEngineNextGearTarget = *pEngineSpeed * (GearRatios[(int32_T)
          *pCurrentGear - 1] / GearRatios[*pCurrentGear]);
        rtDWork.vCar = *pVehicleSpeed;
      }

      rtDWork.Divide2 = rtDWork.nEngineNextGearTarget / rtDWork.vCar *
        *pVehicleSpeed;
    }

    rtDWork.OutportBufferFornEngineRMDStarg = rtDWork.Divide2;
    rtDWork.Memory_PreviousInput_l = *pClutchFlags;
    rtDWork.mem_PreviousInput_h = rtDWork.set;
    rtDWork.Memory_PreviousInput_g = *pClutchFlags;
    rtDWork.Memory_PreviousInput = rtDWork.Divide2_e;
    rtDWork.Memory_PreviousInput_o = *pClutchFlags;
    rtDWork.mem_PreviousInput_b = rtDWork.set_c;
    rtDWork.Memory_PreviousInput_gg = *pClutchFlags;
    rtDWork.Memory_PreviousInput_j = rtDWork.set;
    rtDWork.Memory_PreviousInput_f = rtDWork.set_c;
  }
  else
  {
    if (rtDWork.FFSdetect_MODE)
    {
      rtDWork.set = false;
      rtDWork.set_c = false;
      rtDWork.FFSdetect_MODE = false;
    }
  }

  pRamVariables.bPLSLcutting = ((int32_T)rtDWork.Switch > 0);
  if ((int32_T)pRamVariables.bValetMode > 0)
  {
    rtb_valetOrReg = ValetModeRevLim;
  }
  else
  {
    rtb_valetOrReg = DefaultRedLineCut;
  }

  if (*pVehicleSpeed <= DefaultLaunchControlSpeedMax)
  {
    if (!(int32_T)rtDWork.LCdetect_MODE)
    {
      rtDWork.LCdetect_MODE = true;
    }

    rtDWork.bLCstateSet = (boolean_T)(((int32_T)*pClutchFlags != 0) &&
      (*pThrottlePlate >= LCMinimumThrottle));
  }
  else
  {
    if (rtDWork.LCdetect_MODE)
    {
      rtDWork.bLCstateSet = false;
      rtDWork.LCdetect_MODE = false;
    }
  }

  if (rtDWork.set_c)
  {
    pRamVariables.RevLimResume = rtDWork.OutportBufferFornEngineRMDStarg;
  }
  else if (rtDWork.bLCstateSet)
  {
    pRamVariables.RevLimResume = pRamVariables.LaunchControlCut;
  }
  else if (rtDWork.set)
  {
    pRamVariables.RevLimResume = rtDWork.Add;
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
  rtb_Memory_j = (boolean_T)(*pEngineSpeed >= pRamVariables.RevLimResume);
  pRamVariables.bLCengaged = rtDWork.bLCstateSet;
  pRamVariables.RevLimResume = pRamVariables.RevLimResume - DefaultRedLineHyst;
  rtDWork.mem_PreviousInput = (boolean_T)(((int32_T)rtb_Memory_j) ||
    (!((!(int32_T)rtDWork.mem_PreviousInput) || (*pEngineSpeed <
    pRamVariables.RevLimResume))));
  if (rtDWork.mem_PreviousInput)
  {
    *pFlagsRevLim = (uint8_T)((int32_T)*pFlagsRevLim | 1);
  }
  else
  {
    *pFlagsRevLim = (uint8_T)~(int32_T)(uint8_T)((int32_T)(uint8_T)~(int32_T)
      *pFlagsRevLim | 1);
  }
}

void revLimModel_initialize(void)
{

}
