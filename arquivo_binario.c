#include<stdio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>

typedef struct Dados {
	int id, quant, status;
	char nome[50], marca[20], cat[20];
	float preco;
	
} market;

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
					//converteBinario();
					break;
				case 4:
					//converteDecimal();
					break;
				case 6:
					//converteOctal();
					break;
				case 8:
					//converteHexa();
					break;
				case 10:
					//sobre();
					break;
			}
		}

		if(tecla==32){
			//ajuda();
		}
	}

	sair();

}

void nomeArq(char nome[]){
	printf("\nDigite o nome do arquivo: ");
	fflush(stdin);
	gets(nome);
}

void cadastrar(){
	FILE *A;
	market BC;
	char resp, nome[20];
	
	nomeArq(nome);
	strcat(nome, ".bh");
	
	if((A = fopen(nome, "r+b")) == NULL)
		if((A = fopen(nome, "wb")) == NULL){
			printf("\nErro ao abrir o arquivo.");
			exit(1);
		}
	
	do{
		system("cls");
		printf("\nDigite os dados do seu produto: \n");
		fflush(stdin);
		BC.status = 1;
		printf("\nId: ");
		scanf("%d", &BC.id);
		fflush(stdin);
		printf("\nNome: ");
		gets(BC.nome);
		printf("\nMarca: ");
		gets(BC.marca);
		printf("\nCategoria: ");
		gets(BC.cat);
		printf("\nQuantidade: ");
		scanf("%d", &BC.quant);
		printf("\nPreco: ");
		scanf("%f", &BC.preco);
		fwrite(&BC, sizeof(BC), 1, A);
		do{
			printf("\nDeseja cadastrar mais um? (S/N): ");
			fflush(stdin);
			scanf("%c", &resp);
			resp = toupper(resp);
		} while (resp != 'S' && resp != 'N');
	
	} while (resp == 'S');
	
	fclose(A);
}

void consultarId(){
	FILE *A;
	market BC;
	char nome[20];
	int id, achou = 0;
	
	nomeArq(nome);
	strcat(nome, ".bh");
	
	if((A = fopen(nome, "rb")) == NULL){
		printf("\nErro ao abrir o arquivo.");
		exit(1);
	}
	
	printf("\nDigite o Id que deseja consultar: ");
	scanf("%d", &id);
	
	system("cls");
	
	while((fread(&BC, sizeof(BC), 1, A)) == 1 && achou == 0){
		if(id == BC.id){
			achou = 1;
			printf("\nId: %d", BC.id);
			printf("\nNome: %s", BC.nome);
			printf("\nMarca: %s", BC.marca);
			printf("\nCategoria: %s", BC.cat);
			printf("\nQuantidade: %d", BC.quant);
			printf("\nPreco: %.2f\n\n", BC.preco);
		}
	}
	
	if(achou == 0){
		printf("\nNao existe produto registrado com esse id.");
	}
	
	fclose(A);
	system("pause");
}

void consultarCat(){
	FILE *A;
	market BC;
	char nome[20], cat[20];
	int achou = 0;
	
	nomeArq(nome);
	strcat(nome, ".bh");
	
	if((A = fopen(nome, "rb")) == NULL){
		printf("\nErro ao abrir o arquivo.");
		exit(1);
	}
	
	printf("\nDigite a categoria que deseja consultar: ");
	fflush(stdin);
	gets(cat);
	
	system("cls");
	
	while((fread(&BC, sizeof(BC), 1, A)) == 1){
		if(stricmp(cat, BC.cat) == 0){
			achou = 1;
			printf("\nId: %d", BC.id);
			printf("\nNome: %s", BC.nome);
			printf("\nMarca: %s", BC.marca);
			printf("\nCategoria: %s", BC.cat);
			printf("\nQuantidade: %d", BC.quant);
			printf("\nPreco: %.2f\n\n", BC.preco);
		}
	}
	
	if(achou == 0){
		printf("\nNao existe produto registrado nessa categoria ou essa categoria nao existe.\n");
	}
	
	fclose(A);
	system("pause");
}

void exclusaoLogica(){
	FILE *A;
	market BC;
	char nome[20];
	int id;
	
	nomeArq(nome);
	strcat(nome, ".bh");
	
	if((A = fopen(nome, "r+b")) == NULL){
		printf("\nErro ao abrir o arquivo.");
		exit(1);
	}
	
	printf("\nDigite o Id do produto que deseja excluir: ");
	scanf("%d", &id);
	
	while(fread(&BC, sizeof(BC), 1, A) == 1){
		if(id == BC.id && BC.status == 1){
			BC.status = 0;
			fseek(A, -sizeof(BC), SEEK_CUR);
			fwrite(&BC, sizeof(BC), 1, A);
			fclose(A);
		}
	}
	
	
}

void consultarTudo(){
	FILE *A;
	market BC;
	char nome[20];
	
	nomeArq(nome);
	strcat(nome, ".bh");
	
	if((A = fopen(nome, "rb")) == NULL){
		printf("\nErro ao abrir o arquivo.");
		exit(1);
	}
	
	system("cls");
	
	while((fread(&BC, sizeof(BC), 1, A)) == 1) {
		
		if(BC.status == 1){
			printf("\nId: %d", BC.id);
			printf("\nNome: %s", BC.nome);
			printf("\nMarca: %s", BC.marca);
			printf("\nCategoria: %s", BC.cat);
			printf("\nQuantidade: %d", BC.quant);
			printf("\nPreco: %.2f\n\n", BC.preco);
		}
		
	}
	
	fclose(A);
	system("pause");
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

