#include <stdio.h>

int main (void)
{
	int i, a;
	unsigned int n;
	long long b;
	b=0;
	scanf ("%u", &n);
	for (i=0; i<n; i++)
	{
		scanf ("%d", &a);
		b = a+b;
	}
	printf ("%lli", b);
	return 0;
}
