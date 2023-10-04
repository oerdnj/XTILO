# Turing Machine Implementation

A simple implementation of Turing Machine in C++.  It implements "infinite" tape
in both directions - if the current head position goes outside of the tape
dimensions, the tape is expanded in that direction (in very inefficient manner
though).

## Compile

This projects uses Meson build system and is written in C++17 and can be built
as follows:

```
meson setup builddir
cd builddir
ninja
```

## Syntax

## Syntax for writing your own program for Turing simulator

This Turing Machine can run the examples from: http://morphett.info/turing/turing.html, so their syntax directly matches ours.

* Each line should contain one tuple of the form `<current state> <current symbol> <new symbol> <direction> <new state>`.
* You can use any number or word for `<current state>` and `<new state>`, eg. `10`, `a`, `state1`. State labels are case-sensitive.
* You can use almost any character for `<current symbol>` and `<new symbol>`, or `_` to represent blank (space). Symbols are case-sensitive.
* You can't use `;`, `*`, `_` or whitespace as symbols.
* `<direction>` should be `l`, `r` or `*`, denoting 'move left', 'move right' or 'do not move', respectively.
* Anything after a `;` is a comment and is ignored.
* The machine halts when it reaches any state starting with 'halt', eg. halt, halt-accept.

## Run

```
./tm <tape> <inputfile>
```

Tape can contain `_` or ` ` (space) to represent blank (space).

## Examples

See `examples` directory in the source tree or http://morphett.info/turing/turing.html

## References

The code has been inspired by following GitHub projects:

* https://github.com/saisubham/turing-machine-simulator.git
* https://github.com/sina-rostami/Turing-Machine-Implementation.git

It implements the syntax from http://morphett.info/turing/turing.html
