/**
 ******************************************************************************
 * @author: Nark
 * @date:   23/07/2024
 ******************************************************************************
**/

#include "task_dbg.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "io_cfg.h"

#include "console.h"
#include "led.h"

#include "app.h"
#include "task_list.h"

void task_dbg_handler(stk_msg_t* msg) {
    switch (msg->sig){
    case AC_DBG_1:
        APP_PRINT("[task_dbg] AC_DBG_1 \n");
        break;
    
    case AC_DBG_2:
        APP_PRINT("[task_dbg] AC_DBG_2\n");
        break;

    case AC_DBG_3:
        APP_PRINT("[task_dbg] AC_DBG_3\n");
        break;

    default:
        break;
    }
}