#ifndef C_FILE_H_SER
#define C_FILE_H_SER

#include <stdlib.h>
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
    C_File(C_File &&oth);
    C_File(std::string const& filename, std::string const &mode, bool tmp = true);

    C_File& operator=(C_File &&oth);

    bool finished() const { return finished_reading; }
    bool readline(std::string &s);
    void writeline(std::string &s);

    ~C_File();
};

#endif //C_FILE_H_SER