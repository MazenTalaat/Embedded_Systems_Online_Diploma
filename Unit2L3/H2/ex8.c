/*
 * ex8.c
 *
 *  Created on: Sep 17, 2021
 *      Author: Mazen Talaat
 */


#include "stdio.h"

int main()
{
	char c;
	float ans, x1, x2;
	printf("Enter operator either + or - or * or / : ");
	fflush(stdout); fflush(stdin);
	scanf("%c", &c);
	printf("Enter two operands: ");
	fflush(stdout); fflush(stdin);
	scanf("%f\n%f", &x1, &x2);
	switch(c)
	{
	case '+':
		ans = x1 + x2;
		printf("%.1f + %.1f = %.1f", x1, x2, ans);
		break;
	case '-':
			ans = x1 - x2;
			printf("%.1f - %.1f = %.1f", x1, x2, ans);
			break;
	case '*':
			ans = x1 * x2;
			printf("%1.f * %.1f = %.1f", x1, x2, ans);
			break;
	case '/':
			ans = x1 / x2;
			printf("%.1f / %.1f = %.1f", x1, x2, ans);
			break;
	default:
		printf("Error");
	}
	return 0;
}
