#include <stdio.h>

void compararVectores(int vectores[][5], int numVectores, int longitud);

int main()
{
    int vector1[5];
    int vector2[5];
    int vector3[5];
    int vector4[5];
    int vector5[5];
    int numVectores = 5;
    int longitud = sizeof(vector1) / sizeof(vector1[0]);

    int vectores[][5] = {
        {2, 2, 3, 4, 3},
        {3, 2, 0, 4, 5},
        {1, 3, 3, 4, 1},
        {5, 2, 0, 4, 9},
        {1, 2, 3, 4, 2}
    };

    compararVectores(vectores, numVectores, longitud);

    return 0;
}

void compararVectores(int vectores[][5], int numVectores, int longitud) 
{
    int i, j, k;
    int diferencias = 0;

    printf("Diferencias encontradas:\n");

    for (i = 0; i < longitud; i++) {
        for (j = 0; j < numVectores - 1; j++) {
            for (k = j + 1; k < numVectores; k++) {
                if (vectores[j][i] != vectores[k][i]) {
                    int diferencia = vectores[j][i] - vectores[k][i];
                    if (diferencia < 0) {
                    	diferencia = 0- diferencia;
					}
                    
                    printf("Posición %i: vector%i[%i] = %i, vector%i[%i] = %i, Diferencia: %i\n", i, j+1, i, vectores[j][i], k+1, i, vectores[k][i], diferencia);
                    diferencias++;
                }
            }
        }
    }

    if (diferencias == 0) {
        printf("No se encontraron diferencias.\n");
    }
}
