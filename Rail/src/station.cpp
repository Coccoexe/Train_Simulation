/**
 * @file station.cpp
 * @author Giovanni Brejc
 */

#include "../include/station.hpp"
#include <iostream>

Station::Station(std::string n, double d, bool type)
    : local{type},  deposit{new Deposit()}
{
    name = n;
    distance = d;
}

void Station::print() const
{
    std::cout << "name:     " << name << std::endl;
    std::cout << "local:    " << local << std::endl;
    std::cout << "distance: " << distance << "km" << std::endl;
    std::cout << std::endl;
}

void Station::swap_train()
{
    if(rail.size() == 2)
        if(rail.at(0)->get_velocity_max() < rail.at(1)->get_velocity_max())
            swap(rail.at(0), rail.at(1));
}