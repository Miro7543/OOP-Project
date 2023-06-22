#pragma once
#ifndef FILES_H
#define FILES_H

#include "Curves.h"
#include "Shapes.h"

class File
{
private:
	string path;
	string data;
	string name;
	string getFileName();
	Group* svg;
	bool opened;
	void genShapes();
	int getIndex();
	void printShapesFromVector(vector<BasicShape *>&);
public:
	File();
	void open();
	void close();
	void save();
	void saveAs();
	void help();
	void print();
	void create();
	void translate();
	void erase();
	void within();
	void area();
	void perimeter();
	void length();
	string getData();
};

#endif