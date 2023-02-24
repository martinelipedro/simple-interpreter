#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdlib.h>
#include <stdio.h>

char* get_file_contents(char* filepath)
{
    char* buffer = (void*)0;
    long lenght;

    FILE* file = fopen(filepath, "rb");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        lenght = ftell(file);
        fseek(file, 0, SEEK_SET);

        buffer = calloc(lenght, lenght);
        if (buffer)
        {
            (void)!fread(buffer, 1, lenght, file);
        }

        fclose(file);
        return buffer;
    }

    printf("File not found or error while reading file: %s\n", filepath);
    exit(1);
}

#endif