/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/02/2024
 ******************************************************************************
**/

#include "console.h"

void console_init() {
    #if defined (CONSOLE_DBG_EN)
        xfunc_output = (void(*)(int))usart1_put_char;
    #endif
}