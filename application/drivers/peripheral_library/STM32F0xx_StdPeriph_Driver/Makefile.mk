
CFLAGS += -I./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/inc
CPPFLAGS += -I./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/inc

VPATH += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src

# C source files
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/system_stm32f0xx.c
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_gpio.c
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_rcc.c
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_usart.c
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_misc.c
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_tim.c
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_i2c.c
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_exti.c
SOURCES += ./drivers/peripheral_library/STM32F0xx_StdPeriph_Driver/src/stm32f0xx_syscfg.c