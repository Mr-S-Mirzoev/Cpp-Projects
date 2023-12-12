#include "c_file.h"

#include <stdexcept>

C_File& C_File::operator=(C_File&& oth)
{
    fp = oth.fp;
    line = oth.line;
    mode = oth.mode;
    tmp = oth.tmp;
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
        free(line);
        return true;
    }

    s = "";
    finished_reading = true;
    return false;
}

bool C_File::finished() const { return finished_reading; }

void C_File::writeline(std::string& s, bool newline)
{
    if (mode != WRITE)
        throw std::logic_error("writing to file with \"r\" perms");

    if (s == "")
        return;

    if (newline)
        fprintf(fp, "%s\n", s.c_str());
    else
        fprintf(fp, "%s", s.c_str());
}

void C_File::close()
{
    if (fp)
        fclose(fp);

    fp = nullptr;
}

C_File::~C_File()
{
    close();

    if (line)
        free(line);
    if (tmp)
        remove(filename.c_str());
}
