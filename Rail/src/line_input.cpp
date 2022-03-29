/**
 * @file line_input.cpp
 * @author Andrea Valentinuzzi
 * @brief void Line::vector_trains() \n
 *        void Line::vector_stations() \n
 *        void Line::print_stations() const \n
 *        void Line::print_trains() const \n
 *        void Line::fancy_cout() const
 * 
 */

#include "../include/line.hpp"
#include <fstream>
#include <cmath>
#include <iostream>

void Line::vector_trains()
{
    // fancy stuff :)
    std::cout << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "**   TRAINS INPUT   **" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "|" << std::endl;

    // input stream and prepared string
    std::ifstream filett("input/timetables.txt");
    std::string t;

    // trains input
    while (!filett.eof())
    {
        // saving single line to string
        std::getline(filett, t);

        // basic substring usage to save data
        int train_number = stoi(t.substr(0, t.find(' ')));
        int train_direction = stoi(t.substr(t.find(' ') + 1, 1));
        int train_type = stoi(t.substr(t.find(' ') + 3, 1));

        // updating input string, now containing only times
        t = t.substr(t.find(' ') + 5);
        std::vector<double> train_times;

        // need to save converted train velocity for later checks
        double train_velocity_km_min;
        switch (train_type)
        {
        case 1:
            train_velocity_km_min = 2.7; // 160/60
            break;
        case 2:
            train_velocity_km_min = 4; // 240/60
            break;
        case 3:
            train_velocity_km_min = 5; // 300/60
            break;
        }

        // saving all times from the string
        while (!t.empty())
        {
            if (t.find(' ') == std::string::npos)
            {
                train_times.push_back(stod(t));
                break;
            }
            train_times.push_back(stod(t.substr(0, t.find(' '))));
            t = t.substr(t.find(' ') + 1);
        }

        // adding times (== 0) that will be automatically corrected later
        for (int i = train_times.size(); i < stations.size() + time_to_remove.size(); i++)
            train_times.push_back(0);

        // WILL contain correct times
        std::vector<double> correct_times;

        // SLOW TRAIN
        if (train_type == 1)
        {
            int j = 0;

            // adjusting for removed stations
            for (int i = 0; i < j + stations.size() && i <= train_times.size(); i++)
            {
                // skips current time value if corresponding station was removed
                if (j < time_to_remove.size())
                    if (i == time_to_remove.at(j))
                    {
                        j++;
                        continue;
                    }
                // otherwise pushes the time inside correct_times
                correct_times.push_back(train_times.at(i));
            }

            // adjusting for min times
            for (int i = 1; i < correct_times.size(); i++)
            {
                // calculating correct approx time for each direction
                // 7.5 = 10/80/60
                double approx_time;
                if (!train_direction)
                    approx_time = correct_times.at(i - 1) + 5 + 7.5 +
                                  (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance() - 10) / train_velocity_km_min;
                else
                    approx_time = correct_times.at(i - 1) + 5 + 7.5 +
                                  (stations.at(correct_times.size() - i)->get_distance() - stations.at(correct_times.size() - i - 1)->get_distance() - 10) / train_velocity_km_min;

                // small correction
                if (i == 1)
                    approx_time = approx_time - 5;

                // modifying time
                if (correct_times.at(i) < approx_time)
                {
                    std::cout << "Modified time for station: " << i << " from " << correct_times.at(i) << " to " << approx_time << std::endl;
                    correct_times.at(i) = ceil(approx_time);
                }
            }
        }
        // MEDIUM AND FAST TRAIN
        else
        {
            // creating vector of main_indexes
            std::vector<int> main_indexes;
            for (int i = 0; i < stations.size(); i++)
                if (!stations[i]->is_local())
                    main_indexes.push_back(i);

            int j = 0;

            // adjusting for removed stations
            for (int i = 0; i < main_indexes.size() && i <= train_times.size(); i++)
            {
                // skips current time value if corresponding station was removed
                if (j < time_to_remove_main.size())
                    if (i == time_to_remove_main.at(j))
                    {
                        j++;
                        continue;
                    }
                // otherwise pushes the time inside correct_times
                correct_times.push_back(train_times.at(i));
            }

            // adjusting for min times
            for (int i = 1; i < correct_times.size(); i++)
            {
                // calculating correct approx time for each direction
                // 7.5 = 10/80/60
                double approx_time;
                if (!train_direction)
                    approx_time = correct_times.at(i - 1) + 5 + 7.5 +
                                  (stations.at(main_indexes.at(i))->get_distance() - stations.at(main_indexes.at(i - 1))->get_distance() - 10) / train_velocity_km_min;
                else
                    approx_time = correct_times.at(i - 1) + 5 + 7.5 +
                                  (stations.at(main_indexes.at(correct_times.size() - i))->get_distance() - stations.at(main_indexes.at(correct_times.size() - i - 1))->get_distance() - 10) / train_velocity_km_min;

                // small correction
                if (i == 1)
                    approx_time = approx_time - 5;

                // modifying time
                if (correct_times.at(i) < approx_time)
                {
                    std::cout << "Modified time for station: " << i << " from " << correct_times.at(i) << " to " << approx_time << std::endl;
                    correct_times.at(i) = ceil(approx_time);
                }
            }
        }

        // pushing train correctly inside trains vector
        if (train_type == 1)
        {
            std::shared_ptr<Train> tr{new Slow_Train(train_direction, train_number, correct_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Slow train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        else if (train_type == 2)
        {
            std::shared_ptr<Train> tr{new Medium_Train(train_direction, train_number, correct_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Medium train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        else
        {
            std::shared_ptr<Train> tr{new Fast_Train(train_direction, train_number, correct_times)};
            trains.push_back(std::move(tr));
            std::cout << "constructed Fast train: " << train_number << " - dir: " << train_direction << std::endl;
        }
        std::cout << std::endl;
    }

    // end of input stream
    filett.close();
}

void Line::vector_stations()
{
    // fancy stuff :)
    std::cout << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "**  STATIONS INPUT  **" << std::endl;
    std::cout << "**********************" << std::endl;
    std::cout << "|" << std::endl;

    // input stream and prepared string
    std::ifstream fileld("input/line_description.txt");
    std::string s;

    // first station has only name
    std::getline(fileld, s);
    std::shared_ptr<Station> foo{new Main_Station(s, 0)};
    stations.push_back(std::move(foo));

    // stuff
    double distance_old = 0.0;
    int remove = 1;

    // other stations input
    while (!fileld.eof())
    {
        // saving single line to string
        std::getline(fileld, s);

        // basic substring usage to save data
        double station_distance = stod(s.substr(s.rfind(' ')));
        int station_type = stoi(s.substr(s.rfind(' ') - 1, 1));
        std::string station_name = s.substr(0, s.rfind(' ') - 2);

        // if distance from last station < 20, current station is eliminated and its index is saved for later
        if (station_distance - distance_old < 20)
        {
            if (station_type == 0)
                time_to_remove_main.push_back(remove);
            time_to_remove.push_back(remove++);
            std::cout << "Station at " << station_distance << " km removed...distance from previous was less than 20 km" << std::endl;
            continue;
        }

        // updating distance_old
        distance_old = station_distance;

        // creating station main
        if (station_type == 0)
        {
            std::shared_ptr<Station> foo{new Main_Station(station_name, station_distance)};
            stations.push_back(std::move(foo));
        }

        // creating station local
        else if (station_type == 1)
        {
            std::shared_ptr<Station> foo{new Local_Station(station_name, station_distance)};
            stations.push_back(std::move(foo));
        }

        // updating remove index
        remove++;
    }

    // end of input stream
    fileld.close();
}

void Line::print_stations() const
{
    std::cout << std::endl
              << "     _        _   _                     " << std::endl
              << " ___| |_ __ _| |_(_) ___  _ __  ___     " << std::endl
              << "/ __| __/ _` | __| |/ _ \\| '_ \\/ __|  " << std::endl
              << "\\__ \\ || (_| | |_| | (_) | | | \\__ \\" << std::endl
              << "|___/\\__\\__,_|\\__|_|\\___/|_| |_|___/" << std::endl
              << std::endl;

    // calling built-in member function
    for (int i = 0; i < stations.size(); i++)
        stations.at(i)->print();
}

void Line::print_trains() const
{
    std::cout << std::endl
              << " _             _               " << std::endl
              << "| |_ _ __ __ _(_)_ __  ___     " << std::endl
              << "| __| '__/ _` | | '_ \\/ __|   " << std::endl
              << "| |_| | | (_| | | | | \\__ \\  " << std::endl
              << " \\__|_|  \\__,_|_|_| |_|___/  " << std::endl
              << std::endl;

    // calling built-in member function
    for (int i = 0; i < trains.size(); i++)
        trains.at(i)->print();
}

//                                                           //
//      ____                                            __   //
//     / __/___ _____  _______  __    _________  __  __/ /_  //
//    / /_/ __ `/ __ \/ ___/ / / /   / ___/ __ \/ / / / __/  //
//   / __/ /_/ / / / / /__/ /_/ /   / /__/ /_/ / /_/ / /_    //
//  /_/  \__,_/_/ /_/\___/\__, /____\___/\____/\__,_/\__/    //
//                       /____/_____/                        //
//                                                           //
void Line::fancy_cout() const
{
    // This member functions is NOT meant to be 100% accurate, instead it gives an APPROXIMATE snapshot of the train line.
    // Still, it's useful when debugging. :)

    // output stream in append mode
    std::ofstream of("output.txt", std::ios_base::app);
    of << std::endl;

    // STATIONS
    of << "s: " << '0';
    for (int i = 1; i < stations.size(); i++)
    {
        for (int j = 0; j < (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance()) / 5; j++)
            of << '-';
        of << i;
    }
    of << std::endl;

    // TRAVELLING TRAINS
    of << "t: ";
    if (trains.size())
    {
        // first train
        for (int i = 1; i < (trains.at(trains.size() - 1)->get_distance()) / 5; i++)
            of << ' ';
        of << trains.at(trains.size() - 1)->get_train_name();

        // other trains
        if (trains.size() > 1)
            for (int i = trains.size() - 2; i >= 0; i--)
            {
                for (int j = 1; j < (trains.at(i)->get_distance() - trains.at(i + 1)->get_distance()) / 5; j++)
                    of << ' ';
                of << trains.at(i)->get_train_name();
            }
    }
    of << std::endl;

    // INSIDE STATION OR DEPOSIT
    of << "p: " << ' ';
    for (int i = 1; i < stations.size(); i++)
    {
        for (int j = 1; j < (stations.at(i)->get_distance() - stations.at(i - 1)->get_distance()) / 5; j++)
            of << ' ';

        // deposit
        if (stations.at(i)->get_deposit()->is_empty())
            of << ' ';
        else
            of << 'd';

        // station
        if (!stations.at(i)->get_size())
            of << ' ';
        else
            of << 'p';
    }
    of << std::endl;

    of.close();
}