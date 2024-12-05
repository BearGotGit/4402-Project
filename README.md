<!-- @format -->

# Example 4402 Database Project

## Introduction

This project encompasses a C++ command line interface (CLI) program that interacts with a SQLite database.

## Prerequisites

Before running the project, ensure you have the following prerequisites installed on your system:

- C++ compiler (clang++ or g++)
- [sqlite3](https://www.sqlite.org/download.html)

For sqlite3:
- [Windows Install & Path Update Tutorial](https://www.youtube.com/watch?v=XA3w8tQnYCA)
- [Mac Homebrew Install Tutorial](https://www.youtube.com/watch?v=2CAspm7YwTU) (time 5:20)
- Arch: `sudo pacman -S sqlite3`

(Optional - for diagram.md view) Mermaid Diagram VS Code Extension:
- [Mermaid Diagram](https://marketplace.visualstudio.com/items?itemName=bierner.markdown-mermaid)

## CLI Notes

To compile & run:
`clang++ main.cpp -o m -lsqlite3` or
`g++ main.cpp -o m -lsqlite3`
then run `./m`

The main file sets up the database, setting up the table with 'schema_setup.sql' and populating the table with 'data_population.sql'.

To run the test cases, uncomment the line in main.cpp to replace the console input with the test case file:
```
freopen("case1_test.txt", "r", stdin); // replaces input from console with input from test case file
```
in `main.cpp` and then recompile & run the program.

## Authors

- Example project for class created by Sadie Forbes
- {Zach James, Berend Brandt, Shalvi, Joshua Pugh, [Fill your name here]()}