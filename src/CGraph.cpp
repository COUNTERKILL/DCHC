#include "CGraph.h"
#include <queue>
#include <iostream>

using namespace std;

CGraph::CGraph(const std::size_t verticesCount_)
{
    verticesCount = verticesCount_;
    fwdData.reserve(verticesCount_);
    bwdData.reserve(verticesCount_);
}
CGraph::~CGraph(){  }

CGraph::CGraph(const CGraph& graph)
{
    fwdData = graph.fwdData;
    bwdData = graph.bwdData;
    verticesCount = graph.verticesCount;
}
    
CGraph& CGraph::operator=(const CGraph& graph)
{
    fwdData = graph.fwdData;
    bwdData = graph.bwdData;
    verticesCount = graph.verticesCount;
    return *this;
}

void CGraph::AddEdge(const size_t firstVertex,
                     const size_t secondVertex)
{
    if(fwdData.find(firstVertex) == fwdData.end())
        fwdData[firstVertex] = vector<size_t>();
    if(bwdData.find(secondVertex) == bwdData.end())
        bwdData[secondVertex] = vector<size_t>();
    
    if(fwdData.find(secondVertex) == fwdData.end())
        fwdData[secondVertex] = vector<size_t>();
    if(bwdData.find(firstVertex) == bwdData.end())
        bwdData[firstVertex] = vector<size_t>();
    
    fwdData.at(firstVertex).push_back(secondVertex);
    bwdData.at(secondVertex).push_back(firstVertex);
    return;
}

CGraph::VerticesSet CGraph::ForwardBFS(size_t pivot)
{
    VerticesSet res;
    res.insert(pivot);
    
    queue<size_t> bfsQueue;
    bfsQueue.push(pivot);
    cout << pivot << endl;

    for(TypeOfData::iterator pVerticesList = fwdData.begin(); pVerticesList != fwdData.end(); pVerticesList++)
    {
        cout << "Vertex " << pVerticesList->first << ": ";
        for(vector<size_t>::iterator pVertex = pVerticesList->second.begin(); pVertex != pVerticesList->second.end(); pVertex++)
        {
            cout << *pVertex << " ";
        }
        cout << endl;
    }
    cout << endl;
    while(!bfsQueue.empty())
    {
        cout << "front: " << bfsQueue.front() << endl;
        vector<size_t>& verticesList = fwdData.at(bfsQueue.front());
        cout << 111 << endl;
        for(vector<size_t>::iterator pVertex = verticesList.begin(); pVertex != verticesList.end(); pVertex++)
        {
            if(res.find(*pVertex) == res.end())
            {
                bfsQueue.push(*pVertex);
                res.insert(*pVertex);
            } 
        }
        bfsQueue.pop();
    }
    return res;
}

typename CGraph::VerticesSet CGraph::BackwardBFS(size_t pivot)
{
    VerticesSet res;
    queue<size_t> bfsQueue;
    bfsQueue.push(pivot);
    while(!bfsQueue.empty())
    {
        vector<size_t> verticesList = bwdData.at(bfsQueue.front());
        for(vector<size_t>::iterator pVertex = verticesList.begin(); pVertex != verticesList.end(); pVertex++)
        {
            if(res.find(*pVertex) == res.end())
            {
                bfsQueue.push(*pVertex);
                res.insert(*pVertex);
            } 
        }
        bfsQueue.pop();
    }
    return res;
}

typename CGraph::VerticesSet CGraph::GetUnvisited(VerticesSet& fwdVisited, 
                                 VerticesSet& bwdVisited)
{
    VerticesSet res;
    for(TypeOfData::iterator pVerticesList = fwdData.begin(); pVerticesList != fwdData.end(); pVerticesList++)
    {
        if((fwdVisited.find(pVerticesList->first) == fwdVisited.end()) & (bwdVisited.find(pVerticesList->first) == bwdVisited.end()))
            res.insert(pVerticesList->first);
    }
    return res;
}

CGraph CGraph::CreateGraphFromVertices(const VerticesSet& vertices)
{
    CGraph res(vertices.size());
    for(VerticesSet::const_iterator pVertexInSet = vertices.begin(); pVertexInSet != vertices.end(); pVertexInSet++)
    {
        for(vector<size_t>::iterator pVertex = fwdData.at(*pVertexInSet).begin(); pVertex != fwdData.at(*pVertexInSet).end(); pVertex++)
        {
            if(vertices.find(*pVertex) != vertices.end())
                res.AddEdge(*pVertexInSet, *pVertex);
        }
    }
    return res;
}