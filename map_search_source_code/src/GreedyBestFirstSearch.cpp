/*
 * Search.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kev1nnsays
 */

#include "SearchDerived.h"

GreedyBestFirstSearch::GreedyBestFirstSearch(map2d<char>::type mapOriginal_):Search(mapOriginal_){
	map3d<bool>::type temp(mapRows, std::vector<std::vector<bool> >(mapCols, std::vector<bool>(6)));
	mapHealth = temp;
}

GreedyBestFirstSearch::~GreedyBestFirstSearch(){
}

node GreedyBestFirstSearch::conductSearch()
{
	//Note: check for goal when selecting node for expansion

	//initialize state
	startCoord = findChar(startChar);
	goalCoord = findChar(goalChar);
	goalNode.coord = goalCoord;

	node rootNode;
	rootNode.coord = startCoord;
	rootNode.coord.c = 'S';
	rootNode.pathLength = 0;
	rootNode.pathCost = 0;
	rootNode.coord.attacked = 0;
	rootNode.heuristicCost = std::abs(rootNode.coord.m - goalNode.coord.m) + std::abs(rootNode.coord.n - goalNode.coord.n);
	rootNode.health = 5;

	frontier.push(rootNode);
	markAsExplored(rootNode);
	markHealthMap(rootNode);

	//loop
	while(!frontier.empty())
	{
		//Select node for expansion
		node currNode = frontier.top();
		frontier.pop();
		markAsFrontier(currNode);

		totalNodesExamined += 1;
		if(isGoal(currNode))
		{
			goalNode = currNode;
			return currNode;
		}
		markAsExplored(currNode);

		//Generate children nodes
		std::vector<node> childrenVec = generateChildrenNodes(currNode);
		for(int k = 0; k<childrenVec.size();k++)
		{
			node child = childrenVec.at(k);
			if(child.health > 0)
			{
				//Push child to frontier
				if((isNotExploredNode(child) && isNotInFrontier(child)) ||
						isNewHealthBranch(child))
				{
					frontier.push(child);
					markAsFrontier(child);
					markHealthMap(child);
				}
			}
			else
			{
//				totalNodesExamined += 1;
//				std::cout << "dead" << std::endl;
				;
			}
		}
		markAsNotFrontier(currNode);
	}
	node resultNode;
	return resultNode;
}

bool GreedyBestFirstSearch::isNewHealthBranch(node target)
{
	if(mapHealth.at(target.coord.m).at(target.coord.n).at(target.health))
		return false;
	else
		return true;
}

void GreedyBestFirstSearch::markHealthMap(node target)
{
	mapHealth.at(target.coord.m).at(target.coord.n).at(target.health) = true;
}


