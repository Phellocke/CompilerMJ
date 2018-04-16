// astprint.cpp
#include "astjson.h"

using namespace std;

void ASTjson::visit(ASTree *node) {
	JSON = "{ \"node\": \"ASTree\",\n"; indent();
	JSON += tab("\"vars\": [\n"); indent();
	list<DeclVar*>::iterator var = node->globals.begin();
	JSON += tab("{ "); indent();
	(*var)->accept(*this);
	dedent(); JSON += tab("}");
	for (++var; var != node->globals.end(); ++var) {
		JSON += ",\n" + tab("{ ");
		(*var)->accept(*this);
		dedent(); JSON += tab("}");
	}
	JSON += "\n"; dedent();
	JSON += tab("],\n"); 
	JSON += tab("\"funcs\": [\n"); indent();
	list<DeclFunc*>::iterator func = node->funcs.begin();
	JSON += tab("{ "); indent();
	(*func)->accept(*this);
	dedent(); JSON += tab("}");
	for (++func; func != node->funcs.end(); ++func) {
		JSON += ",\n" + tab("{ "); indent();
	  	(*func)->accept(*this);
		dedent(); JSON += tab("}");
	}
	JSON += "\n"; dedent();
	JSON += tab("]\n"); dedent();
	JSON += tab("}");
}

void ASTjson::visit(DeclFunc *node) {
	JSON += "\"node\": \"DeclFunc\",\n";
	JSON += tab("\"name\": \"" + node->name + "\",\n"); 
	JSON += tab("\"rtype\": \"" + node->rtype.toString() + "\",\n"); 
	JSON += tab("\"params\": [\n"); indent();
	list<DeclVar*>::iterator param = node->params.begin();
	JSON += tab("{ "); indent();
	(*param)->accept(*this);
	dedent(); JSON += tab("}");
	for (++param; param != node->params.end(); ++param) {
		JSON += ",\n" + tab("{ "); indent();
		(*param)->accept(*this);
		dedent(); JSON += tab("}");
	}
	JSON += tab("\n"); dedent();
	JSON += tab("],\n");
	JSON += tab("\"body\": {\n"); indent(); JSON += tab("");
	node->body->accept(*this); dedent();
	JSON += tab("}\n");
}

void ASTjson::visit(DeclVar *node) {
	JSON += "\"node\": \"DeclVar\",\n";
	JSON += tab("\"type\": \"" + node->type.toString() + "\",\n");
	list<string>::iterator var = node->vars.begin();
	JSON += tab("\"vars\": [ "); indent();
	JSON += "\"" + *var + "\"";
	for (++var; var != node->vars.end(); ++var)
		JSON += ", \"" + *var + "\"";
	dedent();
	JSON += " ]\n";
}

void ASTjson::visit(StmtAssign *node) {
	JSON += "{ \"node\": \"StmtAssign\", \"lhs\": { }, \"rhs\": { } }";
}

void ASTjson::visit(StmtIf *node) {
	JSON += "{ \"node\": \"StmtIf\", \"condition\": { }, \"thenPart\": { }, \"elsePart\": { } }";
}

void ASTjson::visit(StmtWhile *node) {
	JSON += "{ \"node\": \"StmtWhile\", \"condition\": { }, \"body\": { } }";
}

void ASTjson::visit(StmtReturn *node) {
	JSON += "{ \"node\": \"StmtReturn\", \"returnValue\": { } }";
}

void ASTjson::visit(StmtCompound *node) {
	JSON += "\"node\": \"StmtCompound\",\n";
	JSON += tab("\"locals\": [ ],\n");
	JSON += tab("\"statements\": [ ]\n");
}

void ASTjson::visit(ExprUnary *node) {
	JSON += "{ \"node\": \"ExprUnary\", \"op\": { }, \"expr\": { } }";
}

void ASTjson::visit(ExprBinary *node) {
	JSON += "{ \"node\": \"ExprBinary\", \"op\": { }, \"lhs\": { }, \"rhs\": { } }";
}

void ASTjson::visit(ExprVar *node) {
	JSON += "{ \"node\": \"ExprVar\", \"name\": \"\" }";
}

void ASTjson::visit(ExprLit *node) {
	JSON += "{ \"node\": \"ExprLit\", \"lexeme\": \"\" }";
}

void ASTjson::visit(ExprCall *node) {
	JSON += "{ \"node\": \"ExprCall\", \"name\": \"\", \"params\": [ ] }";
}			