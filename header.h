#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_keyword(const char *word);
int is_operator_char(char ch);
void tokenize(FILE *fp, FILE *out);
void html_begin(FILE *fp);
void html_end(FILE *fp);