size_t _arbol_recorrido_inorden(nodo_abb_t* nodo, void** array, size_t* cargados,  size_t tamanio_array){
	if(!nodo || *cargados == tamanio_array) return *cargados;
	_arbol_recorrido_inorden(nodo->izquierda, array, cargados, tamanio_array);
	array[*cargados] = nodo->elemento;
	(*cargados)++;
	_arbol_recorrido_inorden(nodo->derecha, array, cargados, tamanio_array);
	return *cargados;
}


size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t* cargados = calloc(0, sizeof(size_t));
	size_t num = _arbol_recorrido_inorden(arbol->nodo_raiz, array, cargados, tamanio_array);
	return num;
}


size_t _arbol_recorrido_preorden(nodo_abb_t* nodo, void** array, size_t* cargados,  size_t tamanio_array){
	if(!nodo || *cargados == tamanio_array) return *cargados;
	array[*cargados] = nodo->elemento;
	(*cargados)++;
	_arbol_recorrido_preorden(nodo->izquierda, array, cargados, tamanio_array);
	_arbol_recorrido_preorden(nodo->derecha, array, cargados, tamanio_array);
	free(cargados);
	return *cargados;
}


size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t* cargados = calloc(0, sizeof(size_t));
	size_t num = _arbol_recorrido_preorden(arbol->nodo_raiz, array, cargados, tamanio_array);
	free(cargados);
	return num;
}

size_t _arbol_recorrido_postorden(nodo_abb_t* nodo, void** array, size_t* cargados,  size_t tamanio_array){
	if(!nodo || *cargados == tamanio_array) return *cargados;
	_arbol_recorrido_postorden(nodo->izquierda, array, cargados, tamanio_array);
	_arbol_recorrido_postorden(nodo->derecha, array, cargados, tamanio_array);
	array[*cargados] = nodo->elemento;
	(*cargados)++;
	return *cargados;
}


size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	size_t* cargados = calloc(0, sizeof(size_t));
	size_t num = _arbol_recorrido_postorden(arbol->nodo_raiz, array, cargados, tamanio_array);
	free(cargados);
	return num;
}