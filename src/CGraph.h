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
                               CGraph                  (const std::size_t verticesCount);
    virtual                    ~CGraph                 ();
public:
                               CGraph                  (const CGraph&)              = delete;
                               CGraph                  (CGraph&&);
public:
            CGraph&            operator=               (const CGraph&)                    = delete;
            CGraph&            operator=               (CGraph&&);
public:
            VerticesSet        GetForwardBFSVisited    (std::size_t);
            VerticesSet        GetBackwardBFSVisited   (std::size_t);
            VerticesSet        GetUnvisited            (VerticesSet&,
                                                        VerticesSet&);
public:
       CGraph CreateGraphFromVertices(const VerticesSet&);
public:
            void               AddEdge                 (std::size_t firstVertex,
                                                        std::size_t secondVertex);
            std::size_t        GetRandomVertex         () { return m_fwdData.begin()->first; };
private:
            TypeOfData          m_fwdData;
            TypeOfData          m_bwdData;
            std::size_t         m_verticesCount = 0;
              
};
