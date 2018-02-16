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

    Resident(std::string nameIn, int percent);

    void setName(std::string nameIn);
    void setPercentWatched(int percent);

    std::string getName();
    int getPercentWatched();

private:
    std::string name;
    int percentWatched = 0;
};
