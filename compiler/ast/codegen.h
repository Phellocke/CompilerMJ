#ifndef __CODEGEN__
#define __CODEGEN__
#include "astree.h"
#include "visitor.h"

class CodeGen: public ASTvisitor {
	public:
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