%start program

%%

program:
  /* rule 2 */
    usings decls
  ;

usings:
  /* rule 3 */
    usings USING FILENAME
  /* rule 4 */
  | %empty
  ;

decls:
  /* rule 5 */
    decls VAR IDENTIFIER
  /* rule 6 */
  | decls NAMESPACE IDENTIFIER
  /* rule 7 */
  | decls class_decl
  /* rule 8 */
  | decls func_decl
  /* rule 9 */
  | %empty
  ;

$@1:
  /* rule 10 */
    %empty
  ;

$@2:
  /* rule 11 */
    %empty
  ;

class_decl:
  /* rule 12 */
    CLASS $@1 IDENTIFIER optional_class_inheritance LEFT_CURLY $@2 class_list RIGHT_CURLY
  ;

optional_class_inheritance:
  /* rule 13 */
    COLON IDENTIFIER
  /* rule 14 */
  | %empty
  ;

class_list:
  /* rule 15 */
    class_list VAR IDENTIFIER
  /* rule 16 */
  | class_list FUNCTION IDENTIFIER LEFT_CURLY RIGHT_CURLY
  /* rule 17 */
  | class_list CONSTRUCTOR LEFT_CURLY RIGHT_CURLY
  /* rule 18 */
  | class_list DESTRUCTOR LEFT_CURLY RIGHT_CURLY
  /* rule 19 */
  | %empty
  ;

func_decl:
  /* rule 20 */
    FUNCTION IDENTIFIER LEFT_CURLY RIGHT_CURLY
  ;
