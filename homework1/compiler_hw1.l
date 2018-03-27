/* Definition section */
%{
	#include <stdio.h>
	#include <stdlib.h>

	/* Symbol table function */
	void create_symbol();
	void insert_symbol();
	int lookup_symbol();
	void dump_symbol();
	int linecount=0;
	int varflag=0;/*要開始宣告*/
	char * nowid = NULL;	
%}

/* Define regular expression label */

letter [a-zA-Z]
digit [0-9]
id {letter}+({letter}|{digit})*
floatdigit [0-9]+"."[0-9]+
number {digit}+|{floatdigit}
ignore [\t\r\s]+|" "
/* Rules section */
%%

{ignore}	{;}
{number} {printf("%s \t Number\n",yytext);}

"//".*	{printf("%s \t C++ Comment \n",yytext);}

"var"     {varflag = 1 ;}
"int"     {
		if(varflag==1){
		printf("%s \t int TYPE VAR\n",nowid);
		}	
		varflag=0;free(nowid);
	}
"float32"     { printf("%s \t RCB \n", yytext); }
"print"     { printf("%s \t print function \n", yytext); }
"println"     { printf("%s \t println function \n", yytext); }
"if"     { printf("%s \t if function \n", yytext); }
"else"     { printf("%s \t else function  \n", yytext); }
"for"     { printf("%s \t for function  \n", yytext); }

"+" 	{ printf("%s \t Add \n", yytext); }
"-"		{ printf("%s \t Sub \n", yytext); }
{id}	{
	nowid = malloc(strlen(yytext)+1);
	strcpy(nowid,yytext);
	}
\n	{linecount++; varflag = 0;nowid=NULL;}

"("     { printf("%s \t LB \n", yytext); }
")"     { printf("%s \t RB \n", yytext); }
"{"     { printf("%s \t LCB \n", yytext); }
"}"     { printf("%s \t RCB \n", yytext); }
"\""     { printf("%s \t quotation \n", yytext); }

"*"     { printf("%s \t Multiply \n", yytext); }
"/"     { printf("%s \t Divide \n", yytext); }
"%"     { printf("%s \t Modulo \n", yytext); }
"++"     { printf("%s \t increment \n", yytext); }
"--"     { printf("%s \t decrement \n", yytext); }
"<"     { printf("%s \t Less than \n", yytext); }
">"     { printf("%s \t Greater than \n", yytext); }
"<="     { printf("%s \t Less-than or equals \n", yytext); }
">="     { printf("%s \t Greater-than or equals \n", yytext); }
"=="     { printf("%s \t Equals \n", yytext); }
"!="     { printf("%s \t Not equal to \n", yytext); }
"="     { printf("%s \t Assign \n", yytext); }
"+="     { printf("%s \t Plus and assign \n", yytext); }
"-="     { printf("%s \t Sub and assign \n", yytext); }
"*="     { printf("%s \t Multiply and assign \n", yytext); }
"/="     { printf("%s \t Divide and assign \n", yytext); }
"%="     { printf("%s \t Modulo and assign \n", yytext); }
"&&"     { printf("%s \t Logic and \n", yytext); }
"||"     { printf("%s \t Logic or \n", yytext); }
"!"     { printf("%s \t Not \n", yytext); }


%%

/*	C Code section */
int yywrap(void)
{
    return 1;
}

void create_symbol() {;}
void insert_symbol() {;}
int lookup_symbol() {;}
void dump_symbol() {;}

int main(int argc,char *argv[])
{
//	nowid = malloc(200);//存id的地方
	yyin = fopen(argv[1],"r");
	yylex();

	dump_symbol();
	printf("Parse over, the line number is %d\n",linecount);
	return 0;
}
