#pragma once
#ifndef MISC_H
#define MISC_H

#include "AttributeMaps.h"

#define queS queue<string>
#define vectS vector<string>
#define vectBS vector<BasicShape*>
class Group;//Forward declaration for G_BS
#define G_BS pair<Group*,BasicShape*>

enum ShapeID
{
    RECTANGLE = 1,
    CIRCLE,
    ELLIPSE,
    LINE,
    POLYLINE,
    POLYGON,
    GROUP
};

struct Point
{
    double x;
    double y;
    Point(string s);
    Point(string X,string Y);
    Point(double X,double Y);
    Point();
    void translate(double offX,double offY);
};

class Region
{
private:
    double supX, supY, infX, infY;

public:
    Region(double up, double down, double left, double rigth);
    Region();
    Region(Point start, double width, double heigth);
    Region(Point,Point);
    double getSupX()const;
    double getSupY()const;
    double getInfX()const;
    double getInfY()const;
    bool contains(Region)const;
};

struct Circle1{
    Point c;
    double r;
    bool contains(Point)const;
    bool contains(Region)const;
    Circle1(Point,double);
};



class BasicShape
{
private:
    virtual void fillArguments(const map<string, string>&)=0;

protected:
    ShapeID ID;
    string fill="black";
    string stroke="none";
    unsigned int stroke_width=1;

public:
    BasicShape(ShapeID id);
    string getType() const;
    virtual Region getRegion()const=0 ;
    virtual BasicShape* clone() = 0;
    virtual ~BasicShape() = default;
    virtual void Print(int&,vector<BasicShape *>&)=0;
    virtual void translate(double,double) = 0;
    virtual bool isInsideCircle(vector<BasicShape*>&,Circle1)const=0;
    virtual string serializeShape()const= 0;
    
    virtual void genFromQueue(queue<string>& tokens);
    virtual G_BS getNthShape(int&,int);
    void readAttributes();
};

class Circle;

class Shape:public BasicShape
{
private:
    virtual void fillArguments(const map<string,string>&)=0;
public:
    Shape(ShapeID id);
    virtual double getArea()const=0 ;
    virtual double getPerimeter()const=0 ;
    virtual Region getRegion()const=0 ;
    virtual BasicShape* clone() = 0;
    virtual void translate(double,double) = 0;
    virtual bool isInsideCircle(vector<BasicShape*>&,Circle1)const=0 ;
    virtual string serializeShape() const= 0 ;
    
    void Print(int&,vector<BasicShape *>&);
};



class Curve :public BasicShape
{
private:
    virtual void fillArguments(const map<string,string>&)=0;
public:
    Curve(ShapeID);
    virtual double getLength()const = 0 ;
    virtual Region getRegion()const = 0 ;
    virtual BasicShape* clone() = 0;
    virtual void translate(double,double) = 0;
    virtual bool isInsideCircle(vector<BasicShape*>&,Circle1)const=0 ;
    virtual string serializeShape() const= 0 ;
    
    void Print(int&,vector<BasicShape *>&);
};

class Group:public BasicShape
{
private:
    int depth;
    void fillArguments(const map<string,string>&);
    vector<BasicShape*> shapes;
    bool root=false;

public:
    Group();
    Group(int depth);
    Group(int,bool);
    ~Group();
    void clear();
    Region getRegion() const;
    void addElement(BasicShape *f);
    BasicShape* clone();
    void genFromQueue(queS& tokens)override;
    void Print(int&,vector<BasicShape *>&);
    void readAttributes();
    void translate(double,double);
    G_BS getNthShape(int&,int)override;
    void eraseShape(BasicShape*);
    void shapesWithin(vector<BasicShape*>&,Region) const;
    void shapesWithin(vector<BasicShape*>&,Circle1) const;
    bool isInsideCircle(vector<BasicShape*>&,Circle1)const;
    string serializeShape()const;
};

#endif