# Read an image with xli.
all : application

# Test : dep with .h versus dep with .c


application : strhelpers.o serveur.o client.o lect_img.o
	gcc strhelpers.o serveur.o lect_img.o mem_targa.o -o enstaserveur -lm
	gcc strhelpers.o client.o lect_img.o mem_targa.o -o enstaclient -lm

mem_targa.o : mem_targa.c mem_targa.h 
	gcc -g -Wall -c mem_targa.c -o mem_targa.o
	
lect_img.o : lect_img.c mem_targa.h 
	gcc -g -Wall -c lect_img.c -o lect_img.o
	
serveur.o : serveur.c  strhelpers.h lect_img.h mem_targa.h 
	gcc -c serveur.c -o serveur.o

client.o : client.c strhelpers.h lect_img.h mem_targa.h
	gcc -c client.c -o client.o 

strhelpers.o : strhelpers.c 
	gcc -c strhelpers.c -o strhelpers.o

