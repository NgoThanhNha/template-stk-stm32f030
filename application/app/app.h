/**
 ******************************************************************************
 * @author: Nark
 * @date:   23/07/2024
 ******************************************************************************
**/

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>

/*---------------------------------------------------------------------------*/
/*                            APP DEFINE SIGNALS                             */
/*---------------------------------------------------------------------------*/
enum app_signals {
    AC_DBG_1,
    AC_DBG_2,
    AC_DBG_3,
};

/* main application */
extern int main_app();

/* polling with system tick */
extern void systick_irq_timer_1ms();

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */
