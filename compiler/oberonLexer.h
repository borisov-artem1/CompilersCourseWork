
// Generated from oberon.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  oberonLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, ARRAY = 25, OF = 26, 
    END = 27, TO = 28, OR = 29, DIV = 30, MOD = 31, NIL = 32, TRUE = 33, 
    FALSE = 34, IF = 35, THEN = 36, ELSIF = 37, ELSE = 38, CASE = 39, WHILE = 40, 
    DO = 41, FOR = 42, BY = 43, BEGIN = 44, RETURN = 45, CONST = 46, TYPE = 47, 
    VAR = 48, MODULE = 49, STRING = 50, IDENT = 51, LETTER = 52, DIGIT = 53, 
    COMMENT = 54, WS = 55
  };

  explicit oberonLexer(antlr4::CharStream *input);

  ~oberonLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

