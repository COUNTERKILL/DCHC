#include "CGraph.h"
#include <queue>
#include <iostream>

using namespace std;

CGraph::CGraph(const std::size_t verticesCount_)
{
    edgesCount = 0;
    verticesCount = verticesCount_;
    src.reserve(edgesCount);
    dst.reserve(edgesCount);
}
CGraph::~CGraph(){  }

CGraph::CGraph(const CGraph& graph)
{
    src = graph.src;
    dst = graph.dst;
    edgesCount = graph.edgesCount;
    verticesCount = graph.verticesCount;
}
    
CGraph& CGraph::operator=(const CGraph& graph)
{
    src = graph.src;
    dst = graph.dst;
    edgesCount = graph.edgesCount;
    verticesCount = graph.verticesCount;
    return *this;
}

void CGraph::AddEdge(const size_t firstVertex,
                     const size_t secondVertex)
{
    src.push_back(firstVertex);
    dst.push_back(secondVertex);
    edgesCount++;
    return;
}

CGraph::VerticesSet CGraph::ForwardBFS(size_t pivot)
{
    VerticesSet res;
    res.insert(pivot);
    
    vector<bool> d (verticesCount, true); // false - ���������, true - ������������� (�����������)
	d[pivot] = 0;
    
    bool any = false;
    do
    {
        any = false;
        for (size_t j = 0; j < edgesCount; j++)
            if (!d[src[j]])
            {
                    d[dst[j]] = false;
                    res.insert(dst[j]);
                    any = true;
            }
    } while (any);
    
    return res;
}

typename CGraph::VerticesSet CGraph::BackwardBFS(size_t pivot)
{
    VerticesSet res;
    res.insert(pivot);
    
    vector<bool> d (verticesCount, true); // false - ���������, true - ������������� (�����������)
	d[pivot] = 0;
    
    bool any = false;
    do
    {
        any = false;
        for (size_t j = 0; j < edgesCount; j++)
            if (!d[dst[j]])
            {
                    d[src[j]] = false;
                    res.insert(src[j]);
                    any = true;
            }
    } while (any);
    
    return res;
}

typename CGraph::VerticesSet CGraph::GetUnvisited(VerticesSet& fwdVisited, 
                                 VerticesSet& bwdVisited)
{
    VerticesSet res;
    for(size_t i = 0; i < edgesCount; i++)
    {
        if((fwdVisited.find(src[i]) == fwdVisited.end()) 
            & (bwdVisited.find(src[i]) == bwdVisited.end()) 
            & (res.find(src[i]) == res.end()) 
            & (fwdVisited.find(dst[i]) == fwdVisited.end()) 
            & (bwdVisited.find(dst[i]) == bwdVisited.end())
        )
            res.insert(src[i]);
        if((fwdVisited.find(dst[i]) == fwdVisited.end()) 
            & (bwdVisited.find(dst[i]) == bwdVisited.end()) 
            & (res.find(dst[i]) == res.end()) 
            & (fwdVisited.find(src[i]) == fwdVisited.end()) 
            & (bwdVisited.find(src[i]) == bwdVisited.end())
        )
            res.insert(dst[i]);
    }
    return res;
}

// ���� ���� ���� � �����, �� ����� (�����)
CGraph CGraph::CreateGraphFromVertices(const VerticesSet& vertices)
{
    CGraph res(vertices.size());
    for(size_t i = 0; i < edgesCount; i++)
    {
       if((vertices.find(src[i]) != vertices.end()) & (vertices.find(dst[i]) != vertices.end()))
        {
           
            res.AddEdge(src[i], dst[i]);
        }
    }
    return res;
}