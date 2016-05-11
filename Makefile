#Build burst

all : burst

#link and compile
burst : burst.c burst.gz
	@gcc -o burst burst.c

#clean
.PHONY: clean
clean :
	@rm -f burst
	@rm -f burst.html burst.gz

#run
.PHONY: run
run :
	./burst moretext.txt

#create and compress manpage
burst.gz : burst.md
	@ronn burst.md
	@gzip burst

#view manpage
view : burst.gz
	@man -l burst.gz
