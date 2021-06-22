#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>




/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/


struct lista;
typedef struct lista lista_t;

struct nodo;
typedef struct nodo nodo_t;

struct lista_iter;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/
/*
    Crea una lista
    Pre: 
    Post: Devuelve una lista vacia
*/
lista_t *lista_crear(void);

/*
    Pre: Recibe una lista creada.
    Post: Devuelve True si la lista no tiene elementos incertados,
    devuelve false en caso contrario o si la lista es NULL.
*/
bool lista_esta_vacia(const lista_t *lista);

/*
    Inserta un nuevo elemento en la primera posicion de la lista 
    Pre: Recibe una lista creada y un puntero generico  
    Post: Devuelve true si el el elemento fue incertado con exito y false en caso contrario
*/
bool lista_insertar_primero(lista_t *lista, void *dato);

/*
    Inserta un nuevo elemento en la ultima posicion de la lista 
    Pre: Recibe una lista creada y un puntero generico  
    Post: Devuelve true si el el elemento fue incertado con exito y false en caso contrario
*/
bool lista_insertar_ultimo(lista_t *lista, void *dato);

/*
    // Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
    // primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
    // Pre: Recibe una lista creada y un puntero generico
    // Post: se devolvió el valor del primer elemento anterior, la lista
    // contiene un elemento menos, si la lista no estaba vacía.
*/
void *lista_borrar_primero(lista_t *lista);

/*
    Pre: La lista fue creada
    Post: Devuelve el valor del primer elemento y NULL si la lista se encuentra vacia
*/
void *lista_ver_primero(const lista_t *lista);

/*
    Pre: La lista fue creada
    Post: Devuelve el valor del ultimo elemento y NULL si la lista se encuentra vacia
*/
void *lista_ver_ultimo(const lista_t* lista);

/*
    Pre: La lista fue creada
    Post: Devuelve la cantidad de elementos en la lista
*/
size_t lista_largo(const lista_t *lista);

/*
    Libera la memoria de todos los elementos de la lista, y destruye 
    sus datos con una funcion ingresada por el usuario. Luego libera la memoria de la lista.
    Pre: La lista fue creada
    Post: 
*/
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/*
    Recorre los elementos de la lista aplicando cada vez una funcion boleana aportada por el usuario.
    En caso de que dicha funcion devuelva true, dejan de recorrese los elementos.
    Pre:
    Post:
*/
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);



/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

/*
    Pre: La lista fue creada y no esta vacia
    Post: Devuelve un iterador externo de la lista que apunta al primer elemento.
*/
lista_iter_t *lista_iter_crear(lista_t *lista);

/*
    El iterador apunta a la posicion siguiente del elemento actual en la lista.
    Pre: El iterador fue creado y la lista no fue modificada tras la creacion del mismo. 
    Ademas, el iterador no puede apuntar al final de la lista.
    Post: Devuelve True si se logra avanzar con exito. En caso contrario devuelve false. 
*/
bool lista_iter_avanzar(lista_iter_t *iter);

/*
    Pre: El iterador fue creado y la lista no fue modificada tras la creacion del mismo.
    Post: Devuelve el valor del elemento en la posicion a la que apunta el iterador, la actual.
    En caso de no haber elemento, devuelve NULL.
*/
void *lista_iter_ver_actual(const lista_iter_t *iter);

/*
    Pre: El iterador fue creado y la lista no fue modificada tras la creacion del mismo.
    Post: Devuelve true si el iterador apunta al final de la lista, esto es, luego
    del ultimo elemento insertado. En caso contrario devuelve false.
*/
bool lista_iter_al_final(const lista_iter_t *iter);

/*
    Libera la memoria donde se encuentra alojado el iterador.
    Pre: El iterador fue creado y la lista no fue modificada tras la creacion del mismo.
    Post:
*/
void lista_iter_destruir(lista_iter_t *iter);

/*
    Inserta un nuevo elemento en la posicion a la que apunta el iterador, la actual.
    Pre: El iterador fue creado y la lista no fue modificada tras la creacion del mismo.
    Post: Devuelve True si se logra insertar el elemento con exito. En caso contrario devuelve false.
*/
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

/*
    Borra el elemento en la posicion a la que apunta el iterador, la actual.
    Pre: El iterador fue creado y la lista no fue modificada tras la creacion del mismo.
    Ademas, el iterador no puede encontrarse al final de la lista.
    Post: Devuelve el valor del elemento borrado. En caso de no haber elemento o fallar, devuelve NULL;
*/
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_lista.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.

void pruebas_lista_estudiante(void);

#endif  // lISTA_H