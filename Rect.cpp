#include "Shapes.h"
//constructors
Rect::Rect(Point Start,double Width,double Heigth):Shape(RECTANGLE),start(Start){
    width=unsignedDouble(Width);
    heigth=unsignedDouble(Heigth);

};
Rect::Rect(Point Start,double Width,double Heigth,double RX,double RY):
Shape(RECTANGLE),start(Start){
    width=unsignedDouble(Width);
    heigth=unsignedDouble(Heigth);
    rx=unsignedDouble(RX);
    ry=unsignedDouble(RY);  
};
Rect::Rect():Shape(RECTANGLE){};

Region Rect::getRegion()const//get the rectangle region around rectangle
{
    return Region(start,width,heigth);
}

double Rect::getArea()const//calculate area of the rectangle
{
    return width*heigth;
}

double Rect::getPerimeter()const//calculate perimeter of the rectangle
{
    return (width+heigth)*2;
}

BasicShape* Rect::clone(){//virtual copy constructor
    return new Rect(*this);
}

void Rect::fillArguments(const map<string,string>& properties){//fill the arguments of this rectangle with the values from the map
    try{
        start=Point(properties.at("x"),properties.at("y"));
        width=unsignedDouble(stod(properties.at("width")));
        heigth=unsignedDouble(stod(properties.at("height")));
        rx=unsignedDouble(stod(properties.at("rx")));
        ry=unsignedDouble(stod(properties.at("ry")));
        stroke_width=stoul(properties.at("stroke-width"));
    }
    catch(const exception& e){
        cout<<"Invalid argument"<<endl;
    }

    stroke=properties.at("stroke");
    fill=properties.at("fill");
}

void Rect::getInfo()const{//print information of this rectangle
    cout<<"Rect: x="<<start.x<<" y="<<start.y<<" width="<<width<<" heigth="<<heigth<<" rx="<<rx<<" ry="<<ry<<" fill="<<fill<<" stroke="<<stroke<<" stroke-width="<<stroke_width<<endl;
}

void Rect::translate(double offX,double offY)//translate rectangle
{
    start.translate(offX,offY);
}

bool Rect::isInsideCircle(vector<BasicShape*>& result, Circle1 C)const{//check if this rectangle is inside C
    bool inside=true;
    inside=inside && distance(C.c,start)<C.r;
    inside=inside && distance(C.c,{start.x+width,start.y})<C.r;
    inside=inside && distance(C.c,{start.x+width,start.y+heigth})<C.r;
    inside=inside && distance(C.c,{start.x,start.y+heigth})<C.r;
    return inside;
}

string Rect::serializeShape()const{//serialize rectangle for writing in SVG file
    string res="";
    res+="<rect ";
    res+=("x=\""+toString(start.x)+"\" ");
    res+=("y=\""+toString(start.y)+"\" ");
    res+=("rx=\""+toString(rx)+"\" ");
    res+=("ry=\""+toString(ry)+"\" ");
    res+=("width=\""+toString(width)+"\" ");
    res+=("height=\""+toString(heigth)+"\" ");
    if(fill!="default")
        res+=("fill=\""+fill+"\" ");
    if(stroke!="default")
        res+=("stroke=\""+stroke+"\" ");
    if(stroke_width!=0)
        res+=("stroke-width=\""+toString(stroke_width)+"\" ");
    res+="/>\n";
    return res;
}
    