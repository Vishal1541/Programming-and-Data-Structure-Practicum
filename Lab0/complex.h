#include<stdio.h>
#include<math.h>
#define PI 3.14159
typedef struct c{
	float real;
	float img;
}complex;
complex complexSum(complex a, complex b){
	complex c;
	c.real = a.real+b.real;
	c.img = a.img+b.img;
	return c;
}
complex complexMultiply(complex a, complex b){
	complex c;
	c.real = a.real*b.real - a.img*b.img;
	c.img = a.img*b.real+b.img*a.real;
	return c;
}
complex conjugate(complex a){
	complex c;
	c.real = a.real;
	c.img = -a.img;
	return c;
}
void rectToPolar(complex c, float *mod, float *arg){
	float x=c.real;
	float y=c.img;
	*mod = sqrt(x*x+y*y);
	*arg = atanf(y/x);
	*arg*= 180/PI;
	if(x<0 && y<0)
		*arg-=180;
	else if(x<0 && y>0)
		*arg+=180;
}
void polarToRect(float mod, float arg, complex *c){
	c->real = mod*cos(arg*PI/180);
	c->img = mod*sin(arg*PI/180);
}
