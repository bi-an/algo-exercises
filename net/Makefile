# compiler options
# CC = gcc
# CFLAGS = -Wall -std=gnu99

# VPATH = ./:CuTests:../cutest-1.5
# src := wrap.c AllTests.c wrapTest.c CuTest.c
# INC := -I./ -I../cutest-1.5

# 内置函数 info/warning/error
# $(info $(CFLAGS))

# a.out : $(src)
# 	$(CC) $(INC) -o $@ $^

# select.server.out : select.server.c wrap.c
# 	$(CC) -o select.server $^

# .PHONY : clear

# clear :
# 	find . -name "*.out" | xargs rm -rf
# 	find . -name "*.tmp" | xargs rm -rf
# 	find . -name "*.o" | xargs rm -rf

# $(HOME) 表示 ~/目录

# ROOT = ..
# DIRS = Select Poll Epoll

all: client server

server: epoll_loop.c
    gcc -o $@ $^

client: lib/wrap.c client.c
    gcc -Ilib -o $@ $^