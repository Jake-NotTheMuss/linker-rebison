enum {
  S_YYEOF = 0,                             // EOF
  S_YYerror = 1,                           // error
  S_YYUNDEF = 2,                           // "invalid token"
  S_ERROR = 3,
  S_IDENTIFIER,
  S_FILENAME,
  S_CLASS,
  S_VAR,
  S_FUNCTION,
  S_NAMESPACE,
  S_USING,
  S_CONSTRUCTOR,
  S_DESTRUCTOR,
  S_COLON,
  S_LEFT_CURLY,
  S_RIGHT_CURLY,
  S_YYACCEPT,
  S_program,
  S_usings,
  S_decls,
  S_class_decl,
  S_AT1,
  S_AT2,
  S_optional_class_inheritance,
  S_class_list,
  S_func_decl
};
