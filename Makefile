#OPT= -g -Wall -Wextra -Werror -std=c99
LIB= -lwiringPi -lwiringPiDev

src = $(wildcard *.c)
obj = $(src:.c=.o)

myprog: $(obj)
	$(CC) -o $@ $^ $(LIB) 

.PHONY: clean
clean:
	rm -f $(obj) myprog