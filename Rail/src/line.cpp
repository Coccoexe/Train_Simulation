/**
 * @file line.cpp
 * @authors Alessio Cocco, Andrea Valentinuzzi, Giovanni Brejc
 * 
 */

#include "../include/line.hpp"
#include <fstream>                // output.txt
#include <iostream>               // yes

Line::Line()
{
    // station initialization
    vector_stations();
    std::cout << "> Stations Input OK" << std::endl;

    // train initialization
    vector_trains();
    std::cout << "> Trains Input OK" << std::endl;

    // security measure, otherwise trains wouldn't despawn
    stations.back()->set_main();

    // print more, more, more!
    std::cout << std::endl;
    print_stations();
    print_trains();

    sim();
}

bool Line::continue_sim() const
{
    if(!trains.empty())
        return true;
    if(!line.empty())
        return true;
    for(int i = 0; i < stations.size(); i++)
    {
        if(stations.at(i)->get_size())
            return true;
        if(!stations.at(i)->get_deposit()->is_empty()) 
            return true;   
    }
    
    return false;
}

void Line::sim()
{
    std::cout << std::endl
              << "     _                 _       _   _                 " << std::endl
              << " ___(_)_ __ ___  _   _| | __ _| |_(_) ___  _ __      " << std::endl
              << "/ __| | '_ ` _ \\| | | | |/ _` | __| |/ _ \\| '_ \\  " << std::endl
              << "\\__ \\ | | | | | | |_| | | (_| | |_| | (_) | | | |  " << std::endl
              << "|___/_|_| |_| |_|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|" << std::endl
              << std::endl;

    sort_trains();
    divide_trains();

    // resetting output.txt file
    std::ofstream of("output.txt");
    of << " ---------- SIMULATION ----------" << std::endl
       << "This simulation is NOT meant to be 100% accurate, instead it gives an APPROXIMATE snapshot of the train line." << std::endl
       << "Still, it's useful when debugging. :)" << std::endl
       << std::endl;
    of.close();

    // simulation direction 0, 2880 minutes = 2 days as time limit.
    for (int minute = 0; minute < 2880 && continue_sim(); minute++)
    {
        // update position and velocity train
        update_velocity();
        update_position(minute);

        // stations
        depart_station(minute);
        depart_deposit();

        // departure
        departure_next_train(minute);
        sort_trains();
        
        fancy_cout();
    }
    std::cout << std::endl
              << " ----- simulation direction 0 OK ----- " << std::endl
              << std::endl;

    // cleaning, just to be safe
    trains.clear();
    // backwards
    reverse_stations();
    // cleaning, just to be safe
    line.clear();
    // trains that have direction 1
    line = tmp;

    // simulation direction 1, 2880 minutes = 2 days as time limit.
    for (int minute = 0; minute < 2880 && continue_sim(); minute++)
    {
        // update position and velocity train
        update_velocity();
        update_position(minute);

        // stations
        depart_station(minute);
        depart_deposit();

        // departure
        departure_next_train(minute);
        sort_trains();

        fancy_cout();
    }
    std::cout << std::endl
              << " ----- simulation direction 1 OK ----- " << std::endl
              << std::endl;
}
