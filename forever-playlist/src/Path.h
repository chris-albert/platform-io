#include <vector>
#include <string>

using namespace std;

#ifndef PATH_H
#define PATH_H

class Path {

    private: 

        string part;
        Path *prev;

    public:
    
        Path();
        Path* append(string part);
        string render();
        int compare(Path * other);
};

#endif

bool pathCompare(Path *left, Path *right);

void sortPaths(vector<Path*> *paths);

vector<string> toSimpleStringPath(vector<Path*> *paths);