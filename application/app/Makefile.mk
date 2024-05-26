CFLAGS 		+= -I./app
CPPFLAGS 	+= -I./app

VPATH += ./app

#CPP source files
SOURCES_CPP += ./app/app.cpp
SOURCES_CPP += ./app/task_polling.cpp
SOURCES_CPP += ./app/task_list.cpp

SOURCES_CPP += ./app/task_template_1.cpp