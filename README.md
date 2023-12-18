# CS300
Portfolio Item for SNHU CS 300.

This program parses a csv file containing a course’s ID, course title, and prerequisites, then sorts all courses alphanumerically by course ID. 

I took multiple factors into consideration when developing this file.  I decided to implement a vector data structure with a quicksort algorithm over a binary search tree to work with the data provided.  I chose the vector data structure over a binary search tree for two reasons.  Considering the relatively small size of the input data I was working with (around 150 courses), a vector is both simple and effective. Were this program to scale, I would consider implementing a binary search tree as BSTs are inherently sorted. However, I would take additional measures to ensure that the BST is balanced.

Ultimately, I developed an understanding of the importance of choosing the correct data structure while designing software. One must consider many factors - the size of the data, which operations will be performed on the data, and scalability amongst other things.
