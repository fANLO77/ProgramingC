#include<stdio.h>

int main() {

	int a;
	scanf("%d", &a);
	int s=0;
	int n;
	for (n=2;n<a;n++){
		if (a%n==0){
			s=1;
			break;
}
}
	if (s==0){
		printf("1\n");
}
	else {
		printf("0\n");
}
}
// простое или составное число
