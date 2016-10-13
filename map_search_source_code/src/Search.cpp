/*
 * Search.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kev1nnsays
 */

#include "Search.h"

Search::Search(map2d<char>::type mapOriginal_)
{
	//Important characters
	startChar = 'S';
	goalChar = 'G';
	obstacles.push_back('X');
	obstacles.push_back('O');

	//Maps
	mapOriginal = mapOriginal_;
	mapRows = mapOriginal.size();
	mapCols = mapOriginal.at(0).size();
	map2d<bool>::type temp(mapRows, std::vector<bool>(mapCols));
	mapExploredSet = temp;
	map2d<int>::type temp2(mapRows, std::vector<int>(mapCols));
	mapLowestCost = temp2;
	map2d<bool>::type temp3(mapRows, std::vector<bool>(mapCols));
	mapFrontier = temp3;
	map2d<state>::type temp4(mapRows, std::vector<state>(mapCols));
	mapParent = temp4;
	map3d<bool>::type temp5(mapRows, std::vector<std::vector<bool> >(mapCols, std::vector<bool>(6)));
	mapHealth = temp5;

	//Count number of nodes explored
	totalNodesExamined = 0;

	//Order to check for neighbors; map is mxn
	//NWES
	state N; N.m = -1; N.n = 0; N.c='N';
	neighborOrder.push_back(N);
	state W; W.m = 0; W.n = -1; W.c='W';
	neighborOrder.push_back(W);
	state E; E.m = 0; E.n = 1; E.c='E';
	neighborOrder.push_back(E);
	state S; S.m = 1; S.n = 0; S.c='S';
	neighborOrder.push_back(S);

	//Point to default heuristic evaluation
	heuristicEval = &Search::manhattanHeuristicEval;
}

Search::~Search() {
}

state Search::findChar(char target)
{
	state result;
	for(int i=0; i<mapRows; i++)
	{
		for(int j=0; j<mapCols; j++)
		{
			if(mapOriginal.at(i).at(j) == target)
			{
				result.m = i;
				result.n = j;
				return result;
			}
		}
	}
	std::cout << "Character " << target << "not found!!!!!" << std::endl;
	return result;
}

void Search::markAsExplored(node target)
{
	mapExploredSet.at(target.coord.m).at(target.coord.n) = true;
}

void Search::markAsUnexplored(node target)
{
	mapExploredSet.at(target.coord.m).at(target.coord.n) = false;
}

void Search::markAsFrontier(node target)
{
	mapFrontier.at(target.coord.m).at(target.coord.n) = true;
}

void Search::markAsNotFrontier(node target)
{
	mapFrontier.at(target.coord.m).at(target.coord.n) = false;
}

void Search::markParentMap(node target)
{
		mapParent.at(target.coord.m).at(target.coord.n).m = target.parentCoord.m;
		mapParent.at(target.coord.m).at(target.coord.n).n = target.parentCoord.n;
}

std::vector<node> Search::generateChildrenNodes(const node parent)
{
	std::vector<node> childrenVec;

	//Iterate through neighborOrder to generate children nodes
	for(int k=0;k<neighborOrder.size();k++)
	{
		node child;
		int rowDelta = neighborOrder.at(k).m;
		int colDelta = neighborOrder.at(k).n;
		if(parent.coord.m+rowDelta >= 0 &&
			parent.coord.n+colDelta >= 0 &&
			parent.coord.m+rowDelta < mapRows &&
			parent.coord.n+colDelta < mapCols)
		{
			child.coord.m = parent.coord.m+rowDelta;
			child.coord.n = parent.coord.n+colDelta;
			child.coord.c = mapOriginal.at(parent.coord.m+rowDelta).at(parent.coord.n+colDelta);

			if(isNotObstacle(child))
			{
				//Populate attacked
				int numberAttacked = isAttackedNode(child);

				if(numberAttacked>0)
					child.coord.attacked = numberAttacked;
				else
					child.coord.attacked = 0;

				//Populate node's parent location
				child.parentCoord = parent.coord;

				//Populate pathLength
				child.pathLength = parent.pathLength +1;

				//Populate pathCost
				if(parent.coord.c == '*') //swamp
					child.pathCost = parent.pathCost + 3;
				else
					child.pathCost = parent.pathCost + 1;

				//Populate Health
				if(child.coord.c == '*') //swamp
					child.health = parent.health - 3*child.coord.attacked;
				else
					child.health = parent.health - child.coord.attacked;

				if(child.health < 0)
					child.health = 0;

				//Populate heuristic using Manhattan Distance
				child.heuristicCost = ((*this).*(heuristicEval))(goalNode, child);

				//Populate total cost = path cost + heuristic cost
				child.totalCost = child.pathCost + child.heuristicCost;

				//Populate path direction
				child.pathDir = parent.pathDir;
				child.pathDir.push_back(neighborOrder.at(k).c);

				childrenVec.push_back(child);
			}
		}
	}
	return childrenVec;
}


bool Search::isInFrontier(const node target)
{
	if(mapFrontier.at(target.coord.m).at(target.coord.n) == true)
		return true;
	else
		return false;
}

bool Search::isNotInFrontier(const node target)
{
	if(mapFrontier.at(target.coord.m).at(target.coord.n) == true)
		return false;
	else
		return true;
}

bool Search::isNotExploredNode(const node target) //examines if node has been explored yet
{

	if(mapExploredSet.at(target.coord.m).at(target.coord.n) == true)
		return false;
	else
		return true;
}

bool Search::isNotObstacle(const node target)
{
	for(int k=0; k<obstacles.size();k++)
	{
		if(mapOriginal.at(target.coord.m).at(target.coord.n) == obstacles.at(k)){
			return false;
		}
	}
	return true;
}

int Search::isAttackedNode(const node target)
{
	int attackNumber = 0;
	for(int k=0;k<neighborOrder.size();k++) //examine neighbors for towers
	{

		int rowDelta = neighborOrder.at(k).m;
		int colDelta = neighborOrder.at(k).n;
		int examineM = target.coord.m+rowDelta;
		int examineN = target.coord.n+colDelta;

		if(examineM>=0 && examineM<mapOriginal.size() && examineN>=0 && examineN<mapOriginal.at(0).size())
		{
			if(mapOriginal.at(examineM).at(examineN) == 'O') //tower is present
				attackNumber++;
		}
	}
	return attackNumber;
}

bool Search::isGoal(node target)
{
	if(target.coord.c=='G')
		return true;
	else
		return false;
}

bool Search::isNewHealthBranch(node target)
{
	if(mapHealth.at(target.coord.m).at(target.coord.n).at(target.health))
		return false;
	else
		return true;
}

void Search::markHealthMap(node target)
{
	mapHealth.at(target.coord.m).at(target.coord.n).at(target.health) = true;
}

float Search::manhattanHeuristicEval(node A, node B)
{
	return std::abs(A.coord.m - B.coord.m) + std::abs(A.coord.n - B.coord.n);
}

float Search::zeroCostHeuristicEval(node A, node B)
{
	return 0;
}

float Search::moveHorizHeuristicEval(node A, node B)
{
	return 0.25*std::abs(A.coord.m - B.coord.m) + std::abs(A.coord.n - B.coord.n);
}

float Search::wallHeuristicEval(node goalNode, node currNode)
{

	if(currNode.coord.n == goalNode.coord.n) //In eastern most column
		return Search::manhattanHeuristicEval(goalNode,currNode);

	node eastNode; //Open space directly east
	eastNode.coord.m = currNode.coord.m;
	eastNode.coord.n = currNode.coord.n+1;
	if(isNotObstacle(eastNode))
		return 1+Search::manhattanHeuristicEval(goalNode, eastNode);

	node northNode;
	float northNodeHeuristic = -1;
	northNode.coord.m = currNode.coord.m-1; //north
	northNode.coord.n = currNode.coord.n+1; //east
	while(northNode.coord.m>=0)
	{
		if(isNotObstacle(northNode))
		{
			northNodeHeuristic = 1+std::abs(northNode.coord.m-currNode.coord.m)+
					Search::manhattanHeuristicEval(goalNode, northNode);
			break;
		}
		northNode.coord.m = northNode.coord.m-1; //increment north
	}

	node southNode;
	float southNodeHeuristic = -1;
	southNode.coord.m = currNode.coord.m+1;	//south
	southNode.coord.n = currNode.coord.n+1; //east
	while(southNode.coord.m<mapRows)
	{
		if(isNotObstacle(southNode))
		{
			southNodeHeuristic =  1+std::abs(southNode.coord.m-currNode.coord.m)+
					Search::manhattanHeuristicEval(goalNode, southNode);
			break;
		}
		southNode.coord.m = southNode.coord.m+1; //increment south
	}

	if(southNodeHeuristic < 0){ //no passage to south
		return northNodeHeuristic;
	} else if(northNodeHeuristic < 0){ //no passage north
		return southNodeHeuristic;
	} else if(southNodeHeuristic < northNodeHeuristic){ //south is closer
		return southNodeHeuristic;
	} else
		return northNodeHeuristic; //north i

}


void Search::debug()
{
	std::cout << std::endl << "Front:";
	for(int k=0; k<4;k++)
	{
	std::cout << neighborOrder.at(k).c;
	}
	std::cout << ":Back" << std::endl;

	std::cout << std::endl << "Front:";
	for(int k=3; k>=0;k--)
	{
	std::cout << neighborOrder.at(k).c;
	}
	std::cout << ":Back" << std::endl;
}

template<typename T>
void Search::printMap2d( T &mapTarget)
{
	std::cout << "----Map----" << std::endl;
	for(int i = 0; i < mapTarget.size(); i++)
	{
		for(int j = 0; j < mapTarget.at(0).size(); j++)
			std::cout << mapTarget.at(i).at(j);
		std::cout << std::endl;
	}
}

void Search::printPath(pathDirection pathResult)
{
	if(pathResult.size()==0)
	{
		std::cout << "NO PATH FOUND" <<std::endl;
	}
	else
	{
		for(int k=0;k<pathResult.size();k++)
		{
			std::cout<< pathResult.at(k);
		}
	}
}
