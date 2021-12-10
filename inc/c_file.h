#ifndef C_FILE_H
#define C_FILE_H

#include <cstdio>
#include <stdexcept>
#include <string>

class C_File {
    FILE *fp = NULL;
    char *line = NULL;

    enum {
        READ,
        WRITE
    };

    bool mode = false;
    bool finished_reading = false;
    bool tmp = false;
    std::string filename;
public:
    C_File() {};
    C_File(C_File &&oth): fp(oth.fp), line(oth.line), 
                          mode(oth.mode), finished_reading(oth.finished_reading), 
                          tmp(oth.tmp), filename(oth.filename) {
        oth.fp = NULL;
        oth.line = NULL;
    }
    C_File(std::string const& filename, std::string const &mode, bool tmp = false): 
        fp(fopen(filename.c_str(), mode.c_str())), mode(mode == "w"), tmp(tmp), filename(filename) 
    {
        if (fp == NULL)
            throw std::logic_error("Failed to open: " + filename);
    }

    C_File& operator=(C_File &&oth);

    bool readline(std::string &s);
    bool finished() const;
    void writeline(std::string &s, bool newline = true);

    void close();

    ~C_File();
};

#endif // C_FILE_H