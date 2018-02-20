#include <iostream>
#include <string>
#include <fstream>
#include "Resident.h"



class Video {
public:
    Video();

    // Requires: title_in is a valid video title as seen in spreadsheets - 
    //           e.g. "Comer 1a", "Fahim 1b", etc
    // Effects: non-default constructor for Video - sets member var title to input
    Video(std::string title_in);

    // Requires: title_in is a valid video title as seen in spreadsheets - 
    //           e.g. "Comer 1a", "Fahim 1b", etc
    // Effects: non-default constructor for Video - sets member var title to input
    void setTitle(std::string title_in);

    // Effects: returns member var title
    std::string getTitle();

    // Requires: names[] is a list of all current residents, as formatted in Canvas analytics
    // Effects: initializes names in member array residents[] to input names
    void initResidents(const std::string names[NUM_RESIDENTS]);

    // Effects: Returns the resident at a given index in member array residents[]
    Resident *(getResident(int index));

private:
    Resident residents[NUM_RESIDENTS];
    std::string title;
};
