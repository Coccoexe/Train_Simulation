/**
 * @file deposit.hpp
 * @author Giovanni Brejc
 */

#ifndef deposit_hpp
#define deposit_hpp

#include "train.hpp"
#include <vector>
#include <stdexcept>
#include <memory>

class Deposit
{
private:
    /** @brief Fast queue. */ 
    std::vector<std::shared_ptr<Train>> fast;
    /** @brief Medium queue. */
    std::vector<std::shared_ptr<Train>> medium;
    /** @brief Slow queue. */
    std::vector<std::shared_ptr<Train>> slow;

public:
    /**
     * @brief Construct a mt deposit, with priority.
     */
    Deposit() : fast(), medium(), slow() {}

    /**
     * @brief 
     * 
     */
    bool is_empty();
    /**
     * @brief Adds incoming train to the deposit.
     * 
     * @param t Train to deposit.
     */
    void push(std::shared_ptr<Train> p);
    /**
     * @brief Removes highest priority train from the deposit
     * 
     * @return Train* that leaves the deposit.
     */
    std::shared_ptr<Train> pop();
    /**
    * @brief add delay to train in deposit
    * 
    */
    void add_delay();
};

#endif