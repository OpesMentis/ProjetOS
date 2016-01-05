default : projos

<<<<<<< HEAD
projos : crypt_img.o lect_img.o mem_targa.o
	gcc -g -Wall crypt_img.o lect_img.o mem_targa.o -o projos -lm
	
=======
# Test : dep with .h versus dep with .c


application : strhelpers.o serveur.o client.o lect_img.o
	gcc strhelpers.o serveur.o lect_img.o mem_targa.o -o enstaserveur -lm
	gcc strhelpers.o client.o lect_img.o mem_targa.o -o enstaclient -lm

>>>>>>> d63d1275f14fafa875dc68f213106c5aeb02620f
mem_targa.o : mem_targa.c mem_targa.h 
	gcc -g -Wall -c mem_targa.c -o mem_targa.o
	
lect_img.o : lect_img.c mem_targa.h 
	gcc -g -Wall -c lect_img.c -o lect_img.o
	
<<<<<<< HEAD
crypt_img.o : crypt_img.c crypt_img.h 
	gcc -g -Wall -c crypt_img.c -o crypt_img.o
=======
serveur.o : serveur.c  strhelpers.h lect_img.h mem_targa.h 
	gcc -c serveur.c -o serveur.o

client.o : client.c strhelpers.h lect_img.h mem_targa.h
	gcc -c client.c -o client.o 

strhelpers.o : strhelpers.c 
	gcc -c strhelpers.c -o strhelpers.o
>>>>>>> d63d1275f14fafa875dc68f213106c5aeb02620f

# serveur.o : serveur.c strhelpers.h
#	gcc -c serveur.c -o serveur.o
	
# client.o : client.c strhelpers.h
#	gcc -c client.c -o client.o
	
# strhelpers.o : strhelpers.c
#	gcc -c strhelpers.c -o strhelpers.o
