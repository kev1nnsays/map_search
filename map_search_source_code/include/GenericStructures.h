/*
 * GenericStructures.h
 *
 *  Created on: Sep 17, 2016
 *      Author: kev1nnsays
 */

#ifndef HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_SRC_GENERICSTRUCTURES_H_
#define HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_SRC_GENERICSTRUCTURES_H_

#include <vector>

template<typename T>
struct map2d
{
	typedef std::vector<std::vector<T> > type;
};

template<typename T>
struct map3d
{
	typedef std::vector<std::vector<std::vector<T> > > type;
};

typedef std::vector<char> pathDirection;

struct state
{
	int m;
	int n;
	char c;
	int attacked;
};

struct node
{
	state coord;
	state parentCoord;
	pathDirection pathDir;
	int pathLength;
	float pathCost;
	float heuristicCost;
	float totalCost;
	int health;

	int nodesExaminedTest; //for checking answers
};

struct orderByPathCost{
	bool operator()(const node& a, const node& b){
		if(a.pathCost == b.pathCost)
		{

			if(b.coord.m < a.coord.m)
				return true;
			else
				{
					if(b.coord.m > a.coord.m)
						return false;
					else
					{
						if(b.coord.n < a.coord.n)
							return true;
						else
						{
							if(b.coord.n > a.coord.n)
								return false;
							else
							{
								return false;
							}
						}
					}
				}
		}
		return a.pathCost > b.pathCost;
	}
};

struct orderByHeuristic{
	bool operator()(const node& a, const node& b){
		if(a.heuristicCost == b.heuristicCost)
		{

			if(b.coord.m < a.coord.m)
				return true;
			else
				{
					if(b.coord.m > a.coord.m)
						return false;
					else
					{
						if(b.coord.n < a.coord.n)
							return true;
						else
						{
							if(b.coord.n > a.coord.n)
								return false;
							else
							{
								if(b.health > a.health)
									return true;
								else
									return false;
							}
						}
					}
				}
		}
		//Primary
		return a.heuristicCost > b.heuristicCost;
	}
};

struct orderByTotalCost{
	bool operator()(const node& a, const node& b){
		if(a.totalCost == b.totalCost)
		{

			if(b.coord.m < a.coord.m)
				return true;
			else
				{
					if(b.coord.m > a.coord.m)
						return false;
					else
					{
						if(b.coord.n < a.coord.n)
							return true;
						else
						{
							if(b.coord.n > a.coord.n)
								return false;
							else
							{
								if(b.health > a.health)
									return true;
								else
									return false;
							}
						}
					}
				}
		}
		//Primary
		return a.totalCost > b.totalCost;
	}
};

#endif /* HOMEWORK_1_HOMEWORK_1_SOURCE_CODE_SRC_GENERICSTRUCTURES_H_ */
