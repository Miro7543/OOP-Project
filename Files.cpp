#include "Files.h"
#include "Commands.h"

string File::getFileName()//returns the name of the file from the path
{
	string fileName;
	int nameStartAt = path.find_last_of('\\') + 1;
	fileName = path.substr(nameStartAt, path.size() - nameStartAt);
	return fileName;
}

File::File() : opened(false), data(""), path(""), name("") { svg = new Group(0,true); };
void File::print() {
	int index=0;
	vector<BasicShape*> emptyVect={};
	svg->Print(index,emptyVect);
}
void File::help()
{
	ifstream in;//Print the help menu from HelpMenu.txt
	string line="";
	in.open("HelpMenu.txt");
	while(getline(in,line)){
		cout<<line<<endl;
	}
	in.close();
}

void File::create()
{
	if (!opened)
		throw logic_error("There is no opened file to be closed");
	
	string shapeType;
	cin >> shapeType;

	if (supportedShapes.find(shapeType) == supportedShapes.end())//Check if program supports the creation of this shape
		throw invalid_argument("This shape is not supported");

	BasicShape *newShape = Factory.at(shapeType)(1);//Create the shape(the "1" is not used)
	newShape->readAttributes();//Read the attributes for the shape
	svg->addElement(newShape);//Add the element to the svg group
	cout << shapeType << " created successfully" << endl;
}

void File::open()
{
	if (opened)
		throw  logic_error("Another file is already open (" + name + ")" );
	
	//get the whole line and remove spaces and ""
	getline(cin, path);
	trim(path);
	
	ifstream in;
	string a;
	in.open(path);

	getline(in, a);//Read the first line and if empty throw exception
	if (a.empty())
		throw invalid_argument("The file is empty.");

	data += a;

	// Read the remaining part of the file and store it in data
	while (getline(in, a))
	{
		data += "\n";
		data += a;
	}

	in.close();

	//Generate the shapes from data
	genShapes();

	// Get file name
	cout << "Successfully opened " << getFileName() << endl;

	opened = true;
}

void File::close()
{
	if (!opened)
		throw logic_error("There is no opened file to be closed");
	
	data.clear();//Clear everything
	path.clear();
	name.clear();
	svg->clear();
	opened = false;

	cout << "The file " << name << " is closed successfully" << endl;
}

void File::save()
{
	if (!opened)
		throw logic_error("There is no open file to be saved");
	
	data=svg->serializeShape();//Save the shapes as string
	
	ofstream out;//Write them to the opened file
	out.open(path);
	out << data << endl;
	out.close();
	cout << "Successfully saved " << getFileName() << endl;
}

void File::saveAs()
{
	if (!opened)
		throw("There is no open file to be saved");

	string savePath;//Read the filename
	getline(cin, savePath);
	trim(savePath);
	data=svg->serializeShape();//Save the shapes as string
	
	ofstream out(savePath);//Write them to the chosen file
	out << data << endl;
	out.close();
	cout << "Successfully saved information at: " << savePath << endl;
}

void File::genShapes()
{
	replaceSubstring(data, "svg", "g");//Make svg elements a group elements
	
	queS tokens;
	getTokens(data, tokens);//Split them into "tokens"

	while (tokens.front() != "g")//Skip file information
		tokens.pop();
	tokens.pop();//Remove the first group(svg) element because it is represented as this->svg;
	
	svg->genFromQueue(tokens);//Generate the shapes from this queue
}

void File::translate()
{
	if (!opened)
		throw logic_error("There is no file open.");
	
	int shapeNumber = -1;
	string line;
	string firstArg = "", secondArg = "";
	vectS args;
	cin >> firstArg;
	try{//Check if the first argument is a number
		shapeNumber = stoi(firstArg);
	}
	catch (const exception &e){//if not read the next argument
		cin >> secondArg;
		getline(cin, line);
		if (trim(line) != "")//if there are more things after the 2 arguments throw error
			throw invalid_argument("Please enter translate information in the format: \"translate <shapeNumber>(optional) horizontal=<value> vertical=<value>\"");
	}
	
	if (shapeNumber != -1){//Then the first argument is a number
		getline(cin, line);
		splitter(args, trim(line), " ");//Read the next arguments and save them to args
		if (args.size() != 2){
			throw invalid_argument("Please enter translate information in the format: \"translate <shapeNumber>(optional) horizontal=<value> vertical=<value>\"");
		}
	}
	else{//The first number was not a number then add them to args
		args.push_back(firstArg);
		args.push_back(secondArg);
	}//In every case it will end up with 2 strings in the vector
	
	map<string, string> values;//split the two arguments to see if they are correct
	vectS temp;
	splitter(temp, args[0], "=");
	if(temp.size()!=2){
		throw invalid_argument("Please enter translate information in the format: \"translate <shapeNumber>(optional) horizontal=<value> vertical=<value>\"");
	}
	values.insert({temp[0], temp[1]});
	temp.clear();
	
	splitter(temp, args[1], "=");
	if(temp.size()!=2){
		throw invalid_argument("Please enter translate information in the format: \"translate <shapeNumber>(optional) horizontal=<value> vertical=<value>\"");
	}
	values.insert({temp[0], temp[1]});

	if (values.find("horizontal") == values.end() || values.find("vertical") == values.end()){
		throw invalid_argument("Please enter translate information in the format: \"translate <shapeNumber>(optional) horizontal=<value> vertical=<value>\"");
	}
	
	
	G_BS searchedShape;
	int index=0;
	if (shapeNumber == -1)//if there was no specified shape it translates every shape in the svg group
		searchedShape = {nullptr, svg};
	else//else it finds the correcct shape
		searchedShape = svg->getNthShape(index, shapeNumber);

	if (searchedShape.first == nullptr && searchedShape.second == nullptr)//if the res is {nullptr,nullptr} then it didn't find it 
		throw out_of_range("The number is out of range");
	
	searchedShape.second->translate(stod(values["horizontal"]), stod(values["vertical"]));//do the translation
	cout<<"Successfully tranlated ";
	if(shapeNumber==-1)
		cout<<"all shapes";
	else cout<<searchedShape.second->getType();
	cout<<" by "<<(values["horizontal"])<<"px horizontally and "<<(values["vertical"])<<"px verticaly."<<endl;
}

int File::getIndex()//gets the index from the 
{
	string indexStr;
	int n;
	
	cin >> indexStr;
	try{//Check if the specified number is valid
		n = stoi(indexStr);
	}
	catch (const std::exception &e){
		throw invalid_argument("Please enter a number");
	}

	if (n <= 0)
		throw out_of_range("The number is out of range");
	
	return n;
}


void File::erase()//erase a shape
{
	if (!opened)
		throw logic_error("There is no file open.");
	
	int n =getIndex();//Get the index from console
	cout<<n<<endl;
	int index = 0;
	G_BS searchedShape = svg->getNthShape(index, n);//get the searched shape
	if (searchedShape.first == nullptr && searchedShape.second == nullptr)//if correct it didn't find the shape
		throw out_of_range("The number is out of range");

	searchedShape.first->eraseShape(searchedShape.second);//else erase it using the group that it is in
	cout << "Successfully erased " << searchedShape.second->getType() << " at position " << n << endl;
	delete searchedShape.second;
}

void File::printShapesFromVector(vector<BasicShape *>& shapes)
{
	if(shapes.empty()){
		cout<<"There are no shapes in the specified region"<<endl;
		return;
	}
	int index=0;
	svg->Print(index,shapes);
}

void File::within()
{
	if (!opened)
		throw logic_error("There is no file open.");
	
	string type;//get the type of shape
	cin>>type;
	trim(type);
	if(type!="circle"&&type!="rectangle")//if not correct throw exception
		throw invalid_argument("The only supported shapes for within function are \"rectangle\" and \"circle\"");

	string line;
	vectS args;
	vector<BasicShape *> result;
	
	getline(cin, line);
	trim(line);
	splitter(args, line, " ");//store shape arguments in args
	if (type == "circle")
	{
		if (args.size() != 3)
			throw invalid_argument("The \"within circle\" requires 3 arguments (\"within circle <cx> <cy> <radius>\" where <cx> and <cy> are the coordinates of the center)");

		Point center;
		int radius;
		try{//try to cast the arguments
			center.x = stod(args[0]);
			center.y = stod(args[1]);
			radius = unsignedDouble(stod(args[2]));
			Circle1 K(center, radius);
			svg->shapesWithin(result, K);
		}
		catch (const std::exception &e){
			throw invalid_argument("The arguments are not valid numbers");
		}
	}
	else if (type == "rectangle")
	{
		if (args.size() != 4)
			throw invalid_argument("The \"within rectangle\" requires 4 arguments (\"within rectangle <x> <y> <width> <heigth>\" where <x> and <y> are the coordinates of the top left corner)");
		
		Point start, lengths;
		double width, heigth;
		try{//try to cast the arguments
			start.x = stod(args[0]);
			start.y = stod(args[1]);
			width = unsignedDouble(stod(args[2]));
			heigth = unsignedDouble(stod(args[3]));
			svg->shapesWithin(result, Region(start, width, heigth));
		}
		catch (const std::exception &e){
			throw invalid_argument("The arguments are not valid numbers");
		}

	}
	printShapesFromVector(result);
}

void File::area(){
	if (!opened)
		throw logic_error("There is no file open.");

	int n=getIndex();
	int index=1;
	G_BS searchedShape = svg->getNthShape(index, n);//get the searched shape
	if (searchedShape.first == nullptr && searchedShape.second == nullptr)//if correct it didn't find the shape
		throw out_of_range("The number is out of range");

	if(dynamic_cast<Shape*>(searchedShape.second))
	{
		cout<<"The "<<searchedShape.second->getType()<<" has an area of "<<((Shape*)searchedShape.second)->getArea()<<endl;;
	}
	else throw invalid_argument(searchedShape.second->getType()+" doesn't have area");

}

void File::perimeter(){
	if (!opened)
		throw logic_error("There is no file open.");
	int n=getIndex();
	int index=1;
	G_BS searchedShape = svg->getNthShape(index, n);//get the searched shape
	if (searchedShape.first == nullptr && searchedShape.second == nullptr)//if correct it didn't find the shape
		throw out_of_range("The number is out of range");

	if(dynamic_cast<Shape*>(searchedShape.second))
	{
		cout<<"The "<<searchedShape.second->getType()<<" has a perimeter of "<<((Shape*)searchedShape.second)->getPerimeter()<<endl;;
	}
	else throw invalid_argument(searchedShape.second->getType()+" doesn't have perimeter");


}

void File::length(){
	if (!opened)
		throw logic_error("There is no file open.");
	int n=getIndex();
	int index=1;
	G_BS searchedShape = svg->getNthShape(index, n);//get the searched shape
	if (searchedShape.first == nullptr && searchedShape.second == nullptr)//if correct it didn't find the shape
		throw out_of_range("The number is out of range");

	if(dynamic_cast<Curve*>(searchedShape.second))
	{
		cout<<"The "<<searchedShape.second->getType()<<" has a length of "<<((Curve*)searchedShape.second)->getLength()<<endl;;
	}
	else throw invalid_argument(searchedShape.second->getType()+" doesn't have length");
}


string File::getData() {
	if (!opened)
		throw logic_error("There is no file open.");
	return data;
}
