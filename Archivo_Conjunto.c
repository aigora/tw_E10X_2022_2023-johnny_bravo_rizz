#include <stdio.h>
#include <stdlib.h>
// El códigpo está comentado casi todo, si falta algo o algo no funciona mandadme un was
// las variables están un poco en spanglish xq estoy acostumbrado a escribir en ingles codigo, pero todo es mio asi q dont worry x plagio
// hay printfs al inicio del proceso de indexado pero me sirven para ver si funciona, no les hagais mucho caso
// NOTA PARA YO DEL FUTURO: Elimina todos  los \n que puedas xq hacen que el codigo corra bastante más rápido
// Esta estructura se usa mas abajo pero por el tema de la funcion tengo que declararla aquí arriba
// De aquí se sacan los datos de la matriz para meterlos a vectores para trabajar con ellos
struct datosMatriz{
    int numColumnas;
    int numFilas;
    int numColumnas;
    char ***matriz;
    char **vectorFilaFechas;
    char **vectorColumnaTitulos;
    double *vectorFila;
    double *vectorColumna;
};
void getVectorByNum (struct datosMatriz *datosATrabajar, int filaDeseada, int columnaDeseada){
if (filaDeseada){
    printf("Output row: %i\n", filaDeseada);
    for (int columna = 1; columna < datosATrabajar->numColumnas; columna++){
        datosATrabajar->vectorFila[columna] = strtof(datosATrabajar->matriz[filaDeseada][columna], NULL);
        printf("%.6f\n", datosATrabajar->vectorFila[columna]);
    }
}

printf("\n\n");
if (columnaDeseada){
    printf("Output column: %i\n", columnaDeseada);
    for (int fila = 1; fila < datosATrabajar->numFilas; fila++){
        datosATrabajar->vectorColumna[fila] = strtof(datosATrabajar->matriz[fila][columnaDeseada], NULL);
        printf("%.6f\n", datosATrabajar->vectorColumna[fila]);
    }
}
return;
}
int main()
{
    // variables para iniciar la lectura
    FILE *dimensionsScout;
    // Aqui se almacena toda la linea, maximo 1024 caracteres (creo que es suficiente)
    char pruebaDimensiones[2048];
    // se llama paco xq estuve probando cosas y se ha quedado asi, si vais a probarlo en vuestro pc
    // guardad el csv en la misma carpeta q el archivo de c y meteis aqui el codigo q sea
    dimensionsScout = fopen("paco.csv", "r");
    // Error por si nos confundimos al escribir el archivo o se mueve o lo que sea
    if (dimensionsScout == NULL)
    {
        printf("Archivo no valido");
        exit(1);
    }
    // Declaración matriz con dimensiones variables por malloc
    for (int columna = 0; columna < 5; columna++){
        fgets(pruebaDimensiones, 1024, dimensionsScout);
    }
    int lastWasComma = 0;
    int isCommaInWord = 0;
    int columnNumber = 1;
    int transportVariable = 0;
    // Coge una fila con datos (la 5) y prueba a ver cuantas columnas de datos hay contando las comas
    // Se asume que delante de cada dato hay una coma, sin contar el titulo
    for (int letra = 0; letra < strlen(pruebaDimensiones); letra++){
        if (pruebaDimensiones[letra] == ','){
            if (lastWasComma){
                break;
            }
            columnNumber++;
            lastWasComma = 1;
        }
        else{
            lastWasComma = 0;
        }
    }
    int rowNumber = 1;
    // A partir de la linea 5 (donde empiezan los datos) se pone a intentar leer lineas hasta que está vacio y para
    while (fgets(pruebaDimensiones, 1024, dimensionsScout)){
        rowNumber++;
    }
    fclose(dimensionsScout);
    int maxSizeWords = 4;
    // declaracion de la matriz con malloc
    // inicializamos el vector que va a almacenar los punteros a las filas
    // Esto no le hagais mucho caso, pero está declarando un tensor asiq necesito usar punteros triples
    // Creo un vector que almacena los punteros de cada uno de los vectores fila
    char*** matrizDatos = (char***)malloc(sizeof(char**)*rowNumber);
    printf(" %i %i \n\n", rowNumber, columnNumber);
    for (int filas = 0; filas < rowNumber; filas++){
        printf("b %i\n", filas);
        // para cada uno de los vectores de fila, declaramos otro vector que almacena los punteros
        // de los vectores de cada una de las columnas (o datos individuales es lo mismo)
        matrizDatos[filas] = (char**)malloc(columnNumber*sizeof(char*));
        for (int columnas = 0; columnas < columnNumber; columnas++){
            printf("%i", columnas);
            // para cada una de las columnas, creamos un vector que almacena el numero máximo de caracteres
            matrizDatos[filas][columnas] = (char*)malloc(80*sizeof(char));
            // Esto inicializa cada una de las celdas y les mete un valor para que no estén vacias y pasen cosas feas
            matrizDatos[filas][columnas][0] = 'A';
            printf("%s\n",matrizDatos[filas][columnas]);
            }
        }
    // comprobación de las dimensiones de la matriz
    printf(" %i %i ", rowNumber, columnNumber);


    // De aqui en adelante se trabaja la matriz per se de las dimensiones que hayan salido
    char almacenFila[2048];
    FILE *elementSeparation;
    elementSeparation = fopen("generacion_por_tecnologias_21_22.csv", "r");
    char element[80] = "";
    // Variables pseudobooleanas que sirven para comprobar cositas
    int letraElement = 0;
    int floatElement = 0;
    int column = 0;
    int filaReal = 0;
    rowNumber += 4;
    int isFirstComma = 1;
    // Se va mirando fila por fila lo que hay y se va almacenando en celdas de la matriz "matrizDatos"
    for (int fila = 0; fila < rowNumber; fila++) {
        column = 0;
        // Se almacena el contenido de la fila en almacenFila
        fgets(almacenFila, 2048, elementSeparation);
        printf("%s", almacenFila);
        printf("\n");
        // Iteramos hasta el final de la linea (hasta que sale \0)
        for (int letra = 0; almacenFila[letra] != '\0'; letra++){
            // si hay una doble coma, se considera que estás dentro de un decimal y la coma de dentro no la interpreta
            // como separación de elementos sino como coma decimal
            if (almacenFila[letra] == '"'){
            floatElement = !floatElement;
            continue;
            }
        if (almacenFila[letra] == ','){
            if (!floatElement){
                // Se ejecuta si pilla una coma fuera de un decimal
                element[letraElement] = '\0';
                if (fila >= 4){
                    // a partir de la fila 5 va almacenando cosas en las celdas
                    filaReal = fila - 4;
                    for (int a = 0; element[a] != '\0'; a++){
                        matrizDatos[filaReal][column][a] = element[a];
                        }
                    printf("%s",matrizDatos[filaReal][column]);
                    printf(" %i %i \nsuccessful\n", filaReal, column);
                    column++;
                    }
                // Esto a veces hace falta a veces no, para la version final si no se corrompe nada lo quitamos
                // Es un fix xq a veces el ultimo término salia raro y ya no pasa, pero porsiaca lo dejo anotado
                /*
                for (int i = 0; element[i] != '\0'; i++) {
                    element[i] = '\0';

                    for (int j = 0; j < 2; j++){
                        element[i + j] = '\0';
                        }

                    }
                */
                letraElement = 0;
            }
            else{
                // esto es si es una coma decimal lo trata como un digito normal
                element[letraElement] = almacenFila[letra];
                letraElement++;
                printf("%s", element);
                printf("\n");
                continue;
                }
            for (int a = 0; element[a] != '\0'; a++){
                element[a] = '\0';
            }
        }
        if (almacenFila[letra] != ','){
            // Si no es una coma almacena el digito en element
            // element es un array que sirve como buffer para el contenido de las celdas, cuando se transfiere se vacia
            element[letraElement] = almacenFila[letra];
            letraElement++;
            printf("%s\n", element);
            }
        }
        element[letraElement - 1] = '\0';
        // Este se ejecuta para el último elemento xq no hay una coma al final de la linea
        for (int a = 0; element[a] != '\0'; a++){
            matrizDatos[filaReal][column][a] = element[a];
            element[a] = '\0';
            }
        printf("%s",matrizDatos[filaReal][column]);
        printf(" %i %i ", filaReal, column);
        printf("\n");
        printf("\nsuccessful\n");
    }
// Esta es la comprobación de que los datos se han guardado bien
for (int prueba2 = 0; prueba2 < 19; prueba2++){
    for (int prueba = 0; prueba < 25; prueba++){
        printf("%s", matrizDatos[prueba2][prueba]);
        printf(" %i %i\n", prueba2,prueba);
    }
printf("\n\n");
}
fclose(dimensionsScout);    
// <---------------- PREPARACIÓN DE LOS DATOS PARA USO ------------------------->
rowNumber -= 4;
// Declaramos una estructura donde meteremos punteros a una serie de vectores (ir al principio del archivo para explicación)
struct datosMatriz datosATrabajar;
datosATrabajar.matriz = matrizDatos;
datosATrabajar.numColumnas = columnNumber;
datosATrabajar.numFilas = rowNumber;
// Declaramos los vectores en funcion del tamaño de la tabla con malloc
// El vector vectorColumnaTitulos almacenará los titulos de las diferentes filas en un vector char
datosATrabajar.vectorColumnaTitulos = (char**)malloc(sizeof(char*)*rowNumber);
// El vector vectorColumna se llenará con datos double de la columna puntual con la que trabajemos gracias a la funcion getVectorByNum
datosATrabajar.vectorColumna = (double*)malloc(sizeof(double*)*(rowNumber-1));
for (int tituloFila = 0; tituloFila < rowNumber; tituloFila++){
    // Declaramos los punteros de memoria para cada array de caracteres, y los llenamos con el titulo de la fila correspondiente
    datosATrabajar.vectorColumnaTitulos[tituloFila] = (char*)malloc(sizeof(char)*80);
    for (int letra = 0; matrizDatos[tituloFila][0][letra] != '\0'; letra++){
        datosATrabajar.vectorColumnaTitulos[tituloFila][letra] = matrizDatos[tituloFila][0][letra];
    }
    printf("\ntitulo: %s\n",datosATrabajar.vectorColumnaTitulos[tituloFila]);
};
// El vector vectorFilaFechas almacenará la fila de fechas en un vector char
datosATrabajar.vectorFilaFechas = (char**)malloc(sizeof(char*)*(columnNumber-1));
datosATrabajar.vectorFila = (double*)malloc(sizeof(double)*(columnNumber-1));
for (int fechaColumna = 1; fechaColumna < columnNumber; fechaColumna++){
    datosATrabajar.vectorFilaFechas[fechaColumna - 1] = (char*)malloc(sizeof(char)*80);
    for (int letra = 0; matrizDatos[0][fechaColumna][letra] != '\0'; letra++){
        datosATrabajar.vectorFilaFechas[fechaColumna - 1][letra] = matrizDatos[0][fechaColumna][letra];
    }
    printf("\nfecha: %s\n",datosATrabajar.vectorFilaFechas[fechaColumna - 1]);
};
getVectorByNum(&datosATrabajar, 5, 3);
    
/* NOTA IMPORTANTE SOBRE EL USO DE LOS VECTORES DE LA MATRIZ:
Los vectores no van a ser vectores per se, son elementos de la estructura datosATrabajar
La funcion getVectorByNum tiene dos parametros, y con esos dos sacas los vectores que quieras
El primero es la FILA que quieres, sus valores van entre 0 y 18, el segundo es la COLUMNA que quieres, sus valores van entre 0 y 25.
Si no quieres sacar un vector fila y un vector columna a la vez y quieres solo uno de los dos, el que no quieras dejalo con VALOR 0
Teoricamente estos datos se podrían ajustar a una tabla de cualquier tamaño, pero en nuestro caso se van a quedar entre esos valores siempre
Cuando llamas a esa funcion, lo que va a cambiar son los vectores de dentro la estructura, para acceder a ellos, tienes que escribir datosATRabajar.vectorFila o datosATrabajar.vectorColumna segun el que quieras
EJEMPLO DE USO: quieres la fila 3 ->
getVectorByNum(&datosATrabajar, 3, 0)
datosATrabajar.vectorFila <-- este es tu vector


*/
return 0;
}

