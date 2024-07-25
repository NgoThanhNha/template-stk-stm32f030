/**
 ******************************************************************************
 * @author: Nark
 * @date:   25/07/2024
 ******************************************************************************
**/

#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdint.h>
#include "task.h"

/*************************************************************************/
/* STK TASKS 
**************************************************************************/
enum {
    /* KERNEL TASKS */
    TASK_TIMER_TICK_ID,

    /* APP TASKS */
    TASK_DBG_ID,
    TASK_SHELL_ID,

    /* END OF TABLE */
    STK_TASK_EOT_ID,
};

/*************************************************************************/
/* POLLING TASKS 
**************************************************************************/
enum {
    /* POLLING TASKS */
    TASK_POLLING_CONSOLE_ID,

    /* END OF TABLE */
    STK_TASK_POLLING_EOT_ID,
};

extern task_t app_task_table[];
extern task_polling_t app_task_polling_table[];

#ifdef __cplusplus
}
#endif

#endif /* __TASK_LIST_H__ */