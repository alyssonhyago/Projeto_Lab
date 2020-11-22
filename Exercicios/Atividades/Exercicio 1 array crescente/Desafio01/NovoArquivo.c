// --- Função de ordenação ---

#define n 10000	

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
	