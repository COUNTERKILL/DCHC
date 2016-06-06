#include "CGraph.h"
#include <queue>

using namespace std;

CGraph::CGraph(const std::size_t verticesCount)
{
    m_verticesCount = verticesCount;
    m_fwdData.reserve(verticesCount);
    m_bwdData.reserve(verticesCount);
}
     
void CGraph::AddEdge(size_t firstVertex,
                     size_t secondVertex)
{
    if(m_fwdData.find(firstVertex) == m_fwdData.end())
        m_fwdData[firstVertex] = vector<size_t>();
    if(m_bwdData.find(secondVertex) == m_bwdData.end())
        m_bwdData[secondVertex] = vector<size_t>();
    m_fwdData.at(firstVertex).push_back(secondVertex);
    m_bwdData.at(secondVertex).push_back(firstVertex);
    return;
}


CGraph::VerticesSet CGraph::GetForwardBFSVisited(size_t pivot)
{
    VerticesSet res;
    
    queue<size_t> bfsQueue;
    bfsQueue.push(pivot);
    
    while(!bfsQueue.empty())
    {
        for(auto& vertex : m_fwdData.at(bfsQueue.front()))
        {
            if(res.find(vertex) == res.end())
            {
                bfsQueue.push(vertex);
                res.insert(vertex);
            } 
        }
        bfsQueue.pop();
    }
    
    return res;
}


typename CGraph::VerticesSet CGraph::GetBackwardBFSVisited(size_t pivot)
{
    VerticesSet res;
    queue<size_t> bfsQueue;
    bfsQueue.push(pivot);
    while(!bfsQueue.empty())
    {
        for(auto& vertex : m_bwdData.at(bfsQueue.front()))
        {
            if(res.find(vertex) == res.end())
            {
                bfsQueue.push(vertex);
                res.insert(vertex);
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
    for(auto& kv : m_fwdData)
    {
        if((fwdVisited.find(kv.first) == fwdVisited.end()) & (bwdVisited.find(kv.first) == bwdVisited.end()))
            res.insert(kv.first);
    }
    return res;
}

CGraph CGraph::CreateGraphFromVertices(const VerticesSet& vertices)
{
    CGraph res(vertices.size());
    for(auto& vertexInSet : vertices)
    {
        for(auto& vertex : m_fwdData.at(vertexInSet))
        {
            if(vertices.find(vertex) != vertices.end())
                res.AddEdge(vertexInSet, vertex);
        }
    }
    
    return res;
}

