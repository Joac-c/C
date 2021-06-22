#include "cola.h"

#include <stdlib.h>
#include <stdio.h>



typedef struct nodo
{
    void* dato;
    struct nodo* prox;
}nodo_t;

typedef struct cola{
    nodo_t* prim;
    nodo_t* ult;
} cola_t;


nodo_t* nodo_crear(void* elem){
    nodo_t* nodo = calloc(1, sizeof(nodo_t));
    if(!nodo) return NULL;
    nodo->dato = elem;
    return nodo;
}


// Crea una cola.
// Post: devuelve una nueva cola vacía.
cola_t *cola_crear(void){
    cola_t* cola = calloc(1, sizeof(cola_t));
    if(!cola) return NULL;
    return cola;
}


void destruir_nodo_recursivo(nodo_t* nodo, void (*destruir_dato)(void *)){
    if(!nodo) return;
    destruir_nodo_recursivo(nodo->prox, destruir_dato);
    if(destruir_dato) destruir_dato(nodo->dato);
    free(nodo);
    return;
} 


// Devuelve verdadero si la cola no tiene elementos encolados, false en caso contrario.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola){
    if(!cola->prim) return true;
    return false;
}

// Destruye la cola. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){
    if(!cola_esta_vacia(cola)) destruir_nodo_recursivo(cola->prim, destruir_dato);
    free(cola);

}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, void *valor){
    nodo_t* nodo = nodo_crear(valor);
    if(!nodo) return false;
    if(!cola->prim) cola->prim = nodo;
    if(cola->ult) cola->ult->prox = nodo;
    cola->ult = nodo;
    return true;
}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void *cola_ver_primero(const cola_t *cola){
    if(cola_esta_vacia(cola)) return NULL;
    return cola->prim->dato;
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void *cola_desencolar(cola_t *cola){
    if(cola_esta_vacia(cola)) return NULL;
    void* elem = cola->prim->dato;
    nodo_t* nodo = cola->prim;
    cola->prim = nodo->prox;
    if(cola->ult == nodo) cola->ult = NULL;
    free(nodo);
    return elem;

}


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_cola.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en cola.h
// (esto es, las pruebas no pueden acceder a los miembros del struct cola).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_cola_estudiante(void);