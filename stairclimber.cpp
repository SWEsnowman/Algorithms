/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Olof Persson
 * Date        : 10/8/2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    if(num_stairs == 0){
        //base case of recursion 
        vector<vector<int>> hello = {{}};
        return hello;
    }
    vector<vector<int>> ways;
    for(int i = 1; i < 4; i++){
        if(num_stairs >= i){
            vector<vector<int>> result;
            //recursive call to get_ways with a lesser num_stairs 
            result = get_ways(num_stairs-i);
            //prepends i to result
            for(int j = 0; j < int(result.size()); j++){
                result[j].insert(result[j].begin(),i);
            }
            //adds result to ways
            for(int i = 0; i< int(result.size()); i++){
                ways.push_back(result[i]);
            }
        }
    }
    return ways;
}
//finds the number of digits a number has
int num_digits(int num){
    int temp = num;
    int count = 0;
    while(temp != 0){
        temp = temp / int(10);
        count++;
    }
    return count;
}
void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    
    // makes it singular if ways is only one vector long
    if(ways.size() == 1){
        cout << ways.size() << " way to climb " << ways[0].size() << " stair." << endl;
    }else{
        cout << ways.size() << " ways to climb " << ways[0].size() << " stairs." << endl;
    }
    int digit = num_digits(ways.size());
    for(int i = 0; i < int(ways.size()); i++){
        //makes the all the first numbers the same size in print out and does this dynamically
        //using num_digits
        cout << setw(digit) << i+1;
        cout << ". [" << ways[i][0];

        for(int j = 1; j < int(ways[i].size()); j++){
            cout << ", " << ways[i][j];
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    int argument;
    istringstream iss;
    //checks if the arguments the allowed type and number 
    if (argc != 2){
        cerr << "Usage: ./stairclimber <number of stairs>";
        return 1;
    }
    iss.str(argv[1]);
    if(!(iss >> argument)){
        cerr << "Error: Number of stairs must be a positive integer.";
        return 1;
    }
    if(argument <= 0){
        cerr << "Error: Number of stairs must be a positive integer.";
        return 1;
    }
    display_ways(get_ways(argument));
}
