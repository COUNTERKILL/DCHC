#include "CGraph.h"
#include <queue>
#include <iostream>
#include <omp.h>

using namespace std;

CGraph::CGraph(const std::size_t verticesCount_, int& availableThreads_):availableThreads(availableThreads_)
{
    edgesCount = 0;
    verticesCount = verticesCount_;
    src.reserve(edgesCount);
    dst.reserve(edgesCount);
}
CGraph::~CGraph(){  }

CGraph::CGraph(const CGraph& graph):availableThreads(graph.availableThreads)
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
    
    vector<int> d (verticesCount, 1); // 0 - достижима, 1 - бесконечность (недостижима)
    d[pivot] = 0;
    
    int threadsCount = 1;
    #pragma omp critical(threads_count)
    {
        threadsCount = availableThreads > 0 ? availableThreads + 1 : 1;
        availableThreads -= (threadsCount-1);
    }
    omp_set_num_threads(availableThreads);
    bool any = false;
    do
    {
        any = false;
        #pragma omp parallel for schedule(static)
        for (size_t j = 0; j < edgesCount; j++)
            if (!d[src[j]] & d[dst[j]])
            {
                    d[dst[j]] = 0;
                    #pragma omp critical
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
    
    vector<int> d (verticesCount, 1); // 0 - достижима, 1 - бесконечность (недостижима)
    d[pivot] = 0;
    
    int threadsCount = 1;
    #pragma omp critical(threads_count)
    {
        threadsCount = availableThreads > 0 ? availableThreads + 1 : 1;
        availableThreads -= (threadsCount-1);
    }
    //omp_set_num_threads(threadsCount);

    bool any = false;
    do
    {
        any = false;
        #pragma omp parallel for num_threads(threadsCount) schedule(static)
        for (size_t j = 0; j < edgesCount; j++)
            if (!d[dst[j]] & d[src[j]])
            {
                    d[src[j]] = 0;
                    #pragma omp critical
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

// если есть хоть в одном, то берем (вроде)
CGraph CGraph::CreateGraphFromVertices(const VerticesSet& vertices)
{
    CGraph res(vertices.size(), availableThreads);
    for(size_t i = 0; i < edgesCount; i++)
    {
       if((vertices.find(src[i]) != vertices.end()) & (vertices.find(dst[i]) != vertices.end()))
        {
           
            res.AddEdge(src[i], dst[i]);
        }
    }
    return res;
}