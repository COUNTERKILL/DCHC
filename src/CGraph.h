#pragma once

#include <vector>
#include <unordered_set>



class CGraph
{
public:
    // ��� ����� ������
    typedef std::unordered_set<std::size_t> VerticesSet;
public:
    // �����������. ��������� ���� �������� - ���������� ������ � �����
    CGraph(const std::size_t verticesCount, std::size_t& availableThreads);
    virtual ~CGraph();
    CGraph(const CGraph&);
    CGraph& operator=(const CGraph&);
    // ForwardBFS() ���������� ����� ������, ���������� ��� "������" ������ �����
    VerticesSet ForwardBFS(std::size_t);
    // BackwardBFS() ���������� ����� ������, ���������� ��� "��������" ������ �����
    VerticesSet BackwardBFS(std::size_t);
    // GetUnvisited() ���������� ����� ������, ������������ �� ��� "��������" ������ �����, �� ��� "������"
    VerticesSet GetUnvisited(VerticesSet&, VerticesSet&);
    // CreateGraphFromVertices() ��������� ���� �������� - ����� ������. ����� ���������� ����� ����, ��������� �� ��������, �� ������ � ���� ���������, ������� ������������ � ������
    CGraph CreateGraphFromVertices(const VerticesSet&);
    // AddEdge() ��������� ����� � ����
    void AddEdge(const std::size_t firstVertex, const std::size_t secondVertex);
    // GetRandomVertex() ������ ���������� ��������� ������.
    std::size_t GetRandomVertex() { return src.at(0); };
private:
    std::vector<size_t> src;
    std::vector<size_t> dst;
    std::size_t verticesCount = 0;      // ���������� ������
    std::size_t edgesCount = 0;      // ���������� �����
    std::sie_t& availableThreads; // �������� ��������-����� ����������� � ����������� ����� availableThreads + 1 (�������)
};
