# MMPDAHE
## Metis Mesh Partition Descomposion Across Hardware Elements

**"METIS is a set of serial programs for partitioning graphs, partitioning finite element meshes, and producing fill reducing orderings for sparse matrices. The algorithms implemented in METIS are based on the multilevel recursive-bisection, multilevel k-way, and multi-constraint partitioning schemes developed in our lab."** [Link to METIS](http://glaros.dtc.umn.edu/gkhome/metis/metis/overview)

An example of an unweighted graph stored in the METIS graph file format.
```sh
0---1---2
|   |   |
3---4---5
```
| Vertex |  Edges   | Number of Edges  |  
| ------ | ------ |------ |
|  0:    |   1 3    |      2           |
|  1:    |   0 4 2  |      5           |
|  2:    |   1 5    |      7           |
|  3:    |   0 4    |      9           |
|  4:    |   3 1 5  |      12          |
|  5:    |   4 2    |      14          |    

The first non-comment line lists  the number of vertices (6) and edges (7).

The next line notes that vertex 1 is connected to vertices 5, 3 and 2.
Subsequent lines list the neighbors of successive vertices.

Notice that each edge is listed twice.  There are 11 edges, but 22 edge entries.

The mandatory parameters are nparts (number of partitions), xadj (the starting positions of adjacent list) and 
adjncy (the compressed adjacent list).

Give a a directed graph based on the following structure:

0---1---2
|   |   |
3---4---5
|   |   |
6---7---8

We can have the set up a simple graph representation, which looks like

>>> graph = {
...    0: [1, 3],
...    1: [0, 2, 4],
...    2: [1, 5],
...    3: [0, 4, 6],
...    4: [1, 3, 5, 7],
...    5: [2, 4, 8],
...    6: [3, 7],
...    7: [4, 6, 8],
...    8: [5, 7],
... }
