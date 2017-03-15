#if !defined _DEFS_H_
#define _DEFS_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

struct Vertex{
	char name;
	int color;
	Vertex* next;	
};

int GraphColoring(FILE* f, Vertex* &v);

#endif

