
// Generated from oberon.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "oberonParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by oberonParser.
 */
class  oberonListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterIdent(oberonParser::IdentContext *ctx) = 0;
  virtual void exitIdent(oberonParser::IdentContext *ctx) = 0;

  virtual void enterQualident(oberonParser::QualidentContext *ctx) = 0;
  virtual void exitQualident(oberonParser::QualidentContext *ctx) = 0;

  virtual void enterIdentdef(oberonParser::IdentdefContext *ctx) = 0;
  virtual void exitIdentdef(oberonParser::IdentdefContext *ctx) = 0;

  virtual void enterInteger(oberonParser::IntegerContext *ctx) = 0;
  virtual void exitInteger(oberonParser::IntegerContext *ctx) = 0;

  virtual void enterReal(oberonParser::RealContext *ctx) = 0;
  virtual void exitReal(oberonParser::RealContext *ctx) = 0;

  virtual void enterNumber(oberonParser::NumberContext *ctx) = 0;
  virtual void exitNumber(oberonParser::NumberContext *ctx) = 0;

  virtual void enterConstDeclaration(oberonParser::ConstDeclarationContext *ctx) = 0;
  virtual void exitConstDeclaration(oberonParser::ConstDeclarationContext *ctx) = 0;

  virtual void enterConstExpression(oberonParser::ConstExpressionContext *ctx) = 0;
  virtual void exitConstExpression(oberonParser::ConstExpressionContext *ctx) = 0;

  virtual void enterTypeDeclaration(oberonParser::TypeDeclarationContext *ctx) = 0;
  virtual void exitTypeDeclaration(oberonParser::TypeDeclarationContext *ctx) = 0;

  virtual void enterType_(oberonParser::Type_Context *ctx) = 0;
  virtual void exitType_(oberonParser::Type_Context *ctx) = 0;

  virtual void enterArrayType(oberonParser::ArrayTypeContext *ctx) = 0;
  virtual void exitArrayType(oberonParser::ArrayTypeContext *ctx) = 0;

  virtual void enterLength(oberonParser::LengthContext *ctx) = 0;
  virtual void exitLength(oberonParser::LengthContext *ctx) = 0;

  virtual void enterIdentList(oberonParser::IdentListContext *ctx) = 0;
  virtual void exitIdentList(oberonParser::IdentListContext *ctx) = 0;

  virtual void enterVariableDeclaration(oberonParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(oberonParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterExpression(oberonParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(oberonParser::ExpressionContext *ctx) = 0;

  virtual void enterRelation(oberonParser::RelationContext *ctx) = 0;
  virtual void exitRelation(oberonParser::RelationContext *ctx) = 0;

  virtual void enterSimpleExpression(oberonParser::SimpleExpressionContext *ctx) = 0;
  virtual void exitSimpleExpression(oberonParser::SimpleExpressionContext *ctx) = 0;

  virtual void enterAddOperator(oberonParser::AddOperatorContext *ctx) = 0;
  virtual void exitAddOperator(oberonParser::AddOperatorContext *ctx) = 0;

  virtual void enterTerm(oberonParser::TermContext *ctx) = 0;
  virtual void exitTerm(oberonParser::TermContext *ctx) = 0;

  virtual void enterMulOperator(oberonParser::MulOperatorContext *ctx) = 0;
  virtual void exitMulOperator(oberonParser::MulOperatorContext *ctx) = 0;

  virtual void enterFactor(oberonParser::FactorContext *ctx) = 0;
  virtual void exitFactor(oberonParser::FactorContext *ctx) = 0;

  virtual void enterDesignator(oberonParser::DesignatorContext *ctx) = 0;
  virtual void exitDesignator(oberonParser::DesignatorContext *ctx) = 0;

  virtual void enterSelector(oberonParser::SelectorContext *ctx) = 0;
  virtual void exitSelector(oberonParser::SelectorContext *ctx) = 0;

  virtual void enterSet_(oberonParser::Set_Context *ctx) = 0;
  virtual void exitSet_(oberonParser::Set_Context *ctx) = 0;

  virtual void enterElement(oberonParser::ElementContext *ctx) = 0;
  virtual void exitElement(oberonParser::ElementContext *ctx) = 0;

  virtual void enterExpList(oberonParser::ExpListContext *ctx) = 0;
  virtual void exitExpList(oberonParser::ExpListContext *ctx) = 0;

  virtual void enterActualParameters(oberonParser::ActualParametersContext *ctx) = 0;
  virtual void exitActualParameters(oberonParser::ActualParametersContext *ctx) = 0;

  virtual void enterStatement(oberonParser::StatementContext *ctx) = 0;
  virtual void exitStatement(oberonParser::StatementContext *ctx) = 0;

  virtual void enterAssignment(oberonParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(oberonParser::AssignmentContext *ctx) = 0;

  virtual void enterStatementSequence(oberonParser::StatementSequenceContext *ctx) = 0;
  virtual void exitStatementSequence(oberonParser::StatementSequenceContext *ctx) = 0;

  virtual void enterIfStatement(oberonParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(oberonParser::IfStatementContext *ctx) = 0;

  virtual void enterWhileStatement(oberonParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(oberonParser::WhileStatementContext *ctx) = 0;

  virtual void enterForStatement(oberonParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(oberonParser::ForStatementContext *ctx) = 0;

  virtual void enterDeclarationSequence(oberonParser::DeclarationSequenceContext *ctx) = 0;
  virtual void exitDeclarationSequence(oberonParser::DeclarationSequenceContext *ctx) = 0;

  virtual void enterModule(oberonParser::ModuleContext *ctx) = 0;
  virtual void exitModule(oberonParser::ModuleContext *ctx) = 0;


};

