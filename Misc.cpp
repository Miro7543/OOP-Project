#include "Misc.h"
#include "Funcs.h"

//------------------------------Point------------------------------------
Point::Point(string s){//turn one string into Point
    int comma=s.find(",");
    x= stod(s.substr(0,comma));
    comma++;
    y= stod(s.substr(comma,s.length()-comma));   
}

Point::Point(string X,string Y){//turn two strings into Point
    x=stod(X);
    y=stod(Y);
}

//Constructors
Point::Point(double X,double Y):x(X),y(Y){};
Point::Point():x(0),y(0){};

void Point::translate(double offX,double offY){//translate Point
    x+=offX;
    y+=offY;
}

//------------------------------Region------------------------------------
//Region constructors
Region::Region(double up, double down, double left, double rigth) : supY(up), supX(rigth), infY(down), infX(left){};
Region::Region() : supX(0), supY(0), infX(0), infY(0){};
Region::Region(Point start, double width, double heigth) : supY(start.y + heigth), supX(start.x + width), infY(start.y), infX(start.x){};
Region::Region(Point p1, Point p2)
{
    supY = max(p1.y, p2.y);
    infY = min(p1.y, p2.y);
    supX = max(p1.x, p2.x);
    infX = min(p1.x, p2.x);
}
//Region getters
double Region::getSupX()const{return supX;}
double Region::getSupY()const{return supY;}
double Region::getInfX()const{return infX;}
double Region::getInfY()const{return infY;}

bool Region::contains(Region other)const{//check if region is inside another region
    return other.infX>=infX && other.infY>=infY && other.supX<= supX && other.supY <=supY;
}

//------------------------------Circle1------------------------------------
Circle1::Circle1(Point p,double d):c(p),r(d){};

bool Circle1::contains(Point p)const{//check if points is inside circle
    return distance(p,c)<=r;
}
bool Circle1::contains(Region reg)const{//check if region is inside circle
    bool inside=distance(Point(reg.getInfX(),reg.getInfY()),c)<=r&&
    distance(Point(reg.getInfX(),reg.getSupY()),c)<=r&&
    distance(Point(reg.getSupX(),reg.getInfY()),c)<=r&&
    distance(Point(reg.getSupX(),reg.getSupY()),c)<=r;
    return inside;
}

//------------------------------BasicShape------------------------------------
string BasicShape::getType()const{//function that returns the type of the shape
    switch (ID)
    {
    case 1:return "Rectangle";break;
    case 2:return "Circle";break;
    case 3:return "Ellipse";break;
    case 4:return "Line";break;
    case 5:return "Polyline";break;
    case 6:return "Polygon";break;
    case 7:return "Group";break;
    };
    return "Not found";
}

//function that reads the prperties of a shape from the console(used for all types of shapes)
void BasicShape::readAttributes()
{
    string args;
    getline(cin,args);
    trim(args);
    vectS argsVect;
    splitter(argsVect,args," ");//separate the arguments by " " 
    if(templateForCreation.find({ID,argsVect.size()})==templateForCreation.end()){//check if there is a template for creation with this number of arguments
        throw invalid_argument("There is no supported creation of a "+getType()+" with these arguments!");
    }

    string attrTemplate= templateForCreation.at({ID,argsVect.size()});//get the needed template
    vectS attrTemplateVect;
    splitter(attrTemplateVect,attrTemplate,",");//split template values by ,

    auto attCopy=distributor.at(ID);//get a map with the values for the shape
    for(int i=0;i<attrTemplateVect.size();i++){//set the ones that are given by the template
        attCopy[attrTemplateVect[i]]=argsVect[i];
    }
    fillArguments(attCopy);//fill up values in the shape
}

//function that generates a shape from queue(used for all types of shape without groups)
void BasicShape::genFromQueue(queS& tokens){
    
    string currStr=tokens.front();
    auto attCopy=distributor.at(ID);//get a copy of the right attribute map

    while(currStr!="/>")//while it reaches the end 
	{
        vectS temp;
        splitter(temp,currStr,"=");//split token to attrName and value
        if(temp.size()==2){
            attCopy[temp[0]]=trim(temp[1]);//add the value to the map
        }    
        tokens.pop();
		currStr=tokens.front();
    }
    fillArguments(attCopy);//fill up values in the shape
    return;
}

G_BS BasicShape::getNthShape(int& current,int searched)//function to get the Nth shape in the list and its' parent group 
{
    if(current==searched)return {nullptr,this};//if the shape is found return it and no group
    return {nullptr,nullptr};//else return nothing
}

//------------------------------Constructors------------------------------------
BasicShape::BasicShape(ShapeID id) : ID(id){};
Curve::Curve(ShapeID id) : BasicShape(id){};
Shape::Shape(ShapeID id) : BasicShape(id){};
void Shape::Print(int &index,vector<BasicShape *>& shapes){
    if(find(shapes.begin(),shapes.end(),this)!=shapes.end())
        cout<<"\033[32m";

    cout<<this->getType()<<"("<<index<<")"<<endl;
    cout<<"\033[0m";
    
}
void Curve::Print(int &index,vector<BasicShape *>& shapes){
    if(find(shapes.begin(),shapes.end(),this)!=shapes.end())
        cout<<"\033[32m";
    
    cout<<this->getType()<<"("<<index<<")"<<endl;
    cout<<"\033[0m";
    
}
