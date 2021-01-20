#include "database.hpp"
#include "csv_parser.hpp"
#include "runner.hpp"

#include <iostream>
#include <sys/stat.h>
#include <csignal>

Training *current_training = nullptr;

inline bool file_exists_test (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage:" << std::endl;
        std::cerr << "./deutsch data.csv - file data.csv will be overwritten if changes applied" << std::endl;
        std::cerr << "./deutsch in.csv out.csv - changes will be written to out.csv" << std::endl;
        exit(1);
    }

    if (!file_exists_test(argv[1])) {
        std::cerr << "File " << argv[1] << " doesn't exist. Check the filename and try again."<< std::endl;
        exit(1);
    }

    struct sigaction action;
    action.sa_handler = sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, 0);

    try {
        if (argc == 2) {
            DataBase db(argv[1]);
            Runner runner(db);
        } else {
            DataBase db(argv[1], argv[2]);
            Runner runner(db);
        }
    } catch (io::error::base &e) {
        std::cerr << "An exception caught during handling the csv file." << std::endl;
        std::cerr << "Exception message: \" " << e.what() << " \"" << std::endl;
    }

    return 0;
}
