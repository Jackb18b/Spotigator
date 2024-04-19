#pragma once
#include <string>
#include <iostream>
using namespace std;


class CountryTable
{
private:
    int* Table;


public:
    int hash(std::string countryCode);

};