
# WordCount
Semestral project for the subject **[B6B36PJC](https://www.fel.cvut.cz/en/education/bk/predmety/31/30/p3130206.html)** on **[FEE CTU](https://www.fel.cvut.cz/)** in winter semester 2019.
# Task
**Word Count**
- A typical problem with simple parallelization.
- The input is a set of files, the output is an ordered listing of the words and their frequency.
- In addition to words, the so-called n-grams can be counted.

*(Translated from Czech original)*

# Implementation
## Overview
- **Written in:** [C++14](https://en.wikipedia.org/wiki/C%2B%2B)
- Supports multiple threads (One thread processing one file)
 ## Build
```bash
git clone https://github.com/Baterka/WordCount.git
cd WordCount
mkdir Release
cd Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
## [Speed measurement](https://github.com/Baterka/WordCount/wiki/Speed-measurement)
## Usage
- [WordCount](https://github.com/Baterka/WordCount/wiki/WordCount) - *Creates dictionary of words (or n-grams) contained in input files and counts their frequency.*
- [Generator](https://github.com/Baterka/WordCount/wiki/Generator) - *A utility to generate multiple word files with random words in them.*
- [Tests](https://github.com/Baterka/WordCount/wiki/Tests) - *Unit tests (WIP)*
