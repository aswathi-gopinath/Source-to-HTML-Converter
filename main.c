#include"header.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./a.out file.c\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror("File error");
        return 1;
    }

    //output html file
    char output_file[100];
    strcpy(output_file, argv[1]);

    /*.c to .html*/
    char *dot = strrchr(output_file, '.'); 
    if(dot)
        strcpy(dot, ".html");
    else
        strcat(output_file, ".html");

    FILE *fd = fopen(output_file, "w");
    if(fd == NULL)
    {
        perror("Output file error");
        return 1;
    }
    
    html_begin(fd);
    tokenize(fp, fd);
    html_end(fd);

    fclose(fp);
    fclose(fd);

    return 0;
}
