#ifndef _CRYPTIMGH_
#define _CRYPTIMGH_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef struct image_desc_ {
	char *fname;
  	uint16_t width;
  	uint16_t height;
  	uint8_t *pRed;
  	uint8_t *pBlue;
  	uint8_t *pGreen;
} image_desc;

typedef struct targa_header_ {
  uint8_t  idlength;
  uint8_t  colourmaptype;
  uint8_t  datatypecode;
  uint8_t useless[9];
  uint16_t width;
  uint16_t height;
  uint8_t useless2[2];
} targa_header;

int image_clone(image_desc i_img, image_desc *p_img);
int * decTo256(int n);
int image_cesar(image_desc i_img, image_desc *p_img);
int x_image_cesar(image_desc i_img, image_desc *p_img);
int image_vignr(image_desc i_img, image_desc *p_img);
int x_image_vignr(image_desc i_img, image_desc *p_img);
int tp(int a, int h, int l);
int x_tp(int b, int h, int l);

#endif
