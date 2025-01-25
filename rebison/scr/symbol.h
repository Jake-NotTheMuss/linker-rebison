enum {
  S_YYEOF = 0,                             // EOF
  S_YYerror = 1,                           // error
  S_YYUNDEF = 2,                           // "invalid token"
  S_ERROR = 3,
  S_BOOL_OR = 4,
  S_BOOL_AND = 5,
  S_BIT_OR = 6,
  S_BIT_XOR = 7,
  S_BIT_AND = 8,
  S_EQUALITY = 9,
  S_SUPER_EQUALITY = 0xa,
  S_INEQUALITY = 0xb,
  S_SUPER_INEQUALITY = 0xc,
  S_EQUALS = 0xd,
  S_LESS = 0xe,
  S_GREATER = 0xf,
  S_LESS_EQUAL = 0x0,
  S_GREATER_EQUAL = 0x1,
  S_SHIFT_LEFT = 0x2,
  S_SHIFT_RIGHT = 0x3,
  S_PLUS = 0x4,
  S_MINUS = 0x5,
  S_MULTIPLY = 0x6,
  S_DIVIDE = 0x7,
  S_MOD = 0x8,
  S_NOT = 0x9,
  S_TILDA = 0xa,
  S_DOLLAR = 0xb,
  S_PERIOD = 0xc,
  S_COMMA = 0xd,
  S_SEMICOLON = 0xe,
  S_FUNCTION = 0xf,
  S_CONDITIONAL = 0x20,
  S_RETURN = 0x21,
  S_CLASS = 0x22,
  S_VAR = 0x23,
  S_CONSTRUCTOR = 0x24,
  S_DESTRUCTOR = 0x25,
  S_ARROW = 0x26,
  S_THREAD = 0x27,
  S_UNDEFINED = 0x28,
  S_SELF = 0x29,
  S_WORLD = 0x2a,
  S_CLASSES = 0x2b,
  S_LEVEL = 0x2c,
  S_GAME = 0x2d,
  S_ANIM = 0x2e,
  S_IF = 0x2f,
  S_ELSE = 0x30,
  S_DO = 0x31,
  S_WHILE = 0x32,
  S_FOR = 0x33,
  S_FOREACH = 0x34,
  S_IN = 0x35,
  S_INC = 0x36,
  S_DEC = 0x37,
  S_BIT_OR_EQUALS = 0x38,
  S_BIT_XOR_EQUALS = 0x39,
  S_BIT_AND_EQUALS = 0x3a,
  S_SHIFT_LEFT_EQUALS = 0x3b,
  S_SHIFT_RIGHT_EQUALS = 0x3c,
  S_PLUS_EQUALS = 0x3d,
  S_MINUS_EQUALS = 0x3e,
  S_MULTIPLY_EQUALS = 0x3f,
  S_DIVIDE_EQUALS = 0x40,
  S_MOD_EQUALS = 0x41,
  S_SIZE_FIELD = 0x42,
  S_USING_ANIMTREE = 0x43,
  S_CUR_ANIMTREE = 0x44,
  S_NAMESPACE = 0x45,
  S_USING = 0x46,
  S_PRECACHE = 0x47,
  S_DOUBLE_COLON = 0x48,
  S_WAITTILL = 0x49,
  S_WAITTILLMATCH = 0x4a,
  S_WAITTILLFRAMEEND = 0x4b,
  S_WAIT = 0x4c,
  S_NOTIFY = 0x4d,
  S_ENDON = 0x4e,
  S_SWITCH = 0x4f,
  S_CASE = 0x50,
  S_DEFAULT = 0x51,
  S_BREAK = 0x52,
  S_CONTINUE = 0x53,
  S_FALSE = 0x54,
  S_TRUE = 0x55,
  S_ASSERT = 0x56,
  S_ASSERTMSG = 0x57,
  S_ISDEFINED = 0x58,
  S_AUTOEXEC = 0x59,
  S_CONSTANT = 0x5a,
  S_CODECALL = 0x5b,
  S_PRIVATE = 0x5c,
  S_ELLIPSIS = 0x5d,
  S_DEVBLOCK_BEGIN = 0x5e,
  S_DEVBLOCK_END = 0x5f,
  S_LEFT_CURLY = 0x60,
  S_RIGHT_CURLY = 0x61,
  S_LEFT_PAREN = 0x62,
  S_RIGHT_PAREN = 0x63,
  S_LEFT_BRACKET = 0x64,
  S_RIGHT_BRACKET = 0x65,
  S_NEW = 0x66,
  S_HSTRING = 0x67,
  S_INTEGER = 0x68,
  S_FLOAT = 0x69,
  S_IDENTIFIER = 0x6a,
  S_STRING = 0x6b,
  S_ISTRING = 0x6c,
  S_FILENAME = 0x6d,
  S_DOCBLOCK = 0x6e,
  S_VECTOR_SCALE = 0x6f,
  S_GETTIME = 0x70,
  S_REALWAIT = 0x71,
  S_PROFILESTART = 0x72,
  S_PROFILESTOP = 0x73,
  S_FUNCTIONNAME_MACRO = 0x74, /* __FUNCTION__/__function__ */
  S_IF2 = 0x75,
  S_NEG = 0x76,
  S_YYACCEPT = 0x78,
  S_program = 0x79,
  S_using_list = 0x7a,
  S_function_list = 0x7b,
  S_class_object = 0x7c,
  S_AT1 = 0x7d,
  S_class_list = 0x7e,
  S_AT2 = 0x7f,
  S_AT3 = 0x80,
  S_optional_class_inheritance = 0x81,
  S_function_decl = 0x82,
  S_AT4 = 0x83,
  S_function_object = 0x84,
  S_optional_funcflags = 0x85,
  S_optional_docblock = 0x86,
  S_formal_parameter_list = 0x87,
  S_formal_parameter = 0x88,
  S_optional_default_value = 0x89,
  S_statement_list = 0x8a,
  S_statement = 0x8b,
  S_nonempty_statement = 0x8c,
  S_AT5 = 0x8d,
  S_AT6 = 0x8e,
  S_AT7 = 0x8f,
  S_optional_foreach = 0x90,
  S_post_op = 0x91,
  S_call_expression = 0x92,
  S_call = 0x93,
  S_basic_call = 0x94,
  S_optimized_calls = 0x95,
  S_nonempty_statement_2 = 0x96,
  S_case_statement_list = 0x97,
  S_primitive_expression = 0x98,
  S_variable_expression = 0x99,
  S_function_call = 0x9a,
  S_expression_list = 0x9b,
  S_nonempty_expression_list = 0x9c,
  S_expression = 0x9d,
  S_optional_expression = 0x9e,
  S_waittill_expression_list = 0x9f,
  S_waittillmatch_expression_list = 0xa0,
  S_filename = 0xa1
};
