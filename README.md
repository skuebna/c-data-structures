# c-data-structures
Data Structures C/C++

# AVL GENERAL INFORMATION
    AVL stands for Georgy Adelson-Velsky and Landis' tree (named after inventors)
    The height of a node is the length of the longest downward path to a leaf from that node.
    The height of the root is the height of the tree.
    The depth of a node is the length of the path to its root.
    It is a self-balancing binary search tree.
    The heights of the two child subtrees of any node differ by at most one;
    if at any time they differ by more than one, rebalancing is done to restore this property.

# AVL BENEFITS
    The number of comparisons required is guaranteed never to exceed log(n).
    
# AVL PROJECT REQUIREMENTS
    Populate a tree via a text file (input.txt)
    After every insert, the tree must be balanced.
    At the end, display the tree in level format.
    Make sure to include the height and the balance factor of every node in your output.
    Redirect the display to  an output file (output.txt)

# TO COMPILE & RUN IT
    create an input.txt file with numbers (on Windows for now)
    in your terminal,    g++ -Wall avl.cpp -o avl
    run the program,     ./avl
    check for output in the output.txt file
    see the uploaded example and explanation.txt file for additional information
