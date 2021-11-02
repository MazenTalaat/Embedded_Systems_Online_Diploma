/*
 * ex2.c
 *
 *  Created on: Nov 02, 2021
 *      Author: Mazen Talaat
 */

#include "stdio.h"

int main(){
	char arr[26];
	char *p;
	int i,j=0;
	for(i=65; i<91; i++){
		arr[j]=i;
		j++;
	}
	p = arr;
	for(i=0; i<26; i++){
		printf("%c	", *p);
		p++;
	}
	return 0;
}
