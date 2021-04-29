//
// HashedDictionary class definitions
// Created by Kelly Lam on 2/8/2021.
//

#include "HashedDictionary.h"
#include <stdexcept>
#include <cstdint>

// HashedDictionary();
HashedDictionary::HashedDictionary() = default;

// ~HashedDictionary();
HashedDictionary::~HashedDictionary() = default;

// int Hash(string s);
std::uint32_t HashedDictionary::Hash(string s) {
    std::uint32_t sum=0;
    for (std::string::size_type i=0;i<s.length();i++)
        sum = sum * i + s[i];
    return sum % DICTIONARY_MAX_SIZE;
}

// void clear();
void HashedDictionary::clear() {
    for (int i=0; i < DICTIONARY_MAX_SIZE; i++) {
        status[i] = DELETED;
    }
    actualSize=0;
}

// bool isEmpty();
bool HashedDictionary::isEmpty() {
    return actualSize == 0;
}

// int size();
int HashedDictionary::size() {
    return actualSize;
}

// void insert(string k, Fraction v);
void HashedDictionary::insert(string k, Fraction v) {
    if (actualSize == DICTIONARY_MAX_SIZE) {
        throw overflow_error("OverflowException");
    }

    int i = Hash(k);
    int count=0;

    while (status[i] != UNUSED && count < DICTIONARY_MAX_SIZE) {
        if ((status[i] == IN_USE) && (keys[i] == k)) {
            throw domain_error("DuplicateKeyException");
        }
        count++;
        i = (i+1)%DICTIONARY_MAX_SIZE;
    }

    i = Hash(k);

    while (status[i] == IN_USE) {
        i = (i+1)%DICTIONARY_MAX_SIZE;
    }

    keys[i] = k;
    values[i] = v;
    status[i] = IN_USE;

    actualSize++;
}

// void remove(string k);
void HashedDictionary::remove(string k) {
    int i = Hash(k);
    int count=0;

    while (status[i] != UNUSED && count < DICTIONARY_MAX_SIZE) {
        if (status[i] == IN_USE && keys[i] == k) {
            status[i] = DELETED;
            actualSize--;
            return;
        }
        count++;
        i = (i+1)%DICTIONARY_MAX_SIZE;
    }

    throw domain_error("KeyNotFoundException");
}

// Fraction search(string k);
Fraction HashedDictionary::search(string k) {
    int i = Hash(k);
    int count=0;

    while (status[i] != UNUSED && count < DICTIONARY_MAX_SIZE) {
        if (status[i] == IN_USE && keys[i] == k) {
            return values[i];
        }
        count++;
        i = (i+1)%DICTIONARY_MAX_SIZE;
    }

    throw domain_error("KeyNotFoundException");
}

// void update(string k, Fraction v);
void HashedDictionary::update(string k, Fraction v) {
    int i = Hash(k);

    while (status[i] != UNUSED) {
        if ((status[i] == IN_USE) && (keys[i] == k)) {
            values[i] = v;
            return;
        }
        i = (i+1)%DICTIONARY_MAX_SIZE;
    }

    throw domain_error("KeyNotFoundException");
}

// void insertOrUpdate(string k, Fraction v);
void HashedDictionary::insertOrUpdate(string k, Fraction v) {
    if (actualSize == DICTIONARY_MAX_SIZE) {
        throw overflow_error("OverflowException");
    }

    int i = Hash(k);

    while (status[i] == IN_USE) {
        i = (i+1)%DICTIONARY_MAX_SIZE;
    }

    keys[i] = k;
    values[i] = v;
    status[i] = IN_USE;

    actualSize++;

    i = Hash(k);
    int count=0;

    while (status[i] != UNUSED && count < DICTIONARY_MAX_SIZE) {
        if ((status[i] == IN_USE) && (keys[i] == k)) {
            keys[i] = k;
            values[i] = v;
        }
        count++;
        i = (i+1)%DICTIONARY_MAX_SIZE;
    }
}

// bool getFirstKey(string &k);
bool HashedDictionary::getFirstKey(string &k) {
    if (isEmpty()) {
        return false;
    }

    for (int i=0; i < DICTIONARY_MAX_SIZE; i++) {
        if (status[i] == IN_USE) {
            k = keys[i];
            elementMarker = i;
            return true;
        }
    }
    return false;
}

// bool getNextKey(string &k);
bool HashedDictionary::getNextKey(string &k) {
    int i = elementMarker + 1;

    while (i < DICTIONARY_MAX_SIZE) {
        if (status[i] == IN_USE) {
            k = keys[i];
            elementMarker = i;
            return true;
        }
        i++;
    }
    return false;
}