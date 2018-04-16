#ifndef __ASTVISITOR__
#define __ASTVISITOR__

#include "astree.h"

class ASTvisitor {
	public:
		virtual void visit(ASTree *node) = 0;
		virtual void visit(DeclFunc *node) = 0;
		virtual void visit(DeclVar *node) = 0;
		virtual void visit(StmtAssign *node) = 0;
		virtual void visit(StmtIf *node) = 0;
		virtual void visit(StmtWhile *node) = 0;
		virtual void visit(StmtReturn *node) = 0;
		virtual void visit(StmtCompound *node) = 0;
		virtual void visit(ExprUnary *node) = 0;
		virtual void visit(ExprBinary *node) = 0;
		virtual void visit(ExprVar *node) = 0;
		virtual void visit(ExprLit *node) = 0;
		virtual void visit(ExprCall *node) = 0;			
};
#endif