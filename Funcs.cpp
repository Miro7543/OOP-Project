#include "Funcs.h"
#include "Curves.h"

double unsignedDouble(double x)
{
    if (x < 0){
        throw invalid_argument("Expected positive value");
    }
    return x;
}

double distance(const Point p1,const Point p2){//find the distance between two points
    return sqrt( (p1.x-p2.x)*(p1.x-p2.x) +(p1.y-p2.y)*(p1.y-p2.y) );
}

string toString(double num){//turn double into string without trailing zeros
    ostringstream strs;
    strs << num;
    return  strs.str();
}

void splitter(vectS &res,const string original, const string delimiter)//split the string into multiple strings divided by delimiter 
{
    int currPos = 0, newPos;
    newPos = original.find_first_of(delimiter, currPos);//find delimiter after the currPos

    while (newPos != -1)//while there are delimiters left
    {
        res.push_back(original.substr(currPos, newPos - currPos));//Add the substr from currPos to newPos
        currPos = original.find_first_not_of(delimiter,newPos);//currPos is now the first character after newPos that is not a delimiter(prevents splitting multiple consecutive spaces to multiple strings)
        newPos = original.find_first_of(delimiter, currPos);//find delimiter after the currPos
    }//the part after the last delimiter won't be added
    res.push_back(original.substr(currPos));//Add the rest of the string
}

void remover(string &original,const string substr)//removes all occurences of substr in original
{
    int pos = 0;
    pos = original.find(substr);
    while (pos != -1)//while the substr can be found in original
    {
        original.erase(pos, substr.length());//erase the first occurence of substr
        pos = original.find(substr);//find the next one
    }
}

string trim(string &str)
{
    int end, start = str.find_first_not_of(" \t\n\"}");//Find the first 
    if (start == string::npos)
        return "";

    end = str.find_last_not_of(" \t\n\"");// and the last character that is not \t \n " or space
    str=str.substr(start, end - start + 1);//return this substr
    return str;
}

void getTokens(string data,queS& res){
    
    remover(data,"\n");//Remove new lines
	vectS tags;
    splitter(tags,data,"<");//Split by <

	for(string tag:tags)
	{
		vectS tokensSplit;
        trim(tag);
        splitter(tokensSplit,tag," ");//Trim every line and split it by the spaces
		
        for(string token: tokensSplit)
		{
            if(endsWith(token,"/>")&&token.length()>2)//Turn tags like: (stroke="none"/>) to (stroke="none") and (/>) 
            {
                token.erase(token.length()-2);

                if(token[0]>='0'&&token[0]<='9'){//Turn tags like (points="100,300 200,400 150,450" stroke="none") to (points="100,300 200,400 150,450") and (stroke="none") instead of (points="100,300), (200,400), etc. 
                    res.back()+=(" "+token);
                }
                else res.push(token);
                
                res.push("/>");
            }
			else
            {
                if(token[0]>='0'&&token[0]<='9'){//Turn tags like (points="100,300 200,400 150,450" stroke="none") to (points="100,300 200,400 150,450") and (stroke="none") instead of (points="100,300), (200,400), etc.
                    res.back()+=(" "+token);
                }
                else res.push(token);
            } 

		}
	}
}

void replaceSubstring(string& str, const string oldSubstr,const string newSubstr) {
    int pos = str.find(oldSubstr);//find the first occurence of oldSubstr
    while (pos != -1) {//while there are no more occurences of oldSubstr
        str.replace(pos, oldSubstr.length(), newSubstr);//replace with newSubstr
        pos=str.find(oldSubstr,pos+newSubstr.length());//find the next
    }
}

void toPoints(string s,vector<Point>& res)//turn string into points in the format: x1,y1 x2,y2 . . . xn,yn
{
    trim(s);
    vectS stringCoord;
    splitter(stringCoord,s,", ");//split into different points(string)
    for(int i=0;i<stringCoord.size();i+=2){//turn those into points(Point)
        res.push_back(Point(stringCoord[i],stringCoord[i+1]));
    }
}

bool endsWith(const string original,const string suffix)//Check if original ends with suffix
{
    if(original.length()<suffix.length())//if original is shorter it can't end with suffix
        return false;
    return suffix==original.substr(original.length()-suffix.length(),suffix.length());
}

