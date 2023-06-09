#include <stdio.h>
#include <stdlib.h>
// funcion para sacar los datos de la matriz malloc (es la unica manera de sacar los datos de la matriz basicamente)
// si quieres leer o modificar la matriz, llamas esta funcion y te devuelve el puntero del vector palabra
// si quieres leer o algo lo unico trata la palabra como un vector y listo

int main()
{
    // variables para iniciar la lectura
    FILE *dimensionsScout;
    // Aqui se almacena toda la linea, maximo 1024 caracteres (creo que es suficiente)
    char pruebaDimensiones[1024];
    dimensionsScout = fopen("paco.csv", "r");
    // Error por si nos confundimos al escribir el archivo o se mueve o lo que sea
    if (dimensionsScout == NULL)
    {
        printf("Archivo no valido");
        exit(1);
    }
    // Declaración matriz con dimensiones variables
    for (int columna = 0; columna < 5; columna++){
        fgets(pruebaDimensiones, 1024, dimensionsScout);
    }
    int lastWasComma = 0;
    int isCommaInWord = 0;
    int columnNumber = 1;
    int transportVariable = 0;
    // Obtencion numero columnas
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
    // Obtencion numero filas (es uno menos xq no cuenta la 1a)
    int rowNumber = 1;
    while (fgets(pruebaDimensiones, 1024, dimensionsScout)){
        rowNumber++;
    }
    fclose(dimensionsScout);
    int maxSizeWords = 4;
    // declaracion de la matriz con malloc
    // inicializamos el vector que va a almacenar los punteros a las filas
    char*** matrizDatos = (char***)malloc(sizeof(char**)*rowNumber);
    printf(" %i %i \n\n", rowNumber, columnNumber);
    for (int filas = 0; filas < rowNumber; filas++){
        printf("b %i\n", filas);
        // para cada uno de los vectores de fila, declaramos otro vector que almacena cada una de las columnas
        matrizDatos[filas] = (char**)malloc(columnNumber*sizeof(char*));
        for (int columnas = 0; columnas < columnNumber; columnas++){
            printf("%i", columnas);
            // para cada una de las columnas, creamos un array que almacena el numero máximo de caracteres
            matrizDatos[filas][columnas] = (char*)malloc(128*sizeof(char));
            matrizDatos[filas][columnas][0] = 'A';
            printf("%s\n",matrizDatos[filas][columnas]);
            }
        }
    //char matrizDatos[rowNumber][columnNumber][128];
    printf(" %i %i ", rowNumber, columnNumber);
    // Aislamiento de datos en celdas de la matriz
    char almacenFila[4096];
    FILE *elementSeparation;
    elementSeparation = fopen("generacion_por_tecnologias_21_22.csv", "r");
    // Variables pseudobooleanas para saber si hay dos comas seguidas o si se esta mirando dentro de una palabra
    char element[128] = "";
    int letraElement = 0;
    int floatElement = 0;
    char tildeFix = 'a';
    int tildeOld = 0;
    int column = 0;
    int filaReal = 0;
    rowNumber += 4;
    char* punteroPalabra;
    for (int fila = 0; fila < rowNumber; fila++) {
        column = 0;
        // Se almacena el contenido de la fila en almacenFila
        fgets(almacenFila, 2048, elementSeparation);
        // reinicio de las variables para cada fila
        printf("%s", almacenFila);
        printf("\n");
        almacenFila[strlen(almacenFila)] = '\0';
        for (int letra = 0; almacenFila[letra] != '\0'; letra++){
            if (almacenFila[letra] == '"'){
            floatElement = !floatElement;
            continue;
            }
        if (almacenFila[letra] == ','){
            if (!floatElement){
                element[letraElement] = '\0';
                if (fila >= 4){
                    filaReal = fila - 4;
                    for (int a = 0; element[a] != '\0'; a++){
                        matrizDatos[filaReal][column][a] = element[a];
                        }
                    printf("%s",matrizDatos[filaReal][column]);
                    printf(" %i %i ", filaReal, column);
                    printf("\n");
                    printf("\nsuccessful\n");
                    column++;
                    }
                for (int i = 0; element[i] != '\0'; i++) {
                    for (int j = 0; j < 2; j++){
                        element[i + j] = '\0';
                        }
                    }
                letraElement = 0;
            }
            else{
                element[letraElement] = almacenFila[letra];
                letraElement++;
                printf("%s", element);
                printf("\n");
                }
        }
        if (almacenFila[letra] != ','){
            element[letraElement] = almacenFila[letra];
            letraElement++;
            printf("%s", element);
            printf("\n");
            }
        }
        element[letraElement] = '\0';
        for (int a = 0; element[a] != '\0'; a++){
            matrizDatos[filaReal][column][a] = element[a];
            }
        printf("%s",matrizDatos[filaReal][column]);
        printf(" %i %i ", filaReal, column);
        printf("\n");
        printf("\nsuccessful\n");
    }
for (int prueba2 = 0; prueba2 < 19; prueba2++){
for (int prueba = 0; prueba < 25; prueba++){
    printf("%s", matrizDatos[prueba2][prueba]);
    printf("\n");
}
printf("\n\n");
}
fclose(dimensionsScout);
return 0;
}
