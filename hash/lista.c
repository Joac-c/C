#include "lista.h"
#include "stdlib.h"

typedef struct nodo
{
    void* dato;
    struct nodo* prox;
}nodo_t;

typedef void (*lista_destruir_elemento)(void*);

typedef struct lista{
    nodo_t* prim;
    nodo_t* ult;
    size_t cant;
}lista_t;

typedef struct lista_iter{
    nodo_t* act;
    nodo_t* ant;
    lista_t* lista;
}lista_iter_t;



nodo_t* nodo_crear(void* elem){
    nodo_t* nodo = calloc(1, sizeof(nodo_t));
    if(!nodo) return NULL;
    nodo->dato = elem;
    return nodo;
}

lista_t *lista_crear(void){
    lista_t* lista = calloc(1, sizeof(lista_t));
    if(!lista) return NULL;
    return lista;
}



void destruir_nodo_recursivo(nodo_t* nodo, void (*destruir_dato)(void *)){
   
    if(!nodo) return;
    destruir_nodo_recursivo(nodo->prox, destruir_dato);
    if(destruir_dato) destruir_dato(nodo->dato);
    free(nodo);
    return;
} 

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    if(!lista) return;
    if(lista->prim) destruir_nodo_recursivo(lista->prim, destruir_dato);
    free(lista);



}

bool lista_esta_vacia(const lista_t *lista){
    if(!lista || !lista->prim || lista->cant == 0) return true;
    return false;
}


bool lista_insertar_primero(lista_t *lista, void *dato){
    if(!lista) return false;
    nodo_t* nodo = nodo_crear(dato);
    if(!nodo) return false;
    nodo->prox = lista->prim;
    if(lista->cant == 0) lista->ult = nodo;
    lista->prim = nodo;
    lista->cant++;
    return true;
}



bool lista_insertar_ultimo(lista_t *lista, void *dato){
    if(!lista) return false;
    nodo_t* nodo = nodo_crear(dato);
    if(!nodo) return false;
    if(!lista->prim) lista->prim = nodo;
    if(lista->ult) lista->ult->prox = nodo;
    lista->ult = nodo;
    lista->cant++;
    return true;
}



void *lista_borrar_primero(lista_t *lista){
    if(lista_esta_vacia(lista)) return NULL;
    void* elem = lista->prim->dato;
    nodo_t* nodo = lista->prim;
    lista->prim = nodo->prox;
    if(lista->ult == nodo) lista->ult = NULL;
    free(nodo);
    lista->cant--;
    return elem;
}




void *lista_ver_primero(const lista_t *lista){
    if(lista_esta_vacia(lista)) return NULL;
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
    if(lista_esta_vacia(lista)) return NULL;
    return lista->ult->dato;
}



size_t lista_largo(const lista_t *lista){
    if(!lista || !lista->prim || lista->cant == 0) return 0;
    return lista->cant;
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    if(lista_esta_vacia(lista)) return;
    bool seguir = true;
    nodo_t* nodo = lista->prim;
    while (seguir)
    {
        seguir = visitar(nodo->dato, extra);
        nodo = nodo->prox;
        if(!nodo) seguir = false;
    }
    
}


void _invertir(nodo_t* nodo, nodo_t* ant, lista_t* lista){
    if(!nodo) return;
    if(!nodo->prox) lista->prim = nodo;
    _invertir(nodo->prox, nodo, lista);
    nodo->prox = ant;
    return;


}

void invertir(lista_t* lista){
    if(lista_esta_vacia(lista)) return;
    nodo_t* nodo = lista->prim;
    nodo_t* ant = NULL;
    lista->ult = lista->prim;
    _invertir(nodo, ant, lista);

}

//Primitivas del iterador

lista_iter_t *lista_iter_crear(lista_t *lista){
    if(!lista) return NULL;
    lista_iter_t* iter = calloc(1, sizeof(lista_iter_t));
    if(!iter) return NULL; 
    iter->ant = NULL;
    iter->act = lista->prim;
    iter->lista = lista;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(!iter || !iter->act) return false;
    iter->ant = iter->act;
    iter->act = iter->ant->prox;    
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if(!iter || !iter->act) return NULL; 
    return iter->act->dato;
    
}

bool lista_iter_al_final(const lista_iter_t *iter){
    if(iter && !iter->act) return true;
    return false;
}

void lista_iter_destruir(lista_iter_t *iter){
    if(iter) free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    if(!iter) return false;
    //lista_insertar_primero(iter->lista, dato);
    nodo_t* nodo = nodo_crear(dato);
    if(!nodo) return false;
    if(!iter->ant) iter->lista->prim = nodo;
    else iter->ant->prox = nodo;
    if(lista_iter_al_final(iter)) iter->lista->ult = nodo;
    nodo->prox = iter->act;
    iter->act = nodo;
    iter->lista->cant++;
    return true;
}

/*
void* lista_iter_borrar_principio(lista_iter_t* iter){
    void* elem = iter->act->dato;
    nodo_t* nodo = iter->act;
    iter->act = nodo->prox;
    if(lista->ult == nodo) lista->ult = NULL;
    free(nodo);
    lista->cant--;
    return elem;
}
*/


void *lista_iter_borrar(lista_iter_t *iter){
    if(!iter || lista_iter_al_final(iter)) return NULL;
    if(!iter->ant) iter->lista->prim = iter->act->prox;
    if(!iter->act->prox) iter->lista->ult = iter->ant;
    void* elem = iter->act->dato;
    nodo_t* nodo = iter->act;
    iter->act = iter->act->prox;
    if(iter->ant)iter->ant->prox = iter->act;
    free(nodo);
    iter->lista->cant--;
    return elem;

    
}




