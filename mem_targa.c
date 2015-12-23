#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mem_targa.h"

/* Free the memory allocated for the given image structure. */
void freeImage(image_desc *pDesc)
{
  free (pDesc->pBlue); pDesc->pBlue = NULL;
  free (pDesc->pGreen); pDesc->pGreen = NULL;
  free (pDesc->pRed); pDesc->pRed = NULL;
}

/* Write an image given a header structure and an image
 * structure into a file named fName.  */
int readImage(image_desc *pDesc, targa_header *pHead, char * fName)
{
  FILE * fDesc;
  int i = 0;
  /* Open fDesc file */
  fDesc = fopen(fName,"r");
  if (fDesc == NULL) {
    fprintf (stderr, "Cannot read the file \"%s\".\n", fName);
    return 0;
  }
  /* Read the header */
  fread(pHead, sizeof(targa_header), 1, fDesc);
  
  printf("[mem_targa] Header : %u %u %u %u %u\n", pHead->idlength, pHead->colourmaptype, pHead->datatypecode, pHead->width, pHead->height);

  /* Initialize image struct (Note that this code is duplicated in
   * mallocImageContent function) */
  pDesc->width = pHead->width;
  pDesc->height = pHead->height;
  pDesc->pBlue  = malloc(sizeof(uint8_t)*pHead->width*pHead->height);
  pDesc->pGreen = malloc(sizeof(uint8_t)*pHead->width*pHead->height);
  pDesc->pRed   = malloc(sizeof(uint8_t)*pHead->width*pHead->height);
  
  /* Fill pixel by pixel the 3 color layers */
  for (i=0; i<pHead->width*pHead->height; i++) {
    // read 1 int : blue
    fread(pDesc->pBlue+i, sizeof(uint8_t), 1, fDesc);
    // read 1 int : green
    fread(pDesc->pGreen+i, sizeof(uint8_t), 1, fDesc);
    // read 1 int : red
    fread(pDesc->pRed+i, sizeof(uint8_t), 1, fDesc);
  }
  printf("[readImage] Number of pixels : %d\n", i);
  return 1;
  
}


/* Read an image from fName and create a header structure and an image
 * structure pointed to by pHeader and pDesc.  */
int writeImage (image_desc iDesc, targa_header head, char * fName)
{
  FILE *fDesc;
  int i;
  
  /* Open output image file */
  if ((fDesc = fopen (fName, "w")) == NULL)
  {
    fprintf (stderr, "Cannot create the file \"%s\".\n", fName);
    return 0;
  }

  /* Write the header in fDesc*/
  head.width = iDesc.width;
  head.height = iDesc.height;
  printf("[write mem_targa] Header : %u %u %u %u %u \n", 
         head.idlength, head.colourmaptype, head.datatypecode, head.width, head.height);

  fwrite (&head, sizeof (targa_header), 1, fDesc);

  /* Write in fDesc head.width*head.height pixels for each color */
  for (i=0; i<head.width*head.height; i++) 
  {
    fwrite((iDesc.pBlue)+i, sizeof(uint8_t), 1, fDesc);
    fwrite((iDesc.pGreen)+i, sizeof(uint8_t), 1, fDesc);
    fwrite((iDesc.pRed)+i, sizeof(uint8_t), 1, fDesc);
  }
  printf("[writeImage] Number of pixels : %d\n", i);
  fclose (fDesc);
  return 1;
}


/* Allocate memory for the content of the image structure given in parameter.
 * @return the number of pixels for the image if allocation succeeds,
 * 0 otherwise.
 */
uint16_t mallocImageContent(image_desc *pDesc, uint16_t width, uint16_t height)
{
  // multiplication strange on uint16_t. Conversion required, 
  uint16_t planeSize = 0;

  /* Do not reallocate if the pDesc pointer is already initialized */
  if (pDesc == NULL)
  {
    printf("Pointer on image structure must be allocated first\n");
    pDesc = (image_desc*)malloc(sizeof(image_desc));
  }
  else
  {
    pDesc->width = width;
    pDesc->height = height;
    planeSize = width * height;
    /* Allocate memory for each image plane */
    pDesc->pBlue = (uint8_t *) malloc(sizeof(uint8_t) * height * width);
    pDesc->pGreen = (uint8_t *) malloc(sizeof(uint8_t) * height * width);
    pDesc->pRed = (uint8_t *) malloc(sizeof(uint8_t) * height * width);
    if (pDesc->pBlue == NULL || pDesc->pGreen == NULL || pDesc->pRed == NULL) {
      planeSize = 0;
    }
  }
  return planeSize;
}
