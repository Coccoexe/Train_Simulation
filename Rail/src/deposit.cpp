/**
 * @file deposit.cpp
 * @author Giovanni Brejc
 */

#include "../include/deposit.hpp"

bool Deposit::is_empty()
{
    // checks size of every queue
    return fast.empty() && medium.empty() && slow.empty();
}

void Deposit::push(std::shared_ptr<Train> p)
{
    // push train in correct queue
    if (p->get_velocity_max() == 5)
        fast.push_back(p);
    else if (p->get_velocity_max() == 4)
        medium.push_back(p);
    else
        slow.push_back(p);

    // stop the train
    p->set_velocity(0);
}

std::shared_ptr<Train> Deposit::pop()
{
    // 1. empty fast queue
    if (fast.size())
    {
        fast.front()->set_velocity(1.3);
        std::shared_ptr<Train> ret = fast.front();
        fast.erase(fast.begin());
        return ret;
    }
    // 2. empty medium queue
    else if (medium.size())
    {
        medium.front()->set_velocity(1.3);
        std::shared_ptr<Train> ret = medium.front();
        medium.erase(medium.begin());
        return ret;
    }
    // 3. empty slow queue
    slow.front()->set_velocity(1.3);
    std::shared_ptr<Train> ret = slow.front();
    slow.erase(slow.begin());
    return ret;
}

void Deposit::add_delay() 
{
    for(int i = 0; i < fast.size(); i++)
        fast.at(i)->increase_delay(1);

    for(int i = 0; i < medium.size(); i++)
        medium.at(i)->increase_delay(1);

    for(int i = 0; i < slow.size(); i++)
        slow.at(i)->increase_delay(1);
}
