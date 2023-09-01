/**
 * abstractdb.cpp
 * C++ source file that should contain implementation for member functions
 * - loadCSV()
 * - saveCSV()
 * 
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Tasks 4 and 5)
 */ 

#include <iostream>
#include "abstractdb.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>


using namespace nwen;

/*
 *  Super class method for turning rows of movies into a file
 *  returns a boolean to indicate success, and param of string for file name
 */
bool AbstractDbTable::saveCSV(string s){

    //ofstream outfile(s, std::ios::trunc); // this is a failsafe snippet of code to absolutely make sure to erase all content of outfile

    ofstream outfile;
    outfile.open(s);

    if(outfile.fail()){     // if there was a failure opening the file
        outfile.close();    // debate as to whether to close a file that didn't even open correctly
        return false;
    }

    for(int i = 0; i < rows(); i++){    // using the rows method we defined
        const movie * m = get(i);       // using the get method we defined

        // to match the test output cases, the strings are wrapped in quotation marks
        outfile << m->id << ",\"" << m->title << "\"," << m->year << ",\"" << m->director << "\"" << endl;

        // Failed to write to the file
        if (outfile.fail()) {
            outfile.close();    // safe practice to close the file before returning
            return false;
        }
    }

    outfile.close();
    return true;
}

/*
 *  Super class method for turning a file into a vector of initialized movie objects
 *  returns a boolean to indicate success, and param of string for file name
 */
bool AbstractDbTable::loadCSV(string s){

    ifstream infn;  // named infn as per assignment paper
    infn.open(s);

    if(!infn.is_open()){    // if there was a failure opening the file
        infn.close();       // debate as to whether to close a file that didn't even open correctly
        return false;
    }

    string line;
    while(getline(infn, line)){     // while we can get a line from file and put it into our line variable

        vector<string> parts;       // declare a storage solution for each parsed part of our line

        string token;
        stringstream ss(line);              // stringstream is turing the line into a stream, similar to file.
        while(getline(ss, token, ',')){     // while we can get a snippet from our line and put into token variable

            parts.push_back(token);         // this works to add to vector a copy of the token, this means it can be updated
        }

        if(parts.size() == 4){  // may have to double check that the size of the vector is indeed 4
            movie m;

            unsigned long id;
            char title[50];             // declaring a temp location for each to be field of our movie
            unsigned short year;
            char director[50];

            try{
                id = stoul(parts[0]);           // parts[0] must be an unsigned long
            } catch (const exception& e) {
                infn.close();                   // doing stoul on non digits will throw an exception which we catch and terminate
                return false;
            }                                   // you could argue I should split this into a function, but laying it out like this, you see what's happening

            try{
                unsigned short temp = stoi(parts[1]);   // parts[1] must be a string and not digits
                infn.close();
                return false;                           // it must throw an exception to 'pass' otherwise terminate
            } catch (const exception& e) {
            }

            try{
                year = stoi(parts[2]);          // parts[2] must be an unsigned short
            } catch (const exception& e) {
                infn.close();                   // doing stoi on non digits will throw an exception which we catch and terminate
                return false;
            }

            try{
                unsigned short temp = stoi(parts[3]);   // parts[1] must be a string and not digits
                infn.close();
                return false;                           // it must throw an exception to 'pass' otherwise terminate
            } catch (const exception& e) {
            }


            // for each token, initialize our new movie record's fields
            m.id = id;
            strcpy(m.title, parts[1].c_str());      //m.title = title;
            m.year = year;
            strcpy(m.director, parts[3].c_str());   //m.director = director;

            add(m);     // add every line into the database using .add()

        }else{          // either more or less than 4 tokens were parsed meaning it didn't follow our expected format

            infn.close();
            return false;
        }
    }
    // when all lines and all tokens are correctly handled, return true

    infn.close();
    return true;

}
