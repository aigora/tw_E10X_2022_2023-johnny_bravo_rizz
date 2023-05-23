#include<stdio.h>

int main()
{
	int menu=0, menu2;
	while(menu!=19)
	{
	printf("What type of electricity?: ");
	fgets(typeInput, sizeof(typeInput), stdin);
	double vectorFila[datosATrabajar.numColumnas - 1];
	menu = getVectorByName(&datosATrabajar, typeInput, vectorFila);
	while(menu<1 || menu>19)
	{
		printf("ese numero no es valido, intenta otra vez");
		printf("elige uno de los siguientes metodos de generacion de energia: 1: Hidraulica , 2: Turbinación bombeo , 3: Nuclear ,4: Carbón ,5:Fuel + Gas ,6:Motores diesel ,7:Turbina de gas ,8:Turbina de vapor ,9:Ciclo combinado ,10:Hidroeelica ,11:Eolica ,12:Solar fotovoltaica ,13: Solar termica ,14:Otras renovables ,15:Cogeneracion ,16:Residuos no renovables ,17:Residuos renovables ,18:Generacon total ,19: finalizar programa\n");
		scanf("%i", &menu);
	}
	
	while(menu>0 && menu<19)
	{ 
		getVectorByNum(&datosATrabajar,menu,0);
		printf("elige una tarea: 1:media , 2: varianza , 3: valor maximo y minimo , 4: energia total, 5: estimaciones de valores futuros, 6: volver a la seleccion de tipo de energia\n");
    		scanf("%i",&menu2);
    		while(menu2>6 || menu2<1)
    	{
    	printf("Lo siento ese, numero no es valido, elige otro")
    	printf("elige una tarea: 1:media , 2: varianza , 3: valor maximo y minimo , 4: energia total, 5: estimaciones de valores futuros, 6: finalizar\n");
    	scanf("%i",&menu2)
	}
		while(menu2<6 && menu2>0)
    		{
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
           		  break;
		   	}
    	    	   }
		}
	}
}
