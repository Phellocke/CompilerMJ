#include <cstring>
#include <cstdio>
#include "symbols.hpp"

#define ANY_SCOPE   -1

static int hashSym(const char *s) {
    return (s == NULL)?0:(7*s[0]+41*s[strlen(s)-1])%MAX_TAB_SIZE;
}

SymTab::SymTab() {
    this->scope = 0;
    for (int i=0;i<MAX_TAB_SIZE;++i)
        table[i] = NULL;
}

SymTab::~SymTab() {
	while (this->scope >= 0)
		this->closeScope();
}

void SymTab::dump() {
    fprintf(stderr, "SCOPE: %d\n", this->scope);
    entry *ent;
    for (int i=0;i<MAX_TAB_SIZE;++i) {
        ent = this->table[i];
        if (ent != NULL) {
            while(ent != NULL) {
                fprintf(stderr, "ID(%d): \"%s\"; ", ent->scope, ent->sym.lexeme.c_str());
                ent = ent->next;
            }
            fprintf(stderr, "\n");
        }
    }
}

void SymTab::openScope() {
    ++(this->scope);
}

void SymTab::closeScope() {
    entry *next;
    for (int i=0;i<MAX_TAB_SIZE;++i)
        while(this->table[i]!=NULL && this->table[i]->scope==this->scope) {
            next = table[i]->next;
            delete table[i];
            table[i] = next;
        }
    --(this->scope);
}

// returns pointer to entry if found, NULL otherwise
SymTab::entry *SymTab::searchTable(int scope, string sym) {
    int i = hashSym(sym.c_str());

    entry *ent = this->table[i];
    while (ent != NULL && ent->scope >= scope) {
        if (ent->sym.lexeme.compare(sym)==0 && (scope == this->scope || scope == ANY_SCOPE))
            break;
        ent = ent->next;
    }

	return ent!=NULL&&ent->scope<scope?NULL:ent;
}

// returns true if found, false otherwise
bool SymTab::isDefined(string sym) {
	return this->searchTable(ANY_SCOPE, sym) != NULL;
}

bool SymTab::isInScope(string sym) {
    return this->searchTable(this->scope, sym) != NULL;
}

// returns true if sym successful, false when sym already defined in current scope
bool SymTab::define(Symbol sym) {
	if (searchTable(this->scope, sym.lexeme) == NULL) {
		int i = hashSym(sym.lexeme.c_str());
		entry *ent = new entry();
		ent->sym = sym;
		ent->scope = this->scope;
		ent->next = this->table[i];
		this->table[i] = ent;
		return true;
	}
	return false;
}

// returns true if sym is found in any scope, false otherwise
bool SymTab::redefine(Symbol sym) {
	entry *ent = searchTable(ANY_SCOPE, sym.lexeme);
	if (ent != NULL)
		ent->sym = sym;
	return ent != NULL;
}

// returns the symbol definition if found in any scope, NULL otherwise
Symbol *SymTab::lookup(string sym) {
	entry *ent = searchTable(ANY_SCOPE, sym);
	return ent!=NULL?&(ent->sym):NULL;
}
