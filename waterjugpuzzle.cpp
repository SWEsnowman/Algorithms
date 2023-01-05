/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Olof Persson and Frank Barton
 * Date        : 10/22/2022
 * Description : Finds a solution to the water jug problem if a solution exists
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

/**
 * Struct to keep track of fill values, directions, and parent states.
*/
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // Constructor to create 2D array of State structs
    State() {
        a = -1;
        b = 0;
        c = 0;
        directions = "";
        parent = NULL;
    }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

/**
 * Check if a new state is possible, given the gallons in source, 
 * gallons in target, and size of target.
*/
bool ifpossible(int source, int target, int targetSize){
    // Return false if target is full or source is empty
    if(target == targetSize || source == 0)
        return false;
    return true;
}

/**
 * Given parameters gallons in source, gallons in target,
 * and targetSize, return an array {new gallons in source, 
 * new gallons in target, gallons transfered};
*/
int* newQuants(int source, int target, int targetSize) {
    // Set space = empty space in target
    int space = targetSize - target;
    int* retArr = new int[3];
    // Condition if gallons in source less than empty space in target
    if (source < space) {
        retArr[0] = 0;
        retArr[1] = target + source;
        retArr[2] = source;
    // Condition if gallons in source is greater than empty space in target
    } else {
        retArr[0] = source - space;
        retArr[1] = targetSize;
        retArr[2] = space;
    }
    return retArr;
}

vector<State> water_jug_bfs(int sizea, int sizeb, int sizec, int goala, int goalb, int goalc){
    vector<State> direction;
    State start(0,0,sizec, "Initial state.");
    State goal(goala,goalb,goalc, "Final state.");
    queue<State> states;
    states.push(start);

    // Initialize 2D array array of states (array of pointers to arrays of states) track visited states
    State **seenStates = new State*[sizea+1];
    // Set each pointer in seenStates = new array of States
    for(int i = 0; i < sizea + 1; i++) {
        seenStates[i] = new State[sizeb+1];
    }

    // while (queue not empty)
    while(!states.empty()) {
        State current = states.front();
        states.pop();
        int a = current.a;
        int b = current.b;
        int c = current.c;

        // return backtracked solution if current == goal_state
        if ((a == goal.a) && (b == goal.b)) {
            // Iterate through all States with a parent
            while (current.parent != nullptr) {
                // Add each state to begining of direction queue (reverses order to chronological)
                direction.insert(direction.begin(), 1, current);
                // Update current to previous State
                current = *current.parent;
            }
            // Add initial State
            direction.insert(direction.begin(), 1, current);
            break;
        }
        
        // Continue loop of current state already seen
        if (seenStates[a][b].a != -1) {
            continue;
        }
        // Otherwise, mark current as seen
        seenStates[a][b] = current;

        // Add all 6 possible new states to queue:

        // Check if new State is possible
        if(ifpossible(c,a,sizea)) {
            // Set quants = newQuants values
            int* quants = newQuants(c, a, sizea);

            // Change verbage based on how many gallon(s) are poured
            if(quants[2] == 1){
                // Create newState based on quants
                State newState(quants[1] , b, quants[0], ("Pour " + to_string(quants[2]) + " gallon from C to A."));
                // Delete dynamically-created quants array
                delete [] quants;
                // Set parent property = State stored in seenStates array at indices a & b
                newState.parent = &seenStates[a][b];
                // Push newState to queue
                states.push(newState);
            }else{
                State newState(quants[1] , b, quants[0], ("Pour " + to_string(quants[2]) + " gallons from C to A."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }
            
        }

        if(ifpossible(b, a, sizea)){
            int* quants = newQuants(b, a, sizea);
            if(quants[2] == 1){
                State newState(quants[1], quants[0], c, ("Pour " + to_string(quants[2]) + " gallon from B to A."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }else{
                State newState(quants[1], quants[0], c, ("Pour " + to_string(quants[2]) + " gallons from B to A."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }
        }

        if(ifpossible(c, b, sizeb)){
            int* quants = newQuants(c, b, sizeb);
            if(quants[2] == 1){
                State newState(a, quants[1], quants[0], ("Pour " + to_string(quants[2]) + " gallon from C to B."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }else{
                State newState(a, quants[1], quants[0], ("Pour " + to_string(quants[2]) + " gallons from C to B."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }
        }

        if(ifpossible(a, b, sizeb)){
            int* quants = newQuants(a, b, sizeb);
            if(quants[2] == 1){
                State newState(quants[0], quants[1], c, ("Pour " + to_string(quants[2]) + " gallon from A to B."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }else{
                State newState(quants[0], quants[1], c, ("Pour " + to_string(quants[2]) + " gallons from A to B."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }
        }

        if(ifpossible(b, c, sizec)){
            int* quants = newQuants(b, c, sizec);
            if(quants[2] == 1){
                State newState(a, quants[0], quants[1], ("Pour " + to_string(quants[2]) + " gallon from B to C."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }else{
                State newState(a, quants[0], quants[1], ("Pour " + to_string(quants[2]) + " gallons from B to C."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }
        }

        if(ifpossible(a, c, sizec)){
            int* quants = newQuants(a, c, sizec);
            if(quants[2] == 1){
                State newState(quants[0], b, quants[1], ("Pour " + to_string(quants[2]) + " gallon from A to C."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }else{
                State newState(quants[0], b, quants[1], ("Pour " + to_string(quants[2]) + " gallons from A to C."));
                delete [] quants;
                newState.parent = &seenStates[a][b];
                states.push(newState);
            }
        }
    }

    // Delete each row first
    for(int i = 0; i < sizea+1; i++) {
        delete [] seenStates[i];
    }
    // Delete the array itself
    delete [] seenStates;

    // Return vector after iterating through all combos (empty vector if no combos found)
    return direction;
}

int main(int argc, char * const argv[]){
    istringstream iss;
    int sizeA, sizeB, sizeC, goalA, goalB, goalC;
    // Check that 6 arguments are given
    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
        return 1;
    }
    // Check that all arguments are valid integer inputs:
    iss.str(argv[1]);
    if(!(iss >> sizeA) || sizeA <= 0){
        cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A.";
        return 1;
    }
    iss.clear();
    iss.str(argv[2]);
    if(!(iss >> sizeB) || sizeB <= 0){
        cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B.";
        return 1;
    }
    iss.clear();
    iss.str(argv[3]);
    if(!(iss >> sizeC) || sizeC <= 0){
        cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C.";
        return 1;
    }
    iss.clear();
    iss.str(argv[4]);
    if(!(iss >> goalA) || goalA < 0){
        cerr << "Error: Invalid goal '" << argv[4] << "' for jug A.";
        return 1;
    }
    iss.clear();
    iss.str(argv[5]);
    if(!(iss >> goalB) || goalB < 0){
        cerr << "Error: Invalid goal '" << argv[5] << "' for jug B.";
        return 1;
    }
    iss.clear();
    iss.str(argv[6]);
    if(!(iss >> goalC) || goalC < 0){
        cerr << "Error: Invalid goal '" << argv[6] << "' for jug C.";
        return 1;
    }
    // Check that goals are <= sizes
    if(goalA > sizeA){
        cerr << "Error: Goal cannot exceed capacity of jug A.";
        return 1;
    }else if(goalB > sizeB){
        cerr << "Error: Goal cannot exceed capacity of jug B.";
        return 1;
    }else if(goalC > sizeC){
        cerr << "Error: Goal cannot exceed capacity of jug C.";
        return 1;
    }
    // Check that total gallons in goal = capacity of C (total gallons given)
    if(sizeC != goalA+goalB+goalC){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return 1;
    }

    // If no tests fail, run water_jug_bfs
    vector<State> directions = water_jug_bfs(sizeA, sizeB, sizeC, goalA, goalB, goalC);
    
    // Check if vector is empty
    if (directions.size() == 0) {
        cout << "No solution." << endl;
    }

    // Otherwise print all directions and states
    for(auto &state : directions) {
        cout << state.directions << " " << state.to_string() << endl;
    }

    return 0;
}