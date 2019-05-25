#include <stdio.h>
#include <math.h>

int main (void)
{
	int i, a;
	unsigned int n;
	long long b;
	b=0;
	scanf ("%d", &n);
	for (i=0; i<n; i++)
	{
		scanf("%d", &a);
		b= b+ (a*a);

	}
	printf ("%lli", b);
	return 0;

}
