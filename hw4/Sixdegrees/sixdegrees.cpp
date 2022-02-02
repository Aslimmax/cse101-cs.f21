/**
 * Filename: sixdegrees.cpp
 * 
 * This is the main file for the assignment detailed in 
 * bfs_six_degrees.pdf
 * 
 * After running make, the usage is
 *     ./sixdegrees <INPUT_FILE> <OUTPUT_FILE>
 * 
 * Input: Each line of INPUT_FILE should contain two actors (<ACTOR1> <ACTOR2>)
 * Output: Each line of OUTPUT_FILE should contain a shortest path between
 * the two actors from INPUT_FILE, or an error message
 * 
 * Look at the associated pdf (bfs_six_degrees.pdf) in the root
 * directory for more details.
 * 
 * Andrew Lim, November 2021
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <string>
#include <list>
#include <iterator>
#include <queue>
#include <tuple>
#include <set>
#include <unordered_map>
using namespace std;


// Custom class to keep track of movies and their actors
class Movie {
    private:
        string movieTitle; // title of the movie
        set<string> actors; // set of actors in the movie
        int id; // unique id to differentiate duplicate movie titles
    
    public:
        // Maintain a counter to make every Movie object unique
        static int uniqueCounter;
    
        // Default constructor
        Movie() {
            id = uniqueCounter;
            // Increment every time a new Movie object is created
            uniqueCounter++;
        }
    
        // Overloaded constructor
        Movie(string movieTitle_, set<string> actors_, int id_) {
            movieTitle = movieTitle_;
            actors = actors_;
            id = id_;
        }
        
        // Member accessors
        string getMovieTitle() { return movieTitle; }
        set<string> getActors() { return actors; }
        int getID() { return id; }
    
        // Member mutators
        void setMovieTitle(string movieTitle_) { movieTitle = movieTitle_; }
        void setActors(set<string> actors_) { actors = actors_; }
        void insertActor(string actor) { actors.insert(actor); }
        void setID(int id_) { id = id_; }
};

// Custom class to keep track of a movie, actor, and id of a related actor.
// This class is used heavily in the creation of the graph that stores
// actors (vertices) and their related movies (edges).
class ActorNode {
    private:
        string movieTitle;
        string actor;
        int movieID;
    
    public:
        // Overloaded constructor
        ActorNode(string movieTitle_, string actor_, int movieID_) {
            movieTitle = movieTitle_;
            actor = actor_;
            movieID = movieID_;
        }
        
        // Member accessors
        string getMovieTitle() { return movieTitle; }
        string getActor() { return actor; }
        int getID() { return movieID; }
    
        // Member mutators
        void setMovieTitle(string movieTitle_) { movieTitle = movieTitle_; }
        void setActors(string actor_) { actor = actor_; }
        void setID(int movieID_) { movieID = movieID_; }
};

// Iniitalize Movie's static unique counter
int Movie::uniqueCounter = 0;

/*
 * unordered_map<string, tuple<string, string, int>>
 * BFS(string, sourceActor, string destinationActor,
 * unordered_map<string, list<ActorNode>> &graph)
 * Perform a BFS from a sourceActor to a destinationActor (essentially
 * determine the shortest path between any two actors)
 * Input: string sourceActor, string destinationActor, unordered_map &graph
 * Output: pred unordered_map<string, tuple<string, string, int>>
 */
unordered_map<string, tuple<string, string, int>> 
    BFS(string sourceActor, string destinationActor, 
         unordered_map<string, list<ActorNode>> &graph) {
    queue<string> actors; // initialize a queue with actor
    actors.push(sourceActor);
    // Iniitalize an unordered_map pred to store the predecessor actor
    // of another actor
    // <actor, tuple<parent actor, movie, id>
    unordered_map<string, tuple<string, string, int>> pred;
    // Initialize an unordered_map visited to track of which actors have already been
    // visisted
    // <actor, visited>
    unordered_map<string, bool> visited;
    
    // Main driver for BFS
    while (!actors.empty()) {
        string currActor = actors.front(); // get the next actor in the list to traverse
        actors.pop(); // remove the oldest actor
        list<ActorNode> tempList = graph[currActor]; // Store list of actors indexed in graph
        // Traverse list of related actors set in graph
        for(auto relatedActor: graph[currActor]) {
            // Get the related actor
            string actor = relatedActor.getActor();
            // Determine if visited[actor] is set
            unordered_map<string, bool>::iterator visIter = visited.find(actor);
            // Check if visited[actor] exists, if it doesn't, it hasn't been
            // visited yet
            if (visIter == visited.end()) { 
                visited[actor] = true; // set visited[actor] to true
                // Initialize a tempTuple to store information about the
                // predecessor for the current actor
                tuple <string, string, int> predActor;
                predActor = make_tuple(currActor, relatedActor.getMovieTitle(),
                                       relatedActor.getID());
                pred[actor] = predActor; // set pred[actor] to predActor tuple
                // Check if actor is the desinationActor
                if (actor == destinationActor) {
                    break;
                }
                actors.push(actor); // push actor into queue
            }
        }
    }
    
    return pred;
}

/*
 * Main function
 * 1. Create an actorGraph
 * 2. Read input from a file
 * 3. Perform BFS on actorGraph for each line in the input file
 * 4. Write the shortest path (or any errors) to an output file
 */
int main(int argc, char** argv) {
    if (argc < 3) { // Must provide two arguments as input
        throw std::invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE>"); // throw error
    }
    
    ifstream input; // stream for input file
    ofstream output; // stream for output file
    
    // Initialize a list to store a list of Movie's (each object will
    // contain a movie, a set of actors, and a unique movie id)
    list<Movie> movieList;
    // Initialize a graph (mimics an adjacency list) to store the names
    // of actors and related actors (based on whether they shared a movie
    // or not)
    unordered_map<string, list<ActorNode>> actorGraph;
    
    /**
     * Parse through cleaned_movielist and create a map of sets. The key will be
     * a movie, and its value will be a set of actors
     */
    ifstream imdbStream("cleaned_movielist.txt"); // stream of IMDB data
    string line = ""; // store the text in the current line
    // Iterate through each line of claned_movielist.txt
    while(getline(imdbStream, line)) {
        istringstream ss(line); // initialize istringstream obj for parsing
        int movieCounter = 0; // track the location of the movie in the line
        string movie = ""; // store the movie of the current line
        string word = ""; // store the string val
        
        // Initailize a Movie object to store a movie title and its actors
        Movie tempMov;
        while(getline(ss, word, ' ')) {
            // Insert the movie into movieMap
            if (movieCounter == 0) {
                tempMov.setMovieTitle(word);
                // Movie has been added, so increment counter to parse actors
                movieCounter++;
            } else {
                // Insert the actor into the specified movie
                tempMov.insertActor(word);
            }
        }
        
        // Insert tempMov into movieList
        movieList.push_back(tempMov);
    }
    
    /**
     * Create a graph that shows the connections between actors (vertices) and
     * movies (edges)
     */
    // Parse list of movies
    for(list<Movie>::iterator listIter = movieList.begin(); listIter != movieList.end();
           ++listIter) {
        // Parse set of actors for each movie
        set<string> tempActors = listIter->getActors();
        for(set<string>::iterator setIter = tempActors.begin();
               setIter != tempActors.end(); ++setIter) {

            // Check if the particular actor does not have any actors in its list
            if (actorGraph.find(*setIter) == actorGraph.end()) {
                // Initailize an empty list
                list<ActorNode> actor;
                // Create an entry in actorGraph for the actor with an empty list
                actorGraph[*setIter] = actor;
            }
            
            // Store the list of actors in the current movie
            set<string> listOfActors = listIter->getActors();
            
            // Parse through each actor in listOfActors
            for(set<string>::iterator actIter = listOfActors.begin();
                   actIter != listOfActors.end(); ++actIter) {
                // Check if the current actor is the same as the parent actor
                if (*actIter != *setIter) {
                     // Initialize a tempMov object (will acts as an edge for the current actor)
                    ActorNode tempActor(listIter->getMovieTitle(), *actIter,
                                        listIter->getID());  
                    // Insert tempMov with the current actor into actorGraph
                    actorGraph[*setIter].push_back(tempActor);                    
                }

            }
        }
    }
    
    /**
     * Parse input files and write the shortest path (if there is one) to the output file
     */
    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file
    
    // Parse through input file and look for the shortest path between the
    // two actors
    string actor1 = ""; 
    string actor2 = "";
    while (input >> actor1 >> actor2) {   
        // Determine if actor1 and actor2 are present in the data
        if (actorGraph.find(actor1) == actorGraph.end() 
            || actorGraph.find(actor2) == actorGraph.end()) {
            output << "Not present" << endl;
            continue;
        }
        
        // Determine if actor1 == actor2
        if (actor1 == actor2) {
            output << actor1 << endl;
            continue;
        }
        
        // Perform BFS from actor1 to actor2
        // tuple<string actor, string movie, int movieID>
        unordered_map<string, tuple<string, string, int>> pred = 
            BFS(actor1, actor2, actorGraph);
        
        // Determine if pred[actor2] has a value
        if (pred.find(actor2) == pred.end()) {
            output << "Not present" << endl;
            continue;
        }
        
        // Initialize vector to store the vertices and edges of the shortest
        // path
        vector<pair<string, string>> shortestPath;
        
        // Store the name of the actor in each traversal up pred. Initially starts off
        // with actor2 (destinationActor)
        string tempActor = actor2;
        // Store the tuple of pred[tempActor]. Initially starts off with pred[actor2]
        tuple <string, string, int> tempTuple = pred[tempActor];
        // Store the path information from tempActor to pred[tempActor]
        pair<string, string> path(get<1>(tempTuple), actor2);
        // Initialize vector with actor2
        shortestPath.push_back(path);
        
        // Loop thorugh the shortestPath starting from actor2 (initailized above)
        // until we reach actor1
        while (true) {
            // Base case: have reached the source actor
            if (tempActor == actor1) {
                break;
            }
            
            // Initialize a pair to store edge (movie) and vertex (actor)
            pair<string, string> path(get<1>(tempTuple), get<0>(tempTuple));
            shortestPath.push_back(path);
            
            // Get the predecessor of the next actor
            tempActor = get<0>(tempTuple);
            tempTuple = pred[tempActor];
        }
        
        // Reverse the shortestPath vector to format to: source -> destination
        reverse(shortestPath.begin(), shortestPath.end());
        
        // Parse shortestPath and write the vertices and edges to the output file
        for(vector<pair<string, string>>::iterator vecIter = shortestPath.begin();
            vecIter != shortestPath.end(); ++vecIter) {
            // Output string containing the actor (vertex) and movie (edge)
            string outputStr = (*vecIter).second + " -(" + (*vecIter).first + ")- ";
            // Check if loop is on the destination actor
            if (vecIter == shortestPath.end() - 1) {
                outputStr = (*vecIter).second;
            }
            
            // Write to output file
            output << outputStr;
        }
        
        output << endl;
    }
    
    input.close(); // close input stream
    output.close(); // close output stream
    
    return 0;
}
