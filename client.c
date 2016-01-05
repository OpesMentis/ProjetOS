#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include "strhelpers.h"
#define MAXTEXT 1024

// Definition des prototypes de fonctions appelees dans le fichier
void write_header(int sock, char * username);
void print_msg(char * chat);
void recv_img(int sock, long img_size);
int main(int argc, char * argv[])
{
  int sock;
  char sock2;
  int sock_talk;
  int port;
  int port_talk = 1111;
  int pidFils;
  char *username;
  struct hostent * hote;
  struct sockaddr_in adr;

  // On verifie qu'il y a au moins 2 options donnees au lancement du client
  if (argc!=4)
  {
    fprintf(stderr,"Usage : %s machine username port-number \n", argv[0]);
    exit(1);
  }
  // Creation d'un socket pour initier le rendez-vous du client avec le serveur
  sock=socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    fprintf(stderr, "Socket rendez-vous n'a pu etre cree");
    exit(1);
  }
  // On recupere la structure de donnee hote a partir du nom de la machine
  hote=gethostbyname(argv[1]);
  port=atoi(argv[3]);
  username=argv[2];
  printf("User: %s - %d; Machine: %s\n", username, geteuid(), argv[1]);

  /* Connexion au service */
  // On convertit l'addresse de l'hote en type compatible avec le type de socket
  // choisi (AF_INET/SOCK_STREAM)
  adr.sin_family=AF_INET;
  adr.sin_port=htons(port);
  bcopy(hote->h_addr, &adr.sin_addr.s_addr, hote->h_length);
  // On demande a se connecter
  int connectResult = connect(sock, (struct sockaddr *)&adr, sizeof(adr));
  if (connectResult ==-1)
  {
    fprintf(stderr, "Erreur de connexion");
    exit(1);
  }


  /* Connexion au talk */
  sock_talk=socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
  {
    fprintf(stderr, "Socket rendez-vous pour talk n'a pu etre cree\n");
    exit(1);
  }
  // On convertit l'addresse de l'hote en type compatible avec le type de socket
  // choisi (AF_INET/SOCK_STREAM)
  adr.sin_family=AF_INET;
  adr.sin_port=htons(port_talk);
  bcopy(hote->h_addr, &adr.sin_addr.s_addr, hote->h_length);
  // On demande a se connecter
  sleep(1);
  connectResult = connect(sock_talk, (struct sockaddr *)&adr, sizeof(adr));
  if (connectResult ==-1)
  {
	perror("Erreur de connexion au talk");
    exit(1);
  }
  printf("Connexion au talk etablie\n");

  char c;
  char f = 'X';
  char *chat =  malloc(MAXTEXT);
  char *begchat = chat;
  char img_name;
  long img_size ;
  int i;
  int j;
  char commande[256];
  char *msgclient = malloc(MAXTEXT);
  char BufferRcv[10000];
  int taille = 0;
  int tailleListe = 0;
  
  /* Le premier message ecrit le nom de l'utilisateur */
  write_header(sock_talk, username);
  while (c!=EOF) {
	printf("Dites moi quelque chose\n");
	i = 0;
	// Le pere produit les requetes sur sock_talk
	do
	{
	  c=getchar();
	  // Stocker la requete client pour savoir s'il faut attendre un message.
	  msgclient[i]=c;
	  write(sock_talk, &c, 1);
	  i++;
	}
	while (c!='\n');
	msgclient[i]='\0';
   	if (startswith("envoie", msgclient)) {
   	
   
   // code qui marche pour decouper selon un truc
   /*char str[80] = "This is - www.tutorialspoint.com - website";
   const char s[2] = "-";
   char *token;
   //get the first token 
   token = strtok(str, s);
   printf( " test adri : %s\n", token );
   //walk through other tokens 
   token = strtok(NULL, s);
   printf( " %s\n", token );*/
  
	  printf("Je vais recevoir une image\n");
	  read(sock, &img_size, sizeof(long));
	  printf("Taille de l'image a recevoir : %ld\n", img_size);
	  recv_img(sock, img_size);
	}
	
	else if (startswith("ls", msgclient)) {
	  printf("Je vais recevoir une liste\n");
	  tailleListe = 0;
	  read(sock, &tailleListe,sizeof(int));
	  printf("tailleListe : %d\n\n", tailleListe);
	  
	  for (i = 0 ; i < tailleListe ; i++) {
	    taille = 0;
	  
   	    read(sock,&taille,sizeof(int));
   	    
        read(sock, &BufferRcv, taille);
        printf("\nchemin : %s\n", BufferRcv);
        // puts(BufferRcv); //plus utile
        memset(BufferRcv,0,sizeof(BufferRcv));
        	    
	    taille = 0;
	    read(sock,&taille,sizeof(int));//On receptionne la hauteur
	    printf("hauteur : %d\n", taille);//On affiche la chaine de caractere
	    
	    taille = 0;
	    read(sock,&taille,sizeof(int));//On receptionne la hauteur
	    printf("largeur : %d\n", taille);//On affiche la chaine de caractere
	  
	    taille = 0;
	    read(sock,&taille,sizeof(int));//On receptionne la hauteur
	    printf("taille : %d octets\n", taille);//On affiche la chaine de caractere
	    // memset(BufferRcv,0,sizeof(BufferRcv));//On réinitialise la chaine
	  } 
	}
	
	else if (startswith("transforme", msgclient)) {
	  printf("Je transforme une image : %s\n", msgclient);
	
	
	}
  }	
  close(sock);
  close(sock_talk);	   
  return 0;
}


void recv_img(int sock, long img_size) {
  char *buffer = malloc(img_size);
  int readdata = 1;
  int total = 0;
  char *startbuffer = buffer;
  do
  {	 
	readdata = read(sock, buffer, img_size);
	buffer += readdata*sizeof(char);
	total+=readdata;
  } while (total<img_size && readdata != -1);

  buffer = startbuffer;
  printf("Copie terminee : lu %d octets , \n", total);
  int fd = open("./output/tasoeur.tga", O_CREAT|O_RDWR);
  write(fd, buffer, img_size); 
  close(fd);
  free(buffer);
}

void print_msg(char * chat) {
  fputs("reply: ", stdout);
  fputs(chat, stdout);
}

void write_header(int sock, char * username) {
  int loglen = strlen(username);
  write(sock, &loglen, 1);
  write(sock, username, loglen);
}

