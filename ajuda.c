#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  FILE *arquivo;
  char texto[81];
  int i;
  if ((arquivo = fopen("help.txt","w")) == NULL) {
    printf ("\n Arquivo não pode ser aberto");
    exit(1);
  }
  while (strlen(gets(texto))>0) {
  	for(i = 0;texto[i] != '\0';i++){
  		texto[i]+=5;	
	}
    fputs (texto,arquivo);  // grava o conjunto de caracteres
    putc ('\n',arquivo);    // grava caractere de mudança de linha
  }
  fclose (arquivo);
}
