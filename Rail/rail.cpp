/**
 * @file main.cpp
 * @authors Alessio Cocco, Andrea Valentinuzzi, Giovanni Brejc
 * @brief Just some fancy comments explaining stuff and setup of the train line.
 *  
 */

#include "include/line.hpp"

int main()
{
    // Line setup, will take care of itslef for inputs and simulation.
    Line segmentation_fault;
    return 0;
}

/** @author Andrea Valentinuzzi :)

| ----------------------------------------------------------------------------------- |
|                  _                          __  ___                                 |
|    ___ ____ ___ (_)__ ____  __ _  ___ ___  / /_|_  |                                |
|   / _ `(_-<(_-</ / _ `/ _ \/  ' \/ -_) _ \/ __/ __/                                 |
|   \_,_/___/___/_/\_, /_//_/_/_/_/\__/_//_/\__/____/                                 |
|                 /___/                                                               |
|                                                                                     |
|                    _-====-__-======-__-========-_____-============-__               |
|                  _(                                                 _)              |
|               OO(     Alessio Cocco               Giovanni Brejc    )_              |
|              0  (_               Andrea Valentinuzzi                 _)             |
|            o0     (_                                                _)              |
|           o         '=-___-===-_____-========-___________-===-dwb-='                |
|         .o                                _________                                 |
|        . ______          ______________  |         |      _____                     |
|      _()_||__|| ________ |            |  |_________|   __||___||__                  |
|     (BNSF 1995| |      | |            | __Y______00_| |_         _|                 |
|    /-OO----OO""="OO--OO"="OO--------OO"="OO-------OO"="OO-------OO"=P               |
|   #####################################################################             |
|                                                                                     |
| ----------------------------------------------------------------------------------- |
|                                                                                     |
|     __ _ _               _                   _                                      |
|    / _(_) | ___  ___ ___| |_ _ __ _   _  ___| |_ _   _ _ __ ___                     |
|   | |_| | |/ _ \/ __/ __| __| '__| | | |/ __| __| | | | '__/ _ \                    |
|   |  _| | |  __/\__ \__ \ |_| |  | |_| | (__| |_| |_| | | |  __/                    |
|   |_| |_|_|\___||___/___/\__|_|   \__,_|\___|\__|\__,_|_|  \___|                    |
|                                                                                     |
|                       ----------                                                    |
|                      | main.cpp |                                                   |
|                       ----------                                                    |
|                           ˅˅              **********************************        |
|                       ----------          * line.hpp    : line.cpp         *        |
|          ˂˂˂˂˂˂˂˂˂˂˂ | line.hpp |         *               line_input.cpp   *        |
|         ˅˅            ----------          *               line_train.cpp   *        |
|         ˅˅                ˅˅              *               line_station.cpp *        |
|    -----------       -------------        * station.hpp : station.cpp      *        |
|   | train.hpp | ˂˂˂ | station.hpp |       * deposit.hpp : deposit.cpp      *        |
|    -----------       -------------        * train.hpp   : train.cpp        *        |
|         ˄˄                ˅˅              **********************************        |
|         ˄˄           -------------                                                  |
|          ˂˂˂˂˂˂˂˂˂˂ | deposit.hpp |                                                 |
|                      -------------                                                  |
|                                                                                     |
| ----------------------------------------------------------------------------------- |
|                                                                                     |
|                  _      _             _                                             |
|     ___ ___   __| | ___| | ___   __ _(_) ___                                        |
|    / __/ _ \ / _` |/ _ \ |/ _ \ / _` | |/ __|                                       |
|   | (_| (_) | (_| |  __/ | (_) | (_| | | (__                                        |
|    \___\___/ \__,_|\___|_|\___/ \__, |_|\___|                                       |
|                                 |___/                                               |
|                                                                                     |
|   Creation of a Line object that contains:                                          |
|    - std::vector of std::shared_ptr to Stations.                                    |
|    - std::vector of std::shared_ptr to Trains.                                      |
|                                                                                     |
|   Filling said vectors with data from timetables.txt & line_description.txt:        |
|    - stations closer than 20km are eliminated (& corresponding times).              |
|    - times not compatible with [distance / train speed + factors] are modified.     |
|                                                                                     |
|   The simulation starts and is executed twice (one per direction):                  |
|    - it consists of a loop that goes on until all trains reach EOL. :(              |
|    - the first step of a loop cycle is updating the position of each train          |
|       taking into consideration their speed.                                        |
|    - every minute various conditions are checked in order to allow                  |
|       take-overs, entrance in deposit, wait inside deposit or station.              |
|    - train delays get updated and communication happens between trains & stations.  |
|                                                                                     |
| ----------------------------------------------------------------------------------- |

*/