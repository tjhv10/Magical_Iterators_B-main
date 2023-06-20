#include <iostream>
#include <stdexcept>
#include "doctest.h"
#include "sources/MagicalContainer.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("Adding numbers to magical container and checking sizes.")
{
    MagicalContainer cont;
    CHECK(cont.size()==0);
    cont.addElement(8);
    CHECK(cont.size()==1);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    CHECK(cont.size()==4);
}
TEST_CASE("Adding numbers to prime magical container and checking sizes.")
{
    MagicalContainer cont;
    cont.addElement(8);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    cont.addElement(49);
    MagicalContainer::PrimeIterator primeIt(cont);
    CHECK(cont.size()==5);
    int expectedVal[] = {2,7,97};
    int i =0;
    for (auto it = primeIt.begin(); it != primeIt.end(); ++it)
    {
        CHECK((*it) == expectedVal[i++]);
    }
}
TEST_CASE("Adding numbers to SideCross magical container and checking sizes.")
{
    MagicalContainer cont;
    cont.addElement(8);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    cont.addElement(49);
    MagicalContainer::SideCrossIterator sideIt(cont);
    CHECK(cont.size()==5);
    int expectedVal[] = {2,97,7,49,8};
    int i =0;
    for (auto it = sideIt.begin(); it != sideIt.end(); ++it)
    {
        CHECK((*it) == expectedVal[i++]);
    }
}
TEST_CASE("Adding numbers to Ascending magical container and checking sizes.")
{
    MagicalContainer cont;
    CHECK(cont.size()==0);
    cont.addElement(8);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    cont.addElement(49);
    MagicalContainer::AscendingIterator asceIt(cont);
    CHECK(cont.size()==5);
    
    int expectedVal[] = {2,7,8,49,97};
    int i =0;
    for (auto it = asceIt.begin(); it != asceIt.end(); ++it)
    {
        CHECK((*it) == expectedVal[i++]);
    }
}
TEST_CASE("Adding numbers to Ascending magical and prime container.")
{
    MagicalContainer cont;
    cont.addElement(8);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    cont.addElement(49);
    MagicalContainer::AscendingIterator asceIt(cont);
    CHECK(cont.size()==5);
    int expectedValasce[] = {2,7,8,49,97};
    int expectedValprime[] = {2,7,97};
    int i =0;
    MagicalContainer::PrimeIterator primeIt(cont);
    for (auto it = primeIt.begin(); it != primeIt.end(); ++it)
    {
        CHECK((*it) == expectedValprime[i++]);
    }
    i=0;
    for (auto it = asceIt.begin(); it != asceIt.end(); ++it)
    {
        CHECK((*it) == expectedValasce[i++]);
    }
}
TEST_CASE("Checking operators AscendingIterator.")
{
    MagicalContainer cont;
    cont.addElement(8);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    cont.addElement(49);
    MagicalContainer::AscendingIterator asceIt1(cont);
    MagicalContainer::AscendingIterator asceIt2(cont);
    while (*asceIt1!=7)
    {
        ++asceIt1;
    }
    while (*asceIt2!=49)
    {
        ++asceIt2;
    }
    CHECK(asceIt1<asceIt2);
}
TEST_CASE("Checking operators PrimeIterator.")
{
    MagicalContainer cont;
    cont.addElement(8);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    cont.addElement(49);
    MagicalContainer::PrimeIterator primeIt1(cont);
    MagicalContainer::PrimeIterator primeIt2(cont);
    while (*primeIt1!=7)
    {
        ++primeIt1;
    }
    while (*primeIt2!=97)
    {
        ++primeIt2;
    }
    CHECK(primeIt1<primeIt2);
}
TEST_CASE("Checking operators SideCrossIterator.")
{
    MagicalContainer cont;
    cont.addElement(8);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    cont.addElement(49);
    MagicalContainer::SideCrossIterator sideCrIt1(cont);
    MagicalContainer::SideCrossIterator sideCrIt2(cont);
    while (*sideCrIt1!=7)
    {
        ++sideCrIt1;
    }
    while (*sideCrIt2!=97)
    {
        ++sideCrIt2;
    }
    CHECK(sideCrIt1>sideCrIt2);
}
TEST_CASE("Adding numbers and counting agian.")
{
    MagicalContainer cont;
    CHECK(cont.size()==0);
    cont.addElement(8);
    cont.addElement(7);
    cont.addElement(2);
    cont.addElement(97);
    MagicalContainer::AscendingIterator asceIt1(cont);
    int count =0;
    while (*asceIt1!=97)
    {
        ++asceIt1;
        count++;
    }
    CHECK(count==3);
    cont.addElement(49);
    count=0;
    asceIt1 = asceIt1.begin();
    while (*asceIt1!=49)
    {
        ++asceIt1;
        count++;
    }
    CHECK(count==3);
    CHECK(*++asceIt1==97);
}