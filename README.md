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
`clang++ -std=c++11 main.cpp -o m -lsqlite3` or
`g++ -std=c++11 main.cpp -o m -lsqlite3`
then run `./m`

The main file sets up the database, setting up the table with 'schema_setup.sql' and populating the table with 'data_population.sql'.

To run the test cases, uncomment the line in main.cpp to replace the console input with the test case file:

```
freopen("case1_test.txt", "r", stdin); // replaces input from console with input from test case file
```

in `main.cpp` and then recompile & run the program.

## Authors

- Example project for class created by Sadie Forbes
- {Zach James, Berend Brandt, Shalvi, Joshua Pugh, Steven Reed [Fill your name here]()}

## Test Queries

1. INSERT INTO USER (Phone, Email, Password, FirstName, LastName, Address, PlanID, PaymentInfo) VALUES ('2255784474', 'mjasim@lsu.edu', 'somereallybadpassword', 'Mahmood', 'Jasim', '3209G Patrick F Taylor Building', 1, 'Visa **** 1111'), ('2255782624', 'goldenrichard1@lsu.edu', 'somereallygoodpassword', 'Golden', 'Richard', '1081A Digital Media Center', 2, 'Mastercard **** 2222');

2. SELECT Password FROM user WHERE FirstName = 'Mahmood' AND LastName = 'Jasim';

