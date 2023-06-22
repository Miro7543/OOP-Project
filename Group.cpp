#include "Misc.h"
#include "Commands.h"

//Constructors and destructors
Group::Group():BasicShape(GROUP){};
Group::Group(int d):BasicShape(GROUP),depth(d){};
Group::Group(int d,bool r):BasicShape(GROUP),depth(d),root(r){};
Group::~Group(){
    clear();
}

void Group::readAttributes(){}//Group has no attributes to be read(used in creating a shape from console)
void Group::fillArguments(const map<string,string>&){};//Group does not have arguments to be filled(used in casting from file to shapes)

void Group::clear(){//clear the shapes from the group and delete them from the heap
    for(auto s:shapes)
        delete s;
    shapes.clear();
};


Region Group::getRegion()const{//get the region of the group by checking all of its children
    Region temp;
    double supY,infY,supX,infX;

    if(shapes.size()==0)return Region();
    
    temp=shapes[0]->getRegion();
    supY = temp.getSupY();
    infY = temp.getInfY();
    supX = temp.getSupX();
    infX = temp.getInfX();
    
    for(auto s:shapes)
    {
        temp=s->getRegion();
        supY = max(supY, temp.getSupY());
        infY = min(infY, temp.getInfY());
        supX = max(supX, temp.getSupX());
        infX = min(infX, temp.getInfX());
    }
    return Region(supY,infY,infX,supX);
}

void Group::addElement(BasicShape *f){//Adding new element to group
    shapes.push_back(f);
}  

BasicShape* Group::clone(){
    Group *newGroup = new Group(depth);//Preserve the depth of the group in the tree
    for (BasicShape* s : shapes)///Preserve the shapes inside the group by cloning them
    {
        newGroup->addElement(s->clone());
    }
    return newGroup;
}
void Group::genFromQueue(queS& tokens)//generate group with elements and prperties from queue with tokens
{
    BasicShape* currentShape;
	string currStr=tokens.front();
    while(currStr!="/g>")//while we reach the end of the group
	{
		if(Factory.find(currStr)!=Factory.end())//check if shape is supported else ignore it 
		{
			currentShape=Factory.at(currStr)(depth+1);//create the shape with depth+1
			tokens.pop();
			currentShape->genFromQueue(tokens);//start generating the shape with its arguments
			shapes.push_back(currentShape);//add the shape to shapes
		}
		tokens.pop();
		currStr=tokens.front();   
	}
}    


void Group::Print(int &index,vector<BasicShape *>& searchedShapes)//print the information about the group with indexes
{
    bool inside;
    if(searchedShapes.empty())inside=false;//if it is not searching then set inside to false
    else inside=find(searchedShapes.begin(),searchedShapes.end(),(BasicShape*)this)!=searchedShapes.end();//else see if the shape if in the searched list
    
    if(inside)//if this shape is searched it will change color of text in console to green
        cout<<"\033[32m";
    cout<<this->getType()<<"("<<index<<"){\n";
    
    for(auto i : shapes)//go through the shapes in the group
    {
        for(int j=0;j<=depth;j++)//print spaces to show depth
            cout<<"    ";
        index++;
        if(inside)//if group is inside then make all the shapes inside the group green
            i->Print(index,shapes);
        else i->Print(index,searchedShapes);//else search individually
    }
    for(int j=0;j<depth;j++)//print the depth
            cout<<"    ";
    if(inside)//if group is inside then color the closing bracket
        cout<<"\033[32m";
    cout<<"};"<<"\033[0m"<<endl;

    
}

void Group::translate(double offX,double offY)//Translate all shapes in the group
{
    for(auto shape:shapes){
        shape->translate(offX,offY);
    }
}

G_BS Group::getNthShape(int& current,int searched){//recursively get the Nth shape and the group that it is in
    Group* nestedGroup;
    G_BS searchedShape;
    if(current==searched)return {nullptr,this};//if this is the searchedShape return this
    for(auto i : shapes)
    {
        current++;
        searchedShape = i->getNthShape(current,searched);//check next shape in the vector
        if(searchedShape.second!=nullptr)//the shape was found
        {
            if(searchedShape.first!=nullptr)return searchedShape;//and the group parent was also found
            else return {this,searchedShape.second};//this is the parent group so return it
        }
    }
    return {nullptr,nullptr};
}

void Group::eraseShape(BasicShape* shape){//erase certain shape in the group
    auto it=find(shapes.begin(),shapes.end(),shape);
    shapes.erase(it);
    
}
    
bool Group::isInsideCircle(vector<BasicShape*>& result,Circle1 c)const{//check if every shape in the group is inside the circle
    bool inside=true,temp=false;
    if(c.contains(getRegion()))return true;//check if the region of the group is the circle  
    for(auto shape:shapes){//else check every shape separetely
        temp=shape->isInsideCircle(result,c);
        if(temp)result.push_back(shape);
        inside=inside&&temp;
    }
    return inside;
}
    

void Group::shapesWithin(vector<BasicShape*>& result,Region R)const//get shapes within region and add them to result
{
    for(auto shape:shapes)
    {
        if(shape->getType()=="Group")//if the shape is group check inside 
            ((Group*)shape)->shapesWithin(result,R);
        if(R.contains(shape->getRegion()))//else check the shape
            result.push_back(shape);
    }
}

void Group::shapesWithin(vector<BasicShape*>& result,Circle1 c)const//get shapes within the circle and add them to result
{
    for(auto shape:shapes)//for every shape check if it is inside c
    {
        if(shape->isInsideCircle(result,c))
            result.push_back(shape);
    }
}

string Group::serializeShape()const{//turn the group to string
    string res="";
    
    if(root){//if root add information and name it svg
        res+="<svg ";
        string w,h;
        w=toString(getRegion().getSupX()+50);
        h=toString(getRegion().getSupY()+50);
        string viewbox="";
        viewbox+="\"0 0 ";
        viewbox+=(w + " " + h);
        res+="xmlns=\"http://www.w3.org/2000/svg\" width=\""+w+"\" height=\""+h+"\" viewBox="+viewbox;
        res+="\">\n";
    }
    else {
        res+="<g>\n";
    }


    for(auto shape : shapes){//add the shapes
        for(int i=0;i<=depth;i++)//add identation
            res+="\t";
        res+=shape->serializeShape();
    }

    for(int i=0;i<depth;i++)//add identation
            res+="\t";
    
    if(root)res+="</svg>\n";//close the tag
    else res+="</g>\n";
    return res;
}