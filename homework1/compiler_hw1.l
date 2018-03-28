/* Definition section */
%{
	#include <stdio.h>
	#include <stdlib.h>
	#define TableSize 100
	/* Symbol table function */
	void create_symbol();
	void insert_symbol(char*,int);
	int lookup_symbol(char*);
	void dump_symbol();
	int linecount=0;
	int varflag=0;/*要開始宣告*/
	char * nowid = NULL;
	
	typedef struct symbol_table{
	char* id;
	char* type;
	int vaild;
	}symboltable;
	symboltable* table[TableSize];
	int CreateTableFlag=0;	
	int commentline=0;
	int CheckUndefined=0;
	int doubleComment=0;//查看是否有同一行複數個comment
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

"//".*	{printf("%s \t C++ Comment \n",yytext);commentline++;
	if(doubleComment==1)commentline--;
	}

"/""*"[^*]*[*]+([^*/][^*]*[*]+)*"/" {
		printf("%s \t C++ Comment \n",yytext);
		commentline++;
		//解決一行有兩個以上的註解
		if(doubleComment==1)commentline--;
		//解決註解橫跨多行
		int i ;
                for(i=0;i<yyleng;i++)
                        if(yytext[i]=='\n')
				{
					commentline++;
					linecount++;
				}
		
		doubleComment=1;

		}

"var"     {varflag = 1 ;}
"int"     {
		if(varflag==1){
			printf("%s \t int TYPE VAR\n",nowid);
			insert_symbol(nowid,0);
		}	
		varflag=0;free(nowid);
	}
"float32" {
                if(varflag==1){
	                printf("%s \t float TYPE VAR\n",nowid);
			insert_symbol(nowid,1);
                }
                varflag=0;free(nowid);
        }
"print"     { printf("%s \t print function \n", yytext); }
"println"     { printf("%s \t println function \n", yytext); }
"if"     { printf("%s \t if function \n", yytext); }
"else"     { printf("%s \t else function  \n", yytext); }
"for"     { printf("%s \t for function  \n", yytext); }

"+" 	{ printf("%s \t Add \n", yytext); }
"-"		{ printf("%s \t Sub \n", yytext); }
{id}	{

	if(varflag==1){//如果是宣告
		nowid = malloc(strlen(yytext)+1);
		strcpy(nowid,yytext);
	}
	else{
		printf("%s \t ID \n", yytext);
		//查看是否是undefined variable
		CheckUndefined = 1;
		lookup_symbol(yytext);
		CheckUndefined = 0;		
		
	}

	}
\n	{linecount++; varflag = 0;nowid=NULL;doubleComment=0;}

"("     { printf("%s \t LB \n", yytext); }
")"     { printf("%s \t RB \n", yytext); }
"{"     { printf("%s \t LCB \n", yytext); }
"}"     { printf("%s \t RCB \n", yytext); }

\"{letter}+({letter}|{digit})*\" {
		
		printf("\" \t quotation \n");
		int i ; 
		for(i=1;i<yyleng-1;i++)
			printf("%c",yytext[i]);
		printf("\t String\n");
		printf("\" \t quotation \n");

	}

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

void create_symbol() 
{
	
	CreateTableFlag=1;
	printf("Create a symbol table\n");
	int i;
	for(i=0;i<TableSize;i++){
	table[i]= malloc(sizeof(struct symbol_table));
	table[i]->type=NULL;
	table[i]->id=NULL;
	table[i]->vaild=0;
	}	

}
void insert_symbol(char* id , int type) {
	if(CreateTableFlag==0){//not create table yet
		create_symbol();
		table[0]->id = malloc(strlen(id)+1);
		strcpy(table[0]->id,id);
		table[0]->vaild = 1 ;//vaild表示有symbol在表中
		printf("Insert a symbol: %s\n",id);

		if(type==0)//int
			table[0]->type="int";
		else if(type==1)//float
			table[0]->type="float32";
	}
	else{
		if(lookup_symbol(id)==-1){//not declare yet(id not in symbol table)
		int i;
		for(i=0;i<TableSize;i++)//look for space to place id
			if(table[i]->vaild==0){
				table[i]->id = malloc(strlen(id)+1);
				strcpy(table[i]->id,id);
				table[i]->vaild = 1 ;//vaild表示有symbol在表中
				printf("Insert a symbol: %s\n",id);
				
		                if(type==0)//int
	                	        table[i]->type="int";
        		        else if(type==1)//float
                        		table[i]->type="float32";
			
				return;
			}
		}
	}

}
int lookup_symbol(char *id) {
	int i;
	//查看是否undefined
	if(CheckUndefined){
		for(i=0;i<TableSize;i++)
                        if(table[i]->vaild==1&&strcmp(table[i]->id,id)==0)
                        	return 0;//表示有defined
	
        	printf("Undefined variable %s\n",id);
		return -1;//沒有defined
	}
	//查看是否redefined
	for(i=0;i<TableSize;i++){
			if(table[i]->vaild==1&&strcmp(table[i]->id,id)==0){
			printf("Redefined variable %s,table index:%d\n",id,i);
			return i;
			}
	}
	return -1;
}
void dump_symbol() {

	printf("\nThe symbol table dump:\n");
	int i ;
	for(i=0;i<TableSize;i++){
		if(table[i]->vaild==1){
		printf("%d\t%s\t%s\n",i+1,table[i]->id,table[i]->type);
		}

	}


}

int main(int argc,char *argv[])
{
//	nowid = malloc(200);//存id的地方
	yyin = fopen(argv[1],"r");
	yylex();
	
	printf("\ncomment: %d lines\n",commentline);
	printf("\nParse over, the line number is %d\n",linecount);
	dump_symbol();

	return 0;
}
