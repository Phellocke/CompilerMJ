/* parser */
#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "source.hpp"
#include "scanner.hpp"

class Parser {

    public:
        Parser(Source &in);
        int parse();
        
    private:
        Scanner scanner;
        Token *lookahead; // TODO check class semantics and pointer
        Token::Value la;  // Token value of the lookahead
        void panic(string msg);
        void match(Token::Value t, string msg);
        void TranslationUnit();
        void Declaration();
        void Function();
        void TypeSpecifier();
        void Parameter();
        void CompoundStatement();
        void Statement();
        void Assignment();
        void SelectionStatement();
        void RepetitionStatement();
        void ReturnStatement();
        void Expression();
        void AndExpression();
        void RelationExpression();
        void SimpleExpression();
        void Term();
        void Factor();
        void Value();
};

#endif