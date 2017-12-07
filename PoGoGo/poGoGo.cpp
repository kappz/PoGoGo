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

struct compare
{
	bool operator()(const Node& lhs, const Node& rhs)
	{
		return lhs.bound > rhs.bound;
	}
};

bool stopInList(int, int, vector<pokeStop>);

int main()
{
	int numStops = 0;
	int numStopsCounter = 0;
	int tempXCoord = 0;
	int tempYCoord = 0;
	string pokemon = " ";
	vector<pokeStop> pokeStopList;
	vector<string> empty;
	ifstream inFile;
	inFile.open("input.txt");
	inFile >> numStops;
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