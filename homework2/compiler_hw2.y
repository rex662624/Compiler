/*	Definition section */
%{
/*	insert the C library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern int yylex();
void yyerror(char *);
/* Symbol table function - you can add new function if need. */
//原來的 lex
	#include <stdio.h>
	#include <stdlib.h>
	#define TableSize 100
	/* Symbol table function */
	void create_symbol();
	void insert_symbol(char*,int);
	int lookup_symbol(char*);
	void dump_symbol();
	
	int linecount=0;	
	int commentline=0;

	typedef struct symbol_table{
	char* id;
	char* type;
	int vaild;
	}symboltable;
	symboltable* table[TableSize];
	int CreateTableFlag=0;	
	int CheckUndefined=0;

	// new
	int FloatOrInt=-1;//check值是float還是int
	double PassF;
	int PassI;
%}

/* Using union to define nonterminal and token type */
%union {
	struct{
		union{
    		int	i_val;
			double f_val;
		};
		int type;
	}val;
    char *string;
}

/* Token without return */
%token PRINT PRINTLN 
%token IF ELSE FOR
%token VAR NEWLINE
%token ADD SUB MUL DIV MOD GT LTGE LE EQ NE
%token '(' ')' INC DEC LT GE ASSIGN 
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token AND OR NOT LB2 RB2
%token C_COMMENT
/* Token with return, which need to sepcify type 這裡好像要跟上面的union一樣*/
%token <val> I_CONST	
%token <val> F_CONST
%token <string> STRING

%token <string> INT
%token <string> FLOAT
%token <string> VOID


%token <string> ID

/* Nonterminal with return, which need to sepcify type */
%type <string> type 
%type <val> arith
/*associate*/


%right ASSIGN
%left ADD SUB
%left MUL DIV
%left UMINUS

/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    : program stat
    |
;

stat
    : declaration
    | print_func
	| NEWLINE
	| arith { if($1.type==1)//int
				printf("ans = %d\n", $1.i_val);
			else
				printf("ans = %lf\n", $1.f_val);
				FloatOrInt=-1;}
	| C_COMMENT
;

arith
	: arith ADD arith	{ 
						if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val + $3.i_val;
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
                        $$.f_val = v1 + v2;
                      }
						printf("%s\n","ADD");}
	| arith SUB arith   { 
						if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val - $3.i_val;
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
                        $$.f_val = v1 - v2;
                      }
						printf("%s\n","SUB");}
	| arith MUL arith   { 
						if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val * $3.i_val;
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
                        $$.f_val = v1 * v2;
                      }
		
							printf("%s\n","MUL");}
	| arith DIV arith   { 

					if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val / $3.i_val;
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
                        $$.f_val = v1 / v2;
                      }
							printf("%s\n","DIV");}
	| arith MOD arith   { 
						printf("%s\n","MOD");

						}
	| SUB arith %prec UMINUS	{$$.i_val = $2.i_val*(-1); }//優先處理因為代表負數
	| ID ASSIGN arith      {;}
	| '(' arith ')'     { $$.i_val = $2.i_val; }
	| ID                { ;}
	| I_CONST			{$$.i_val = $1.i_val;}
	| F_CONST			{$$.f_val = $1.f_val;}
;

declaration
	: VAR ID type NEWLINE {printf("declare : %s %s\n",$2,$3) ;}
	| VAR ID type ASSIGN initializer NEWLINE {
				if(FloatOrInt==0){//float
					printf("declare : %s %s %lf\n",$2,$3,PassF) ;
					FloatOrInt=-1;
				}else if(FloatOrInt==1){//int
					printf("declare : %s %s %d\n",$2,$3,PassI) ;
					FloatOrInt=-1;
					}
			}//這裡要做type chexk
;

type
    : INT { $$ = $1;}
    | FLOAT { $$ = $1; }
    | VOID { $$ = $1; }
;
initializer
	: I_CONST {PassI=$1.i_val;FloatOrInt=1;}
	| F_CONST {PassF=$1.f_val;FloatOrInt=0;}
	//| arith //{ $$ = $1; }
;


print_func 
	: PRINT '(' STRING ')' NEWLINE {printf("PRINT : %s\n",$3) ;}
	| PRINTLN '(' STRING ')' NEWLINE {printf("PRINTLN : %s\n",$3) ;}
;


%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;
    yyparse();

	printf("\nParse over, the line number is %d\n",linecount);
	printf("\ncomment: %d lines\n",commentline);

	if(CreateTableFlag==1)//如果有建立symbol table
		dump_symbol();

	
    return 0;
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
	
        	printf("Error:Undefined variable %s\n",id);
		return -1;//沒有defined
	}
	//查看是否redefined
	for(i=0;i<TableSize;i++){
			if(table[i]->vaild==1&&strcmp(table[i]->id,id)==0){
			printf("Error:Redefined variable %s,table index:%d\n",id,i+1);
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

void yyerror(char *s) {
    printf("%s on %d line \n", s , yylineno);
}

