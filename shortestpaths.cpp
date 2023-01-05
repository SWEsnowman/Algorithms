/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Olof Persson and Jesse Knuckles
 * Version     : 1.0
 * Date        : 12/7/2022
 * Description : Code for Floyd's Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;
//as the name suggests checks the rest of the errors not checked in the main function
bool error_handling(string const s, int const range, int const num) {
    string j = to_string(range);
    if (range < 1) {
        cerr << "Error: Invalid number of vertices '" << j << "' on line 1." << endl;
        return false;
    }
    else if (range > 26) {
        cerr << "Error: Invalid number of vertices '" << j << "' on line 1." << endl;
        return false;
    }
    string err = "";
    if (num != 1) {
        //cout << s.length();
        if (s.length() < 5) {
            
            if (s.length() == 3) {
                cerr << "Error: Invalid edge data '" << s[0] << " " << s[2] << "' on line "<< to_string(num) << "." << endl;
                return false;
            }
        }
        if (s.length() > 5) {
            string sub = "";
            if (int(s[1]) != 32){
                int i = 0;
                while (int(s[i]) != 32) {
                    sub += s[i];
                    i++;
                }
            err += char(range + 64);
            cerr << "Error: Starting vertex '" << sub << "' on line " << to_string(num) << " is not among valid values A-" << err << "." << endl;
            return false;
            }
            else if (int(s[3]) != 32) {
                int i = 2;
                while (int(s[i]) != 32) {
                    sub += s[i];
                    i++;
                }
            err += char(range + 64);
            cerr << "Error: Ending vertex '" << sub << "' on line " << to_string(num) << " is not among valid values A-" << err << "." << endl;
            return false;
            }
        }
        if ((int(s[0]) - 64) > range || (int(s[0]) - 64) < 0) {
            err += char(range + 64);
            cerr << "Error: Starting vertex '" << s[0] << "' on line " << to_string(num) << " is not among valid values A-" << err << "." << endl;
            return false;
        }
        else if ((int(s[2]) - 64) > range || (int(s[2]) - 64) < 0) {
            err += char(range + 64);
            cerr << "Error: Ending vertex '" << s[2] << "' on line " << to_string(num) << " is not among valid values A-" << err << "." << endl;
            return false;
        }
        else if (int(s[4]) <= 48 || int(s[4]) > 57) {
            string err = "";
            for(int i = 4; i < int(s.length()); i++){
                err += s[i];
            }
            cerr << "Error: Invalid edge weight '" << err << "' on line " << to_string(num) << "." << endl;
            return false;
        }
    }
    return true;
}
//adds the new edge to the distance matrix Dmatrix every time a new line is read from the file
long update_matrix(long** matrix, string const s, long max) {
    int one = int(s[0]) - 65;
    int two = int(s[2]) - 65;
    long d = 0;
    for (int i = 4; i < int(s.length()); i++) {
        d = d * 10;
        d += (int(s[i]) - 48);
    }
    matrix[one][two] = d;
    if(d > max){
        return d;
    }else{
        return max;
    }
} 

//prints out the original direct paths in a matrix
void print_distance_matrix(long** matrix, int range, long max) {
    cout << "Distance matrix:" << endl;
    cout << " ";
    string s;
    int test = range;
    int numdigits = floor(log10(max))+1;
    for (int i = 0; i < test; i++) {
        s = "";
        s += char(i+65);
        cout << " ";
        cout << setw(numdigits) << s;
    }
    cout << endl;
    for (int i = 0; i < test; i++) {
        s = "";
        s += char(i+65);
        cout << s;
        for (int j = 0; j < test; j++) {
            if (matrix[i][j] == -1) {
                cout << " ";
                cout << setw(numdigits) << '-';
            }
            else {
                cout << " ";
                cout << setw(numdigits) << to_string(matrix[i][j]);
            }
        }
        cout << endl;
    }
    cout << endl;
} 
//creates the intermediate matrix and also updates the distance matrix to show all the of the shortest paths
void create_other_matricies(long** Dmatrix, char** Imatrix, int range) {
    for(int z = 0; z < range; z++) {
        for (int i = 0; i < range; i++) {
            for (int j = 0; j < range; j++) {
                if ((j != z) && (i != z) && (Dmatrix[z][j] != -1) && (Dmatrix[i][z] != -1)) {
                long update = Dmatrix[z][j] + Dmatrix[i][z];
                   if (Dmatrix[i][j] == -1) {
                    Dmatrix[i][j] = update;
                    Imatrix[i][j] = char(z+65);
                   }
                   else {
                    if (Dmatrix[i][j] > update) {
                        Imatrix[i][j] = char(z+65);
                    }
                    Dmatrix[i][j] = min(Dmatrix[i][j],update);
                   }
                }
            }
        }
    }
}
// prints out the path lengths matrix which is the distance matrix Dmatrix after being
// updated from create_other_matrices function
void print_path_lengths(long** matrix, int range) {
    cout << "Path lengths:" << endl;
    cout << " ";
    string s;
    int test = range;
    long max = 0;
    for(int i = 0; i < test; i++){
        for(int j = 0; j < test; j++){
            if(matrix[i][j] > max){
                max = matrix[i][j];
            }
        }
    }
    int numdigits = floor(log10(max))+1;
    for (int i = 0; i < test; i++) {
        s = "";
        s += char(i+65);
        cout << " " << setw(numdigits) << s;
    }
    cout << endl;
    for (int i = 0; i < test; i++) {
        s = "";
        s += char(i+65);
        cout << s;
        for (int j = 0; j < test; j++) {
            if (matrix[i][j] == -1) {
                cout << " " << setw(numdigits) <<"-";
            }
            else {
            cout << " " << setw(numdigits) << to_string(matrix[i][j]);
            }
        }
        cout << endl;
    }
    cout << endl;
}
//prints out the matrix of intermediate vertices
void print_intermediate(char** matrix, int range) {
    cout << "Intermediate vertices:" << endl;
    cout << " ";
    string s;
    int test = range;
    for (int i = 0; i < test; i++) {
        s = "";
        s += char(i+65);
        cout << " " << s;
    }
    cout << endl;
    for (int i = 0; i < test; i++) {
        s = "";
        s += char(i+65);
        cout << s;
        for (int j = 0; j < test; j++) {
            s = "";
            s += matrix[i][j];
            cout << " " << s;
        }
        cout << endl;
    }
    cout << endl;
}
//recursively finds the path between two specific vertices
string path(int start, int finish, char** Imatrix, long** Dmatrix) {
    string s;
    if (start == finish) {
        s = "";
        s += char(start + 65);
        return s;
    }
    if (Imatrix[start][finish] == '-') {
        if(Dmatrix[start][finish] != -1){
            s = "";
            s += char(start+65);
            s += " -> ";
            s += char(finish + 65);

        }else{
            return "none";
        }
        return s;
    }
    else {
        if(Dmatrix[start][finish] == -1){
            return "none";
        }
        return path(start, int(Imatrix[start][finish])-65, Imatrix, Dmatrix) + path(int(Imatrix[start][finish])-65, finish, Imatrix, Dmatrix);
    }
}
//prints out the paths of all of the vertices
void print_final(long** Dmatrix, char** Imatrix, int range) {
    string s;
    char p;
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {
            s = "";
            s += char(i + 65);
            cout << s << " -> ";
            s = "";
            s+= char(j + 65);
            if(Dmatrix[i][j] == -1){
                cout << s << ", distance: infinity, path: " << path(i, j, Imatrix, Dmatrix) << endl;
            }else{
                string f = path(i, j, Imatrix, Dmatrix);
                string r = "";
                p = '2';
                for (size_t i =0; i < f.length(); i++) {
                    if (f[i] != p) {
                        r += f[i];
                    }
                    p = f[i];
                }
                cout << s << ", distance: " << to_string(Dmatrix[i][j]) << ", path: " << r << endl;
            }
            
        }
    }
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    int range = 0;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/

        
        int validinput;
        getline(input_file, line);
        istringstream iss(line);
        if(!(iss >> validinput)){
            cerr << "Error: Invalid number of vertices '" << line << "' on line 1.";
            return -1;
        }
        for (int i = 0; i < int(line.length()); i++) {
            range = range * 10;
            range += (int(line[i]) - 48);
        }

        long** Dmatrix;
        char** Imatrix;
        Dmatrix = new long*[range];
        for (int i = 0; i < range; i++) {
            Dmatrix[i] = new long[range];
            fill_n(Dmatrix[i],range, -1);
            Dmatrix[i][i] = 0;
        }
        Imatrix = new char*[range];
        for (int i = 0; i < range; i++) {
            Imatrix[i] = new char[range];
            fill_n(Imatrix[i],range, '-');
            //Imatrix[i][i] = '0';
        }
        line_number++;
        long max = 0;
        while (getline(input_file, line)) {
            //cout << line_number << ":\t" << line << endl;
            
            bool temp = error_handling(line, range, line_number);
            if(!temp){
                for (int i = 0; i < range; i++) {
                    delete[] Dmatrix[i];
                    delete[] Imatrix[i];
                }   
                delete[] Dmatrix;
                delete[] Imatrix;
                return 1;
            }
            long tempmax = update_matrix(Dmatrix, line, max);
            max = tempmax;
            ++line_number;

        }
        print_distance_matrix(Dmatrix, range, max);
        create_other_matricies(Dmatrix, Imatrix,range);
        print_path_lengths(Dmatrix, range);
        print_intermediate(Imatrix, range);
        print_final(Dmatrix, Imatrix, range);
        // Don't forget to close the file.
        for (int i = 0; i < range; i++) {
            delete[] Dmatrix[i];
            delete[] Imatrix[i];
        }
        delete[] Dmatrix;
        delete[] Imatrix;
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}