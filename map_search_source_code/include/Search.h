/*
 * Search.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kev1nnsays
 */

#ifndef HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_INCLUDE_SEARCH_H_
#define HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_INCLUDE_SEARCH_H_

#include "GenericStructures.h"
#include <iostream>
#include <stack>
#include <queue>
#include <cmath>

class Search
{
public:
	Search(map2d<char>::type);
	virtual ~Search();

	state startCoord, goalCoord;
	char startChar, goalChar;
	int totalNodesExamined;
	std::vector<char> obstacles;
	std::vector<state> neighborOrder;
	node goalNode;

	state findChar(char); //returns coordinate of first match, starts search from upper left corner

	int mapRows, mapCols;
	map2d<char>::type mapOriginal;
	map2d<bool>::type mapExploredSet;
	map2d<bool>::type mapFrontier;
	map2d<state>::type mapParent;
	map2d<int>::type mapLowestCost;
	std::vector<node> closedNodeList;

	void pickLeafNode();
	std::vector<node> generateChildrenNodes(const node parent);
	void markAsExplored(node);
	void markAsUnexplored(node);
	void markAsFrontier(node);
	void markAsNotFrontier(node);
	void markParentMap(node);

	bool isNotInFrontier(node);
	bool isInFrontier(node);
	bool isNotExploredNode(node);
	bool isNotObstacle(const node target);
	int isAttackedNode(node);
	bool isGoal(node);

	map3d<bool>::type mapHealth;
	bool isNewHealthBranch(node);
	void markHealthMap(node);

	//function pointer for evaluating heuristic
	float (Search::*heuristicEval)(node, node);
	float manhattanHeuristicEval(node,node);
	float zeroCostHeuristicEval(node,node);
	float moveHorizHeuristicEval(node,node);
	float wallHeuristicEval(node,node);

	void debug();
	template<typename T>
	void printMap2d(T &);
	void printPath(pathDirection);

};


#endif /* HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_INCLUDE_SEARCH_H_ */
