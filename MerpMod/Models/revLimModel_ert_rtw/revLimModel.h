#ifndef RTW_HEADER_revLimModel_h_
#define RTW_HEADER_revLimModel_h_
#include <stddef.h>
#ifndef revLimModel_COMMON_INCLUDES_
# define revLimModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

typedef struct
{
  real32_T Divide2;
  real32_T nEngineNextGearTarget;
  real32_T vCar;
  real32_T Divide2_e;
  real32_T nEngineNextGearTarget_f;
  real32_T vCar_j;
  real32_T Memory_PreviousInput;
  uint8_T Memory_PreviousInput_d;
  uint8_T Memory_PreviousInput_h;
  boolean_T mem_PreviousInput;
  boolean_T Memory_PreviousInput_j;
  boolean_T mem_PreviousInput_g;
  boolean_T Memory_PreviousInput_f;
  boolean_T mem_PreviousInput_h;
}
D_Work;


extern D_Work rtDWork;
extern void revLimModel_initialize(void);
extern void revLimModel_custom();


#endif

