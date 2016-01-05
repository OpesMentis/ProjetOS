#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include "lect_img.h"

list acqui_info(char * path) {
	DIR * d;
	struct dirent *dir;
	d = opendir(path);
	list * desc_img = malloc(sizeof(list));
	(*desc_img).nb_elt = 0;
	
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (strlen(dir->d_name) > 4) {
				char * ff = "";
				ff = malloc(sizeof(char[100]));
				strcat(ff, path);
				strcat(ff, dir->d_name);
				
				add_node(ff, desc_img);
			}
		}
		closedir(d);
	}
	return *desc_img;
}

void add_node(char * addr, list * data) {
	FILE * f_tga;
	targa_header * f_header = malloc(sizeof(targa_header));
	f_tga = fopen(addr, "r");
	fread(f_header, sizeof(targa_header), 1, f_tga);
	fclose(f_tga);

	struct node * nw_node = malloc(sizeof(struct node));
	(*nw_node).name_file = addr;
	(*nw_node).hauteur = (*f_header).height;
	(*nw_node).largeur = (*f_header).width;
	
	if ((*data).nb_elt == 0) {
		(*data).rac = *nw_node;
	} else {
		struct node * cur = &(*data).rac;
		
		int i;
		
		for (i = 1; i < (*data).nb_elt; i++) {
			cur = (*cur).next;
		}
		(*cur).next = nw_node;
	}
	(*data).nb_elt += 1;
}

int calcsize(int a) {
  if (a < 10)
	return 1;
  else if (a > 10 && a < 100)
  	return 2;
  else if (a > 100 && a < 1000)
  	return 3;
  else if (a > 1000 && a < 10000)
  	return 4;
  else if (a > 10000 && a < 100000)
  	return 5;
  else if (a > 100000 && a < 1000000)
    return 6;
  else if (a > 1000000 && a < 10000000)
  	return 7;
  else if (a > 10000000 && a < 100000000)
  	return 8;
  else if (a > 100000000 && a < 1000000000)
  	return 9;
  else if (a > 1000000000 && a < 10000000000)
  	return 10;
} 

void print_espace(int sizecompare, int size) {
  int espace;
  int i;
  espace = sizecompare - size;
  for (i = 0; i < espace; i++) {
    printf(" ");  
  }
}


/*void print_list(list data) {
	struct node cur = data.rac;
	int i;
	int fd;
	for (i = 0 ; i < data.nb_elt ; i++) {
	
		fd = open(cur.name_file, O_RDONLY);
  		long img_size = lseek(fd, 0L, SEEK_END);
  		lseek(fd, 0L, SEEK_SET);
 		close(fd);
 		
		printf("Chemin : C%s\n", cur.name_file);
		printf("hauteur : %i\n", cur.hauteur);
		printf("largeur : %i\n", cur.largeur);
		printf("taille de l'image : %ld octets\n\n", img_size);
		if (i + 1 < data.nb_elt) {
			cur = *cur.next;
		}
	}
}*/


/*int main() {

	char * path = "./images-test/";
	
	list * data = malloc(sizeof(list));
	
	*data = acqui_info(path);
	
	print_list(*data);
	
	return 1;
}*/
