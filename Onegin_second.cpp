#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

long f_size_file (FILE* onegin);

long count_lines ( char* buffer,long size_file);

int compare_backward (const char* first, const char* second);

void bubble_sort (char** index, long line_cnt);

char* find_start (char* end);

void swap_index(char** index, int i);

int main ()
{
    char* buffer;
    FILE* onegin;
    onegin = fopen ("Text.txt","r");

    long size_file;
    size_file = f_size_file (onegin);
    buffer = (char*) calloc ( size_file + 1, sizeof (char));

    fread (buffer + 1, sizeof (char), size_file, onegin);
    fclose (onegin);

    long line_cnt = count_lines (buffer, size_file);
    char** index; int i, j = 0;
    index = (char**) calloc (line_cnt, sizeof (char*));

    for ( i = 0; i <= size_file; ++i)
       {
       if (buffer[i] == '\n')
          {
           index[j++] = &buffer[i];
          }
       }

    buffer[0] = '\n';

    bubble_sort ( index, line_cnt);

    for (i = 0; i <= size_file; ++i)
        if (buffer[i] == '\n')
            buffer[i] = '\0';

    FILE* output = fopen("result_second.txt", "w");

    for ( i = 0 ; i < line_cnt; ++i)
    {
        fputs (find_start (index[i]), output);
        fputc ('\n', output);
    }

    fclose (output);
    free (index);
    free (buffer);
}


long f_size_file (FILE* onegin)
{
    long size_file;
    fseek (onegin, 0, SEEK_END);
    size_file = ftell (onegin);
    fseek (onegin, 0, SEEK_SET);
    return size_file;
}


long count_lines ( char* buffer,long size_file)
{
    int i, lines; lines = 0;
    for (i = 0; i < size_file; i++)
    {
        if (buffer[i] == '\n') lines++;
    }
    return lines;
}


int compare_backward (const char* first, const char* second)
{
    --first; --second;
    while(true)
    {
        while (*first != '\n' && !isalpha (*first)) --first;
        while (*second != '\n' && !isalpha (*second)) --second;
        if (*first == '\n' && *second == '\n') return 0;
        if (*first == '\n'|| tolower (*first) < tolower (*second))  return 0;
        if (*second == '\n'|| tolower (*first) > tolower (*second))  return 1;
        --first; --second;
    }
    return 0;
}


void bubble_sort (char** index, long line_cnt)
{
    int n, i;
    n = line_cnt - 1;
    while (n >= 0)
    {
        for (i = 0; i < n; ++i)
            if (compare_backward (index[i], index[i+1]))
            swap_index(index, i);
        --n;
    }
}

void swap_index(char** index, int i)
{
    char* c;
    c = index[i]; index[i] = index[i+1]; index[i+1] = c;
}


char* find_start (char* end)
{
    for(; *(end - 1) != '\0'; --end);
    return end;
}
