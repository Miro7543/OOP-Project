#pragma once
#ifndef FUNCS_H
#define FUNCS_H

#include "Misc.h"


double unsignedDouble(double x);

double distance(Point p1,Point p2);

string toString(double num);

void splitter(vectS& res,const string original,const string delimiter);

void remover(string &original,string substr);

string trim(string &str);

void getTokens(string data,queS& res);

void replaceSubstring(string& str, string oldSubstr,string newSubstr);

void toPoints(string s,vector<Point>& res);

bool endsWith(string original,string suffix);

#endif