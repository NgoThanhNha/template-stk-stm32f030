/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/05/2024
 ******************************************************************************
**/

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "platform.h"

#include "app.h"
#include "io_cfg.h"

#include "hard_timer.h"
#include "console.h"
#include "led.h"

#include "task_list.h"
#include "task_polling.h"

void main_app() {
    /* system tick init */
    systick_init();

    /* io init */
    io_init();    

    /* led init */
    led_init_func(&led_life, led_life_on, led_life_off);
    led_blink_set(&led_life, 1000);

    /* stk init */
    msg_init();
    task_create((task_t*)&app_task_table);
    timer_init();

    timer_set(TASK_TEMPLATE_1_ID, SIG_TESTING_1, 500, TIMER_PERIODIC);
    timer_set(TASK_TEMPLATE_1_ID, SIG_TESTING_2, 2000, TIMER_PERIODIC);

    /* kernel start */
    task_run();
}


