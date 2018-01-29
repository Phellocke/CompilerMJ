#include <cstdlib>
#include <cstring>
#include "scanner.hpp"

#define BUFF_INIT_SIZE  500
#define BUFF_INC_SIZE   100

Scanner::Scanner() {
    this->in = NULL;
}

Scanner::Scanner(Source &in) {
    this->in = &in;
    this->init_buffer();
}

Scanner::~Scanner() {
    //this->free_buffer();
}

Token *Scanner::nextToken() {
	int ch;
	Token::Value tok;  // Token::Value or Error::Value

	// consume whitespace and comments
	while (isspace(this->in->peek()) || this->in->peek() == '/') { // found whitespace or comment
		if (this->in->peek() == '/')
			this->reset_buffer();

		ch = nextCh();

		if (ch == '/' && (this->in->peek() == '/' || this->in->peek() == '*')) { // comment
			ch = nextCh();
			if (ch == '/') { 	// single line comment
				ch = nextCh();
				while (ch > 0 && ch != '\n' && ch != '\r')
					ch = nextCh();
			} else { 			// multiline comment
				ch = nextCh();
				while (ch > 0 && (ch != '*' || this->in->peek() != '/'))
					ch = nextCh();
				if (ch < 0) { 
					tok = (Token::Value)Error::UnterminatedComment;
					return new Token(tok, row, col, buffer);
				} else 
					nextCh();
			}
		} else if (ch =='/') {
			this->in->unget();
			break;
		}
	}

	this->reset_buffer();		// remember row, col for lexeme
	ch = this->nextCh();		// current non-whitespace character
	if (ch < 0) { 				// EOI
		tok = Token::EOI;
	} else if (ch == '_' || isalpha(ch)) {		// keyword or identifier
		while((ch = this->in->peek()) == '_' || isalnum(ch))
			nextCh();
		if (strcmp("else", buffer) == 0) {
			tok = Token::KW_else;
		} else if (strcmp("extern", buffer) == 0) {
			tok = Token::KW_extern;
		} else if (strcmp("float", buffer) == 0) {
			tok = Token::KW_float;
		} else if (strcmp("func", buffer) == 0) {
			tok = Token::KW_func;
		} else if (strcmp("if", buffer) == 0) {
			tok = Token::KW_if;
		} else if (strcmp("return", buffer) == 0) {
			tok = Token::KW_return;
		} else if (strcmp("string", buffer) == 0) {
			tok = Token::KW_string;
		} else if (strcmp("void", buffer) == 0) {
			tok = Token::KW_void;
		} else if (strcmp("var", buffer) == 0) {
			tok = Token::KW_var;
		} else if (strcmp("while", buffer) == 0) {
			tok = Token::KW_while;
		} else {
			tok = Token::IDENT;
		}		
	} else if (isdigit(ch) || (ch == '.' && isdigit(this->in->peek()))) {	// literal float
		if (isdigit(ch)) {		// [0-9]+\.[0-9]*
			while(isdigit(this->in->peek()))
				nextCh();
			if (this->in->peek() == '.') 
				nextCh();
			while(isdigit(this->in->peek()))
				nextCh();
		} else {				// \.[0-9]+
		    nextCh();
		    while(isdigit(this->in->peek()))
		        nextCh();
		}
		tok = Token::LIT_float;
		ch = this->in->peek();
		if (ch == 'E' || ch == 'e') { 
			nextCh();
			ch = this->in->peek();
			if (ch == '+' || ch == '-')
				nextCh();
			if (isdigit(this->in->peek())) {
				while(isdigit(this->in->peek()))
					nextCh();
			} else { 			// missing exponent
				tok = (Token::Value)Error::FloatWithoutExpon;
			}
		}
	} else if (ch == '"') {		// literal string
		while((ch = nextCh()) >= 0 && ch != '"' && ch != '\n')
			/* empty */ ;
		if (ch == '"') {
			tok = Token::LIT_string;
		} else {
			tok = (Token::Value)Error::UnterminatedString;
		}
	} else if (ch == '+') {
		tok = Token::SYM_plus;
	} else if (ch == '-') {
		tok = Token::SYM_minus;
	} else if (ch == '*') {
		tok = Token::SYM_mult;
	} else if (ch == '/') {
		tok = Token::SYM_div;
	} else if (ch == '%') {
		tok = Token::SYM_mod;
	} else if (ch == '<') {
		if (this->in->peek() == '=') {
			nextCh();
			tok = Token::SYM_lesseq;
		} else {
			tok = Token::SYM_less;
		}
	} else if (ch == '>') {
		if (this->in->peek() == '=') {
			nextCh();
			tok = Token::SYM_greateq;
		} else {
			tok = Token::SYM_greater;
		}
	} else if (ch == '=') {
		if (this->in->peek() == '=') {
			nextCh();
			tok = Token::SYM_equal;
		} else {
			tok = Token::SYM_assign;
		}
	} else if (ch == '!') {
		if (this->in->peek() == '=') {
			nextCh();
			tok = Token::SYM_noteq;
		} else {
			tok = Token::SYM_not;
		}
	}else if (ch == ';') {
		tok = Token::SYM_semi;
	} else if (ch == ',') {
		tok = Token::SYM_comma;
	} else if (ch == '(') {
		tok = Token::SYM_open;
	} else if (ch == ')') {
		tok = Token::SYM_close;
	} else if (ch == '[') {
		tok = Token::SYM_opensq;
	} else if (ch == ']') {
		tok = Token::SYM_closesq;
	} else if (ch == '{') {
		tok = Token::SYM_openbr;
	} else if (ch == '}') {
		tok = Token::SYM_closebr;
	} else if (ch == '&' && this->in->peek() == '&') {
		nextCh();
		tok = Token::SYM_and;
	} else if (ch == '|' && this->in->peek() == '|') {
		nextCh();
		tok = Token::SYM_or;
	} else {
		tok = (Token::Value)Error::IllegalCharacter;
	}

	return new Token(tok, row, col, buffer);
}

void Scanner::init_buffer() {
    this->buffer = new char[BUFF_INIT_SIZE];
    this->bsize = BUFF_INIT_SIZE;
    this->reset_buffer();
}

void Scanner::reset_buffer() {
    this->buffer[0] = '\0';
    this->bindex = 0;
    this->row = in->row();
    this->col = in->col();
}

void Scanner::append_buffer(char c) {
	if (this->bindex >= this->bsize - 1) { // resize and copy
	    char *temp = new char[this->bsize+BUFF_INC_SIZE];
	    for(int i=0; i < this->bsize; ++i)
	        temp[i] = this->buffer[i];
	    delete[] this->buffer;
	    this->buffer = temp;
	    bsize += BUFF_INC_SIZE;
	}
    this->buffer[bindex] = c;
    this->buffer[++bindex] = '\0';
}

void Scanner::free_buffer() {
    delete[] this->buffer;
}

int Scanner::nextCh() {
    int c = -1;     // eof
    if (!this->in->eof()) {
        c = this->in->get();
		this->append_buffer((char)c);
    }
    return c;
}