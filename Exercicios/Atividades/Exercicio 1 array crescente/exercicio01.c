//
//--- Array de 5 elemntos em ordem crescente ---
//
//Data: 04/09/2020  Perido:2020.3 
//
//Nome: Alysson Hyago Pereira de Oliveira   Mat:119210495 



#include <stdio.h>

int main()
{
    
    int array[5];  // criando o array de 5 elementos
    int comp;   // vari�vel ordena��o 
    int y;  //vari�vel de compara��o
        
    
    for(int i =0 ; i<5; i++)    //lendo e armazenando os 5 elementos
    {
        printf("Digite os 5 elementos inteiros: "); 
        scanf("%d",&array[i]);
    }
    
    
    for(int i =0 ; i<5; i++)    //bloco de compara��o
    {
        for( y=i+1;y<5;y++)
        {
            if(array[i]>array[y])
            {
                comp=array[i];
                array[i]=array[y];
                array[y]=comp;
            }
        }
    }
    
    
    for(int i =0 ; i<5; i++)    //exibindo os valores em ordem crescente
    {
        printf("endere�o[%d]: %d\n",i,array[i]);
    }
    return 0;
}
