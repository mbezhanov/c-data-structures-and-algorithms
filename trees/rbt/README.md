# Red-Black Tree

Red-Black Tree is a variant of a self-balancing Binary Search Tree (BST)

## Complexity

| Operation | Average  | Worst case |
| --------- | -------- | ---------- |
| Insert    | O(log n) | O(log n)   |
| Delete    | O(log n) | O(log n)   |
| Search    | O(log n) | O(log n)   |

## Properties

In addition to the requirements imposed on a binary search tree, the following must also be satisfied by a red–black tree:

1. Each node is either red or black.
2. The root node is always black.
3. Leaf nodes (NULLs) are always black.
4. Red nodes have only black children.
5. Every path from a node to a descendant leaf contains the same number of black nodes.
6. Newly inserted nodes are red.

## Operations

### Insertion

Perform standard BST insertion, then rebalance the tree if the newly inserted node introduces a red violation.

The following charts, illustrate all cases for recovering from a red violation:

- **GP**: Grandparent
- **P**: Parent
- **U**: Aunt/Uncle of the Child that we inserted
- **C**: Child that we inserted

**Case 1**: Aunt/Uncle is red; perform a color flip.

![Case 1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-insert-case-1.png)

**Case 2**: Aunt/Uncle is black, violation is in straight direction; perform single rotation, recolor nodes;

![Case 2-1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-insert-case-2-1.png)

For a real world scenario, consider an example, where the value **80** is being inserted into a red-black tree, built from the sequence: **40, 20, 10, 30, 60, 50, 70**

![Case 2-2](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-insert-case-2-2.png)

**Case 3**: Aunt/Uncle is black, violation is in zig-zag direction; perform double rotation, recolor nodes;

![Case 3-1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-insert-case-3-1.png)

For a real world scenario, consider an example, where the value **60** is being inserted into a red-black tree, built from the sequence: **70, 20, 10, 40, 80, 50, 30**

![Case 3-2](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-insert-case-3-2.png?v=2)

### Deletion

**Case 1**:

*TBD*

**Case 2**:

*TBD*

**Case 3**:

*TBD*

**Case 4**:

*TBD*

### Search

Perform standard BST search.
