
// Generated from oberon.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "oberonParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by oberonParser.
 */
class  oberonVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by oberonParser.
   */
    virtual std::any visitIdent(oberonParser::IdentContext *context) = 0;

    virtual std::any visitQualident(oberonParser::QualidentContext *context) = 0;

    virtual std::any visitIdentdef(oberonParser::IdentdefContext *context) = 0;

    virtual std::any visitInteger(oberonParser::IntegerContext *context) = 0;

    virtual std::any visitReal(oberonParser::RealContext *context) = 0;

    virtual std::any visitNumber(oberonParser::NumberContext *context) = 0;

    virtual std::any visitConstDeclaration(oberonParser::ConstDeclarationContext *context) = 0;

    virtual std::any visitConstExpression(oberonParser::ConstExpressionContext *context) = 0;

    virtual std::any visitTypeDeclaration(oberonParser::TypeDeclarationContext *context) = 0;

    virtual std::any visitType_(oberonParser::Type_Context *context) = 0;

    virtual std::any visitArrayType(oberonParser::ArrayTypeContext *context) = 0;

    virtual std::any visitLength(oberonParser::LengthContext *context) = 0;

    virtual std::any visitIdentList(oberonParser::IdentListContext *context) = 0;

    virtual std::any visitVariableDeclaration(oberonParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitExpression(oberonParser::ExpressionContext *context) = 0;

    virtual std::any visitRelation(oberonParser::RelationContext *context) = 0;

    virtual std::any visitSimpleExpression(oberonParser::SimpleExpressionContext *context) = 0;

    virtual std::any visitAddOperator(oberonParser::AddOperatorContext *context) = 0;

    virtual std::any visitTerm(oberonParser::TermContext *context) = 0;

    virtual std::any visitMulOperator(oberonParser::MulOperatorContext *context) = 0;

    virtual std::any visitFactor(oberonParser::FactorContext *context) = 0;

    virtual std::any visitDesignator(oberonParser::DesignatorContext *context) = 0;

    virtual std::any visitSelector(oberonParser::SelectorContext *context) = 0;

    virtual std::any visitSet_(oberonParser::Set_Context *context) = 0;

    virtual std::any visitElement(oberonParser::ElementContext *context) = 0;

    virtual std::any visitExpList(oberonParser::ExpListContext *context) = 0;

    virtual std::any visitActualParameters(oberonParser::ActualParametersContext *context) = 0;

    virtual std::any visitStatement(oberonParser::StatementContext *context) = 0;

    virtual std::any visitAssignment(oberonParser::AssignmentContext *context) = 0;

    virtual std::any visitStatementSequence(oberonParser::StatementSequenceContext *context) = 0;

    virtual std::any visitIfStatement(oberonParser::IfStatementContext *context) = 0;

    virtual std::any visitWhileStatement(oberonParser::WhileStatementContext *context) = 0;

    virtual std::any visitForStatement(oberonParser::ForStatementContext *context) = 0;

    virtual std::any visitDeclarationSequence(oberonParser::DeclarationSequenceContext *context) = 0;

    virtual std::any visitModule(oberonParser::ModuleContext *context) = 0;


};

