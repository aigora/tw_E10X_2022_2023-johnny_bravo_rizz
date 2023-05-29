#include<stdio.h>
void grafica(int vector[], int longitud);

int main(){
	 int vector1[24]={4057.346783,4517.602492,3715.416012,2745.019022,2159.483245,2182.252545,2209.4646239999997,1883.2608030000001,1396.698883,1023.215446,1199.445532,2536.803672,2085.857451,1174.9701699999998,1764.806206,1782.053848,1922.3023759999999,1190.985484,1043.519078,972.977692,1153.775681,717.70239,1309.281418,2744.808065};
	 int longitud= sizeof(vector1)/sizeof(vector1[0]);
	 grafica(vector1, longitud);
	 
}

void grafica(int vector[], int longitud){
	int i;
	for (i=0; i<longitud; i++){
		int nveces=vector[i]/100;
		int j;
		for(j=0; j<nveces; j++){
			printf("-");
			if(j==(nveces-1)){
				printf("\n");
			}
		}
		
	}
	
}
