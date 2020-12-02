# fake-trasnlator
This is the second assignment for the System Software discipline, which will trasnlate code in a fake assembly language into Intel's IA-32 assembly, which can be assembled by `NASM` and linked by `ld`

## Compilation Instructions

A makefile can be found on the root directory. Once in there, type `make` to initiate the compilation process. On the same directory, an executable named `tradutor` will be found.

### Input
To execute this program, you must provide a `.asm` assembly file, written in the fake-assembly languade (you can fin a working assembler [here](https://github.com/JoaoPedroAssis/fake-assembler)). An example is shown bellow

```
./tradutor test.asm
```

Some examples can be found in the `assets` directory

### Output
The primary output of this program is a `.s` file written in IA-32 assembly. This code can be assembled with:

```
nasm -f elf32 -o test.o test.s
```

And linked with:

```
ld -m elf_i386 -o test test.o
```

The `tradutor` executable will perform both steps automatically, so along with the `.s` output, a working binary will also be provided



---
Programmed by João Pedro Assis for the System Software discipline at Universidade de Brasília - 11/10/2020 😎