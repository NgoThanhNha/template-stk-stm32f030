CFLAGS 		+= -I./sys/irq/system_irq
CPPFLAGS 	+= -I./sys/irq/system_irq

CFLAGS 		+= -I./sys/irq
CPPFLAGS 	+= -I./sys/irq

VPATH += ./sys/irq

# C source files
SOURCES += ./sys/irq/system_irq/system_irq.c