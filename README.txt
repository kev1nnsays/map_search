This code finds a path from start to goal node using different search 
algorithms. The search algorithms can be used to find paths through 
an occupancy grid. The main program applies the search algorithms 
to a tower defense game, where a robot with 5 HP must find the optimal
path through a maze filled with swamps and towers. The text map can be 
constructed as follows:

S = Start node
G = Goal node
X = Wall
* = Swamp (slows robot by 3 turns)
o = Towers (injures robot by 1 HP)

To compile code on Linux (cmake required):
	1. Navigate into folder map_search_source_code
		>>cd map_search_source_code
	2. Build the source code using the "auto_build_and_exe.sh" script
 		>> source auto_build_and_exe.sh
	3. The executable is located at map_search_source_code/build/map_search

To run the executable (user defined map and search type):
	1. Navigate into folder map_search_source_code/build
		>>cd map_search_source_code
	2. Run the executable map_search with the text file location and mode
	   	>>./map_search <map file> <mode>

	   Some text file maps are located in map_search_source_code/text_maps
	   Mode:
	   	1 = Depth, Breadth, Uniform Search 
		2 = Greedy and A* Search 
		3 = A* Search with zero, manhattan, move horizontally, and wall 
		    heuristics 
		
	   For example, to run a Greedy and A* Search on the map "large_map1.txt" 
	   in folder "text_maps/":
	   	>> ./map_search_search ../text_maps/large_map1.txt 2

Author: Kevin Choi
Date: Sept-16-2016
