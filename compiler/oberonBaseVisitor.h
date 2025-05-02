
// Generated from oberon.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "oberonVisitor.h"


#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Support/TargetSelect.h>
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"


/**
 * This class provides an empty implementation of oberonVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  oberonBaseVisitor : public oberonVisitor {


public:
  llvm::LLVMContext& context;
  llvm::IRBuilder<>& builder;
  llvm::Module* module;
  static llvm::Function* function;
  std::unordered_map<std::string, llvm::Value*> namedValues;
  oberonBaseVisitor(llvm::LLVMContext& ctx, llvm::IRBuilder<>& builder, llvm::Module* module)
  : context(ctx), builder(builder), module(module) {}

  virtual std::any visitIdent(oberonParser::IdentContext *ctx) override {
    return ctx->getText();
  }

  virtual std::any visitQualident(oberonParser::QualidentContext *ctx) override {
    return visitIdent(ctx->ident());
  }

  virtual std::any visitIdentdef(oberonParser::IdentdefContext *ctx) override {
    return visitIdent(ctx->ident());
  }

  virtual std::any visitInteger(oberonParser::IntegerContext *ctx) override {
    int value = std::stoi(ctx->getText());
    llvm::Value* result = llvm::ConstantInt::get(builder.getInt32Ty(), value);

    return result;
  }

  virtual std::any visitReal(oberonParser::RealContext *ctx) override {
    double value = std::stod(ctx->getText());
    llvm::Value* result = llvm::ConstantFP::get(builder.getFloatTy(), value);

    return result;
  }

  virtual std::any visitNumber(oberonParser::NumberContext *ctx) override {
    std::any result = nullptr;
    if (ctx->integer())
    {
      result = visitInteger(ctx->integer());
    } else if (ctx->real())
    {
      result = visitReal(ctx->real());
    }
    return result;
  }

  virtual std::any visitConstDeclaration(oberonParser::ConstDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExpression(oberonParser::ConstExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDeclaration(oberonParser::TypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_(oberonParser::Type_Context *ctx) override {
    llvm::Type* t = nullptr;
    if (ctx->qualident() != nullptr)
    {
      std::string typeName = ctx->qualident()->getText();

      if (typeName == "INTEGER")
      {
        t = builder.getInt32Ty();
      } else if (typeName == "REAL")
      {
        t = builder.getFloatTy();
      } else
      {
        std::cerr << "Type " << typeName << " is not supported." << std::endl;
        t = builder.getVoidTy();
      }
    } else if (ctx->arrayType() != nullptr)
    {
      visit(ctx->arrayType());
    } else
    {
      throw std::runtime_error("Type is not supported.");
    }
    return t;
  }

  virtual std::any visitArrayType(oberonParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLength(oberonParser::LengthContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentList(oberonParser::IdentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(oberonParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(oberonParser::ExpressionContext *ctx) override {
    if (ctx->simpleExpression().size() == 1)
    {
      return visit(ctx->simpleExpression(0));
    }

    auto lhsAny = visit(ctx->simpleExpression(0));
    auto rhsAny = visit(ctx->simpleExpression(1));
    auto op = ctx->relation()->getText();

    llvm::Value* lhs = std::any_cast<llvm::Value*>(lhsAny);
    llvm::Value* rhs = std::any_cast<llvm::Value*>(rhsAny);

    if (op == "=")
    {
      return builder.CreateICmpEQ(lhs, rhs, "eqtmp");
    } else if (op == "<")
    {
      return builder.CreateICmpSLT(lhs, rhs, "lttmp");
    }

    std::cerr << op << ": Unknown binary operator" << std::endl;
    return nullptr;
  }

  virtual std::any visitRelation(oberonParser::RelationContext *ctx) override {
    return ctx->getText();
  }

  virtual std::any visitSimpleExpression(oberonParser::SimpleExpressionContext *ctx) override {
    auto resultAny = visit(ctx->term(0));
    //std::cout << resultAny.type().name() << std::endl;
    llvm::Value* result = std::any_cast<llvm::Value*>(resultAny);

    for (size_t i = 1; i < ctx->term().size(); ++i)
    {
      auto rhsAny = visit(ctx->term(i));
      llvm::Value* rhs = std::any_cast<llvm::Value*>(rhsAny);
      std::string op = ctx->addOperator(i - 1)->getText();

      if (op == "+")
      {
        result = builder.CreateAdd(result, rhs, "addtmp");
      } else if (op == "-")
      {
        result = builder.CreateSub(result, rhs, "subtmp");
      } else
      {
        return nullptr;
      }
    }
    return result;
  }

  virtual std::any visitAddOperator(oberonParser::AddOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTerm(oberonParser::TermContext *ctx) override {
    auto resultAny = visit(ctx->factor(0));
    llvm::Value* result = std::any_cast<llvm::Value*>(resultAny);

    for (size_t i = 1; i < ctx->factor().size(); ++i)
    {
      auto rhsAny = visit(ctx->factor(i));
      llvm::Value* rhs = std::any_cast<llvm::Value*>(rhsAny);
      std::string op = ctx->mulOperator(i - 1)->getText();

      if (op == "*")
      {
        result = builder.CreateMul(result, rhs, "multmp");
      } else if (op == "DIV")
      {
        result = builder.CreateSDiv(result, rhs, "sdiv");
      } else
      {
        return nullptr;
      }
    }
    return result;
    //return visitChildren(ctx);
  }

  virtual std::any visitMulOperator(oberonParser::MulOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFactor(oberonParser::FactorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDesignator(oberonParser::DesignatorContext *ctx) override {
    std::string varName = ctx->getText();
    std::any qualident = visitQualident(ctx->qualident());
    //llvm::Value* valueRef =
    llvm::Value* var = namedValues[varName];
    if (!var)
    {
      std::cerr << "Variable " << varName << " is not defined" << std::endl;
      return nullptr;
    }
    llvm::Value* loaded = builder.CreateLoad(builder.getInt32Ty(), var, varName + "_load");
    return loaded;
  }

  virtual std::any visitSelector(oberonParser::SelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSet_(oberonParser::Set_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(oberonParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpList(oberonParser::ExpListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitActualParameters(oberonParser::ActualParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(oberonParser::StatementContext *ctx) override {
    if (ctx->assignment() != nullptr)
    {
      return visitAssignment(ctx->assignment());
    }
    if (ctx->ifStatement() != nullptr)
    {
      return visitIfStatement(ctx->ifStatement());
    }
    if (ctx->whileStatement() != nullptr)
    {
      return visitWhileStatement(ctx->whileStatement());
    }
    if (ctx->forStatement() != nullptr)
    {
      return visitForStatement(ctx->forStatement());
    }
    return nullptr;
  }

  virtual std::any visitAssignment(oberonParser::AssignmentContext *ctx) override {
    std::string varName = ctx->designator()->getText();
    llvm::Value* design = std::any_cast<llvm::Value*>(visitDesignator(ctx->designator()));
    llvm::Value* expr = std::any_cast<llvm::Value*>(visitExpression(ctx->expression()));

    // llvm::Value* value = nullptr;
    // try
    // {
    //   std::cout << "Debug: expression type = " << valueAny.type().name() << "\n";
    //   value = std::any_cast<llvm::Value*>(valueAny);
    // } catch (const std::bad_any_cast& e)
    // {
    //   std::cerr << "Error: bad_any_cast in visitAssignment at expression for variable '"
    //          << ctx->designator()->getText() << "'\n";
    //   return nullptr;
    // }

    if (!namedValues[varName])
    {
      auto* alloca = builder.CreateAlloca(builder.getInt32Ty(), nullptr, varName);
      namedValues[varName] = alloca;
    }

    builder.CreateStore(design, expr);
    return nullptr;
  }

  virtual std::any visitStatementSequence(oberonParser::StatementSequenceContext *ctx) override {
    for (auto* stmt : ctx->statement())
    {
      visitStatement(stmt);
    }
    return nullptr;
  }

  virtual std::any visitIfStatement(oberonParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(oberonParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(oberonParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarationSequence(oberonParser::DeclarationSequenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitModule(oberonParser::ModuleContext *ctx) override {
    auto* mainType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    auto* mainFunc = llvm::Function::Create(mainType, llvm::Function::ExternalLinkage, "main", module);
    auto* entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);
    visitChildren(ctx);

    auto valueAny = visit(ctx->factor());
    llvm::Value* retValue = nullptr;

    try
    {
      retValue = std::any_cast<llvm::Value*>(valueAny);
    } catch (const std::bad_any_cast& e)
    {
      std::cerr << "Error: bad_any_cast in visitModule at RETURN" << std::endl;
      return nullptr;
    }

    builder.CreateRet(retValue);
    return nullptr;
  }


};

