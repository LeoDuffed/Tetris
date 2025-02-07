#ifndef Colors_H
#define Colors_H
#include<iostream>
#include <raylib.h>
#include <vector> 
#pragma once
using namespace std;

extern const Color darkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;

vector<Color> GetCellColors();

#endif