#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <string>

#define MAX_SYM_LEN 33
#define MAX_TAB_SIZE 107

using namespace std;

class Symbol {
    public:
        Symbol() { }
        Symbol(string lex) { this->lexeme = lex; }
        string lexeme;  // identifier
};

class SymTab {
    public:
        SymTab();
        ~SymTab();
        void dump();
        void openScope();
        void closeScope();
        bool isDefined(string);
        bool isInScope(string);
        bool define(Symbol);
        bool redefine(Symbol);
        Symbol *lookup(string);

    private:
        int scope;
        class entry {
            public:
                Symbol sym;
                int scope;
                entry *next;
        } *table[MAX_TAB_SIZE];
        entry *searchTable(int scope, string sym);
};

#endif
