#include "LoadFile.h"
#include "GenericStructures.h"
#include "SearchDerived.h"
#include "cstring"

typedef struct{
	node DFS;
	node BFS;
	node US;
	node GBFS;
	node ASS;
}test;

template<typename T>
void performanceMetrics(T searcher, node resultNode, node answerNode);

template<typename T>
void performanceMetrics(T searcher, node resultNode);

std::vector<char> stringToVec(std::string myWord);

test initAnswers(test &testAnswer);

void testCases();
void uninformedSearch(std::string);
void informedSearch(std::string);
void informedSearchAltHeuristic(std::string);

int main(int argc, char* argv[])
{
    std::string fileName;
    int mode;
    if( argc < 2)
    {
    	std::cout << "Need text file location and mode (1,2,or 3)." << std::endl;

    } else if (argc < 3)
	{
    	std::cout << "Need mode (1,2,or 3)." << std::endl;
	} else
	{
		mode = ((int) *argv[2])-48;
		if (mode<1 || mode>3)
		{
			std::cout << " Not valid mode (1,2,or 3)." << std::endl;
		}
		else
		{
			fileName = std::string(argv[1]);
//			std::cout << "fileName = " << fileName << " mode = " << mode << std::endl;

			switch(mode)
			{
			case 1:
				uninformedSearch(fileName);
				break;
			case 2:
				informedSearch(fileName);
				break;
			case 3:
				informedSearchAltHeuristic(fileName);
				break;
			}
		}
	}
	return 0;
}

template<typename T>
void performanceMetrics(T searcher, node resultNode, node answerNode)
{
	std::cout << "Returned Path:" << std::endl;
	searcher.printPath(resultNode.pathDir);
	std::cout << std::endl;
	std::cout << "Path Length: " << resultNode.pathLength <<std::endl;
	std::cout << "Path Cost: " << resultNode.pathCost <<std::endl;
	std::cout << "Nodes explored: " << searcher.totalNodesExamined <<std::endl;

	if(resultNode.pathLength == answerNode.pathLength &&
			resultNode.pathCost == answerNode.pathCost &&
			resultNode.pathDir == answerNode.pathDir &&
			searcher.totalNodesExamined == answerNode.nodesExaminedTest)
	{
		std::cout << "CORRECT" << std::endl;
	}
	else
	{
		std::cout << "FAILED!!!!!!!!!" << std::endl;
		if(resultNode.pathLength != answerNode.pathLength)
			std::cout << "Path Length: Result = " << resultNode.pathLength << ", Answer = " << answerNode.pathLength << std::endl;

		if(resultNode.pathCost != answerNode.pathCost)
			std::cout << "Path Cost: Result = " << resultNode.pathCost << ", Answer = " << answerNode.pathCost << std::endl;

		if(resultNode.pathDir != answerNode.pathDir)
		{
			std::cout << "Path Direction: Result = " << std::endl;
			searcher.printPath(resultNode.pathDir);
			std::cout << std::endl << ", Answer = " << std::endl;
			searcher.printPath(answerNode.pathDir);
			std::cout << std::endl;
		}

		if(searcher.totalNodesExamined != answerNode.nodesExaminedTest)
					std::cout << "Nodes Examined: Result = " << searcher.totalNodesExamined << ", Answer = " << answerNode.nodesExaminedTest << std::endl;
	}

	std::cout << std::endl;
}

template<typename T>
void performanceMetrics(T searcher, node resultNode)
{
	std::cout << "Returned Path:" << std::endl;
	searcher.printPath(resultNode.pathDir);
	std::cout << std::endl;
	std::cout << "Path Length: " << resultNode.pathLength <<std::endl;
	std::cout << "Path Cost: " << resultNode.pathCost <<std::endl;
	std::cout << "Nodes explored: " << searcher.totalNodesExamined <<std::endl;
	std::cout << std::endl;
}



std::vector<char> stringToVec(std::string myWord)
{
	char myArray[myWord.size()+1];//as 1 char space for null is also required
	std::strcpy(myArray, myWord.c_str());
	std::vector<char> v(&myArray[0], &myArray[0]+myWord.size());
	return v;
}

test initAnswers(test &testAnswer){
	testAnswer.DFS.pathDir= stringToVec("NNNNEEEEENNEEEESSWSSSSWWNNWWSSWWSWSWSSEEEEEEESSEEEEEENNWWWNNNNNNNENNNEEEEEESSWSSESS");
	testAnswer.DFS.pathLength = 83;
	testAnswer.DFS.pathCost = 103;
	testAnswer.DFS.nodesExaminedTest = 97;

	testAnswer.BFS.pathDir= stringToVec("EEEENEESEENNNEEENNNEEEEEESSWSSESS");
	testAnswer.BFS.pathLength = 33;
	testAnswer.BFS.pathCost = 47;
	testAnswer.BFS.nodesExaminedTest = 160;

	testAnswer.US.pathDir= stringToVec("NNNNEEEEENEEEESSEENNNEEEEEESSWSSESS");
	testAnswer.US.pathLength = 35;
	testAnswer.US.pathCost = 35;
	testAnswer.US.nodesExaminedTest = 156;

	testAnswer.GBFS.pathDir= stringToVec("EEEEEEENNWWNNWWNNEEEEEEEEEEESSSSSS");
	testAnswer.GBFS.pathLength = 34;
	testAnswer.GBFS.pathCost = 64;
	testAnswer.GBFS.nodesExaminedTest = 140;

	testAnswer.ASS.pathDir= stringToVec("WSSEEEEEESSSSEENNEENNEENNNNWWNNWWNNEEEEEEESSSSSS");
	testAnswer.ASS.pathLength = 48;
	testAnswer.ASS.pathCost = 58;
	testAnswer.ASS.nodesExaminedTest = 384;

	return testAnswer;
}

void testCases()
{
	//----Load Maze from text file----
	LoadFile fileLoaderPart1("../../homework_1_source_code/text_maps/test_map1.txt");
	fileLoaderPart1.printMap2d();
	std::cout << std::endl;
	//	homework_1::Graph grapher(fileLoader.getMap());
	//	grapher.testPlot();

	test testAnswers;
	initAnswers(testAnswers);

	//----Depth First Search----
	std::cout << "---- Depth First Search ----" << std::endl;
	DepthFirstSearch DFS(fileLoaderPart1.getMap());
	node resultNodeDFS = DFS.conductSearch();
	performanceMetrics(DFS,resultNodeDFS, testAnswers.DFS);

	//----Breadth First Search----
	std::cout << "---- Breadth First Search ----" << std::endl;
	BreadthFirstSearch BFS(fileLoaderPart1.getMap());
	node resultNodeBFS = BFS.conductSearch();
	performanceMetrics(BFS,resultNodeBFS, testAnswers.BFS);

	//----Uniform Search----
	std::cout << "---- Uniform Search ----" << std::endl;
	UniformSearch US(fileLoaderPart1.getMap());
	node resultNodeUS = US.conductSearch();
	performanceMetrics(US,resultNodeUS, testAnswers.US);

	//----Load Maze from text file----
	LoadFile fileLoaderPart2("../../homework_1_source_code/text_maps/test_map2.txt");
	fileLoaderPart2.printMap2d();
	std::cout << std::endl;

	//----Greedy Best First Search----
	std::cout << "---- GBFS Search ----" << std::endl;
	GreedyBestFirstSearch GBFS(fileLoaderPart2.getMap());
	node resultNodeGBFS = GBFS.conductSearch();
	performanceMetrics(GBFS,resultNodeGBFS, testAnswers.GBFS);

	//----A* Search----
	std::cout << "---- A* Search ----" << std::endl;
	AStarSearch ASS(fileLoaderPart2.getMap());
	node resultNodeASS = ASS.conductSearch();
	performanceMetrics(ASS,resultNodeASS, testAnswers.ASS);
}

void uninformedSearch(std::string fileName)
{

	//----Load Maze from text file----
//	LoadFile fileLoaderPart1("../../homework_1_source_code/text_maps/large_map1.txt");
	LoadFile fileLoaderPart1(fileName);
//	fileLoaderPart1.printMap2d();
	std::cout << std::endl;

	std::cout << "---- HW1 Problem1 ----" << std::endl;

	//----Depth First Search----
	std::cout << "---- (1A) Depth First Search ----" << std::endl;
	DepthFirstSearch DFS(fileLoaderPart1.getMap());
	node resultNodeDFS = DFS.conductSearch();
	performanceMetrics(DFS,resultNodeDFS);

	//----Breadth First Search----
	std::cout << "---- (1B) Breadth First Search ----" << std::endl;
	BreadthFirstSearch BFS(fileLoaderPart1.getMap());
	node resultNodeBFS = BFS.conductSearch();
	performanceMetrics(BFS,resultNodeBFS);

	//----Uniform Search----
	std::cout << "---- (1C) Uniform Search ----" << std::endl;
	UniformSearch US(fileLoaderPart1.getMap());
	node resultNodeUS = US.conductSearch();
	performanceMetrics(US,resultNodeUS);
}

void informedSearch(std::string fileName)
{
	//----Load Maze from text file----
//	LoadFile fileLoaderPart2("../../homework_1_source_code/text_maps/large_map2.txt");
	LoadFile fileLoaderPart2(fileName);
//	fileLoaderPart2.printMap2d();
	std::cout << std::endl;

	//----Greedy Best First Search----
	std::cout << "---- (2A) GBFS Search ----" << std::endl;
	GreedyBestFirstSearch GBFS(fileLoaderPart2.getMap());
	node resultNodeGBFS = GBFS.conductSearch();
	performanceMetrics(GBFS,resultNodeGBFS);

	//----A* Search----
	std::cout << "---- (2B) A* Search ----" << std::endl;
	AStarSearch ASS(fileLoaderPart2.getMap());
	node resultNodeASS = ASS.conductSearch();
	performanceMetrics(ASS,resultNodeASS);
}

void informedSearchAltHeuristic(std::string fileName)
{
//	LoadFile fileLoaderPart2("../../homework_1_source_code/text_maps/large_map2.txt");
	LoadFile fileLoaderPart2(fileName);
//	fileLoaderPart2.printMap2d();
	std::cout << std::endl;

	//----(1) A* Search with Zero Heruistic----
	std::cout << "---- A* Search:Zero Cost Heuristic (Eq. to Uniform) ----" << std::endl;
	AStarSearch ASS1(fileLoaderPart2.getMap());
	ASS1.heuristicEval = &Search::zeroCostHeuristicEval;
	node resultNodeASS1 = ASS1.conductSearch();
	performanceMetrics(ASS1,resultNodeASS1);

	//----(2) A* Search with Manhattan Dist. Heruistic----
	std::cout << "---- A* Search: Manhattan Dist. Heruistic (Default) ----" << std::endl;
	AStarSearch ASS2(fileLoaderPart2.getMap());
	ASS2.heuristicEval = &Search::manhattanHeuristicEval;
	node resultNodeASS2 = ASS2.conductSearch();
	performanceMetrics(ASS2,resultNodeASS2);

	//----(3) A* Search Diagonal Heruistic----
	std::cout << "---- A* Search: Move Horizontally ----" << std::endl;
	AStarSearch ASS3(fileLoaderPart2.getMap());
	ASS3.heuristicEval = &Search::moveHorizHeuristicEval;
	node resultNodeASS3 = ASS3.conductSearch();
	performanceMetrics(ASS3,resultNodeASS3);

	//----(4) A* Search Wall--
	std::cout << "---- A* Search: Wall ----" << std::endl;
	AStarSearch ASS4(fileLoaderPart2.getMap());
	ASS4.heuristicEval = &Search::wallHeuristicEval;
	node resultNodeASS4 = ASS4.conductSearch();
	performanceMetrics(ASS4,resultNodeASS4);

}


