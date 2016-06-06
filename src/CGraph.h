#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>



class CGraph
{
public:
    typedef std::unordered_set<size_t> VerticesSet;
private:
    typedef std::unordered_map<size_t, std::vector<size_t>> TypeOfData;
public:
                               CGraph                  (const std::size_t verticesCount);
    virtual                    ~CGraph                 ()                           = default;
public:
                               CGraph                  (const CGraph&)                    = default;
                               CGraph                  (CGraph&&)                   = default;
public:
            CGraph&            operator=               (const CGraph&)                    = delete;
            CGraph&            operator=               (CGraph&&)                   = default;
public:
            VerticesSet        GetForwardBFSVisited    (size_t);
            VerticesSet        GetBackwardBFSVisited   (size_t);
            VerticesSet        GetUnvisited            (VerticesSet&,
                                                        VerticesSet&);
public:
       CGraph CreateGraphFromVertices(const VerticesSet&);
public:
            void               AddEdge                 (size_t firstVertex,
                                                        size_t secondVertex);
            size_t   GetRandomVertex         () { return m_fwdData.begin()->first; };
private:
            TypeOfData          m_fwdData;
            TypeOfData          m_bwdData;
            std::size_t         m_verticesCount = 0;
              
};
