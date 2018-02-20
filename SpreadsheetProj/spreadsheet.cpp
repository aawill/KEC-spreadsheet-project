#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Video.h"
#include "Shlobj.h"

using namespace std;

// Requires: title_in is a valid video title as seen in spreadsheets - 
//           e.g. "Comer 1a", "Fahim 1b", etc
// Effects: Adds a video to the end of vids, with title set to input title
void addVideo(vector<Video> &vids, string title);

// Requires: ins points to a .csv file containing existing engagement data,
//           vids is empty
// Effects: populates vids with Videos for each name read in from the first column of ins.
//          each Video is initialized with an array of Residents, with percentWatched values
//          corresponding to the data from ins. this function prepares the Videos for 
//          comparison to new data.
void initVideos(vector<Video> &vids, ifstream &ins);

// Effects: returns true if given name is found in resNames, changes index to its location
bool isResident(string name, int &index);

// Effects: returns true if title is a Video title in vids, changes index to its location
bool isVideo(string title, vector<Video> &vids, int &index);

// Requires: filepath is the path to the user's desktop
// Effects: returns true if user enters valid video name, 
//          appends the user-selected video to filepath
bool getVidFile(vector<Video> &vids, int &vidIndex, string &filepath);

// Requires: ins points to a .csv file containing new analytics data for one video
//           vids has been initialized with initVideos
//           vidIndex is within the bounds of vids
// Effects: reads the file from ins and tells the user which residents' watch
//          percentages have changed for that video
void readVidFile(ifstream &ins, vector<Video> &vids, int &vidIndex);

// Effects: returns the path of the user's desktop
string GetDesktopfilePath(PTCHAR filePathIn);

// Effects: prints welcome message and instructions
void printWelcome();

int main() {
    int vidIndex;
    vector<Video> videos;
    string vidFile, dataFile, resName, trash, percent;
    ifstream dataIn, vidIn;
    TCHAR filepath[MAX_PATH];
    string fullPath = GetDesktopfilePath(filepath);
    
    printWelcome();
    cout << "Enter data spreadsheet filename, or 'quit': ";
    // gets the old engagement data file from user
    while (getline(cin, dataFile)) {
        if (dataFile == "quit") {
            system("pause");
            exit(0);
        }
        dataFile = fullPath + "\\" + dataFile + ".csv";
        dataIn.open(dataFile);
        if (!dataIn.is_open()) cout << "Invalid filename, please try again: ";
        else break;
    }
    // initializes video list based on old data file
    initVideos(videos, dataIn);
    // main driver loop: checks videos specified by user, displays necessary changes
    while (true) {
        fullPath = GetDesktopfilePath(filepath);
        if (getVidFile(videos, vidIndex, fullPath)) {
            vidIn.open(fullPath);
            if (vidIn.is_open()) readVidFile(vidIn, videos, vidIndex);
            else cout << "Not found - make sure .csv file is on desktop!" << endl;
            vidIn.close();
        }
    }
    dataIn.close(); 
    return 0;
}

void printWelcome() {
    cout << "------------------------------------------" << endl
         << "Welcome to the KEC Podcast Analytics Tool!" << endl
         << "------------------------------------------" << endl
         << "Please make sure all your files are located on" << endl
         << "the desktop in .csv format. Note that input is case-sensitive." << endl << endl;
}

string GetDesktopfilePath(PTCHAR filePathIn) {
    // Get the full path of the desktop
    SHGetFolderPath(NULL,
        CSIDL_DESKTOPDIRECTORY | CSIDL_FLAG_CREATE,
        NULL,
        SHGFP_TYPE_CURRENT,
        filePathIn);
    string filePath = filePathIn;
    return filePath;
}

void readVidFile(ifstream &ins, vector<Video> &vids, int &vidIndex) {
    string trash, resName, percent;
    int resIndex;
    bool changes = false;

    // gets rid of "user", "view drop-off" line
    getline(ins, trash);
    // reads through every line of file, assigning first column values to resName
    while (getline(ins, resName, ',')) {
        // removes quotes 
        resName = resName.substr(1, (resName.length() - 2));
        // second column into percent
        getline(ins, percent, '\n');
        percent = percent.substr(1, (percent.length() - 2));
        // checks if resName is a resident, not faculty/etc. 
        if (isResident(resName, resIndex)) {
            // checks if watch percentage has changed
            if (vids[vidIndex].getResident(resIndex)->getPercentWatched() != stoi(percent)) {
                cout << "Change " << resName << "'s watch percentage to " << percent << endl;
                changes = true;
            }
        }
    }
    if (!changes) cout << "No changes to make" << endl;
}

bool getVidFile(vector<Video> &vids, int &vidIndex, string &filepath) {
    string input;
    cout << "Enter video to check (e.g. 'Comer 1a'), or 'quit': ";
    getline(cin, input);
    if (input == "quit") {
        system("pause");
        exit(0);
    }
    // checks if user input is a possible video
    if (!isVideo(input, vids, vidIndex)) {
        cout << "Invalid video name" << endl;
        return false;
    }
    // formats input as file path
    filepath += "\\" + input + ".csv";
    return true;
}

bool isVideo(string title, vector<Video> &vids, int &index) {
    for (int i = 0; i < vids.size(); ++i) {
        if (vids[i].getTitle() == title) {
            index = i;
            return true;
        }
    }
    return false;
}

bool isResident(string name, int &index) {
    for (int i = 0; i < NUM_RESIDENTS; ++i) {
        if (resNames[i] == name) {
            index = i;
            return true;
        }
    }
    return false;
}

void initVideos(vector<Video> &vids, ifstream &ins) {
    char charTrash;
    string vidName, trash;
    int percentWatched;
    // gets rid of trash data (sheet info, years, names, etc)
    getline(ins, trash);
    getline(ins, trash);
    int index = 0;
    // fills vids with videos from existing data sheet
    while (getline(ins, vidName, ',')) {
        addVideo(vids, vidName);
        vids[index].initResidents(resNames);
        // fills watch percentages
        for (int i = 0; i < NUM_RESIDENTS; ++i) {
            ins >> percentWatched;
            if (i != NUM_RESIDENTS - 1) ins >> charTrash;
            // last column
            else getline(ins, trash, '\n');
            vids[index].getResident(i)->setPercentWatched(percentWatched);
        }
        ++index;
    }
    // gives user list of videos present in old sheet
    cout << "VIDEOS TO CHOOSE FROM:" << endl;
    for (int i = 0; i < vids.size(); ++i) {
        cout << vids[i].getTitle() << endl;
    }
}

void addVideo(vector<Video> &vids, string title) {
    Video newVid(title);
    vids.push_back(newVid);
}

// 2017 Retina Podcast Analytics