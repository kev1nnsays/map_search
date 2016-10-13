/*
 * Search.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kev1nnsays
 */

#include "SearchDerived.h"

BreadthFirstSearch::BreadthFirstSearch(map2d<char>::type mapOriginal_):Search(mapOriginal_){
}

BreadthFirstSearch::~BreadthFirstSearch(){
}

node BreadthFirstSearch::conductSearch()
{
	//Note: check for goal during node generation

	//initialize state
	startCoord = findChar(startChar);
	node rootNode;
	rootNode.coord = startCoord;
	rootNode.coord.c = 'S';
	rootNode.pathLength = 0;
	rootNode.pathCost = 0;
	
//	std::cout << "Start State:" << startCoord.m << ", " << startCoord.n << std::endl;

	frontier.push(rootNode);
	markAsExplored(rootNode);
	
	//loop
	while(!frontier.empty())
	{
		//Select node for expansion
		node currNode = frontier.front();
		frontier.pop();
		markAsFrontier(currNode);

		totalNodesExamined += 1;
		if(isGoal(currNode))
		{
			goalNode = currNode;
			return currNode;
		}
		markAsExplored(currNode);
		
		std::vector<node> childrenVec = generateChildrenNodes(currNode);
		for(int k = 0; k<childrenVec.size();k++)
		{
			//Push child to frontier
			if(isNotExploredNode(childrenVec.at(k)) && isNotInFrontier(childrenVec.at(k)))
			{
				frontier.push(childrenVec.at(k));
				markAsFrontier(childrenVec.at(k));
			}
		}
		markAsNotFrontier(currNode);
	}
	node resultNode;
	return resultNode;
}
