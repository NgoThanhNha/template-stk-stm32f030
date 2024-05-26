/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/05/2024
 ******************************************************************************
**/

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdio.h>
#include <stdint.h>

#define ENTRY_CRITICAL()            disable_interrupts()
#define EXIT_CRITICAL()             enable_interrupts()

#if RELEASE_EN
#define FATAL(str, id)

#else
#define FATAL(str, id) fatal_error(str, id)

#endif

extern void enable_interrupts();
extern void disable_interrupts();
extern void sys_ctrl_delay_ms(volatile uint32_t count);
extern void fatal_error(const char* fatal_info, uint8_t fatal_id);

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_H__ */