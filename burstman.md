split files into multiple files

## SYNOPSIS

./burst [input] [number of lines]

## DESCRIPTION

This program will take a text file as input, and produce several smaller files
based on the desired number of lines per file. The default is 500.

## EXAMPLES

./burst myfile.txt
: Let's say myfile.txt is 1200 lines long. burst will create 3 files,
myfile1.txt and myfile2.txt both 500 lines long, and myfile3.txt at 200 lines long.

./ burst myfile.txt 600
: Two files will be generated, myfile1.txt and myfile2.txt, 600 lines each.

## BUGS

The last file seems to be a bit long, some extra information is being copied over.
This program has not been fully completed and tested, and was written for learning 
purposes only. :)

## AUTHOR

Written by Peter Jindra
