# Jason Compiler
This is a sysY compiler for the Compiling Principles. It could generate two kind of intermediate representations which is Eeyore and Tigger and the corresponding RISC-V instructions from sysY language
## Compilation
First use flex.
```
$ flex -o lex.yy.cpp source.l
```
Then use bison
```
$ bison -d -o source.tab.cpp source.y
``` 
Finally compile with g++ (because makefile is prohibited by the platform)
```
g++ -Wno-register -O2 -lm -std=c++17 main.cpp driver.cpp global.cpp ir.cpp irgen.cpp lex.yy.cpp source.tab.cpp -o main -Idirs
```
## Usage
```
./main -S [-e|-t] testcase.sy [-o testcase.S]
```
