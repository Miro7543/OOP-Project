#include "Shapes.h"
#include "Curves.h"

//constructors
Polygon::Polygon():Shape(POLYGON){};
Polygon::Polygon(const vector<Point>& p):Shape(POLYGON){
    if(p.size()<3){
        throw invalid_argument("Expected at least 3 points");
    }
    else {
        points=p;
        points.push_back(p[0]);
    }
};

Region Polygon::getRegion()const{//get the rectangle region around polygon
    Point start=points[0],end=points[0];
    for(auto point: points)
    {
        start.x=min(start.x,point.x);
        end.x=max(start.x,point.x);
        start.y=min(start.y,point.y);
        end.y=max(start.y,point.y);
    }
    return Region(start,end);
};

double Polygon::getArea()const{//calculate area of the polygon
    double total=0;
    for(int i=0;i<points.size()-1;i++)
        total+=(points[i].x*points[i+1].y - points[i].y*points[i+1].x);
    return abs(total)/2;
}

double Polygon::getPerimeter()const{//calculate perimeter of the polygon
    Line l;
    double total=0;
    for(int i=0;i<points.size()-1;i++)
    {
        l=Line(points[i],points[i+1]);
        total+=l.getLength();
    }
    return total;
}

BasicShape* Polygon::clone(){//virtual copy constructor
    return new Polygon(*this);
}

void Polygon::fillArguments(const map<string,string>& properties){//fill the arguments of this polygon with the values from the map
    try{
        toPoints(properties.at("points"),points);
        stroke_width=stoul(properties.at("stroke-width")); 
    }
    catch(const exception& e){
        cout<<"Invalid argument"<<endl;
    }

    stroke=properties.at("stroke");
    fill=properties.at("fill");
}

void Polygon::getInfo()const //print information of this polygon
{
    cout<<"Polygon: points={";
    for(auto i:points)
        cout<<i.x<<","<<i.y<<" ";
    cout<<"} fill="<<fill<<" stroke="<<stroke<<" stroke-width="<<stroke_width<<endl;
}

bool Polygon::isInsideCircle(vector<BasicShape*>& result, Circle1 c)const{//check if this polygon is inside c
    bool inside=true;
    for(auto point:points){
        inside=inside&&c.contains(point);
    }
    return inside;
}

void Polygon::translate(double offX,double offY)//translate polygon
{
    for(int i=0;i<points.size();i++)
        points[i].translate(offX,offY);
}

string Polygon::serializeShape()const{//serialize polygon for writing in SVG file
    string res="";
    res+="<polygon ";
    res+="points=\"";
    for(auto point : points){
        res+=(toString(point.x)+","+toString(point.y) +" ");
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
    