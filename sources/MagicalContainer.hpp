#ifndef MAGICAL_CONTAINER
#define MAGICAL_CONTAINER

#include <vector>
#include <functional>
#include <algorithm>
#include <set>
namespace ariel{
    class MagicalContainer;

    class Iterator
    {
    public:
        virtual ~Iterator() = default;
        Iterator(){};
        Iterator(const Iterator &other) = default;
        Iterator &operator=(const Iterator &other) = default;
        Iterator(Iterator &&other) = default;
        Iterator &operator=(Iterator &&other) = default;
    };

    class MagicalContainer
    {
        private:
            std::set<int> elements;
            std::vector<const int *> prElem;
            std::vector<const int *> ascIt;
            std::vector<const int *> sideIt;
        public:
            
            MagicalContainer() = default;
            void addElement(int element);
            void removeElement(int element);
            size_t size() const;
            std::set<int> getElements() const;
            friend class PrimeIterator;
            friend class AscendingIterator;
            friend class SideCrossIterator;
        class AscendingIterator : public Iterator
        {
        private:
            MagicalContainer &cont;
            size_t position;
        public:

            AscendingIterator(MagicalContainer &cont);
            AscendingIterator begin() const;
            AscendingIterator end() const;
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            AscendingIterator &operator=(const AscendingIterator &other);
            int operator*() const;
            AscendingIterator & operator++();
        };

        class PrimeIterator : public Iterator
        {
        private:
            MagicalContainer &cont;
            size_t position;
            
        public:
            PrimeIterator(MagicalContainer &cont);
            static bool isPrime(int num);
            PrimeIterator begin();
            PrimeIterator end();
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            PrimeIterator &operator=(const PrimeIterator &other);
            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            int operator*() const;
            PrimeIterator & operator++();
        };

        class SideCrossIterator : public Iterator
        {
        private:
            MagicalContainer &cont;
            size_t position;
        public:
            SideCrossIterator(MagicalContainer &cont);
            SideCrossIterator begin();
            SideCrossIterator end();
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator<(const SideCrossIterator &other) const;
            int operator*() const;
            SideCrossIterator & operator++();
        };
    };
}
#endif