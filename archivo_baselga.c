#include <stdio.h>
#include <stdlib.h>

int main()
{   
    // variables para iniciar la lectura
    FILE *fp;
    // Aqui se almacena toda la linea, maximo 1024 caracteres (creo que es suficiente)
    char almacenFila[1024];
    int columna  = 0;
    // Aqui se van almacenando los valores individuales
    char *termino;
    fp = fopen("generacion_por_tecnologias_21_22.csv", "r");
    // Error por si nos confundimos al escribir el archivo o se mueve o lo que sea
    if (fp == NULL)
    {
        printf("Archivo no valido");
        exit(1);
    }
    // bucle principal
    for (int colummna = 0; columna < 6; columna++) {
            // Se almacena el contenido de la fila en almacenFila
            fgets(almacenFila, 1024, fp);
            // Variable de cuantas palabras hay en la fila
            int numeroPalabras = 0;
            // Variables pseudobooleanas para saber si hay dos comas seguidas o si se esta mirando dentro de una palabra
            int lastWasComma = 0;
            int isCommaInWord = 0;
            // Bucle de recuento de palabras
            for (int letra = 0; letra < strlen(almacenFila); letra++){
                if (almacenFila[letra] == 34){
                    isCommaInWord = !isCommaInWord;
                }
                if (!isCommaInWord){
                    if (almacenFila[letra] == ','){
                        if (lastWasComma){
                            break;
                        }
                            numeroPalabras++;
                            lastWasComma = 1;
                    }
                    else{
                        lastWasComma = 0;
                    }
                }
            }
            printf("%i", numeroPalabras);
            printf("\n");
            // Print de cada uno de los valores individuales (hay que cambiarlo xq las comas de dentro de los valores decimales se los come)
            termino = strtok(almacenFila, ",");
            while (termino != NULL && columna != 3)
            {
                termino = strtok(NULL, ",");
                if (termino != NULL)
                {
                    printf("%s ", termino);
                }
            }
    }
    fclose(fp);
    return 0;
}
