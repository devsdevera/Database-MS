/**
 * abstractdb.hpp
 * C++ header file that should contain declaration for
 * - struct movie (given)
 * - AbstractDbTable abstract class
 * 
 * You need to modify this file to declare AbstractDbTable abstract class 
 * as specified in the hand-out (Task 1)
 */ 



#ifndef __ABSTRACT_DB_HPP__
#define __ABSTRACT_DB_HPP__

#include <string>

using namespace std;

namespace nwen
{
    struct movie {              // creating the structure for a movie
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };

    class AbstractDbTable { // this will be the super class, abtract because we won't be making objects of this
    public:
        virtual int rows() const = 0;                       // does not modify any member variables = const
        virtual const movie* get(int i) const = 0;          // = 0 is pure virtual
        virtual int add(movie m) = 0;                       // important, return value was not stated. made int for testing
        virtual bool update(unsigned long i, movie m) = 0;  // a (non-pointer) movie structure parameters
        virtual bool remove(unsigned long i) = 0;           // documenting this method so as not to forget - const movie& m

        bool loadCSV(string s);
        bool saveCSV(string s);
    };
}

#endif /* __ABSTRACT_DB_HPP__ */
