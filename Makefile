#Build burst

all : burst

#link and compile
burst : burst.c
	@gcc -o burst burst.c

#clean
.PHONY: clean
clean :
	@rm burst
	@rm -f burst.gz

#run
.PHONY: run
run :
	./burst moretext.txt

#create manpage
burst : burst.md
	@ronn burst.md

#compress manpage
burst.gz : burst
	@gzip burst

#view manpage
view : burst.gz
	@man -l burst.gz
