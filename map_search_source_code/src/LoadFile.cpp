/*
 * LoadFile.cpp
 *
 *  Created on: Sep 16, 2016
 *      Author: kev1nnsays
 */

#include "../../homework_1_source_code/include/LoadFile.h"

LoadFile::LoadFile(std::string fileName) {
	loadMap2d(fileName);
}

LoadFile::~LoadFile() {

}

void LoadFile::loadMap2d(std::string fileName)
{
	std::ifstream loader(fileName.c_str());
	if(!loader)
	{
		std::cout << "Cannot find file to load." << std::endl;
		throw std::exception();
	}

	//--------Load the first line which contains the rows and columns
	int m,n;
	std::string textLine;
	getline(loader, textLine);
	std::istringstream iss(textLine);
	iss >> m >> n;

	//--------Load the map
	mapOriginal = new map2d<char>::type(m, std::vector<char>(n)); //allocate mem
	for(int i = 0; i < m; i++)
	{
		getline(loader, textLine);
		std::vector<char> temp(textLine.begin(), textLine.end());
		mapOriginal->at(i) = temp;
	}
}

void LoadFile::printMap2d()
{
	std::cout << "----Loaded Map----" << std::endl;
	for(int i = 0; i < mapOriginal->size(); i++)
	{
		for(int j = 0; j < mapOriginal->at(0).size(); j++)
			std::cout << mapOriginal->at(i).at(j);
		std::cout << std::endl;
	}
}

map2d<char>::type LoadFile::getMap()
{
	return *mapOriginal;
}
