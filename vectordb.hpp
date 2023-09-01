/**
 * vectordb.hpp
 * C++ header file that should contain declaration for
 * - VectorDbTable class
 * 
 * You need to modify this file to declare VectorDbTable class 
 * as specified in the hand-out (Task 2)
 */ 

#include "abstractdb.hpp"
#include <vector>


namespace nwen
{
    class VectorDbTable : public AbstractDbTable {
                                                        // vector as table for storing the movie records
        vector<movie> arraylist;                        // I named our vector arraylist because

    public:
        int rows() const override;                      // does not modify any member variables = const
        const movie* get(int i) const override;         // override keyword after each one is good practice
        int add(movie m) override;
        bool update(unsigned long i, movie) override;   // a (non-pointer) movie structure parameters
        bool remove(unsigned long i) override;

        // you may declare a default constructor, additional member variables and functions.

        VectorDbTable(){}

    };
}


