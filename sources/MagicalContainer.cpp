#include "MagicalContainer.hpp"
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace ariel;
using namespace std;

// Add an element to the container
void MagicalContainer::addElement(int elem) {
    // Clear iterators to ensure they are up-to-date
    ascIt.clear();
    sideIt.clear();
    
    // Insert the element into the set
    auto it = elements.insert(elem);

    // Check if the element is prime
    if (PrimeIterator::isPrime(elem)) {
        primeIt.clear();
        for (const int& elem : elements) {
            if (PrimeIterator::isPrime(elem))
                primeIt.push_back(&elem);
        }
    }

    // Populate the ascending iterator
    for (const int& elem : elements) {
        ascIt.push_back(&elem);
    }

    // Generate the side cross iterator
    size_t start = 0, end = this->size() - 1;
    if (end != 0) {
        while (start <= end && end != 0) {
            sideIt.push_back(ascIt.at(start));

            if (start != end)
                sideIt.push_back(ascIt.at(end));

            start++;
            end--;
        }
    } else {
        sideIt.push_back(ascIt.at(0));
    }
}

// Remove an element from the container
void MagicalContainer::removeElement(int elem) {
    // Find the element in the set
    auto it = elements.find(elem);

    if (it == elements.end())
        throw runtime_error("Element is not found in the container.");

    // Erase the element from the set
    elements.erase(elem);

    // Check if the removed element was prime
    if (PrimeIterator::isPrime(elem)) {
        auto it_pr = find(primeIt.begin(), primeIt.end(), &(*it));
        primeIt.erase(it_pr);
    }

    // Remove the element from the ascending iterator
    auto it_asc = find(ascIt.begin(), ascIt.end(), &(*it));
    ascIt.erase(it_asc);

    // Clear and reconstruct the side cross iterator
    sideIt.clear();
    size_t start = 0, end = this->size() - 1;
    if (end != 0) {
        while (start <= end && end != 0) {
            sideIt.push_back(ascIt.at(start));

            if (start != end)
                sideIt.push_back(ascIt.at(end));

            start++;
            end--;
        }
    } else {
        sideIt.push_back(ascIt.at(0));
    }
}

// Return the size of the container
size_t MagicalContainer::size() const {
    return elements.size();
}

// AscendingIterator

// Return the beginning of the ascending iterator
MagicalContainer::AscendingIterator ariel::MagicalContainer::AscendingIterator::begin() const {
    return AscendingIterator(cont);
}

// Return the end of the ascending iterator
MagicalContainer::AscendingIterator ariel::MagicalContainer::AscendingIterator::end() const {
    AscendingIterator ascIter(cont);
    ascIter.position = cont.ascIt.size();
    return ascIter;
}

// Dereference the iterator and return the value
int ariel::MagicalContainer::AscendingIterator::operator*() const {
    return *(cont.ascIt.at(position));
}

// Move the iterator to the next element
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    if (position >= cont.ascIt.size())
        throw std::runtime_error("Iterator is out of range.");
    ++position;
    return *this;
}

// Assign the iterator to another iterator
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (this != &other) {
        if (&cont != &other.cont)
            throw std::runtime_error("Cannot compare iterators from different containers.");

        position = other.position;
    }
    return *this;
}

// Compare the iterator with another iterator for equality
bool ariel::MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position == other.position;
}

// Compare the iterator with another iterator for inequality
bool ariel::MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position != other.position;
}

// Compare the iterator with another iterator for greater than
bool ariel::MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position > other.position;
}

// Compare the iterator with another iterator for less than
bool ariel::MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position < other.position;
}

// SideCrossIterator

// Return the beginning of the side cross iterator
MagicalContainer::SideCrossIterator ariel::MagicalContainer::SideCrossIterator::begin() const {
    return SideCrossIterator(cont);
}

// Return the end of the side cross iterator
MagicalContainer::SideCrossIterator ariel::MagicalContainer::SideCrossIterator::end() const {
    SideCrossIterator sidIter(cont);
    sidIter.position = cont.sideIt.size();
    return sidIter;
}

// Dereference the iterator and return the value
int ariel::MagicalContainer::SideCrossIterator::operator*() const {
    return *(cont.sideIt.at(position));
}

// Move the iterator to the next element
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (position >= cont.sideIt.size())
        throw std::runtime_error("Iterator is out of range.");
    ++position;
    return *this;
}

// Assign the iterator to another iterator
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (this != &other) {
        if (&cont != &other.cont)
            throw std::runtime_error("Cannot compare iterators from different containers.");

        position = other.position;
    }
    return *this;
}

// Compare the iterator with another iterator for equality
bool ariel::MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position == other.position;
}

// Compare the iterator with another iterator for inequality
bool ariel::MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position != other.position;
}

// Compare the iterator with another iterator for greater than
bool ariel::MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position > other.position;
}

// Compare the iterator with another iterator for less than
bool ariel::MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position < other.position;
}

// PrimeIterator

// Return the beginning of the prime iterator
MagicalContainer::PrimeIterator ariel::MagicalContainer::PrimeIterator::begin() const {
    return PrimeIterator(cont);
}

// Return the end of the prime iterator
MagicalContainer::PrimeIterator ariel::MagicalContainer::PrimeIterator::end() const {
    PrimeIterator primeIter(cont);
    primeIter.position = cont.primeIt.size();
    return primeIter;
}

// Dereference the iterator and return the value
int ariel::MagicalContainer::PrimeIterator::operator*() const {
    return *(cont.primeIt.at(position));
}

// Move the iterator to the next element
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if (position >= cont.primeIt.size())
        throw std::runtime_error("Iterator is out of range.");
    ++position;
    return *this;
}

// Assign the iterator to another iterator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    position = other.position;
    return *this;
}

// Compare the iterator with another iterator for equality
bool ariel::MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position == other.position;
}

// Compare the iterator with another iterator for inequality
bool ariel::MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position != other.position;
}

// Compare the iterator with another iterator for greater than
bool ariel::MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position > other.position;
}

// Compare the iterator with another iterator for less than
bool ariel::MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from different containers.");
    return position < other.position;
}

// Check if a number is prime
bool MagicalContainer::PrimeIterator::isPrime(int num) {
    if (num <= 1)
        return false;
    if (num % 2 == 0 && num != 2)
        return false;
    int sqrtNumber = sqrt(num);
    for (int i = 2; i <= sqrtNumber; ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}
