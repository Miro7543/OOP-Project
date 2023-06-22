#include "Curves.h"

//constructors
Line::Line(Point s, Point e):Curve(LINE),start(s),end(e){};
Line::Line():Curve(LINE){};
Line::Line(string s, string e):Curve(LINE){
    try{
        start=Point(s);
        end=Point(e);
    }
    catch(const exception& e){
        throw invalid_argument("Invalid argument");
    }

};
Region Line::getRegion()const{//get the rectangle region around line
    return Region(start,end);
}


double Line::getLength()const{//calculate the length of the line
    return distance(start,end);
}

BasicShape* Line::clone(){//virtual copy constructor
    return new Line(*this);
}

Point Line::getStart()const{return start;}//getters
Point Line::getEnd()const{return end;}

void Line::fillArguments(const map<string,string>& properties)//fill the arguments of this line with the values from the map
{
    try{
        stroke_width=stoul(properties.at("stroke-width"));
        start=Point(properties.at("x1"),properties.at("y1"));
        end=Point(properties.at("x2"),properties.at("y2"));    
    }
    catch(const exception& e){
        cout<<"Invalid argument"<<endl;
    }
    
    stroke=properties.at("stroke");
    if(properties.at("fill")=="default")fill="none";
    else fill=properties.at("fill");

}

void Line::getInfo()const{//print information of this line
    cout<<"Line: start="<<start.x<<","<<start.y<<" end="<<end.x<<","<<end.y<<" stroke="<<stroke<<" stroke-width="<<stroke_width<<endl;
}

void Line::translate(double offX,double offY)//translate line
{
    start.translate(offX,offY);
    end.translate(offX,offY);
}

bool Line::isInsideCircle(vector<BasicShape*>& result, Circle1 c)const{//check if this line is inside C
    return c.contains(start) && c.contains(end);
}

string Line::serializeShape()const{//serialize line for writing in SVG file
    string res="";
    res+="<line ";
    res+=("x1=\""+toString(start.x)+"\" ");
    res+=("y1=\""+toString(start.y)+"\" ");
    res+=("x2=\""+toString(end.x)+"\" ");
    res+=("y2=\""+toString(end.y)+"\" ");
    if(fill!="default")
        res+=("fill=\""+fill+"\" ");
    if(stroke!="default")
        res+=("stroke=\""+stroke+"\" ");
    if(stroke_width!=0)
        res+=("stroke-width=\""+toString(stroke_width)+"\" ");
    res+="/>\n";
    return res;
}