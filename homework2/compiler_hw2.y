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
	#define TableSize 50000
	/* Symbol table function */
	void create_symbol();
	int insert_symbol(char*,int);
	int lookup_symbol(char*);
	void dump_symbol();
	void insert_value(int ret , double f_val, int i_val);
	int linecount=0;	
	int commentline=0;

	typedef struct symbol_table{
	char* id;
	char* type;
	union{
 			int i_val;
 			double f_val;
 	};
	int vaild;
	}symboltable;
	symboltable* table[TableSize];
	int CreateTableFlag=0;	
	int CheckUndefined=0;

	// new
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
%type <val> initializer
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
	| COMPARE
	| arith {	
				 if($1.type==1)//int
				printf("ans = %d\n", $1.i_val);
				else
				printf("ans = %lf\n", $1.f_val);
			}
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
						if($3.i_val==0)
							printf("<ERROR> The divisor can’t be 0\n");
						else
                        	$$.i_val = $1.i_val / $3.i_val;
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
						if(v2==0)
							printf("<ERROR> The divisor can’t be 0\n");
						else
                        	$$.f_val = v1 / v2;
                      }
							printf("%s\n","DIV");}
	| arith MOD arith   { 
					  if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val % $3.i_val;
						printf("%s\n","MOD");
                      } else {//double
						printf("ERROR:The modulo does not involve any floating-points\n");
                      $$.i_val=0;$$.type = 1;
						}

						}
	|ID INC 			{
						int ret=-1;
						CheckUndefined = 1;
						ret=lookup_symbol($1);
						if(ret==-1)
							printf("Error:Undefined variable %s\n",$1);
						else{
								if(strcmp(table[ret]->type,"float32")==0){
								insert_value(ret,(table[ret]->f_val)+1,0);
								}
								else if(strcmp(table[ret]->type,"int")==0){
								insert_value(ret,0.0,(table[ret]->i_val)+1);
								}
							}
						}
	|ID DEC			{
						int ret=-1;
						CheckUndefined = 1;
						ret=lookup_symbol($1);
						if(ret==-1)
							printf("Error:Undefined variable %s\n",$1);
						else{
								if(strcmp(table[ret]->type,"float32")==0){
								insert_value(ret,(table[ret]->f_val)-1,0);
								}
								else if(strcmp(table[ret]->type,"int")==0){
								insert_value(ret,0.0,(table[ret]->i_val)-1);
								}
							}
						}
	| SUB arith %prec UMINUS	{$$.i_val = $2.i_val*(-1); }//優先處理因為代表負數
	| ID ASSIGN arith      {
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								printf("Error:Undefined variable %s\n",$1);
							else{
								if(strcmp(table[ret]->type,"float32")==0){
								insert_value(ret,$3.f_val,0);
								}
								else if(strcmp(table[ret]->type,"int")==0){
								insert_value(ret,0.0,$3.i_val);
								}
							}

							}
	| '(' arith ')'     { $$.i_val = $2.i_val; }
	| ID                {							
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								printf("Error:Undefined variable %s\n",$1) ;
							else{
								if(strcmp(table[ret]->type,"float32")==0)
								{
									$$.f_val=table[ret]->f_val;
									$$.type=0;
								}
								else if(strcmp(table[ret]->type,"int")==0)
								{
									$$.i_val=table[ret]->i_val;
									$$.type=1;
								}
							}
						}
	| I_CONST			{$$.i_val = $1.i_val; $$.type=1;}
	| F_CONST			{$$.f_val = $1.f_val; $$.type=0;}
;

COMPARE 
		:arith GT arith	{
							int ret;
							if($1.type==1&&$3.type==1)
							{
								ret=($1.i_val>$3.i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
							else if($1.type==0&&$3.type==0)
							{
								ret=($1.f_val>$3.f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
								
							else
								printf("Error:compare between different type\n");						

						}
		|arith LT arith {
							int ret;
							if($1.type==1&&$3.type==1)
							{
								ret=($1.i_val<$3.i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
							else if($1.type==0&&$3.type==0)
							{
								ret=($1.f_val<$3.f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
								
							else
								printf("Error:compare between different type\n");						

						}
		|arith GE arith	{
							int ret;
							if($1.type==1&&$3.type==1)
							{
								ret=($1.i_val>=$3.i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
							else if($1.type==0&&$3.type==0)
							{
								ret=($1.f_val>=$3.f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
								
							else
								printf("Error:compare between different type\n");						

						}
		|arith LE arith {
							int ret;
							if($1.type==1&&$3.type==1)
							{
								ret=($1.i_val<=$3.i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
							else if($1.type==0&&$3.type==0)
							{
								ret=($1.f_val<=$3.f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
								
							else
								printf("Error:compare between different type\n");						

						}
		|arith EQ arith {
							int ret;
							if($1.type==1&&$3.type==1)
							{
								ret=($1.i_val==$3.i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
							else if($1.type==0&&$3.type==0)
							{
								ret=($1.f_val==$3.f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
								
							else
								printf("Error:compare between different type\n");						

						}
		|arith NE arith {
							int ret;
							if($1.type==1&&$3.type==1)
							{
								ret=($1.i_val!=$3.i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
							else if($1.type==0&&$3.type==0)
							{
								ret=($1.f_val!=$3.f_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
							}
								
							else
								printf("Error:compare between different type\n");						

						}

;


declaration
	: VAR ID type NEWLINE {
							printf("declare : %s %s\n",$2,$3) ;
							strcmp($3,"int")==0?insert_symbol($2,1):insert_symbol($2,0);
						}
	| VAR ID type ASSIGN initializer NEWLINE {
				if(strcmp($3,"float32")==0){//float
					int ret;
					printf("declare : %s %s %lf\n",$2,$3,$5.f_val) ;
					ret = insert_symbol($2,0);
					insert_value(ret,$5.f_val,0);
				}else if(strcmp($3,"int")==0){//int
					int ret;
					printf("declare : %s %s %d\n",$2,$3,$5.i_val) ;
					ret = insert_symbol($2,1);
					insert_value(ret,0.0,$5.i_val);
					}
			}//這裡要做type chexk
;

type
    : INT { $$ = $1;}
    | FLOAT { $$ = $1; }
    | VOID { $$ = $1; }
;
initializer
	: arith   { 
				if($1.type==0)//double
				{
					$$.type=0;
					$$.f_val=$1.f_val;
				}
				else{//int
					$$.type=1;
					$$.i_val=$1.i_val;
				}
			}
;


print_func 
	: PRINT '(' STRING ')' NEWLINE {printf("PRINT : %s\n",$3) ;}
	| PRINTLN '(' STRING ')' NEWLINE {printf("PRINTLN : %s\n",$3) ;}
	| PRINT '(' arith ')' NEWLINE 
						{		                  
							if($3.type==1)//int
                 				printf("PRINT : %d\n", $3.i_val);
                 			else
								printf("PRINT : %lf\n", $3.f_val);
						}	
	| PRINTLN '(' arith ')' NEWLINE 
						{							
                             if($3.type==1)//int                           
                                 printf("PRINT : %d\n", $3.i_val);
                             else
                                 printf("PRINT : %lf\n", $3.f_val);
			
						}
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
int insert_symbol(char* id , int type) {

	if(CreateTableFlag==0){//not create table yet
		create_symbol();
		table[0]->id = malloc(strlen(id)+1);
		strcpy(table[0]->id,id);
		table[0]->vaild = 1 ;//vaild表示有symbol在表中
		printf("Insert a symbol: %s\n",id);

		if(type==1)//int
			table[0]->type="int";
		else if(type==0)//float
			table[0]->type="float32";

		return 0;
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
				
		                if(type==1)//int
	                	        table[i]->type="int";
        		        else if(type==0)//float
                        		table[i]->type="float32";
			
				return i;
			}
		}
	}
	return -1;

}

void insert_value(int ret , double f_val, int i_val){
		if(CreateTableFlag==0)return ;
		if(ret==-1)
			return;
		else{
			if(table[ret]->vaild==1&&strcmp(table[ret]->type,"float32")==0)
			{
				table[ret]->f_val=f_val;
			}
			else if(table[ret]->vaild==1&&strcmp(table[ret]->type,"int")==0)	
			{
				table[ret]->i_val=i_val;
			}
		
		}
		return;

}
int lookup_symbol(char *id) {//command=0:declare command=1:取出var
	int i;
	//查看是否undefined
	if(CreateTableFlag==0)return -1;
	if(CheckUndefined==1){//表示是要取出id,是非宣告狀態（宣告狀態是要去看下面的redefined）
		for(i=0;i<TableSize;i++)
                        if(table[i]->vaild==1&&strcmp(table[i]->id,id)==0)
                        	return i;//表示有defined
	
//        	printf("Error:Undefined variable %s\n",id);
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
		printf("%d\t%s\t%s",i+1,table[i]->id,table[i]->type);
		if(strcmp(table[i]->type,"float32")==0)
		{
		printf("\t%lf\n",table[i]->f_val);
		}
		else if(strcmp(table[i]->type,"int")==0)
		{
		printf("\t%d\n",table[i]->i_val);
		}
		}


	}

}

void yyerror(char *s) {
    printf("%s on %d line \n", s , yylineno);
}

