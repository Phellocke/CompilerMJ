// codegen.cpp
#include "codegen.h"

void CodeGen::visit(ASTree *node) {
    // open output file
	// write prolog
	// generate global variables
	// generate functions
	// write postscript
	// close output file
}

void CodeGen::visit(DeclFunc *node) {

}

void CodeGen::visit(DeclVar *node) {

}

void CodeGen::visit(StmtAssign *node) {

}

void CodeGen::visit(StmtIf *node) {

}

void CodeGen::visit(StmtWhile *node) {

}

void CodeGen::visit(StmtReturn *node) {

}

void CodeGen::visit(StmtCompound *node) {

}

void CodeGen::visit(ExprUnary *node) {

}

void CodeGen::visit(ExprBinary *node) {

}

void CodeGen::visit(ExprVar *node) {

}

void CodeGen::visit(ExprLit *node) {

}

void CodeGen::visit(ExprCall *node) {

}			
