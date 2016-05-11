#Build burst

all : burst

#link and compile
burst : burst.c
	gcc -o burst burst.c

#clean
.PHONY: clean
clean :
	@rm burst

#run
.PHONY: run
run :
	./burst moretext.txt
