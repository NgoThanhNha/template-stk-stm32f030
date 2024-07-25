/**
 ******************************************************************************
 * @author: Nark
 * @date:   25/07/2024
 ******************************************************************************
**/

#include "task.h"
#include "message.h"
#include "timer.h"

#include "platform.h"

#include "app.h"
#include "io_cfg.h"

#include "app_dbg.h"
#include "ring_buffer.h"
#include "led.h"

#include "task_list.h"
#include "task_dbg.h"
#include "task_shell.h"
#include "shell.h"

static void app_start_timer();
static void app_task_init();

int main_app() {
    /******************************************************************************
    * init kernel
    *******************************************************************************/
    msg_init();
    task_create((task_t*)&app_task_table);
    task_polling_create((task_polling_t*)&app_task_polling_table);
    timer_init();

    /* ring buffer init */
    ring_buffer_char_init(&ring_buffer_console_rev, buffer_console_rev, BUFFER_CONSOLE_REV_SIZE);

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

}

/*****************************************************************************/
/* app common function
 */
/*****************************************************************************/

/* hardware timer interrupt 10ms
 * used for led, button polling
 */
void sys_irq_timer_10ms() {
    led_polling(&led_life);
}