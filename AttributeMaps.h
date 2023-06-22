#pragma once
#ifndef ATTRIBUTEMAPS_H
#define ATTRIBUTEMAPS_H
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

//Shapes-------------------------------------------------
const map<string,string> circleAttributes={
    {"cy","0"},
    {"cx","0"},
    {"r","0"},
    {"stroke","default"},
    {"fill","default"},
    {"stroke-width","0"},  
};

const map<string,string> ellipseAttributes={
    {"cy","0"},
    {"cx","0"},
    {"rx","0"},
    {"ry","0"},
    {"stroke","default"},
    {"fill","default"},
    {"stroke-width","0"},  
};

const map<string,string> rectangleAttributes={
    {"y","0"},
    {"x","0"},
    {"width","0"},
    {"height","0"},
    {"ry","0"},
    {"rx","0"},
    {"stroke","default"},
    {"fill","default"},
    {"stroke-width","0"},
    
};

const map<string,string> polygonAttributes={
    {"points",""},
    {"stroke","default"},
    {"stroke-width","0"},  
    {"fill","default"},
    
};
//Curves-----------------------------------------------

const map<string,string> lineAttributes={
    {"x1","0"},
    {"y1","0"},
    {"x2","0"},
    {"y2","0"},
    {"fill","default"},
    {"stroke","default"},
    {"stroke-width","0"},  
};

const map<string,string> polylineAttributes={
    {"points",""},
    {"fill","default"},
    {"stroke","default"},
    {"stroke-width","0"},  
};

const map<int,map<string,string> > distributor={
    {1,rectangleAttributes},
    {2,circleAttributes},
    {3,ellipseAttributes},
    {4,lineAttributes},
    {5,polylineAttributes},
    {6,polygonAttributes}
};

const map<pair<int,int>, string> templateForCreation={
    //Rectangle
    {{1,4},"x,y,width,height"},
    {{1,5},"x,y,width,height,fill"},
    {{1,6},"x,y,width,height,fill,stroke"},
    {{1,7},"x,y,width,height,fill,stroke,stroke-width"},
    {{1,9},"x,y,width,height,rx,ry,fill,stroke,stroke-width"},
    //Circle
    {{2,3},"cx,cy,r"},
    {{2,4},"cx,cy,r,fill"},
    {{2,5},"cx,cy,r,fill,stroke"},
    {{2,6},"cx,cy,r,fill,stroke,stroke-width"},
    //Ellipse
    {{3,4},"cx,cy,rx,ry"},
    {{3,5},"cx,cy,rx,ry,fill"},
    {{3,6},"cx,cy,rx,ry,fill,stroke"},
    {{3,7},"cx,cy,rx,ry,fill,stroke,stroke-width"},
    //Polygon
    {{6,1},"points"},
    {{6,2},"points,fill"},
    {{6,3},"points,fill,stroke"},
    {{6,4},"points,fill,stroke,stroke-width"},
    //Line
    {{4,4},"x1,y1,x2,y2"},
    {{4,5},"x1,y1,x2,y2,stroke"},
    {{4,6},"x1,y1,x2,y2,stroke,stroke-width"},
    //PolyLine
    {{5,1},"points"},
    {{5,2},"points,fill"},
    {{5,3},"points,fill,stroke"},
    {{5,4},"points,fill,stroke,stroke-width"}

};

#endif