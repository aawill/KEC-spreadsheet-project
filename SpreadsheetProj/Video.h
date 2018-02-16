#include <iostream>
#include <string>
#include <fstream>
#include "Resident.h"



class Video {
public:
    //Default constructor
    Video();
    //Non-default constructor
    Video(std::string title_in);

    void setTitle(std::string title_in);
    std::string getTitle();

    //Creates an array of residents for this video, fills in names
    void initResidents(const std::string names[NUM_RESIDENTS]);

    //Returns the resident at a given index in the array
    Resident *(getResident(int index));

private:
    Resident residents[NUM_RESIDENTS];
    std::string title;
};
