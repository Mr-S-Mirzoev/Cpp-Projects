#include "c_file.h"
#include <stdexcept>

C_File::C_File(C_File&& oth)
    : fp(oth.fp), line(oth.line), mode(oth.mode), finished_reading(oth.finished_reading),
      tmp(oth.tmp), filename(oth.filename)
{
    oth.fp = NULL;
    oth.line = NULL;
}

C_File::C_File(std::string const& filename, std::string const& mode, bool tmp)
    : fp(fopen(filename.c_str(), mode.c_str())), mode(mode == "w"), tmp(tmp), filename(filename)
{
    if (fp == NULL)
        exit(EXIT_FAILURE);
}

C_File& C_File::operator=(C_File&& oth)
{
    fp = oth.fp;
    line = oth.line;
    mode = oth.mode;
    finished_reading = oth.finished_reading;
    oth.fp = NULL;
    oth.line = NULL;

    return *this;
}

bool C_File::readline(std::string& s)
{
    if (mode != READ)
        throw std::logic_error("reading from file with \"w\" perms");

    ssize_t read;
    size_t len = 0;

    if ((read = getline(&line, &len, fp)) != -1)
    {
        if (line[read - 1] == '\n')
            line[read - 1] = 0;
        s = line;
        return true;
    }

    finished_reading = true;
    return false;
}

void C_File::writeline(std::string& s)
{
    if (mode != WRITE)
        throw std::logic_error("writing to file with \"r\" perms");

    fprintf(fp, "%s\n", s.c_str());
}

C_File::~C_File()
{
    if (fp)
        fclose(fp);
    if (line)
        free(line);
    if (tmp)
        remove(filename.c_str());
}