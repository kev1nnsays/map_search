/*
 * LoadFile.h
 *
 *  Created on: Sep 16, 2016
 *      Author: kev1nnsays
 */

#ifndef HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_SRC_LOADFILE_H_
#define HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_SRC_LOADFILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "GenericStructures.h"

class LoadFile
{
public:
	LoadFile(std::string fileName);
	virtual ~LoadFile();

	map2d<char>::type getMap();
	void printMap2d();

	map2d<char>::type* mapOriginal;

private:
	void loadMap2d(std::string fileName);
};

#endif /* HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_SRC_LOADFILE_H_ */
