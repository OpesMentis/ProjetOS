#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "crypt_img.h"
#include "mem_targa.h"

int image_clone(image_desc i_img, image_desc *p_img) {
	uint16_t planeSize;
	int i = 0;
	planeSize = mallocImageContent(p_img, i_img.width, i_img.height);

  	if (planeSize == 0) return 0;
  
  	for (i=0; i<(i_img.width) * (i_img.height); i++) {
    	(p_img->pBlue)[i] = (i_img.pBlue)[i];
    	(p_img->pGreen)[i] = (i_img.pGreen)[i];
    	(p_img->pRed)[i] = (i_img.pRed)[i];
  	}

  	return 1;
}

// chiffre avec un algo de Cesar un peu tuned
int image_cesar(image_desc i_img, image_desc *p_img) {
	uint16_t planeSize;
	
	int cle = 217;
	int i = 0;
	planeSize = mallocImageContent(p_img, i_img.width, i_img.height);

	if (planeSize == 0) return 0;
	
	for (i=0; i<(i_img.width) * (i_img.height); i++) {
	    (p_img->pBlue)[i] = ((i_img.pGreen)[i] + i * cle) % 256;
	    (p_img->pGreen)[i] = ((i_img.pRed)[i] + i * cle) % 256;
		(p_img->pRed)[i] = ((i_img.pBlue)[i] + i * cle) % 256;
	}
    
    return 1;
}

// dechiffre l'algo de Cesar
int x_image_cesar(image_desc i_img, image_desc *p_img) {
	uint16_t planeSize;
	
	int cle = 217;
	int i = 0;
	planeSize = mallocImageContent(p_img, i_img.width, i_img.height);

	if (planeSize == 0) return 0;
	
	for (i=0; i<(i_img.width) * (i_img.height); i++) {
	    (p_img->pBlue)[i] = ((i_img.pRed)[i] - i * cle) % 256;
	    (p_img->pGreen)[i] = ((i_img.pBlue)[i] - i * cle) % 256;
		(p_img->pRed)[i] = ((i_img.pGreen)[i] - i * cle) % 256;
	}
    
    return 1;
}

int tp(int a, int h, int l) {
	return (a % h) * l + (a / h);
}

int x_tp(int b, int h, int l) {
	return (b % l) * h + (b / l);
}

int main() {
	char * inputfn = "./images-test/pin2.tga";
	char * outputfn = "./images-test/pin3.tga";
	
	image_desc i_img, o_img;
  	targa_header i_head;

	readImage(&i_img, &i_head, inputfn);
	
	x_image_cesar(i_img, &o_img);
	
	writeImage(o_img, i_head, outputfn);
  	freeImage(&o_img);
  	
  	return 0;
}
