#include "header.h"

/* ================= KEYWORDS ================= */
int is_keyword(const char *word)
{
    static const char *keywords[] = {
        "auto","break","case","char","const","continue","default","do","double",
        "else","enum","extern","float","for","goto","if","int","long","register",
        "return","short","signed","sizeof","static","struct","switch","typedef",
        "union","unsigned","void","volatile","while"
    };

    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;

    return 0;
}

/* ================= SYMBOLS ================= */
int is_symbol(char ch)
{
    static const char symbols[] = "(){}[];,:";

    for (int i = 0; symbols[i] != '\0'; i++)
        if (symbols[i] == ch)
            return 1;

    return 0;
}

/* ================= OPERATORS ================= */
int is_operator_char(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '=' || ch == '!' || ch == '<' || ch == '>' ||
            ch == '&' || ch == '|' || ch == '^' || ch == '%');
}

/* ================= TOKENIZER ================= */
void tokenize(FILE *fp, FILE *out)
{
    char ch;

    /* IMPORTANT:  flag for include to identify headers */
    int is_header = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        /* ================= SPACE ================= */
        if (isspace(ch))
        {
            fputc(ch, out);
            continue;
        }

        /* ================= COMMENT ================= */
        if (ch == '/')
        {
            char next = fgetc(fp);

            if (next == '/')
            {
                fprintf(out, "<span class=\"comment\">//");

                while ((ch = fgetc(fp)) != EOF && ch != '\n')
                    fputc(ch, out);

                fprintf(out, "</span>\n");
                continue;
            }

            if (next == '*')
            {
                fprintf(out, "<span class=\"comment\">/*");

                char prev = 0;

                while ((ch = fgetc(fp)) != EOF)
                {
                    fputc(ch, out);
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }

                fprintf(out, "</span>");
                continue;
            }

            ungetc(next, fp);
            fprintf(out, "<span class=\"operator\">/</span>");
            continue;
        }

        /* ================= PREPROCESSOR ================= */
        if (ch == '#')
        {
            char buffer[64];
            int i = 0;

            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF && isalpha(ch))
                buffer[i++] = ch;

            buffer[i] = '\0';

            fprintf(out, "<span class=\"preprocess_dir\">%s</span>", buffer);

            /* enable include mode */
            if (strcmp(buffer, "#include") == 0)
                is_header = 1;

            continue;
        }

        /* ================= HEADER FILE ================= */
        if (is_header && ch == '<')
        {
            fprintf(out, "<span class=\"header_file\">&lt;");

            while ((ch = fgetc(fp)) != EOF && ch != '>')
                fputc(ch, out);

            fprintf(out, "&gt;</span>");

            is_header = 0;
            continue;
        }

        if (is_header && ch == '"')
        {
            fprintf(out, "<span class=\"header_file\">\"");

            while ((ch = fgetc(fp)) != EOF && ch != '"')
                fputc(ch, out);

            fprintf(out, "\"</span>");

            is_header = 0;
            continue;
        }

        /* ================= STRING ================= */
        if (ch == '"')
        {
            fprintf(out, "<span class=\"string\">\"");

            while ((ch = fgetc(fp)) != EOF && ch != '"')
                fputc(ch, out);

            fprintf(out, "\"</span>");
            continue;
        }

        /* ================= CHAR ================= */
        if (ch == '\'')
        {
            fprintf(out, "<span class=\"ascii_char\">'");

            while ((ch = fgetc(fp)) != EOF && ch != '\'')
                fputc(ch, out);

            fprintf(out, "'</span>");
            continue;
        }

        /* ================= NUMBER ================= */
        if (isdigit(ch))
        {
            fprintf(out, "<span class=\"numeric_constant\">");

            while (isdigit(ch) || ch == '.')
            {
                fputc(ch, out);
                ch = fgetc(fp);
            }

            fprintf(out, "</span>");
            ungetc(ch, fp);
            continue;
        }

        /* ================= IDENTIFIER / KEYWORD ================= */
        if (isalpha(ch) || ch == '_')
        {
            char buffer[256];
            int i = 0;

            buffer[i++] = ch;

            while (isalnum(ch = fgetc(fp)) || ch == '_')
                buffer[i++] = ch;

            buffer[i] = '\0';

            if (is_keyword(buffer))
                fprintf(out, "<span class=\"reserved_key1\">%s</span>", buffer);
            else
                fprintf(out, "<span class=\"identifier\">%s</span>", buffer);

            ungetc(ch, fp);
            continue;
        }

        /* ================= OPERATORS ================= */
        if (is_operator_char(ch))
        {
            char next = fgetc(fp);
            char op[3] = {ch, next, '\0'};

            if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
                strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0 ||
                strcmp(op, "+=") == 0 || strcmp(op, "-=") == 0 ||
                strcmp(op, "*=") == 0 || strcmp(op, "/=") == 0 ||
                strcmp(op, "&&") == 0 || strcmp(op, "||") == 0)
            {
                fprintf(out, "<span class=\"operator\">%s</span>", op);
            }
            else
            {
                ungetc(next, fp);
                fprintf(out, "<span class=\"operator\">%c</span>", ch);
            }
            continue;
        }

        /* ================= SYMBOL ================= */
        if (is_symbol(ch))
        {
            fprintf(out, "<span class=\"symbol\">%c</span>", ch);
            continue;
        }

        /* ================= SAFE OUTPUT ================= */
        if (ch == '<')
            fprintf(out, "&lt;");
        else if (ch == '>')
            fprintf(out, "&gt;");
        else if (ch == '&')
            fprintf(out, "&amp;");
        else
            fputc(ch, out);
    }
}
