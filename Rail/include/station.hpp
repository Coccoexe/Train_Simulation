/**
 * @file station.hpp
 * @author Giovanni Brejc
 */

#ifndef station_hpp
#define station_hpp

#include "deposit.hpp"
#include <string>

class Station
{
protected:
    std::string name; //station name
    double distance;  //station distance
    bool local; //station type
    std::vector<std::shared_ptr<Train>> rail; //station rails
    std::shared_ptr<Deposit> deposit;         //station deposit

public:
    /**
     * @brief Construct a new Station object
     * 
     * @param n name
     * @param d distance
     * @param type station type
     */
    Station(std::string n, double d, bool type);

    inline void set_distance(double dis) { distance = dis; }
    inline std::string get_name() const { return name; }
    inline double get_distance() const { return distance; }
    inline void set_main() { local = false; } //extreme case
    inline bool is_local() const { return local; }
     /**
     * @brief prints stations information
     * 
     */
    void print() const;

     /**
     * @brief checks if rails are full
     * 
     */
    inline bool is_full() const { return rail.size() == 2; }

     /**
     * @brief add train to rail
     * 
     */
    inline void add_rail(const std::shared_ptr<Train> p) { rail.push_back(p); }
     /**
     * @brief remvoes train from rail
     * 
     */
    inline void remove_train() { rail.erase(rail.begin()); }
     /**
     * @brief returns how many trains on rails
     * 
     */
    inline int get_size() { return rail.size(); }
     /**
     * @brief returns next train to depart
     * 
     */
    inline std::shared_ptr<Train> get_front() { return rail.front(); }
     /**
     * @brief returns the other train
     * 
     */
    inline std::shared_ptr<Train> get_back() { return rail.back(); }
     /**
     * @brief puts in front the train that is supposed to depart first
     * 
     */
    void swap_train();

     /**
     * @brief returns stations deposit
     * 
     */
    inline std::shared_ptr<Deposit> get_deposit() { return deposit; }
};

 
class Main_Station : public Station
{
public:
    Main_Station(std::string n, double d) : Station(n, d, false) {}
};

class Local_Station : public Station
{
public:
    Local_Station(std::string n, double d) : Station(n, d, true) {}
};

#endif