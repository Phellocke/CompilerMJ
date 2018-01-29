#include "parser.hpp"
#include "token.hpp"

void Parser::panic(string msg) {
	cout << "ERROR(" << lookahead->row() << "," << lookahead->col() 
		 << " \"" << lookahead->lexeme() << "\""
		 << "): " << msg << endl;
	exit(1);
}

Parser::Parser(Source &in) {
    this->scanner = Scanner(in);
}

int Parser::parse() {
    int errors = 0;
    lookahead = scanner.nextToken();
	la = lookahead->value();

	TranslationUnit();
	match(Token::EOI, "expecting end of file");	

    return errors;
}

void Parser::match(Token::Value t, string msg) {
	if (lookahead->value() == t) {
		lookahead = scanner.nextToken();
		la = lookahead->value();
	} else 
		panic(msg);
}

void Parser::TranslationUnit() {
	if (la == Token::KW_extern || la == Token::KW_var
		|| la == Token::KW_func || la == Token::EOI) {
		while (la == Token::KW_extern || la == Token::KW_var
			   || la == Token::KW_func) {
			if (la == Token::KW_extern) {
				match(Token::KW_extern, "expecting end of input");
			}
			if (la == Token::KW_var) {
				Declaration();
			} else if (la == Token::KW_func) {
				Function();
			} else
				panic("expecting variable or function declaration");
		}
	} else
		panic("expecting variable or function declaration");
}

void Parser::Declaration() {
	if (la == Token::KW_var) {
		match(Token::KW_var, "expecting variable declaration");
		TypeSpecifier();
		match(Token::IDENT, "expecting identifier");
		while (la == Token::SYM_comma) {
			match(Token::SYM_comma, "expecting ','");
			match(Token::IDENT, "expecting identifier");
		}
		match(Token::SYM_semi, "expecting ';'");
	} else 
		panic("expecting variable declaration");
}

void Parser::Function() {
	if (la == Token::KW_func) {
		match(Token::KW_func, "expecting function declaration");
		if (la == Token::KW_float || la == Token::KW_string) {
			TypeSpecifier();
		}
		match(Token::IDENT, "expecting identifier");
		match(Token::SYM_open, "expecting '('");
		if (la == Token::KW_float || la == Token::KW_string) {
			Parameter();
			match(Token::IDENT, "expecting identifier");
			while (la == Token::SYM_comma) {
				match(Token::SYM_comma, "expecting ','");
				Parameter();
				match(Token::IDENT, "expecting identifier.");
			}
		}
		match(Token::SYM_close, "expecting ')'");
		if (la == Token::SYM_openbr) {
			CompoundStatement();
		} else if (la == Token::SYM_semi) {
			match(Token::SYM_semi, "expecting ';'");
		} else
			panic("expecting compound statement or ';'");
	} else
		panic("expecting function declaration");
}

void Parser::TypeSpecifier() {
	if (la == Token::KW_float) 
	{
		match(Token::KW_float, "expecting float");	
	} 
	else if (la == Token::KW_string)
	{
		match(Token::KW_string, "expecting string");
	}
	else
		panic("expecting float or string");
}

void Parser::Parameter() {
	if (la == Token::KW_string || la == Token::KW_float) 
	{
		TypeSpecifier();
	} else if (la == Token::IDENT) 
	{
		match(Token::IDENT, "expecting identifier");
	}
	else
		panic("expecting string, float or identifier");
}

void Parser::CompoundStatement() {
	if (la == Token::SYM_openbr) 
	{
		match(Token::SYM_openbr, "expecting '{'");
		while (la != Token::SYM_closebr)
		{
			if (la == Token::KW_var) {
				Declaration();
			
			}
			if (la == Token::SYM_plus   || la == Token::SYM_minus 
				|| la == Token::SYM_not || la == Token::SYM_open 
				|| la == Token::IDENT   || la == Token::LIT_float 
				|| la == Token::LIT_string || la == Token::SYM_openbr
				|| la == Token::KW_if || la == Token::KW_while
				|| la == Token::KW_return || la == Token::SYM_semi)
			{
				Statement();
			}
		}
		match(Token::SYM_closebr, "expecting '}'");

	} 
	else  {
		panic("Expecting compound statment");
	}
}

void Parser::Statement() {
	if (   la == Token::SYM_semi  || la == Token::SYM_plus
	    || la == Token::SYM_minus || la == Token::SYM_not
	    || la == Token::SYM_open  || la == Token::IDENT
	    || la == Token::LIT_float || la == Token::LIT_string) {
		Assignment();
	} else if (la == Token::SYM_openbr) {
		CompoundStatement();
	} else if (la == Token::KW_if) {
		SelectionStatement();
	} else if (la == Token::KW_while) {
		RepetitionStatement();
	} else if (la == Token::KW_return) {
		ReturnStatement();
	} else 
		panic("expecting a statement");
}

void Parser::Assignment() {
	if (   la == Token::SYM_plus || la == Token::SYM_minus 
		|| la == Token::SYM_not  || la == Token::LIT_float 
		|| la == Token::LIT_string || la == Token::IDENT
		|| la == Token::SYM_mult || la == Token::SYM_div
		|| la == Token::SYM_mod)
	{
		Expression();
	} 
	if (la == Token::SYM_assign)
	{
		match(Token::SYM_assign, "expecting '='");
		if (   la == Token::SYM_plus  || la == Token::SYM_minus 
			|| la == Token::SYM_not   || la == Token::LIT_float 
			|| la == Token::LIT_string || la == Token::SYM_mult 
			|| la == Token::SYM_div   || la == Token::SYM_mod
			|| la == Token::IDENT)
		{
			Expression();
		}
	}
	if (la == Token::SYM_semi)
	{
		match(Token::SYM_semi, "expecting ';'");
	}
	else 
	{
		panic("expecting assignment");
	}
}

void Parser::SelectionStatement() {
	if (la == Token::KW_if) 
	{
		match(Token::KW_if, "expecting if statment");
		if (la == Token::SYM_open)
		{
			match(Token::SYM_open, "expecting '('");
			if (   la == Token::SYM_plus  || la == Token::SYM_minus 
				|| la == Token::SYM_not   || la == Token::LIT_float 
				|| la == Token::LIT_string || la == Token::IDENT
				|| la == Token::SYM_mult || la == Token::SYM_div
				|| la == Token::SYM_mod)
			{
			Expression();
			match(Token::SYM_close, "expecting ')'");
			Statement();
			if (la == Token::KW_else)
			{
				match(Token::KW_else, "expected else statement");
				Statement();
			}
			}

		}
		else
			panic("expecting '('");
	} else {
		panic("expecting if statement");
	}
}

void Parser::RepetitionStatement() {
	if (la == Token::KW_while) {
		match(Token::KW_while, "expecting 'while'");
		match(Token::SYM_open, "expecting '('");
		if (   la == Token::SYM_plus  || la == Token::SYM_minus 
				|| la == Token::SYM_not   || la == Token::LIT_float 
				|| la == Token::LIT_string || la == Token::IDENT
				|| la == Token::SYM_mult || la == Token::SYM_div
				|| la == Token::SYM_mod)
		{
			Expression();
			match(Token::SYM_close, "expecting ')'");
			Statement(); 
		} 
		else 
		{
			panic("expecting while loop");
		}
	}
}

void Parser::ReturnStatement() {
	if (la == Token::KW_return) 
	{
		match(Token::KW_return, "extecting retun statment");
		if (   la == Token::SYM_plus  || la == Token::SYM_minus 
				|| la == Token::SYM_not   || la == Token::LIT_float 
				|| la == Token::LIT_string || la == Token::SYM_mult 
				|| la == Token::SYM_div || la == Token::SYM_mod
				|| la == Token::IDENT)
		{
			Expression();
		}
		if(la == Token::SYM_semi)
		{
			match(Token::SYM_semi, "expecting ';'");
		}
	
	} 
	else {
		panic("expecting return statment.");
	
	}
}

void Parser::Expression() {
	if (la == Token::SYM_plus      || la == Token::SYM_minus 
		|| la == Token::SYM_not    || la == Token::LIT_float 
		|| la == Token::LIT_string || la == Token::IDENT
		|| la == Token::SYM_mult || la == Token::SYM_div
		|| la == Token::SYM_mod)
	{
		AndExpression();
		while(la == Token::SYM_or)
		{
			match(Token::SYM_or, "expecting '||'");
			AndExpression();
		}

	
	} else {
		panic("expecting expression");
	}
}

void Parser::AndExpression() {
	if (la == Token::SYM_plus      || la == Token::SYM_minus 
		|| la == Token::SYM_not    || la == Token::LIT_float 
		|| la == Token::LIT_string || la == Token::IDENT
		|| la == Token::SYM_mult || la == Token::SYM_div
		|| la == Token::SYM_mod)
	{
		RelationExpression();
		while(la == Token::SYM_and)
		{
			match(Token::SYM_and, "expecting '&&'");
			AndExpression();
		}
	
	} else {
		panic("expecting and expression");
	}
}

void Parser::RelationExpression() {
	if (la == Token::SYM_plus      || la == Token::SYM_minus 
		|| la == Token::SYM_not    || la == Token::LIT_float 
		|| la == Token::LIT_string || la == Token::IDENT
		|| la == Token::SYM_mult || la == Token::SYM_div
		|| la == Token::SYM_mod)
	{
		SimpleExpression();
		if(la == Token::SYM_lesseq)
		{
			match(Token::SYM_lesseq, "expecting '<='");
			SimpleExpression();
		}
		else if(la == Token::SYM_less)
		{
			match(Token::SYM_less, "expecting '<'");
			SimpleExpression();
		}
		else if(la == Token::SYM_greateq)
		{
			match(Token::SYM_greateq, "expecting '>='");
			SimpleExpression();
		}
		else if(la == Token::SYM_greater)
		{
			match(Token::SYM_greater, "expecting '>'");
			SimpleExpression();
		}
		else if(la == Token::SYM_equal)
		{
			match(Token::SYM_equal, "expecting '=='");
			SimpleExpression();
		}
		else if(la == Token::SYM_noteq)
		{
			match(Token::SYM_noteq, "expecting '!='");
			SimpleExpression();
		}
	
	} else {
		panic("expecting a relational expression");
	}
}

void Parser::SimpleExpression() {
	if (la == Token::SYM_plus      || la == Token::SYM_minus 
		|| la == Token::SYM_not    || la == Token::LIT_float 
		|| la == Token::LIT_string || la == Token::IDENT
		|| la == Token::SYM_mult || la == Token::SYM_div
		|| la == Token::SYM_mod)
	{
		Term();
		while ( la == Token::SYM_plus || la == Token::SYM_minus)
		{
			if (la == Token::SYM_plus)
			{
				match(Token::SYM_plus, "expecting '+'");
				Term();
			}
			else if (la == Token::SYM_minus)
			{
				match(Token::SYM_minus, "expecting '-'");
				Term();
			}
		}
	} else {
		panic("expecting simple expression");
	}
}

void Parser::Term() {
	if (la == Token::SYM_plus      || la == Token::SYM_minus 
		|| la == Token::SYM_not    || la == Token::LIT_float 
		|| la == Token::LIT_string || la == Token::IDENT)
	{
		Factor();
		while(la == Token::SYM_mult || la == Token::SYM_div 
			|| la == Token::SYM_mod)
		{
			if ( la == Token::SYM_mult)
			{
				match(Token::SYM_mult, "expecting '*'");
				Factor();
			}
			else if (la == Token::SYM_div)
			{
				match(Token::SYM_div, "expecting '/'");
				Factor();
			}
			else if (la == Token::SYM_mod)
			{
				match(Token::SYM_mod, "expecting '%'");
				Factor();
			}
		}
	
	} else {
		panic("execting term");
	}
}

void Parser::Factor() {
	if (la == Token::SYM_plus)
	{
		match(Token::SYM_plus, "expecting '+'");
	}
	if (la == Token::SYM_minus)
	{
		match(Token::SYM_minus, "expecting '-'");
	}
	if (la == Token::SYM_not)
	{
		match(Token::SYM_not, "expecting  '!'");
	} 
	if (la == Token::SYM_open || la == Token::IDENT
		|| la == Token::LIT_float || la == Token::LIT_string)
	{
		Value();
	}
	else {
		panic("expecting Factor");
	}
}

void Parser::Value() {
	if (la == Token::SYM_open)
	{
		match(Token::SYM_open, "expecting ')'");
		Expression();
		match(Token::SYM_close, "expecting ')'");
	
	}
	else if (la == Token::IDENT)
	{
		match(Token::IDENT, "expecting identifier");
		if (la == Token::SYM_open)
		{
			match(Token::SYM_open, "expecting '('");
			Expression();
			while(la == Token::SYM_comma)
			{
				match(Token::SYM_comma, "expecting ','");
				Expression();
			}
			if (la == Token::SYM_close)
			{
				match(Token::SYM_close, "expecting ')'");
			}
		}
	}
	else if (la == Token::LIT_float)
	{
		match(Token::LIT_float, "execting a float");
	}
	else if (la == Token::LIT_string)
	{
		match(Token::LIT_string, "expecting a string");
	}
	 else {
	 	panic("expecting a value");
	}
	}

