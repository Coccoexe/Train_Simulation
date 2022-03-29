#ifndef line_hpp
#define line_hpp

/**
 * @file line.hpp
 * @authors Alessio Cocco, Andrea Valentinuzzi, Giovanni Brejc
 * @brief Line object, containing all trains and stations required to run the simulation, and the simulation itself.
 * 
 */

#include <memory>         // smart pointers
#include <vector>         // vectors
#include "station.hpp"
#include "train.hpp"

class Line
{
private:
    /** @brief Vector containing all stations. */
    std::vector<std::shared_ptr<Station>> stations;
    /** @brief Vector containing all trains. */
    std::vector<std::shared_ptr<Train>> trains;
    /** @brief Vector contatining trains waiting for departure. */
    std::vector<std::shared_ptr<Train>> line;
    /** @brief Vector contatining train waiting for the second simulation (backwards). */
    std::vector<std::shared_ptr<Train>> tmp;
    /** @brief Vector containing indexes of removed stations. */
    std::vector<int> time_to_remove;
    /** @brief Vector containing indexes of removed main stations. */
    std::vector<int> time_to_remove_main;

public:

    /**
     * @brief Construct a new Line object.
     */
    Line();
    /**
     * @brief Actual simulation.
     */
    void sim();
    bool continue_sim() const;

    /// Andrea Valentinuzzi
    /**
     * @brief Manages input file: timetables.txt. \n
     *        Trains are recognized and put inside the trains vector. \n
     *        There is need to remove times of removed stations. \n
     *        Times not compatible with [distance / train speed + factors] are modified.
     */
    void vector_trains();
    /**
     * @brief Manages input file: line_description.txt. \n
     *        Stations are recognized and put inside the stations vector. \n
     *        Stations too close to their previous (< 20km) are removed and thei indexes saved for later use.
     */
    void vector_stations();
    /**
     * @brief Just a recap cout for created trains.
     */
    void print_trains() const;
    /**
     * @brief Just a recap cout for created stations.
     */
    void print_stations() const;
    /**
     * @brief A fancy way to check each train's position every minute. \n
     *        Output stored in output.txt.
     * @note ** This member functions is NOT meant to be 100% accurate, instead it gives an APPROXIMATE snapshot of the train line. ** \n
     *       Still, it's useful when debugging. :)
     */
    void fancy_cout() const;

    /// Alessio Cocco
    /**
     * @brief sort train by departure time
     */
    void sort_trains();
    /**
     * @brief divide trains in vector line and tmp
     */
    void divide_trains();
    /**
     * @brief update velocity of all departed trains
     */
    void update_velocity();
    /**
     * @brief update distance of all departed trains
     * @param index the actual minute of sim
     */
    void update_position(int index);
    /**
     * @brief let depart next train
     * @param index the actual minute of sim
     */
    void departure_next_train(int index);

    /// Giovanni Brejc
    /**
     * @brief let depart next train from station
     * 
     * @param index 
     */
    void depart_station(int index);
    /**
     * @brief let depart next train from deposit
     */
    void depart_deposit();
    /**
     * @brief inverts the line. Last station becomes starting station with its distance = 0
     *              
     */
    void reverse_stations();
    
};

#endif
