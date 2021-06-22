#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdbool.h>
#include "calc_helper.h"
#include <math.h>
#include <stdio.h>
#include "cola.h"
#include "pila.h"
#include "/home/joa/codigo/C/tp1_v2/gestor/strutil.h"

#define ERROR "ERROR"

//

void imprimir_traducidos(cola_t* cola){
    struct calc_token* aux;
    while(!cola_esta_vacia(cola)){
        aux = (struct calc_token*)cola_desencolar(cola);
        if(aux->type == TOK_NUM) printf("%ld", aux->value);
        if(aux->type == TOK_OPER){
            switch (aux->oper.op)
            {
            case OP_ADD:
                printf("+");
                break;
            case OP_SUB:
                printf("-");
                break;
            case OP_MUL:
                printf("*");
                break;
            case OP_DIV:
                printf("/");
                break;
            case OP_POW:
                printf("^");
                break;
            default:
                printf(ERROR);
                break;
            }
            
        }
        free(aux);
        printf(" ");
    }
    printf("\n");
}

void liberar_token(void* token){
    struct calc_token* tok = (struct calc_token*)token;
    free(tok);
}

bool traductor(char** lista){
    pila_t* operadores = pila_crear();//Pila de numeros
    cola_t* cola = cola_crear();
    bool sigo = true;
    size_t indice = 0;//Indica el elemento de la lista
    struct calc_token* token; //token auxiliar para ir descargando la lista
    struct calc_token* aux; //Token auxiliar para las comparaciones
    while (sigo)
    {
        
        //final
        if(!lista[indice]){
        //Esto cuando termino de leer
        while(!pila_esta_vacia(operadores)) cola_encolar(cola, pila_desapilar(operadores)); 
        imprimir_traducidos(cola);
        cola_destruir(cola, liberar_token);
        pila_destruir(operadores);

        return true;
        }

        token = calloc(1, sizeof(struct calc_token));
        sigo = calc_parse(lista[indice], token);//Almaceno en el token auxiliar un elemento de la lista



        if(token->type == TOK_NUM) cola_encolar(cola, token);
        
        
        //Esta es la parte picante donde hay que actuar segun la precedencia y todo eso
        else if(token->type == TOK_OPER){
            while(!pila_esta_vacia(operadores)){
                aux = (struct calc_token*)pila_ver_tope(operadores);
                if((aux->oper.asociatividad>= token->oper.asociatividad && aux->oper.precedencia == ASSOC_LEFT)
                   || (aux->oper.asociatividad > token->oper.asociatividad && aux->oper.precedencia == ASSOC_RIGHT)){
                    cola_encolar(cola, pila_desapilar(operadores));
                }
                else break;
            }
            pila_apilar(operadores, token); 
        }


        else if(token->type == TOK_LPAREN) pila_apilar(operadores, token);

        //Esto cuando toca un parentesis derecho
        else if(token->type == TOK_RPAREN){
            aux = pila_ver_tope(operadores);
            while (aux->type != TOK_LPAREN)
            {
                cola_encolar(cola, pila_desapilar(operadores));
                aux = pila_ver_tope(operadores);
            }
            free(token);
            free(pila_desapilar(operadores));

        }

        indice++;
    }
    return true;
}

void infix(){
    char* cadena = NULL;
    size_t tam = 0;
    ssize_t cargados =  getline(&cadena, &tam, stdin);
    char** lista;
    while(cargados > 1){
        
    lista = dc_split(cadena);
    traductor(lista);
    free_strv(lista);
    cargados = getline(&cadena, &tam, stdin);
    }
    free(cadena);
    

}
int main(){
    infix();
    return 0;
}