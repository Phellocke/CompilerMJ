#include <iostream>
#include <string>
#include <list>
#include "astree.h"
#include "astjson.h"

using namespace std;

int main() {

	ASTree *ast;
	ASTjson JSON;
		
	list<DeclVar*> vdecls;
	list<string> vars;
	vars.push_back("_i"); vars.push_back("x1");
	BaseType t;
	t.type = Scalar::NUMBER;
	t.refs = 3;
	vdecls.push_back(new DeclVar(t,vars)); 
	list<DeclFunc*> funcs;
	funcs.push_back(new DeclFunc("g12", t, vdecls, new StmtCompound()));
	ast = new ASTree(vdecls,funcs);
	ast->accept(JSON);
	cout << JSON.toString() << endl;
	
	return 0;
}