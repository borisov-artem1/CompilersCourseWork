
// Generated from oberon.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "oberonListener.h"


/**
 * This class provides an empty implementation of oberonListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  oberonBaseListener : public oberonListener {
public:

  virtual void enterIdent(oberonParser::IdentContext * /*ctx*/) override { }
  virtual void exitIdent(oberonParser::IdentContext * /*ctx*/) override { }

  virtual void enterQualident(oberonParser::QualidentContext * /*ctx*/) override { }
  virtual void exitQualident(oberonParser::QualidentContext * /*ctx*/) override { }

  virtual void enterIdentdef(oberonParser::IdentdefContext * /*ctx*/) override { }
  virtual void exitIdentdef(oberonParser::IdentdefContext * /*ctx*/) override { }

  virtual void enterInteger(oberonParser::IntegerContext * /*ctx*/) override { }
  virtual void exitInteger(oberonParser::IntegerContext * /*ctx*/) override { }

  virtual void enterReal(oberonParser::RealContext * /*ctx*/) override { }
  virtual void exitReal(oberonParser::RealContext * /*ctx*/) override { }

  virtual void enterNumber(oberonParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(oberonParser::NumberContext * /*ctx*/) override { }

  virtual void enterConstDeclaration(oberonParser::ConstDeclarationContext * /*ctx*/) override { }
  virtual void exitConstDeclaration(oberonParser::ConstDeclarationContext * /*ctx*/) override { }

  virtual void enterConstExpression(oberonParser::ConstExpressionContext * /*ctx*/) override { }
  virtual void exitConstExpression(oberonParser::ConstExpressionContext * /*ctx*/) override { }

  virtual void enterTypeDeclaration(oberonParser::TypeDeclarationContext * /*ctx*/) override { }
  virtual void exitTypeDeclaration(oberonParser::TypeDeclarationContext * /*ctx*/) override { }

  virtual void enterType_(oberonParser::Type_Context * /*ctx*/) override { }
  virtual void exitType_(oberonParser::Type_Context * /*ctx*/) override { }

  virtual void enterArrayType(oberonParser::ArrayTypeContext * /*ctx*/) override { }
  virtual void exitArrayType(oberonParser::ArrayTypeContext * /*ctx*/) override { }

  virtual void enterLength(oberonParser::LengthContext * /*ctx*/) override { }
  virtual void exitLength(oberonParser::LengthContext * /*ctx*/) override { }

  virtual void enterIdentList(oberonParser::IdentListContext * /*ctx*/) override { }
  virtual void exitIdentList(oberonParser::IdentListContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(oberonParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(oberonParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterExpression(oberonParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(oberonParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterRelation(oberonParser::RelationContext * /*ctx*/) override { }
  virtual void exitRelation(oberonParser::RelationContext * /*ctx*/) override { }

  virtual void enterSimpleExpression(oberonParser::SimpleExpressionContext * /*ctx*/) override { }
  virtual void exitSimpleExpression(oberonParser::SimpleExpressionContext * /*ctx*/) override { }

  virtual void enterAddOperator(oberonParser::AddOperatorContext * /*ctx*/) override { }
  virtual void exitAddOperator(oberonParser::AddOperatorContext * /*ctx*/) override { }

  virtual void enterTerm(oberonParser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(oberonParser::TermContext * /*ctx*/) override { }

  virtual void enterMulOperator(oberonParser::MulOperatorContext * /*ctx*/) override { }
  virtual void exitMulOperator(oberonParser::MulOperatorContext * /*ctx*/) override { }

  virtual void enterFactor(oberonParser::FactorContext * /*ctx*/) override { }
  virtual void exitFactor(oberonParser::FactorContext * /*ctx*/) override { }

  virtual void enterDesignator(oberonParser::DesignatorContext * /*ctx*/) override { }
  virtual void exitDesignator(oberonParser::DesignatorContext * /*ctx*/) override { }

  virtual void enterSelector(oberonParser::SelectorContext * /*ctx*/) override { }
  virtual void exitSelector(oberonParser::SelectorContext * /*ctx*/) override { }

  virtual void enterSet_(oberonParser::Set_Context * /*ctx*/) override { }
  virtual void exitSet_(oberonParser::Set_Context * /*ctx*/) override { }

  virtual void enterElement(oberonParser::ElementContext * /*ctx*/) override { }
  virtual void exitElement(oberonParser::ElementContext * /*ctx*/) override { }

  virtual void enterExpList(oberonParser::ExpListContext * /*ctx*/) override { }
  virtual void exitExpList(oberonParser::ExpListContext * /*ctx*/) override { }

  virtual void enterActualParameters(oberonParser::ActualParametersContext * /*ctx*/) override { }
  virtual void exitActualParameters(oberonParser::ActualParametersContext * /*ctx*/) override { }

  virtual void enterStatement(oberonParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(oberonParser::StatementContext * /*ctx*/) override { }

  virtual void enterAssignment(oberonParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(oberonParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterStatementSequence(oberonParser::StatementSequenceContext * /*ctx*/) override { }
  virtual void exitStatementSequence(oberonParser::StatementSequenceContext * /*ctx*/) override { }

  virtual void enterIfStatement(oberonParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(oberonParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterWhileStatement(oberonParser::WhileStatementContext * /*ctx*/) override { }
  virtual void exitWhileStatement(oberonParser::WhileStatementContext * /*ctx*/) override { }

  virtual void enterForStatement(oberonParser::ForStatementContext * /*ctx*/) override { }
  virtual void exitForStatement(oberonParser::ForStatementContext * /*ctx*/) override { }

  virtual void enterDeclarationSequence(oberonParser::DeclarationSequenceContext * /*ctx*/) override { }
  virtual void exitDeclarationSequence(oberonParser::DeclarationSequenceContext * /*ctx*/) override { }

  virtual void enterModule(oberonParser::ModuleContext * /*ctx*/) override { }
  virtual void exitModule(oberonParser::ModuleContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

