#include <iostream>
#include <fstream>
#include <string>
#include <queue>
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
    int verticesCount = 0;
    fInput >> verticesCount;
    if(verticesCount == 0)
    {
        cout << "Vertices count is eq 0" << endl;
        return 0;
    }
    
    // graph reading
    CGraph firstCGraph(verticesCount);
    while(!fInput.eof())
    {
        int v1 = 0, v2 = 0;
        fInput >> v1;
        fInput >> v2;
        firstCGraph.AddEdge(v1, v2);
    };
    //try
    {
        queue<CGraph> graphsQueue;
        graphsQueue.push(move(firstCGraph));
        vector<CGraph::VerticesSet> components;
        
        //finding components
        while(!graphsQueue.empty())
        {
            auto& graph = graphsQueue.front();
            graphsQueue.pop();
            int pivot = graph.GetRandomVertex();
            CGraph::VerticesSet fwd = graph.GetForwardBFSVisited(pivot);
            CGraph::VerticesSet bwd = graph.GetBackwardBFSVisited(pivot);
            CGraph::VerticesSet unvisited = graph.GetUnvisited(fwd, bwd);
            
            CGraph::VerticesSet component;
            CGraph::VerticesSet verticesFoundedInFwdButNotInBwd;
            CGraph::VerticesSet verticesFoundedInBwdButNotInFwd;
            // writing components
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
            components.push_back(move(component));
            for(auto& vertex : bwd)
            {
                if(fwd.find(vertex) == fwd.end())
                {
                    verticesFoundedInBwdButNotInFwd.insert(vertex);
                }
            }
            // check founded in bwd but not founded in fwd size
            if(verticesFoundedInFwdButNotInBwd.size() == 1)
            {
                CGraph::VerticesSet simpleComponent;
                simpleComponent.insert(*(verticesFoundedInFwdButNotInBwd.begin()));
                components.push_back(move(simpleComponent));
            }
            else
            {
                if(!verticesFoundedInFwdButNotInBwd.empty())
                {
                    auto newGraph = graph.CreateGraphFromVertices(verticesFoundedInFwdButNotInBwd);
                    graphsQueue.push(move(newGraph));
                }
            }
            // check founded in fwd but not founded in bwd size
            if(verticesFoundedInBwdButNotInFwd.size() == 1)
            {
                CGraph::VerticesSet simpleComponent;
                simpleComponent.insert(*(verticesFoundedInBwdButNotInFwd.begin()));
                components.push_back(move(simpleComponent));
            }
            else
            {
                if(!verticesFoundedInBwdButNotInFwd.empty())
                {
                    auto newGraph = graph.CreateGraphFromVertices(verticesFoundedInBwdButNotInFwd);
                    graphsQueue.push(move(newGraph));
                }
            }
            // check unvisited size
            if(unvisited.size() == 1)
            {
                CGraph::VerticesSet simpleComponent;
                simpleComponent.insert(*(unvisited.begin()));
                components.push_back(move(simpleComponent));   
            }
            else
            {
                if(!unvisited.empty())
                {
                    auto newGraph = graph.CreateGraphFromVertices(unvisited);
                    graphsQueue.push(move(newGraph));
                }   
            }
        }
        cout << "result: " << endl;
        for(auto& component : components)
        {
            for(auto& vertex : component)
            {
                cout << vertex << " ";
            }
            cout << endl;
        }
    }
    /*catch(exception& ex)
    {
        cout << ex.what() << endl;
    }*/
    return 0;
}
