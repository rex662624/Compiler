/*	Definition section */
%{
/*	insert the C library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern int yylex();
void yyerror(char *);
/* Sym
bol table function - you can add new function if need. */
//原來的 lex
	#include <stdio.h>
	#include <stdlib.h>
	#define TableSize 500
	/* Symbol table function */
	void create_symbol();
	int insert_symbol(char*,int);
	int lookup_symbol(char*);
	void dump_symbol();
	void insert_value(int ret , double f_val, int i_val);
	int linecount=1;	
	int commentline=0;

	typedef struct symbol_table{
	char* id;
	char* type;
	union{
 			int i_val;
 			double f_val;
 	};
	int vaild;

	int scope_depth;
	}symboltable;
	symboltable* table[TableSize];
	int CreateTableFlag=0;	
	int CheckUndefined=0;
	int NowDepth=0;
	void ScopeOver();
	//NEW
	int printidscope=0;//表示目前是不是要print id 或是數字 
	int out=0;//要輸出的值
	//jasmin
	int ERROR=0;//程式有沒有錯誤
	FILE * fp;
	
	int labelStack[256];//目前存的 label
	int labeltop;//目前所在的label
	int globallabel=0;//目前label編到幾號

	void ForAssign(char* out ,char* $1,int type,char * buf,int i_val,double f_val,int index);	

%}

/* Using union to define nonterminal and token type */
%union {
	struct{
		union{
    		int	i_val;
		double f_val;
		};
		int type;
		//NEW
		char buf[512];//為了插入i2f使用
	}val;
    char *string;
}

/* Token without return */
%token PRINT PRINTLN 
%token IF ELSE FOR
%token VAR NEWLINE
%token ADD SUB MUL DIV MOD GT LTGE LE EQ NE
%token '(' ')' '{' '}'INC DEC LT GE ASSIGN 
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token AND OR NOT LB2 RB2
%token C_COMMENT
%token SEM
%token FUNC COM
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
%type <val> compare_expr

%type <val> call_function
%type <val> argument_list
%type <string> for_assign
/*associate*/


%left GT LTGE LE EQ NE
%right ASSIGN
%left ADD SUB
%left MUL DIV MOD
%left INC DEC
%left UMINUS
%right ')' ELSE
/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    :  program stat 
    |
;

stat
	: 	'{' 				{NowDepth++;}
		
		block_item_list 	{
							
							printf("Scope %d\n",NowDepth);
						}
		
		'}'				{	
						// NEW 把目前scope的vaild設為2表示dead不能用
						ScopeOver();
						NowDepth--; 
						//printf("-------------------------Scope %d\n",NowDepth);
						}
	| for_loop			{		}
    	| declaration
	| if_block
    	| print_func
	| NEWLINE {linecount++;}
	| assign_expr
	| compare_expr
	| arith {	
/*				 if($1.type==1)//int
				printf("ans = %d\n", $1.i_val);
				else
				printf("ans = %lf\n", $1.f_val);*/
			//printf("--------------------------------------------\n%s-----------------------------------------",$1.buf);
			fprintf(fp,"%s",$1.buf);
				
			}
	| C_COMMENT
	| function
	
;
//--------------------------function
function
	:FUNC ID '(' parameter_list ')' funct_type 
	'{' 
	block_item_list 
	'}'
;

funct_type
    : INT 
    | FLOAT 
    | VOID 
    |
;
parameter_list
	:  ID type 
	| ID type COM  parameter_list 
	|
;
//-------------------------if

if_block
    : 	IF					{//進到if表示新label開始
							labeltop++;//pointer往前
							labelStack[labeltop]=globallabel;//Stack內的暫存label=我的label
							globallabel++;
						} 	
	'(' compare_expr ')' stat ELSE_block	{
							//printf("-----------------------------asdsad\n");
							labeltop--;
						
						}
;

ELSE_block
	:ELSE 				{								
							fprintf(fp,"\tgoto EXIT_%d\n",labelStack[labeltop]);
							fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
						}
	stat 				{
							fprintf(fp,"EXIT_%d:\n",labelStack[labeltop]);
							//nowlabel--;//結束這個scope，要還原到上個scope的
						}
	| NEWLINE			{//沒有else的情況，可以想成else的do something 沒東西
											linecount++;
											//printf("-----------------------------label_%d\n",labelStack[labeltop]);
											fprintf(fp,"\tgoto EXIT_%d\n",labelStack[labeltop]);
											fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
											fprintf(fp,"EXIT_%d:\n",labelStack[labeltop]);
						}
	|					{//EOF
											//linecount++;
											fprintf(fp,"\tgoto EXIT_%d\n",labelStack[labeltop]);
											fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
											fprintf(fp,"EXIT_%d:\n",labelStack[labeltop]);
						}
	
;

block_item_list
    : stat
    | block_item_list stat
;

//------------------------for
for_loop 													//for i = 0; i < 15; i++ {		}
		: FOR assign_expr SEM								{//初始化值後，準備進入for
																labeltop++;//pointer往前
																labelStack[labeltop]=globallabel;//Stack內的暫存label=我的label
																globallabel++;	
																//For label的數字會跟裡面的if數字一樣
																fprintf(fp,"FORLabel_%d:\n",labelStack[labeltop]);
															} 
		 compare_expr SEM 	For_block						{//for loop 的 body結束後才會進來
																labeltop--;
															}
		| FOR'(' 												{//準備進入for
																labeltop++;//pointer往前
																labelStack[labeltop]=globallabel;//Stack內的暫存label=我的label
																globallabel++;	
																//For label的數字會跟裡面的if數字一樣
																fprintf(fp,"FORLabel_%d:\n",labelStack[labeltop]);
															}	
		 compare_expr ')'	stat							  	{
																fprintf(fp,"\tgoto FORLabel_%d\n",labelStack[labeltop]);
																fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
															} 
;
For_block	:	ID DEC stat							{
													//---------------------------本來ID做的事		
													int ret=-1;
													CheckUndefined = 1;
													ret=lookup_symbol($1);
													CheckUndefined = 0;
													if(ret==-1)
														{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
													else{
															if(strcmp(table[ret]->type,"float32")==0)
															{
																insert_value(ret,(table[ret]->f_val)+1,0);
																char *tmp=malloc(30);
																fprintf(fp,"\tfload %d\n",ret);
																fprintf(fp,"\tldc 1.0\n");
																fprintf(fp,"\tfsub\n");
																fprintf(fp,"\tfstore %d\n",ret);
															}
															else if(strcmp(table[ret]->type,"int")==0)
															{
																insert_value(ret,0.0,(table[ret]->i_val)+1);
																char *tmp=malloc(30);
																fprintf(fp,"\tiload %d\n",ret);
																fprintf(fp,"\tldc 1\n");
																fprintf(fp,"\tisub\n");
																fprintf(fp,"\tistore %d\n",ret);
															}
														}
													//------------------------------------------------------------					
													fprintf(fp,"\tgoto FORLabel_%d\n",labelStack[labeltop]);
													fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
													labeltop--;
												}					
			|	ID INC  stat							{
													//---------------------------本來ID做的事		
													int ret=-1;
													CheckUndefined = 1;
													ret=lookup_symbol($1);
													CheckUndefined = 0;
													if(ret==-1)
														{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
													else{
															if(strcmp(table[ret]->type,"float32")==0)
															{
																insert_value(ret,(table[ret]->f_val)+1,0);
																char *tmp=malloc(30);
																fprintf(fp,"\tfload %d\n",ret);
																fprintf(fp,"\tldc 1.0\n");
																fprintf(fp,"\tfadd\n");
																fprintf(fp,"\tfstore %d\n",ret);
															}
															else if(strcmp(table[ret]->type,"int")==0)
															{
																insert_value(ret,0.0,(table[ret]->i_val)+1);
																char *tmp=malloc(30);
																fprintf(fp,"\tiload %d\n",ret);
																fprintf(fp,"\tldc 1\n");
																fprintf(fp,"\tiadd\n");
																fprintf(fp,"\tistore %d\n",ret);
															}
														}
													//------------------------------------------------------------					
													fprintf(fp,"\tgoto FORLabel_%d\n",labelStack[labeltop]);
													fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
													labeltop--;
												}
			|	for_assign	stat					{
													fprintf(fp,"%s",$1);
													fprintf(fp,"\tgoto FORLabel_%d\n",labelStack[labeltop]);
													fprintf(fp,"Label_%d:\n",labelStack[labeltop]);
													labeltop--;
											
												}
;

for_assign 
			:  ID ASSIGN arith 					{
													$$=malloc(512);
													ForAssign($$ ,$1,$3.type,$3.buf,$3.i_val,$3.f_val,0);
												}
			| ID ADD_ASSIGN arith 				{
													$$=malloc(512);
													ForAssign($$ ,$1,$3.type,$3.buf,$3.i_val,$3.f_val,1);
	
												}
			| ID SUB_ASSIGN arith 				{
													$$=malloc(512);
													ForAssign($$ ,$1,$3.type,$3.buf,$3.i_val,$3.f_val,2);
												}
			| ID MUL_ASSIGN arith 				{
													$$=malloc(512);
													ForAssign($$ ,$1,$3.type,$3.buf,$3.i_val,$3.f_val,3);
												}
			| ID DIV_ASSIGN arith 				{
													$$=malloc(512);
													ForAssign($$ ,$1,$3.type,$3.buf,$3.i_val,$3.f_val,4);
												} 

//-------------------------- basic
arith
	: arith ADD arith	{ 
		sprintf($$.buf,"%s","");//先清空	
	
		if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val + $3.i_val;
				
			strcat($$.buf,$1.buf);
			strcat($$.buf,$3.buf);
			strcat($$.buf, "\tiadd\n");
			
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
                        $$.f_val = v1 + v2;


			strcat($$.buf,$1.buf);
			if($1.type == 1){strcat($$.buf,"\ti2f\n");}//如果是int要轉成float
			strcat($$.buf,$3.buf);
			if($3.type == 1)strcat($$.buf,"\ti2f\n");
			strcat($$.buf, "\tfadd\n");
                      }
						printf("%s\n","ADD");
						}
	| arith SUB arith   {
			sprintf($$.buf,"%s","");//先清空	
			
			if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val - $3.i_val;

			strcat($$.buf,$1.buf);
			strcat($$.buf,$3.buf);
			strcat($$.buf, "\tisub\n");
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
                        $$.f_val = v1 - v2;

			strcat($$.buf,$1.buf);
			if($1.type == 1){strcat($$.buf,"\ti2f\n");}//如果是int要轉成float
			strcat($$.buf,$3.buf);
			if($3.type == 1)strcat($$.buf,"\ti2f\n");
			strcat($$.buf, "\tfsub\n");
                      }
						printf("%s\n","SUB");
						}
	| arith MUL arith   { 
			sprintf($$.buf,"%s","");//先清空	
			
			if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val * $3.i_val;

			strcat($$.buf,$1.buf);
			strcat($$.buf,$3.buf);
			strcat($$.buf, "\timul\n");
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
                        $$.f_val = v1 * v2;

			strcat($$.buf,$1.buf);
			if($1.type == 1){strcat($$.buf,"\ti2f\n");}//如果是int要轉成float
			strcat($$.buf,$3.buf);
			if($3.type == 1)strcat($$.buf,"\ti2f\n");
			strcat($$.buf, "\tfmul\n");
                      }
		
							printf("%s\n","MUL");
						}
	| arith DIV arith   { 
			sprintf($$.buf,"%s","");//先清空	

			if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
						if($3.i_val==0)
							{printf("<ERROR> The divisor can’t be 0 (line %d)\n",linecount);ERROR=1;}
						else
                        				$$.i_val = $1.i_val / $3.i_val;

			strcat($$.buf,$1.buf);
			strcat($$.buf,$3.buf);
			strcat($$.buf, "\tidiv\n");
                      } else {//double
                        double v1 = $1.type == 1 ? (double)$1.i_val
                                                   : $1.f_val;
                        double v2 = $3.type == 1 ? (double)$3.i_val
                                                   : $3.f_val;
                        $$.type = 0;
						if(v2==0)
							{printf("<ERROR> The divisor can’t be 0 (line %d)\n",linecount);ERROR=1;}
						else
                        				$$.f_val = v1 / v2;

			strcat($$.buf,$1.buf);
			if($1.type == 1){strcat($$.buf,"\ti2f\n");}//如果是int要轉成float
			strcat($$.buf,$3.buf);
			if($3.type == 1)strcat($$.buf,"\ti2f\n");
			strcat($$.buf, "\tfdiv\n");
                      }
							printf("%s\n","DIV");}
	| arith MOD arith   { 
			sprintf($$.buf,"%s","");//先清空
			
			if ($1.type == 1 && $3.type == 1) {//integer
                        $$.type = 1;
                        $$.i_val = $1.i_val % $3.i_val;
						printf("%s\n","MOD");
			
			strcat($$.buf,$1.buf);
			strcat($$.buf,$3.buf);
			strcat($$.buf, "\tirem\n");
                      } else {//double
						{printf("ERROR:The modulo does not involve any floating-points (line %d)\n",linecount);ERROR=1;}
                     				 $$.i_val=0;$$.type = 1;
				}

						}
	|ID INC 			{
						sprintf($$.buf,"%s","");//先清空
						int ret=-1;
						CheckUndefined = 1;
						ret=lookup_symbol($1);
						CheckUndefined = 0;
						if(ret==-1)
							{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
						else{
								if(strcmp(table[ret]->type,"float32")==0){
								insert_value(ret,(table[ret]->f_val)+1,0);
								//id+1;
								char *tmp=malloc(30);	
								sprintf(tmp,"\tfload %d\n",ret);
								strcat( $$.buf,tmp);
								
								strcat($$.buf,"\tldc 1.0\n");
								strcat($$.buf,"\tfadd\n");
								sprintf(tmp,"\tfstore %d\n",ret);
								strcat($$.buf,tmp);
								}
								else if(strcmp(table[ret]->type,"int")==0){
								insert_value(ret,0.0,(table[ret]->i_val)+1);
								char *tmp=malloc(30);	
								sprintf(tmp,"\tiload %d\n",ret);
								strcat( $$.buf,tmp);
								
								strcat($$.buf,"\tldc 1\n");
								strcat($$.buf,"\tiadd\n");
								sprintf(tmp,"\tistore %d\n",ret);
								strcat($$.buf,tmp);
								}
							}
						}
	|ID DEC			{
						sprintf($$.buf,"%s","");//先清空
						int ret=-1;
						CheckUndefined = 1;
						ret=lookup_symbol($1);
						CheckUndefined = 0;
						if(ret==-1)
							{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
						else{
								if(strcmp(table[ret]->type,"float32")==0){
								insert_value(ret,(table[ret]->f_val)-1,0);
								//id+1;
								char *tmp=malloc(30);	
								sprintf(tmp,"\tfload %d\n",ret);
								strcat( $$.buf,tmp);
								
								strcat($$.buf,"\tldc 1.0\n");
								strcat($$.buf,"\tfsub\n");
								sprintf(tmp,"\tfstore %d\n",ret);
								strcat($$.buf,tmp);
								}
								else if(strcmp(table[ret]->type,"int")==0){
								insert_value(ret,0.0,(table[ret]->i_val)-1);
								char *tmp=malloc(30);	
								sprintf(tmp,"\tiload %d\n",ret);
								strcat( $$.buf,tmp);
								
								strcat($$.buf,"\tldc 1\n");
								strcat($$.buf,"\tisub\n");
								sprintf(tmp,"\tistore %d\n",ret);
								strcat($$.buf,tmp);
								}
							}
						}
	| SUB arith %prec UMINUS	{$$.i_val = $2.i_val*(-1); }//優先處理因為代表負數
	| '(' arith ')'     { 
							if($2.type==1)
								{$$.i_val = $2.i_val;$$.type=1;}
							else
								{$$.f_val = $2.f_val;$$.type=0;}

							sprintf($$.buf,"%s",$2.buf);
 
						}
	| ID                {				
							sprintf($$.buf,"%s","");//先清空			
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
							else{
								if(strcmp(table[ret]->type,"float32")==0)
								{
									$$.f_val=table[ret]->f_val;
									$$.type=0;
									char *tmp=malloc(30);
									sprintf(tmp,"\tfload %d\n",ret);
									strcat( $$.buf,tmp);
								}
								else if(strcmp(table[ret]->type,"int")==0)
								{
									$$.i_val=table[ret]->i_val;
									$$.type=1;
									char *tmp=malloc(30);
									sprintf(tmp,"\tiload %d\n",ret);
									strcat( $$.buf,tmp);
								}
							//NEW
							printidscope=1;
							out=table[ret]->scope_depth;
							}
						}
	| I_CONST			{$$.i_val = $1.i_val; $$.type=1;    
								char *tmp=malloc(30);
								sprintf(tmp,"\tldc %d\n",$1.i_val);
								strcat( $$.buf,tmp);
						}
	| F_CONST			{$$.f_val = $1.f_val; $$.type=0;  
								char *tmp=malloc(30);
								sprintf(tmp,"\tldc %lf\n",$1.f_val);
								strcat( $$.buf,tmp);
						}
	| call_function
;
//-----------------------------------------------
call_function
	: ID '(' argument_list ')' {sprintf($$.buf,"%s",$3.buf);}
;

argument_list
	: argument_list COM arith 
	| arith
	|	{sprintf($$.buf," ");}//沒有argument
;
//----------------------------------------------

compare_expr 
		:arith GT arith	{//>
							sprintf($$.buf,"%s","");//先清空
							int ret;
							if($1.type==1&&$3.type==1)// compare between int
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								strcat($$.buf,$3.buf);
								strcat($$.buf, "\tisub\n");
								sprintf(tmp,"\tifle Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
							else // compare between float
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								if($1.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf,$3.buf);
								if($3.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf, "\tfcmpl\n");//作到這裡stack上是0($1=$3) 1($1>$3) -1($1<$3)
								sprintf(tmp,"\tifle Label_%d\n",labelStack[labeltop]);//如果<=0做else
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}					

						}
		|arith LT arith {//<
							sprintf($$.buf,"%s","");//先清空
							int ret;
							if($1.type==1&&$3.type==1)
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								strcat($$.buf,$3.buf);
								strcat($$.buf, "\tisub\n");
								sprintf(tmp,"\tifge Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
							else
							{

								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								if($1.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf,$3.buf);
								if($3.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf, "\tfcmpl\n");//作到這裡stack上是0($1=$3) 1($1>$3) -1($1<$3)
								sprintf(tmp,"\tifge Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
						}
		|arith GE arith	{//>=
							sprintf($$.buf,"%s","");//先清空
							int ret;
							if($1.type==1&&$3.type==1)
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								strcat($$.buf,$3.buf);
								strcat($$.buf, "\tisub\n");
								sprintf(tmp,"\tiflt Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
							else
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								if($1.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf,$3.buf);
								if($3.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf, "\tfcmpl\n");//作到這裡stack上是0($1=$3) 1($1>$3) -1($1<$3)
								sprintf(tmp,"\tiflt Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
						}
		|arith LE arith {//<=
							sprintf($$.buf,"%s","");//先清空
							int ret;
							if($1.type==1&&$3.type==1)
							{
								ret=($1.i_val<=$3.i_val);
								if(ret)
									printf("True\n");
								else
									printf("False\n");	
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								strcat($$.buf,$3.buf);
								strcat($$.buf, "\tisub\n");
								sprintf(tmp,"\tifgt Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
							else
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								if($1.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf,$3.buf);
								if($3.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf, "\tfcmpl\n");//作到這裡stack上是0($1=$3) 1($1>$3) -1($1<$3)
								sprintf(tmp,"\tifgt Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
						}
		|arith EQ arith {//==
							sprintf($$.buf,"%s","");//先清空
							int ret;
							if($1.type==1&&$3.type==1)
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								strcat($$.buf,$3.buf);
								strcat($$.buf, "\tisub\n");
								sprintf(tmp,"\tifne Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);		
							}
							else
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								if($1.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf,$3.buf);
								if($3.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf, "\tfcmpl\n");//作到這裡stack上是0($1=$3) 1($1>$3) -1($1<$3)
								sprintf(tmp,"\tifne Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
						}
		|arith NE arith {//!=
							sprintf($$.buf,"%s","");//先清空
							int ret;
							if($1.type==1&&$3.type==1)
							{

								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								strcat($$.buf,$3.buf);
								strcat($$.buf, "\tisub\n");
								sprintf(tmp,"\tifeq Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
							else
							{
								char* tmp=malloc(30);
								strcat($$.buf,$1.buf);
								if($1.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf,$3.buf);
								if($3.type==1)strcat($$.buf,"\ti2f\n");//如果他是int要轉型成float
								strcat($$.buf, "\tfcmpl\n");//作到這裡stack上是0($1=$3) 1($1>$3) -1($1<$3)
								sprintf(tmp,"\tifeq Label_%d\n",labelStack[labeltop]);	
								strcat($$.buf,tmp);	
								fprintf(fp,"%s",$$.buf);	
							}
						}

;

assign_expr
	:	ID ASSIGN arith      {
							printf("ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
							else{
								if(strcmp(table[ret]->type,"float32")==0){//如果ID是float
									if($3.type==0)//如果arith是float
									{
										insert_value(ret,$3.f_val,0);
										fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
										fprintf(fp, "\tfstore %d\n",ret);
										
									}
									else//如果arith是int
									{
										insert_value(ret,(float)$3.i_val,0);
										fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
										fprintf(fp, "\ti2f\n");
										fprintf(fp, "\tistore %d\n",ret);
		
									}

								}
								else if(strcmp(table[ret]->type,"int")==0){//ID是int
									if($3.type==0)//如果arith是float
									{
										insert_value(ret,0.0,(int)$3.f_val);
										fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
										fprintf(fp, "\tf2i\n");
										fprintf(fp, "\tistore %d\n",ret);										
									}
									else//如果arith是int
									{
										insert_value(ret,0.0,$3.i_val);
										fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
										fprintf(fp, "\tistore %d\n",ret);		
									}
								
								}
							}

							}
	|	ID ADD_ASSIGN arith      {
							printf("ADD_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
							else{
								if(strcmp(table[ret]->type,"float32")==0){
								if($3.type==0){//ID是float且arith是float
									table[ret]->f_val +=$3.f_val;

									//x+arith
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入

									fprintf(fp,"\tfadd\n");
									fprintf(fp, "\tfstore %d\n",ret);									
								}
								else{//ID是float且arith是int
									table[ret]->f_val +=(double)$3.i_val;

									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									//x+arith
									fprintf(fp,"\ti2f\n");
									fprintf(fp,"\tfadd\n");
									fprintf(fp,"\tfstore %d\n",ret);	
								}
								}
								else if(strcmp(table[ret]->type,"int")==0){
								if($3.type==1){//ID是int且arith是int
									table[ret]->i_val +=$3.i_val;

									//x+arith
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tiadd\n");
									fprintf(fp, "\tistore %d\n",ret);		
								}
								else{//ID是int且arith是float
									//printf("<ERROR>:assign float to int variable (line %d)\n",linecount);

									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									//x+arith
									fprintf(fp,"\tf2i\n");
									fprintf(fp,"\tiadd\n");
									fprintf(fp, "\tistore %d\n",ret);	
								}
								}

							}
							}
	|	ID SUB_ASSIGN arith       {
							printf("SUB_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
							else{
							if(strcmp(table[ret]->type,"float32")==0){
								if($3.type==0){//ID是float，arith是float
									table[ret]->f_val -=$3.f_val;

									//x-arith
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tfsub\n");
									fprintf(fp, "\tfstore %d\n",ret);	
								}
								else{//ID是float，arith是int
									table[ret]->f_val -=(double)$3.i_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\ti2f\n");
									fprintf(fp,"\tfsub\n");
									fprintf(fp,"\tfstore %d\n",ret);	
								}

							}
							else if(strcmp(table[ret]->type,"int")==0){
								if($3.type==1){//ID是int，arith是int
									table[ret]->i_val -=$3.i_val;
									
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tisub\n");
									fprintf(fp, "\tistore %d\n",ret);
								}	
								else{//ID是int，arith是float
									//printf("<ERROR>:assign float to int variable (line %d)\n",linecount);
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tf2i\n");
									fprintf(fp,"\tisub\n");
									fprintf(fp, "\tistore %d\n",ret);	
								}
							}
								

							}
							}
	|	ID MUL_ASSIGN arith      {
							printf("MUL_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
							else{
							if(strcmp(table[ret]->type,"float32")==0){
								if($3.type==0){//ID是float，arith是float
									table[ret]->f_val *=$3.f_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tfmul\n");
									fprintf(fp, "\tfstore %d\n",ret);	
								}
								else{//ID是float，arith是int
									table[ret]->f_val *=(double)$3.i_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\ti2f\n");
									fprintf(fp,"\tfmul\n");
									fprintf(fp,"\tfstore %d\n",ret);	
								}

							}
							else if(strcmp(table[ret]->type,"int")==0){
								if($3.type==1){//ID是int，arith是int
									table[ret]->i_val *=$3.i_val;
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\timul\n");
									fprintf(fp, "\tistore %d\n",ret);
								}	
								else{//ID是int，arith是float
									//printf("<ERROR>:assign float to int variable (line %d)\n",linecount);
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tf2i\n");
									fprintf(fp,"\timul\n");
									fprintf(fp, "\tistore %d\n",ret);	
								}
							}
							}
							}
	|	ID DIV_ASSIGN arith      {
							printf("DIV_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
							else{
							if(strcmp(table[ret]->type,"float32")==0){
								if($3.type==0){//ID是float，arith是float
									table[ret]->f_val /=$3.f_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tfdiv\n");
									fprintf(fp, "\tfstore %d\n",ret);	
								}
								else{//ID是float，arith是int
									table[ret]->f_val /=(double)$3.i_val;
									fprintf(fp,"\tfload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\ti2f\n");
									fprintf(fp,"\tfdiv\n");
									fprintf(fp,"\tfstore %d\n",ret);	
								}

							}
							else if(strcmp(table[ret]->type,"int")==0){
								if($3.type==1){//ID是int，arith是int
									table[ret]->i_val /=$3.i_val;
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tidiv\n");
									fprintf(fp, "\tistore %d\n",ret);
								}	
								else{//ID是int，arith是float
									//printf("<ERROR>:assign float to int variable (line %d)\n",linecount);
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tf2i\n");
									fprintf(fp,"\tidiv\n");
									fprintf(fp, "\tistore %d\n",ret);	
								}
							}
							}
						}
	|	ID MOD_ASSIGN arith      {
							printf("MOD_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
							else{
								if(strcmp(table[ret]->type,"int")==0&&$3.type==1){
									table[ret]->i_val %=$3.i_val;
									fprintf(fp,"\tiload %d\n",ret);
									fprintf(fp,"%s",$3.buf);//所有arith結束都要寫入
									fprintf(fp,"\tirem\n");
									fprintf(fp, "\tistore %d\n",ret);
								}
								else{
									printf("<ERROR>:assign float to int variable (line %d)\n",linecount);ERROR=1;
								} 
							}
							}

;


declaration
	: VAR ID type  {
//							printf("declare : %s %s\n",$2,$3) ;
							int ret;
							if(strcmp($3,"int")==0){
								ret=insert_symbol($2,1);
								fprintf(fp, "\tldc %d\n",0);
								fprintf(fp, "\tistore %d\n",ret);
							}else{
								ret=insert_symbol($2,0);
								fprintf(fp, "\tldc %f\n",0.0);
								fprintf(fp, "\tfstore %d\n",ret);
							}
						}
	| VAR ID type ASSIGN initializer {
				if(strcmp($3,"float32")==0){//float
					int ret;
//					printf("declare : %s %s %lf\n",$2,$3,$5.f_val) ;
					ret = insert_symbol($2,0);
					insert_value(ret,$5.f_val,0);
					
					fprintf(fp,"%s",$5.buf);//有關arith結束都要寫入
					fprintf(fp, "\tfstore %d\n",ret);					
				}else if(strcmp($3,"int")==0){//int
					int ret;
//					printf("declare : %s %s %d\n",$2,$3,$5.i_val) ;
					ret = insert_symbol($2,1);
					insert_value(ret,0.0,$5.i_val);

					fprintf(fp,"%s",$5.buf);//有關arith結束都要寫入
					fprintf(fp, "\tistore %d\n",ret);
					}
			}//這裡要做type check
;

type
    : INT { $$ = $1;}
    | FLOAT { $$ = $1; }
    | VOID { $$ = $1; }
;
initializer
	: arith   { 
				sprintf($$.buf,"%s",$1.buf);
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
	: PRINT '(' STRING ')' {

							printf("PRINT : %s\n",$3) ;
							fprintf(fp, "\tldc \"%s\"\n",$3);
							fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
							fprintf(fp, "\tswap\n");
							fprintf(fp, "\tinvokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
						}
	| PRINTLN '(' STRING ')' {
							printf("PRINTLN : %s\n",$3) ;
							fprintf(fp, "\tldc \"%s\"\n",$3);
							fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
							fprintf(fp, "\tswap\n");
							fprintf(fp, "\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");

						}
	| PRINT '(' arith ')' 
						{	
							
							fprintf(fp,"%s",$3.buf);//有關arith結束都要寫入
										
							fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
							fprintf(fp, "\tswap\n");
														                  
							if($3.type==1)//int
								{	
									fprintf(fp, "\tinvokevirtual java/io/PrintStream/print(I)V\n");	
									if(printidscope==0)//要印出數字
										{	
                 									printf("PRINT : %d\n", $3.i_val);
										}
									else//印出id
										printf("PRINT : %d (Block:%d)\n", $3.i_val,out);
								}
                 					else
								{	
									fprintf(fp, "\tinvokevirtual java/io/PrintStream/print(F)V\n");	
									if(printidscope==0)
                 								printf("PRINT : %lf\n", $3.f_val);
									else
										printf("PRINT : %lf (Block:%d)\n", $3.f_val,out);
								}
						printidscope=0;
						}	
	| PRINTLN '(' arith ')' 
						{	
							fprintf(fp,"%s",$3.buf);//有關arith結束都要寫入
							//printf("--------------------------------------------\n%s-----------------------------------------",$3.buf);					
							fprintf(fp, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
							fprintf(fp, "\tswap\n");
								
	                  
							if($3.type==1)//int
								{	
									fprintf(fp, "\tinvokevirtual java/io/PrintStream/println(I)V\n");	
									if(printidscope==0)
                 								printf("PRINTLN : %d\n", $3.i_val);
									else
										printf("PRINTLN : %d (Block:%d)\n", $3.i_val,out);
								}
                 					else
								{	

									fprintf(fp, "\tinvokevirtual java/io/PrintStream/println(F)V\n");	
									if(printidscope==0)
                 								printf("PRINTLN : %lf\n", $3.f_val);
									else
										printf("PRINTLN : %lf (Block:%d)\n", $3.f_val,out);
								}
						printidscope=0;
						}	
;


%%


/* C code section */
int main(int argc, char** argv)
{
    	yylineno = 0;
	fp= fopen("Computer.j", "w" );	
	if( fp == NULL )  {
		fprintf( stdout, "Open  file  error\n" );
		exit(-1);
	}
	//把lablestack設成-1
	int i;
	for(i=0;i<256;i++)labelStack[i]=-1;
	labeltop=-1;
	
	//----basic program --------------------
	
	fprintf(fp, ".class public main\n");
	fprintf(fp, ".super java/lang/Object\n");
	fprintf(fp, ".method public static main([Ljava/lang/String;)V\n");
	fprintf(fp, ".limit stack 100\n");
	fprintf(fp, ".limit locals 100\n");
	
    	yyparse();

	fprintf(fp, "\treturn\n");
	fprintf(fp, ".end method\n");
	
	fclose(fp);
	//------------------------------------------------
	printf("\nParse over, the line number is %d\n",linecount);
	printf("\ncomment: %d lines\n",commentline);

	if(CreateTableFlag==1)//如果有建立symbol table
		dump_symbol();

	if(ERROR==1){//有錯誤不要產生.j檔
		remove("Computer.j");

	}

	
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
	table[i]->scope_depth=-1;
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
		//New
		table[0]->scope_depth=NowDepth;

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
				
				//New
				table[i]->scope_depth=NowDepth;
				
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
	int smallest=-1;//NEW先設定最小scope=-1(沒有defined)
	int i;
	//查看是否undefined
	if(CreateTableFlag==0)return -1;
	if(CheckUndefined==1){//表示是要取出id,是非宣告狀態（宣告狀態是要去看下面的redefined）
		for(i=0;i<TableSize;i++)
			//NEW  只能取 <= 目前 scope的人 但是要看最小的，所以for要走完
                        if(table[i]->vaild==1&&strcmp(table[i]->id,id)==0&&table[i]->scope_depth<=NowDepth)
                        	{
					if(smallest<=i)smallest=i;
				}//會進來表示有defined
	
//        	printf("<ERROR>:Undefined variable %s (line %d)\n",id,linecount);ERROR=1;
		return smallest;//沒有defined
	}
	
	//查看是否redefined
	for(i=0;i<TableSize;i++){
			//NEW 會進到這裡表示是宣告
			if(table[i]->vaild==1&&strcmp(table[i]->id,id)==0&&table[i]->scope_depth==NowDepth){
			
			printf("<ERROR>:Redefined variable %s,table index:%d (line %d)\n",id,i+1,linecount);ERROR=1;
			return i;
			}
	}
	
	return -1;
}
void dump_symbol() {

	printf("\nThe symbol table dump:\n");
	int i ;
	printf("%3s\t%6s\t%8s\t%10s\t%5s\n","index","ID","type","value","Scope");
	for(i=0;i<TableSize;i++){
		if(table[i]->vaild!=0){
		printf("%3d\t%6s\t%8s",i+1,table[i]->id,table[i]->type);
		if(strcmp(table[i]->type,"float32")==0)
		{
		printf("\t%10lf",table[i]->f_val);
		}
		else if(strcmp(table[i]->type,"int")==0)
		{
		printf("\t%10d",table[i]->i_val);
		}
		//NEW
		printf("\t%5d\n",table[i]->scope_depth);
		}


	}

}

void yyerror(char *s) {
    printf("%s on %d line \n", s , linecount);
}

//NEW
void ScopeOver()
{
	int i ;
	for(i=0;i<TableSize;i++){
		if(table[i]->vaild!=0&&NowDepth==table[i]->scope_depth){
			table[i]->vaild=2;
		}
	}
}

void ForAssign(char* out ,char* $1,int type,char * buf,int i_val,double f_val,int index)
{
							char * temp=malloc(512);
							sprintf(out,"%s","");		
							printf("FOR_ASSIGN\n");
							int ret=-1;
							CheckUndefined = 1;
							ret=lookup_symbol($1);
							CheckUndefined = 0;
							if(ret==-1)
								{printf("<ERROR>:Undefined variable %s (line %d)\n",$1,linecount);ERROR=1;}
							else{
								if(strcmp(table[ret]->type,"float32")==0){
								if(type==0){//ID是float且arith是float
									
									if(index!=0)sprintf(out,"\tfload %d\n",ret);
									strcat(out,buf);//所有arith結束都要寫入
									if(index==0){//=
									}else if(index==1){//+=
									table[ret]->f_val +=f_val;
									strcat(out,"\tfadd\n");
									}else if(index==2){//-=
									table[ret]->f_val -=f_val;
									strcat(out,"\tfsub\n");
									}else if(index==3){// *=
									table[ret]->f_val *=f_val;
									strcat(out,"\tfmul\n");
									}else if(index==4){// /=
									table[ret]->f_val /=f_val;
									strcat(out,"\tfdiv\n");
									}
									sprintf(temp,"\tfstore %d\n",ret);
									strcat(out, temp);								
								}
								else{//ID是float且arith是int									
									if(index!=0)sprintf(out,"\tfload %d\n",ret);
									strcat(out,buf);//所有arith結束都要寫入
									strcat(out,"\ti2f\n");
									if(index==0){//=
									}else if(index==1){//+=
									table[ret]->f_val +=f_val;
									strcat(out,"\tfadd\n");
									}else if(index==2){//-=
									table[ret]->f_val -=f_val;
									strcat(out,"\tfsub\n");
									}else if(index==3){// *=
									table[ret]->f_val *=f_val;
									strcat(out,"\tfmul\n");
									}else if(index==4){// /=
									table[ret]->f_val /=f_val;
									strcat(out,"\tfdiv\n");
									}
									sprintf(temp,"\tfstore %d\n",ret);
									strcat(out, temp);	
								}
								}
								else if(strcmp(table[ret]->type,"int")==0){
								if(type==1){//ID是int且arith是int
									
									if(index!=0)sprintf(out,"\tiload %d\n",ret);
									strcat(out,buf);//所有arith結束都要寫入
									if(index==0){//=
									}else if(index==1){//+=
									table[ret]->i_val +=i_val;
									strcat(out,"\tiadd\n");
									}else if(index==2){//-=
									table[ret]->i_val -=i_val;
									strcat(out,"\tisub\n");
									}else if(index==3){// *=
									table[ret]->i_val *=i_val;
									strcat(out,"\timul\n");
									}else if(index==4){// /=
									table[ret]->i_val /=i_val;
									strcat(out,"\tidiv\n");
									}
									sprintf(temp,"\tistore %d\n",ret);
									strcat(out, temp);		
								}
								else{//ID是int且arith是float
									if(index!=0)sprintf(out,"\tiload %d\n",ret);
									strcat(out,buf);//所有arith結束都要寫入
									strcat(out,"\tf2i\n");
									if(index==0){//=
									}else if(index==1){//+=
									table[ret]->i_val +=i_val;
									strcat(out,"\tiadd\n");
									}else if(index==2){//-=
									table[ret]->i_val -=i_val;
									strcat(out,"\tisub\n");
									}else if(index==3){// *=
									table[ret]->i_val *=i_val;
									strcat(out,"\timul\n");
									}else if(index==4){// /=
									table[ret]->i_val /=i_val;
									strcat(out,"\tidiv\n");
									}
									sprintf(temp,"\tistore %d\n",ret);
									strcat(out, temp);		
								}
								}

							}

}

