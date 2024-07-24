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

static void app_start_timer();
static void app_task_init();

int main_app() {
    /* system tick init */
    systick_init();

    /* io init */
    io_init();    

    /* led init */
    led_init_func(&led_life, led_life_on, led_life_off);
    led_blink_set(&led_life, 1000);

    /******************************************************************************
    * init kernel
    *******************************************************************************/
    msg_init();
    task_create((task_t*)&app_task_table);
    timer_init();

    /******************************************************************************
    * app task initial
    *******************************************************************************/
    app_task_init();

    /******************************************************************************
    * start timer for application
    *******************************************************************************/
    app_start_timer();

    /******************************************************************************
    * run applications
    *******************************************************************************/
    return task_run();
}

/*****************************************************************************/
/* app initial function 
 */
/*****************************************************************************/

/* send the first message to tasks */
void app_task_init() {
    task_post_pure_msg(TASK_DBG_ID, AC_DBG_2);
}

/* start software timer for application */
void app_start_timer() {
    timer_set(TASK_DBG_ID, AC_DBG_1, 3000, TIMER_PERIODIC);
}

/*****************************************************************************/
/* app common function
 */
/*****************************************************************************/

/* hardware timer interrupt 1ms
 * used for led, button polling
 */
void systick_irq_timer_1ms() {
    led_polling(&led_life);
}