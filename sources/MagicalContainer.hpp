#ifndef MAGICAL_CONTAINER
#define MAGICAL_CONTAINER

#include <vector>
#include <functional>
#include <algorithm>
#include <set>

namespace ariel {

    // Forward declaration of MagicalContainer
    class MagicalContainer;

    // Base iterator class
    class Iterator {
    public:
        virtual ~Iterator() = default;
        Iterator() = default;
        Iterator(const Iterator& other) = default;
        Iterator& operator=(const Iterator& other) = default;
        Iterator(Iterator&& other) = default;
        Iterator& operator=(Iterator&& other) = default;
    };

    // Main MagicalContainer class
    class MagicalContainer {
    private:
        std::set<int> elements;
        std::vector<const int*> primeIt;
        std::vector<const int*> ascIt;
        std::vector<const int*> sideIt;

    public:
        MagicalContainer() = default;

        // Add an element to the container
        void addElement(int element);

        // Remove an element from the container
        void removeElement(int element);

        // Get the size of the container
        size_t size() const;

        // Iterator for iterating over elements in ascending order
        class AscendingIterator : public Iterator {
        private:
            MagicalContainer& cont;
            size_t position;

        public:
            AscendingIterator(MagicalContainer& cont) : cont(cont), position(0) {}
            AscendingIterator(const AscendingIterator& other) : cont(other.cont), position(other.position) {}

            // Get the beginning of the iterator
            AscendingIterator begin() const;

            // Get the end of the iterator
            AscendingIterator end() const;

            // Compare iterators for equality
            bool operator==(const AscendingIterator& other) const;

            // Compare iterators for inequality
            bool operator!=(const AscendingIterator& other) const;

            // Compare iterators for greater than
            bool operator>(const AscendingIterator& other) const;

            // Compare iterators for less than
            bool operator<(const AscendingIterator& other) const;

            // Assign an iterator to another iterator
            AscendingIterator& operator=(const AscendingIterator& other);

            // Dereference the iterator and return the value
            int operator*() const;

            // Move the iterator to the next element
            AscendingIterator& operator++();
        };

        // Iterator for iterating over prime elements
        class PrimeIterator : public Iterator {
        private:
            MagicalContainer& cont;
            size_t position;

        public:
            PrimeIterator(MagicalContainer& cont) : cont(cont), position(0) {}
            PrimeIterator(const PrimeIterator& other) : cont(other.cont), position(other.position) {}

            // Check if a number is prime
            static bool isPrime(int num);

            // Get the beginning of the iterator
            PrimeIterator begin() const;

            // Get the end of the iterator
            PrimeIterator end() const;

            // Compare iterators for equality
            bool operator==(const PrimeIterator& other) const;

            // Compare iterators for inequality
            bool operator!=(const PrimeIterator& other) const;

            // Assign an iterator to another iterator
            PrimeIterator& operator=(const PrimeIterator& other);

            // Compare iterators for greater than
            bool operator>(const PrimeIterator& other) const;

            // Compare iterators for less than
            bool operator<(const PrimeIterator& other) const;

            // Dereference the iterator and return the value
            int operator*() const;

            // Move the iterator to the next element
            PrimeIterator& operator++();
        };

        // Iterator for iterating over elements in a side cross pattern
        class SideCrossIterator : public Iterator {
        private:
            MagicalContainer& cont;
            size_t position;

        public:
            SideCrossIterator(MagicalContainer& cont) : cont(cont), position(0) {}
            SideCrossIterator(const SideCrossIterator& other) : cont(other.cont), position(other.position) {}

            // Get the beginning of the iterator
            SideCrossIterator begin() const;

            // Get the end of the iterator
            SideCrossIterator end() const;

            // Compare iterators for equality
            bool operator==(const SideCrossIterator& other) const;

            // Compare iterators for inequality
            bool operator!=(const SideCrossIterator& other) const;

            // Compare iterators for greater than
            bool operator>(const SideCrossIterator& other) const;

            // Assign an iterator to another iterator
            SideCrossIterator& operator=(const SideCrossIterator& other);

            // Compare iterators for less than
            bool operator<(const SideCrossIterator& other) const;

            // Dereference the iterator and return the value
            int operator*() const;

            // Move the iterator to the next element
            SideCrossIterator& operator++();
        };
    };
}

#endif