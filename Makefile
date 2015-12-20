lect_img: lect_img.o
	gcc -o lect_img lect_img.o
	
lect_img.o: lect_img.c
	gcc -o lect_img.o -c lect_img.c -W -Wall
