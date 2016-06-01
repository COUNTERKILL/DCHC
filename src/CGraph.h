#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>


template <typename VertexNumberType>
class CGraph
{
public:
    typedef std::unordered_set<VertexNumberType> VerticesSet;
private:
    typedef std::unordered_map<VertexNumberType, std::vector<VertexNumberType>> TypeOfData;
public:
                               CGraph                  (const std::size_t verticesCount);
    virtual                    ~CGraph                 ()                           = default;
public:
                               CGraph                  (const CGraph&)                    = default;
                               CGraph                  (CGraph&&)                   = default;
public:
            CGraph&            operator=               (const CGraph&)                    = delete;
            CGraph&            operator=               (const CGraph&&)                   = delete;
public:
            VerticesSet        GetForwardBFSVisited    (VertexNumberType);
            VerticesSet        GetBackwardBFSVisited   (VertexNumberType);
            VerticesSet        GetUnvisited            (VerticesSet&,
                                                        VerticesSet&);
public:
       Graph<VertexNumberType> CreateGraphFromVertices(const VerticesSet&);
public:
            void               AddEdge                 (VertexNumberType firstVertex,
                                                        VertexNumberType secondVertex);
private:
            TypeOfData          m_fwdData;
            TypeOfData          m_bwdData;
            std::size_t         m_verticesCount = 0;
              
};
