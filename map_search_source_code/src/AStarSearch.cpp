/*
 * Search.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kev1nnsays
 */

#include "SearchDerived.h"

AStarSearch::AStarSearch(map2d<char>::type mapOriginal_):Search(mapOriginal_){


}

AStarSearch::~AStarSearch(){
}

node AStarSearch::conductSearch()
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
	rootNode.heuristicCost = ((*this).*(heuristicEval))(goalNode, rootNode);
	rootNode.totalCost = rootNode.pathCost + rootNode.heuristicCost;
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
						isNewHealthBranch(child) )
				{
					frontier.push(child);
					markAsFrontier(child);
					markLowestCostMap(child);
					markHealthMap(child);
				}
				else if(isInFrontier(child) && isLowerCost(child))
				{
					replaceFrontierNode(child);
				}
			}
			else
			{
	//			totalNodesExamined += 1;
	//			std::cout << "dead" << std::endl;
				;
			}
		}
		markAsNotFrontier(currNode);
	}
	node resultNode;
	return resultNode;
}



void AStarSearch::markLowestCostMap(node target)
{
	mapLowestCost.at(target.coord.m).at(target.coord.n) = target.totalCost;
}

bool AStarSearch::isLowerCost(const node target)
{
	if(target.totalCost < mapLowestCost.at(target.coord.m).at(target.coord.n))
		return true;
	else
		return false;
}

void AStarSearch::replaceFrontierNode(const node newNode)
{
	std::priority_queue<node, std::vector<node>, orderByTotalCost> frontierCopy = frontier;
	std::priority_queue<node, std::vector<node>, orderByTotalCost> frontierResult;

	while(!frontierCopy.empty())
	{
		//Don't push if it matches
		if(newNode.coord.m == frontierCopy.top().coord.m &&
				newNode.coord.n == frontierCopy.top().coord.n &&
				newNode.health == frontierCopy.top().health)
		{
			frontierResult.push(newNode);
		}
		else //Not matching so push
		{
			frontierResult.push(frontierCopy.top());
		}
		frontierCopy.pop();
	}
	markLowestCostMap(newNode);
	frontier = frontierResult;
}




