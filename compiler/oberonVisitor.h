
// Generated from oberon.g4 by ANTLR 4.13.1

#pragma once


#include <llvm/IR/Value.h>

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
    virtual std::string visitIdent(oberonParser::IdentContext *context) = 0;

    virtual std::string visitQualident(oberonParser::QualidentContext *context) = 0;

    virtual std::string visitIdentdef(oberonParser::IdentdefContext *context) = 0;

    virtual llvm::Value* visitInteger(oberonParser::IntegerContext *context) = 0;

    virtual llvm::Value* visitReal(oberonParser::RealContext *context) = 0;

    virtual llvm::Value* visitNumber(oberonParser::NumberContext *context) = 0;

    virtual std::any visitConstDeclaration(oberonParser::ConstDeclarationContext *context) = 0;

    virtual llvm::Value* visitConstExpression(oberonParser::ConstExpressionContext *context) = 0;

    virtual std::any visitTypeDeclaration(oberonParser::TypeDeclarationContext *context) = 0;

    virtual llvm::Type* visitType_(oberonParser::Type_Context *context) = 0;

    virtual llvm::Type* visitArrayType(oberonParser::ArrayTypeContext *context) = 0;

    virtual llvm::Value* visitLength(oberonParser::LengthContext *context) = 0;

    virtual std::vector<std::string> visitIdentList(oberonParser::IdentListContext *context) = 0;

    virtual std::any visitVariableDeclaration(oberonParser::VariableDeclarationContext *context) = 0;

    virtual llvm::Value* visitExpression(oberonParser::ExpressionContext *context) = 0;

    virtual std::string visitRelation(oberonParser::RelationContext *context) = 0;

    virtual llvm::Value* visitSimpleExpression(oberonParser::SimpleExpressionContext *context) = 0;

    virtual std::string visitAddOperator(oberonParser::AddOperatorContext *context) = 0;

    virtual std::any visitTerm(oberonParser::TermContext *context) = 0;

    virtual std::string visitMulOperator(oberonParser::MulOperatorContext *context) = 0;

    virtual llvm::Value* visitFactor(oberonParser::FactorContext *context) = 0;

    virtual std::any visitDesignator(oberonParser::DesignatorContext *context) = 0;

    virtual std::any visitSelector(oberonParser::SelectorContext *context) = 0;

    virtual std::any visitSet_(oberonParser::Set_Context* context) = 0;

    virtual std::any visitElement(oberonParser::ElementContext *context) = 0;

    virtual llvm::Value* visitExpList(oberonParser::ExpListContext *context) = 0;

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

