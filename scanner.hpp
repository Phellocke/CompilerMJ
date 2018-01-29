#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__

#include "source.hpp"
#include "error.hpp"
#include "token.hpp"

class Scanner {

    public:
        Scanner();
        Scanner(Source &in);
        ~Scanner();
        Token *nextToken();

    private:
        Source *in;
        char *buffer;
        int bindex, bsize;
        void init_buffer();
        void reset_buffer();
        void append_buffer(char c);
        void free_buffer();
        int nextCh();
        int row,col;
};

#endif
