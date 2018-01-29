#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <iostream>
#include <string>

#include "error.hpp"

using namespace std;

class Token {

    public:
        enum Value {
            EOI,            // End-of-input
            IDENT,          // identifiers

            // literals
            LIT_float,
            LIT_string,
            
            // keywords
            KW_else, 
            KW_extern,
            KW_float,
            KW_func,
            KW_if,
            KW_return,
            KW_string,
            KW_void,
            KW_var,
            KW_while,

            // symbols
            SYM_plus,		//+ 
            SYM_minus,		//- 
            SYM_mult,		//* 
            SYM_div,		/// 
            SYM_mod,        //%
            SYM_less,		//< 
            SYM_lesseq,		//<= 
            SYM_greater,	//> 
            SYM_greateq,	//>= 
            SYM_equal,		//== 
            SYM_noteq,		//!= 
            SYM_assign,		//= 
            SYM_semi,		//; 
            SYM_comma,		//, 
            SYM_open,		//( 
            SYM_close,		//) 
            SYM_opensq,		//[ 
            SYM_closesq,	//] 
            SYM_openbr,		//{ 
            SYM_closebr,	//}
            SYM_not,		//!
            SYM_and,		//&&
            SYM_or,			//||
        };

        Token(Token::Value val, int row, int col, string lex);
        Token::Value value();
        int row();
        int col();
        string lexeme();
        bool error();


    private:
        Token::Value val;              // hold Token.value or Error.value
        int r,c;             // row, col of lexeme matched
        string lex;          // lexeme matched

        friend std::ostream& operator<<(std::ostream&, const Token&);
};

#endif