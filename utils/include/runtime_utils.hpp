#pragma once

#include <execinfo.h>
#include <unistd.h>
#include <map>
#include <fstream>
#include <iostream>

class RuntimeUtils {
public:
    static void printStackTrace() {
        const int MAX_CALLSTACK = 100;
        void * callstack[MAX_CALLSTACK];
        int frames;

        // get void*'s for all entries on the stack...
        frames = backtrace(callstack, MAX_CALLSTACK);

        // print out all the frames to stderr...
        backtrace_symbols_fd(callstack, frames, STDERR_FILENO);
    }

    static std::map<std::string, std::string> getConfiguration(std::string filename) {
        std::fstream fs;
        fs.open(filename, std::ios_base::in);
        std::map<std::string, std::string> cfg;
        if(!fs.is_open())
            std::cout << "Error in openning configuration script.\n" ;
        else
            while(!fs.eof()) {
                std::string line;
                std::getline(fs, line, '\n');
                for(int i = 0; i < line.size(); i++)
                    if(line[i] == ':')
                        cfg[line.substr(0,i)] = line.substr(i+1,line.size() - i+1);
            }
        return cfg;
    }
};
