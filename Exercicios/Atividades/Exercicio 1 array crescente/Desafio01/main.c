//
//--- Array de N elemntos em ordem crescente ---
//
//Data: 08/09/2020  Perido:2020.3 
//
//Nome: Alysson Hyago Pereira de Oliveira   Mat:119210495 




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 10000	// numero de elementos


int main()
{
	
    int x = 0;
    int array[n]; // array de elementos 
    int i;    
 	float tempo; // variavel para armazenar o tempo de execução 
 	
	time_t t_ini, t_fim; 
 	
 	srand(time(NULL)); // função para gerais numeros aleatorios diferentes 
        
    t_ini = time(NULL);  
	  
//	--- Laço de condição para os 10 grupos de arrays ---
    while(x < 10)
	{
    	
		for( i =0 ; i<n; i++)    //lendo e armazenando os  elementos
    	{
    		
    		array[i] = rand()%100;
    		
    	}
    
    	ordena(array);
    
    	for( i =0 ; i<n; i++)    //exibindo os valores em ordem crescente
    	{
        	
			printf("endereço[%d]: %d\n",i,array[i]);
    	
		}
 	   	
		t_fim = time(NULL);
    
		
     x++;
	}
	tempo = difftime(t_fim, t_ini); // valor do tempo de execução 
    
		printf("Tempo : %f", tempo);
    return 0;
}
