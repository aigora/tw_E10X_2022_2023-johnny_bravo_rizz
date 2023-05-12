#include<stdio.h>

int main() //poner eñ break en el switch case
{
  int menu; //plantilla menu
  printf("elige uno de los siguientes metodos de generacion de energia: 1: Hidraulica , 2: Turbinación bombeo , 3: Nuclear ,4: Carbón ,5:Fuel + Gas ,6:Motores diesel ,7:Turbina de gas ,8:Turbina de vapor ,9:Ciclo combinado ,10:Hidroeelica ,11:Eolica ,12:Solar fotovoltaica ,13: Solar termica ,14:Otras renovables ,15:Cogeneracion ,16:Residuos no renovables ,17:Residuos renovables ,18:Generacon total");
  scanf("%i", &menu); // habria que hacer un ultimo case en el que el usuario pueda elegir finalizar el programa y que se ejecute el programa infinitamente hasta que el usuario lo finalize
  switch menu
  {
      case 1:
      {
        float vector[n] , vector1[n];
        vector[n] = vector1[n]; //el abjetivo de esta linea es asignar el valor del vector seleccionado en el case al vector[n]
        int menu2;
        printf("elige una tarea: 1:media , 2: varianza , 3: valor maximo , 4: valor minimo , 5: energia total");
        scanf("%i",&menu2)
        switch menu2
        {
          case 1:
            {
              printf("la media es : %f",media(vector[n]));
              break;
            }
            
          case 2:
            {
              printf("la varianza es : %f",varianza(vector[n]));
              break;
            }
            
          case 3:
            {
              printf("el maximo es : %f",maximo(vector[n]));
              break;
            }
            
          case 4:
            {
              printf("el minimo es : %f",minimo(vector[n]));
              break;
            }
            
          case 5:
            {
              printf("la energia total es : %f",engtot(vector[n]));
              break;
            }
            default
            {
              printf("ha abido un error , prueba otra vez");
            }
              
        break;
      }
      case 2:
      {
        break;
      }
      case 3:
      {
        break;
      }
      case 4:
      {
        break;
      }
      case 5:
      {
        break;
      }
      case 6:
      {
        break;
      }
      case 7:
      {
        break;
      }
      case 8:
      {
        break;
      }
      case 9:
      {
        break;
      }
      case 10:
      {
        break;
      }
      case 11:
      {
        break;
      }
      case 12:
      {
        break;
      }
      case 13:
      {
        break;
      }
      case 14:
      {
        break;
      }
      case 15:
      {
        break;
      }
      case 16:
      {
        break;
      }
      case 17:
      {
        break;
      }
      case 18:
      {
        break;
      }
      default:
      {
        printf("no es valido , vuelve a empezar");
        break;
      }
    }
  }
  
  //ver codigo de lectura de fichero de baselga para completar los vectores
  
float media(float vector[n])
{
  int i;/*valor unico*/
  float j = vector[0];/*sumatorio de los valores*/
  for(i=0; i<n ; i++)
  {
    j=j+vector[i];
  }
  float resultado=(j)/(n);/*n es el tamaño del vector , osea , el numero de valores*/
}return resultado
  

  
  
float maximo(float vector[n])
{
  int i;
  float resultado=0;
  for(i=0 ; i<n ; i++) //alomejor habria que hacer esto con while
  {
    if (resultado < vector[i])
    {
      resultado = vector[i]
    }
  } 
}return resultado     
  
  
  
float minimo(float vector[n])
{
  int i;
  float resultado = vector[0];
  for(i=0 ; i<n ; i++) //alomejor habria que hacer esto con while
  {
    if (resultado > vector[i])
    {
      resultado = vector[i]
    }
  } 
}return resultado 
  
  
  
float varianza(float vector[n]) //revisar esto, creo que no funciona
{
  int i;
  float resultado , sum=0;
  for(i=0 ; i<n ; i++)
  {
    sum = (sum-media(vector[n])) * (sum-media(vector[n]))
  }
  resultado = sum / n;
}return resultado 
  
  
float covarianza(float vector[n], float vector2[n])
{
  int i;
  for(i=0 ; i<n)
}
  
float engtot(float vector[n]) //energia total generada a lo largo del tiempo
{
  float resultado = vector[0];
  for(i=1 , i<n , i++)
  {
    resultado = resultado +  vector[i];
  }
}return resultado
  
  
float regresion(float vector[n] , int vector2[n])//calcula la recta de regresion de una fila de datos usando la media la varianza y la covarianza(hay que hacer la covarianza aun) para usando esa recta hacer una estimacion de lo que podria ser un valor futuro
{//en regresion hay que introducir tres datos , el primer vector (y) es el valor energético , el segundo vector son los dias o fechas en los que ocurren esos valores , las fechas se hacen como numeros enteros para facilitar los calculos .
  float regresion, b;
  b = (covarianza(vector[n],vector2[n]))/(varianza(vector2[n]))
  regresion = media(vector[n])+b*(x-media(vector2[n]))
}
  

  
