# RobonTL 

RobonTL is a C++ library for ROBust ONline monitoring of signal Temporal Logic. 

## Compilation

RobonTL is written in C++ with no special requirement. A makefile is provided that compiles every source file in `src` folder, and creates a simple static library file called `robonlib.a`. 
```
make all
```

## Testing

A simple program is given in the `test` folder. 

```
g++ test_prog.cpp ../lib/robonlib.a -I ../include -o test_prog
```
