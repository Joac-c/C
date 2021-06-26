#include <string.h>

#include "testing.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"


/*
 * Devuelve una nueva cadena con los primeros ‘n’ caracteres de la cadena
 * ‘str’. La liberación de la memoria dinámica devuelta queda a cargo de
 * quien llame a esta función.
 *
 * Devuelve NULL si no se pudo reservar suficiente memoria.
 */
char *substr(const char *str, size_t n){
    // Esta es una version O(n) del algoritmo. No se me ocurre como hacerla constante. 
    
    if(str[0] == '\0' || n == 0){
        char* nueva = calloc(1, sizeof(char));
        nueva[0] = '\0';
        return nueva;    
    }
    
    char* nueva = calloc(n + 1, sizeof(char));
    int i = 0;
     
    while(true){
        if(i == n || str[i] == '\0'){
            nueva[i] = '\0';
            return nueva;
        }
        nueva[i] = str[i];
        i++;
    }
    nueva[i - 1] = '\0';
    return nueva;
}

/*
 * Devuelve en un arreglo dinámico terminado en NULL todos los subsegmentos de
 * ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene se ubicarán en nuevos espacios de memoria dinámica.
 *
 * La liberación de la memoria dinámica devuelta queda a cargo de quien llame a
 * esta función. La función devuelve NULL en caso de error.
 */

char **_split(const char *str, char sep, size_t palabras){
    //printf("%s", str);
    if(str[0] == '\0'){
        char** lista = calloc(palabras + 1, sizeof(char*));
        lista[palabras] = NULL;
        return lista;
    }
    //if(str[0] == sep) str++;
    bool sigo = true;
    size_t letras = 0;
    char* palabra;
    while(sigo){
        if(str[letras] == sep || str[letras] == '\0'){
            palabra = substr(str, letras);
            //printf("%s\n", palabra);
            palabras++;
            sigo = false;
        }
        if(str[letras] != '\0')letras++;
    }
    char** lista = _split(str + letras, sep, palabras);
    lista[palabras - 1] = palabra;
    return lista;

}

char **split(const char *str, char sep){
    size_t palabras = 0;
    return _split(str, sep, palabras);

}

/*
 * Devuelve la cadena resultante de unir todas las cadenas del arreglo
 * terminado en NULL ‘str’ con ‘sep’ entre cadenas. La cadena devuelta se
 * ubicará en un nuevo espacio de memoria dinámica.
 *
 * La liberación de la memoria dinámica devuelta queda a cargo de quien llame a
 * esta función. La función devuelve NULL en caso de error.
 */
char *join(char **strv, char sep);

/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char *strv[]);