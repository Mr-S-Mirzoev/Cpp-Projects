# How to build and use

## If you don't have CMake installed, install it as:

  - Linux

    sudo apt-get install cmake 

  - MacOS

    brew install cmake 

If your current folder is "German Words Trainer", build this as:

    cmake -B build
    make -C build

Start this as simple as 

    ./build/deutsch <input_file> 
    
or 

    ./build/deutsch <input_file> <output_file>

Note that you can move binary file ./build/deutsch wherever you wish.

# Special thanks:

[Ben Strasser's Fast C++ CSV reader](https://github.com/ben-strasser/fast-cpp-csv-parser)