enum {
  S_YYEOF = 0,                             // EOF
  S_YYerror = 1,                           // error
  S_YYUNDEF = 2,                           // invalid token
  S_IF,
  S_ELIF,
  S_AND,
  S_OR,
  S_NOT,
  S_LPAREN,
  S_RPAREN,
  S_INTEGER,
  S_EQUAL,
  S_NOTEQUAL,
  S_GREATER,
  S_GREATER_EQUAL,
  S_LESS,
  S_LESS_EQUAL,
  S_NEWLINE,
  S_IDENTIFIER,
  S_STRING,
  S_YYACCEPT,
  S_program,
  S_expressions,
  S_expression,
  S_operand,
  S_exp_operator,
  S_operator,
  S_unary_operator
};
