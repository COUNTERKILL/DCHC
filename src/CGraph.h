#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>



class CGraph
{
public:
    // ��� ����� ������
    typedef std::unordered_set<std::size_t> VerticesSet;
private:
    // ������ ���������, �������� ��������� �����
    typedef std::unordered_map<std::size_t, std::vector<std::size_t>> TypeOfData;
public:
    // �����������. ��������� ���� �������� - ���������� ������ � �����
    CGraph(const std::size_t verticesCount);
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
    std::size_t GetRandomVertex() { return fwdData.begin()->first; };
private:
    TypeOfData fwdData;                 // ������ ��������� ��� �������� ������
    TypeOfData bwdData;                 // ������ ���������, � ������� ��� ����� ���������� ��� ��������� ������
    std::size_t verticesCount = 0;      // ���������� ������
};
