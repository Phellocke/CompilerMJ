#include <cstdio>
#include "Scanner.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    if (argc>1) {
      if ((input = fopen(argv[1],"r")) == NULL) {
        fprintf(stderr, "file '%s' not found\n", argv[1]);
        exit(1);
      }
    }

    Scanner *scanner = new Scanner(input);
    Parser *parser = new Parser(scanner);
    parser->Parse();

    printf("%d errors detected\n", parser->errors->count);
    return parser->errors->count;
}
