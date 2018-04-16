#ifndef __ASTREE__
#define __ASTREE__
#include <list>
#include <string>
#include "types.h"

using namespace std;

class ASTvisitor;  // forward reference for visitor class

class ASTNode {
	public:
		virtual void accept(class ASTvisitor &v) = 0;
};

class Expression: public ASTNode {  // ensures only expression nodes are used
	public:
		BaseType derivedType;
		virtual void accept(class ASTvisitor &v) = 0;
};

class ExprUnary: public Expression {
	public:
		//ExprUnary(Operator, Expression*);
		Operator op;
		Expression *expr;
		void accept(class ASTvisitor &v);
};

class ExprBinary: public Expression {
	public:
		//ExprBinary(Operator, Expression*, Expression*);
		Operator op;
		Expression *lhs;
		Expression *rhs;
		void accept(class ASTvisitor &v);
};

class ExprVar: public Expression {
	public:
		//ExprVar(string);
		string name;
		BaseType type;
		void accept(class ASTvisitor &v);
};

class ExprLit: public Expression {
	public:
		//ExprLit(string);
		string lexeme;
		BaseType type;
		void accept(class ASTvisitor &v);
};

class ExprCall: public Expression {
	public:
		//ExprCall(string, list<Expression*>);
		string name;
		BaseType type;
		list<Expression*> params;
		void accept(class ASTvisitor &v);
};

class Statement: public ASTNode {  // ensures that only statement nodes are used
	public:
		virtual void accept(class ASTvisitor &v) = 0;
};

class StmtAssign: public Statement {
	public:
		//StmtAssign(Expression*, Expression*);
		Expression *lhs;
		Expression *rhs;
		void accept(class ASTvisitor &v);
};

class StmtIf: public Statement {
	public:
		//StmtIf(Expression*, Statement*, Statement*);
		Expression *condition;
		Statement *thenPart;
		Statement *elsePart;
		void accept(class ASTvisitor &v);
};

class StmtWhile: public Statement {
	public:
		//StmtWhile(Expression*, Statement*);
		Expression *condition;
		Statement *body;
		void accept(class ASTvisitor &v);
};

class StmtReturn: public Statement {
	public:
		//StmtReturn(Expression*);
		Expression *returnValue;
		void accept(class ASTvisitor &v);
};

class DeclVar: public ASTNode {
	public:
		DeclVar(BaseType t, list<string> v) { type = t; vars = v; }
		BaseType type;
		list<string> vars;		
		void accept(class ASTvisitor &v);
};

class StmtCompound: public Statement {
	public:
		//StmtCompound(list<Statement*>, list<DeclVar*>);
		list<DeclVar*> locals;
		list<Statement*> statements;
		void accept(class ASTvisitor &v);
};

class DeclFunc: public ASTNode {
	public:
		DeclFunc(string n, BaseType r, list<DeclVar*> p, StmtCompound* b) { name = n; rtype = r; params = p; body = b; } 
		string name;
		BaseType rtype;
		list<DeclVar*> params;
		StmtCompound *body;
 		void accept(class ASTvisitor &v);
};

class ASTree: public ASTNode {
	public:
		ASTree(list<DeclVar*> g, list<DeclFunc*> f) { globals = g; funcs = f;}
		list<DeclVar*> globals;
		list<DeclFunc*> funcs;
		void accept(class ASTvisitor &v);
};

#endif