#OPT= -g -Wall -Wextra -Werror -std=c99
LIB= -wiringPi -wiringPiDev

src = $(wildcard *.c)
obj = $(src:.c=.o)

myprog: $(obj)
    $(CC) -o $@ $^ $(LIB) 

.PHONY: clean
clean:
    rm -f $(obj) myprog