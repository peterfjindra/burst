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
	@rm -f moretext1.txt moretext2.txt moretext3.txt sometext1.txt

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
