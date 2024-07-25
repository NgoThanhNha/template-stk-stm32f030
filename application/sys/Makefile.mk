CFLAGS 		+= -I./sys
CPPFLAGS 	+= -I./sys

CFLAGS 		+= -I./sys
CPPFLAGS 	+= -I./sys

VPATH += ./sys

# C source files
SOURCES += ./sys/io_cfg.c
SOURCES += ./sys/sys_startup.c
SOURCES += ./sys/sys_irq.c
SOURCES += ./sys/sys_cfg.c
SOURCES += ./sys/platform.c