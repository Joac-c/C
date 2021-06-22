#include "lista.h"
#include <stdio.h>
#include <stdbool.h>

#define TILDE "✓"
#define CRUZ "✗"

#define ERROR -1
#define EXITO 0

int exitosas = 0;
int fallidas = 0;
int verificaciones = 0;


void verificar(bool afirmacion, const char* texto){
    /*Recibe un booleano generado comparando la salida de una funcion con cierto valor y un texto que describe la prueba a realizarse.
    De pasarse la prueba el texto se imprime antecedido con un tick, en caso contrario se imprime con una cruz*/
    if(afirmacion){
        printf("\n");
        printf(TILDE);
        exitosas++;
    }
    else{
        fallidas++;
        printf(CRUZ);
    }
    printf("%d -%s ",verificaciones, texto);
    verificaciones++;
    fflush(stdout);

}


unsigned char* elementos_prueba(unsigned char* elementos){

    for(int i = 0; i != 256; i++){
        elementos[i] = (unsigned char)(i);
    }
    return elementos;
}



size_t pos_arbitraria = 20;


bool avanzar_mostrando_hasta_contexto(void* elemento, void* contexto){

    char* e = elemento;
    char* c = contexto;
    if ((*c) > (*e))
    {
        printf("%d, ", *e);
        return true;
    }
        
    return false;
    
}


bool mostrar_elementos(void* elemento, void* contexto){

    

    char* e = elemento;
    printf("%d, ", *e);
    return true;
        
    return false;
    
}


void probar_lista(unsigned char* elementos){



    lista_t* lista;
    
    printf("Pruebas de creacion de la lista\n\n");

    verificar(((lista = lista_crear()) != NULL), "Creo una lista");
    verificar((lista_elementos(lista)  ==  0), "La lista se creo sin elementos");
    verificar((lista_ultimo(lista)  ==  NULL), "El primer elemento es nulo");
    verificar((lista_ultimo(lista)  ==  NULL), "El Ultimo elemento es nulo");
    verificar((lista_borrar(lista)  ==  ERROR), "Borrar da error porque no hay nada en la lista");
    verificar((lista_borrar_de_posicion(lista, pos_arbitraria)  ==  ERROR), "Borrar en posicion tambien da error");
    verificar((lista_elemento_en_posicion(lista, pos_arbitraria)  ==  NULL), "Elemento en posicion arbitraria devuelve NULL");



    printf("\n\nPruebas de operaciones basicas\n\n");

    printf("::___Con un solo elemento\n\n");

    verificar((lista_insertar(lista, &elementos[0]) == EXITO), "Incerto un elemento");
    verificar((&elementos[0] == lista_primero(lista)), "El primer elemento es correcto");
    verificar((&elementos[0] == lista_ultimo(lista)), "El ultimo elemento es correcto");
    verificar((lista_elementos(lista) == 1), "La cantidad de elementos es uno");
    verificar((lista_elemento_en_posicion(lista, pos_arbitraria)  ==  NULL), "Busco un elemento en una posicion arbitraria y devuelve Null");
    verificar((lista_borrar(lista) == EXITO), "Borro el elemento");
    verificar((lista_elementos(lista) == 0), "La cantidad de elementos es cero");
    verificar((lista_ultimo(lista)  ==  NULL), "El primer elemento es nulo");
    verificar((lista_ultimo(lista)  ==  NULL), "El ultimo elemento nulo");
    verificar((lista_borrar(lista)  ==  ERROR), "Borrar devuelve error porque no hay nada en la lista");



    printf(":: Pruebas de incercion multiple___\n\n");

    size_t acciones = 0;
    bool seguimos = true;
    while ((acciones < pos_arbitraria) && (seguimos == true))
    {
        
        if(lista_insertar(lista, &elementos[acciones]) == EXITO){
        acciones++;
        }
        else{
            seguimos = false;
        }    
    }
    verificar((pos_arbitraria == acciones), "Realizo multiples incerciones exitosamente");
    verificar((pos_arbitraria == lista_elementos(lista)), "La lista tiene tantos elementos como incerciones realizadas");
    printf("Se incertaron %ld elementos\n\n", lista_elementos(lista));
    verificar((&elementos[0] == lista_primero(lista)), "El primer elemento es correcto");
    verificar((&elementos[pos_arbitraria - 1] == lista_ultimo(lista)), "El ultimo elemento es correcto");


    printf("\n\n:: Pruebas de iterador interno___\n\n");


    char contexto = 5;

    lista_t* lista_sin_nada = lista_crear();
    verificar((lista_con_cada_elemento(NULL, mostrar_elementos, &contexto) == 0),"El iterador interno recibe una lista nula y devuelve 0");
    verificar((lista_con_cada_elemento(lista, NULL, &contexto) == 0),"El iterador interno recibe una funcion nula y devuelve 0");
    verificar((lista_con_cada_elemento(lista_sin_nada, avanzar_mostrando_hasta_contexto, &contexto) == 0),"El iterador interno recibe una lista vacia y devuelve 0");
    lista_insertar(lista_sin_nada, &elementos[40]);
    printf("incerto un elemento en la lista vacia");
    verificar((lista_con_cada_elemento(lista_sin_nada, mostrar_elementos, NULL) == 1),"El iterador interno recorre la lista con un elemento y devuelve 1");
    lista_destruir(lista_sin_nada);

    verificar((lista_con_cada_elemento(lista, avanzar_mostrando_hasta_contexto, &contexto) == 5),"El iterador interno recorrio hasta 5 elementos de la lista larga mostrandolos");
    printf("\n");
    verificar((lista_con_cada_elemento(lista, mostrar_elementos, &contexto) == pos_arbitraria),"El iterador interno recorrio hasta el final de la lista larga mostrando sus elementos");
    


    printf(":: Pruebas de incercion especiales___\n\n");

    verificar((lista_insertar_en_posicion(lista, &elementos[pos_arbitraria + 1],  pos_arbitraria/2)  ==  EXITO), "Incerto un elemento en el medio de la lista");
    verificar((lista_insertar_en_posicion(lista, &elementos[pos_arbitraria + 2],  pos_arbitraria/2 + 1 )  == EXITO), "Incerto otro elemento en el medio de la lista");
    verificar((lista_insertar_en_posicion(lista, &elementos[pos_arbitraria + 3], pos_arbitraria*2 )  ==  EXITO), "Incerto un elemento en una posicion mayor al largo de la lista");
    verificar((lista_insertar_en_posicion(lista, &elementos[pos_arbitraria + 4], 0 )  ==  EXITO), "Incerto un elemento en la posicion 0");
    
    verificar((lista_elemento_en_posicion(lista, pos_arbitraria/2 + 1) == &elementos[pos_arbitraria + 1]), "El primer elemento incertado en el medio es correcto");
    verificar((lista_elemento_en_posicion(lista, pos_arbitraria/2 + 2) == &elementos[pos_arbitraria + 2]), "El segundo elemento incertado en el medio es correcto");
    verificar((lista_elemento_en_posicion(lista, pos_arbitraria + 3) == &elementos[pos_arbitraria + 3]), "El tercer elemento incertado fuera de rango esta al final de la lista");
    verificar((lista_elemento_en_posicion(lista, 0) == &elementos[pos_arbitraria + 4]), "El cuarto elemento incertado en la posicion 0 esta al principio de la lista");
    
    verificar((lista_elementos(lista) == pos_arbitraria + 4), "Cantidad de elementos es correcta");


    printf(":: Pruebas de borrar en posicion___\n\n");

    verificar((lista_borrar_de_posicion(lista, pos_arbitraria/2 + 1) == EXITO), "El primer elemento en posicion intermedia  borrado");
    verificar((lista_borrar_de_posicion(lista, pos_arbitraria/2 + 1) == EXITO), "El segundo elemento en posicion intermedia  borrado");
    verificar((lista_borrar_de_posicion(lista, pos_arbitraria + 200) == EXITO), "Borramos en posicion fuera de rango, eliminando el tercer elemento(al final)");
    verificar((lista_borrar_de_posicion(lista, 0) == EXITO), "El cuarto elemento (al principio) borrado");
    verificar((lista_elementos(lista) == pos_arbitraria), "la Cantidad de elementos es correcta");
    
    unsigned int coinciden = 0;
    while (lista_elemento_en_posicion(lista, coinciden) == &elementos[coinciden])
    {
        coinciden++;
    }
    verificar((coinciden == lista_elementos(lista)), "Todos los elementos en la lista son correctos");
    printf("Son correctos %d\n\n", coinciden);
     
    


    printf(":: Pruebas con el iterador externo\n\n");

    lista_iterador_t* iter;
    verificar(((iter = lista_iterador_crear(lista)) != NULL), "Iterador creado con lista no vacia");
    acciones = 0;
    verificar((lista_iterador_elemento_actual(iter) == &elementos[0]), "El elemento actual es el primero de la lista");
    verificar((lista_iterador_tiene_siguiente(iter) == true), "El iterador tiene siguiente");
    coinciden = 1;
    while (lista_iterador_avanzar(iter))
    {
        acciones++;
        if (lista_iterador_elemento_actual(iter) == &elementos[acciones])
        {
            coinciden++;
        }
            
    }

    printf("\n");
    verificar((lista->cantidad  == acciones + 1), "Avanzo el iterador hasta que no se pueda mas (tantas veces como elementos en la lista)");
    verificar((lista->cantidad == coinciden), "Cada elemento actual en el iterador fue correcto");
    printf("Avance %ld veces. Coincidieron %d elementos\n\n", acciones, coinciden);
    verificar((lista_iterador_tiene_siguiente(iter) == false), "El iterador ya no tiene siguiente");
    verificar((lista_iterador_elemento_actual(iter) == NULL), "El elemento actual del iterador es NULL");
    verificar((lista_iterador_avanzar(iter) == false), "El iterador devuelve false si intento avanzar mas alla del final de la lista");      
    

    lista_iterador_t* iter_vacio;
    lista_t* lista_vacia;
    verificar(((iter_vacio = lista_iterador_crear(lista_vacia = lista_crear())) != NULL), "Puedo crear un iterador con una lista vacia");
    verificar((lista_iterador_elemento_actual(iter_vacio) == NULL), "El elemento actual del iterador devuelve Null");
    verificar((lista_iterador_tiene_siguiente(iter_vacio) == false), "Tiene siguiente devuelve falso");
    verificar((lista_iterador_avanzar(iter_vacio) == false), "Avanzar el iterador devuelve falso");
    verificar((lista_iterador_tiene_siguiente(iter_vacio) == false), "Tiene siguiente devuelve falso");
    verificar((lista_iterador_elemento_actual(iter_vacio)== NULL), "El elemento actual del iterador devuelve Null");
    lista_destruir(lista_vacia);
    lista_iterador_destruir(iter_vacio);
    verificar(((lista_iterador_crear(NULL)) == NULL), "No puedo crear un iterador con una lista nula");



    printf("\n\n:: Pruebas de borrar desde el final multiple___\n}\n");

    acciones = 0;
    seguimos = true;
    while (acciones < pos_arbitraria - 1 && seguimos == true){
        if(lista_borrar(lista) == EXITO){
        acciones++;
        }
        else{
            seguimos = false;
        }    
    }
    verificar(((pos_arbitraria - 1) == acciones), "Borre exitosamente todos los elementos menos uno");
    printf("Borre %ld elementos. Quedan %ld \n\n", acciones, lista_elementos(lista));
    verificar((&elementos[0] == lista_primero(lista)), "El primer elemento es correcto");
    verificar((&elementos[0] == lista_ultimo(lista)), "El ultimo elemento es correcto");
    verificar((lista_borrar(lista) == EXITO), "Borro el ultimo elemento");
    printf("La cantidad de elementos en la lista es %ld \n", lista_elementos(lista));
    verificar((lista_ultimo(lista)  ==  NULL), "El primer elemento es nulo");
    verificar((lista_ultimo(lista)  ==  NULL), "El ultimo elemento nulo");


    printf(":: Pruebas de Pila\n\n");

    acciones = 0;
    seguimos = true;
    while (acciones < pos_arbitraria && seguimos == true)
    {
        if(lista_apilar(lista, &elementos[acciones]) == EXITO){
        acciones++;
        }
        else{
            seguimos = false;
        }    
    }
    verificar((lista->cantidad == acciones), "Apile varias veces  ");
    printf("%ld\n\n", acciones);



    int desapiladas = 0;
    coinciden = 0;
    seguimos = true;
    while (desapiladas < pos_arbitraria  && seguimos == true)
    {
        if (lista_tope(lista) == &elementos[pos_arbitraria  - 1 - (size_t)(desapiladas)])
            {
                coinciden++;
            }
        if(lista_desapilar(lista) == EXITO){
            desapiladas++;
            
        }
        else{
            seguimos = false;
        }    
    }
    verificar((pos_arbitraria == desapiladas), "desapile todas");
    verificar((desapiladas == coinciden), "coinciden todos los topes");
    printf("Desapiladas: %d Coinciden: %d \n\n", desapiladas, coinciden);
    
    verificar((lista_desapilar(lista) == ERROR), "No se puede desapilar mas");
    verificar((lista_tope(lista) == NULL), "El tope es correcto");


    printf(":: Pruebas de Cola");
    
    acciones = 0;
    seguimos = true;
    while (acciones < pos_arbitraria && seguimos == true)
    {
        if(lista_encolar(lista, &elementos[acciones]) == EXITO){
        acciones++;
        }
        else{
            seguimos = false;
        }    
    }
    verificar((lista->cantidad == acciones), "Apile varias veces  ");
    printf("%ld\n\n", acciones);



    int desencoladas = 0;
    coinciden = 0;
    seguimos = true;
    while (desencoladas < pos_arbitraria  && seguimos == true)
    {
        if (lista_primero(lista) == &elementos[desencoladas])
            {
                coinciden++;
            }
        if(lista_desencolar(lista) == EXITO){
            desencoladas++;
            
        }
        else{
            seguimos = false;
        }    
    }
    verificar((pos_arbitraria == desencoladas), "desapile todas");
    verificar((desencoladas == coinciden), "coinciden todos los topes");
    printf("desencoladas: %d Coinciden: %d \n\n", desencoladas, coinciden);

    
    verificar((lista_desencolar(lista) == ERROR), "No se puede desencolar mas");
    verificar((lista_primero(lista) == NULL), "No hay mas elementos");


    lista_iterador_destruir(iter);
    lista_destruir(lista);
    lista_t* lista_nula = NULL;
    lista_iterador_t* iter_nulo = NULL;
    lista_destruir(lista_nula);
    lista_iterador_destruir(iter_nulo);



    printf("verificaciones realizadas %d / fallidas %d", verificaciones, fallidas);
}


int main(){
    unsigned char elementos[256]; 
    elementos_prueba(elementos);
    probar_lista(elementos);
    return 0;
}
