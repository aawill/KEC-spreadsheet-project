#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Video.h"
#include "Shlobj.h"

using namespace std;

void addVideo(vector<Video> &vids, string title);
void initVideos(vector<Video> &vids, ifstream &ins);
bool isResident(string name, int &index);
bool isVideo(string title, vector<Video> &vids, int &index);
string getVidFile(vector<Video> &vids, int &vidIndex);
void readVidFile(ifstream &ins, vector<Video> &vids, int &vidIndex);
string GetDesktopfilePath(PTCHAR filePathIn);
void printWelcome();

TCHAR    filePath[MAX_PATH];
string actual = GetDesktopfilePath(filePath);

int main() {
    int vidIndex;
    vector<Video> videos;
    string vidFile, dataFile, resName, trash, percent;
    ifstream dataIn, vidIn;
    
    printWelcome();
    cout << "Enter data spreadsheet filename, or 'quit': ";
    while (getline(cin, dataFile)) {
        if (dataFile == "quit") {
            system("pause");
            exit(0);
        }
        dataFile = actual + "\\" + dataFile + ".csv";
        dataIn.open(dataFile);
        if (!dataIn.is_open()) {
            cout << "Invalid filename, please try again: ";
        }
        else {
            break;
        }
    }
    initVideos(videos, dataIn);
    while (true) {
        vidFile = getVidFile(videos, vidIndex);
        vidIn.open(vidFile);
        if (vidIn.is_open()) {
            readVidFile(vidIn, videos, vidIndex);
        }
        vidIn.close();
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
    // Get the full path of the desktop :
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
    int flag = 0;

    getline(ins, trash);
    while (getline(ins, resName, ',')) {
        resName = resName.substr(1, (resName.length() - 2));
        getline(ins, percent, '\n');
        percent = percent.substr(1, (percent.length() - 2));
        if (isResident(resName, resIndex)) {
            if (vids[vidIndex].getResident(resIndex)->getPercentWatched() != stoi(percent)) {
                cout << "Change " << resName << "'s watch percentage to " << percent << endl;
                flag = 1;
            }
        }
    }
    if (!flag) {
        cout << "No changes to make" << endl;
    }
}

string getVidFile(vector<Video> &vids, int &vidIndex) {
    string input;

    cout << "Enter video to check (e.g. 'Comer 1a'), or 'quit': ";
    getline(cin, input);
    if (input == "quit") {
        system("pause");
        exit(0);
    }
    if (!isVideo(input, vids, vidIndex)) {
        cout << "Invalid video name" << endl;
    }
    return (actual + "\\" + input + ".csv");
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
    getline(ins, trash);
    getline(ins, trash);
    int index = 0;
    while (getline(ins, vidName, ',')) {
        addVideo(vids, vidName);
        vids[index].initResidents(resNames);
        for (int j = 0; j < NUM_RESIDENTS; ++j) {
            ins >> percentWatched;
            if (j != NUM_RESIDENTS - 1) {
                ins >> charTrash;
            }
            else {
                getline(ins, trash, '\n');
            }
            vids[index].getResident(j)->setPercentWatched(percentWatched);
        }
        ++index;
    }
    cout << "VIDEOS TO CHOOSE FROM:" << endl;
    for (int i = 0; i < vids.size(); ++i) {
        cout << vids[i].getTitle() << endl;
    }
}

void addVideo(vector<Video> &vids, string title) {
    Video newVid = { title };
    vids.push_back(newVid);
}

