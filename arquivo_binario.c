#include<stdio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
void menu();
void sair();
void hideCursor();
void showCursor();
void gotoxy(int x,int y);

void menu(){
	system("cls");
	int tecla;
	int cont = 2;
	hideCursor();
	gotoxy(40,3);printf("CONVERSOR DE BASES");
	gotoxy(7,6);printf("->");
	gotoxy(10,6);printf("Binario para as demais bases");
	gotoxy(10,8);printf("Decimal para as demais bases");
	gotoxy(10,10);printf("Octal para as demais bases");
	gotoxy(10,12);printf("Hexadecimal para as demais bases");
	gotoxy(10,14);printf("Sobre");
	gotoxy(10,18);printf("<ESC> Sair");
	gotoxy(10,20);printf("<SPACE> Ajuda");

   	while(tecla!=27){
   		gotoxy(10,14);tecla = getch();

   		if(tecla == 80 && cont<=8){ // para baixo
   			gotoxy(7,4+cont);printf("  ");
   			cont+=2;
			gotoxy(7,4+cont);printf("->");
		}

		if(tecla == 72 && cont>2){ // para cima
   			gotoxy(7,4+cont);printf("  ");
   			cont-=2;
			gotoxy(7,4+cont);printf("->");
		}

		if(tecla == 13){
			switch(cont){
				case 2:
					converteBinario();
					break;
				case 4:
					converteDecimal();
					break;
				case 6:
					converteOctal();
					break;
				case 8:
					converteHexa();
					break;
				case 10:
					sobre();
					break;
			}
		}

		if(tecla==32){
			ajuda();
		}
	}

	sair();

}

void sair(){
	system("cls");
	gotoxy(30,3);printf("Obrigada por utilizar o nosso sistema!\n\n");
	exit(0); // força o fechamento do programa;
}

void hideCursor(){
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void showCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x,int y){
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y}); //posiciona cursor na tela
}

int main(){
	// menu();
}

