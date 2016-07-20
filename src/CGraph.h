#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>



class CGraph
{
public:
    // тип набор вершин
    typedef std::unordered_set<std::size_t> VerticesSet;
private:
    // список смежности, хран€щий структуру графа
    typedef std::unordered_map<std::size_t, std::vector<std::size_t>> TypeOfData;
public:
    // конструктор. ѕринимает один параметр - количество вершин в графе
    CGraph(const std::size_t verticesCount);
    virtual ~CGraph();
    CGraph(const CGraph&);
    CGraph& operator=(const CGraph&);
    // ForwardBFS() возвращает набор вершин, достижимых при "пр€мом" обходе графа
    VerticesSet ForwardBFS(std::size_t);
    // BackwardBFS() возвращает набор вершин, достижимых при "обратном" обходе графа
    VerticesSet BackwardBFS(std::size_t);
    // GetUnvisited() возвращает набор вершин, недостижимых ни при "обратном" обходе графа, ни при "пр€мом"
    VerticesSet GetUnvisited(VerticesSet&, VerticesSet&);
    // CreateGraphFromVertices() принимает один параметр - набор вершин. ћетод возвращает новый граф, созданный из текущего, но только с теми вершинами, которые присутствуют в наборе
    CGraph CreateGraphFromVertices(const VerticesSet&);
    // AddEdge() добавл€ет ребро в граф
    void AddEdge(const std::size_t firstVertex, const std::size_t secondVertex);
    // GetRandomVertex() должна возвращать случайный вектор.
    std::size_t GetRandomVertex() { return fwdData.begin()->first; };
private:
    TypeOfData fwdData;                 // список смежности дл€ при€мого обхода
    TypeOfData bwdData;                 // список смежности, в котором все ребра развернуты дл€ обратного обхода
    std::size_t verticesCount = 0;      // количество вершин
};
