# MMPDAHE
## Metis Mesh Partition Descomposion Across Hardware Elements

**"METIS is a set of serial programs for partitioning graphs, partitioning finite element meshes, and producing fill reducing orderings for sparse matrices. The algorithms implemented in METIS are based on the multilevel recursive-bisection, multilevel k-way, and multi-constraint partitioning schemes developed in our lab."** [Link to METIS](http://glaros.dtc.umn.edu/gkhome/metis/metis/overview)

Example 1: An unweighted graph stored in the METIS graph file format.

```sh
0---1---2
|   |   |
3---4---5
```

| Vertex |  Vertices   | Number of Edges  |  
| ------ |   ------    |     ------       |
|  0:    |   [1, 3]    |      2           |
|  1:    |   [0, 4, 2] |      5           |
|  2:    |   [1, 5]    |      7           |
|  3:    |   [0, 4]    |      9           |
|  4:    |   [3, 1, 5] |      12          |
|  5:    |   [4, 2]    |      14          |  

Using the table above we can buid the data set: 
```sh
6 7
1 3
0 4 2
1 5
0 4
3 1 5
4 2
```
- The first line lists  the number of vertices (6) and edges (7).
- The second line refer to vertex (0), list the connected vertices (1) and (3).
- The subsequent lines list the vertex's neighbors of successive connected vertices.
- Notice that each edge is listed twice. There are (7) edges, but (14) edge entries.

The mandatory parameters are:
- nparts (number of partitions), 
- xadj (the starting positions of adjacent list),
  xadj = [0, 2, 5, 7, 9, 12, 14]
- adjncy (the compressed adjacent list).
  adjncy = [1,3,0,4,2,1,5,0,4,3,1,5,4,2]

Fpr example2 : Give a a directed graph based on the following structure:
```sh
0---1---2
|   |   |
3---4---5
|   |   |
6---7---8
```
We can have the set up a simple graph representation, which looks like

| Vertex |  Vertices   | Number of Edges  |  
| ------ |   ------    |     ------       |
  0:     | [1, 3]      |     2            |
| 1:     | [0, 2, 4]   |     5            |
| 2:     | [1, 5]      |     7            |
| 3:     | [0, 4, 6]   |     10           |
| 4:     | [1, 3, 5, 7]|     14           |
| 5:     | [2, 4, 8]   |     17           |
| 6:     | [3, 7]      |     19           |
| 7:     | [4, 6, 8]   |     22           |
| 8:     | [5, 7]      |     24           |

```sh
8 12
1 3
0 2 4
1 5
0 4 6
1 3 5 7
2 4 8
3 7
4 6 8
5 7
```
The mandatory parameters are:
- nparts (number of partitions), 
- xadj (the starting positions of adjacent list),
  xadj = [0, 2, 5, 7, 10, 14, 17, 19, 22, 24]
- adjncy (the compressed adjacent list).
  adjncy = [1, 3, 0, 2, 4, 1, 5, 0, 4, 6, 1, 3, 5, 7, 2, 4, 8, 3, 7, 4, 6 ,8, 5, 7]
