%option noyywrap
%{
	/*
		Running 
		1. $ lex 190101070.l
		2. $ gcc lex.yy.c
		3. $ ./a.out
	*/
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdbool.h>
	#define TWO 2
	#define ONE TWO/TWO
	#define ZERO TWO - TWO
	#define SIZE ONE * TWO * 50
	int lval, line = 1, col = 1, idx = 0,idx2=0;
	struct Data {
	   char* data;   
	   int let_num;
	   int block_num;
	};
	int new_num = ZERO;
	struct Data arr[SIZE];
	struct Data numarr[SIZE];
	int install_id();
	int install_num();
%}

delim [ \t]
ws {delim}+
letter [A-Za-z]
digit [0-9]
id {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

{ws} {/* no action and no return */}
\n {line++;}
EOF {return 0;}
PROGRAM {lval=1; return(1);}
VAR {lval++; return(2);}
BEGIN {lval++; return(3);}
END {lval++; return(4);}
"END." {lval++; return(5);}
INTEGER  {lval++; return(lval);}
FOR {lval++; return(lval);}
READ {lval++; return(lval);}
WRITE {lval++; return(lval);}
TO {lval++; return(lval);}
DO {lval++; return(lval);}
";" {lval++; return(lval);}
":" {lval++; return(lval);}
"," {lval++; return(lval);}
":=" {lval++; return(lval);}
"+" {lval++; return(lval);}
"-" {lval++; return(lval);}
"*" {lval++; return(lval);}
DIV {lval++; return(lval);}
"(" {lval++; return(lval);}
")" {lval++; return(lval);}
id {lval++; return(lval);}
int {lval++; return(lval);}
{id} {lval = (int) install_id(); return(22);}
{number} {lval = (int) install_num(); return(23);}
%%

/* int findIndex(char *x,int len){
	int temp = 0;
	for(int i=0;i<len;i++){
		temp+=x[i];
	}
	return temp%SIZE;
} */

int install_id(){
	int key = idx;
	if(arr[key].data == NULL){
		arr[key].data = yytext;
	}else{
		printf("Conflict\n");
	}
	idx++;
	return key;
}

int install_num(){
	int key = idx2;
	if(numarr[key].data == NULL){
		numarr[key].data = yytext;
	}else{
		printf("Conflict\n");
	}
	idx2++;
	return key;
}


int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		FILE *file = fopen(argv[1], "r");
		if(file)
			yyin = file;
	}
	{
		printf("%-10s %-10s %-20s\n","LINE NO","TOKEN NO","TOKEN SPECIFIER");
	}
	int i, prevline =0;
	while((i=yylex()) != 0)
	{
		int num = 0;
		if(line != prevline){
			num = line;
			prevline = line;
		}
		switch(i)
		{
			case 22:
				{
					if(num == 0) {
						printf("%-10s %-10d ^%-20s\n","",i,arr[lval].data);
					} else {
						printf("%-10d %-10d ^%-20s\n",num,i,arr[lval].data);
					}
					break;
				}
			case 23:
				{
					if(num == 0) {
						printf("%-10s %-10d #%-20s\n","",i,numarr[lval].data);
					} else {
					printf("%-10d %-10d #%-20s\n",num,i,numarr[lval].data); 
					}
					break;
				}
			default:
				{
					if(num == 0) {
						printf("%-10s %-10d\n","",i);
					} else {printf("%-10d %-10d\n",num,i);}
					break;
				}
		}
	}
	return 1;
}