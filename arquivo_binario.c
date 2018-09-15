/*Programa desenvolvido por Henrique Marciano da Silva e Bianca Dias Barbosa.
Programa de arquivos binários e arquivos texto.

BSI - 2018
Algoritmos II - Profª Andrea*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#include<limits.h>
#include<unistd.h>
typedef struct Dados {
	int id, quant, status;
	char nome[50], marca[20], cat[20];
	float preco;
	
} market;

void menu();
void nomeArq(char nome[]);
void pegaPasta();
void cadastrar(char cwd[]);
void consultarTudo();
void consultarId();
void consultarCat();
void exclusaoLogica();
void menuBoasVindas();
void sair();
void moldura();
void hideCursor();
void showCursor();
void gotoxy(int x,int y);
void personalizacao();
void ajuda();
void sobre();
void pegaDiretorioAtual();

void pegaDiretorioAtual(char cwd1[]){
	char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       printf("getcwd() error");
       exit(1);
   }
   
   strcpy(cwd1, cwd);
   
}

void menu(char cwd[]){
	system("cls");
	
	//printf("Current working dir: %s\n", cwd);
	
	gotoxy(70,40);system("date/t");
	gotoxy(72,42);system("time/t");
	int tecla;
	int cont = 2;
	hideCursor();
	gotoxy(30,3);printf("Supermercado Bick - Menu principal");
	gotoxy(7,6);printf("->");
	gotoxy(10,6);printf("Cadastrar alimentos"); //2
	gotoxy(10,8);printf("Alterar alimentos"); //4
	gotoxy(10,10);printf("Excluir alimentos"); // 6
	gotoxy(10,12);printf("Consultar todos os registros");
	gotoxy(10,14);printf("Consultar por id");
	gotoxy(10,16);printf("Consultar por categoria");
	gotoxy(10,18);printf("Trocar o nome do arquivo");
	gotoxy(10,20);printf("Remover o arquivo do disco");
	gotoxy(10,22);printf("Alterar data e hora"); //18
	gotoxy(10,24);printf("Criar uma pasta");
	gotoxy(10,26);printf("Alterar o nome de uma pasta");	
	gotoxy(10,28);printf("Mudar um arquivo de pasta");
	gotoxy(10,30);printf("Personalizacao"); //26
	gotoxy(10,32);printf("Sobre");
	gotoxy(10,36);printf("<ESC> Sair");
	gotoxy(10,38);printf("<F1> Ajuda");

   	while(tecla!=27){
   		gotoxy(10,14);tecla = getch();

   		if(tecla == 80 && cont<=26){ // para baixo
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
					cadastrar(cwd);
					break;
//				case 4:
//					break;
//				case 6:
//					break;
				case 8:
					consultarTudo(cwd);
					break;
//				case 10:
//					consultarId();
//					break;
//				case 12:
//					consultarCat();
//					break;
				case 18:
					// alterarData();
					break;
				case 26:
					personalizacao();
					break;
				case 28:
					sobre();
					break;
			}
		}

		if(GetAsyncKeyState(VK_F1)){
			ajuda();
		}
	}

	sair();

}

void nomeArq(char nome[]){
	showCursor();
	printf("Digite o nome do arquivo: ");
	fflush(stdin);
	gets(nome);
}

void pegaPasta(){
	char nome[20];
	showCursor();
	printf("Digite o nome da pasta: ");
	fflush(stdin);
	gets(nome);
	mkdir(nome);
	chdir(nome);
}

void cadastrar( char cwd[]){
	system("cls");
	FILE *A;
	market BC;
	char resp, nome[20];
	gotoxy(30,3);printf("Supermercado Bick - Cadastrar");
	gotoxy(10,6);pegaPasta();
	gotoxy(10,8);nomeArq(nome);
	strcat(nome, ".bh");
	
	if((A = fopen(nome, "r+b")) == NULL)
		if((A = fopen(nome, "wb")) == NULL){
			printf("\nErro ao abrir o arquivo.");
			exit(1);
		}
	
	fseek(A, 0, SEEK_END);
	
	do{
		system("cls");
		gotoxy(30,3);printf("Supermercado Bick - Cadastrar");
		gotoxy(10,6);printf("Digite os dados do seu produto:");
		fflush(stdin);
		BC.status = 1;
		gotoxy(10,8);printf("Id: ");
		scanf("%d", &BC.id);
		fflush(stdin);
		gotoxy(10,10);printf("Nome: ");
		gets(BC.nome);
		gotoxy(10,12);printf("Marca: ");
		gets(BC.marca);
		gotoxy(10,14);printf("Categoria: ");
		gets(BC.cat);
		gotoxy(10,16);printf("Quantidade: ");
		scanf("%d", &BC.quant);
		gotoxy(10,18);printf("Preco: ");
		scanf("%f", &BC.preco);
		fwrite(&BC, sizeof(BC), 1, A);
		do{
			gotoxy(10,20);printf("Deseja cadastrar mais um? (S/N): ");
			fflush(stdin);
			scanf("%c", &resp);
			resp = toupper(resp);
		} while (resp != 'S' && resp != 'N');
	
	} while (resp == 'S');
	
	fclose(A);
	chdir(cwd);
	//system("cd");
	menu(cwd);
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

void consultarTudo(char cwd[]){
	FILE *A;
	market BC;
	char nome[20];
	int aux = 4;
	int tecla = 32;
	system("cls");
	gotoxy(30,4);printf("Supermercado Bick - Consultar tudo");
	gotoxy(10,6);pegaPasta();
	gotoxy(10,8);nomeArq(nome);
	strcat(nome, ".bh");
	
	if((A = fopen(nome, "rb")) == NULL){
		printf("\nErro ao abrir o arquivo.");
		exit(1);
	}
	
	system("cls");
	gotoxy(30,3);printf("Supermercado Bick - Consultar tudo");
		
	while((fread(&BC, sizeof(BC), 1, A)) == 1) {
		
		if(BC.status == 1){
			gotoxy(10,aux+=2);printf("Id: %d", BC.id);
			gotoxy(10,aux+=2);printf("Nome: %s", BC.nome);
			gotoxy(10,aux+=2);printf("Marca: %s", BC.marca);
			gotoxy(10,aux+=2);printf("Categoria: %s", BC.cat);
			gotoxy(10,aux+=2);printf("Quantidade: %d", BC.quant);
			gotoxy(10,aux+=2);printf("Preco: %.2f", BC.preco);
			aux+=2;
		}
		
	}
	
	fclose(A);
	chdir(cwd);
	//system("cd");
	printf("\n\n\n\n\t<ESC> Voltar ao menu principal.");
	tecla = getch();
	while(tecla!=27){
		tecla = getch();
	}
	if(tecla == 27)
		menu(cwd);
}

void ajuda(char cwd[]){
	int tecla = 32;
	system("cls");
	gotoxy(70,40);system("date/t");
	gotoxy(72,42);system("time/t");
	gotoxy(30,3);printf("Supermercado Bick - Ajuda");
	gotoxy(10,6);printf("Utilize as setas do seu teclado para mover a seta para cima ou para baixo.");
	gotoxy(10,8);printf("Para escolher uma opcao, aperte ENTER.");
	gotoxy(10,10);printf("Para finalizar o programa, aperte ESC");
	gotoxy(10,12);printf("id = Numero identificador do produto");
	gotoxy(10,14);printf("Divirta-se!");
	gotoxy(10,18);printf("<ESC> Voltar ao menu principal.");

	tecla = getch();

	while(tecla!=27){
		tecla = getch();
	}

	if(tecla == 27)
		menu(cwd);
}

void sobre(char cwd[]){
	int tecla = 32;
	system("cls");
	gotoxy(70,40);system("date/t");
	gotoxy(72,42);system("time/t");
	gotoxy(30,3);printf("Supermercado Bick - Sobre");
	printf("\n\n\n\tTrabalho de arquivos desenvolvido por Bianca Dias e Henrique Marciano\n\t");
	printf("\n\tDisciplina: Algoritmos II\n\t");
	printf("\n\tProfessora: Andrea");
	printf("\n\n\t\t\t\tBSI - 2018");
	printf("\n\n\n\t<ESC> Voltar ao menu principal.");

	tecla = getch();

	while(tecla!=27){
		tecla = getch();
	}

	if(tecla == 27)
		menu(cwd);
	
}

void menuBoasVindas(){
	char cwd[PATH_MAX];
	pegaDiretorioAtual(cwd);
	
	char tecla;
	int aux = 1;
	int tent = 1;
	gotoxy(30,13);printf("Bem-vindo ao supermercado Bick");
	gotoxy(24,16);printf("Pressione qualquer tecla para continuar...");
	gotoxy(70,40);system("date/t");
	gotoxy(72,42);system("time/t");
	hideCursor();

	if(tecla = getch()){
		menu(cwd);
	}
}

void personalizacao(char cwd[]){
	char fundo;
	char esc;
	int pers;
	char fonte;
	char cSystem[255];
	system("cls");
	gotoxy(70,40);system("date/t");
	gotoxy(72,42);system("time/t");
	gotoxy(30,3);printf("Supermercado Bick - Personalizacao");
	gotoxy(30,6); printf("0 - Preto         8 - Cinza");
	gotoxy(30,8); printf("1 - Azul          9 - Azul claro");
	gotoxy(30,10); printf("2 - Verde         A - Verde claro"); 
	gotoxy(30,12); printf("3 - Verde-agua    B - Verde-agua claro"); 
	gotoxy(30,14); printf("4 - Vermelho      C - Vermelho claro"); 
	gotoxy(30,16); printf("5 - Roxo          D - Lilas"); 
	gotoxy(30,18); printf("6 - Amarelo       E - Amarelo claro");
	gotoxy(30,20); printf("7 - Branco        F - Branco brilhante");
	gotoxy(30,22);printf("\n\tCor do fundo: ");
	fundo=getche();
	gotoxy(30,24);printf("\n\tCor da fonte: ");
 	fonte=getche();
	sprintf(cSystem, "color %c%c", fundo, fonte);
    system(cSystem);
	gotoxy(10,34);printf("<ESC> Voltar ao menu principal.");
	esc=getch();
	if(esc!=27)
	{
		do{
	   		esc=getch();
		}while(esc!=27);	
	}
	if(esc==27)
	{
		menu(cwd);
	}	
}

void sair(){
	system("cls");
	gotoxy(30,3);printf("Obrigada por utilizar o sistema do supermercado Bick!\n\n");
	exit(0); // força o fechamento do programa;
}

void moldura(){ //desenha a moldura
	int a;
	unsigned char caracter=178;
	int i = 100, j = 50;
	system("cls");
	//parede de cima horizontal
	for(a=0;a<j+1;a++){
		gotoxy(a,0);
		printf("%c",caracter);
	}

	//parede da direita vertical
	for(a=1;a<i;a++)
    {
        gotoxy(j,a);
        printf("%c",caracter);
    }

    //parede de baixo horizontal
    for(a=j;a>=0;a--)
    {
        gotoxy(a,i);
        printf("%c",caracter);
    }

    //parede da esquerda vertical
    for(a=i;a>0;a--)
    {
       	gotoxy(0,a);
        printf("%c",caracter);
    }
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
	system("color 0E");
	// system("mode con:cols=100 lines=50");
	menuBoasVindas();
}
