#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "shell.hpp"
#include "source.hpp"
#include "parser.hpp"

int exit_code = 0;

int tabwidth    = DEFTABSIZE;
bool use_stdin  = false;
char *filename  = NULL;

void processCmdLine(char *args[]);

int main(int argc, char *argv[]) {
    Source in;
    int errors = 0;

    processCmdLine(argv);

    std::cout << COMPILER << " compiler, v" << VERSION << "." << REVISION << "." << PATCH << std::endl;

    if (filename != NULL) {
        if (! std::fstream(filename)) {
			std::cerr << "ERROR: file not found: " << filename << std::endl;
			std::exit(1);
        }
        in = Source(filename, tabwidth);
        if (use_stdin)
            std::cerr << "WARNING: -stdin ignored, using \"" << filename << "\" for input" << std::endl;
    } else if (use_stdin) {
        in = Source(cin, tabwidth);
    } else { // no input
        std::cout << "no input specified" << std::endl;
        std::exit(exit_code);
    }

    Parser parser(in);

    errors = parser.parse();

    if (errors==0) {
        std::cout << "compile successful" << std::endl;
    } else {
        std::cout << "compile failed: " << errors << " errors detected" << std::endl;
    }

    return exit_code;
}

void processCmdLine(char *args[]) {
    int i;
    char *opt, *arg;

    for (i=1; args[i] != NULL && args[i][0] == '-'; ++i) {
        opt = strtok(args[i],":=");
        arg = strtok(NULL, "");
        if (opt==NULL) {
            std::cerr << "ERROR: missing option" << std::endl;
            std::exit(1);
        } else if (strcmp(opt, "--help")==0 || strcmp(opt, "-h")==0 || strcmp(opt, "-?")==0) {
            std::cout << args[0] << " <options> filename.cmm" << std::endl;
            std::cout << "\t--help\t\tprint this help message (or -h, -?)" << std::endl;
            std::cout << "\t--version\tprint the version number (or -v)" << std::endl;
            std::cout << "\t--tabwidth:n\tset tabwidth to n (or -t:n)" << std::endl;
            std::cout << "\t--stdin\t\tset input to stdin (or --)" << std::endl;
            exit(exit_code);
        } else if (strcmp(opt, "--version")==0 || strcmp(opt, "-v")==0) {
            std::cout << VERSION << "." << REVISION << "." << PATCH << std::endl;
            exit(exit_code);
        } else if (strcmp(opt, "--tabwidth")==0 || strcmp(opt, "-t")==0) {
            tabwidth = 4;
        } else if (strcmp(opt, "--stdin")==0 || strcmp(opt, "--")==0) {
            use_stdin = true;
        } else {
            std::cerr << "ERROR: unknown option: " << opt << std::endl;
            std::exit(1);
        }
    }
    
    if (args[i] != NULL) {
        filename = args[i];
        if (args[i+1] != NULL) {
            std::cout << "ERROR: unprocessed options" << std::endl;
        }
    }
}