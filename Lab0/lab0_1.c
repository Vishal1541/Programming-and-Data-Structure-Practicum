#include<stdio.h>
#include<math.h>
#include"complex.h"
#define PI 3.14159

int main(){
	printf("Select the serial no of the operation to be performed on complex no:\n");
	printf("1. Summation\n");
	printf("2. Multiplication\n");
	printf("3. Rectangular to Polar\n");
	printf("4. Polar to rectangular\n");
	printf("5. Conjugate\n");
	int serialNo;
	scanf("%d",&serialNo);
	while(!(serialNo>0 && serialNo<6)){
		printf("Invalid Serial No!\n");
		scanf("%d",&serialNo);
	}
	float mod,arg;
	if(serialNo==1 || serialNo==2){
		printf("Enter the no of complex no on which the operation is to be performed:\n");
		int n,type;
		scanf("%d",&n);
		while(n<=0){
			printf("No cannot be less than or equal to 0.\n");
			scanf("%d",&n);
		}
		printf("Enter 1 for giving input in Rect form or 2 for Polar form:\n");
		scanf("%d",&type);
		complex ans,input_complex;
		ans.real=0;
		ans.img=0;
		int count=0;
		if(type==1){
			int i;
			for(i=1;i<=n;i++){
				printf("Enter real and img part of Complex No %d\n",i);
				scanf("%f%f",&input_complex.real,&input_complex.img);
				if(serialNo==1)
					ans=complexSum(ans,input_complex);
				else{
					if(count==0){
						ans.real=1;
						count=1;
					}
					ans=complexMultiply(ans,input_complex);
				}
			}
			rectToPolar(ans,&mod,&arg);
			printf("Answer is %.2f + %.2fi or %.2f angle %.2f degrees\n",ans.real,ans.img,mod,arg);
		}
		else{
			int i;
			for(i=1;i<=n;i++){
				printf("Enter modulous and argument in degrees of Complex No %d\n",i);
				scanf("%f%f",&mod,&arg);
				polarToRect(mod,arg,&input_complex);	
				if(serialNo==1)
					ans=complexSum(ans,input_complex);
				else{
					if(count==0){
						ans.real=1;
						count=1;
					}
					ans=complexMultiply(ans,input_complex);
				}
			}
			rectToPolar(ans,&mod,&arg);
			printf("Answer is %.2f + %.2fi or %.2f angle %.2f degrees\n",ans.real,ans.img,mod,arg);
		}
	}
	else if(serialNo==3){
		complex c;
		printf("Enter the real part of the complex no:\n");
		scanf("%f",&c.real);
		printf("Enter the img part of the complex no:\n");
		scanf("%f",&c.img);
		rectToPolar(c,&mod,&arg);
		printf("The polar form is %.2f angles %.2f degrees.\n",mod,arg);
	}
	else if(serialNo==4){
		complex c;
		printf("Enter the mod of the complex no:\n");
		scanf("%f",&mod);
		printf("Enter the arg of the complex no:\n");
		scanf("%f",&arg);
		polarToRect(mod,arg,&c);
		printf("The rect form is %.2f + %.2fi.\n",c.real,c.img);
	}
	else{
		int n;
		complex c,c_conjugate;
		printf("Enter 1 for giving input in Rect form or 2 for Polar form:\n");
		scanf("%d",&n);
		if(n==1){
			printf("Enter real and img part:\n");
			scanf("%f%f",&c.real,&c.img);
			c_conjugate = conjugate(c);
			rectToPolar(c_conjugate,&mod,&arg);
			printf("The conjugate is %.2f + %.2fi or %.2f angles %.2f degree.\n",c_conjugate.real,c_conjugate.img,mod,arg);
		}
		else{
			printf("Enter mod and arg:\n");
			scanf("%f%f",&mod,&arg);
			polarToRect(mod,arg,&c);
			c_conjugate = conjugate(c);
			rectToPolar(c_conjugate,&mod,&arg);
			printf("The conjugate is %.2f + %.2fi or %.2f angles %.2f degree.\n",c_conjugate.real,c_conjugate.img,mod,arg);
		}
	}
	return 0;
}
