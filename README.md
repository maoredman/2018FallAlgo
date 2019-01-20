# 2018 Fall Algorithms course

* pa1: implement insertion sort, merge sort, heap sort, quicksort
* pa2: solve Maximum Planar Subset problem using dynamic programming (my implementation would have been more efficient if I used arrays)
* pa3: solve Global Routing problem using Dijkstra's shortest path algorithm. I used an array of `std::unordered_maps` to store the sparse graph, then used a min-heap (used a small "hack" on `std::priority_queue`) for the algorithm's `extract-min` operation, yielding an overall runtime of O(V lgV), where V is the number of grid cells (modeled as graph vertices)

**All code written in C++ for faster running time**
