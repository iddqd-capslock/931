#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int f_size_file(FILE* onegin);

int count_lines ( char* buffer,int size_file);

void find_str(char**index,char* buffer,int size_file);

int comp(char** first, char** second);

void bubble_sort(char** index,const int line_cnt);

void swap_index(char* first,char* second);


int main ()
{
    FILE* onegin = fopen("Text.txt","r");
    int size_file;
    char* buffer;

    size_file = f_size_file(onegin);
    buffer = (char*) calloc(size_file, sizeof(char));
    fread(buffer + 1, sizeof(char), size_file, onegin);
    fclose(onegin);

    int line_cnt;
    line_cnt = count_lines(buffer, size_file);

    char** index;
    index = (char**) calloc (line_cnt, sizeof (char*));
    buffer[0] = '\n';
    find_str(index,buffer,size_file);

    bubble_sort(index, line_cnt);

    int i;
    for (i = 0; i <= size_file; ++i)
        if (buffer[i] == '\n')
            buffer[i] = '\0';

    FILE* output = fopen("result_first.txt", "w");

    for ( i = 0 ; i < line_cnt; ++i)
    {
        fputs (index[i+1], output);
        fputc ('\n', output);
    }

    fclose (output);
    free (index);
    free (buffer);
}





int f_size_file(FILE* onegin)
{
    int size_file;
    fseek(onegin,0,SEEK_END);
    size_file=ftell(onegin);
    fseek(onegin,0,SEEK_SET);
    return size_file;
}


int count_lines ( char* buffer,int size_file)
{
    int i, lines; lines = 0;
    for (i = 0; i < size_file; i++)
    {
        if (buffer[i] == '\n') lines++;
    }
    return lines;
}

void find_str(char**index,char* buffer,int size_file)
{
    int  i, line;
    for (i=0; i < size_file; i++)
    {
        if (buffer[i] == '\n')
            index[line++] = &buffer[i];
    }
}

int comp(const char* first,const char* second)
{
    ++first; ++second;
    while(true)
    {
        while (*first != '\n' && !isalpha (*first)) ++first;
        while (*second != '\n' && !isalpha (*second)) ++second;
        if (*first == '\n' && *second == '\n') return 0;
        if (*first == '\n'|| tolower (*first) < tolower (*second))  return 0;
        if (*second == '\n'|| tolower (*first) > tolower (*second))  return 1;
        ++first; ++second;
    }
    return 0;
}

void bubble_sort(char** index,const int line_cnt)
{
    int n, i; char* c;
    n = line_cnt - 1;
    while (n >= 0)
    {
        for (i = 0; i < n; ++i)
            if (comp(index[i], index[i + 1])){
                 c = index[i]; index[i] = index[i+1]; index[i+1] = c;
        }
        --n;
    }
}

void swap_index(char* first,char* second)
{
    char* c;
    c = first; first = second; second = c;
}



