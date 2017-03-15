#include "defs.h"
#define MAX_PER_LINE 54

int charToInt(char c)
{
	return c-'A';
}

char intToChar(int i)
{
	return i+'A';
}

void readFile(FILE* f, int &numOfVertex, int** &adjacentTable, int* &color)
{
	char str[MAX_PER_LINE];	

	fgets(str, MAX_PER_LINE, f);		
	sscanf(str, "%d", &numOfVertex);	

	adjacentTable = new int* [numOfVertex];
	for(int i = 0; i< numOfVertex; i++)
		adjacentTable[i] = new int [numOfVertex];
	for(int i = 0; i< numOfVertex; i++)
		for(int j = 0; j < numOfVertex; j++)
			adjacentTable[i][j] = 0;

	color = new int [numOfVertex];
	for(int i = 0; i < numOfVertex; i++)
		color[i] = 0;

	for(int i = 0; i< numOfVertex; i++)
	{
		fgets(str, MAX_PER_LINE, f);	

		int j = 0;
		while (str[j] != '\0')	
		{
			if (str[j] == ' ' || str[j] == '\r' || str[j] == '\n')	
				j++;
			else
			{
				if (i == charToInt(str[j])) adjacentTable[i][charToInt(str[j])] = 0;
				else adjacentTable[i][charToInt(str[j])] = 1;
				j++;
			}
		}		
	}
}

int findMaxLevel(int numOfVertex, int** adjacentTable, int* color)
{	
	int vertex = -1;	
	int level = -1;		
	for (int i = 0; i < numOfVertex; i++)	
	{
		if (color[i] == 0)		
		{
			int count = 0;		
			for (int j = 0; j < numOfVertex; j++)	
				if (color[j] == 0 && adjacentTable[i][j] == 1)
					count++;
			if (count > level)
			{
				level = count;
				vertex = i;
			}
		}
	}
	return vertex;
}

void dawnColor(int u, int* color, int numOfColor, int &count)
{
	color[u] = numOfColor;
	count++;
}

int findSameColor(int u, int numOfVertex, int** adjacentTable, int* color)
{
	int vertex = -1;	
	int level = 0;	

	for (int i = 0; i < numOfVertex; i++)
	{
		if (color[i] == 0 && adjacentTable[u][i] == 0)	
		{
			int count = 0; 
			for (int j = 0; j < numOfVertex; j++)		
				if (adjacentTable[u][j] == 1 && adjacentTable[j][i] == 1)
				{
					for (int k = 0; k < numOfVertex; k++)
						if (color[k] == 0 && adjacentTable[i][k] == 1)
							count++;
					break;
				}
			if (count >= level) 
			{
				vertex = i;
				level = count;
			}
		}
	}
	if (vertex > -1) return vertex;		

	for (int i = 0; i < numOfVertex; i++)
	{
		if (color[i] == 0 && adjacentTable[u][i] == 0)
		{
			int count = 0;
			for (int j = 0; j < numOfVertex; j++)		
				if (color[j] == 0 && adjacentTable[i][j] == 1)
					count++;
			if (count >= level) 
			{
				vertex = i;
				level = count;
			}
		}
	}
	return vertex;
}

void mergeVertex(int u, int v, int numOfVertex, int** adjacentTable)
{
	for (int i = 0; i < numOfVertex; i++)
		if (adjacentTable[v][i] == 1)
		{
			adjacentTable[u][i] = 1;
			adjacentTable[i][u] = 1;
		}
}

void addFirst (Vertex* &v, int vertex, int color)
{
	Vertex* pTemp = new Vertex;
	pTemp->name = intToChar(vertex);
	pTemp->color = color;
	pTemp->next = v;
	v = pTemp;
}

int GraphColoring(FILE* f, Vertex* &v)
{
	int numOfVertex;			
	int** adjacentTable;		
	int* color;					

	readFile(f, numOfVertex, adjacentTable, color);		
	fclose(f);

	/*for(int i = 0; i< numOfVertex; i++)
	{
		for(int j = 0; j < numOfVertex; j++)
			cout << adjacentTable[i][j] << " ";
		cout << endl;
	}*/

	int u, k;					
	int numOfColor = 0;		
	int count = 0;					
	while (count < numOfVertex)
	{
		numOfColor++;
		u = findMaxLevel(numOfVertex, adjacentTable, color);
		dawnColor(u, color, numOfColor, count);
	
		while ((k = findSameColor(u, numOfVertex, adjacentTable, color)) != -1)
		{
			dawnColor(k, color, numOfColor, count);
			mergeVertex(u, k, numOfVertex, adjacentTable);
		}
	}

	for (int i = numOfVertex-1; i >= 0; i--)
		addFirst(v, i, color[i]);

	for (int i = 0; i < numOfVertex; i++)
		delete adjacentTable[i];
	delete adjacentTable;
	delete color;

	return numOfColor;
}



