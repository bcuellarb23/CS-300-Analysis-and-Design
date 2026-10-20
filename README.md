# CS-300-Analysis-and-Design
This project is a course finder designed for the academic advisor team in the Computer Science department at ABCU. This software helps the advisors when talking with students and finding courses and their information.

In this project, three data structures were studied to determine which was the most appropriate application to solve advisors' requirements. The three data structures used in this project were:

## Vectors

Vectors are easy to implement and they require a quick setup; Vectors store data in the order it was received, so it requires an extra function that iterates over the data to organize it. This data structure is memory efficient because it does not store any pointers, and it does not need to make an organized copy of the vector; instead, it can be organized directly in memory. The designed data structure to store the courses had a running time of O(n^2).

## Hash Tables

Hash tables are the fastest data structure among the three we studied in this project; using hash keys might reduce search time to O(1). Deletion is easier, and it handles big data loads fast. It also requires a function that copies data into an organized map to print a sorted list due to the sorting method; hash tables scramble the data upon storage. It is not very memory efficient if a sorted list must be printed. However, I performed a running time of O(N). 

## Binary Search Tree (BST)

BSTs auto-sort data upon storage, making it easier to get sorted data when needed; they can grow and shrink as needed, and they also allow the use of recursion. However, its implementation is very complicated, and it has an expensive memory cost due to the use of pointers. BTS running time for a search was O(n log n). 



Hash tables were selected as a data structure for this project; this structure solves the advising department's needs of getting a fast and reliable software to get information of a course, handling fast searches for courses and printing a sorted list of the courses. 

 Understanding data structures is important because, by mastering them, a developer can approach a problem using the data structure that better fits their case. Choosing the right data structure can improve the reliability and running-time performance of an application, generating time-proof and scalable software. 

Documentation is always the best ally to solve roadblocks; most of these data structures are well documented. There are several websites and forums with relevant information about sorting any difficulty when implementing any of these data structures. 

Working on this project has improved my knoledge about the different approaches a problem can have, and how to choose an appropriate solution based on documented running times and memory efficiency. At this point, I would have chosen a different data structure that could solve the problem in a more efficient way.  

This code is maintainable, readable, and adaptable to any transformation; for example, if in the future a developer switches to a vector approach, the project ensures modularity, which makes it easy to implement different structures with minimal changes. 

