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
    char ***matriz;
    char **vectorFilaFechas;
    char **vectorColumnaTitulos;
    char **vectorFila;
    char **vectorColumna;
    int longitudIntervalo;
};

float media(struct datosMatriz *datosATrabajar, double* Vector);
float media1(double* Vector);
float varianza(struct datosMatriz *datosATrabajar, double* Vector);
float varianza1(double* Vector);
float engtot(struct datosMatriz *datosATrabajar, double* Vector);
void regresion(struct datosMatriz *datosATrabajar, double* Vector);
void grafica(struct datosMatriz *datosATrabajar, double* Vector);
// FUNCION PARA SACAR SOLO UN CACHO DE LA MATRIZ
int getSpliceOfVector (struct datosMatriz *datosATrabajar, char* inicioSplice, char* finSplice, char* filaSpliced, double* vectorSpliced){
	int fechaInicio = getNumberFromName(datosATrabajar, inicioSplice)/29;
	int fechaFinal = getNumberFromName(datosATrabajar, finSplice)/29;
	int intfilaSpliced = getNumberFromName(datosATrabajar, filaSpliced)/31;
	int fila;
	for (fila = fechaInicio; fila <= fechaFinal; fila++){
		vectorSpliced[fila - fechaInicio] = strtof(datosATrabajar->matriz[intfilaSpliced][fila], NULL);
		printf("\n%.6f %i\n",vectorSpliced[fila - fechaInicio], fila);
	}
return intfilaSpliced;
}
// FUNCION PARA CONVERTIR EL TITULO DE LA FILA/COLUMNA A SU POSICION NUMERICA
int getNumberFromName (struct datosMatriz *datosATrabajar, char* peticion){
int filas, columnas, letra, sizeOfVector;
int columnaDeseada = 0;
int filaDeseada = 0;
for (filas = 0; filas < datosATrabajar->numFilas; filas++){
	letra = 0;
	while (datosATrabajar->vectorColumnaTitulos[filas][letra] != '\0' && peticion[letra] != '\0') {
	        if (datosATrabajar->vectorColumnaTitulos[filas][letra] != peticion[letra]) {
				break;  // Strings are not equal
	        }
	        letra++;
	    }
	    if ((datosATrabajar->vectorColumnaTitulos[filas][letra] == '\0'|| datosATrabajar->vectorColumnaTitulos[filas][letra] == '\n') && (peticion[letra] == '\0' || peticion[letra] == '\n')) {
			filaDeseada = filas;
			return (filaDeseada)*31;;  // Strings are equal
	    }  // Strings are not equal
	}
if (!filaDeseada){
	for (columnas = 0; columnas < datosATrabajar->numColumnas - 1; columnas++){
	letra = 0;
	while (datosATrabajar->vectorFilaFechas[columnas][letra] != '\0' && peticion[letra] != '\0') {
	        if (datosATrabajar->vectorFilaFechas[columnas][letra] != peticion[letra]) {
				break;  // Strings are not equal
	        }
	        letra++;
	    }
	    if ((datosATrabajar->vectorFilaFechas[columnas][letra] == '\0'|| datosATrabajar->vectorFilaFechas[columnas][letra] == '\n') && (peticion[letra] == '\0' || peticion[letra] == '\n')) {
	        columnaDeseada = columnas;
			return (columnaDeseada + 1)*29;  // Strings are equal
	    }  // Strings are not equal
	}
}
printf("\n No column or row by that name \n");
return 0;	

}
// FUNCION SACAR VECTOR FILA/COLUMNA POR NOMBRE 
int getVectorByName (struct datosMatriz *datosATrabajar, char* peticion, double* vectorPeticion){
int sizeOfVector, alojamientoVector, deseo;
deseo = getNumberFromName(datosATrabajar, peticion);
if (!deseo){
	printf("\nThe spelling went wrong or something failed\n");
	return 0;
}
// IMPORTANTE AVISO
// En c no hay error por colocar valores fuera del scope de un array, asi que hay que cuidar mucho el tamaño de los vectores que le metes a esta funcion
if (!(deseo%31)){
	int filaDeseada = deseo/31;
	printf("Fila deseada: %i\n\n", filaDeseada);
	sizeOfVector = datosATrabajar->numColumnas;	
	for(alojamientoVector = 1; alojamientoVector < sizeOfVector; alojamientoVector++){	
		vectorPeticion[alojamientoVector - 1] = strtof(datosATrabajar->matriz[filaDeseada][alojamientoVector], NULL);
		printf("%.6f %i\n",vectorPeticion[alojamientoVector - 1], alojamientoVector);
	}
	// Parte de luis
	return filaDeseada;
}
else if (!(deseo%29)){
	int columnaDeseada = deseo/29;
	printf("Columna deseada: %i\n\n", columnaDeseada);
	sizeOfVector = datosATrabajar->numFilas - 1;
	for(alojamientoVector = 1; alojamientoVector < sizeOfVector; alojamientoVector++){	
		vectorPeticion[alojamientoVector - 1] = strtof(datosATrabajar->matriz[alojamientoVector][columnaDeseada], NULL);
		printf("%.6f %i\n",vectorPeticion[alojamientoVector - 1], alojamientoVector);
	}
}
else{
	printf("No match found, please check your spelling or see the list of available options\nSi quieres sacar la columna titulos o la fila fechas, reminder de que estan en la estructura datosATRabajar\n");
	return -1;
}
}

	
// FUNCION PARA SACAR UN VALOR CONCRETO DE ALGUN SITIO DE LA MATRIZ
double getExactValueFromMatrix(struct datosMatriz *datosATrabajar, char* tituloDeseado, char* fechaDeseada){
int filas, columnas, letra;
int columnaDeseada = getNumberFromName(datosATrabajar, fechaDeseada)/29;
if (columnaDeseada){
	int filaDeseada = getNumberFromName(datosATrabajar, tituloDeseado)/31;
	if (filaDeseada){
		return strtof(datosATrabajar->matriz[filaDeseada][columnaDeseada], NULL);
	}
	}
printf("Could not get exact value from matrix\n");
return 0;
}
void sortVector (struct datosMatriz *datosATrabajar, double* vectorAOrdenar, char mayorOMenor)
{
// Esta es una implementación adaptada a nosotros de un algortimo que ya existe llamado BubleSort
printf("\n%c \n",datosATrabajar->vectorFilaFechas[0][0]);
int i, j, letra; 
double temporalStore;
char buffer;
char temporalDateStore[7];
printf("Before sort: \n");
for (i= 0; i < datosATrabajar->numColumnas - 1; i++){
	datosATrabajar->vectorFila[i] = datosATrabajar->vectorFilaFechas[i];
	printf("%s\n", datosATrabajar->vectorFila[i]);
	printf(" %.6f ", vectorAOrdenar[i]);
	
}
printf("\n");
if (mayorOMenor == '<'){
	for (i= 0; i < datosATrabajar->numColumnas-2; i++){
		for (j= 0; j < datosATrabajar->numColumnas-2-i;j++){
			if (vectorAOrdenar[j] > vectorAOrdenar[j+1]){
				temporalStore = vectorAOrdenar[j];
				vectorAOrdenar[j] = vectorAOrdenar[j+1];
				vectorAOrdenar[j+1] = temporalStore;
				datosATrabajar->vectorColumna[j] = datosATrabajar->vectorFila[j];
				datosATrabajar->vectorFila[j] = datosATrabajar->vectorFila[j+1];
				datosATrabajar->vectorFila[j+1]= datosATrabajar->vectorColumna[j];
			
				
			}
		}
	}
}
else if (mayorOMenor == '>'){
	for (i= 0; i < datosATrabajar->numColumnas-2; i++){
		for (j= 0; j < datosATrabajar->numColumnas-2-i;j++){
			if (vectorAOrdenar[j] < vectorAOrdenar[j+1]){
				temporalStore = vectorAOrdenar[j];
				vectorAOrdenar[j] = vectorAOrdenar[j+1];
				vectorAOrdenar[j+1] = temporalStore;
				datosATrabajar->vectorColumna[j] = datosATrabajar->vectorFila[j];
				datosATrabajar->vectorFila[j] = datosATrabajar->vectorFila[j+1];
				datosATrabajar->vectorFila[j+1]= datosATrabajar->vectorColumna[j];
			}
		}
	}
}
else{
	printf("That is not one of the two options sugested\n");
	return;
}
printf("After sort: \n");
for (i= 0; i < datosATrabajar->numColumnas-1; i++){
	printf("%s  %.6f \n", datosATrabajar->vectorFila[i],vectorAOrdenar[i]);
}
} 		
int main()
{
	char inputArchivo[40];
	int filasAntesDatos;
	int filasDespuesDatos;
	printf("\nBienvenido/a al indexador de csv del grupo johnny bravo rizz. \n\nEsta aplicación está programada de tal manera que puede leer cualquier csv que se le ofrezca, siempre y cuando\nse ajusten ciertos parametros. \n\nHemos preparado 3 archivos de demostración, por favor elige cual deseas (introduce el numero):\n");
	printf("1.SALDOS POR FRONTERAS - FÍSICO_01-05-2022_29-05-2023\n");
	printf("2.ESTRUCTURA DE LA GENERACIÓN POR TECNOLOGÍAS_01-01-2021_31-12-2022\n");
	printf("3.EMISIONES Y FACTOR DE EMISIÓN DE CO2 EQ. DE LA GENERACIÓN_22-05-2023_29-05-2023\n");
	// VALORES DE AJUSTE DEPENDIENTES DE ARCHIVO DE ORIGEN
	fgets(inputArchivo,sizeof(inputArchivo),stdin);
	FILE *dimensionsScout;
	switch (inputArchivo[0])
	{
		case '1':
			filasAntesDatos = 4;
			filasDespuesDatos = 11;
			dimensionsScout = fopen("Archivo1.csv", "r");
			break;
		case '2':
			filasAntesDatos = 4;
			filasDespuesDatos = 11;
			dimensionsScout = fopen("Archivo2.csv", "r");
			break;
		case '3':
			filasAntesDatos = 4;
			filasDespuesDatos = 12;
			dimensionsScout = fopen("Archivo3.csv", "r");
			break;
		default:
			printf("Not one of the options, please restart the program");
			return 0;
	}
	printf("\n\n %i %i \n\n", filasAntesDatos, filasDespuesDatos);
    // variables para iniciar la lectura
    // Aqui se almacena toda la linea, maximo 1024 caracteres (creo que es suficiente)
    int sizeBuffer = 1024;
    char* pruebaDimensiones = (char*)malloc(sizeof(char*)*sizeBuffer);
    // se llama paco xq estuve probando cosas y se ha quedado asi, si vais a probarlo en vuestro pc
    // guardad el csv en la misma carpeta q el archivo de c y meteis aqui el codigo q sea
    // Error por si nos confundimos al escribir el archivo o se mueve o lo que sea
    if (dimensionsScout == NULL)
    {
        printf("Archivo no valido");
        exit(1);
    }
    // Declaración matriz con dimensiones variables por malloc
    int columna;
    for (columna = 0; columna < filasAntesDatos + 1; columna++){
        fgets(pruebaDimensiones, 1024, dimensionsScout);
    }
    int lastWasComma = 0;
    int isCommaInWord = 0;
    int columnNumber = 1;
    int transportVariable = 0;
    // Coge una fila con datos (la 5) y prueba a ver cuantas columnas de datos hay contando las comas
    // Se asume que delante de cada dato hay una coma, sin contar el titulo
    int letra;
    for (letra = 0; pruebaDimensiones[letra] != '\0'; letra++){
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
	int i;
	for (i = 0; pruebaDimensiones[i] != '\0'; i++){
		pruebaDimensiones[i] = '\0';
	}
    }
    if (filasDespuesDatos){
    	rowNumber = rowNumber - filasDespuesDatos;
	}
    fclose(dimensionsScout);
    free(pruebaDimensiones);
    // declaracion de la matriz con malloc
    // inicializamos el vector que va a almacenar los punteros a las filas
    // Esto no le hagais mucho caso, pero está declarando un tensor asiq necesito usar punteros triples
    // Creo un vector que almacena los punteros de cada uno de los vectores fila
    char*** matrizDatos = (char***)malloc(sizeof(char**)*rowNumber);
    printf(" %i %i \n\n", rowNumber, columnNumber);
    int filas = 0;
    for (filas = 0; filas < rowNumber; filas++){
        // para cada uno de los vectores de fila, declaramos otro vector que almacena los punteros
        // de los vectores de cada una de las columnas (o datos individuales es lo mismo)
        matrizDatos[filas] = (char**)malloc(columnNumber*sizeof(char*));
        int columnas = 0;
        for (columnas = 0; columnas < columnNumber; columnas++){
            printf("%i", columnas);
            // para cada una de las columnas, creamos un vector que almacena el numero máximo de caracteres
            matrizDatos[filas][columnas] = (char*)malloc(80*sizeof(char));
            // Esto inicializa cada una de las celdas y les mete un valor para que no estén vacias y pasen cosas feas
            // Solucion temporal mientras arreglo el memory leak
            int arregloGuarro;
	    for (arregloGuarro = 0; arregloGuarro < 80; arregloGuarro++){
	        matrizDatos[filas][columnas][arregloGuarro] = '\0';
	    }
	    printf("%c \n",  matrizDatos[filas][columnas][0]);
            }
        }
    // comprobación de las dimensiones de la matriz
    printf(" %i %i ", rowNumber, columnNumber);

    // < ------------------------------------------- PROCESO DE INSERTADO DE DATOS DEL ARCHIVO EN EL TENSOR DINAMICO matrizDatos ------------------------------------->
    char almacenFila[1024];
    FILE *elementSeparation;
    switch (inputArchivo[0])
	{
		case '1':
			elementSeparation = fopen("Archivo1.csv", "r");
			break;
		case '2':
			elementSeparation = fopen("Archivo2.csv", "r");
			break;
		case '3':
			elementSeparation = fopen("Archivo3.csv", "r");
			break;
	}
    char element[80] = "";
    // Variables pseudobooleanas que sirven para comprobar cositas
    int letraElement = 0;  
    int column = 0 ;
    int filaReal = 0; 
    int fila = 0;
    int floatElement = 0;
    rowNumber += 4;
    int isFirstComma = 1;
    // Se va mirando fila por fila lo que hay y se va almacenando en celdas de la matriz "matrizDatos"
    for (fila = 0; fila < rowNumber; fila++) {
        column = 0;
        // Se almacena el contenido de la fila en almacenFila
        fgets(almacenFila, 2048, elementSeparation);
        printf("%s\n", almacenFila);
        letraElement = 0; 
        letra = 0;
        // Iteramos hasta el final de la linea (hasta que sale \0)
        for (letra = 0; almacenFila[letra] != '\0'; letra++){
            // si hay una doble coma, se considera que estás dentro de un decimal y la coma de dentro no la interpreta
            // como separación de elementos sino como coma decimal
            if (almacenFila[letra] == '"'){
            floatElement = !floatElement;
            continue;
            }
        if (almacenFila[letra] == ','){
            if (!floatElement){
                // Se ejecuta si pilla una coma fuera de un decimal
                if (fila >= filasAntesDatos){
                    element[letraElement] = '\0';
                    // a partir de la fila 5 va almacenando cosas en las celdas
                    filaReal = fila - filasAntesDatos;
                    int a = 0;
                    for (a = 0; element[a] != '\0'; a++){
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
                element[letraElement] = '.';
                letraElement++;
                printf("%s\n", element);
                continue;
                }
            int b = 0;
            for (b = 0; element[b] != '\0'; b++){
                element[b] = '\0';
            }
        }
        if (almacenFila[letra] != ','){
                       // Si no es una coma almacena el digito en element
            // element es un array que sirve como buffer para el contenido de las celdas, cuando se transfiere se vacia
            if (column == 0){
            // Esto es un poco overkill xq no hay tantos acentos pero quiero programar algo que funcione para todos los programas asiq mimimi
	            char fixedChar;
		    switch (almacenFila[letra])
		    {
			case 'á':
				fixedChar = 'a';
				break;
			case 'é':
				fixedChar = 'e';
				break;
			case 'í':
				fixedChar = 'i';
				break;
			case 'ó':
				fixedChar = 'o';
				break;
			case 'ú':
				fixedChar = 'u';
				break;
			case 'Á':
				fixedChar = 'A';
				break;
			case 'É':
				fixedChar = 'E';
				break;
			case 'Í':
				fixedChar = 'I';
				break;
			case 'Ó':
				fixedChar = 'O';
				break;
			case 'Ú':
				fixedChar = 'U';
				break;
			case 'ü':
				fixedChar = 'u';
				break;
			case 'Ü':
				fixedChar = 'U';
				break;
			default:
				fixedChar = almacenFila[letra];
				break;
		}
		element[letraElement] = fixedChar;
	}
		else{
		    element[letraElement] = almacenFila[letra];
		}
		letraElement++;
		printf("%s\n", element);
		}
        }
        element[letraElement - 1] = '\0';
        // Este se ejecuta para el último elemento xq no hay una coma al final de la linea
        if (fila >= filasAntesDatos){
	int c = 0;
        for (c = 0; element[c] != '\0'; c++){
            matrizDatos[filaReal][column][c] = element[c];
            element[c] = '\0';
            }
        printf("%s",matrizDatos[filaReal][column]);
        printf(" %i %i ", filaReal, column);
        printf("\n");
        printf("successful\n\n");
	}
}
// Esta es la comprobación de que los datos se han guardado bien

fclose(dimensionsScout);    
// <---------------- PREPARACIÓN DE LOS DATOS PARA USO ------------------------->
rowNumber -= filasAntesDatos;
int prueba2, prueba = 0;
for (prueba2 = 0; prueba2 < rowNumber; prueba2++){
    for (prueba = 0; prueba < columnNumber; prueba++){
        printf("%s", matrizDatos[prueba2][prueba]);
        printf(" %i %i\n", prueba2,prueba);
    }
printf("\n\n");
}
// Declaramos una estructura donde meteremos punteros a una serie de vectores (ir al principio del archivo para explicación)
struct datosMatriz datosATrabajar;
datosATrabajar.matriz = matrizDatos;
datosATrabajar.numColumnas = columnNumber;
datosATrabajar.numFilas = rowNumber;
// Declaramos los vectores en funcion del tamaño de la tabla con malloc
// El vector vectorColumnaTitulos almacenará los titulos de las diferentes filas en un vector char
datosATrabajar.vectorColumnaTitulos = (char**)malloc(sizeof(char*)*rowNumber);
// El vector vectorColumna se llenará con datos double de la columna puntual con la que trabajemos gracias a la funcion getVectorByNum
datosATrabajar.vectorColumna = (char**)malloc(sizeof(char*)*(rowNumber-1));
int tituloFila = 0;
for (tituloFila = 0; tituloFila < rowNumber; tituloFila++){
    // Declaramos los punteros de memoria para cada array de caracteres, y los llenamos con el titulo de la fila correspondiente
    datosATrabajar.vectorColumnaTitulos[tituloFila] = (char*)malloc(sizeof(char)*80);
    int letra = 0;
    for (letra = 0; letra<80; letra++){
        datosATrabajar.vectorColumnaTitulos[tituloFila][letra] = '\0';
    }
	for (letra = 0; matrizDatos[tituloFila][0][letra] != '\0'; letra++){
        datosATrabajar.vectorColumnaTitulos[tituloFila][letra] = matrizDatos[tituloFila][0][letra];
    }
    printf("\ntitulo: %s\n",datosATrabajar.vectorColumnaTitulos[tituloFila]);
};
// El vector vectorFilaFechas almacenará la fila de fechas en un vector char
datosATrabajar.vectorFilaFechas = (char**)malloc(sizeof(char*)*(columnNumber-1));
datosATrabajar.vectorFila = (char**)malloc(sizeof(char*)*(columnNumber-1));
int fechaColumna = 1;
for (fechaColumna = 1; fechaColumna < columnNumber; fechaColumna++){
    datosATrabajar.vectorFilaFechas[fechaColumna - 1] = (char*)malloc(sizeof(char)*80);
    int letra = 0;
    for (letra = 0; letra < 80; letra++){
        datosATrabajar.vectorFilaFechas[fechaColumna - 1][letra] = '\0';
    }
    for (letra = 0; matrizDatos[0][fechaColumna][letra] != '\0'; letra++){
        datosATrabajar.vectorFilaFechas[fechaColumna - 1][letra] = matrizDatos[0][fechaColumna][letra];
    }
    printf("\nfecha: %s\n",datosATrabajar.vectorFilaFechas[fechaColumna - 1]);
};
// <--------------------- USO DE LOS DATOS ---------------------------->
// EJEMPLO DE COMO USAR EL getVectorByName y la funcion SortVector (ahora mismo solamente funciona para filas)
/*
char inputString[40];
int cosaAAA = 1;
while (cosaAAA){
printf("Enter a string: ");
fgets(inputString, sizeof(inputString), stdin);
double vectorFila[datosATrabajar.numColumnas - 1];
getVectorByName(&datosATrabajar, inputString, vectorFila);
sortVector(&datosATrabajar, vectorFila, '>');	
}
*/    
/* NOTA IMPORTANTE SOBRE EL USO DE LOS VECTORES DE LA MATRIZ:
He cambiado como se sacan los vectores de la matriz para que sea mas sencillo de utilizar
la funcion getVectorByName simplemente tiene el input del vector y la fila/columna que quereis (detecta sola si es una fila o una columna)
lo unico tened cuidado con el tema del vector, la funcion no puede detectar si pone un elemento fuera de un vector, asi que asume que quereis o una fila 
o una columna entera. Si pedis una fila y el vector es mas pequeño que el numero de columnas, va a dar errores
He dejado arriba un ejemplo de cómo se puede implementar el uso de la funcion

*/

// INICIO DEL MENÚ DE OPCIONES
int opcion1 = 0;
int opcion;
int opcion2; 
char inputPeriodSelect[40], inputDataSelect[40], inputOperationSelect[40], inputFuncionalidadSelect[40], inputAnual[40];
int numeroTareas = 5;
char vectorFuncionalidades[5][60] = {"Media","Varianza","Valor maximo y minimo", "Estimaciones futuras","Grafico"};
double* vectorFila;
while(1)
{
	opcion1 = 0;
	opcion2 = 1;
	printf("\n%s\n", inputDataSelect);
	printf("Bienvenido al menú del equip 3232!\n");
	printf("Cómo deseas trabajar con los datos? \n");
	printf("1.Intervalo Mensual 3.Total 4.Dato Exacto 5.Fecha concreta (Escribe el numero)\n");
	fgets(inputPeriodSelect, sizeof(inputPeriodSelect), stdin);
    inputPeriodSelect[strcspn(inputPeriodSelect, "\n")] = '\0';
    char* inputYear[40], inputYearInicio[40], inputYearFinal[40];
    int yearInicio, yearFinal, sizeIntervalo;
	int opcion = inputPeriodSelect[0] - '0';
    switch(opcion){
    	case 1:
    	{
    		char inputYearInicio[40], inputYearFinal[40]; 
			// Intervalo mensual
    		printf("\nIntroduce el mes inicial:\n ");
    		int mes;
    		for (mes = 1; mes < (datosATrabajar.numColumnas - 1); mes++){
				printf("%i. %s ",mes,datosATrabajar.vectorFilaFechas[mes]);
				if ((mes-1)%5 == 0 && (mes-1) ){
					printf("\n");
				}
			}
    		fgets(inputYearInicio, sizeof(inputYearInicio), stdin);
    		inputYearInicio[strcspn(inputYearInicio, "\n")] = '\0';
    		yearInicio = getNumberFromName(&datosATrabajar, inputYearInicio)/29;
    		printf("\nIntroduce el mes final: \n");
    		int mes2;
    		for (mes2 = 1; mes2 < (datosATrabajar.numColumnas - 1); mes2++){
				printf("%i. %s ",mes2,datosATrabajar.vectorFilaFechas[mes2]);
				if ((mes2-1)%5 == 0 && (mes2-1) ){
					printf("\n");
				}
			}
    		printf("\n");
			fgets(inputYearFinal, sizeof(inputYearFinal), stdin);
    		inputYearFinal[strcspn(inputYearFinal, "\n")] = '\0';
			yearFinal = getNumberFromName(&datosATrabajar, inputYearFinal)/29;
			sizeIntervalo = yearFinal - yearInicio + 1;
			printf("\n\n %i \n\n", sizeIntervalo);
			datosATrabajar.longitudIntervalo = sizeIntervalo;
			if (sizeIntervalo <= 1 || !yearFinal || !yearInicio){
				printf("Las fechas no son las correctas\n ");
				continue;
			}
			break;
		}
    	case 3:
    	{
    		//Total
    		sizeIntervalo = datosATrabajar.numColumnas - 1;
    		datosATrabajar.longitudIntervalo = sizeIntervalo;
    		break;
		}
    	case 4:
    	{
    		printf("\nIntroduce la fila deseada: \n");
	    	int tipoElectricidad2;
			for (tipoElectricidad2 = 1; tipoElectricidad2 < datosATrabajar.numFilas; tipoElectricidad2++){
				printf("%i. %s ",tipoElectricidad2,datosATrabajar.vectorColumnaTitulos[tipoElectricidad2]);
				if ((tipoElectricidad2-1)%5 == 0 && (tipoElectricidad2-1) ){
					printf("\n");
				}
			}
			printf("\n");
	    	fgets(inputDataSelect, sizeof(inputDataSelect), stdin);
		    inputDataSelect[strcspn(inputDataSelect, "\n")] = '\0';
    		printf("\nIntroduce the date desired: \n");
			int mes;
    		for (mes = 1; mes < (datosATrabajar.numColumnas - 1); mes++){
				printf("%i. %s ",mes,datosATrabajar.vectorFilaFechas[mes]);
				if ((mes-1)%5 == 0 && (mes-1) ){
					printf("\n");
				}
			}
			printf("\n");
			fgets(inputYearInicio, sizeof(inputYearInicio), stdin);
    		inputYearInicio[strcspn(inputYearInicio, "\n")] = '\0';
    		double validacionExacto = getExactValueFromMatrix(&datosATrabajar,inputDataSelect,inputYearInicio);
    		if (validacionExacto){
				printf("\nOn %s, there were %.6fGWh produced of type %s",inputYearInicio, getExactValueFromMatrix(&datosATrabajar,inputDataSelect,inputYearInicio),inputDataSelect);
				}
			else{
				printf("One of the two parameters is wrong");
			}
			int i;
			for (i = 0; i < 40; i++){
				inputDataSelect[i] = '\0';
				inputYearInicio[i] = '\0';
			}
			continue;
		}
		case 5:{
			printf("\nIntroduce the date desired: ");    		
    		fgets(inputYearInicio, sizeof(inputYearInicio), stdin);
    		inputYearInicio[strcspn(inputYearInicio, "\n")] = '\0';
    		sizeIntervalo = 1;
    		datosATrabajar.longitudIntervalo = datosATrabajar.numFilas-2;
			break;
		}
	}
	// Mete aqui lo que haga falta
	if(sizeIntervalo != 1){
		printf("elige una de las siguientes filas con la que quieras trabajar (Escribe el nombre): (Para volver atras, introduce Exit) \n");
		int tipoElectricidad;
		for (tipoElectricidad = 1; tipoElectricidad < datosATrabajar.numFilas; tipoElectricidad++){
			printf("%i. %s ",tipoElectricidad,datosATrabajar.vectorColumnaTitulos[tipoElectricidad]);
			if ((tipoElectricidad-1)%5 == 0 && (tipoElectricidad-1) ){
				printf("\n");
			}
		}
		printf("\n");
		fgets(inputDataSelect, sizeof(inputDataSelect), stdin);
	    inputDataSelect[strcspn(inputDataSelect, "\n")] = '\0';
		if (inputDataSelect[0] == 'E' && inputDataSelect[1] == 'x' && inputDataSelect[2] == 'i' && inputDataSelect[3] == 't'){
			int i;
			for (i = 0; i < 40; i++){
				inputDataSelect[i] = '\0';
			}
			continue;
		}
		if (sizeIntervalo != datosATrabajar.numColumnas - 1){
		vectorFila = (double*)malloc(sizeof(double)*sizeIntervalo);
		opcion1 = getSpliceOfVector(&datosATrabajar, inputYearInicio, inputYearFinal, inputDataSelect, vectorFila);
		}
		else{
		printf("\nHE HECHO LO QUE DEBERIA\n");
		vectorFila = (double*)malloc(sizeof(double)*(datosATrabajar.numColumnas - 1));
		opcion1 = getVectorByName(&datosATrabajar, inputDataSelect, vectorFila);
		}
		if(!opcion1)
		{
			printf("\n ese tipo de energia no es valido, intenta otra vez");
			int i;
			for (i = 0; i < 40; i++){
				inputDataSelect[i] = '\0';
			}
			continue;
		}
	}
	else{
	vectorFila = (double*)malloc(sizeof(double)*(datosATrabajar.numFilas)); 
	opcion1 = getVectorByName(&datosATrabajar, inputYearInicio, vectorFila);
	if (!opcion1){
		printf("\nEsa fecha no es valida");
		continue;
	}
	}
	while(opcion2)
	{ 
		printf("\n elige una tarea(Escribe el numero): (Para volver atras, escribe Back) \n");
    	int tarea;
		for (tarea = 1; tarea <= numeroTareas; tarea++){
			printf("%i. %s ",tarea,vectorFuncionalidades[tarea-1]);
			if ((tarea-1)%5 == 0 && (tarea-1) ){
				printf("\n");
			}
		};
		if (sizeIntervalo != 1){
			printf("%i. Ordenar vector", numeroTareas + 1);
		}
		printf("\n");
		fgets(inputFuncionalidadSelect, sizeof(inputFuncionalidadSelect), stdin);
    	inputFuncionalidadSelect[strcspn(inputFuncionalidadSelect, "\n")] = '\0';
    	if (inputFuncionalidadSelect[0] == 'B' && inputFuncionalidadSelect[1] == 'a' && inputFuncionalidadSelect[2] == 'c' && inputFuncionalidadSelect[3] == 'k'){
		int i;
		for (i = 0; i < 40; i++){
			inputDataSelect[i] = '\0';
			inputFuncionalidadSelect[i] = '\0';
		}
		break;
		}
    	int opcion2 = inputFuncionalidadSelect[0] - '0';
		if(opcion2> numeroTareas|| opcion2<1)
    	{
	    	printf("\n Esta opcion no es valida, por favor vuelve a intentarlo");
	    	continue;
		}
		else{
		  		switch(opcion2)
	    		{
	   	        	case 1:
	    	    	{
	    	    		// MEDIA
	            		printf("la media es : %f\n",media(&datosATrabajar, vectorFila));
	       				break;
	        		}
          			case 2:
         	   		{
         	   			// Varianza
         	   			  printf("la varianza es: %f",varianza(&datosATrabajar, vectorFila));
          	    	  break;
          			}
          			case 3:
          			{
          				// energia total
          	    		printf("la energia total acumulada es : %f\n",engtot(&datosATrabajar,vectorFila));
           		  		break;
		   			}
		   			case 4:
	    	    	{
	    	    			// recta de regresion
	    	    		regresion(&datosATrabajar,vectorFila);
	       				break;
	        		}
	    	    	case 5:
	    			{
	    				// GRAFICO
	     	    		grafica(&datosATrabajar,vectorFila);
						break;
	         		}
	         		case 6:
	    			{
	    				if (datosATrabajar.longitudIntervalo == 1){
	    					printf("Choose another option\n");				 
							continue;
						}
	    				sortVector(&datosATrabajar, vectorFila, '>');
	     	   			break;
	         		}
	         		default:
	         		{	
					printf("Choose another option\n");				 
					continue;
					}
						 
    	    	}
		}
	break;
	}
printf("\n LIMPIO STRING \n");
int i;
for (i = 0; i < 40; i++){
			inputDataSelect[i] = '\0';
			inputOperationSelect[i] = '\0';
			inputFuncionalidadSelect[i] = '\0';
			inputPeriodSelect[i] = '\0';
			inputAnual[i] = '\0';
			inputYearInicio[i] = '\0';
			inputYearFinal[i] = '\0';
		}
free(vectorFila);
}
return 0;
}
// <---------------------------------------- FIN DEL ARCHIVO MAIN ---------------------------------------------------->
float media(struct datosMatriz *datosATrabajar, double* Vector)//funcion calculo de una media
{
  int i;/*valor unico*/
  float j = Vector[0], resultado;/*sumatorio de los valores*/
  for(i=0; i<datosATrabajar->longitudIntervalo ; i++)
  {
	j=j+Vector[i];
  }
  resultado =(float)(j)/(float)(datosATrabajar->longitudIntervalo);/*n es el tamaño del vector , osea , el numero de valores, se divide entre el sumatorio para obtener resultado , oesa la media*/
  return resultado;
}

float varianza(struct datosMatriz *datosATrabajar, double* Vector)
{
  double* vectorFila;
  int i;
  float resultado , sum=0;
  for(i=0 ; i<datosATrabajar->longitudIntervalo ; i++)
  {
    sum = sum + ((Vector[i]-media(datosATrabajar, Vector)) * (Vector[i]-media(datosATrabajar, Vector)));//sumatorio del valor menos la media al cuadrado
  }
  resultado = sum / datosATrabajar->longitudIntervalo;//se divide lo anterior para conseguir resultado osea la varianza desesada
  return resultado;
}


float engtot(struct datosMatriz *datosATrabajar,double* Vector) //energia total generada a lo largo del tiempo
{
  int i;
  float resultado = Vector[0];
  for(i=1 ; i<datosATrabajar->longitudIntervalo ; i++)
  {
    resultado = resultado +  Vector[i]; //simplemente un sumatorio de la energia para encontrar la energia total
  }
  return resultado;
}

void regresion(struct datosMatriz *datosATrabajar, double* Vector)//calcula la recta de regresion de una fila de datos usando la media la varianza y la covarianza(hay que hacer la covarianza aun) para usando esa recta hacer una estimacion de lo que podria ser un valor futuro
{//en regresion hay que introducir tres datos , el primer vector (y) es el valor energético , el segundo vector son los dias o fechas en los que ocurren esos valores , las fechas se hacen como numeros enteros para facilitar los calculos .
  double vectorFecha[datosATrabajar->longitudIntervalo] ;
  int r=0;
  for(r=0; r<datosATrabajar->longitudIntervalo; r++)
  {
  	vectorFecha[r]=r+1; //aqui se crea el vector de la fecha , cada nuevo valor de r corresponde a un mes , se numera los meses (mas 1 , 2 , ...) para facilitar los calculos , mas tarde se usa en otros calculos asique por conveniencia evitamos el valor 0 ya que no se puede dividir por cero
  }
  float b, x;
  //aqui calculo la covarianza poruque por ahora solo la usamos en esta funcion y es complicado hacerlo con una funcion ya que tiene dos vectores, aqui uno de esos vectores no es variable asique es mas facil
  int i;
  float covarianza , sum=0;//la covarianza no tiene funcion porque solo se usa aqui , porloque hacemos el calculo de la covarianza para obtener la recta de regresion
  for(i=0 ; i<datosATrabajar->longitudIntervalo ; i++)
  {
    sum = sum + ((Vector[i]-media(datosATrabajar, Vector)) * (vectorFecha[i]-media1(vectorFecha)));
  }
  covarianza = sum / datosATrabajar->longitudIntervalo; 
  
  b = (covarianza)/(varianza1(vectorFecha)); 
  printf("La recta de regresion tiene la forma : y= %f + %f * (x-%f) , ahora , dame un numero entero positivo , ese numero representara la cantidad de meses despues del ultimo mes registrado y hara una estimacion para ese mes. Pero cuanto mayor sea el numero , mayor sera el error\n", media(datosATrabajar, Vector), b, media1(vectorFecha));
  int num_meses;
  scanf("%i",&num_meses);
  float error ,estimacion;
  
  estimacion = media(datosATrabajar, Vector) + b * (((datosATrabajar->longitudIntervalo)+num_meses)-media(datosATrabajar, vectorFecha));  
  error = covarianza / (varianza(datosATrabajar, Vector) * varianza1(vectorFecha));
  printf("Podemos hacer una estimacion para los primeros meses despues de los medidos: despues de %i meses , estimamos:%f . El coeficiente de correlacion lineal (precision) de estos datos es: %f \n",num_meses, estimacion, error);
}

float media1(double* Vector) //esto es igual que la funcion media pero con un vector cualquiera, es decir un vector del cual no conocemos el tamaño (por lo que tenemos que calcular este)
{
  int tamanio;
  tamanio = sizeof(Vector) / sizeof(Vector[0]);
  int i;/*valor unico*/
  float j = Vector[0], resultado;/*sumatorio de los valores*/
  for(i=0; i<tamanio ; i++)
  {
	j=j+Vector[i];
  }
  resultado =(float)(j)/(float)(tamanio);/*n es el tamaño del vector , osea , el numero de valores*/
  return resultado;
}

float varianza1(double* Vector)//varianza1 tiene la misma diferencia con varianza que la funcion media1 con media
{
  int tamanio;
  tamanio = sizeof(Vector) / sizeof(Vector[0]);
  int i;
  float resultado , sum=0;
  for(i=0 ; i<tamanio ; i++)
  {
    sum = sum + ((Vector[i]-media1(Vector)) * (Vector[i]-media1(Vector)));
  }
  resultado = sum / tamanio;
  return resultado;
}

void grafica(struct datosMatriz *datosATrabajar, double* Vector){//funcion para expresar de forma gráfica los resultados numéricos
	int i, longitud;
	longitud = sizeof(Vector) / sizeof (Vector[0]);
	for (i=0; i<datosATrabajar->longitudIntervalo; i++){
		int nveces=Vector[i]/100; //de esta forma hacemos que cada '-', que es de lo que esta formada la grafica represente 100 unidades
		int j;
		for(j=0; j<nveces; j++){ //bucle para imprimir la grafica
			printf("-");
			if(j==(nveces-1)){//cuando el vector se acaba hay que añadir un \0
				printf("\n");
			}
		}
	}
}

void imprimirVectorEnArchivo(struct datosMatriz *datosATrabajar, double* Vector, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
	    //en caso de que el archivo no se pueda abrir informará del error
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    fprintf(archivo, "El vector es: ");
    int i;
    int longitud = sizeof(Vector) / sizeof (Vector[0]);
    for (i = 0; i < datosATrabajar->longitudIntervalo; i++) {
	    //recorre el vector
        fprintf(archivo, "%d ", Vector[i]);
	    //lo imprime en el archivo
    }
    fprintf(archivo, "\n");
    
    fclose(archivo);
//cerramos el archivo
    printf("\nEl vector se ha escrito correctamente en el archivo.\n");
	//informamos que se ha impreso correctamente el vector
}
