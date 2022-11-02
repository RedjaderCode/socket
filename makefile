

OBJS = main.cpp
CC = g++

INCLUDE_PATHS = -IC:/mingw_ASIO_lib/asio-1.24.0/include

#COMPILER_FLAGS = -w
OBJ_NAME = Socket_Server

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) -w -lmingw32 $(LINK)-o $(OBJ_NAME) -lws2_32


