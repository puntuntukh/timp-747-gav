#include <stdio.h>
#include <stdlib.h>

//Просеивание элементов
void siftDown(int *arr, int root, int bottom)
{
 	int max;
	
 	while (root * 2 <= bottom)
	{
		if ((root * 2 == bottom) || (arr[root * 2] > arr[root * 2 + 1]))
		{
			max = root * 2;
		}
		else
		{
			max = root * 2 + 1;
		}
		if (arr[root] < arr[max]) 
		{ 
			int t = arr[root]; 
			arr[root] = arr[max];
			arr[max] = t;
			root = max;
		}
		else break;
	}
}

//Пиромидальная сортировка
void sorting_function(int *arr, int arr_len)
{
	for (int i = (arr_len / 2) - 1; i >= 0; i--)
		siftDown(arr, i, arr_len - 1);
	for (int i = arr_len - 1; i >= 1; i--)
	{
    		int t = arr[0];
    		arr[0] = arr[i];
    		arr[i] = t;
    		siftDown(arr, 0, i - 1);
	}
}

int main()
{
	int n;	
	scanf("%d", &n);
	int arr[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	sorting_function(arr, n);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
