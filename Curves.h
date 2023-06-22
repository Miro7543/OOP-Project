#pragma once
#ifndef CURVES_H
#define CURVES_H

#include "Funcs.h"

class Line : public Curve
{
private:
    Point start, end;
    void fillArguments(const map<string,string>&);


public:
    Line(Point s, Point e);
    Line(string s, string e);
    Line();
    Region getRegion()const;    
    double getLength()const;
    Point getStart()const;
    Point getEnd()const;
    BasicShape* clone();
    void translate(double,double);
    bool isInsideCircle(vector<BasicShape*>&, Circle1)const;
    string serializeShape()const;
    void getInfo()const;
    
    
};

class PolyLine : public Curve
{
private:
    vector<Line> lines;
    void fillArguments(const map<string,string>&);

public:
    PolyLine(vector<Line>& l);
    PolyLine(vector<Point>points);
    PolyLine();
    Region getRegion()const;
    double getLength()const;
    BasicShape* clone();
    void translate(double,double);
    bool isInsideCircle(vector<BasicShape*>&, Circle1)const;
    string serializeShape()const;
    void getInfo()const;
    
};
#endif