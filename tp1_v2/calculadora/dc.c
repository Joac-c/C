#define _POSIX_C_SOURCE 200809L

#include "/home/joa/codigo/C/tp1_v2/gestor/strutil.h"
#include <stdlib.h>
#include <stdbool.h>
#include "calc_helper.h"
#include <math.h>
#include <stdio.h>
#define ERROR "ERROR\n\n"

/*
 OP_ADD,   // suma, +
    OP_SUB,   // resta, -
    OP_MUL,   // multiplicación, *
    OP_DIV,   // división entera, /
    OP_POW,   // potencia, ^
    OP_LOG,   // logaritmo, "log"
    OP_RAIZ,  // raíz cuadrada, "sqrt"
    OP_TERN,  // operador ternario, ?:

*/

bool sumar(calc_num b, calc_num a, calc_num* resultado){
    *resultado = a + b;
    return true;
}
bool restar(calc_num b, calc_num a, calc_num* resultado){
    *resultado = b - a;
    return true;
}
bool multiplicar(calc_num b, calc_num a, calc_num* resultado){
    *resultado = a*b;
    return true;
}
bool dividir(calc_num b, calc_num a, calc_num* resultado){
    if(a == 0) return false;
    *resultado = b/a;
    return resultado;
}
bool potenciar(calc_num b, calc_num a, calc_num* resultado){
    if(a < 2) return false;
    *resultado = (calc_num)pow((double)b, (double)a);
    return true;
}
bool logear(calc_num b, calc_num a, calc_num* resultado){
    //Para esto hay que encontrar un log generico. ni idea lol.
    if(a < 2) return false;
    *resultado = (calc_num)(log((double)a)/log((double)b));
    return true;
}
bool raiz(calc_num a, calc_num* resultado){
    if(a<0) return false;
    *resultado = (calc_num)sqrt((double)a);
    return true;
}
bool ternario(calc_num c, calc_num b, calc_num a, calc_num* resultado){
    *resultado = b ? a : c;
    return true;
}


bool levantar_error(){
    printf(ERROR);
    return false;
}


void calcular_post(char** tokens){
    
    pilanum_t* numeros = pilanum_crear();//Pila de numeros
    bool sigo = true;
    size_t indice = 0;//Indica el elemento de la lista
    struct calc_token* token = calloc(1, sizeof(struct calc_token)); //token auxiliar para ir descargando la lista
    
    while(sigo){
        calc_num resultado; //Aca se almacena el resultado de cada operacion individual y el que se imprime al final
        
        
        //Lo que hago cuando llego al final
        
        if(!tokens[indice]){
            if(desapilar_num(numeros, &resultado)){
                if(pila_esta_vacia(numeros)) printf("El resultado es: %ld\n\n", resultado);
            }
            else levantar_error();
            break;
        }
        else if(tokens[indice][0] == '\0') levantar_error();



        if(!calc_parse(tokens[indice], token)){
            levantar_error(); 
            break;
        }

        if(token->type == TOK_NUM) apilar_num(numeros, token->value); //Si es un numero, apilo su valor

        else if (token->type == TOK_OPER) //Si es un operando...
        {
        
            
            calc_num a;
            calc_num c;
            calc_num b;
            
            
            
            if(!desapilar_num(numeros, &a)) sigo = levantar_error();
            if(token->oper.op != OP_RAIZ) if(!desapilar_num(numeros, &b)) sigo = levantar_error();
            if(!sigo) break;

            
            
            switch (token->oper.op)
            {
            case OP_ADD:
                sumar(b, a, &resultado);
                apilar_num(numeros, resultado);
                break;
            case OP_SUB:
                if(!restar(b, a, &resultado)) sigo = levantar_error();
                else apilar_num(numeros, resultado);
                break;
            case OP_MUL:
                multiplicar(b, a, &resultado);
                apilar_num(numeros, resultado);
                break;
            case OP_DIV:
                if(!dividir(b, a, &resultado)) sigo = levantar_error();
                else apilar_num(numeros, resultado);
                break;
            case OP_POW:
                if(!potenciar(b, a, &resultado)) sigo = levantar_error();
                else apilar_num(numeros, resultado);
                break;
            case OP_LOG:
                if(!logear(b, a, &resultado)) sigo = levantar_error();
                else apilar_num(numeros, resultado);
                break;
            case OP_RAIZ:
                if(!raiz(a, &resultado)) sigo = levantar_error();
                else apilar_num(numeros, resultado);
                break;
            case OP_TERN:
                if(!desapilar_num(numeros, &c) || !ternario(c, b, a, &resultado)) sigo = levantar_error();
                else apilar_num(numeros, resultado);
                break;
            default:
                sigo = levantar_error(); 
                break;
            }
        }
    indice++;
    }
    pilanum_destruir(numeros);
    free(token);
    return;
}


void dc(){
    char* cadena = NULL;
    size_t tam = 0;
    printf("Escribí tu cuenta en notacion postfija: \n");
    ssize_t cargados =  getline(&cadena, &tam, stdin);
    while(cargados > 1){
        
    char** tokens = dc_split(cadena);
    calcular_post(tokens);
    free_strv(tokens);
    cargados = getline(&cadena, &tam, stdin);
    }
    free(cadena);
    

}

int main(){
    dc();
    return 0;
}