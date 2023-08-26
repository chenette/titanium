# titanium

to run separated files:
``` bash
gcc -c lexer.c -o lexer.o
gcc parser.c lexer.o -o parser
./parser
```

to run compined files:
``` bash
gcc lexer_parser.c -o lexer_parser
./lexer_parser
```