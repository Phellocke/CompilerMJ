#ifndef __ASTJSON__
#define __ASTJSON__

#include <string>
#include "astree.h"
#include "visitor.h"

using namespace std;

class ASTjson: public ASTvisitor {
	private:
		string JSON;
		int tabwidth = 2;
		int currenttab = 0;
		void dedent() { if (currenttab >= tabwidth) currenttab -= tabwidth; }
		void indent() { currenttab += tabwidth; }
		string tab(string s) { return string(currenttab,' ')+s; }
	public:
		string toString() { return JSON; }
		void visit(ASTree *node);
		void visit(DeclFunc *node);
		void visit(DeclVar *node);
		void visit(StmtAssign *node);
		void visit(StmtIf *node);
		void visit(StmtWhile *node);
		void visit(StmtReturn *node);
		void visit(StmtCompound *node);
		void visit(ExprUnary *node);
		void visit(ExprBinary *node);
		void visit(ExprVar *node);
		void visit(ExprLit *node);
		void visit(ExprCall *node);			
};
#endif