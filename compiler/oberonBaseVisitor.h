
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
  std::unordered_map<std::string, llvm::Type*> namedTypes;

  oberonBaseVisitor(llvm::LLVMContext& ctx, llvm::IRBuilder<>& builder, llvm::Module* module)
  : context(ctx), builder(builder), module(module) {}

  virtual std::string visitIdent(oberonParser::IdentContext *ctx) override {
    return ctx->getText();
  }

  virtual std::string visitQualident(oberonParser::QualidentContext *ctx) override {
    return visitIdent(ctx->ident());
  }

  virtual std::string visitIdentdef(oberonParser::IdentdefContext *ctx) override {
    return visitIdent(ctx->ident());
  }

  virtual llvm::Value* visitInteger(oberonParser::IntegerContext *ctx) override {
    int value = std::stoi(ctx->getText());
    llvm::Value* result = llvm::ConstantInt::get(builder.getInt32Ty(), value);

    return result;
  }

  virtual llvm::Value* visitReal(oberonParser::RealContext *ctx) override {
    double value = std::stod(ctx->getText());
    llvm::Value* result = llvm::ConstantFP::get(builder.getFloatTy(), value);

    return result;
  }

  virtual llvm::Value* visitNumber(oberonParser::NumberContext *ctx) override {
    llvm::Value* result = nullptr;
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

  virtual llvm::Value* visitConstExpression(oberonParser::ConstExpressionContext *ctx) override {
    return visitExpression(ctx->expression());
  }

  virtual std::any visitTypeDeclaration(oberonParser::TypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual llvm::Type* visitType_(oberonParser::Type_Context *ctx) override {
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
      t = visitArrayType(ctx->arrayType());
    } else
    {
      throw std::runtime_error("Type is not supported.");
    }
    return t;
  }

  virtual llvm::Type* visitArrayType(oberonParser::ArrayTypeContext *ctx) override {
    llvm::Value* lengthValue = visitLength(ctx->length());
    const auto* constLength = llvm::dyn_cast<llvm::ConstantInt>(lengthValue);
    const uint64_t length = constLength->getSExtValue();
    llvm::Type* t = visitType_(ctx->type_());
    return llvm::ArrayType::get(t, length);
  }

  virtual llvm::Value* visitLength(oberonParser::LengthContext *ctx) override {
    return visitConstExpression(ctx->constExpression());
  }

  virtual std::vector<std::string> visitIdentList(oberonParser::IdentListContext *ctx) override {
    std::vector<std::string> resIdentdefVec;
    for (auto ct : ctx->identdef())
    {
      resIdentdefVec.push_back(visitIdentdef(ct));
    }
    return resIdentdefVec;
  }

  virtual std::any visitVariableDeclaration(oberonParser::VariableDeclarationContext *ctx) override {
    std::vector<std::string> identList = visitIdentList(ctx->identList());
    llvm::Type* resType_ = visitType_(ctx->type_());

    for (const std::string& ident : identList)
    {
      llvm::AllocaInst* alloca = builder.CreateAlloca(resType_, nullptr, ident);

      namedValues[ident] = alloca;
      namedTypes[ident] = resType_;
    }
    return nullptr;
  }

  virtual llvm::Value* visitExpression(oberonParser::ExpressionContext *ctx) override {
    llvm::Value* simpleExpr = visitSimpleExpression(ctx->simpleExpression(0));

    if (ctx->simpleExpression().size() == 2)
    {
      const std::string op = visitRelation(ctx->relation());
      llvm::Value* rhs = visitSimpleExpression(ctx->simpleExpression(1));
      if (op == "#")
      {
        return builder.CreateICmpNE(simpleExpr, rhs, "cmp_unequal");
      }
      if (op == "=")
      {
        return builder.CreateICmpEQ(simpleExpr, rhs, "cmp_equal");
      }
      if (op == "<")
      {
        return builder.CreateICmpSLT(simpleExpr, rhs, "cmp_smaller");
      }
      if (op == ">")
      {
        return builder.CreateICmpSGT(simpleExpr, rhs, "cmp_bigger");
      }
      if (op == "<=")
      {
        return builder.CreateICmpSLE(simpleExpr, rhs, "cmp_smaller_or_equal");
      }
      if (op == ">=")
      {
        return builder.CreateICmpSGE(simpleExpr, rhs, "cmp_bigger_or_equal");
      }

    }
    return simpleExpr;
  }

  virtual std::string visitRelation(oberonParser::RelationContext *ctx) override {
    return ctx->getText();
  }

  virtual llvm::Value* visitSimpleExpression(oberonParser::SimpleExpressionContext *ctx) override {
    auto resultAny = visit(ctx->term(0));
    //std::cout << resultAny.type().name() << std::endl;
    llvm::Value* result = std::any_cast<llvm::Value*>(resultAny);

    if (ctx->addOperator().size() < ctx->term().size())
    {
      std::string prefixOp = ctx->getStart()->getText();
      if (prefixOp == "-")
      {
        result = builder.CreateNeg(result, "negtmp");
      }
    }

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

  virtual std::string visitAddOperator(oberonParser::AddOperatorContext *ctx) override {
    return ctx->getText();
  }

  virtual std::any visitTerm(oberonParser::TermContext *ctx) override {
    auto resultAny = visitFactor(ctx->factor(0));
    llvm::Value* result = std::any_cast<llvm::Value*>(resultAny);

    for (size_t i = 0; i < ctx->mulOperator().size(); ++i)
    {
      std::string op = visitMulOperator(ctx->mulOperator(i));
      auto rhsAny = visitFactor(ctx->factor(i + 1));
      llvm::Value* rhs = std::any_cast<llvm::Value*>(rhsAny);

      if (op == "*")
      {
        if (result->getType()->isFloatTy() || rhs->getType()->isFloatTy())
        {
          result = builder.CreateFMul(result, rhs, "fmultmp");
        } else
        {
          result = builder.CreateMul(result, rhs, "multmp");
        }
      } else if (op == "/")
      {
        result = builder.CreateFDiv(result, rhs, "fdivtmp");
      }
      else if (op == "DIV")
      {
        result = builder.CreateSDiv(result, rhs, "divtmp");
      } else if (op == "MOD")
      {
        result = builder.CreateSRem(result, rhs, "modtmp");
      } else if (op == "&")
      {
        result = builder.CreateAnd(result, rhs, "andtmp");
      }
      else
      {
        std::cerr << "Unknown operator: " << op << std::endl;
        throw std::runtime_error("Unknown operator");
      }
    }
    return result;
    //return visitChildren(ctx);
  }

  virtual std::string visitMulOperator(oberonParser::MulOperatorContext *ctx) override {
    return ctx->getText();
  }

  virtual llvm::Value* visitFactor(oberonParser::FactorContext *ctx) override {
    llvm::Value* result = nullptr;
    if (ctx->number() != nullptr)
    {
      result = visitNumber(ctx->number());
    } else if (ctx->STRING() != nullptr)
    {
      std::string str = ctx->STRING()->getText();
      str = str.substr(1, str.size() - 2);
      llvm::Value* strConst = builder.CreateGlobalStringPtr(str, "str");
      result = strConst;
    }
    else if (ctx->NIL() != nullptr)
    {
      result = llvm::ConstantPointerNull::get(llvm::PointerType::getUnqual(builder.getInt8Ty()));
    }
    else if (ctx->TRUE() != nullptr)
    {
      result = llvm::ConstantInt::get(builder.getInt1Ty(), 1);
    }
    else if (ctx->FALSE() != nullptr)
    {
      result = llvm::ConstantInt::get(builder.getInt1Ty(), 0);
    }
    else if (ctx->set_() != nullptr)
    {
      // result = visitSet_(ctx->set_());
      throw std::runtime_error("Not implemented yet");
    } else if (ctx->designator() != nullptr)
    {
      llvm::Value* varPtr = std::any_cast<llvm::Value*>(visitDesignator(ctx->designator()));
      // if (ctx->designator()->selector(0) != nullptr)
      // {
      //
      // }
      std::string varName = ctx->designator()->qualident()->getText();

      if (!varPtr->getType()->isPointerTy())
      {
        std::cerr << "Expected a pointer type in visitFactor" << std::endl;
        throw std::runtime_error("Expected a pointer type");
      }

      auto it = namedTypes.find(varName);
      if (it == namedTypes.end())
      {
        std::cerr << "Type of variable " << varName << " not found in namedTypes" << std::endl;
        throw std::runtime_error("Unknown variable type");
      }

      llvm::Type* elemType = it->second;
      llvm::ArrayType* arrayType = nullptr;
      if (ctx->designator()->selector(0) != nullptr)
      {
        arrayType = llvm::dyn_cast<llvm::ArrayType>(namedTypes[varName]);
        result = builder.CreateLoad(arrayType->getElementType(), varPtr, "value");
      } else
      {
        result = builder.CreateLoad(namedTypes[varName], varPtr, "value");
      }


      // auto* ptrType = llvm::dyn_cast<llvm::PointerType>(varPtr->getType());
      // if (!ptrType)
      // {
      //   std::cerr << "Expected a pointer type in visitFactor" << std::endl;
      //   throw std::runtime_error("Expected a pointer type");
      // }
      //
      // llvm::Type* loadType = ptrType->getNonOpaquePointerElementType();
      // result = builder.CreateLoad(loadType, varPtr, "value");
    }
    else if (ctx->expression() != nullptr)
    {
      result = visitExpression(ctx->expression());
    }
    else if (ctx->factor() != nullptr && ctx->getText()[0] == '~')
    {
      llvm::Value* val = visitFactor(ctx->factor());
      result = builder.CreateNot(val, "notted");
    }
    return result;
  }

  virtual std::any visitDesignator(oberonParser::DesignatorContext *ctx) override {
    //std::string varName = ctx->getText();
    std::string varName = visitQualident(ctx->qualident());
    llvm::Type* varType = namedTypes[varName];
    llvm::Value* varPtr = namedValues.contains(varName) ?
      namedValues[varName] : module->getNamedGlobal(varName);

    if (!varPtr)
    {
      varPtr = builder.CreateAlloca(builder.getInt32Ty(), nullptr, varName);
      namedValues[varName] = varPtr;
    }

    llvm::Value* valueSelector = nullptr;
    for (auto* selector : ctx->selector())
    {
      valueSelector = std::any_cast<llvm::Value*>(visitSelector(selector));
      if (valueSelector)
      {
        llvm::Value* zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
        llvm::Value* indices[] = { zero, valueSelector };

        // auto* ptrType = llvm::dyn_cast<llvm::PointerType>(valueSelector->getType());
        llvm::Type* elementType = nullptr;
        // if (auto* ptrType = llvm::dyn_cast<llvm::PointerType>(varPtr->getType()))
        // {

        auto* arrayType = llvm::dyn_cast<llvm::ArrayType>(namedTypes[varName]);
          // if (auto* arrayType = llvm::dyn_cast<llvm::ArrayType>(namedTypes[varName]))
          // {
          //   elementType = arrayType->getElementType();
          // }
          // std::cerr << "Error: valueSelector is not a pointer!" << std::endl;
          // throw std::runtime_error("Expected pointer type. Error in function visitDesignator");
        // }
        // else
        // {
        //   std::cerr << "Error: valueSelector is not a pointer!" << std::endl;
        //   throw std::runtime_error("Expected pointer type.");
        // }
    //     llvm::Type* loadType = ptrType->getNonOpaquePointerElementType(); // TODO: need to be fixed!!!
    //     valueSelector = builder.CreateLoad(loadType, valueSelector, "value");
    //
    //
    //     llvm::Type* elementType =
    // llvm::cast<llvm::PointerType>(namedValues[varName]->getType())->getNonOpaquePointerElementType();

        varPtr = builder.CreateGEP(
          arrayType,
          varPtr,
          indices,
          "arr_element_ptr"
          );
      }
    }
    //llvm::Value* loaded = builder.CreateLoad(builder.getInt32Ty(), var, varName + "_load");
    return varPtr;
  }

  virtual std::any visitSelector(oberonParser::SelectorContext *ctx) override {
    llvm::Value* varPtr = nullptr;
    if (ctx->expList() != nullptr)
    {
      varPtr = visitExpList(ctx->expList());
    }
    return varPtr;
  }

  virtual std::any visitSet_(oberonParser::Set_Context* ctx) override {

    return visitChildren(ctx);
    // TODO: add some
  }

  virtual std::any visitElement(oberonParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual llvm::Value* visitExpList(oberonParser::ExpListContext *ctx) override {
    llvm::Value* leftExpr = visitExpression(ctx->expression(0));
    for (size_t i = 1; i < ctx->expression().size(); ++i)
    {
      llvm::Value* rightExpr = visitExpression(ctx->expression(i));
    }
    return leftExpr;
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

    if (!namedValues[varName])
    {
      auto* alloca = builder.CreateAlloca(builder.getInt32Ty(), nullptr, varName);
      namedValues[varName] = alloca;
    }

    builder.CreateStore(expr, design);
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
    llvm::Function* func = builder.GetInsertBlock()->getParent();

    llvm::BasicBlock* nextBlock = llvm::BasicBlock::Create(context, "next", func);
    llvm::BasicBlock* endBlock = llvm::BasicBlock::Create(context, "end", func);

    builder.CreateBr(nextBlock);
    llvm::BasicBlock* thenBlock = nullptr;

    for (size_t i = 0; i < ctx->expression().size(); ++i)
    {
      builder.SetInsertPoint(nextBlock);

      thenBlock = llvm::BasicBlock::Create(context, "then", func);
      nextBlock = llvm::BasicBlock::Create(context, "next", func);

      llvm::Value* cond = visitExpression(ctx->expression(i));

      if (cond->getType()->isIntegerTy() && cond->getType()->getIntegerBitWidth() != 1)
      {
        cond = builder.CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0), "ifcond");
      }

      builder.CreateCondBr(cond, thenBlock, nextBlock);

      builder.SetInsertPoint(thenBlock);
      visitStatementSequence(ctx->statementSequence(i));
      builder.CreateBr(endBlock);

      //func->insert(func->end(), nextBlock);
    }

    builder.SetInsertPoint(nextBlock);
    size_t seqSize = ctx->statementSequence().size();
    size_t exprSize = ctx->expression().size();
    if (seqSize != exprSize)
    {
      visitStatementSequence(ctx->statementSequence(seqSize - 1));
    }
    builder.CreateBr(endBlock);

    //func->insert(func->end(), endBlock);
    builder.SetInsertPoint(endBlock);

    return nullptr;
  }

  virtual std::any visitWhileStatement(oberonParser::WhileStatementContext *ctx) override {
    llvm::Function* func = builder.GetInsertBlock()->getParent();

    llvm::BasicBlock* whileBlock = llvm::BasicBlock::Create(context, "while", func);
    llvm::BasicBlock* doBlock = llvm::BasicBlock::Create(context, "do", func);
    llvm::BasicBlock* endBlock = llvm::BasicBlock::Create(context, "end", func);

    builder.CreateBr(whileBlock);

    builder.SetInsertPoint(whileBlock);
    llvm::Value* exprCondPtr = visitExpression(ctx->expression(0));
    builder.CreateCondBr(exprCondPtr, doBlock, endBlock);

    builder.SetInsertPoint(doBlock);
    visitStatementSequence(ctx->statementSequence(0));
    builder.CreateBr(whileBlock);

    if (ctx->expression().size() > 1)
    {
      throw std::invalid_argument("Several expressions not supported");
    }
    builder.SetInsertPoint(endBlock);

    return nullptr;
  }

  virtual std::any visitForStatement(oberonParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarationSequence(oberonParser::DeclarationSequenceContext *ctx) override {
    if (ctx->constDeclaration().size() > 0)
    {
      throw std::runtime_error("Declaration sequence is not allowed yet");
    }
    if (ctx->typeDeclaration().size() > 0)
    {
      throw std::runtime_error("Type declaration sequence is not allowed yet");
    }
    if (ctx->variableDeclaration().size() > 0)
    {
      for (auto* var : ctx->variableDeclaration())
      {
        visitVariableDeclaration(var);
      }
    }
    return nullptr;
  }

  virtual std::any visitModule(oberonParser::ModuleContext *ctx) override {
    std::string moduleName = visitIdent(ctx->ident(0));
    module = new llvm::Module(moduleName, context);
    auto* funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    auto* mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
    auto* entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);
    //visitChildren(ctx);

    visitDeclarationSequence(ctx->declarationSequence());
    visitStatementSequence(ctx->statementSequence());

    llvm::Value* returnValue = visitFactor(ctx->factor());
    // std::string varName = valueAny
    // llvm::Value* retPtr = nullptr;
    //
    // try
    // {
    //   retPtr = std::any_cast<llvm::Value*>(valueAny);
    // } catch (const std::bad_any_cast& e)
    // {
    //   std::cerr << "Error: bad_any_cast in visitModule at RETURN" << std::endl;
    //   return nullptr;
    // }

    // llvm::Type* t = namedTypes[retPtr]; // TODO: must fixed bug with cast
    // llvm::Value* retVal = builder.CreateLoad(t, retPtr);

    // if (retVal->getType()->isFloatTy()) {
    //   retVal = builder.CreateFPToSI(retVal, builder.getInt32Ty());
    // }

    llvm::FunctionCallee printfFunc = module->getOrInsertFunction(
    "printf",
    llvm::FunctionType::get(
        llvm::IntegerType::getInt32Ty(context),
        llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(context)),
        true
        )
    );

    llvm::Value* formatStr = builder.CreateGlobalStringPtr("%d\n");
    builder.CreateCall(printfFunc, {formatStr, returnValue});

    builder.CreateRet(returnValue);

    std::string endName = visitIdent(ctx->ident(1));
    if (moduleName != endName)
    {
      std::cerr << "Module name mismatch: " << moduleName << " vs " << endName << std::endl;
      throw std::runtime_error("Module name mismatch");
    }
    return module;
  }


};

