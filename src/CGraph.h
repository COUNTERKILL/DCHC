#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>



class CGraph
{
public:
    typedef std::unordered_set<std::size_t> VerticesSet;
private:
    typedef std::unordered_map<std::size_t, std::vector<std::size_t>> TypeOfData;
public:
    CGraph(const std::size_t verticesCount);
    virtual ~CGraph();
    CGraph(const CGraph&);
    CGraph& operator=(const CGraph&);
    VerticesSet ForwardBFS(std::size_t);
    VerticesSet BackwardBFS(std::size_t);
    VerticesSet GetUnvisited(VerticesSet&, VerticesSet&);
    CGraph CreateGraphFromVertices(const VerticesSet&);
    void AddEdge(const std::size_t firstVertex, const std::size_t secondVertex);
    std::size_t GetRandomVertex() { return fwdData.begin()->first; };
private:
    TypeOfData fwdData;
    TypeOfData bwdData;
    std::size_t verticesCount = 0;   
};
