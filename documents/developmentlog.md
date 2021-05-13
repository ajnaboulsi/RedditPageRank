# CS 225 Data Structures

## Development Log (rohitc2-ssohai20-adamjn3-nconner2)

**Week 1:** In week 1, we first preprocessed the data using a Python script. We also started setting up the graph structure. We created a graph.h file and graph.cpp file, which contain several variables and functions that we will be using in our project. Next, we implemented some functions that were necessary for the PageRank algorithm. We then implemented PageRank, which we use to rank the subreddits in our dataset by popularity. Next, we implemented mergesort, which sorts the data in pairs containing the subreddit and its popularity. Then we deleted mergesort, as we realized we don't need it. We also created a Makefile to help compile our program and make it easier to run. We then added some coloring to make the output text more aesthetically pleasing. Finally, we started working on the force directed graph structure.
    Contributors: Adam Naboulsi, Rohit Chalamala, Noah Conner, Sophia Sohail

**Week 2:** In week 2, we first implemented spring embedder, which is one of the force directed graph algorithms we are using. We also added some files from the PNG class that we will use to create a visual of our graph. We then implemented BFS traversal, which we are trying to debug so it works as intended. We are also working on trying to implement the GRIP algorithm because it is much faster than the spring embedder. We also added a function called "printRank" to our graph which prints out the rank of the input subreddit, or prints "subreddit not found!" if the input does not exist. This function also has a "wild card" feature.
    Contributors: Adam Naboulsi, Rohit Chalamala, Noah Conner, Sophia Sohail

**Week 3:** Since we have the majority of our project done already, we did not have much work left to do in week 3. This week, we focused on debugging our BFS. Our BFS traversal size was larger than the size of the unordered map which stores the vertices (subreddits), so we were trying to fix this issue. We think we may have found a potential cause for the error; it might be coming from one of the constructors. Unfortunately we have not yet figured out how to fix this issue, so we will continue working on it into week 4. We also started working on the final presentation slides this week. 
    Contributors: Adam Naboulsi, Rohit Chalamala, Noah Conner, Sophia Sohail

**Week 4:** The first thing we did in week 4 is fix our BFS traversal. It now traverses the correct number of vertices. Then we decided not to implement the GRIP algorithm anymore since spring embedder accomplishes the same goal. We used spring embedder to create a gif represenation of our graph. We also added comments to most of our functions so that they are easier to understand. We tried to add some test cases but something went wrong in the Makefile so our code is not compiling anymore. We will definitely fix this error before the deadline. Other than that, the bulk of our project is complete. All we need to do is update the README and finish the presentation.
    Contributors: Adam Naboulsi, Rohit Chalamala, Noah Conner, Sophia Sohail

**Week 5:** Fixed some bugs and recorded the final project presentation.
    Contributors: Adam Naboulsi, Rohit Chalamala, Noah Conner, Sophia Sohail