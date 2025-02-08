enum {
  S_YYEOF = 0,                             // EOF
  S_YYerror = 1,                           // error
  S_YYUNDEF = 2,
  S_ERROR,
  S_TEXTBLOCK,
  S_STRING,
  S_IDENTIFIER,
  S_GREATER,
  S_LESS,
  S_SLASH,
  S_EQUALS,
  S_ESCAPECHAR,
  S_YYACCEPT,
  S_program,
  S_block,
  S_tag,
  S_attributes
};
