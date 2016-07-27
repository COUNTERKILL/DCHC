#pragma once

#include <vector>
#include <unordered_set>



class CGraph
{
public:
    // тип набор вершин
    typedef std::unordered_set<std::size_t> VerticesSet;
public:
    // конструктор. ѕринимает один параметр - количество вершин в графе
    CGraph(const std::size_t verticesCount, std::size_t& availableThreads);
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
    std::size_t GetRandomVertex() { return src.at(0); };
private:
    std::vector<size_t> src;
    std::vector<size_t> dst;
    std::size_t verticesCount = 0;      // количество вершин
    std::size_t edgesCount = 0;      // количество ребер
    std::sie_t& availableThreads; // алгоритм Ѕеллмана-‘орда запускаетс€ с количеством нитей availableThreads + 1 (текуща€)
};
