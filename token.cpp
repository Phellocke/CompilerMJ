#include "token.hpp"

Token::Token(Token::Value val, int row, int col, string lex) {
    this->val = val;
    this->r = row;
    this->c = col;
    this->lex = lex;
}

Token::Value Token::value() {
    return val;
}

int Token::row() {
    return r;
}

int Token::col() {
    return c;
}

string Token::lexeme() {
    return lex;
}

bool Token::error() {
    return val<0;
}

static char *tokenStr(int val) {
	char *str;
	
	if (val < 0) { // process error
		switch (val) {
			case Error::IllegalCharacter: str = "Error: Illegal Char";
					break;
			case Error::UnterminatedComment: str = "Error: Unterminated Comment";
					break;
			case Error::UnterminatedString: str = "Error: Unterminated String";
					break;
			case Error::FloatWithoutExpon: str = "Error: Missing Exponent";
					break;
			default:
					str = "Internal Error";
		}
	} else { // process token
		switch (val) {
			case Token::EOI: str = "End of Input";
					break;
			case Token::IDENT: str = "Identifier";
					break;
			case Token::LIT_float: str = "Literal float";
					break;
			case Token::LIT_string: str = "Literal string";
					break;
			case Token::KW_else: str = "Keyword else";
					break;
			case Token::KW_extern: str = "Keyword extern";
					break;
			case Token::KW_float: str = "Keyword float";
					break;
			case Token::KW_func: str = "Keyword func";
					break;
			case Token::KW_if: str = "Keyword if";
					break;
			case Token::KW_return: str = "Keyword return";
					break;
			case Token::KW_string: str = "Keyword string";
					break;
			case Token::KW_void: str = "Keyword void";
					break;
			case Token::KW_var: str = "Keyword var";
					break;
			case Token::KW_while: str = "Keyword while";
					break;
			case Token::SYM_plus: str = "Symbol '+'";
					break;
			case Token::SYM_minus: str = "Symbol '-'";
					break;
			case Token::SYM_mult: str = "Symbol '*'";
					break;
			case Token::SYM_div: str = "Symbol '/'";
					break;
			case Token::SYM_mod: str = "Symbol '%'";
					break;
			case Token::SYM_less: str = "Symbol '<'";
					break;
			case Token::SYM_lesseq: str = "Symbol '<='";
					break;
			case Token::SYM_greater: str = "Symbol '>'";
					break;
			case Token::SYM_greateq: str = "Symbol '>='";
					break;
			case Token::SYM_equal: str = "Symbol '=='";
					break;
			case Token::SYM_noteq: str = "Symbol '!='";
					break;
			case Token::SYM_assign: str = "Symbol '='";
					break;
			case Token::SYM_semi: str = "Symbol ';'";
					break;
			case Token::SYM_comma: str = "Symbol ','";
					break;
			case Token::SYM_open: str = "Symbol '('";
					break;
			case Token::SYM_close: str = "Symbol ')'";
					break;
			case Token::SYM_opensq: str = "Symbol '['";
					break;
			case Token::SYM_closesq: str = "Symbol ']'";
					break;
			case Token::SYM_openbr: str = "Symbol '{'";
					break;
			case Token::SYM_closebr: str = "Symbol '}'";
					break;
			default:
					str = "Internal Error";
		}
	}
	
	return str;
}

// TODO: add code to print string to identify token, i.e., tokenStr(t.val)
std::ostream& operator<<(std::ostream& out, const Token& t) {
    return out << "<" << tokenStr(t.val) << " (" << t.r << "," << t.c << "):\"" << t.lex << "\">";
}