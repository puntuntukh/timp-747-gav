#include <stdio.h>
#include <stdlib.h>

void sorting_function (int *arr, int first, int last)
{
	if (first<last){int l = first, r = last-1;
	int opor = arr[(l + last) / 2]; 
	while (l <= r)
	{
		while (arr[l] < opor)
			l++;
		while (arr[r] > opor)
			r--;
		if (l <= r){
			int t = arr[l];
			arr[l] = arr[r];
			arr[r] = t;
			l++;
			r--;}
	}
	/*if (r < first)*/
		sorting_function (arr, first, r+1);
	/*if (l > last)*/
		sorting_function (arr, l, last);
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

	sorting_function(arr, 0, n);

	for (int i = 0; i < n; i++)
	{
		printf("%d ", (arr[i]));
	}
	printf("\n");
}
