# compiler options
# CC = gcc
# CFLAGS = -Wall -std=gnu99

VPATH = ./:CuTests:../cutest-1.5
src := wrap.c AllTests.c wrapTest.c CuTest.c
INC := -I./ -I../cutest-1.5

# 内置函数 info/warning/error
# $(info $(CFLAGS))

a.out : $(src)
	$(CC) $(INC) -o $@ $^
