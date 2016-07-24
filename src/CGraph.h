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
    // список смежности, хранящий структуру графа
    //typedef std::unordered_map<std::size_t, std::vector<std::size_t>> TypeOfData;
public:
    // конструктор. Принимает один параметр - количество вершин в графе
    CGraph(const std::size_t verticesCount);
    virtual ~CGraph();
    CGraph(const CGraph&);
    CGraph& operator=(const CGraph&);
    // ForwardBFS() возвращает набор вершин, достижимых при "прямом" обходе графа
    VerticesSet ForwardBFS(std::size_t);
    // BackwardBFS() возвращает набор вершин, достижимых при "обратном" обходе графа
    VerticesSet BackwardBFS(std::size_t);
    // GetUnvisited() возвращает набор вершин, недостижимых ни при "обратном" обходе графа, ни при "прямом"
    VerticesSet GetUnvisited(VerticesSet&, VerticesSet&);
    // CreateGraphFromVertices() принимает один параметр - набор вершин. Метод возвращает новый граф, созданный из текущего, но только с теми вершинами, которые присутствуют в наборе
    CGraph CreateGraphFromVertices(const VerticesSet&);
    // AddEdge() добавляет ребро в граф
    void AddEdge(const std::size_t firstVertex, const std::size_t secondVertex);
    // GetRandomVertex() должна возвращать случайный вектор.
    std::size_t GetRandomVertex() { return src.at(0); };
private:
    //TypeOfData fwdData;                 // список смежности для приямого обхода
    //TypeOfData bwdData;                 // список смежности, в котором все ребра развернуты для обратного обхода
    std::vector<size_t> src;
    std::vector<size_t> dst;
    std::size_t verticesCount = 0;      // количество вершин
    std::size_t edgesCount = 0;      // количество ребер
};
