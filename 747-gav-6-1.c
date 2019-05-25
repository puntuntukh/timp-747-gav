#include <stdio.h>
#include <stdlib.h>

int sorting_function (int *arr, int arr_len) 
{
	int step;
	double fakt = 1.2473309;
	step = arr_len;	
	while (step > 1)
	{	
		step = step/fakt;
		int swap = 0;
		for (int i = 0; i + step < arr_len; ++i)
			if (arr[i + step] < arr[i])
			{
				int t = arr[i];
				arr[i] = arr[i + step];
				arr[i + step] = t;
				swap = 1;
			}			
		
	}

}	

int main()
{
	int n, i;
	scanf("%d", &n);
	int arr[n];
	for(i = 0; i < n; i++) { scanf("%d", &arr[i]); }

sorting_function(arr, n); 

for (i = 0; i < n; i++) { printf("%d ", arr[i]); }
printf("\n");
return 0;
}
