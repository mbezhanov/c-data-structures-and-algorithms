# Splay Tree

Splay Tree is a type of a self-adjusting Binary Search Tree (BST)

## Complexity

| Operation | Average  |
| --------- | -------- |
| Insert    | O(log n) |
| Delete    | O(log n) |
| Search    | O(log n) |

## Properties

Same as BST

## Operations

### Splaying

Splaying is the process of bringing a desired node to the root of the tree through rotations. Insertion, deletion and search are all built around splaying, so this is the most essential operation behind splay trees.

There are two possible implementations:

#### Recursive (Bottom-Up)

Easier to implement, but could also easily blow out the stack as the tree grows. You start at the tree root and begin searching for the node containing the value of interest. If neither the current node, nor any of its children contain that value, you repeat the procedure recursively on the current node's grandchild, then the grandchild's grandchild, and so on, until you either find the value, or reach the end of the tree (signified by a NULL node)

If the value is nowhere to be found, the last non-NULL node becomes the node to be brought to the root of the tree.

At each recursion step, you are on the lookout for the following cases:

* **Case 1**: Searched node is child of the current node; rotate current node;

    ![Recursive Splay: Case 1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-recursive-01.png)

* **Case 2**: Searched node is grandchild of the current node, and is in a straight direction; rotate its grandparent, then rotate its parent;

    ![Recursive Splay: Case 2](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-recursive-02.png)

* **Case 3**: Searched node is grandchild of the current node, and is in a zig-zag direction; rotate its parent, then rotate its grandparent;

    ![Recursive Splay: Case 3](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-recursive-03.png)

#### Iterative (Top-Down)

A little less trivial to implement, but with better performance indications:

Create a dummy tree root. This dummy tree root will act as a host of two subtrees:
- A **right subtree** rooted at its **left child**
- A **left subtree** rooted at its **right child**

![Dummy Tree](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-iterative-01.png)

Beginning from the root of the original tree, start moving down, searching for the node that needs to become the new root.

As you move down, if the current node is not the node you're looking for:

1. Perform a rotation, if the node you're looking for is located more than two steps away in a straight direction from the current node. For example, imagine you are searching for a node with a value of **less than 10** in the tree from the diagram below, and you're currently at the node with value **40** (**C** = current node; **OC** = old "current" node):

    ![Top-Down Splay Rotation](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-iterative-02.png)

    Keep in mind that after the rotation, the node that takes over the position of the previous "current node" is now considered the new "current node" (so this is the node that's going to be referenced in step 2)

2. Then, depending on the value of the current node:
    - Add it as the **leftmost child** of the **right subtree** hosted by the **dummy tree root**, if its value is higher than the value you're searching for
    - Add it as the **rightmost child** of the **left subtree** hosted by the **dummy tree root**, if its value is lower than the value you're searching for

Repeat steps 1 and 2, until you either find the node, or reach a node that has no further children (in which case, this node is going to become the new root)

Finally, to reassemble a tree, where the last visited node is going to be the root:

1. Add the node's **left child** as the **rightmost child** of the **left subtree** hosted by the **dummy tree root**
2. Add the node's **right child** as the **leftmost child** of the **right subtree** hosted by the **dummy tree root**
3. Make the **left subtree**, hosted by the **dummy tree root**, the node's new **left child**
4. Make the **right subtree**, hosted by the **dummy tree root**, the node's new **right child**

The diagram below shows:

1. The search path to a node with value **28** that we want to perform a splay operation on.
2. The contents of the dummy tree, right before we perform the final splay tree assembly. **-1** marks the dummy tree root. As you can see, **40** and **30** have been added to the **right subtree**, while **20** and **25** have been added to the **left subtree**.
3. The last visited node and its remaining children.

![Iterative Splaying 1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-iterative-03.png)

The next diagram shows the assembly process:

1. The children (**27** and **29**) of the last visited node (**28**) become, respectively, **rightmost child** of the **left subtree** and **leftmost child** of the **right subtree** hosted by the **dummy tree root**.
2. The **left subtree** and **right subtree** become the new children of the last visited node (**28**) which effectively results in our final assembled splay tree.

![Iterative Splaying 1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-iterative-04.png)

**Recursive or Iterative?**

The [original paper](https://www.cs.cmu.edu/~sleator/papers/self-adjusting.pdf) generally recommends using the top-down (iterative) approach. [splay.c](https://github.com/mbezhanov/c-data-structures-and-algorithms/blob/master/trees/splay/splay.c) presents both implementations.

### Insertion

Splay the tree at the value you'd like to insert. This will effectively bring the node that will become the inorder predecessor / indorder successor of the new node, to the root of the tree.

Compare the value of the node at the tree root with the value of the new node that you'd like to insert. There are two possibilities:

**Case 1**: new node value > tree root value; root's right child becomes new node's right child, root becomes new node's left child, new node becomes tree root;

![Splay Tree Insertion Case 1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-insert-01.png)

**Case 2**: new node value < tree root value; root's left child becomes new node's left child, root becomes new node's right child, new node becomes tree root;

![Splay Tree Insertion Case 2](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-insert-02.png)

### Deletion

Splay the tree at the value you'd like to remove. If a node with such value exists, it will appear at the tree root. If it does, evaluate the value of its left child. There are two possibilities:

**Case 1**: left child is NULL; make the node for deletion's right child the tree root, then delete the node;

![Splay Tree Deletion Case 1](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-delete-01.png)

**Case 2**: left child is not NULL; splay the tree at the node for deletion's left child value (that way the node for deletion will become right child of the tree root), then make the node for deletion's right child to be right child of the tree root, and finally remove the node;

![Splay Tree Deletion Case 2](https://raw.githubusercontent.com/mbezhanov/c-data-structures-and-algorithms/master/trees/splay/images/splay-delete-02.png)

### Search

Splay the tree at the value you're looking for. If the value exists in the tree, it will be placed at the root of the tree by the splay operation. If the tree root is NOT equal to the value you're looking for, this means the value is not in the tree.

## Further reading

* https://www.cs.cmu.edu/~sleator/papers/self-adjusting.pdf
* https://www.link.cs.cmu.edu/link/ftp-site/splaying/top-down-splay.c
