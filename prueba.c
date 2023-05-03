#include<stdio.h>
#include<stdiolib.h>
printf("holis")
//aqui el menu
int main()
{
  FILE *fp;
  char ch;
  fp = fopen("nombreDelArchivo.css", "r+"):
  while ((ch = fgetc(fp)) != EOF)
    print("%c", ch);
  fprintf(fp, "\n\n/* New content*/\n");
  fprintf(fp, "body { background-color: #f0f0f0; }");

  fclose(fp);

  printf("elige uno de los siguientes metodos de generacion de energia: 1: Hidraulica , 2: Turbinación bombeo , 3: Nuclear ,4: Carbón
  switch
  {
    case 1:
