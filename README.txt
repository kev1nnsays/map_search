Author: Kevin Choi
Date: Sept-16-2016

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
