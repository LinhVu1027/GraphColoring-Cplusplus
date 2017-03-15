#include "defs.h"
#include "GraphColoring.cpp"

void display(Vertex* VLists)
{
	while (VLists != NULL)
	{ 
		cout << "	Dinh " << VLists->name << " co mau " << VLists->color << endl;
		VLists = VLists->next;
	}
	return;
}

int main()
{
   	// initialize the input file
	char* file_name = (char*)"input.txt";
	FILE* f = fopen(file_name, "r");
	if (f == NULL)	//file not found or cannot read
	{
		printf("File not found \n");
		return 0;
	}

	Vertex* vList = NULL;   
	int numColor = GraphColoring(f, vList);
	cout << "So mau da dung de to do thi: " << numColor << endl;
	cout << "Cu the: " << endl;
	display(vList);
  
   	return 0;
}

