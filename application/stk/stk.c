/**
 ******************************************************************************
 * @author: Nark
 * @date:   03/05/2024
 ******************************************************************************
**/

#include "stk.h"
#include "message.h"

#include "platform.h"
#include "console.h"

static task_t* task_table = (task_t*)0;
static uint8_t size_of_task_list = 0;

static signal_queue_t event_signal;

void task_create(task_t* task_table_create) {

    task_table = task_table_create;
    size_of_task_list = 0;

    while (task_table[size_of_task_list].task_handler != NULL) {
        size_of_task_list++;
    }
    
    event_signal.qhead = STK_MSG_NULL;
    event_signal.qtail = STK_MSG_NULL;

    SYS_PRINT("Welcome to my application!\n");
    SYS_PRINT("Application tasks created: %d\n", size_of_task_list);
    SYS_PRINT("\n");
    SYS_PRINT("\n");
}

void task_post(task_id_t task_id, stk_msg_t* msg) {
    if (task_id >= size_of_task_list) {
        FATAL("TASK_POST", 0x01);
    }
    else {
        ENTRY_CRITICAL();

        /* assign the task_id to message */
        msg->next = STK_MSG_NULL;
        msg->des_task_id = task_id;

        /* put message to queue */
        if (event_signal.qtail == STK_MSG_NULL) {
            event_signal.qhead = msg;
            event_signal.qtail = msg;
        }
        else {
            event_signal.qtail->next = msg;
            event_signal.qtail = msg;
        }

        EXIT_CRITICAL();
    }
}

void task_post_pure_msg(task_id_t des_task_id, uint8_t signal) {
    stk_msg_t* get_pure_msg_from_pool = get_pure_msg();
    get_pure_msg_from_pool->sig = signal;
    task_post(des_task_id, get_pure_msg_from_pool);
}

void task_scheduler() {
    if (event_signal.qhead != STK_MSG_NULL) {

        ENTRY_CRITICAL();

        /* get msg from queue */
        stk_msg_t* get_msg = event_signal.qhead;

        /* move head queue to new position */
        event_signal.qhead = get_msg->next;

        if (get_msg->next == STK_MSG_NULL) {
            event_signal.qtail = STK_MSG_NULL;
        }
        
        EXIT_CRITICAL();

        /* execute task */
        task_table[get_msg->des_task_id].task_handler(get_msg);

        /* free message */
        free_msg(get_msg);
    }
}

void task_run() {
    for (;;) {
        task_scheduler();
    }
}