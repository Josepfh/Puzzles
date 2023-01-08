# Puzzles

In this mini project, I tested my understanding of graphs and breadth-first search to solve two puzzles or brain teasers.

The first puzzle is Water Jugs problem:
  In this puzzle we have two cups with volumes 3 and 4 liters. Our goal is to measure 5 liters using only these cups.
  The action steps we can take are as follows:
    Fill A
    Fill B
    Pour A->B
    Pour B->A
    Empty A
    Empty B
  I tried solving this puzzle by using a graph structure and a breadth-first search. According to my program the solution steps are:
    Initial state: [0,0]
    Fill B: [0,4]
    Pour B->A: [3,1]
    Empty A: [0,1]
    Pour B->A: [1,0]
    Fill B: [1,4]
    
The second puzzle is the Wolf Goat and Cabbage puzzle:
  In this puzzle, there is one wolf, one goat and one cabbage on one side of a river. We are provided a boat that can take a person and an item at most to cross the river.
  Our goal is to make sure every single item crosses the river, but we fail if any of the following occur:
     If the goat and the wolf is left unattended, the goat eats the cabbage.
     If the wold and the goat is left unattended, the wold eats the goat.
  I wrote a program using a graph structure and breadth-first search to solve the puzzle. According to my program the solution steps are:
    Initial state: wolf goat cabbage you  |river|
    Cross with goat: wolf cabbage  |river| goat you
    Cross alone: wolf cabbage you  |river| goat
    Cross with wolf: cabbage  |river| wolf goat you
    Cross with goat: goat cabbage you  |river| wolf
    Cross with cabbage: goat  |river| wolf cabbage you
    Cross alone: goat you  |river| wolf cabbage
    Cross with goat:  |river| wolf goat cabbage you
