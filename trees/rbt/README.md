# Red-Black Tree

Red-Black Tree is a type of a self-balancing Binary Search Tree (BST)

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

The following diagrams illustrate all cases for recovering from a red violation:

- **GP**: Grandparent
- **P**: Parent
- **U**: Aunt/Uncle of the Child that we inserted
- **C**: Child that we inserted

**Case 1**: Aunt/Uncle is red; perform a color flip.

![Case 1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-insert-case-1.png)

**Case 2**: Aunt/Uncle is black, violation is in straight direction; perform single rotation, recolor nodes;

![Case 2-1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-insert-case-2.png)

**Case 3**: Aunt/Uncle is black, violation is in zig-zag direction; perform double rotation, recolor nodes;

![Case 3](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-insert-case-3.png)

**Real-world Examples**:

- Start with a red-black tree built from the sequence: **40, 20, 10, 30, 60, 50, 70**, and insert **80**. **Case 1** will occurr at **60**, and **Case 2** will occurr at **20**.
- Start with a red-black tree built from the sequence: **70, 20, 10, 40, 80, 50, 30**, and insert **60**. **Case 1** will occurr at **40**, and **Case 3** will occurr at **20**.

### Deletion

Create a dummy tree root, colored in black, and assign its right child to be the actual tree root (this will spare us from having to deal with tricky edge cases later on). Then start moving down the tree, searching for the value you'd like to delete. 

On the way down:
- Keep rebalancing the tree in a way that ensures that the node that will end up being removed is going to be red.
- If you encounter the value you want to delete along the way, store its pointer into a variable, but keep walking down, until you reach a leaf node (you may need this pointer later on, in case you have to swap the node you want to remove with its inorder predecessor)

Other than that, the standard BST deletion principles apply:
- If the node to be deleted has no children, remove it.
- If the node to be deleted has one child, replace it with its child.
- If the node to be deleted has two children, find its inorder predecessor, swap the values, and remove the predecessor.

The following diagrams illustrate all the cases for ensuring that the node that will be removed from the tree is red.

- **P:** Parent
- **C:** Current (the node we are currently looking at)
- **S:** Sibling of the Current node
- **N:** Next (the node we will visit next)

**Case 1**: Current node is black, next node is black, sibling of next node is red; perform single rotation, recolor nodes;

![Case 1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-delete-case-1.png)

**Case 2**: Current node is black, both of its children are black, both of its sibling's children are black; perform reverse color flip;

![Case 2](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-delete-case-2.png)

**Case 3**: Sibling is black and has a red child in zig-zag direction from parent; perform double rotation, fix node colors;

![Case 3](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-delete-case-3.png)

**Case 4**: Sibling is black and has a red child in straight direction from parent; perform single rotation, fix node colors;

![Case 4](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/rbt/images/rbt-delete-case-4.png)

**Real-world Examples:**

Starting with a red-black tree built from the sequence: **110, 50, 20, 100, 70, 120, 40, 10, 90, 30, 60**.

You can encounter all different cases, if you follow these steps:

- **Case 1**: Insert 95, then delete 90.
- **Case 2**: Insert 95 and immediately delete it, then delete 90.
- **Case 3**: Insert 65, then delete 90.
- **Case 4**: Insert 55, then delete 90.

### Search

Perform standard BST search.

## Further reading

http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx
