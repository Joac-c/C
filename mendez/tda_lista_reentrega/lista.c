#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1
#define EXITO 0

//static ???


lista_t* lista_crear (){
    lista_t* lista = malloc(sizeof(lista_t));
    if(lista){
    	lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
        lista->cantidad = 0;
    }
    return lista;    
}


nodo_t* crear_nodo(void* elemento){
    nodo_t* nuevo = malloc(sizeof(nodo_t));
    nuevo->elemento = elemento;
    nuevo->siguiente = NULL;
    return nuevo;
}



int insertar_entre_nodos(nodo_t* anterior, nodo_t* actual, void* elemento){
    //Introduce un nodo entre anterior y actual
    nodo_t* nuevo = crear_nodo(elemento);   
    if(!anterior || !nuevo){
        return ERROR;
    }
    nuevo->siguiente = actual;
    (*anterior).siguiente = nuevo;
    return EXITO;
}




int lista_insertar(lista_t* lista , void* elemento){
    if(!lista){
        return ERROR;
    }
    nodo_t* nuevo = crear_nodo(elemento);
    if(!nuevo){
        return ERROR;
    }
    lista->cantidad ++;
    if(!lista->nodo_inicio){
        lista->nodo_fin = nuevo;
        lista->nodo_inicio = nuevo;
        return EXITO;      
    }
    
    (*lista->nodo_fin).siguiente = nuevo;
    lista->nodo_fin = nuevo;
    return EXITO;

}

int lista_insertar_en_posicion (lista_t* lista , void* elemento , size_t posicion){
	if(!lista){
        return ERROR;
    }
    if(lista->cantidad == 0 || lista->cantidad <= posicion){
        return lista_insertar(lista, elemento);
    }
    else if(posicion == 0){
        nodo_t* nuevo = crear_nodo(elemento);
        nuevo->siguiente = lista->nodo_inicio;
        lista->nodo_inicio = nuevo;
        lista->cantidad++;
        return EXITO;
    }
    else{
        nodo_t* actual = lista->nodo_inicio;
        for(int i = 0; i != posicion - 1; i++){ 
            actual = actual->siguiente;           
        }
        if((insertar_entre_nodos(actual, (*actual).siguiente, elemento) == EXITO)){
            lista->cantidad++;
            return EXITO;
        }
    }
    return ERROR;
}



int lista_borrar_unico(lista_t* lista){
    //Elimina el unico nodo de la lista y la deja vacia
    if(lista){
        free(lista->nodo_inicio);
        lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		lista->cantidad--;
		return EXITO;
    }
    return ERROR;
}

int lista_borrar_ultimo(lista_t* lista){
    //Borra el ultimo nodo de la lista dejando el resto
    if (lista)
    {
        nodo_t* actual = lista->nodo_inicio;
        while (actual->siguiente != lista->nodo_fin)
        {
            actual = actual->siguiente;
        }
		free(actual->siguiente);
        actual->siguiente = NULL;           
		lista->nodo_fin = actual;
		lista->cantidad--;
		return EXITO;
    }
    return ERROR;
    
}


int lista_borrar(lista_t* lista){
	if(!lista || lista->cantidad == 0){
        return ERROR;
    }
	
	if(lista->cantidad == 1){
	    return lista_borrar_unico(lista);
	}
	else
	{
		return lista_borrar_ultimo(lista);
	}
		
	

}



int lista_borrar_de_posicion (lista_t* lista , size_t posicion){

	if(!lista || lista->cantidad == 0){
        return ERROR;
    }
	if((posicion >= lista->cantidad - 1)){
		return lista_borrar(lista);
	}
	else if(posicion == 0){
        nodo_t* borrable = lista->nodo_inicio;
        lista->nodo_inicio = borrable->siguiente;
		free(borrable);
		lista->cantidad--;
		return EXITO;
    }
	{
		nodo_t* actual = lista->nodo_inicio;
    	for(int i = 0; i != posicion - 1; i++){ 
            actual = actual->siguiente;				
		}
        nodo_t* borrable = actual->siguiente;
		actual->siguiente = actual->siguiente->siguiente;
        free(borrable);
        lista->cantidad--;
		return EXITO;
	}
}



void* lista_elemento_en_posicion (lista_t* lista , size_t posicion){
    if (!lista)
    {
        return NULL;
    }

	if(posicion < lista->cantidad){
		nodo_t* actual = lista->nodo_inicio;
        for(int i = 0; i != posicion; i++){ 
            actual = actual->siguiente;				
		}
		return actual->elemento;
	}
	return NULL;

}



void* lista_ultimo(lista_t* lista){
    if(!lista || lista->cantidad == 0){
        return NULL;
    }
	return lista->nodo_fin->elemento;
}



bool lista_vacia(lista_t* lista){
	if(lista == NULL || ((lista->cantidad == 0) && (lista->nodo_inicio == NULL) && (lista->nodo_fin == NULL)))
    {
		return true;
	}
	return false;
}


size_t lista_elementos(lista_t* lista){
    if (!lista)
    {
        return 0;
    }
	return lista->cantidad;
}


int lista_apilar(lista_t* lista , void* elemento){
    if (!lista)
    {
        return ERROR;
    }
	lista_insertar(lista, elemento);
	return EXITO;
}

int lista_desapilar(lista_t* lista){
    if (!lista)
    {
        return ERROR;
    }
	return lista_borrar(lista); 
}

void* lista_tope(lista_t* lista){
    if (!lista){
        return NULL;
    }
    
	return lista_ultimo(lista);
}

int lista_encolar(lista_t* lista , void* elemento){
    if (!lista)
    {
        return ERROR;
    }
    lista_insertar(lista, elemento);
	return EXITO;
}

int lista_desencolar(lista_t* lista){
    if (!lista)
    {
        return ERROR;
    }
    if(lista->cantidad == 0){
        return ERROR;
    }
    lista_borrar_de_posicion(lista, 0);
	return EXITO;
}


void* lista_primero(lista_t* lista){
    if (!lista)
    {
        return NULL;
    }
    if(lista->nodo_inicio == NULL){
        return NULL;
    }   
	return lista->nodo_inicio->elemento;
}




size_t lista_con_cada_elemento(lista_t* lista , bool (* funcion)(void*, void *), void *contexto){
    if (!lista || !funcion)
    {
        return 0;
    }
    
	nodo_t* actual = lista->nodo_inicio;
    if (!actual){
        return 0;
    }

    size_t cumplen = 0;
    while (actual && funcion(actual->elemento, contexto))
    {
        cumplen ++;
        actual = actual->siguiente;
        
    }
    return cumplen;
    
}




void eliminar_nodos_recursivos(nodo_t* nodo){
    //Recibe un puntero a nodo y elimina recursivamente los que le siguen hasta llegar a un puntero NULL
    if(nodo){
        eliminar_nodos_recursivos(nodo->siguiente);
        free(nodo);
    }
}

void lista_destruir(lista_t* lista){
    if(lista){
        nodo_t* nodo = lista->nodo_inicio;
        eliminar_nodos_recursivos(nodo);
        free(lista);
    }

}



//Funciones de iterador

lista_iterador_t* lista_iterador_crear (lista_t* lista){

    lista_iterador_t* iter = malloc(sizeof(lista_iterador_t));
    if(!iter || !lista){
        free(iter);
        return NULL;
    }
    iter->lista = lista;
    iter->corriente = lista->nodo_inicio;
    return iter;
}

bool lista_iterador_tiene_siguiente ( lista_iterador_t* iterador){
    if(!iterador->corriente || !iterador){
        return false;
    }
	if(iterador->corriente != NULL){
        return true;

	}
    return false;

}

bool lista_iterador_avanzar (lista_iterador_t* iterador){
    if(!iterador->corriente ||!iterador){
        return false;
    }
    iterador->corriente = iterador->corriente->siguiente;

    if(!iterador->corriente){
        return false;
    }
    return true;
}


void* lista_iterador_elemento_actual (lista_iterador_t* iterador){
    if(iterador){
        if(!iterador->corriente){
            return NULL;
        }
        return iterador->corriente->elemento;
	}
	return NULL;
}


void lista_iterador_destruir (lista_iterador_t* iterador){
    free(iterador);
}


