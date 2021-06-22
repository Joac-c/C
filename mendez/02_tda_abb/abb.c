
#include "abb.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define EXITO 0
#define ERROR -1	




nodo_abb_t* crear_nodo(void* elemento){
	nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
	nodo->elemento = elemento;
	nodo->derecha = NULL;
	nodo->izquierda = NULL;
	return nodo;

}

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if (comparador == NULL) return NULL;
    
    abb_t* arbol = malloc(sizeof(abb_t));
    arbol->comparador = comparador;
    arbol->destructor = destructor;
    arbol->nodo_raiz = NULL;
	return arbol;
}



void destruir_arboles_recursivo(abb_t* arbol, nodo_abb_t* nodo){
	if(arbol && nodo){
		destruir_arboles_recursivo(arbol, nodo->derecha);
		destruir_arboles_recursivo(arbol, nodo->izquierda);
		if(arbol->destructor) arbol->destructor(nodo->elemento);
		free(nodo);
	}
}


void arbol_destruir(abb_t* arbol){
	if(arbol){
		if(arbol->nodo_raiz){
		destruir_arboles_recursivo(arbol, arbol->nodo_raiz);
		}
		free(arbol);
	}
}

typedef struct ubicador
{
	abb_comparador* comparador;
	abb_liberar_elemento* destructor;
	nodo_abb_t** nodo;
	char hijos;
}ubicador_t;

ubicador_t* _buscar_nodo(void* buscado, ubicador_t* ubicador){
	/*Recibe un arbol, un nodo del mismo(usualmente la raiz) y el elemento que se busca. Devuelve la estructura ubicador_t
	que contiene  */
	if(!ubicador) return NULL;
	if(!(*ubicador->nodo)) return ubicador;
	if((*ubicador->comparador)(buscado, (*ubicador->nodo)->elemento) == 0){
		if((*ubicador->nodo)->derecha) ubicador->hijos++;
		if((*ubicador->nodo)->izquierda) ubicador->hijos++;
		return ubicador;
	}  
	else if((*ubicador->comparador)(buscado, (*ubicador->nodo)->elemento) > 0) ubicador->nodo = &(*ubicador->nodo)->derecha;
	else if(0 > (*ubicador->comparador)(buscado, (*ubicador->nodo)->elemento)) ubicador->nodo = &(*ubicador->nodo)-> izquierda;
	return _buscar_nodo(buscado, ubicador); 
}

ubicador_t* buscar_nodo(void* buscado, abb_t* arbol){
	ubicador_t* ubicador = calloc(1, sizeof(ubicador_t));
	ubicador->comparador = &arbol->comparador;
	ubicador->nodo = &arbol->nodo_raiz;
	if(arbol->destructor) ubicador->destructor = &arbol->destructor;
	ubicador->hijos = 0;
	return _buscar_nodo(buscado, ubicador);
}


int insertar_final(nodo_abb_t* nodo, void* elemento, abb_t* arbol){
	if(!nodo || !arbol) return ERROR;
	if(arbol->comparador(elemento, nodo->elemento) > 0){
		if(nodo->derecha == NULL) nodo->derecha = crear_nodo(elemento);
		else return insertar_final(nodo->derecha, elemento, arbol);
		return EXITO; 
	}
	else{
		if(nodo->izquierda == NULL) nodo->izquierda = crear_nodo(elemento);
		else return insertar_final(nodo->izquierda, elemento, arbol);
		return EXITO;
	}
	return ERROR;
	
}


int arbol_insertar(abb_t* arbol, void* elemento){
	if (!arbol) return ERROR;
	if (!(arbol->nodo_raiz)){
		arbol->nodo_raiz = crear_nodo(elemento);
		return EXITO;
	}
	return insertar_final(arbol->nodo_raiz, elemento, arbol);
}

int borrar_al_final(abb_t* arbol, ubicador_t* ubicador){
	if(!arbol) return ERROR;
	free(*ubicador->nodo);
	*ubicador->nodo = NULL;
	return EXITO;
	

}

int arbol_borrar_sin_hijos(ubicador_t* ubicador){
	if(ubicador->destructor) (*ubicador->destructor)((*ubicador->nodo)->elemento);
	free(*ubicador->nodo);
	*ubicador->nodo = NULL;
	
	if(!*ubicador->nodo) return EXITO;
	return ERROR;
}

int arbol_borrar_un_hijo(ubicador_t* ubicador){
	nodo_abb_t* aux = *ubicador->nodo;
	if((*ubicador->nodo)->izquierda) *ubicador->nodo = (*ubicador->nodo)->izquierda;
	else *ubicador->nodo = (*ubicador->nodo)->derecha;
	if(ubicador->destructor) (*ubicador->destructor)(aux->elemento);
	free(aux);
	return EXITO;
}




ubicador_t* ultimo_derecha(ubicador_t* ultimo){
	//Desciende por la derecha hasta encontrar el ultimo nodo
	if(!(*ultimo->nodo)->derecha){
		if((*ultimo->nodo)->izquierda) ultimo->hijos++;
		return ultimo;
	}
	ultimo->nodo = &(*ultimo->nodo)->derecha;
	return ultimo_derecha(ultimo);
}



int arbol_borrar_dos_hijos(ubicador_t* ubicador){
	if(!ubicador) return ERROR;
	//Ubicador contiene la direccion del nodo a borrar
	ubicador_t* ultimo = malloc(sizeof(ubicador_t));
	ultimo->hijos = 0;
	ultimo->nodo = &(*ubicador->nodo)->izquierda;


	//Ultimo entra con la direccion del nodo a la izquierda del que queremos borrar
	ultimo = ultimo_derecha(ultimo);

	//Ultimo sale con la direccion del nodo mas derecho de la rama izquierda del nodo a borrar
	if(ubicador->destructor) (*ubicador->destructor)((*ubicador->nodo)->elemento);
	(*ubicador->nodo)->elemento = (*ultimo->nodo)->elemento;
	nodo_abb_t* aux = NULL;
	if(ultimo->hijos == 1) aux = (*ultimo->nodo)->izquierda; 
	free((*ultimo->nodo));
	(*ultimo->nodo) = aux;
	//printf("verificacion rama %d\n", *(unsigned char*)((*ubicador->nodo)->izquierda->elemento));
	free(ultimo);
	
	return EXITO;
}


int arbol_borrar(abb_t* arbol, void* elemento){
	if (!arbol || !elemento) return ERROR;
	int resultado = ERROR;
	ubicador_t* ubicador = buscar_nodo(elemento, arbol);
	if(!ubicador || !*ubicador->nodo) return ERROR;
	if(ubicador->hijos == 0) resultado = arbol_borrar_sin_hijos(ubicador);// Simplemente libero el ubicador.nodo y le asigno NULL 
	if(ubicador->hijos == 1) resultado = arbol_borrar_un_hijo(ubicador);// creo un auxiliar que apunte al nodo a borrar, si existe nodo.derecha igualo ubicador.nodo a ese, sino al otro
	if(ubicador->hijos == 2) resultado = arbol_borrar_dos_hijos(ubicador);// 

	free(ubicador);
	return resultado;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	if (!arbol || !elemento) return NULL;

	ubicador_t* ubicador = buscar_nodo(elemento, arbol);
	if((*ubicador->nodo)){
	void* resultado = (*ubicador->nodo)->elemento;
	free(ubicador);
	return resultado;
	}
	free(ubicador);
	return NULL;
	
	
}

bool arbol_vacio(abb_t* arbol){
	if( !arbol || !arbol->nodo_raiz ) return true;
	return false;
}

void* arbol_raiz(abb_t* arbol){
	if(arbol_vacio(arbol)) return NULL;
	else return arbol->nodo_raiz->elemento;	
}


size_t _arbol_recorrido_inorden(nodo_abb_t* nodo, void** array, size_t cargados,  size_t tamanio_array){
	if(!nodo || cargados == tamanio_array) return cargados;
	cargados = _arbol_recorrido_inorden(nodo->izquierda, array, cargados, tamanio_array);
	array[cargados] = nodo->elemento;
	cargados++;
	cargados = _arbol_recorrido_inorden(nodo->derecha, array, cargados, tamanio_array);
	return cargados;
}


size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t cargados = 0;
	size_t num = _arbol_recorrido_inorden(arbol->nodo_raiz, array, cargados, tamanio_array);
	return num;
}


size_t _arbol_recorrido_preorden(nodo_abb_t* nodo, void** array, size_t cargados,  size_t tamanio_array){
	if(!nodo || cargados == tamanio_array) return cargados;
	array[cargados] = nodo->elemento;
	cargados++;
	cargados = _arbol_recorrido_preorden(nodo->izquierda, array, cargados, tamanio_array);
	cargados = _arbol_recorrido_preorden(nodo->derecha, array, cargados, tamanio_array);
	return cargados;
}


size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t cargados = 0;
	size_t num = _arbol_recorrido_preorden(arbol->nodo_raiz, array, cargados, tamanio_array);
	return num;
}


size_t _arbol_recorrido_postorden(nodo_abb_t* nodo, void** array, size_t cargados,  size_t tamanio_array, bool* corte){
	if(!nodo) return cargados;
	cargados = _arbol_recorrido_postorden(nodo->izquierda, array, cargados, tamanio_array, corte);
	cargados = _arbol_recorrido_postorden(nodo->derecha, array, cargados, tamanio_array, corte);
	if(*corte) return cargados;
	array[cargados] = nodo->elemento;
	cargados++;
	if(cargados == tamanio_array) *corte = true;
	return cargados;
}


size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t cargados = 0;
	bool* corte = calloc(1, sizeof(bool));
	size_t num = _arbol_recorrido_postorden(arbol->nodo_raiz, array, cargados, tamanio_array, corte);
	free(corte);
	return num;
}






size_t abb_con_cada_elemento_inorden(nodo_abb_t* nodo, size_t recorridos, bool (*funcion)(void*, void*), void* extra, bool* corte){
	if(!nodo) return recorridos;
	recorridos = abb_con_cada_elemento_inorden(nodo->izquierda, recorridos, funcion, extra, corte);
	if(*corte){
		return recorridos;
	}
	recorridos++;
	*corte = funcion(nodo->elemento, extra);
	recorridos = abb_con_cada_elemento_inorden(nodo->derecha, recorridos, funcion, extra, corte);
	return recorridos;
}

size_t abb_con_cada_elemento_preorden(nodo_abb_t* nodo, size_t recorridos, bool (*funcion)(void*, void*), void* extra, bool* corte){
	if(!nodo) return recorridos;
	if(*corte){
		return recorridos;
	}
	recorridos++;
	*corte = funcion(nodo->elemento, extra);
	recorridos = abb_con_cada_elemento_preorden(nodo->izquierda, recorridos, funcion, extra, corte);
	recorridos = abb_con_cada_elemento_preorden(nodo->derecha, recorridos, funcion, extra, corte);
	return recorridos;
}

size_t abb_con_cada_elemento_postorden(nodo_abb_t* nodo, size_t recorridos, bool (*funcion)(void*, void*), void* extra, bool* corte){
	if(!nodo) return recorridos;
	recorridos = abb_con_cada_elemento_postorden(nodo->izquierda, recorridos, funcion, extra, corte);
	recorridos = abb_con_cada_elemento_postorden(nodo->derecha, recorridos, funcion,  extra, corte);
	if(*corte){
		return recorridos;
	}
	recorridos++;
	*corte = funcion(nodo->elemento, extra);
	return recorridos;
	

	
}


size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){	
	size_t recorridos = 0;
	if(!arbol || !funcion) return 0;
	bool* corte = calloc(1, sizeof(bool));
	switch (recorrido)
	{
	case ABB_RECORRER_INORDEN:
			recorridos = abb_con_cada_elemento_inorden(arbol->nodo_raiz, recorridos, funcion, extra, corte);
		break;
	case ABB_RECORRER_PREORDEN:
			recorridos = abb_con_cada_elemento_preorden(arbol->nodo_raiz, recorridos, funcion, extra, corte);
		break;
	case ABB_RECORRER_POSTORDEN:
			recorridos = abb_con_cada_elemento_postorden(arbol->nodo_raiz, recorridos, funcion, extra, corte);
		break;	
	default:
		break;
	}
	free(corte);
	return recorridos;

}