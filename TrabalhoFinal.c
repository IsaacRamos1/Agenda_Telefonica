#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN64
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif

//Agenda telefonica criada por: Artur Suleimane e Isaac Ramos
//perfil do contato
//Aplicativo 

struct Contato{
	char nome[30];
	char fone[30];
};
struct Contato contato;

int pesquisa_contatoDelete(struct Contato *contato, int tam, char nome_pesq[]){
	int i, quant = 0;
	char temp[30];
	for(i = 0; i < tam; i++){
		if(strcmp(nome_pesq, contato[i].nome) == 0){
			strcpy(temp, contato[i].nome);
			strcpy(contato[i].nome, contato[i + 1].nome);
			strcpy(contato[i + 1].nome, temp);
			quant = 1;
		}
	}
	CLEAR_SCREEN;
	printf("Usuario Removido.");
	if (quant == 0){
		CLEAR_SCREEN;  //system("cls"); para windows
		printf("Usuario Nao encontrado.\n");
	}
	return quant;
}

void altera_Contato(struct Contato *contato, int tam){
	int i, pos, op;
	char novoNome[30], novoFone[30], nome;
	
	listar_contatos(contato, tam);
	
	printf("\nAltere: [1]-Nome [2]-Fone: \n");
	scanf("%d", &op);
	
	if(op == 1){
		printf("\nDigite o nome para ser alterado: ");
		scanf("%s", &nome);
		
		for(i = 0; i < tam; i++){
			if(strcmp(nome, *contato[i].nome) == 0){
				printf("\nNovo nome: ");
				scanf("%s", &novoNome);
				
				strcpy(contato[i].nome, nome);
				printf("\nAlterado!");
				break;
			}
		}
	}else if(op == 2){
		
		printf("\nDigite o nome do contato: ");
		scanf("%s", &nome);
		
			for(i = 0; i < tam; i++){
				if(strcmp(nome, *contato[i].nome)){
					printf("\nAltera fone: ");
					scanf("%s", &novoFone);
	
					strcpy(contato[i].fone, novoFone);
					printf("\nAlterado!");
					break;
				}
			}		
	}
	ordena(contato, tam);
}

void listar_contatos(struct Contato *contato, int tam){
	int i;
	for(i = 0; i < tam; i++){
		printf("\nNome: %s ==== Fone: %s\n", contato[i].nome, contato[i].fone);
	}
}

void ordena(struct Contato *contato, int tam){
	int i, j;
	char temp[tam];
	
	for(j = 0; j < tam; j++){
		for(i = 0; i < (tam - 1); i++){
			if(strcmp(contato[i].nome, contato[i + 1].nome) == 1){		//	contato[i].nome[0] > contato[i - 1].nome[0]
				strcpy(temp, contato[i + 1].nome);
				strcpy(contato[i + 1].nome, contato[i].nome);
				strcpy(contato[i].nome, temp);
			}
		}
	}
	
}

int inserir_contato(struct Contato *contato, int tam){
	
	printf("Nome do Contato: ");
	scanf("%s", contato[tam].nome);
	if(strcmp(contato[tam].nome, "0") == 0)
		return 0;
	printf("Fone do Contato: ");
	scanf("%s", contato[tam].fone);
	CLEAR_SCREEN; //system("cls");
	printf("Adicionado com sucesso.\n");
	return 1;
}

void pesquisa_contato(struct Contato *contato, int tam, char nome_pesq[]){
	int i;
	for(i = 0; i < tam; i++){
		if(strcmp(nome_pesq, contato[i].nome) == 0){
			system("cls");
			printf("\nContato: \nNome: %s\nFone: %s\n", contato[i].nome, contato[i].fone);
			return ;
		}
	}
	CLEAR_SCREEN; //system("cls");
	printf("Usuario nao encontrado.\n");
}

void menu(){
	printf("\nMenu: \n[1]-Inserir\n[2]-Remover\n[3]-Pesquisar\n[4]-Listar Contatos\n[5]-Alterar\t[0]-Sair\n");
}

int main(){
	int op, n, tam = 0, i = 0, quant, inseriu;
	struct Contato *p;
	char nome_pesq[20];
	
	if(!(p = (struct Contato *) malloc ( 2 * sizeof(struct Contato)))){
		printf("Memoria insuficiente.");
	}

	menu();
	do{
		scanf("%d", &op);
		if( op == 0){
			break;
		}else if(op < 0 || op > 5){
				printf("Resposta Invalida, digite novamente\n");
				continue;
		}	
		switch(op){
			case 1:
					inseriu = inserir_contato(p, tam);
					if(inseriu == 1){
						tam++;
						p = realloc(p,(tam + 2)*sizeof(struct Contato)); //aumenta o espa�o reservado para os contatos;
						ordena(p, tam);
						i++;
					}
				break; 
				
			case 2:	printf("Digite o Nome do contato: \n");			//remover
					scanf("%s", &nome_pesq);
					quant = pesquisa_contatoDelete(p, tam, nome_pesq);
					if(quant == 1)
						tam--;
				break;
			case 3:	printf("Digite o Nome do contato: \n");			//pesquisar
					scanf("%s", &nome_pesq);
					pesquisa_contato(p, tam, nome_pesq);
				break;
				
			case 4: listar_contatos(p, tam);						//listar
				break;
				
			case 5:	altera_Contato(p, tam);							//Alterar
				break;
		}
	menu();
	}while(op);
	return 0;
}