#include "Curves.h"
 
//constructors
PolyLine::PolyLine(vector<Line>& l):lines(l), Curve(POLYLINE){};
PolyLine::PolyLine():Curve(POLYLINE){};

Region PolyLine::getRegion()const{//get the rectangle region around polyline
    Point start=lines[0].getStart(),end=lines[0].getEnd();
    
    for(auto line: lines)
    {
        start.x=min(start.x,line.getStart().x);
        end.x=max(start.x,line.getStart().x);
        start.y=min(start.y,line.getStart().y);
        end.y=max(start.y,line.getStart().y);

        start.x=min(start.x,line.getEnd().x);
        end.x=max(start.x,line.getEnd().x);
        start.y=min(start.y,line.getEnd().y);
        end.y=max(start.y,line.getEnd().y);
    }
    return Region(start,end);
};

double PolyLine::getLength()const{//calculate the length of this polyline
    double total=0;
    for(auto line: lines)
        total+=line.getLength();
    return total;
};

BasicShape* PolyLine::clone(){//virtual copy constructor
    return new PolyLine(*this);
}

void toLines(string s,vector<Line>& res)//turn a string containing coordinates of the polygon lines to vector<Line>
{
    vectS stringCoord;
    splitter(stringCoord,s,", ");//split by ,
    for(int i=3;i<stringCoord.size();i+=2){//create every line by the last 4 coordinates and add it to the result
        Line newLine(Point(stringCoord[i-3],stringCoord[i-2]),Point(stringCoord[i-1],stringCoord[i]));
        res.push_back(newLine);
    }
}

void PolyLine::fillArguments(const map<string,string>& properties)//fill the arguments of this polyline with the values from the map
{
    try{
        toLines(properties.at("points"),lines);
        stroke_width=stoul(properties.at("stroke-width")); 
    }
    catch(const exception& e){
        cout<<"Invalid argument"<<endl;
    }
    
    stroke=properties.at("stroke");
    if(properties.at("fill")=="default")fill="none";
    else fill=properties.at("fill");

}

void PolyLine::getInfo()const//print information of this polyline
{
    cout<<"PolyLine: lines={";
    for(auto i:lines)
        cout<<i.getStart().x<<","<<i.getStart().y<<" - "<<i.getEnd().x<<","<<i.getEnd().y<<"| ";
    cout<<"} stroke="<<stroke<<" stroke-width="<<stroke_width<<endl;

}

void PolyLine::translate(double offX,double offY)//translate polyline
{
    for(int i=0;i<lines.size();i++)
        lines[i].translate(offX,offY);

}

bool PolyLine::isInsideCircle(vector<BasicShape*>& result, Circle1 c)const{//check if this polyline is inside C
    bool inside=true;
    for(auto line:lines){
        inside=inside && line.isInsideCircle(result,c);
    }
    return inside;
}

string PolyLine::serializeShape()const{//serialize polyline for writing in SVG file
    string res="";
    Point start=lines[0].getStart();
    res+="<polyline ";
    res+="points=\"";
    res+=(toString(start.x)+","+toString(start.y) +" ");
    
    for(auto line : lines){
        Point end=line.getEnd();
        res+=(toString(end.x)+","+toString(end.y) +" ");
    }
    res.erase(res.length()-1);
    res+="\" ";
    if(fill!="default")
        res+=("fill=\""+fill+"\" ");
    if(stroke!="default")
        res+=("stroke=\""+stroke+"\" ");
    if(stroke_width!=0)
        res+=("stroke-width=\""+toString(stroke_width)+"\" ");
    res+="/>\n";
    return res;
}

