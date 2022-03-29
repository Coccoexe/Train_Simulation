/**
 * @file line_trains.cpp
 * @author Alessio Cocco - 1219609 (alessio.cocco@studentiunipd.it)
 */

#include "../include/train.hpp"
#include <iostream>

Train::Train(double max_v, int dir, int num, std::vector<double> t)
    : velocity_max{max_v}, direction{dir}, train_number{num}
{
    velocity_curr = 0;
    distance = 0;
    expected_times = t;
}

void Train::print() const
{
    std::cout << "number:    " << train_number << std::endl;
    std::cout << "max velocity:  " << velocity_max << std::endl;
    std::cout << "direction: " << direction << std::endl;
    for (int i = 0; i < expected_times.size(); i++)
        std::cout << " - station: " << i << " - time: " << expected_times.at(i) << std::endl;
    std::cout << std::endl;
}
