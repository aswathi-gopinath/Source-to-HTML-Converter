#include "header.h"

/* Begin HTML document */
void html_begin(FILE *fp)
{
    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<html lang=\"en\">\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "  <meta charset=\"UTF-8\">\n");
    fprintf(fp, "  <title>Source2HTML</title>\n");
    fprintf(fp, "  <link rel=\"stylesheet\" href=\"styles.css\">\n");
    fprintf(fp, "</head>\n");

    fprintf(fp, "<body style=\"background-color:lightgrey;\">\n");
    fprintf(fp, "<pre>\n");
}

/* End HTML document */
void html_end(FILE *fp)
{
    fprintf(fp, "</pre>\n");
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");
}
