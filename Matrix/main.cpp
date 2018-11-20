//
//  main.cpp
//  Matrix
//
//  Created by Luke Clement on 18/11/2018.
//  Copyright © 2018 Luke Clement. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;


int main(int argc, const char * argv[]) {
    //Declaration of variables
    //File names
    string filename = "matrix.txt";
    string outputFile = "transpose.txt";
    string inv = "inverse.txt";
    //Files
    ifstream file(filename);
    ofstream output(outputFile);
    ofstream outputInv(inv);
    //Strings
    string line;
    string number;
    //Vectors
    vector < vector <double> > matrix;
    vector < vector <double> > inverse;
    vector < vector <double> > transpose;
    vector <double> row;
    vector <double> column;
    //Numbers to be used
    int start, end;
    double factor, n;
    
    /*
     Opening file
    */
    if(file.is_open()){
        //Opening file
        while(!file.eof()){
            //Getting line
            getline(file, line);
            //Start and end points of commas
            start = 0;
            end = 0;
            //Going through each line
            for(int i = 0; end != -1; i++){
                //Finding next comma
                end = (int)line.find(",", i);
                //Checking validity
                if(end - start > 0){
                    //Getting number and adding to row
                    number = line.substr(start, end - start);
                    row.push_back(atof(number.c_str()));
                    
                }else if(end == -1){
                    //Hit the end of the line
                    end = (int)line.length();
                    //Adding to row
                    number = line.substr(start, end-start);
                    row.push_back(atof(number.c_str()));
                    //Setting end to -1 to end loop
                    end = -1;
                }
                //Resetting start
                start = end + 1;
            }
            //Adding row to matrix and resetting row
            matrix.push_back(row);
            row.clear();
        }
    }else{
        //Error message
        cout << filename << " file didn't open!" << "\n";
        exit(1);
    }
    //Closing file
    file.close();
    
    /*
        Making transpose
    */
    //Going through matrix
    for(int i = 0; i < matrix[0].size(); i++){
        
        for(int j = 0; j < matrix.size(); j++){
            //Getting columns
            column.push_back(matrix[j][i]);
        }
        //Adding to transpose and clearing column
        transpose.push_back(column);
        column.clear();
    }
    
    /*
        Making inverse
    */
    
    //Checking it can be inversable
    bool valid=matrix.size() == matrix[0].size();
    if(valid){
        //Making identity matrix to start off inverse
        for(int i = 0; i < matrix.size(); i++){
            for (int j = 0; j < matrix[0].size(); j++){
                if(i == j){
                    row.push_back(1);
                }else{
                    row.push_back(0);
                }
            }
            //Making inverse
            inverse.push_back(row);
            row.clear();
        }
        
        //Setting constants
        factor = 0;
        n = 0;
        
        for(int i = 0; i < matrix[0].size() ;i++){
            
            //Making diagonal   1,a,b,c...      Showing what happens on first run for brevity
            //                  d,e,f,g...
            factor = matrix[i][i];
            for(int j = 0; j < matrix.size(); j++){
                //Changing matrix and inverse
                matrix[i][j] = matrix[i][j]/factor;
                inverse[i][j] = inverse[i][j]/factor;
            }
            //Zeroing the rest  1,a,b,c...
            //                  0,e,f,g...
            //                  0,x,y,z...
            for(int k = 0; k < matrix.size(); k++){
                if(k != i){
                    //Setting multiplication constant
                    n = matrix[k][i];
                    for(int j = 0; j < matrix.size(); j++){
                        //Changing matrix and inverse to reflect that
                        matrix[k][j] = matrix[k][j] - matrix[i][j]*n;
                        inverse[k][j] = inverse[k][j] - inverse[i][j]*n;
                    }
                }
            }
        }
        
    }else{
        cout << "Inverse of a non-square matrix can't be found!\n";
        //No reason to exit program
    }
    
    /*
        Writing files
    */
    //Writing transpose
    if(output.is_open()){
        for(int i = 0; i < transpose.size(); i++){
            for(int j = 0; j < transpose[0].size(); j++){
                //Adding every item
                output << transpose[i][j];
                if(j != transpose[0].size() - 1){
                    output << ",";
                }
            }
            //Newline for new row
            output << "\n";
        }
    }else{
        //File error, no need to exit as no ramifications on later code
        cout << outputFile << " file not open!" << "\n";
    }
    //Close file
    output.close();
    
    //Writing inverse and making sure it was valid to begin
    if(outputInv.is_open()&&valid){
        for(int i = 0; i < inverse.size(); i++){
            for(int j = 0; j < inverse[0].size(); j++){
                //Adding every item
                outputInv << inverse[i][j];
                if(j!=inverse[0].size()-1){
                    outputInv << ",";
                }
            }
            //Newline for new row
            outputInv << "\n";
        }
    }else{
        //File error, no need to exit as no ramifications on later code
        cout << inv << " file not open!" << "\n";
    }
    //Close file
    outputInv.close();
    return 0;
}
