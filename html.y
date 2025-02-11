%start program

%%

program:
  /* rule 2 */
    block
  ;

block:
  /* rule 3 */
    block tag
  /* rule 4 */
  | block TEXTBLOCK
  /* rule 5 */
  | %empty
  ;

tag:
  /* rule 6 */
    LESS IDENTIFIER attributes GREATER
  /* rule 7 */
  | LESS SLASH IDENTIFIER GREATER
  /* rule 8 */
  | LESS IDENTIFIER attributes SLASH GREATER
  ;

attributes:
  /* rule 9 */
    attributes IDENTIFIER EQUALS STRING
  /* rule 10 */
  | attributes IDENTIFIER EQUALS IDENTIFIER
  /* rule 11 */
  | attributes IDENTIFIER
  /* rule 12 */
  | %empty
