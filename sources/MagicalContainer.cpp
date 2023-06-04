#include "MagicalContainer.hpp"
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>
using namespace ariel;
using namespace std;

void MagicalContainer::addElement(int elem) {
    ascIt.clear();
    sideIt.clear();
    auto it = elements.insert(elem);
    if(PrimeIterator::isPrime(elem))
    {
        prElem.clear();
        for (const int &elem : elements)
        {
            if (PrimeIterator::isPrime(elem))
                prElem.push_back(&elem);
        }
    }
    for (const int &elem : elements)
    {
        ascIt.push_back(&elem);
    }
    size_t start = 0, end = this->size() - 1;
    if (end != 0)
    {
        while (start <= end && end != 0)
        {
            sideIt.push_back(ascIt.at(start));

            if (start != end)
                sideIt.push_back(ascIt.at(end));
            start++;
            end--;
        }
    }
    else
    {
        sideIt.push_back(ascIt.at(0));
    }
}

void MagicalContainer::removeElement(int elem) {
auto it = elements.find(elem);

	if (it == elements.end())
		throw runtime_error("Element is not found in the container.");

	elements.erase(elem);

	if (PrimeIterator::isPrime(elem))
	{
		auto it_pr = find(prElem.begin(), prElem.end(), &(*it));
		prElem.erase(it_pr);
	}


	auto it_asc = find(ascIt.begin(), ascIt.end(), &(*it));
	ascIt.erase(it_asc);

	sideIt.clear();
	size_t start = 0, end = this->size() - 1;

	if (end!=0)
    {
        while (start <= end && end != 0)
	    {
			sideIt.push_back(ascIt.at(start));

			if (start != end)
				sideIt.push_back(ascIt.at(end));

			start++;
			end--;
		}
    }
	else
	{
		sideIt.push_back(ascIt.at(0));
	}
}
size_t MagicalContainer::size() const {
    return elements.size();
}
// AscendingIterator
ariel::MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &cont):cont(cont),position(0){}

MagicalContainer::AscendingIterator ariel::MagicalContainer::AscendingIterator::begin() const
{
    return AscendingIterator(cont);
}
MagicalContainer::AscendingIterator ariel::MagicalContainer::AscendingIterator::end() const
{
    AscendingIterator ascIter(cont);
    ascIter.position =cont.ascIt.size();
    return ascIter;
}
int ariel::MagicalContainer::AscendingIterator::operator*() const
{
    return *(cont.ascIt.at(position));
}
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (position >= cont.ascIt.size())
		throw std::runtime_error("Iterator is out of range.");
    ++position;
    return *this;
}
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
	if (this != &other)
	{
		if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");

		position = other.position;
	}
	return *this;
}

bool ariel::MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position==other.position;
}

bool ariel::MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position!=other.position;
}

bool ariel::MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position>other.position;
}
bool ariel::MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position<other.position;
}
//SideCrossIterator
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& cont) : cont(cont),position(0){}

MagicalContainer::SideCrossIterator ariel::MagicalContainer::SideCrossIterator::begin()
{
    return SideCrossIterator(cont);
}
MagicalContainer::SideCrossIterator ariel::MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator sidIter(cont);
    sidIter.position =cont.sideIt.size();
    return sidIter;
}
bool ariel::MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position==other.position;
}
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
	if (this != &other)
	{
		if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");

		position = other.position;
	}
	return *this;
}
bool ariel::MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position!=other.position;
}

bool ariel::MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position>other.position;
}

bool ariel::MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position<other.position;
}

int ariel::MagicalContainer::SideCrossIterator::operator*() const
{
    return *(cont.sideIt.at(position));
}

MagicalContainer::SideCrossIterator &ariel::MagicalContainer::SideCrossIterator::operator++()
{
    if (position >= cont.sideIt.size())
		throw std::runtime_error("Iterator is out of range.");
    ++position;
    return *this;
}

//PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& cont) : cont(cont),position(0){}

MagicalContainer::PrimeIterator ariel::MagicalContainer::PrimeIterator::begin()
{
    return PrimeIterator(cont);
}
MagicalContainer::PrimeIterator ariel::MagicalContainer::PrimeIterator::end()
{
    PrimeIterator primeIter(cont);
    primeIter.position =cont.prElem.size();
    return primeIter;
}

bool ariel::MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position==other.position;
}

bool ariel::MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position!=other.position;
}

MagicalContainer::PrimeIterator &ariel::MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (&cont != &other.cont)
        throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    position = other.position;
	return *this;
}

bool ariel::MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position>other.position;
}

bool ariel::MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    if (&cont != &other.cont)
			throw std::runtime_error("Cannot compare iterators from diffrent containers.");
    return position<other.position;
}

int ariel::MagicalContainer::PrimeIterator::operator*() const
{
    return *(cont.prElem.at(position));
}

MagicalContainer::PrimeIterator &ariel::MagicalContainer::PrimeIterator::operator++()
{
    if (position >= cont.prElem.size())
		throw std::runtime_error("Iterator is out of range.");
    ++position;
    return *this;
}

bool MagicalContainer::PrimeIterator::isPrime(int num) {
    if (num <= 1)
        return false;
    if(num%2 == 0&&num!=2)
        return false;
    int sqrtNumber = sqrt(num);
    for (int i = 2; i <= sqrtNumber; ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}