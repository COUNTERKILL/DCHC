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
    
    // graph reading
    Graph<size_t> graph(verticesCount);
    while(!fInput.eof())
    {
        size_t v1 = 0, v2 = 0;
        fInput >> v1;
        fInput >> v2;
        graph.AddEdge(v1, v2);
    }
    
    vector<Graph::VerticesSet> components;
    
    //finding components
    while(true)
    {
        Graph::VerticesSet fwd = graph.GetForwardBFSVisited();
        Graph::VerticesSet bwd = graph.GetBackwardBFSVisited();
        Graph::VerticesSet unvisited = graph.GetUnvisited();
        
        Graph::VerticesSet component;
        Graph::VerticesSet verticesFoundedInFwdButNotInBwd;
        Graph::VerticesSet verticesFoundedInBwdButNotInFwd;
        for(auto& vertex : fwd)
        {
            if(bwd.find(vertex) != bwd.end())
            {
                component.insert(vertex);
            }
            else
            {
                verticesFoundedInFwdButNotInBwd.insert(vertex);
            }
        }
        
        for(auto& vertex : bwd)
        {
            if(fwd.find(vertex) == fwd.end())
            {
                verticesFoundedInBwdButNotInFwd.insert(vertex);
            }
        }
        if((verticesFoundedInFwdButNotInBwd.size() == 1) && (verticesFoundedInBwdButNotInFwd.size() == 1))
        {
            Graph::VerticesSet simpleComponent;
            simpleComponent.insert(verticesFoundedInFwdButNotInBwd.begin()
            components
        }
    }
    
    return 0;
}
