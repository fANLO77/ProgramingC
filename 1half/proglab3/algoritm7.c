#include<stdio.h>

int main() {

	int a;
	scanf("%d", &a);
	int n = 2;
	int flag = 0;
	while (a%n!=0){
		n++;
		if (n==a){
			flag = 1;
			break;
}
}
	printf("%d\n", n);
	printf("%d\n", flag);

}
// выводит самый маленький делитель и говорит составное или простое число
