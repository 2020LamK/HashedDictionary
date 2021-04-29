//
// HashedDictionary class header file
// Created by Kelly Lam on 2/8/2021.
//

#ifndef _HASHEDDICTIONARY_H
#define _HASHEDDICTIONARY_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Fraction.h"

using namespace std;

constexpr int DICTIONARY_MAX_SIZE = 101;

class HashedDictionary {
public:
    enum statusStates {
        UNUSED,
        IN_USE,
        DELETED
    };

    static std::uint32_t Hash(string s); // hash function

    HashedDictionary(); // Constructor
    ~HashedDictionary(); // Destructor
    void clear();
    bool isEmpty();
    int size(); // Number of elements in Dictionary

    void insert(string k, Fraction v);
    void remove(string k);
    Fraction search(string k);
    void update(string k, Fraction v);

    void insertOrUpdate(string k, Fraction v);
    bool getFirstKey(string &k);
    bool getNextKey(string &k);

private:
    string keys[DICTIONARY_MAX_SIZE];
    Fraction values[DICTIONARY_MAX_SIZE];
    statusStates status[DICTIONARY_MAX_SIZE]{};
    int actualSize=0; // dictionary actual size
    int elementMarker=0; // marks the index that the user left off on
};

#endif
