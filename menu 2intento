#include<stdio.h>

int main() //poner eñ break en el switch case
{
	int menu, menu2; //plantilla menu
	printf("elige uno de los siguientes metodos de generacion de energia: 1: Hidraulica , 2: Turbinación bombeo , 3: Nuclear ,4: Carbón ,5:Fuel + Gas ,6:Motores diesel ,7:Turbina de gas ,8:Turbina de vapor ,9:Ciclo combinado ,10:Hidroeelica ,11:Eolica ,12:Solar fotovoltaica ,13: Solar termica ,14:Otras renovables ,15:Cogeneracion ,16:Residuos no renovables ,17:Residuos renovables ,18:Generacon total\n");
	scanf("%i", &menu); // habria que hacer un ultimo case en el que el usuario pueda elegir finalizar el programa y que se ejecute el programa infinitamente hasta que el usuario lo finalize
 
	getVectorByNum(&datosATrabajar,menu,0);
	printf("elige una tarea: 1:media , 2: varianza , 3: valor maximo y minimo , 4: energia total, 5: estimaciones de valores futuros\n");
    scanf("%i",&menu2)
    switch menu2
        {
          case 1:
            {
              printf("la media es : %f\n",media(&datosATrabajar));
              break;
            }
            
          case 2:
            {
              printf("la varianza es : %f\n",varianza(&datosATrabajar));
              break;
            }
            
          case 3:
            {
              printf("el maximo es : %f y el minimo es: %f\n",maximo(&datosATrabajar), minimo(&datosATrabajar));
              break;
            }
          case 4:
            {
              printf("la energia total es : %f\n",engtot(&datosATrabajar));
              break;
            }
          case 5:
            {
              regresion(&datosATrabajar);
		    }
          default
            {
              printf("ha abido un error , prueba otra vez\n");
            }
        }
}
