#ifndef RTW_HEADER_revLimModel_h_
#define RTW_HEADER_revLimModel_h_
#include <stddef.h>
#ifndef revLimModel_COMMON_INCLUDES_
# define revLimModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

typedef struct
{
  real32_T OutportBufferFornEngineFFStarge;
  real32_T Divide2;
  real32_T nEngineNextGearTarget;
  real32_T vCar;
  struct
  {
    uint_T mem_PreviousInput:1;
    uint_T mem_PreviousInput_h:1;
    uint_T Memory_PreviousInput_j:1;
    uint_T LCdetect_MODE:1;
    uint_T FFSdetect_MODE:1;
  }
  bitsForTID0;

  uint8_T Memory_PreviousInput;
  uint8_T Memory_PreviousInput_l;
}
D_Work;

extern D_Work rtDWork;
extern void revLimModel_initialize(void);
extern void revLimModel_custom();


#endif

