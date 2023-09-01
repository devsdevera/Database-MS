/**
 * vectordb.cpp
 * C++ source file that should contain implementation for member functions
 * - rows()
 * - get()
 * - add()
 * - update()
 * - remove()
 * 
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Task 3)
 */ 

#include "vectordb.hpp"
using namespace nwen;


int VectorDbTable::rows() const{
    return arraylist.size();    // our vector stores each movie as rows, therefore simple .size()
}

const movie* VectorDbTable::get(int i) const{

    if(i > rows()){   // prevent an index out of bounds exception, should be within .size()
        return NULL;
    }
    return &(arraylist[i]);     // returns a pointer to a movie structure, thus wrapped address
}

int VectorDbTable::add(movie m){

    for(movie n : arraylist){   // double check that the movie does not already exist in arrayList
        if(n.id == m.id){
            return 0;           // id is designed to be a unique identifier, therefore I use id
        }
    }
    arraylist.push_back(m);     // put the movie at the end of the vector collection
    return 1;
}

bool VectorDbTable::update(unsigned long id, movie m){
    for (auto& mov : arraylist) {
        if (mov.id == id) {         // find the id of the movie we are updating
            mov = m;                // can very simply set this movie to parameter movie
            return true;
        }
    }
    return false;                   // no ids matched, therefore not updated
}

bool VectorDbTable::remove(unsigned long id){
    for(int j = 0; j < arraylist.size(); j++){          // another method to run through each movie in vector
        movie mov = arraylist[j];
        if(mov.id == id){                               // find the id of the move we want to remove
            arraylist.erase(arraylist.begin() + j);     // must use .begin with .erase to get a pointer
            return true;
        }                                               // no need to shift elements to left, vector is cool
    }
    return false;                                       // no ids matched, therefore not removed
}
