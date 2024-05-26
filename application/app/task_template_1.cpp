/**
 ******************************************************************************
 * @author: Nark
 * @date:   03/05/2024
 ******************************************************************************
**/

#include "task_template_1.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "io_cfg.h"

#include "console.h"
#include "led.h"

#include "task_list.h"
#include "task_polling.h"

static uint8_t counter_temp1 = 0;
static uint8_t counter_temp2 = 0;

void task_template_1(stk_msg_t* msg) {
    switch (msg->sig){
    case SIG_TESTING_1:
        APP_PRINT("[TASK_TEMPATE_1] SIGNAL_1_EXECUTED \n");
        counter_temp1++;
        if (counter_temp1 == 20) {
            counter_temp1 = 0;
            timer_remove(TASK_TEMPLATE_1_ID, SIG_TESTING_1);
        }
        break;
    
    case SIG_TESTING_2:
        APP_PRINT("[TASK_TEMPATE_1] SIGNAL_2_EXECUTED\n");
        counter_temp2++;
        if (counter_temp2 == 5) {
            counter_temp2 = 0;
            task_post_pure_msg(TASK_TEMPLATE_1_ID, SIG_TESTING_3);
        }
        break;

    case SIG_TESTING_3:
        APP_PRINT("[TASK_TEMPATE_1] SIGNAL_3_EXECUTED\n");
        break;

    default:
        break;
    }
}