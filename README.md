# Kruskal Maze Generation Algorithm

This repository contains a C++ implementation of the Kruskal Maze Generation Algorithm. The algorithm was developed as part of a learning exercise while working on a labyrinth game in Unreal Engine 4 (UE4). Although the UE4 project files are no longer available, the core algorithm and its functionality are preserved here.

## Overview

The Kruskal Maze Generation Algorithm creates a maze using a randomized version of Kruskal's algorithm for minimum spanning trees. This method ensures that the generated maze has a single, unique solution with no isolated sections.

## Sample Output

Here is a sample output of the generated maze:

<pre>
[1]    25   [2]    9    [3]    1    [4]    21   [5]

11          24          10          21          4

[6]    16   [7]    10   [8]    7    [9]    1    [10]

17          17          16          17          3

[11]   19   [12]   12   [13]   13   [14]    4   [15]

3           13          19          23          22

[16]    7   [17]    5   [18]   18   [19]   18   [20]

22          11          16          20          17

[21]   21   [22]    4   [23]   24   [24]   19   [25]
</pre>

## Test Cases
I also wrote an automatic tester:
- **Complex graph small circle:** successful
- **Complex graph no circle:** successful
- **Complex graph big circle:** successful
- **Single graph:** successful
- **Tri point graph no circle:** successful
- **Tri point graph has circle:** successful
- **Rectangular graph has circle:** successful
- **Rectangular graph no circle:** successful
