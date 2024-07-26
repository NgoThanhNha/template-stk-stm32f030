/**
 ******************************************************************************
 * @author: Nark
 * @date:   25/07/2024
 ******************************************************************************
**/

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>

/******************************************************************************
* APP DEFINE SIGNALS
*******************************************************************************/
enum app_signals {
    /* TASK DBG */
    AC_DBG_1,
    AC_DBG_2,
    AC_DBG_3,

    /* TASK SHELL */
    AC_SHELL_CMD_PARSER,
};

/* main application */
extern int main_app();

/* polling with system tick */
extern void sys_irq_timer_10ms();

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */
