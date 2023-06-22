#include "Shapes.h"

//constructors
Circle::Circle(Point C, double r) : radius(unsignedDouble(r)), center(C),Shape(CIRCLE){};
Circle::Circle():radius(0),center(Point()),Shape(CIRCLE){};

double Circle::getPerimeter()const{//calculate perimeter of the circle
    return 2 * M_PI * radius;
}

double Circle::getArea()const{//calculate area of the circle
    return M_PI * radius * radius;
}

Region Circle::getRegion()const{//get the rectangle region around circle
    return Region(Point(center.x-radius,center.y-radius),2*radius,2*radius);
}

BasicShape* Circle::clone(){//virtual copy constructor
    return new Circle(*this);
}

double Circle::getRadius()const{//getters
    return radius;
}

Point Circle::getCenter()const{
    return center;
}

void Circle::getInfo()const{//print information of this circle
    cout<<"Circle: x="<<center.x<<" y="<<center.y<<" r="<<radius<<" fill="<<fill<<" stroke="<<stroke<<" stroke-width="<<stroke_width<<endl;
}

void Circle::fillArguments(const map<string,string>& properties){//fill the arguments of this circle with the values from the map
    try{
        center=Point(properties.at("cx"),properties.at("cy"));
        radius=unsignedDouble(stod(properties.at("r")));
        stroke_width=stoul(properties.at("stroke-width"));
    }
    catch(const exception& e){
        throw invalid_argument("Invalid arguments");
    }
    stroke=properties.at("stroke");
    fill=properties.at("fill");
}

void Circle::translate(double offX,double offY)//translate circle
{
    center.translate(offX,offY);
}

bool Circle::contains(Point p)const{//check if point is inside
    return distance(p,center)<=radius;
}

bool Circle::isInsideCircle(vector<BasicShape*>& result, Circle1 C)const{//check if this circle is inside C
    return distance(C.c,center)+radius<=C.r;
}

string Circle::serializeShape()const{//serialize circle for writing in SVG file
    string res="";
    res+="<circle ";
    res+=("cx=\""+toString(center.x)+"\" ");
    res+=("cy=\""+toString(center.y)+"\" ");
    res+=("r=\""+toString(radius)+"\" ");
    if(fill!="default")
        res+=("fill=\""+fill+"\" ");
    if(stroke!="default")
        res+=("stroke=\""+stroke+"\" ");
    if(stroke_width!=0)
        res+=("stroke-width=\""+toString(stroke_width)+"\" ");
    res+="/>\n";
    return res;
}