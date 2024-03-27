#ifndef INC_SYSTEM_H
#define INC_SYSTEM_H

#include <common-defines.h>

#define CPU_FREQ (84000000)
#define SYSTICK_FREQ (1000)

void system_setup(void);
uint64_t system_get_ticks(void);

#endif /* FDFBD366_7148_47C5_AB21_359DBDAFB6D4 */
