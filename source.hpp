#ifndef __SOURCE_HPP__
#define __SOURCE_HPP__

#include <iostream>
#include <fstream>
#include <cstdlib>

#define DEFAULTTAB  8

using namespace std;

class Source {
    public:
        Source(const char *name, int tw=DEFAULTTAB);// opens file "name" for input
        Source(istream &in, int tw=DEFAULTTAB);     // uses previously opened file
        Source(int tw=DEFAULTTAB);                  // uses cin (stdin)
        const char *name(); // name of open file
        bool eof();         // true if eof found
        int get();          // read next character
        void unget();       // put back the last character read, call to get must follow before another call to unget
        int peek();         // look into input without reading
        int tabsize();      // known tab size of text
        int row();          // current row (of next read)
        int col();          // current col (of next read)

    private:
        const char *filename = NULL;// if NULL, initialized without name
        istream *input = NULL;      //
        int tabwidth = DEFAULTTAB;  // used in calculating col
        int r, c;                   // row, col of next character to read
        int lastr, lastc;           // used to remember if unget called
};

#endif