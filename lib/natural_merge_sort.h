#ifndef NATURAL_MERGE_SORT_
#define NATURAL_MERGE_SORT_
#include <fstream>
#include <iostream>
void PrintFile(const char*);
void Sort(const char* name);
void Split(std::fstream& A, std::fstream* F);
void Merge();
#endif