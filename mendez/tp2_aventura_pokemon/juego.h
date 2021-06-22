#ifndef __JUEGO_H__
#define __JUEGO_H__
#define MAXIMO 100
#define ERROR -1
#define EXITO 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "herramientas/abb.h"
#include "herramientas/lista.h"
#include "herramientas/heap.h"

#define GIMNASIO 1
#define PERSONAJE 2
#define FORMATO_GIM "%99[^;];%99[^;];%i;%i\n"
#define FORMATO_ENTRENADOR "%99[^;];%99[^;]\n"
#define FORMATO_POKE "%99[^;];%99[^;];%i;%i%i;\n"
#define FORMATO_PJ "%99[^;];%99[^;]\n"
#define MENU_INICIO 0
#define MENU_GIMNASIOS 1
#define MENU_BATALLA 2  
#define MENU_VICTORIA 3        
#define MENU_DERROTA 4

typedef int (* funcion_batalla)(void*, void *);

typedef struct pokemon{
char nombre[MAXIMO];
int nivel;
int velocidad;
int defensa;
int ataque;
}pokemon_t;



typedef struct entrenador {
    int nivel;
    char nombre[MAXIMO];
    lista_t* luchadores;
}entrenador_t;



typedef struct gimnasio {
    char nombre[MAXIMO];
    int dificultad;
    int cantidad;
    int id;
    heap_t* entrenadores; //Aca usa el nivel para cargarlos 
}gimnasio_t;


typedef struct personaje{
    char nombre[MAXIMO];
    lista_t* luchadores; // Aca uso cantidad de la lista para dejar de cargar
    abb_t* pokemones; // Los pokemones van a 
}personaje_t;

typedef struct juego
{
    personaje_t personaje;
    heap_t* gimnasios;
    int menu;
    int paso;
}juego_t;


// Pre: Recibe la linea de texto con los datos del pokemon
// Post: Devuelve un puntero a un pokemon con todos los datos guardados
pokemon_t* crear_pokemon(char* datos, char tipo);

// Pre: Recibe la linea de texto con los datos del gimnasio
// Post: Devuelve un puntero a un gimnasio con todos los datos guardados
gimnasio_t* crear_gimnasio(char* linea, char tipo);

// Pre: Recibe la linea de texto con los datos del entrenador
// Post: Devuelve un puntero a un entrenador con todos los datos guardados
entrenador_t* crear_entrenador(char* linea, char tipo);


// Pre: Recibe la ruta del archivo con los gimnasios
// Post: Devuelve un heap con los gimnasios almacenados
heap_t* cargar_gimnasios(char* ruta);


// Pre: Recibe la ruta del archivo con el nombre y los pokemones iniciales del personaje
// Post: Devuelve un personaje con sus iniciales cargados
personaje_t* crear_personaje(char* ruta, char tipo);


// Pre: Recibe la ruta del archivo con los datos del personaje
// Post: Devuelve el personaje cargado
personaje_t cargar_personaje(char* ruta);


juego_t* crear_juego(char* gims, char*pj);

#endif /* __JUEGO_H__ */