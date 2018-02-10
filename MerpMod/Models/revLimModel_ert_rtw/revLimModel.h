#ifndef RTW_HEADER_revLimModel_h_
#define RTW_HEADER_revLimModel_h_
#include <stddef.h>
#ifndef revLimModel_COMMON_INCLUDES_
# define revLimModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

typedef struct
{
  real32_T Add;
  real32_T Divide2;
  real32_T nEngineNextGearTarget;
  real32_T vCar;
  real32_T Memory_PreviousInput;
  uint16_T Switch;
  uint8_T Memory_PreviousInput_l;
  uint8_T Memory_PreviousInput_g;
  boolean_T bLCstateSet;
  boolean_T set;
  boolean_T mem_PreviousInput;
  boolean_T mem_PreviousInput_h;
  boolean_T Memory_PreviousInput_j;
  boolean_T Subsystem_MODE;
  boolean_T FFSdetect_MODE;
  boolean_T LCdetect_MODE;
}
D_Work;


extern D_Work rtDWork;
extern void revLimModel_initialize(void);
extern void revLimModel_custom();


#endif

