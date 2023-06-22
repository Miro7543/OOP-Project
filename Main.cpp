#include "Commands.h"

void Input()
{
	string command,argument;
	string data;
	File myFile;
	while(command!="exit")
	{
		cin>>command;
		if(commandEntries.find(command)!=commandEntries.end())
		{
			try{	
				commandEntries.at(command)(myFile);
			}
			catch(const std::exception& e){
				std::cerr <<"Error - "<< e.what() << '\n';
			}	
		}
		else cout<<"Command not found"<<endl;
	}
}

int main()
{
	cout<<"Ready"<<endl;
	cout<<"Type help to see the available commands"<<endl;
	Input();
	return 0;
}
