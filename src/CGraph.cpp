#include "CGraph.h"
#include <queue>

using namespace std;

void CGraph::CGraph(size_t verticesCount)
{
    m_verticesCount = verticesCount;
    m_fwdData.reserve(verticesCount);
    m_bwdData.reserve(verticesCount);
}
    
    
void CGraph::AddEdge(VertexNumberType firstVertex,
                     VertexNumberType secondVertex)
{
    if(m_fwdData.find(firstVertex) == m_fwdData.end())
        m_fwdData[firstVertex] = vector<VertexNumberType>();
    if(m_bwdData.find(secondVertex) == m_bwdData.end())
        m_bwdData[secondVertex] = vector<VertexNumberType>();
    m_fwdData.at(firstVertex).push_back(secondVertex);
    m_bwdData.at(secondVertex).push_back(firstVertex);
}

VerticesSet CGraph::GetForwardBFSVisited(VertexNumberType pivot)
{
    VerticesSet res;
    
    queue bfsQueue;
    bfsQueue.push(pivot);
    
    while(!bfsQueue.empty())
    {
        for(auto& vertex : m_fwdData.at(bfsQueue.front()))
        {
            if(!res.find(vertex))
            {
                fsQueue.push(vertex);
                res.insert(vertex);
            } 
        }
        bfsQueue.pop();
    }
    
    return res;
}

VerticesSet CGraph::GetBackwardBFSVisited(VertexNumberType pivot)
{
    VerticesSet res;
    queue bfsQueue;
    bfsQueue.push(pivot);
    while(!bfsQueue.empty())
    {
        for(auto& vertex : m_bwdData.at(bfsQueue.front()))
        {
            if(!res.find(vertex))
            {
                fsQueue.push(vertex);
                res.insert(vertex);
            } 
        }
        bfsQueue.pop();
    }
    
    return res;
}


VerticesSet CGraph::GetUnvisited(VerticesSet& fwdVisited, 
                                 VerticesSet& bwdVisited)
{
    for(auto& kv : 
        // TODO
}
    
Graph<VertexNumberType> CGraph::CreateGraphFromVertices(const VerticesSet& vertices)
{
    Graph res(vertices.size());
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

