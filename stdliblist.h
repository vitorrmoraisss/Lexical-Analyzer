#ifndef STDLIBLIST_H_INCLUDED
#define STDLIBLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char *endereco;
  char lexema[20];
  char *token;
  char *padrao;
  char *ocorrencia;
  struct node* next;
}Node;

Node* initialize(void){
    return NULL;
}

Node* insert(Node* actualList, char lexema[], char token[], char padrao[], char ocorrencia[]){
    Node* newNode = (Node*) malloc(sizeof(Node));
    int contador_de_ocorrencia = 1;
    if(newNode == NULL){
        printf("Nao foi possivel criar o no da lista");
        exit(-1);
    }
    strcpy(newNode -> lexema, lexema);
    newNode -> endereco = &lexema;
    newNode -> token = token;
    newNode -> padrao = padrao;
    newNode -> next = NULL;

    if(actualList == NULL){
       actualList = newNode;
    } else {
       Node* current = actualList;
        while(current -> next != NULL){
         if(strcmp(current -> lexema, lexema) == 0) {
             contador_de_ocorrencia++;
         }
         current = current -> next;
       };
       newNode -> ocorrencia = contador_de_ocorrencia;
       current -> next = newNode;
    }
    return actualList;
}

void printList(Node* list){
	Node* aux_list = list;
    char lexms_array[1000][1000];
    int cfr = 0;
	int cont = 0;
    do{
        strcpy(lexms_array[cfr], aux_list-> lexema);
        cfr++;
        printf("\n================================================\n");
        printf("Endereco: %p\n", aux_list -> endereco);
        printf("Lexema: %s\n", aux_list-> lexema);
        printf("Token: %s\n", aux_list -> token);
        printf("Padrao: %s\n", aux_list -> padrao);
        printf("Ocorrencia: %d\n", aux_list -> ocorrencia);
        printf("================================================\n");


        FILE *file;
        file = fopen("tabela_simbolos.txt" , "a");

        if (file == NULL) {
            printf ("Arquivo nao pode ser aberto!");
            getchar();
            exit (1);

        }

        fprintf(file, "\n================================================\n");
        fprintf(file, "Endereco: %d\n", &aux_list);
        fprintf(file, "Lexema: %s\n", aux_list->lexema);
        fprintf(file, "Token: %s\n", aux_list -> token);
        fprintf(file, "Padrao: %s\n", aux_list -> padrao);
        fprintf(file, "Ocorrencia: %d\n", aux_list -> ocorrencia);
        fprintf(file, "================================================\n");

        fclose(file);



        FILE *file2;
        file2 = fopen("token.txt" , "a");

        if (file2 == NULL) {
            printf ("Arquivo nao pode ser aberto!");
           getchar();
           exit (1);

        }

        fprintf(file2, "< ");
        fprintf(file2, "%s", aux_list -> token);
        fprintf(file2, ", %d", aux_list -> ocorrencia);
        fprintf(file2, ">; ");

        fclose(file2);

        cont++;
        aux_list = aux_list -> next;
    }while(aux_list != NULL);
}

#endif // STDLIBLIST_H_INCLUDED
