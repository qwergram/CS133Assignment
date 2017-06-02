# AVL-Tree

## [Instructions](http://faculty.edcc.edu//paul.bladek/CS133/p3.htm)
[`AVL<T>`](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html) Trees, as explained in class, are a roughly-balanced form of binary trees. The version you need to write and test should be **publicly** inherited from the [`BST<T>`](https://github.com/qwergram/AVL-Tree/blob/master/AVLTree/bst.h) class as presented in class--with one exception. Before inheriting, make a quick change to `BST` so that inserting will not allow duplicates; that is, make insert a `bool` method. On insert, if the data is equal to the data in the node, insert should return a `false`, and insert nothing.

You may *(and should)* use the starting files provided on this boilerplate.  These files include the **necessary** binary search tree definition along with the start of the avl class. You will need to write your own test driver. 

You may want to test your program using the [AVL simulation](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html) available on the web.

html In general, you will need to override the definitions of a number of the inherited `BST<T>` methods. You should also add in the following protected or private methods *(as described in class)*:

- `node<T>* rotateRight(node<T> *nodeN);`
- `node<T>* rotateLeft(node<T> *nodeN);`
- `node<T>* rotateRightLeft(node<T> *nodeN);`
- `node<T>* rotateLeftRight(node<T> *nodeN);`
- `node<T>* rebalance(node<T> *&nodeN);`
- `int getHeightDifference(const node<T> *const nodeN)const;`

## Boilerplate Contents

Download this project as a zip [here](https://github.com/qwergram/AVL-Tree/archive/master.zip).
Alternatively, you can clone with `git clone https://github.com/qwergram/AVL-Tree.git` if you are familiar with
github.

<table>
<tr>
    <th>File Name</th>
    <th>Source</th>
</tr>
<tr>
    <td><code>bst.h</code></td>
    <td><a href="https://github.com/qwergram/AVL-Tree/blob/master/AVLTree/bst.h">Source</a></td>
</tr>
<tr>
    <td><code>bstDriver.cpp</code></td>
    <td><a href="https://github.com/qwergram/AVL-Tree/blob/master/AVLTree/bstDriver.cpp">Source</a></td>
</tr>
<tr>
    <td><code>bsttests.cpp</code></td>
    <td><a href="https://github.com/qwergram/AVL-Tree/blob/master/AVLTests/bsttests.cpp">Source</a></td>
</tr>
</table>

This boilerplate comes with unit tests. You do have the ability to remove the testing framework if you choose to by using the [`notests` branch](https://github.com/qwergram/AVL-Tree/tree/notests).
