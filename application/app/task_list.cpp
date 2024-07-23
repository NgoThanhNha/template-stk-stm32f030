/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/05/2024
 ******************************************************************************
**/

#include "task_list.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "console.h"

#include "task_dbg.h"

task_t app_task_table[] = {
    /*************************************************************************/
    /* SYSTEM TASKS */
    /*************************************************************************/
    {TASK_TIMER_TICK_ID,            task_timer_handler},

    /*************************************************************************/
    /* APP TASKS */
    /*************************************************************************/
    {TASK_DBG_ID,                   task_dbg_handler},

    /*************************************************************************/
    /* END OF TABLE */
    /*************************************************************************/
    {STK_TASK_EOT_ID,               (pf_task)0},
};