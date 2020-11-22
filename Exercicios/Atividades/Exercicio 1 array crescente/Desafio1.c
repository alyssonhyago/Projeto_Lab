//
//--- Array de N elemntos em ordem crescente ---
//
//Data: 04/09/2020  Perido:2020.3 
//
//Nome: Alysson Hyago Pereira de Oliveira   Mat:119210495 

// .h prototipo da fun��o 
// .c instru��es da fun��o
// arquivos locais #include ""


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 10000	// numero de elementos

// --- Prot�tipo ---
void ordena(int [n]);

int main()
{
 	  
    int x = 0;
    int array[n]; // array de elementos 
   // int comp;   // vari�vel ordena��o 
    //int y;  //vari�vel de compara��o
    int i;    
 	float tempo; // variavel para armazenar o tempo de execu��o 
 	
	time_t t_ini, t_fim; 
 	
 	srand(time(NULL)); // fun��o para gerais numeros aleatorios diferentes 
        
    t_ini = time(NULL);  
	  
//	--- La�o de condi��o para os 10 grupos de arrays ---
    while(x < 10)
	{
    	
		for( i =0 ; i<n; i++)    //lendo e armazenando os  elementos
    	{
    		
    		array[i] = rand()%100;
    		
    	}
    
    	ordena(array);
    
    	for( i =0 ; i<n; i++)    //exibindo os valores em ordem crescente
    	{
        	
			printf("endere�o[%d]: %d\n",i,array[i]);
    	
		}
 	   	
		t_fim = time(NULL);
    
    
		tempo = difftime(t_fim, t_ini); // valor do tempo de execu��o 
    
		printf("Tempo : %f", tempo);
		
     x++;
	}
    return 0;
}

// --- Fun��o de ordena��o ---
void ordena(int array[n])
{
	int i,j,aux;
	for(i = 0; i<n; i++)
	{
		for(j = i; j<n; j++)
		{
			if(array[i]>array[j])
			{
				aux = array[i];
				array[i] = array[j];
				array[j] = aux;
            
			}
			
		}
	}
}
	
	