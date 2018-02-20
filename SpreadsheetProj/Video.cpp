#include "Video.h";

using namespace std;

Video::Video() {
    title = "default title";
}

Video::Video(string title_in) {
    title = title_in;
}

void Video::setTitle(string title_in) {
    title = title_in;
    return;
}

string Video::getTitle() {
    return title;
}

void Video::initResidents(const string names[NUM_RESIDENTS]) {
    for (int i = 0; i < NUM_RESIDENTS; ++i) {
        residents[i].setName(names[i]);
    }
}

Resident *(Video::getResident(int index)) {
    return &(residents[index]);
}