#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char almacenFila[1024];
    int columna  = 0;
    char *termino;

    fp = fopen("generacion_por_tecnologias_21_22.csv", "r");

    if (fp == NULL)
    {
        printf("Archivo no valido");
        exit(1);
    }
    while (fgets(almacenFila, 1024, fp)) {
        termino = strtok(almacenFila, ",");
        while (termino != NULL) {
            termino = strtok(NULL, ",");
            if (termino != NULL) {
                printf("%s ", termino);
            }
        }
    }
    fclose(fp);
    return 0;
}
