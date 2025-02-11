%start program

%%

program:
  /* rule 2 */
    using_list function_list
  ;

using_list:
  /* rule 3 */
    using_list USING filename SEMICOLON
  /* rule 4 */
  | %empty
  ;

function_list:
  /* rule 5 */
    function_list function_object
  /* rule 6 */
  | function_list class_object
  /* rule 7 */
  | %empty
  ;

@1:
  /* rule 8 */
    %empty
  ;

class_object:
  /* rule 9 */
    CLASS IDENTIFIER optional_class_inheritance LEFT_CURLY @1 class_list RIGHT_CURLY
  ;

class_list:
  /* rule 10 */
    class_list VAR IDENTIFIER SEMICOLON
  /* rule 11 */
  | class_list function_decl
  ;

$@2:
  /* rule 12 */
    %empty
  ;

class_list:
  /* rule 13 */
    class_list optional_docblock CONSTRUCTOR $@2 LEFT_PAREN RIGHT_PAREN LEFT_CURLY statement_list RIGHT_CURLY
  ;

$@3:
  /* rule 14 */
    %empty
  ;

class_list:
  /* rule 15 */
    class_list optional_docblock DESTRUCTOR $@3 LEFT_PAREN RIGHT_PAREN LEFT_CURLY statement_list RIGHT_CURLY
  /* rule 16 */
  | %empty
  ;

optional_class_inheritance:
  /* rule 17 */
    COLON IDENTIFIER
  /* rule 18 */
  | %empty
  ;

$@4:
  /* rule 19 */
    %empty
  ;

function_decl:
  /* rule 20 */
    optional_docblock FUNCTION optional_funcflags IDENTIFIER $@4 LEFT_PAREN formal_parameter_list RIGHT_PAREN LEFT_CURLY statement_list RIGHT_CURLY
  ;

function_object:
  /* rule 21 */
    function_decl
  /* rule 22 */
  | USING_ANIMTREE LEFT_PAREN STRING RIGHT_PAREN SEMICOLON
  /* rule 23 */
  | NAMESPACE IDENTIFIER SEMICOLON
  /* rule 24 */
  | PRECACHE LEFT_PAREN STRING COMMA STRING RIGHT_PAREN SEMICOLON
  /* rule 25 */
  | PRECACHE LEFT_PAREN STRING COMMA STRING COMMA STRING RIGHT_PAREN SEMICOLON
  /* rule 26 */
  | PRECACHE LEFT_PAREN STRING COMMA STRING COMMA STRING COMMA STRING RIGHT_PAREN SEMICOLON
  /* rule 27 */
  | DEVBLOCK_BEGIN
  /* rule 28 */
  | DEVBLOCK_END
  ;

optional_funcflags:
  /* rule 29 */
    optional_funcflags AUTOEXEC
  /* rule 30 */
  | optional_funcflags PRIVATE
  /* rule 31 */
  | %empty
  ;

optional_docblock:
  /* rule 32 */
    DOCBLOCK
  /* rule 33 */
  | %empty
  ;

formal_parameter_list:
  /* rule 34 */
    formal_parameter
  /* rule 35 */
  | ELLIPSIS
  /* rule 36 */
  | formal_parameter COMMA ELLIPSIS
  /* rule 37 */
  | %empty
  ;

formal_parameter:
  /* rule 38 */
    formal_parameter COMMA IDENTIFIER optional_default_value
  /* rule 39 */
  | formal_parameter COMMA BIT_AND IDENTIFIER optional_default_value
  /* rule 40 */
  | IDENTIFIER optional_default_value
  /* rule 41 */
  | BIT_AND IDENTIFIER optional_default_value
  ;

optional_default_value:
  /* rule 42 */
    EQUALS primitive_expression
  /* rule 43 */
  | %empty
  ;

statement_list:
  /* rule 44 */
    statement_list statement
  /* rule 45 */
  | %empty
  ;

statement:
  /* rule 46 */
    nonempty_statement
  /* rule 47 */
  | SEMICOLON
  ;

nonempty_statement:
  /* rule 48 */
    nonempty_statement_2 SEMICOLON
  /* rule 49 */
  | call_expression SEMICOLON
  /* rule 50 */
  | LEFT_CURLY statement_list RIGHT_CURLY
  /* rule 51 */
  | IF LEFT_PAREN expression RIGHT_PAREN nonempty_statement
  /* rule 52 */
  | IF LEFT_PAREN expression RIGHT_PAREN nonempty_statement ELSE nonempty_statement
  /* rule 53 */
  | WHILE LEFT_PAREN expression RIGHT_PAREN nonempty_statement
  /* rule 54 */
  | DO LEFT_CURLY statement_list RIGHT_CURLY WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON
  /* rule 55 */
  | FOR LEFT_PAREN statement optional_expression SEMICOLON post_op RIGHT_PAREN nonempty_statement
  /* rule 56 */
  | FOREACH LEFT_PAREN optional_foreach IN expression RIGHT_PAREN nonempty_statement
  /* rule 57 */
  | SWITCH LEFT_PAREN expression RIGHT_PAREN LEFT_CURLY case_statement_list RIGHT_CURLY
  ;

$@5:
  /* rule 58 */
    %empty
  ;

nonempty_statement:
  /* rule 59 */
    DEVBLOCK_BEGIN $@5 statement_list DEVBLOCK_END
  ;

$@6:
  /* rule 60 */
    %empty
  ;

nonempty_statement:
  /* rule 61 */
    ASSERT LEFT_PAREN $@6 expression_list RIGHT_PAREN SEMICOLON
  ;

$@7:
  /* rule 62 */
    %empty
  ;

nonempty_statement:
  /* rule 63 */
    ASSERTMSG LEFT_PAREN $@7 expression_list RIGHT_PAREN SEMICOLON
  ;

optional_foreach:
  /* rule 64 */
    IDENTIFIER COMMA IDENTIFIER
  /* rule 65 */
  | IDENTIFIER
  ;

post_op:
  /* rule 66 */
    nonempty_statement_2
  /* rule 67 */
  | %empty
  ;

call_expression:
  /* rule 68 */
    call LEFT_PAREN expression_list RIGHT_PAREN
  /* rule 69 */
  | primitive_expression call LEFT_PAREN expression_list RIGHT_PAREN
  /* rule 70 */
  | optimized_calls
  ;

call:
  /* rule 71 */
    basic_call
  /* rule 72 */
  | THREAD basic_call
  ;

basic_call:
  /* rule 73 */
    function_call
  /* rule 74 */
  | LEFT_BRACKET LEFT_BRACKET expression RIGHT_BRACKET RIGHT_BRACKET
  /* rule 75 */
  | LEFT_BRACKET LEFT_BRACKET expression RIGHT_BRACKET RIGHT_BRACKET ARROW IDENTIFIER
  ;

optimized_calls:
  /* rule 76 */
    ISDEFINED LEFT_PAREN expression_list RIGHT_PAREN
  /* rule 77 */
  | VECTOR_SCALE LEFT_PAREN expression_list RIGHT_PAREN
  /* rule 78 */
  | GETTIME LEFT_PAREN RIGHT_PAREN
  /* rule 79 */
  | PROFILESTART LEFT_PAREN STRING RIGHT_PAREN
  /* rule 80 */
  | PROFILESTOP LEFT_PAREN RIGHT_PAREN
  /* rule 81 */
  | NEW IDENTIFIER LEFT_PAREN expression_list RIGHT_PAREN
  ;

nonempty_statement_2:
  /* rule 82 */
    variable_expression EQUALS expression
  /* rule 83 */
  | CONSTANT IDENTIFIER EQUALS expression
  /* rule 84 */
  | RETURN expression
  /* rule 85 */
  | RETURN
  /* rule 86 */
  | variable_expression INC
  /* rule 87 */
  | variable_expression DEC
  /* rule 88 */
  | variable_expression BIT_OR_EQUALS expression
  /* rule 89 */
  | variable_expression BIT_XOR_EQUALS expression
  /* rule 90 */
  | variable_expression BIT_AND_EQUALS expression
  /* rule 91 */
  | variable_expression SHIFT_LEFT_EQUALS expression
  /* rule 92 */
  | variable_expression SHIFT_RIGHT_EQUALS expression
  /* rule 93 */
  | variable_expression PLUS_EQUALS expression
  /* rule 94 */
  | variable_expression MINUS_EQUALS expression
  /* rule 95 */
  | variable_expression MULTIPLY_EQUALS expression
  /* rule 96 */
  | variable_expression DIVIDE_EQUALS expression
  /* rule 97 */
  | variable_expression MOD_EQUALS expression
  /* rule 98 */
  | WAIT expression
  /* rule 99 */
  | REALWAIT expression
  /* rule 100 */
  | primitive_expression WAITTILL LEFT_PAREN waittill_expression_list RIGHT_PAREN
  /* rule 101 */
  | primitive_expression WAITTILLMATCH LEFT_PAREN waittillmatch_expression_list RIGHT_PAREN
  /* rule 102 */
  | WAITTILLFRAMEEND
  /* rule 103 */
  | primitive_expression NOTIFY LEFT_PAREN waittillmatch_expression_list RIGHT_PAREN
  /* rule 104 */
  | primitive_expression ENDON LEFT_PAREN expression RIGHT_PAREN
  /* rule 105 */
  | BREAK
  /* rule 106 */
  | CONTINUE
  ;

case_statement_list:
  /* rule 107 */
    case_statement_list CASE primitive_expression COLON statement_list
  /* rule 108 */
  | case_statement_list DEFAULT COLON statement_list
  /* rule 109 */
  | %empty
  ;

primitive_expression:
  /* rule 110 */
    call_expression
  /* rule 111 */
  | variable_expression
  /* rule 112 */
  | primitive_expression SIZE_FIELD
  /* rule 113 */
  | LEFT_PAREN expression_list RIGHT_PAREN
  /* rule 114 */
  | DOLLAR INTEGER
  /* rule 115 */
  | DOLLAR IDENTIFIER
  /* rule 116 */
  | INTEGER
  /* rule 117 */
  | FLOAT
  /* rule 118 */
  | STRING
  /* rule 119 */
  | ISTRING
  /* rule 120 */
  | HSTRING
  /* rule 121 */
  | UNDEFINED
  /* rule 122 */
  | FALSE
  /* rule 123 */
  | TRUE
  /* rule 124 */
  | SELF
  /* rule 125 */
  | WORLD
  /* rule 126 */
  | CLASSES
  /* rule 127 */
  | LEVEL
  /* rule 128 */
  | GAME
  /* rule 129 */
  | ANIM
  /* rule 130 */
  | LEFT_BRACKET RIGHT_BRACKET
  /* rule 131 */
  | MOD IDENTIFIER
  /* rule 132 */
  | MOD IDENTIFIER DOUBLE_COLON IDENTIFIER
  /* rule 133 */
  | CUR_ANIMTREE
  ;

variable_expression:
  /* rule 134 */
    primitive_expression PERIOD IDENTIFIER
  /* rule 135 */
  | primitive_expression LEFT_BRACKET expression RIGHT_BRACKET
  /* rule 136 */
  | IDENTIFIER
  /* rule 137 */
  | FUNCTIONNAME_MACRO
  /* rule 138 */
  | BIT_AND IDENTIFIER
  /* rule 139 */
  | BIT_AND IDENTIFIER DOUBLE_COLON IDENTIFIER
  ;

function_call:
  /* rule 140 */
    IDENTIFIER DOUBLE_COLON IDENTIFIER
  /* rule 141 */
  | IDENTIFIER
  ;

expression_list:
  /* rule 142 */
    nonempty_expression_list
  /* rule 143 */
  | %empty
  ;

nonempty_expression_list:
  /* rule 144 */
    nonempty_expression_list COMMA expression
  /* rule 145 */
  | expression
  ;

expression:
  /* rule 146 */
    primitive_expression
  /* rule 147 */
  | LEFT_PAREN expression CONDITIONAL expression COLON expression RIGHT_PAREN
  /* rule 148 */
  | expression BOOL_OR expression
  /* rule 149 */
  | expression BOOL_AND expression
  /* rule 150 */
  | expression BIT_OR expression
  /* rule 151 */
  | expression BIT_XOR expression
  /* rule 152 */
  | expression BIT_AND expression
  /* rule 153 */
  | expression EQUALITY expression
  /* rule 154 */
  | expression INEQUALITY expression
  /* rule 155 */
  | expression SUPER_EQUALITY expression
  /* rule 156 */
  | expression SUPER_INEQUALITY expression
  /* rule 157 */
  | expression LESS expression
  /* rule 158 */
  | expression GREATER expression
  /* rule 159 */
  | expression LESS_EQUAL expression
  /* rule 160 */
  | expression GREATER_EQUAL expression
  /* rule 161 */
  | expression SHIFT_LEFT expression
  /* rule 162 */
  | expression SHIFT_RIGHT expression
  /* rule 163 */
  | expression PLUS expression
  /* rule 164 */
  | expression MINUS expression
  /* rule 165 */
  | expression MULTIPLY expression
  /* rule 166 */
  | expression DIVIDE expression
  /* rule 167 */
  | expression MOD expression
  /* rule 168 */
  | NOT expression
  /* rule 169 */
  | TILDA expression
  /* rule 170 */
  | MINUS expression
  ;

optional_expression:
  /* rule 171 */
    expression
  /* rule 172 */
  | %empty
  ;

waittill_expression_list:
  /* rule 173 */
    waittill_expression_list COMMA IDENTIFIER
  /* rule 174 */
  | waittill_expression_list COMMA UNDEFINED
  /* rule 175 */
  | expression
  ;

waittillmatch_expression_list:
  /* rule 176 */
    waittillmatch_expression_list COMMA expression
  /* rule 177 */
  | expression
  ;

filename:
  /* rule 178 */
    IDENTIFIER
  /* rule 179 */
  | FILENAME
