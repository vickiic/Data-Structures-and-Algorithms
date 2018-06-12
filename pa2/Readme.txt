Vicki Chen 8757122
To compile and run:

make
./final


Part 1:
Eccentricity of a node: The eccentricity of a node v is the maximum distance from v to another
vertex.
Diameter: The diameter is the greatest eccentricity of the nodes of a graph, or the greatest
distance between any pair of nodes. One method to do so is to find the shortest paths between
each pair of vertices and then choose the largest one.
Radius: The radius of a graph is the minimum eccentricity between any two nodes, which is the
minimum of the maximum distances between node pairs in the graph.
Center: The center of the graph is the set of all vertices u where the greatest distance to other
vertices v is minimal. Equivalently, it is the set of vertices with distances equal to the graph’s
radius. To find the central vertices, find the vertices with lowest eccentricity.
Output : 3 lines, first is diameter, second is radius, third is center node

part 2:
	-first output: shortest paths between all pairs of vertices in one file, ordered according to nodes
	-second output: a list of nodes in descending order of path centralities 

Part 3:
The output of the program is expected to be a single output file named “pa2_op3.txt”, having
exactly three lines. The first line must contain the source node and the sequence of nodes visited
during the bidirectional search. The second line must contain the destination node and the sequence
of nodes visited from the destination node during the bidirectional search. The third line is expected to have the sequence of nodes visited from source to destination using unidirectional search

Part 4: 
output: the node that has the least distance to each of the three vertices