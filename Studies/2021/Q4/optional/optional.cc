#include <iostream>
#include <optional>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class C_File
{
    FILE* fp;
    char* line = NULL;

public:
    C_File(std::string const& filename, std::string const& mode)
        : fp(fopen(filename.c_str(), mode.c_str()))
    {
        if (fp == NULL)
            exit(EXIT_FAILURE);
    }

    std::optional<std::string> readline()
    {
        size_t len = 0;
        ssize_t read;
        std::string s;

        if ((read = getline(&line, &len, fp)) != -1)
        {
            if (line[read - 1] == '\n')
                line[read - 1] = 0;
            s = line;
            return s;
        }

        return std::nullopt;
    }

    ~C_File()
    {
        fclose(fp);
        if (line)
            free(line);
    }
};

int main(void)
{
    C_File f("input.txt", "r");

    while (auto s = f.readline())
    {
        std::cout << *s << std::endl;
    }
}