// k7scan1.cpp : Definiert den Einsprungpunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#pragma warning(disable:4786)
#include <string>
#include <map>


using namespace std;

#define	Getc(s)			getc(s)
#define	Ungetc(c)		{ungetc(c,IP_Input); ugetflag=1;}


/*
 *	Lexical analyzer states.
 */
enum lexstate{L_START,L_INT,L_IDENT,L_STRING,L_STRING2,
		L_COMMENT,L_TEXT_COMMENT,L_LINE_COMMENT,L_END_TEXT_COMMENT};
enum parsestate{P_START,P_ARTICLE,P_COSTS,P_DISCOUNT,P_COSTS_PRICE,P_COSTS_WARE_GROUP,P_DISCOUNT_PRICE,P_DISCOUNT_WARE_GROUP};

const int STRING1=3;
const int IDENTIFIER=4;
const int INTEGER1=5;
const int ARTICLE=300;
const int COSTS=301;
const int DISCOUNT=302;
//const int CPU=303;
//const int WARE_GROUP=304;



class CParser
{
public:

	string yytext;								//input buffer
	struct tyylval{								//value return
		string s;								//structure
		int i;
	}yylval;
	FILE *IP_Input;								//Input File
	FILE *IP_Error;								//Error Output
	FILE *IP_List;								//List Output
	int  IP_LineNumber;							//Line counter
	int ugetflag;								//checks ungets
	int prflag;									//controls printing
	map<string,int> IP_Token_table;				//Tokendefinitions
	map<int,string> IP_revToken_table;			//reverse Tokendefinitions


	int CParser::yyparse();	//parser
	int CParser::yylex();						//lexial analyser
	void CParser::yyerror(char *ers);			//error reporter
	int CParser::IP_MatchToken(string &tok);	//checks the token
	void CParser::InitParse(FILE *inp,FILE *err,FILE *lst);
	void CParser::pr_tokentable();				//test output for tokens
	void CParser::IP_init_token_table();		//loads the tokens
	void CParser::Load_tokenentry(string str,int index);//load one token
	void CParser::PushString(char c);			//Used for dtring assembly
	CParser(){IP_LineNumber = 1;ugetflag=0;prflag=0;};	//Constructor
};