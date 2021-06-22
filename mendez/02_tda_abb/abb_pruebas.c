#include "abb.h"
#include <stdio.h>
#include <stdbool.h>

#define TILDE "✓"
#define CRUZ "✗"
#define AMARILLO "\e[33m"
#define NORMAL "\e[0m"
#define ROJO "\e[31m"
#define AZUL "\e[34m"
#define ERROR -1
#define EXITO 0
#define TOPE 17

int exitosas = 0;
int fallidas = 0;
int verificaciones = 0;


void verificar(bool afirmacion, const char* texto){
    if(afirmacion){
        printf(AZUL "\n" TILDE);
        exitosas++;
    }
    else{
        fallidas++;
        printf(ROJO "\n" CRUZ);
    }
    printf(NORMAL "%d -%s \n",verificaciones, texto);
    verificaciones++;
    fflush(stdout);

}

void subindice(){
    printf(":\n:");
}

int comparador(void* elemento1, void* elemento2){
    if(elemento1 == NULL) return -1;
    if(elemento2 == NULL) return 1;
    int primero = *(unsigned char*)elemento1;
    int segundo = *(unsigned char*)elemento2;
    if(primero > segundo){
        return 1;
    }
    if(segundo > primero){
        return -1;
    }   
    return 0;
    
}

void destructor(void* elemento){
    free(elemento);
}

unsigned char** elementos_prueba(unsigned char** elementos){
    unsigned char indices[] = {8, 4, 12, 2, 6, 10, 14, 15, 1, 13, 9, 3, 11, 5, 7, 8, 6};
    for(int i = 0; i != TOPE; i++){
        elementos[i] = calloc(1, sizeof(unsigned char));
        *(elementos[i]) = indices[i];
    }
    return elementos;
}
void acciones_basicas(){
    unsigned char* elemento = calloc(1, sizeof(unsigned char));
    *elemento = 8;
    printf(AMARILLO "\n\n\n/////// Acciones basicas del arbol ///////\n\n");

    abb_t* arbol = arbol_crear(comparador, destructor);
    verificar(arbol, "Un arbol fue creado con exito");
    verificar(arbol_vacio(arbol), "El arbol se crea vacio");
    verificar(arbol_borrar(arbol, NULL), "No se puede borrar NULL");
    verificar(arbol_insertar(arbol, NULL) == EXITO, "Se puede insertar NULL");
    verificar(arbol_insertar(arbol, &elemento[0]) == EXITO, "Inserto un elemento con exito");
    verificar(arbol_borrar(arbol, &elemento[0]) == EXITO, "Borro un elemento con exito");
    arbol_destruir(arbol);
    arbol = arbol_crear(comparador, NULL);
    verificar(arbol, "Un arbol sin destructor fue creado con exito");
    arbol_destruir(arbol);

}
int potencia(int valor, int exponente){
    int resultado = valor;
    for(int i = 1; i <= exponente; i++) resultado*=valor;
    return resultado;
}

void inserciones_y_busquedas(){
    printf(AMARILLO  NORMAL"\n\n\n/////// Pruebas de insercion y busqueda multiple ///////\n\n");
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = arbol_crear(comparador, destructor);
    elementos = elementos_prueba(elementos);
    size_t acciones = 0;
    bool seguimos = true;
    printf(NORMAL "//= insertamos varios elementos: ");
    while ((acciones < TOPE) && (seguimos == true))
    {
        if(arbol_insertar(arbol, elementos[acciones]) == EXITO){
            printf("%d, ", *elementos[acciones]);
            acciones++;
        }
        else seguimos = false;
    
    }
    printf("\n");
    verificar((TOPE == acciones), "Realizo multiples inserciones exitosamente incluyendo repetidos");
    printf("Se insertaron %ld elementos\n", acciones);
    printf("la raiz es %d\n", *(unsigned char*)arbol_raiz(arbol));
    verificar((8 == *(unsigned char*)arbol_raiz(arbol)), "La raiz es correcta");
    
    acciones = 0;
    while ((acciones < TOPE) && (seguimos == true))
    {
        if(*(unsigned char*)arbol_buscar(arbol, elementos[acciones]) == *(unsigned char*)elementos[acciones]) acciones++;
        else seguimos = false;
    
    }
    verificar((TOPE  == acciones), "Se encotraron todos los elementos");
    printf("Fueron encontrados %ld elementos\n\n", acciones);
    char* non = malloc(sizeof(unsigned char));
    *non = 42;
    verificar((arbol_buscar(arbol, non) == NULL), "Buscar un elemento no insertado devuelve NULL");
    free(non);
    arbol_destruir(arbol);
    free(elementos);
    
}
abb_t* cargar_arbol(unsigned char** elementos){
    abb_t* arbol = arbol_crear(comparador, destructor);
    size_t tope = TOPE;
    size_t acciones = 0;
    printf("//= insertamos varios elementos: ");
    elementos_prueba(elementos);
    while ((acciones < tope))
    {
        arbol_insertar(arbol, elementos[acciones]);
        printf("%d, ", *(unsigned char*)elementos[acciones]);
        acciones++;

    }

    return arbol;
}
void prueba_inorden(){
    printf(AMARILLO "\n\n\n///////  Prueba inorden /////// \n\n"NORMAL);
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = cargar_arbol(elementos);
    printf("\n\n/// Pruebas con un arreglo mas grande que el arbol ///");
    void** arreglo = malloc(sizeof(void*)*20);
    size_t recorridos = arbol_recorrido_inorden(arbol, arreglo, 20);
    printf("\n Recorrido inorden: ");
    int i = 0;
    while(i != recorridos){
        printf("%d, ", *(char*)arreglo[i]);
        i++;
    }
    free(arreglo);

    printf("\n\n/// Pruebas con un arreglo mas chico que el arbol ///");
    arreglo = malloc(sizeof(void*)*10);
    recorridos = arbol_recorrido_inorden(arbol, arreglo, 10);
    printf("\n Recorrido inorden: ");
    i = 0;
    while(i != recorridos){
        printf("%d, ", *(char*)arreglo[i]);
        i++;
    }
    free(arreglo);


    arbol_destruir(arbol);
    free(elementos);


}
void prueba_preorden(){
    printf(AMARILLO "\n\n\n/////// Pruebas preorden ///////\n\n"NORMAL);
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = cargar_arbol(elementos);
    printf("\n\n/// Pruebas con un arreglo mas grande que el arbol ///");
    void** arreglo = malloc(sizeof(void*)*20);
    size_t recorridos = arbol_recorrido_preorden(arbol, arreglo, 20);
     printf("\n Recorrido preorden: ");
    int i = 0;
    while(i != recorridos){
        printf("%d, ", *(char*)arreglo[i]);
        i++;
    }
    free(arreglo);

    printf("\n\n/// Pruebas con un arreglo mas chico que el arbol ///");
    arreglo = malloc(sizeof(void*)*10);
    recorridos = arbol_recorrido_preorden(arbol, arreglo, 10);
     printf("\n Recorrido preorden: ");
    i = 0;
    while(i != recorridos){
        printf("%d, ", *(char*)arreglo[i]);
        i++;
    }
    free(arreglo);


    arbol_destruir(arbol);
    free(elementos);


}

void prueba_postorden(){
    printf(AMARILLO "\n\n\n/////// Pruebas postorden ///////\n\n"NORMAL);
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = cargar_arbol(elementos);
    printf("\n\n/// Pruebas con un arreglo mas chico que el arbol ///");
    void** arreglo = malloc(sizeof(void*)*10);
    size_t recorridos = arbol_recorrido_postorden(arbol, arreglo, 10);
    printf("\n Recorrido postorden: ");
    int i = 0;
    while(i != recorridos){
        printf("%d, ", *(char*)arreglo[i]);
        i++;
    }
    free(arreglo);
    printf("\n/// Pruebas con un arreglo mas grande que el arbol ///");
    arreglo = malloc(sizeof(void*)*20);
    recorridos = arbol_recorrido_postorden(arbol, arreglo, 20);
     printf("\n Recorrido postorden: ");
    i = 0;
    while(i != recorridos){
        printf("%d, ", *(char*)arreglo[i]);
        i++;
    }
    free(arreglo);
    arbol_destruir(arbol);
    free(elementos);


}

void pruebas_de_borrado(){
    printf(AMARILLO "\n\n\n/////// Pruebas de borrado ///////\n\n"NORMAL);
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = cargar_arbol(elementos);
    unsigned char valores[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; 
    verificar((arbol_borrar(arbol, &valores[1]) == EXITO), "Borramos con exito el elemento mas bajo (hoja)");
    verificar((arbol_borrar(arbol, &valores[2]) == EXITO), "Borramos con exito el segundo elemento mas bajo (con una hoja derecha)");
    verificar((arbol_borrar(arbol, &valores[15]) == EXITO), "Borramos con exito el elemento mas alto (hoja)");
    verificar((arbol_borrar(arbol, &valores[14]) == EXITO), "Borramos con exito el segundo elemento mas alto (con una hoja izquierda)");
    verificar((arbol_borrar(arbol, &valores[10]) == EXITO), "Borramos con exito un elemento con dos hojas");
    verificar((arbol_borrar(arbol, &valores[6]) == EXITO), "Borramos con exito un elemento repetido");
    verificar((*(unsigned char*)arbol_buscar(arbol, &valores[6]) == valores[6]), "Encontramos el elemento repetido ");
    verificar((arbol_borrar(arbol, &valores[6]) == EXITO), "Borramos con exito ese elemento");
    verificar((arbol_buscar(arbol, &valores[6]) == NULL), " No encontramos el elemento repetido ");
    verificar((*(unsigned char*)arbol_raiz(arbol) == valores[8]), "La raiz es correcta ");
    verificar((arbol_borrar(arbol, &valores[8]) == EXITO), "Borramos con exito la raiz");
    verificar((*(unsigned char*)arbol_raiz(arbol) == valores[8]), "La raiz es correcta ");
    verificar((*(unsigned char*)arbol_buscar(arbol, &valores[8]) == valores[8]), "Encontramos el elemento repetido ");
    verificar((arbol_borrar(arbol, &valores[8]) == EXITO), "Como estaba repetida volvemos a borrarla");
    verificar((arbol_raiz(arbol) != &valores[8]), "La raiz cambio");
    printf("La raiz actual es %d \n", *(unsigned char*)arbol_raiz(arbol));
    for(int i = 0; i != 8; i++){
        printf("La raiz es %d\n", *(unsigned char*)(arbol_raiz(arbol)));
        verificar((arbol_borrar(arbol, &valores[*(unsigned char*)arbol_raiz(arbol)]) == EXITO), "borro la raiz con exito");
    }
    
    verificar((arbol_buscar(arbol, &valores[8]) == NULL), "La raiz original ya no se encuentra en el arbol");
    arbol_destruir(arbol);
    free(elementos);
}

void pruebas_de_borrado_sin_destructor(){
    printf(AMARILLO "\n\n\n/////// Pruebas de borrado ///////\n\n"NORMAL);
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = cargar_arbol(elementos);
    arbol->destructor = NULL;
    unsigned char valores[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; 
    verificar((arbol_borrar(arbol, &valores[1]) == EXITO), "Borramos con exito el elemento mas bajo (hoja)");
    verificar((arbol_borrar(arbol, &valores[2]) == EXITO), "Borramos con exito el segundo elemento mas bajo (con una hoja derecha)");
    verificar((arbol_borrar(arbol, &valores[15]) == EXITO), "Borramos con exito el elemento mas alto (hoja)");
    verificar((arbol_borrar(arbol, &valores[14]) == EXITO), "Borramos con exito el segundo elemento mas alto (con una hoja izquierda)");
    verificar((arbol_borrar(arbol, &valores[10]) == EXITO), "Borramos con exito un elemento con dos hojas");
    verificar((arbol_borrar(arbol, &valores[6]) == EXITO), "Borramos con exito un elemento repetido");
    verificar((*(unsigned char*)arbol_buscar(arbol, &valores[6]) == valores[6]), "Encontramos el elemento repetido ");
    verificar((arbol_borrar(arbol, &valores[6]) == EXITO), "Borramos con exito ese elemento");
    verificar((arbol_buscar(arbol, &valores[6]) == NULL), " No encontramos el elemento repetido ");
    verificar((*(unsigned char*)arbol_raiz(arbol) == valores[8]), "La raiz es correcta ");
    verificar((arbol_borrar(arbol, &valores[8]) == EXITO), "Borramos con exito la raiz");
    verificar((*(unsigned char*)arbol_raiz(arbol) == valores[8]), "La raiz es correcta ");
    verificar((*(unsigned char*)arbol_buscar(arbol, &valores[8]) == valores[8]), "Encontramos el elemento repetido ");
    verificar((arbol_borrar(arbol, &valores[8]) == EXITO), "Como estaba repetida volvemos a borrarla");
    verificar((arbol_raiz(arbol) != &valores[8]), "La raiz cambio");
    printf("La raiz actual es %d \n", *(unsigned char*)arbol_raiz(arbol));
    for(int i = 0; i != 8; i++){
        printf("La raiz es %d\n", *(unsigned char*)(arbol_raiz(arbol)));
        verificar((arbol_borrar(arbol, &valores[*(unsigned char*)arbol_raiz(arbol)]) == EXITO), "borro la raiz con exito");
    }
    
    verificar((arbol_buscar(arbol, &valores[8]) == NULL), "La raiz original ya no se encuentra en el arbol");
    arbol_destruir(arbol);
    for(int i = 0; i != TOPE; i++){
        free(elementos[i]);
    }
    free(elementos);
}

bool mostrar_hasta(void* elemento, void* extra){
    if(elemento) printf("\nElemento: %d", *(unsigned char*)elemento);
    if(*(unsigned char*)elemento == *(unsigned char*)extra) return true;
    return false;
}

void prueba_cada_elemento_inorden(){
    printf(AMARILLO "\n\n\n/////// Prueba del iterador interno inorden///////\n\n"NORMAL);
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = cargar_arbol(elementos);
    char* cincuenta = malloc(sizeof(char));
    char* nueve = malloc(sizeof(char));
    *cincuenta = 50; 
    *nueve = 9;
    verificar((abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta, cincuenta) == TOPE), "El iterador interno recorre todos los elementos del arbol");
    verificar((abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta, nueve) == 11), "El iterador interno recorre todos los elementos hasta el 9");
    arbol_destruir(arbol);
    free(elementos);
    free(cincuenta);
    free(nueve);
}

void prueba_cada_elemento_preorden(){
    printf(AMARILLO "\n\n\n/////// Prueba del iterador interno preorden///////\n\n"NORMAL);
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = cargar_arbol(elementos);
    char* cincuenta = malloc(sizeof(char));
    char* nueve = malloc(sizeof(char));
    *cincuenta = 50; 
    *nueve = 9;
    verificar((abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta, cincuenta) == TOPE), "El iterador interno recorre todos los elementos del arbol");
    verificar((abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta, nueve) == 13), "El iterador interno recorre todos los elementos hasta el 9");
    arbol_destruir(arbol);
    free(elementos);
    free(cincuenta);
    free(nueve);
}

void prueba_cada_elemento_postorden(){
    printf(AMARILLO "\n\n\n/////// Prueba del iterador interno postorden///////\n\n"NORMAL);
    unsigned char** elementos = calloc(TOPE, sizeof(int*));
    abb_t* arbol = cargar_arbol(elementos);
    char* cincuenta = malloc(sizeof(char));
    char* nueve = malloc(sizeof(char));
    *cincuenta = 50; 
    *nueve = 9;
    verificar((abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta, cincuenta) == TOPE), "El iterador interno recorre todos los elementos del arbol");
    verificar((abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta, nueve) == 10), "El iterador interno recorre todos los elementos hasta el 9");
    arbol_destruir(arbol);
    verificar((abb_con_cada_elemento(NULL, ABB_RECORRER_POSTORDEN, mostrar_hasta, cincuenta) == 0), "No puedo iterar con un arbol nulo");
    free(elementos);
    free(cincuenta);
    free(nueve);
}

int main (int argc, char* argv[]) {
    
    
    acciones_basicas();
    inserciones_y_busquedas();
    prueba_inorden();
    prueba_preorden();
    prueba_postorden();
    pruebas_de_borrado();
    prueba_cada_elemento_inorden();
    prueba_cada_elemento_preorden();
    prueba_cada_elemento_postorden();
    pruebas_de_borrado_sin_destructor();
    printf("\nEjecutaste las pruebas. Exitosas: %d  Fallidas: %d\n\n", exitosas, fallidas);
    return 0;
}