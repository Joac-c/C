#include "juego.h"

// -FUNCIONES DE CREACION

int heap_comparador_entrenadores(void* primero, void* segundo){
    if(!primero||!segundo) return -2;
    entrenador_t* primeroo = (entrenador_t*)primero;
    entrenador_t* segundoo = (entrenador_t*)segundo;
    if(!primeroo->nivel || !segundoo->nivel) return -2;
    if(primeroo->nivel > segundoo->nivel) return 1;
    if(primeroo->nivel < segundoo->nivel) return -1;
    if(primeroo->nivel == segundoo->nivel) return 0;
    return -2;
}

int heap_comparador_gimnasios(void* primero, void* segundo){
    if(!primero||!segundo) return -2;
    gimnasio_t* primeroo = (gimnasio_t*)primero;
    gimnasio_t* segundoo = (gimnasio_t*)segundo;
    if(primeroo->dificultad > segundoo->dificultad) return 1;
    if(primeroo->dificultad < segundoo->dificultad) return -1;
    if(primeroo->dificultad == segundoo->dificultad) return 0;
    return -2;
}


int abb_comparador_pokemones(void* primero, void* segundo){
    if(!primero || !segundo) return -2;
    char letra1 = ((pokemon_t*)primero)->nombre[0];
    char letra2 = ((pokemon_t*)segundo)->nombre[0];

    if(letra1 > letra2) return 1;
    if(letra1 < letra2) return -1;
    if(letra1 == letra2) return 0;
    return -2;
}


// Pre: Recibe la ruta del archivo con el nombre y los pokemones iniciales del personaje
// Post: Devuelve un personaje con sus iniciales cargados
personaje_t* crear_personaje(char* linea, char tipo){
    personaje_t* personaje = calloc(1, sizeof(personaje_t));
    int exitos = scanf(linea, FORMATO_PJ, tipo, personaje->nombre);
    if(tipo != linea[0]|| exitos != 2) return NULL;
    personaje->luchadores = lista_crear();
    personaje->pokemones = arbol_crear(abb_comparador_pokemones, NULL);
    return personaje;
}

// Pre: Recibe la linea de texto con los datos del pokemon
// Post: Devuelve un puntero a un pokemon con todos los datos guardados
pokemon_t* crear_pokemon(char* linea, char tipo){
    pokemon_t* poke = calloc(1, sizeof(pokemon_t));
    if(!poke) return NULL;
    int exitos = scanf(linea, FORMATO_POKE, tipo, poke->nombre, poke->velocidad, poke->ataque, poke->defensa);
    if(tipo != linea[0] || exitos != 2) return NULL;
    return poke;

}

// Pre: Recibe la linea de texto con los datos del entrenador
// Post: Devuelve un puntero a un entrenador con todos los datos guardados
entrenador_t* crear_entrenador(char* linea, char tipo){
        entrenador_t* e_actual = calloc(1, sizeof(entrenador_t));
        if(!e_actual) return NULL;
        int exitos = scanf(linea, FORMATO_ENTRENADOR, tipo, e_actual->nombre);
        if(tipo != linea[0] || exitos != 2) return NULL;
        e_actual->luchadores = lista_crear();
        return e_actual;
}

// Pre: Recibe la linea de texto con los datos del gimnasio
// Post: Devuelve un puntero a un gimnasio con todos los datos guardados
gimnasio_t* crear_gimnasio(char* linea, char tipo){

        gimnasio_t* g_actual = calloc(1, sizeof(gimnasio_t));
        if(!g_actual) return NULL;
        int exitos = scanf(linea, FORMATO_GIM, tipo, g_actual->dificultad, g_actual->id);
        if(tipo != linea[0] || exitos != 4) return NULL;
        g_actual->entrenadores = crear_heap(MAXIMO);
        return g_actual;
}


int subir_a_gimnasios(heap_t* gimnasios, char* linea, gimnasio_t* g_actual, entrenador_t* e_actual){
    if(!linea) return ERROR;
    char tipo = linea[0];
    if(tipo == 'G'){
        /*
        if(g_actual){
            
            if(heap_devolver_raiz(g_actual->entrenadores) == NULL){
                heap_borrar_raiz(gimnasios)
            }
            Esto era para borrar los gimnasios sin pokemones pero como estan en un heap no se pueden buscar
            hay que resolverlo en la ejecucion.  
            
        }
        */
        g_actual = crear_gimnasio(linea, tipo);
        if(!g_actual) return ERROR;
        heap_insertar(g_actual, gimnasios, heap_comparador_gimnasios);
        return EXITO;
    }
    else if(tipo == 'L' || tipo == 'E'){
        if(!g_actual) return ERROR;
        e_actual = crear_entrenador(linea, tipo);
        if(tipo == 'L') e_actual->nivel = 0;
        else{
            g_actual->cantidad++;
        }
        if(g_actual) return ERROR;
        heap_insertar(e_actual, g_actual->entrenadores, heap_comparador_entrenadores);
        return EXITO;
    }
    else if(tipo == 'P'){
        pokemon_t* poke;
        if((poke = crear_pokemon(linea, tipo))) lista_apilar(e_actual->luchadores, poke);
        else return ERROR;
        return EXITO;
    }
    else return ERROR;
}

int subir_a_personaje(personaje_t* personaje, char* linea){
    if(!linea) return ERROR;
    char tipo = linea[0];
    if(tipo == 'E'){
        if(personaje) return ERROR;
        personaje_t* personaje = crear_personaje(linea, tipo);
        if(personaje){

        } return EXITO;
    }
    else if(tipo == 'P'){
        pokemon_t* poke;
        if((poke = crear_pokemon(linea, tipo))) arbol_insertar(personaje->pokemones, poke);
        else return ERROR;
        if(lista_cantidad_elementos(personaje->luchadores) != 6) lista_insertar(personaje->luchadores, poke);
        return EXITO;
        
    }
    return ERROR;
}



int descargar_archivo(char* ruta, char accion, void* estructura){
    FILE* archivo = fopen(ruta, "r");
    if (!archivo)
    {
        return ERROR;
    }
    char buffer[MAXIMO];
    char* linea; 
    size_t tamano;
    gimnasio_t* g_actual = NULL;
    entrenador_t* e_actual = NULL;
    while ((linea = fgets(buffer, MAXIMO, archivo)) != NULL)
    {
        tamano = strlen(linea);
        if(linea[tamano - 1] == '\n'){
            switch (accion)
            {
            case PERSONAJE:
                return subir_a_personaje(estructura, linea);
                break;
            case GIMNASIO:
                return subir_a_gimnasios(estructura, linea, g_actual, e_actual);
                break;
            default:
                break;
            }
        }
    }
    
    return ERROR;
}





// Pre: Recibe la ruta del archivo con los gimnasios
// Post: Devuelve un heap con los gimnasios almacenados
heap_t* cargar_gimnasios(char* ruta){
    heap_t* gimnasio = crear_heap(MAXIMO);
    descargar_archivo(ruta, GIMNASIO, &gimnasio);
    return gimnasio;
}


// Pre: Recibe la ruta del archivo con los datos del personaje
// Post: Devuelve el personaje cargado
personaje_t cargar_personaje(char* ruta){
    personaje_t personaje;
    descargar_archivo(ruta, PERSONAJE, &personaje);
    return personaje;
}



//NOTA: Tengo que hacer una version dinamica del heap por las dudas de que haya muchos gimnasios



//prints de la interfas

// FUNCIONES DE ACCION


void bucle(juego_t* juego){
    if(!juego || !juego->gimnasios);
    switch (juego->menu)
    {
    case MENU_INICIO:
        /* code */
        break;
    case MENU_GIMNASIOS:
        /* code */
        break;
    case MENU_BATALLA:
        /* code */
        break;
    case MENU_VICTORIA:
        /* code */
        break;
    case MENU_DERROTA:
        /* code */
        break;
    
    default:
        break;
    }
}

juego_t* crear_juego(char* gims, char*pj){
    juego_t* juego = calloc(1, sizeof(juego_t));
    juego->gimnasios = cargar_gimnasios(gims);
    juego->personaje = cargar_personaje(pj);
    juego->menu = 0;
    juego->paso = 0;
    return juego;
}



