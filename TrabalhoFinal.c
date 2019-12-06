#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN64
# define CLEAR_SCREEN system ("cls")
#else
# define CLEAR_SCREEN puts("\x1b[H\x1b[2J")
#endif

//Agenda telefonica criada por: Larissa Brasil e Isaac Ramos.

struct Contato{    //ID do contato
	char nome[30];
	char fone[30];
};
struct Contato contato;

//todas as funções recebem o vetor de struct e o tamanho.

int pesquisa_contatoDelete(struct Contato *contato, int tam, char nome_pesq[]){		//pesquisa contato para remover
	int i, quant = 0;
	char temp[30];
	for(i = 0; i < tam; i++){
		if(strcmp(nome_pesq, contato[i].nome) == 0){ //comparação entre strings
			strcpy(temp, contato[i].nome);
			strcpy(contato[i].nome, contato[i + 1].nome);
			strcpy(contato[i + 1].nome, temp);
			quant = 1;
		}
	}
	CLEAR_SCREEN; //limpa a tela
	printf("Usuario Removido.\n");
	if (quant == 0){
		CLEAR_SCREEN;  //system("cls"); para windows
		printf("Usuario Nao encontrado.\n");
	}
	return quant;
}

void altera_Contato(struct Contato *contato, int tam){   //altera contato
	int i, pos, op;
	char nome1[30], nome_lista[30];

	listar_contatos(contato, tam);	//lista primeiro os contatos

	printf("\nDigite o nome a ser alterado: ");
	scanf("%s", &nome_lista);
	
	for(i = 0; i < tam; i++){
		if(strcmp(nome_lista, contato[i].nome) == 0){ //busca contato pesquisado pelo nome
			printf("Altera nome: ");
			scanf("%s", &nome1);
			
			strcpy(contato[i].nome, nome1);
			CLEAR_SCREEN;
			printf("\nAlterado!"); //altera com sucesso o nome
			break;
			}
		}
}

void altera_Fone(struct Contato *contato, int tam){ //altera o telefone
	int i, pos, op;
	char fone1[30], nome_lista[30];
	
	CLEAR_SCREEN;//limpa tela
	listar_contatos(contato, tam); //lista 
	
	printf("\nDigite o nome a ser alterado: ");
	scanf("%s", &nome_lista);
	
	for(i = 0; i < tam; i++){
		if(strcmp(nome_lista, contato[i].nome) == 0){	//busca contato pesquisado pelo nome
			printf("Altera fone: ");		//altera fone
			scanf("%s", &fone1);	
			
			strcpy(contato[i].fone, fone1);
			CLEAR_SCREEN;
			printf("\nAlterado!");	//fone alterado
			break;
			}
		}
}

void listar_contatos(struct Contato *contato, int tam){ //lista os contatos
	int i;						// lista todos e quantos contatos.
	for(i = 0; i < tam; i++){
		printf("\n\t[%d] Nome: %s\n"
				"\tFone: %s\n", i+1, contato[i].nome, contato[i].fone);
	}
	printf("\n------------- [%d] Contatos -------------\n", i);
}

void ordena(struct Contato *contato, int tam){  //ordena vetor
	int i, j;
	char temp[tam];			//bubblesort para ordenar o vetor de struct
	
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

int inserir_contato(struct Contato *contato, int tam){ //insere contato
											//insere contato
	printf("Nome do Contato: ");			//caso nome == "0", volta para o menu
	scanf("%s", contato[tam].nome);
	
	if(strcmp(contato[tam].nome, "0") == 0)
		return 0;
	
	printf("Fone do Contato: ");
	scanf("%s", contato[tam].fone);
	
	CLEAR_SCREEN; //system("cls");
	printf("Adicionado com sucesso.\n");
	
	return 1;
}

void pesquisa_contato(struct Contato *contato, int tam, char nome_pesq[]){ //pesquisa contato
	int i;
	for(i = 0; i < tam; i++){
		if(strcmp(nome_pesq, contato[i].nome) == 0){  //busca contato pelo nome
			system("cls");
			printf("\nContato: \nNome: %s\nFone: %s\n", contato[i].nome, contato[i].fone);
			return ;
		}
	}
	CLEAR_SCREEN; //system("cls");
	printf("Usuario nao encontrado.\n");
}

void menu(){		//menu de operações
	printf("\nMenu: \n"
			"[1]-Inserir\n"
			"[2]-Remover\n"
			"[3]-Pesquisar\n"
			"[4]-Listar Contatos\n"
			"[5]-Alterar\n"
			"[0]-Sair\n");
}

int main(){
	int op, n, tam = 0, i = 0, quant, inseriu, op2;  //variáveis utilizadas
	struct Contato *p;			// ponteiro para vetor
	char nome_pesq[20];  //variável para receber o nome que deseja ser pesquisado na função pesquisar
	int tamanho;
	
	FILE* f;
//--------------------------------------------------------
	time_t rawtime;
	struct tm * timeinfo;			//bonus: implementação do relógio com data
	int hora;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	hora = asctime(timeinfo);
//--------------------------------------------------------	
	
	
	//tamanho referente a quantidade inicial de contatos;
	tamanho = 100;
	if(!(p = (struct Contato *) malloc ( tamanho * sizeof(struct Contato)))){
		printf("Memoria insuficiente.");
	}
	
	//abre o arquivo para leitura e preserva na memória
	int k = 0;
	
	f=fopen("trabalhoFinal.txt","r");
	
	if(f == NULL)
		printf("ERRO: arquivo inexistente");
	else{
		while(1){
			fscanf(f,"%s",&p[k].nome);			//lê nome
			fscanf(f,"%s",&p[k].fone);			//lê fone
			
			if(feof(f))
				break;
				
			k++;
		}
		fclose(f); //fecha arquivo
	}
	tam=k;
	

	do{
		printf("time = %s", hora);
		menu();
		scanf("%d", &op);  //recebe a operação
		if( op == 0){
			break;
		}else if(op < 0 || op > 5){ //validação da resposta
				printf("Resposta Invalida, digite novamente\n");
				continue;
		}	
		switch(op){
			case 1:
					inseriu = inserir_contato(p, tam);	//insere contato
					if(inseriu == 1){	//se inserir, realoca
						tam++;
						p = realloc(p,(tam + 2)*sizeof(struct Contato));	//realocamento de p
						i++;
					}
				break; 
				
			case 2:	printf("Digite o Nome do contato: \n");			//remover contato
					scanf("%s", &nome_pesq);
					quant = pesquisa_contatoDelete(p, tam, nome_pesq);
					if(quant == 1) //se removeu, diminui uma posição
						tam--;
				break;
			case 3:	printf("Digite o Nome do contato: \n");			//pesquisar contato
					scanf("%s", &nome_pesq);
					pesquisa_contato(p, tam, nome_pesq);
				break;
				
			case 4: listar_contatos(p, tam);						//listar contatos
				break;
				
			case 5:	do{												//Alterar contato: Alterar Nome ou Fone 
					printf("\nAlterar: [1]-Nome [2]-Fone: ");
					scanf("%d", &op2);
					}while(op2 < 1 || op2 > 2); //validação da resposta
					
					CLEAR_SCREEN;
					if(op2 == 1)
						altera_Contato(p, tam);
					else
						altera_Fone(p, tam);
				break;
		}
	ordena(p, tam);
	
	}while(op);

	//abre o arquivo novamente, apaga o conteúdo antigo e escreve o conteúdo manipulado.
	i = 0;
	
	f=fopen("trabalhoFinal.txt","w");
	
	if(f == NULL)
		printf("ERRO: arquivo inexistente");
	else{
		for(i=0;i<tam;i++){
			fprintf(f,"%s\n",p[i].nome);		//traz os nomes para a memória
			fprintf(f,"%s\n",p[i].fone);		//traz os fones para a memória
		}
		printf("Salvo com sucesso!\n");
		fclose(f);	//fecha arquivo
	}
	return 0;
}
