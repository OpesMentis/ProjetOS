# Read an image with xli.
all : application

# Test : dep with .h versus dep with .c


application : strhelpers.o serveur.o client.o
	gcc strhelpers.o serveur.o -o enstaserveur
	gcc strhelpers.o client.o -o enstaclient

serveur.o : serveur.c  strhelpers.h 
	gcc -c serveur.c -o serveur.o

client.o : client.c strhelpers.h 
	gcc -c client.c -o client.o

strhelpers.o : strhelpers.c 
	gcc -c strhelpers.c -o strhelpers.o

