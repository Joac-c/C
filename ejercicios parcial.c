///Ejercicios parcial de algoritmos

void liberar_elementos(){
}

#define letras = "abcde"

typedef struct triple{
    int* t[3];
}triple_t

int _crear_memorias(int contador, triple_t* direccion){
    contador++;
    if(contador != 5){
        direccion->t[2] = calloc(1, sizeof(triple_t));
        int cuenta  = crear_memorias(contador, direccion->t[2]) + 1;
        direccion->t[0] = &letra[cuenta];
        return cuenta;   
    }
    direccion->t[0] = malloc(sizeof(char)*5);
    direccion->[0][0] = letras[0];
    return 0;

}

void* _asignar_salteado(int contador, triple_t* direccion){
    contador++;
    if(contador == 5) return;
    *direccion->t[1] = *direccion->t[2]->t[2];
    _asignar_salteado(contador, direccion->t[2]);
    
}


void* crear_memorias(){
    triple_t* cosa = calloc(1, sizeof(triple_t));
    int contador = 0;
    _crear_memorias(contador, cosa);
    _asignar_salteado(contador, cosa);
}

void liberar_memorias(int contador, triple_t* cosa){
    contador++;
    if(contador == 5){
        free(cosa->t[0]);
        free(cosa)
        return;
    }
    else{
    liberar_memoria(contador, cosa);
    free(cosa);
    }
}


void* _crear(triple_t* cosa, int contador, triple_t* vector){
    if(contador = 5) return;
    cosa->t[2] = &vector[contador];
    vector[contador] = calloc(1, sizeof(triple_t));
    (*vector[contador]).t[0] = cosa;
    contador++

    _crear(vector[contador - 1], contador, vector))    
    cosa->t[1] = vector[contador]; 
}

void* crear(){
    triple_t* cosa = calloc(1, sizeof(triple_t));
    int contador = 0;
    cosa->t[2] = calloc(5, sizeof(triple_t*))
}



int _babilonico(int valor, int b){
    if((-0,0001 <= valor - b*b <= 0,0001) return b;
    _babilonico(valor, ((b + valor/b)/2);
}

int babilonico(int valor){
    int b = valor/2;
    _babilonico(valor, b);
}  





int* _buscar_posiciones (const char* arreglo, char cifra, int indice, int encontrados){
    if(arreglo[indice] == "\n"){
        int* indices = malloc(sizeof(int)* (encontrados + 1));
        indices[encontrados + 1] = -1;
        return indices;
    }
    if(arreglo[indice] == cifra){
        encontrados++;
        indices++;
        int* arreglo = _buscar_posiciones(arreglo, cifra, indices, encontrados);
        arreglo[encontrado] = indice;
        return arreglo;
    }
    else return _buscar_posiciones(arreglo, cifra, indices, encontrados)
    
}

int* buscar_posiciones(const char* arreglo, char cifra){
    
    int* lista = 
    int i = 0;
}




typedef struct ciudad{
    char nombre[MAX_NOMBRE];
    int habitantes;
    struct ciudad* proxima;
    struct ciudad* anterior
} ciudad_t;

typedef struct mapa{
    ciudad_t* origen;
    int cant_ciudades;
}mapa_t;



int agregar_ciudad(mapa_t* mapa, ciudad_t* ciudad_nueva, char ciudad_anterior[MAX_NOMBRE]){
    ciudad_t* puntero = mapa->origen;
    if(!mapa || !ciudad_nueva ) return -1;
    if(!mapa->origen){
        mapa->origen = ciudad_nueva;
        ciudad_nueva->anterior = NULL;
        ciudad_nueva->proxima = NULL
    }
    while(puntero && !strcmp(puntero->nombre, ciudad_anterior)){
        puntero = puntero->proxima;
    }
    if(!puntero) return -1;
    ciudad_nueva->anterior = puntero;
    ciudad_nueva->proxima = puntero->proxima;
    puntero->proxima = ciudad_nueva;
    if(ciudad_nueva->proxima) ciudad_nueva->proxima->anterior = ciudad_nueva;
}


mapa_t* crear_mapa(ciudad_t ciudades[MAX_CIUDADES]){
    mapa_t* mapa = calloc(1, sizeof(mapa_t));
    if(!mapa) return NULL;
    int cantidad = sizeof(ciudades)/sizeof(ciudad_t);
    mapa->origen = ciudades[0];
    mapa->origen->anterior = NULL;
    int i = 0;
    while(i != cantidad - 1){
        ciudades[i]->proximo = ciudades[i+1];
        ciudades[i+1]->anterior = ciudades[i]
    }
}

