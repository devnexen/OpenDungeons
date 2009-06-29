#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Globals.h"
#include "Tile.h"

void readGameMapFromFile(string fileName);
void writeGameMapToFile(string fileName);
double randomDouble(double min,double max);
double gaussianRandomDouble();
void seedRandomNumberGenerator();
void swap(int &a, int &b);
string colourizeMaterial(string materialName, int color);

#endif

