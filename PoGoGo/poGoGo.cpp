/*
Author: Peter O'Donohue
Creation Date: 12/04/17
Modificatio Date: 12/06/17
Description: FILL IN
*/

#include <iostream>
#include <string>
#include <vector>
#include <functional> 
#include <queue>
#include <fstream>

using namespace std;

class Node
{
public:
	int bound;
	vector<int> stopsVisited;
	Node(int, int);
};

Node::Node(int lowBound, int stops)
{
	int digit = 0;
	bound = lowBound;
	while (stops >= 1)
	{
		digit = stops % 10;
		stopsVisited.insert(stopsVisited.begin(), digit);
		stops /= 10;
	}
}

struct pokeStop
{
	int xCoord;
	int yCoord;
	int stopNum;
	vector<string> pokemonList;

	pokeStop(int num, int xCoordinate, int yCoordinate, string pokemon)
	{
		stopNum = num;
		xCoord = xCoordinate;
		yCoord = yCoordinate;
		pokemonList.push_back(pokemon);
	}
};

struct compare
{
	bool operator()(const Node& lhs, const Node& rhs)
	{
		return lhs.bound > rhs.bound;
	}
};

template <class Object>
class Matrix
{
public:
	Matrix(int rows = 0, int cols = 0) : array(rows)
	{
		for (int i = 0; i < rows; i++)
			array[i].resize(cols);
	}
	void resize(int rows, int cols)
	{
		array.resize(rows);
		for (int i = 0; i < rows; i++)
			array[i].resize(cols);
	}
	const vector<Object> & operator[](int row) const
	{
		return array[row];
	}
	vector<Object> & operator[](int row)
	{
		return array[row];
	}
	int numrows() const
	{
		return array.size();
	}
	int numcols() const
	{
		return numrows() ? array[0].size() : 0;
	}
private:
	vector< vector<Object> > array;
};

// main functions
bool stopInList(int, int, vector<pokeStop>);
void fillTable(Matrix<int>&, vector<pokeStop>);

int main()
{
	int numStops = 0;
	int numStopsCounter = 0;
	int tempXCoord = 0;
	int tempYCoord = 0;
	string pokemon = " ";
	vector<pokeStop> pokeStopList;
	ifstream inFile;
	Matrix<int> distanceTable;
	inFile.open("input.txt");

	inFile >> numStops;
	distanceTable.resize(numStops + 1, numStops + 1);
	pokeStopList.push_back(pokeStop(0, 0, 0, " "));
	while (!inFile.eof())
	{
		inFile >> tempXCoord >> tempYCoord >> pokemon;
		if (stopInList(tempXCoord, tempYCoord, pokeStopList))
			for (auto& stop : pokeStopList)
			{
				if (stop.xCoord == tempXCoord && stop.yCoord == tempYCoord)
					stop.pokemonList.push_back(pokemon);
			}
		else
		{
			++numStopsCounter;
			pokeStopList.push_back(pokeStop(numStopsCounter, tempXCoord, tempYCoord, pokemon));
		}
	}
	for (auto stop : pokeStopList)
	{
		cout << stop.stopNum << " " << stop.xCoord << " " << stop.yCoord << endl;
		for (int i = 0; i < stop.pokemonList.size(); ++i)
		{
			cout << stop.pokemonList[i] << " ";
		}
		cout << endl;
	}
	fillTable(distanceTable, pokeStopList);
	for (int i = 0; i < distanceTable.numrows(); ++i)
	{
		for (int j = 0; j < distanceTable.numcols(); ++j)
		{
			cout << distanceTable[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
		return 0;
}

bool stopInList(int tempX, int tempY, vector<pokeStop> stopList)
{
	for (auto stop : stopList)
	{
		if (stop.xCoord == tempX && stop.yCoord == tempY)
			return true;
	}
	return false;
}

void fillTable(Matrix<int>& table, vector<pokeStop> stopList)
{
	int distance = 0;
	for (int i = 0; i < table.numrows(); ++i)
		for (int j = 0; j < table.numcols(); ++j)
		{
			distance += abs(stopList[i].xCoord - stopList[j].xCoord);
			distance += abs(stopList[i].yCoord - stopList[j].yCoord);
			table[i][j] = distance;
			distance = 0;
		}
}