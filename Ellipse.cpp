#include "Shapes.h"

//constructors
Ellipse::Ellipse(Point center, double rx, double ry) : center(center), Shape(ELLIPSE)
{
    radiusX = unsignedDouble(rx);
    radiusY = unsignedDouble(ry);
}
Ellipse::Ellipse():Shape(ELLIPSE){};

double Ellipse::getArea()const{//calc area of the ellipse
    return M_PI * radiusX * radiusY;
}

double Ellipse::getPerimeter()const{//calc perimeter of the ellipse
    // Ramanujan aproximation formula
    double h = ((radiusX - radiusY) * (radiusX - radiusY)) /
               ((radiusX + radiusY) * (radiusX + radiusY));

    double perimeter = M_PI * (radiusX + radiusY);
    perimeter *= (1 + 3 * h / (10 + sqrt(4 - 3 * h)));

    return perimeter;
}

Region Ellipse::getRegion()const{//get the rectangle region around ellipse
    return Region(Point(center.x - radiusX, center.y - radiusY), 2 * radiusX, 2 * radiusY);
}

BasicShape* Ellipse::clone(){//virtual copy constructor
    return new Ellipse(*this);
}

void Ellipse::fillArguments(const map<string,string>& properties){//fill the arguments of this ellipse with the values from the map
    stroke=properties.at("stroke");
    fill=properties.at("fill");

    try{
        center=Point(properties.at("cx"),properties.at("cy"));
        radiusX=unsignedDouble(stod(properties.at("rx")));
        radiusY=unsignedDouble(stod(properties.at("ry")));
        stroke_width=stoul(properties.at("stroke-width"));
    }
    catch(const exception& e){
        throw invalid_argument("Invalid arguments");
    }
}

void Ellipse::getInfo()const{//print information of this ellipse
    cout<<"Ellipse: x="<<center.x<<" y="<<center.y<<" rx="<<radiusX<<" ry="<<radiusY<<" fill="<<fill<<" stroke="<<stroke<<" stroke-width="<<stroke_width<<endl;
}

void Ellipse::translate(double offX,double offY){//translate ellipse
    center.translate(offX,offY);
}
#include "Curves.h"
bool Ellipse::isInsideCircle(vector<BasicShape*>& result, Circle1 C)const{//check if this ellipse is inside C    
    double angle;
    bool inside=true;
    double Mx,My;
    for(double angle=0;angle<=2*M_PI;angle+=M_PI/50)//Solution consulted with geometry assistant Yana Aleksieva
    {
        Mx=center.x+radiusX*cos(angle);
        My=center.y+radiusY*sin(angle);
        bool temp=distance(Point(Mx,My),C.c)<=C.r;
        inside=inside&&temp;
    }
    return inside;
}

string Ellipse::serializeShape()const{//serialize ellipse for writing in SVG file
    string res="";
    res+="<ellipse ";
    res+=("cx=\""+toString(center.x)+"\" ");
    res+=("cy=\""+toString(center.y)+"\" ");
    res+=("rx=\""+toString(radiusX)+"\" ");
    res+=("ry=\""+toString(radiusY)+"\" ");
    if(fill!="default")
        res+=("fill=\""+fill+"\" ");
    if(stroke!="default")
        res+=("stroke=\""+stroke+"\" ");
    if(stroke_width!=0)
        res+=("stroke-width=\""+toString(stroke_width)+"\" ");
    res+="/>\n";
    return res;
}
    