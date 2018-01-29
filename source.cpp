#include "source.hpp"

Source::Source(const char *name, int tw) {
    this->filename = name;
    this->input = new ifstream(name);
    this->tabwidth = tw;
    this->r = this->c = 1;
    this->lastr = this->lastc = 0;
}

Source::Source(istream &in, int tw) {
    this->input = &in;
    this->tabwidth = tw;
    this->r = this->c = 1;
    this->lastr = this->lastc = 0;
}

Source::Source(int tw) {
    this->filename = "<cin>";
    this->input = &cin;
    this->tabwidth = tw;
    this->r = this->c = 1;
    this->lastr = this->lastc = 0;
}

const char *Source::name() {
    return this->filename;
}

bool Source::eof() {
    return this->input->eof();
}

int Source::get() {
    int c = -1;                                     // eof by default
    if (!this->input->eof()) {
        this->lastr = this->r;
        this->lastc = this->c;
        c = this->input->get();
        if (c == '\r' || c == '\n') {               // Mac or Unix EOL
            if (c == '\r' && this->input->peek() == '\n')  // DOS style EOL
                c = this->input->get();
            ++this->r;
            this->c = 1;
        } else if (c == '\t')
            this->c =                               // calculate the tab column
                this->c/this->tabwidth * this->tabwidth + this->tabwidth;
        else
            ++this->c;
    }
    return c;
}

void Source::unget() {
    this->input->unget();
    this->r = this->lastr;
    this->c = this->lastc;
}

int Source::peek() {
    return this->input->eof()?-1:this->input->peek();
}

int Source::tabsize() {
    return this->tabwidth;
}

int Source::row() {
    return this->r;
}

int Source::col() {
    return this->c;
}