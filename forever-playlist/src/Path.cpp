#include <Arduino.h>
#include <vector>
#include <string>
#include <algorithm>
#include "Path.h"

using namespace std;

Path::Path() { 
  prev = nullptr;
  part = "";
}

Path* Path::append(string newPart) {
    Path * newPath = new Path();
    newPath->part = newPart;
    newPath->prev = this;
    return newPath;
}

string Path::render() {
    if(prev) {
        return prev->render() + "/" + part;
    } else {
        return part;
    }
}

int Path::compare(Path *other) {
    if(prev && other->prev) {
        int prevCompare = prev->compare(other->prev);
        if(prevCompare == 0) {
            return part.compare(other->part);
        } else {
            return prevCompare;
        }
    } else if(prev && !other->prev) {
        return -1;
    } else if(!prev && other->prev) {
        return 1;
    } else {
        return part.compare(other->part);
    }
}

bool pathCompare(Path *left, Path *right) {
    int res = left->compare(right);
    // string print = "Comparing3 [" + left->render() + "] and [" + right->render() + "] result [" + to_string(res) + "]";
    // Serial.println(print.c_str());
    // Serial.println("");

    return res < 0;
}

void sortPaths(vector<Path*> *paths) {
    string print = "Sorting size: " + to_string(paths->size());
    Serial.println(print.c_str());
    sort(paths->begin(), paths->end(), pathCompare);
}

vector<string> toSimpleStringPath(vector<Path*> *paths) {
    vector<string> simple;
    for(unsigned int i = 0; i < paths->size(); i++) {
        simple.push_back((*paths)[i]->render());
    }
    return simple;
}