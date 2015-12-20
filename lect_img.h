#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

typedef struct targa_header {
	uint8_t  idlength;
	uint8_t  colourmaptype;
	uint8_t  datatypecode;
	uint8_t useless[9];
	uint16_t width;
	uint16_t height;
	uint8_t useless2[2];
} targa_header;

struct node {
	char * name_file;
	int hauteur;
	int largeur;
	struct node * next;
};

typedef struct list {
	struct node rac;
	int nb_elt;
} list;

void add_node(char * addr, list * data);
void print_list(list data);
