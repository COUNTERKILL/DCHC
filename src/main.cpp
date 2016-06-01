#include <iostream>
#include <fstream>
#include <string>
#include "CGraph.h"

using namespace std;



int main(int argc, char** argv)
{
    std::fstream fInput("input.graph", std::ios_base::in);
    if(!fInput.is_open())
    {
        cout << "Error openning file" << endl;
        return 0;
    }
    size_t verticesCount = 0;
    fInput >> verticesCount;
    if(verticesCount == 0)
    {
        cout << "Vertices count is eq 0" << endl;
        return 0;
    }
    
    Graph graph(verticesCount);
    while(!fInput.eof())
    {
        
    }
    return 0;
}
