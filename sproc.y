%start program

%%

program:
  /* rule 2 */
    IF expressions NEWLINE
  /* rule 3 */
  | ELIF expressions NEWLINE
  ;

expressions:
  /* rule 4 */
    expression exp_operator expression
  /* rule 5 */
  | expression
  ;

expression:
  /* rule 6 */
    LPAREN expressions RPAREN
  /* rule 7 */
  | operand operator operand
  /* rule 8 */
  | operand
  /* rule 9 */
  | unary_operator operand
  ;

operand:
  /* rule 10 */
    IDENTIFIER
  /* rule 11 */
  | STRING
  /* rule 12 */
  | INTEGER
  ;

exp_operator:
  /* rule 13 */
    AND
  /* rule 14 */
  | OR
  ;

operator:
  /* rule 15 */
    EQUAL
  /* rule 16 */
  | NOTEQUAL
  /* rule 17 */
  | GREATER
  /* rule 18 */
  | GREATER_EQUAL
  /* rule 19 */
  | LESS
  /* rule 20 */
  | LESS_EQUAL
  ;

unary_operator:
  /* rule 21 */
    NOT
  ;
