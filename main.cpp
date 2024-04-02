#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <regex>
#include "analisador.h"
#include "stdLibList.h"

int main(void){
    FILE *file;
    char nome_arquivo[12] = "entrada.txt";
    char str[25];
    memset(&str[0], 0, sizeof(str));
    int cont_linha, cont_coluna, cont_caracter;
    int i = 0;

    typedef struct no{
    char endereco[20];
    char lexema[20];
    char *token;
    char *padrao;
    char *ocorrencia;
    struct no *next;
    }no;

    if((file = fopen(nome_arquivo, "r")) == NULL){
        puts("Não existe arquivo no diretório");
        exit(1);
    }
    no* n = initialize();

	while(!feof(file)){
	   fgets(str, 100, file);
	   cont_linha++;
       int str_len = strlen(str);
       str_len++;
       char new_str[str_len];
       memset(&new_str[0], 0, sizeof(new_str));

       //crio um outro array limpo(new_str) com apenas os elementos necessários.
       for(i = 0; i < str_len; i++){
           if(!isspace(str[i]) || verifica_se_num(str[i]) || verifica_se_op(str[i]) || verifica_se_parentese(str[i]) || verifica_se_end_of_statement(str[i]) || verifica_se_letra(str[i])){
               char c = str[i];
               append(new_str, c);
           }
       }


       char lexema[20];
       char aux_lexema[20];
       memset(&lexema[0], 0, sizeof(lexema));
       memset(&aux_lexema[0], 0, sizeof(aux_lexema));
       contador_de_caract = 0;

       for(i = 0; i <= str_len; i++){
          char atual = new_str[i];
          char anterior = i == 0 ? "" : new_str[i-1];
          cont_caracter++;

          if(i ==0 || i == 1){
             append(lexema, atual);
          }

          if(i > 1 && getTipoChar(atual) == getTipoChar(anterior)){
              append(lexema, atual);
          }else if(i > 1 && getTipoChar(atual) != getTipoChar(anterior)){
              strcpy(aux_lexema, lexema);
              if(verifica_se_num(anterior)){
                  no = insert(no, aux_lexema, "NUMBER", "Numeros seguidos de numeros.", "1");
              }else if(verifica_se_op(anterior)){
                  no = insert(no, aux_lexema, "OPERATOR", "Operadores.", "1");
              }else if(verifica_se_parentese(anterior)){
                  no = insert(no, aux_lexema, "PARENTESES", "Abertura ou fechamento de parenteses().", "1");
              }else if(verifica_se_palavra(lexema)){
                  no = insert(no, aux_lexema, "PALAVRA", "Variavel ou palavra reservada.", "1");
              }else{
                  no = insert(no, aux_lexema, "END_OF_STATEMENT", ";", "1");
              }

              memset(&lexema[0], 0, sizeof(lexema));
              append(lexema, atual);
           }
       }
       memset(&new_str[0], 0, sizeof(new_str));
	}

	printList(no);
    fclose(file);


    printf("Hello world!\n");
    return 0;
}
