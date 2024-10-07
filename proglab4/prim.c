#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	int i;
	int j;
	for (i=0;i<n;i++) {
	for (j=0;j<n;j++) {
		printf("%5d", i*n+j+1);
	}
	printf("\n");
	}
	}
