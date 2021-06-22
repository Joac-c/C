
README DEL TDA NRO 2: ARBOL BINARIO B

Resumen.
El trabájo consiste en implementar un ABB (Árbol Binario B) a partir de las clases Nodo, que contiene punteros al elemento almacenado y hacia 
sus dos nodos hijos, y Árbol, con punteros hacia el nodo raíz, la función comparar(impresindible para encontrar elementos) y la función 
destruir(opcional segun los requerimientos del usuario).
Las funcion arbol_crear() reserva la memoria para un arbol e inicializa sus atributos. Las funciones arbol_vacio() y arbol_raiz() verifican
si el nodo_raiz del arbol es o no NULL respectivamente (al crear el arbol la raiz se inicializa como NULL).
El resto de las funciones tienen implementaciones recursivas. arbol_insertar() utiliza insertar_final() en caso de que el arbol tenga raiz.
Esta recorre el arbol desde la raiz comparando cada elemento con el que se busca insertar y descendiendo por la rama correspondiente hasta 
alcanzar una hoja, donde le asigna como hijo el nuevo nodo. Para las funciones que requieren de buscar algún elemento dentro del árbol
(arbol_buscar() y arbol_borrar()) creé clase Ubicador_t.
 Contiene:
- Un puntero hacia un puntero a nodo. Esta parte es importante porque permite editar los hijos de cada nodo desde el puntero que los enlaza, 
  desconociendo al nodo en si. 
- Un integer que indica el número de hijos que tiene dicho nodo.
- Punteros a las funciones destruir y comparador.
A su vez cree la funcion buscar_nodo() que inicializa ubicador_t y utilizando _buscar_nodo() recorre el arbol de manera similar a insertar_final()
exeptuando que si encuentra el elemento buscado devuelve el ubicador con la direccion del puntero al nodo y el numero de hijos que tiene. 
En arbol_buscar() simplemente utilizo _buscar_nodo() y devuelvo el elemento del nodo encontrado (si este no es NULL). 
En arbol_borrar() el mecanismo inicial es el mismo. Luego, utilizando la informacion que brinda el ubicador(cuantos hijos tiene el nodo encontrado)
 aplico una de estas tres funciones:

- arbol_borrar_sin_hijos(). Recibe el ubicador y si hay destructor lo aplica sobre el elemento del nodo señalado. Luego, libera dicho nodo.

- arbol_borrar_un_hijo(). Recibe el ubicador y copia la direccion del nodo en un puntero auxiliar. Luego sustituye al nodo por su unico hijo.
  Finalmente destruye(si puede) el elemento y libera el nodo encontrado. 

- arbol_borrar_dos_hijos(). Recibe el ubicador. Luego utiliza la funcion ultimo_derecha() que recorre recursivamente el arbol bajando por los hijos
  derechos(a partir del hijo izquierdo del nodo a borrar) y devuelve un ubicador (ultimo) con la informacion del ultimo nodo de esa rama. El elemento
  de dicho nodo remplaza al que deseamos borrar (tras haberlo destruido si es posible). Finalmente el ultimo nodo es eliminado de forma similar a las
  funciones anteriores segun si tiene o no hijo izquierdo.

Para las funciones de recoridos (inorden, preorden y postorden) utilice implementaciones recursivas con estructuras similares, distinguidas por
el orden en que se realizaban las autollamadas recursivas y se añadian los elementos al vector. Para identificar cuando debia frenar la funcion 
utilice un contador que crece en una unidad al añadir un elemento al array y es devuelto por la funcion. En el caso del recorrido postorden, 
ademas, agregue un puntero a un valor booleano que informa en caso de que ya este completo el vector.

En funcion abb_con_cada_elemento() utilice switch() para elegir una de tres funciones, una para cada tipo de recorrido y de mecanica similar a los recorridos.
En esta ocacion utilice en todas un puntero a un valor booleano para informar si la condicion de corte ya se cumplio y frenar las iteraciones.

Una vez completada cada funcion (creadas en orden de complejidad) implemente las pruebas necesarias para verificar que funcionen correctamente antes de avanzar
con las siguiientes funciones. Para todas utilice la misma lista de 17 elementos, distribuidos de modo que el arbol se cargue balanceado. implemente las pruebas:

- acciones_basicas(). Con esto verifique crear_arbol(), arbol_raiz(), arbol_vacio(), arbol_insertar() y arbol_borrar() para casos simples, con dos elementos
  y argumentos NULL

- inserciones_y_busquedas(). Primero inserta todos los elementos de la lista y verifica que haya habido 17 exitos. Luego busca cada elemento y verifica que 
  la raiz sea correcta.

- prueba_inorden(), prueba_preorden() y prueba postorden(). Las tres son iguales, primero cargan el arbol e imprimen cada elemento en orden de carga. Luego
  recorren el arbol(primero con un arreglo mas grande y luego con uno mas chico que la cantidad de elementos) e imprimen el recorrido. El usuario debera
  verificar manualmente si los recorridos se dieron correctamente.

- pruebas_de_borrado() primero carga el arbol. Luego elimina varios elementos en distintas posiciones del arbol y realiza busquedas verificando que se 
  hayan eliminado los elementos correctos. Finalmente elimina todos los elementos del arbol desde la raiz, imprimiendolos.
  pruebas_de_borrado_sin_destructor() realiza las mismas pruebas con la diferencia de que el arbol cargado no tiene destructor, verificando asi q
  que los borrados funcionen sin el.

- Las tres pruebas de abb_con_cada_elemento() son similares. Cargan el arbol. Pimero lo recorren entero y luego hasta cierto elemento verificando 
  que el numero de iteraciones sea correcto. Por ultimo verifican que no se pueda iterar con un valor nulo.

Todas las pruebas utilizan arbol_destruir() al finalizar su ejecucion. 
                            
///La linea de compilacion es: cc abb.c abb_pruebas.c -std=c99 -g -O0 -Wall -Wconversion -Werror -o abb
///La linea de ejecucion es: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb


Teoria.

1. Un abb es un tipo de dato abstracto del tipo arbol binario. Esto quiere decir que sus elementos se encuentran organizados
en nodos, cada uno de los cuales posee a su vez dos nodos "hijos". El unico nodo que no es "hijo" de nadie (no posee "padre") es 
la raiz del arbol. A partir de esta ultima podemos acceder al resto del arbol. La particularidad del abb es que, ademas de ser un arbol
binario, los nodos estan ordenados por la magnitud de alguna clave. El hijo derecho de cualquier nodo siempre sera mayor y el izquierdo 
siempre sera menor (o a la inversa). De esta manera se establece una estructura recursiva donde el valor del nodo siempre crece descendiendo
por la rama derecha y siempre decrece descendiendo por la rama izquierdo.

2. La funcion destruccion permite liberar automaticamente la memoria ocupada por los elementos cuyos nodos son borrados del arbol. 
De otra forma esto deberia hacerlo el usuario. En los casos donde no deseamos perder el contenido de los elementos es util que no 
exista dicha funcion. Tambien puede ocurrir que los elementos se encuentren almacenados en memoria estatica en cuyo caso no podemos
ni hace falta liberar dicha memoria.

3. 
- Las funciones crear_arbol(), arbol_vacio() y arbol_raiz() son O(1) porque todas utiliizan operaciones de tiempo constante (reservar memoria y 
verificar la raiz) una unica vez.
- arbol_buscar(), arbol_insertar() y arbol_borrar() son las tres O(n) porque todas requieren buscar un elemento (el resto de las operaciones
son de tiempo constante). Esto puede implicar recorrer una rama del arbol hasta el final si el nodo que lo contiene es una hoja y, dado que el
arbol no es avl(no se encuentra balanceado), dicha rama es potencialmente tan larga como la cantidad de elementos en el arbol.  
- Los iteradores del arbol (recorridos y abb_con_cada_elemento()) son tambien O(n) porque La implementacion es recursiva y cada llamado
recursivo(uno por nodo recorrido) es de tiempo constante. En el caso mas extenso (que el arreglo sea mayor o igual al
arbol o que la condicion de corte no se active respectivamente) deben recorrerese todo el arbol. En el caso de arbol_destruir() es lo mismo
exeptuando que siempre hace falta recorrer todo el arbol para destruir todos los nodos. 