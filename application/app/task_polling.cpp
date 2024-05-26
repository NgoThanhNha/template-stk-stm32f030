/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/05/2024
 ******************************************************************************
**/

#include "stk.h"
#include "message.h"

#include "app.h"
#include "io_cfg.h"

#include "console.h"
#include "led.h"

#include "task_list.h"
#include "task_polling.h"

void task_polling_handler() {
    led_polling(&led_life);
}