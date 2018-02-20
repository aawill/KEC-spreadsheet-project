#include <iostream>
#include <string>
#include <fstream>

const int NUM_RESIDENTS = 21;
const std::string resNames[NUM_RESIDENTS] = {
    "Philip Stephen Garza", "Rohan Jalalizadeh", "Ryan P Lange",
    "Sarah Michelson", "Erik Sweet",
    "Megan Tuohy", "Eric John Weinlander",
    "Stephen Armenti", "Katherine Davis", "Michael Huvard",
    "Nathan William Anderson Liles", "Jason Miller",
    "Tapan Pinakin Patel", "Yu Cheng Zhao",
    "Tatiana Deveney", "Jr Joseph Grubbs", "Sean Hansen",
    "Tyson Kim", "Lev Prasov",
    "David Sanders", "Nakul Shekhawat",
};

class Resident {
public:
    Resident();
    // Requires: nameIn is a name in resNames[]
    //           percent is an int between 0 and 100 inclusive
    // Effects:  non-default constructor for Resident - sets member vars to inputs
    Resident(std::string nameIn, int percent);

    
    // Requires: nameIn is a name in resNames[]
    // Effects: sets member var name to input
    void setName(std::string nameIn);

    // Requires: percent is an int between 0 and 100 inclusive
    // Effects: sets member var percentWatched to input
    void setPercentWatched(int percent);

    // Effects: returns member var name
    std::string getName();

    // Effects: returns member var percentWatched
    int getPercentWatched();

private:
    std::string name;
    int percentWatched = 0;
};
