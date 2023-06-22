#pragma once
#ifndef SHAPES_H
#define SHAPES_H

#include "Funcs.h"

//-------------------------------------------------------------------------
class Circle : public Shape
{
private:
    Point center;
    double radius;
    void fillArguments(const map<string,string>&);

public:
    Circle(Point center, double r);
    Circle();
    double getArea()const;
    double getPerimeter()const;
    double getRadius()const;
    Point getCenter()const;
    Region getRegion()const;
    BasicShape *clone();
    void translate(double,double);
    bool contains(Point p)const;
    bool isInsideCircle(vector<BasicShape*>&, Circle1)const;
    string serializeShape()const;
    void getInfo()const;
    
};


//-------------------------------------------------------------------------
class Rect : public Shape
{
private:
    Point start;
    double width, heigth;
    double rx, ry;
    void fillArguments(const map<string,string>&);

public:
    Rect(Point Start, double Width, double Heigth);
    Rect(Point Start, double Width, double Heigth, double RX, double RY);
    Rect();
    Region getRegion()const;
    double getArea()const;
    double getPerimeter()const;
    BasicShape* clone();
    void translate(double,double);
    bool isInsideCircle(vector<BasicShape*>&, Circle1)const;
    string serializeShape()const;
    void getInfo()const;
    
};


//-------------------------------------------------------------------------
class Ellipse : public Shape
{
private:
    Point center;
    double radiusX;
    double radiusY;
    void fillArguments(const map<string,string>&);

public:
    Ellipse(Point center, double rx, double ry);
    Ellipse();
    double getArea()const;
    double getPerimeter()const;
    Region getRegion()const;
    BasicShape* clone();
    void translate(double,double);
    bool isInsideCircle(vector<BasicShape*>&, Circle1)const;
    string serializeShape()const;
    void getInfo()const;
    
};


//-------------------------------------------------------------------------
class Polygon : public Shape
{
private:
    vector<Point> points;
    void fillArguments(const map<string,string>&);

public:
    Polygon(const vector<Point> &p);
    Polygon();
    Region getRegion()const;
    double getArea()const;
    double getPerimeter()const;
    BasicShape* clone();
    void translate(double,double);
    bool isInsideCircle(vector<BasicShape*>&, Circle1)const;
    string serializeShape()const;
    void getInfo()const;
    
 };
 
#endif