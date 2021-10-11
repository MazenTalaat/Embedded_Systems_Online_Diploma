/*
 * ex3.c
 *
 *  Created on: Oct 11, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

struct Scomplex
{
	float m_real;
	float m_img;
} gx, gy, gsum;

struct Scomplex read_data();
struct Scomplex add_complex(struct Scomplex, struct Scomplex);

int main(){
	printf("\nFor 1st complex number\n");
	gx = read_data();
	printf("\nFor 2nd complex number\n");
	gy = read_data();
	gsum = add_complex(gx, gy);
	printf("Sum=%.1f+%.1fi\n", gsum.m_real, gsum.m_img);
	return 0;
}

struct Scomplex read_data(){
	struct Scomplex x;
	printf("Enter real and imaginary respectively: ");
	scanf("%f\n%f", &x.m_real, &x.m_img);
	return x;
}

struct Scomplex add_complex(struct Scomplex n1, struct Scomplex n2){
	struct Scomplex sum;
	sum.m_real = n1.m_real + n2.m_real;
	sum.m_img = n1.m_img + n2.m_img;
	return sum;
}
