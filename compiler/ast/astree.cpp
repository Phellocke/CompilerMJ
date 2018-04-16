#include "astree.h"
#include "visitor.h"	// because of circular references with ASTree, this is placed here

void ExprUnary::accept(ASTvisitor &v) {
	v.visit(this);
}

void ExprBinary::accept(ASTvisitor &v) {
	v.visit(this);
}

void ExprVar::accept(ASTvisitor &v) {
	v.visit(this);
}

void ExprLit::accept(ASTvisitor &v) {
	v.visit(this);
}

void ExprCall::accept(ASTvisitor &v) {
	v.visit(this);
}

void StmtAssign::accept(ASTvisitor &v) {
	v.visit(this);
}

void StmtIf::accept(ASTvisitor &v) {
	v.visit(this);
}

void StmtWhile::accept(ASTvisitor &v) {
	v.visit(this);
}

void StmtReturn::accept(ASTvisitor &v) {
	v.visit(this);
}

void StmtCompound::accept(ASTvisitor &v) {
	v.visit(this);
}

void DeclVar::accept(ASTvisitor &v) {
	v.visit(this);
}

void DeclFunc::accept(ASTvisitor &v) {
	v.visit(this);
}

void ASTree::accept(ASTvisitor &v) {
	v.visit(this);
}
