#include <stdio.h>
#include <stdlib.h>

void sorting_function(int *arr,int arr_len) 
{ 
        int j, step;
        for(step = arr_len/2; step > 0; step = step/2)
		{
                for (int i = step; i < arr_len; i++)
			{
                        int t = arr[i];
                        for ( j= i; j >= step; j = j - step)
				{
                                if (t < arr[j - step])
					arr[j] = arr[j - step];
                                else break;
                        	}
                        arr[j] = t;
                }
        }
}

int main()
{
	int n, i;
	scanf("%d", &n);
	int arr[n];
	for(i = 0; i < n; i++) { scanf("%d",&arr[i]); }

sorting_function(arr, n);

for (i = 0; i < n; i++) { printf("%d ", arr[i]); }
printf("\n");
return 0;
}
