/**
 * @file station.hpp
 * @author Giovanni Brejc
 */

#include "../include/line.hpp"
#include <iostream>
#include <algorithm>

void Line::reverse_stations()
{

    std::vector<double> dis;

    for (int i = 0; i < stations.size(); i++)
        dis.push_back(stations.at(stations.size() - 1)->get_distance() - stations.at(stations.size() - 1 - i)->get_distance());

    reverse(stations.begin(), stations.end());

    for (int i = 0; i < stations.size(); i++)
        stations.at(i)->set_distance(dis.at(i));
}

void Line::depart_station(int index)
{
    for (int i = 1; i < stations.size(); i++)
    {
        if (i != stations.size() - 1)
            stations.at(i)->swap_train();

        if (!stations.at(i)->get_size())
            continue;

        if (!stations.at(i)->get_front()->get_stop())  //if stop == 0
        {
            if (i == stations.size() - 1 && stations.at(i)->get_size() > 0) //if last station
            {
                std::cout << "Train: " << stations.at(i)->get_front()->get_train_name() << " - Bye, Have a Great Time!" << std::endl;
                stations.at(i)->get_front().reset();
                stations.at(i)->remove_train();
                return;
            }

            if (trains.empty())  //if there are no trains moving
            {
                std::cout << "Train: " << stations.at(i)->get_front()->get_train_name() << " - departing from " << stations.at(i)->get_name() << " at minute " << index << std::endl;
                stations.at(i)->get_front()->set_velocity(1.3);
                trains.push_back(stations.at(i)->get_front());
                stations.at(i)->remove_train();
            }
            else
            {
                if (stations.at(i)->get_distance() > trains.front()->get_distance()) //checks if departing train is the furthest from origin station
                {
                    std::cout << "Train: " << stations.at(i)->get_front()->get_train_name() << " - departing from " << stations.at(i)->get_name() << " at minute " << index << std::endl;
                    stations.at(i)->get_front()->set_velocity(1.3);
                    trains.insert(trains.begin(), stations.at(i)->get_front());
                    stations.at(i)->remove_train();
                }
                else if (stations.at(i)->get_distance() < trains.back()->get_distance() && trains.back()->get_distance() - stations.at(i)->get_distance() >= 10) //checks if departing train is the closest to origin station
                {
                    std::cout << "Train: " << stations.at(i)->get_front()->get_train_name() << " - departing from " << stations.at(i)->get_name() << " at minute " << index << std::endl;
                    stations.at(i)->get_front()->set_velocity(1.3);
                    trains.insert(trains.end(), stations.at(i)->get_front());
                    stations.at(i)->remove_train();
                }
                else  
                    for (int j = 0; j < trains.size() - 1; j++)  //cycle to insert train in vector in the correct position
                        if (stations.at(i)->get_distance() > trains.at(j)->get_distance() && trains.at(j + 1)->get_distance() - stations.at(i)->get_distance() >= 10)
                        {
                            std::cout << "Train: " << stations.at(i)->get_front()->get_train_name() << " - departing from " << stations.at(i)->get_name() << " at minute " << index << std::endl;
                            stations.at(i)->get_front()->set_velocity(1.3);
                            trains.insert(trains.begin() + j + 1, stations.at(i)->get_front());
                            stations.at(i)->remove_train();
                            break;
                        }
            }
        }

        switch (stations.at(i)->get_size()) //decrease stop and increase delay if necessary
        {
        case 1:
            if (stations.at(i)->get_front()->get_stop() == 0)
                stations.at(i)->get_back()->increase_delay(1);
            stations.at(i)->get_front()->decrease_stop();
            break;
        case 2:
            stations.at(i)->get_front()->decrease_stop();
            if (stations.at(i)->get_back()->get_stop() == 0)
                stations.at(i)->get_back()->increase_delay(1);
            else
                stations.at(i)->get_back()->decrease_stop();
            break;
        default:
            break;
        }
    }
}

void Line::depart_deposit()
{
    for (int i = 1; i < stations.size(); i++) 
    {
        int size = 0;  // count the number of trains between the deposit and station, plus trains stopped in stations
        for (int j = 0; j < trains.size(); j++) 
        {
            if (trains.at(j)->get_distance() >= stations.at(i)->get_distance() - 5 && trains.at(j)->get_distance() <= stations.at(i)->get_distance())
                size++;
        }
        size += stations.at(i)->get_size();

        if (!stations.at(i)->is_full() && !stations.at(i)->get_deposit()->is_empty() && size < 2)  //if there are less than 2 trains in station and between station an deposit
        {                                                                                          //train can depart from deposit and approach station
            std::shared_ptr<Train> tr = stations.at(i)->get_deposit()->pop();                    
            if (trains.empty())
            {
                trains.push_back(tr);
                stations.at(i)->get_deposit()->add_delay();
                return;
            }
            else
            {
                if (tr->get_distance() < trains.back()->get_distance()) //checks if train is the closest from origin station
                    trains.insert(trains.end(), tr);
                else
                {
                    for (int j = 0; j < trains.size(); j++)  //cycle to insert train in vector in correct position    
                    {
                        if (tr->get_distance() > trains.at(j)->get_distance())
                        {
                            trains.insert(trains.begin() + j + 1, tr);
                            break;
                        }
                    }
                }
            }
        }
        stations.at(i)->get_deposit()->add_delay();
    }
}