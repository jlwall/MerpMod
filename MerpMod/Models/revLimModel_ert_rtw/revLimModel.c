#include "revLimModel.h"

#include "EcuHacks.h"

D_Work rtDWork __attribute__ ((section ("RamHole")));
D_Work rtDWork;

void revLimModel_custom()
{
  boolean_T rtb_set;
  if (*pVehicleSpeed <= DefaultLaunchControlSpeedMax)
  {
    if (!(int32_T)rtDWork.bitsForTID0.LCdetect_MODE)
    {
      rtDWork.bitsForTID0.LCdetect_MODE = true;
    }

    pRamVariables.LCEngaged = (((int32_T)*pClutchFlags != 0) && (*pThrottlePlate
      >= LCMinimumThrottle));
  }
  else
  {
    if (rtDWork.bitsForTID0.LCdetect_MODE)
    {
      pRamVariables.LCEngaged = false;
      rtDWork.bitsForTID0.LCdetect_MODE = false;
    }
  }

  if (*pVehicleSpeed >= DefaultFlatFootShiftSpeedThreshold)
  {
    if (!(int32_T)rtDWork.bitsForTID0.FFSdetect_MODE)
    {
      rtDWork.bitsForTID0.FFSdetect_MODE = true;
    }

    pRamVariables.FFSEngaged = ((((int32_T)*pClutchFlags > (int32_T)
      rtDWork.Memory_PreviousInput_l) && (*pThrottlePlate >= FFSMinimumThrottle))
      || (!((!(int32_T)rtDWork.bitsForTID0.mem_PreviousInput_h) || ((int32_T)
      *pClutchFlags < (int32_T)rtDWork.Memory_PreviousInput))));
    if (pRamVariables.FFSEngaged)
    {
      if ((int32_T)pRamVariables.FFSEngaged > (int32_T)
          rtDWork.bitsForTID0.Memory_PreviousInput_j)
      {
        rtDWork.nEngineNextGearTarget = *pEngineSpeed * (GearRatios
          [*pCurrentGear] / GearRatios[(int32_T)*pCurrentGear - 1]);
        rtDWork.vCar = *pVehicleSpeed;
      }

      rtDWork.Divide2 = rtDWork.nEngineNextGearTarget / rtDWork.vCar *
        *pVehicleSpeed;
    }

    rtDWork.OutportBufferFornEngineFFStarge = rtDWork.Divide2;
    rtDWork.bitsForTID0.mem_PreviousInput_h = pRamVariables.FFSEngaged;
    rtDWork.Memory_PreviousInput = *pClutchFlags;
    rtDWork.Memory_PreviousInput_l = *pClutchFlags;
    rtDWork.bitsForTID0.Memory_PreviousInput_j = pRamVariables.FFSEngaged;
  }
  else
  {
    if (rtDWork.bitsForTID0.FFSdetect_MODE)
    {
      pRamVariables.FFSEngaged = false;
      rtDWork.bitsForTID0.FFSdetect_MODE = false;
    }
  }

  if (pRamVariables.LCEngaged)
  {
    pRamVariables.RevLimCut = pRamVariables.LaunchControlCut;
  }
  else if (pRamVariables.FFSEngaged)
  {
    pRamVariables.RevLimCut = rtDWork.OutportBufferFornEngineFFStarge;
  }
  else
  {
    pRamVariables.RevLimCut = DefaultRedLineCut;
  }

  if (DefaultRedLineCut < pRamVariables.RevLimCut)
  {
    pRamVariables.RevLimCut = DefaultRedLineCut;
  }

  if (pRamVariables.RevLimCut > 6800.0F)
  {
    pRamVariables.RevLimCut = 6800.0F;
  }
  else
  {
    if (pRamVariables.RevLimCut < 2100.0F)
    {
      pRamVariables.RevLimCut = 2100.0F;
    }
  }

  pRamVariables.RevLimResume = pRamVariables.RevLimCut - DefaultRedLineHyst;
  rtb_set = (boolean_T)((*pEngineSpeed >= pRamVariables.RevLimCut) ||
                        (!((!(int32_T)rtDWork.bitsForTID0.mem_PreviousInput) ||
    (*pEngineSpeed < pRamVariables.RevLimResume))));
  if (rtb_set)
  {
    *pFlagsRevLim = (uint8_T)((int32_T)*pFlagsRevLim | 1);
  }
  else
  {
    *pFlagsRevLim = (uint8_T)~(int32_T)(uint8_T)((int32_T)(uint8_T)~(int32_T)
      *pFlagsRevLim | 1);
  }

  rtDWork.bitsForTID0.mem_PreviousInput = rtb_set;
}

void revLimModel_initialize(void)
{
 
}
