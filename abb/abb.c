
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

abb_t* arbol_crear(abb_comparar_clave_t comparador, abb_destruir_dato_t destructor){
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
	abb_comparar_clave_t* comparador;
	abb_destruir_dato_t* destructor;
	nodo_abb_t** nodo;
	char hijos;
}ubicador_t;



int devolver_hijos(nodo_abb_t* nodo){
	int hijos = 0;
	if(nodo->derecha) hijos++;
	if(nodo->izquierda)hijos++;
	return hijos;
}

/*
ubicador_t* _buscar_nodo(const char clave, ubicador_t* ubicador){
	Recibe un arbol, un nodo del mismo(usualmente la raiz) y el elemento que se busca. Devuelve la estructura ubicador_t
	que contiene  
	if(!ubicador) return NULL;
	if(!(*ubicador->nodo)) return ubicador;
	if((*ubicador->comparador)(clave, (*ubicador->nodo)->clave) == 0){
		if((*ubicador->nodo)->derecha) ubicador->hijos++;
		if((*ubicador->nodo)->izquierda) ubicador->hijos++;
		return ubicador;
	}  
	else if((*ubicador->comparador)(clave, (*ubicador->nodo)->clave) > 0) ubicador->nodo = &(*ubicador->nodo)->derecha;
	else if(0 > (*ubicador->comparador)(clave, (*ubicador->nodo)->clave)) ubicador->nodo = &(*ubicador->nodo)-> izquierda;
	return _buscar_nodo(clave, ubicador); 
}



ubicador_t* buscar_nodo(const char* clave, abb_t* arbol){
	ubicador_t* ubicador = calloc(1, sizeof(ubicador_t));
	ubicador->comparador = &arbol->comparador;
	ubicador->nodo = &arbol->nodo_raiz;
	if(arbol->destructor) ubicador->destructor = &arbol->destructor;
	ubicador->hijos = 0;
	return _buscar_nodo(clave, ubicador);
}
*/

nodo_abb_t** _buscar_nodo(const char* clave, nodo_abb_t** nodo, abb_t* arbol){
	/*Recibe un arbol, un nodo del mismo(usualmente la raiz) y el elemento que se busca. Devuelve la estructura ubicador_t
	que contiene  */
	if(!(*nodo)) return nodo;
	if((arbol->comparador)(clave, (*nodo)->clave) == 0){
		return nodo;
	}  
	else if((arbol->comparador)(clave, (*nodo)->clave) > 0) nodo = &(*nodo)->derecha;
	else if(0 > (arbol->comparador)(clave, (*nodo)->clave)) nodo = &(*nodo)-> izquierda;
	return _buscar_nodo(clave, nodo, arbol); 
}


nodo_abb_t** buscar_nodo(const char* clave, abb_t* arbol){
	nodo_abb_t** buscado = calloc(1, sizeof(nodo_abb_t));
	return _buscar_nodo(clave, buscado, arbol);

}


int guardar_final(nodo_abb_t* nodo, const char* clave, void* elemento, abb_t* arbol){
	if(!nodo || !arbol) return ERROR;
	if(arbol->comparador(elemento, nodo->elemento) > 0){
		if(nodo->derecha == NULL) nodo->derecha = crear_nodo(elemento);
		else return guardar_final(nodo->derecha, clave, elemento, arbol);
		arbol->cantidad++;
		return EXITO; 
	}
	else{
		if(nodo->izquierda == NULL) nodo->izquierda = crear_nodo(elemento);
		else return guardar_final(nodo->izquierda, clave, elemento, arbol);
		arbol->cantidad++;
		return EXITO;
	}
	return ERROR;
	
}


int guardar(abb_t* arbol, const char* clave, void* elemento){
	if (!arbol) return ERROR;
	if (!(arbol->nodo_raiz)){
		arbol->nodo_raiz = crear_nodo(elemento);
		arbol->cantidad++;
		return EXITO;
	}
	return guardar_final(arbol->nodo_raiz, clave, elemento, arbol);
}

int borrar_al_final(abb_t* arbol, nodo_abb_t** nodo){
	if(!arbol) return ERROR;
	free(*nodo);
	*nodo = NULL;
	return EXITO;
	

}

int arbol_borrar_sin_hijos(nodo_abb_t** nodo, abb_t* arbol){
	if(arbol->destructor) (*arbol->destructor)((*nodo)->elemento);
	free(*nodo);
	*nodo = NULL;
	
	if(!*nodo) return EXITO;
	return ERROR;
}

int arbol_borrar_un_hijo(nodo_abb_t** nodo, abb_t* arbol){
	nodo_abb_t* aux = *nodo;
	if((*nodo)->izquierda) *nodo = (*nodo)->izquierda;
	else *nodo = (*nodo)->derecha;
	if(arbol->destructor) (*arbol->destructor)(aux->elemento);
	free(aux);
	return EXITO;
}




nodo_abb_t** ultimo_derecha(nodo_abb_t** ultimo){
	//Desciende por la derecha hasta encontrar el ultimo nodo
	if(!(*ultimo)->derecha){
		return ultimo;
	}
	ultimo = &(*ultimo)->derecha;
	return ultimo_derecha(ultimo);
}



int arbol_borrar_dos_hijos(nodo_abb_t** nodo, abb_t* arbol){
	if(!nodo) return ERROR;
	//Ubicador contiene la direccion del nodo a borrar
	nodo_abb_t** ultimo = malloc(sizeof(nodo_abb_t*));
	
	ultimo = &((*nodo)->izquierda);

	//Ultimo entra con la direccion del nodo a la izquierda del que queremos borrar
	ultimo = ultimo_derecha(ultimo);

	//Ultimo sale con la direccion del nodo mas derecho de la rama izquierda del nodo a borrar
	if(arbol->destructor) (arbol->destructor)((*nodo)->elemento);
	(*nodo)->elemento = (*ultimo)->elemento;
	nodo_abb_t* aux = NULL;
	if(devolver_hijos(*ultimo) == 1) aux = (*ultimo)->izquierda; 
	free((*ultimo));
	(*ultimo) = aux;
	//printf("verificacion rama %d\n", *(unsigned char*)((nodo)->izquierda->elemento));
	free(ultimo);
	
	return EXITO;
}

void* arbol_borrar(abb_t* arbol, const char* clave){
	if (!arbol) return NULL;
	int resultado = ERROR;
	nodo_abb_t** nodo = buscar_nodo(clave, arbol);
	
	if(!nodo) return NULL;
	void* elemento = (*nodo)->elemento;
	if(devolver_hijos(*nodo) == 0) resultado = arbol_borrar_sin_hijos(nodo, arbol);// Simplemente libero el nodo, arbol.nodo y le asigno NULL 
	if(devolver_hijos(*nodo) == 1) resultado = arbol_borrar_un_hijo(nodo, arbol);// creo un auxiliar que apunte al nodo a borrar, si existe nodo.derecha igualo nodo, arbol.nodo a ese, sino al otro
	if(devolver_hijos(*nodo) == 2) resultado = arbol_borrar_dos_hijos(nodo, arbol);// 

	if(resultado) arbol->cantidad--;
	if(resultado) return elemento;
	else return NULL;
}

void* arbol_obtener(abb_t* arbol, const char* clave){
	if (!arbol) return NULL;

	nodo_abb_t** nodo = buscar_nodo(clave, arbol);
	if((nodo)){
	void* resultado = (*nodo)->elemento;
	free(nodo);
	return resultado;
	}
	free(nodo);
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




typedef struct abb_iter abb_iter_t;

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
bool abb_iter_in_avanzar(abb_iter_t *iter);
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
bool abb_iter_in_al_final(const abb_iter_t *iter);
void abb_iter_in_destruir(abb_iter_t* iter);

int main(){
	return 0;
}