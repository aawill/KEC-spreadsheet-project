#include "Resident.h";
using namespace std;

Resident::Resident() {
    name = "John Doe";
    percentWatched = 0;
}

Resident::Resident(string nameIn, int percent) {
    name = nameIn;
    percentWatched = percent;
}

void Resident::setName(string nameIn) {
    name = nameIn;
    return;
}

void Resident::setPercentWatched(int percent) {
    percentWatched = percent;
    return;
}

string Resident::getName() {
    return name;
}

int Resident::getPercentWatched() {
    return percentWatched;
}