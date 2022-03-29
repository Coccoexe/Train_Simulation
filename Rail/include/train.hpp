/**
 * @file train.hpp
 * @author Alessio Cocco - 1219609 (alessio.cocco@studentiunipd.it)
 */

#ifndef train_hpp
#define train_hpp

#include <vector>

/**
 * @class Train
 * @brief base class Train
*/
class Train
{
protected:
    const int train_number;                 //train name
    double velocity_curr;                   //current velocity
    const double velocity_max;              //max velocity
    double distance;                        //distance done
    const int direction;                    //direction, 0 for left-right, 1 for right-left
    int delay = 0;                          //delay
    std::vector<double> expected_times;     //estimated arrival times
    int stations_done = 0;                  //passed stations
    int stop = 0;                           //minute trains stop in stations
    bool deposit = false;                   //true if must stop in next deposit

public:
    /**
     * @brief Construct a new Train object
     * 
     * @param max_v velocity_max
     * @param dir   direction
     * @param num   train_number
     * @param t     vector of expected_times
     */
    Train(double max_v, int dir, int num, std::vector<double> t);

    //get functions
    /**
     * @brief Get the train name
     * 
     * @return int 
     */
    inline int get_train_name() const { return train_number; }
    /**
     * @brief Get the velocity
     * 
     * @return double 
     */
    inline double get_velocity_curr() const { return velocity_curr; }
    /**
     * @brief Get the velocity max
     * 
     * @return double 
     */
    inline double get_velocity_max() const { return velocity_max; }
    /**
     * @brief Get the distance
     * 
     * @return double 
     */
    inline double get_distance() const { return distance; }
    /**
     * @brief Get the direction
     * 
     * @return int 
     */
    inline int get_direction() const { return direction; }
    /**
     * @brief Get the delay
     * 
     * @return int 
     */
    inline int get_delay() const { return delay; }
    /**
     * @brief Get the expected time at index
     * 
     * @param index 
     * @return double 
     */
    inline double get_expected_time(int index) const { return expected_times.at(index); }
    /**
     * @brief Get the number of stations done
     * 
     * @return int 
     */
    inline int get_stations_done() const { return stations_done; }
    /**
     * @brief Get minute train must stop
     * 
     * @return int 
     */
    inline int get_stop() const { return stop; }
    /**
     * @brief Get the deposit status
     * 
     * @return true 
     * @return false 
     */
    inline bool get_deposit() { return deposit; }

    //set functions
    /**
     * @brief Set the velocity
     * 
     * @param v 
     */
    inline void set_velocity(double v) { velocity_curr = v; }
    /**
     * @brief Set the distance
     * 
     * @param d 
     */
    inline void set_distance(double d) { distance = d; }
    /**
     * @brief Set the stop
     * 
     * @param s 
     */
    inline void set_stop(int s) { stop = s; }
    /**
     * @brief Set the deposit status
     * 
     * @param b 
     */
    inline void set_deposit(bool b) { deposit = b; }

    //increase & decrease functions
    /**
     * @brief increase delay of train
     * 
     * @param l 
     */
    inline void increase_delay(int l) { delay += l; }
    /**
     * @brief increase the number of stations done
     * 
     */
    inline void increase_stations_done() { stations_done++; }
    /**
     * @brief decrease stop left
     * 
     */
    inline void decrease_stop() { (stop <= 1) ? stop = 0 : stop--; }

    //cout functions
    /**
     * @brief print all train stuffs
     */
    void print() const;
    
    
    
};

/**
 * @class of a Fast Train
 * @see class Train
 */
class Fast_Train : public Train
{
public:
    /**
     * @brief Construct a new Fast_Train object
     * 
     * @param d direction
     * @param n number
     * @param t expected times
     */
    Fast_Train(int d, int n, std::vector<double> t) : Train(5, d, n, t) {}
};

/**
 * @class of a Medium Train
 * @see class Train
 */
class Medium_Train : public Train
{
public:
    /**
     * @brief Construct a new Medium_Train object
     * 
     * @param d direction
     * @param n number
     * @param t expected times
     */
    Medium_Train(int d, int n, std::vector<double> t) : Train(4, d, n, t) {}
};

/**
 * @class of a Slow Train
 * @see class Train
 */
class Slow_Train : public Train
{
public:
    /**
     * @brief Construct a new Slow_Train object
     * 
     * @param d direction
     * @param n number
     * @param t expected times
    */
    Slow_Train(int d, int n, std::vector<double> t) : Train(2.7, d, n, t) {}
};

#endif
