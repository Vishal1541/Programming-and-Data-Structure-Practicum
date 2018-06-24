#include<stdio.h>
#include<math.h>
#define GOLDEN_RATIO (1+sqrt(5))/2
int fibonacci(int n){
	if(n==0) return 0;
	else if(n==1) return 1;
	else return (fibonacci(n-1) + fibonacci(n-2));
}
int main(){
	int n,fibo_by_defination;
	float fibo_by_formula,error;
	printf("Enter the term for which the fibonacci has to be found:\n");
	scanf("%d",&n);
	fibo_by_defination = fibonacci(n);
	fibo_by_formula = ( pow(GOLDEN_RATIO,n)-pow(-GOLDEN_RATIO,-n) )/sqrt(5);
	error = fabsf(fibo_by_defination - fibo_by_formula);
	printf("Fibonacci for term %d by using:\n",n);
	printf("1. The defination is %d\n",fibo_by_defination);
	printf("2. The formula is %f\n",fibo_by_formula);
	printf("with an error of %f\n",error);
	return 0;
}
