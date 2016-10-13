/*
 * SearchDerived.h
 *
 *  Created on: Sep 23, 2016
 *      Author: kev1nnsays
 */

#ifndef HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_INCLUDE_SEARCHDERIVED_H_
#define HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_INCLUDE_SEARCHDERIVED_H_

#include "Search.h"


class DepthFirstSearch: public Search
{
public:
	DepthFirstSearch(map2d<char>::type);
	virtual ~DepthFirstSearch();
	node conductSearch();
	std::stack<node> frontier;
};

class BreadthFirstSearch:public Search
{
public:
	BreadthFirstSearch(map2d<char>::type);
	virtual ~BreadthFirstSearch();
	node conductSearch();
	std::queue<node> frontier;
};


//overload operator< for priority queue
class UniformSearch:public Search
{
public:
	UniformSearch(map2d<char>::type);
	virtual ~UniformSearch();
	node conductSearch();

	void markLowestCostMap(const node);
	bool isLowerCost(const node);
//	bool isNotExploredNode(const node); //validates as true if node is already explored but new cost is lower
	void replaceFrontierNode(const node);
	std::priority_queue<node, std::vector<node>, orderByPathCost> frontier;

};

class GreedyBestFirstSearch: public Search
{
public:
	GreedyBestFirstSearch(map2d<char>::type);
	virtual ~GreedyBestFirstSearch();
	node conductSearch();

	map3d<bool>::type mapHealth;
	bool isNewHealthBranch(node);
	void markHealthMap(node);

	std::priority_queue<node, std::vector<node>, orderByHeuristic> frontier;
};

class AStarSearch: public Search
{
public:
	AStarSearch(map2d<char>::type);
	virtual ~AStarSearch();
	node conductSearch();


	void markLowestCostMap(const node);
	bool isLowerCost(const node);
	void replaceFrontierNode(const node);

	std::priority_queue<node, std::vector<node>, orderByTotalCost> frontier;
};


#endif /* HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_INCLUDE_SEARCHDERIVED_H_ */
