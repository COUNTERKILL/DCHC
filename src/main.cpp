#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <omp.h>
#include <memory>
#include "CGraph.h"


const int THREADS_COUNT = 1;
int availableThreads = THREADS_COUNT;

using namespace std;




size_t runnedJobsCount = 0;

// AtomicGetJob() атомарно получает указатель на граф из очереди. Из очереди граф удаляется. После ипользования графа, память по указателю нужно удалить
CGraph* AtomicGetJob(queue<CGraph>& graphsQueue)
{
    CGraph *pRes = NULL;
    #pragma omp critical(job)
    {
        if(!graphsQueue.empty())
        {
            pRes = new CGraph(graphsQueue.front());
            graphsQueue.pop();
            runnedJobsCount++;
        }
    }
    #pragma omp critical(threads_count)
    availableThreads--;
    return pRes;
}

// Обработчик события завершения обработки очередного графа. Уменьшает количество обрабатываемых в данный момент разными потоками графов
void CompliteJob()
{
    #pragma omp critical(job)
    runnedJobsCount--;
    #pragma omp critical(threads_count)
    availableThreads++;
}


int main(int argc, char** argv)
{
    std::fstream fInput("input.graph", std::ios_base::in);
    if(!fInput.is_open())
    {
        cout << "Error openning file" << endl;
        return 0;
    }
    
    int verticesCount = 0;
    fInput >> verticesCount;
    if(verticesCount == 0)
    {
        cout << "Vertices count is eq 0" << endl;
        return 0;
    }
    
    // graph reading
    CGraph firstCGraph(verticesCount, availableThreads);
    while(!fInput.eof())
    {
        int v1 = 0, v2 = 0;
        fInput >> v1;
        fInput >> v2;
        firstCGraph.AddEdge(v1, v2);
    };
    //try
    {
        queue<CGraph> graphsQueue;
        graphsQueue.push(move(firstCGraph));
        vector<CGraph::VerticesSet> components;
        
        omp_set_num_threads(THREADS_COUNT);
        omp_set_nested(1);
        omp_set_dynamic(0);
        #pragma omp parallel
        {
            bool isExit = false;
            //finding components
            while(!isExit)
            {
                CGraph *pGraph = AtomicGetJob(graphsQueue);
                if(pGraph)
                {
                    CGraph graph = *pGraph;
                    int pivot = graph.GetRandomVertex();
                    CGraph::VerticesSet fwd = graph.ForwardBFS(pivot);
                    CGraph::VerticesSet bwd = graph.BackwardBFS(pivot);
                    CGraph::VerticesSet unvisited = graph.GetUnvisited(fwd, bwd);
                    
                    CGraph::VerticesSet component;
                    CGraph::VerticesSet verticesFoundedInFwdButNotInBwd;
                    CGraph::VerticesSet verticesFoundedInBwdButNotInFwd;
                    // writing components
                    for(CGraph::VerticesSet::iterator pVertex = fwd.begin(); pVertex != fwd.end(); pVertex++)
                    {
                        if(bwd.find(*pVertex) != bwd.end())
                        {
                            component.insert(*pVertex);
                        }
                        else
                        {
                            verticesFoundedInFwdButNotInBwd.insert(*pVertex);
                        }
                    }
                    #pragma omp critical(componentsAdding)
                    components.push_back(move(component));
                    for(CGraph::VerticesSet::iterator pVertex = bwd.begin(); pVertex != bwd.end(); pVertex++)
                    {
                        if(fwd.find(*pVertex) == fwd.end())
                        {
                            verticesFoundedInBwdButNotInFwd.insert(*pVertex);
                        }
                    }
                    // check founded in bwd but not founded in fwd size
                    if(verticesFoundedInFwdButNotInBwd.size() == 1)
                    {
                        CGraph::VerticesSet simpleComponent;
                        simpleComponent.insert(*(verticesFoundedInFwdButNotInBwd.begin()));
                        #pragma omp critical(componentsAdding)
                        components.push_back(move(simpleComponent));
                    }
                    else
                    {
                        if(!verticesFoundedInFwdButNotInBwd.empty())
                        {
                            CGraph newGraph = graph.CreateGraphFromVertices(verticesFoundedInFwdButNotInBwd);
                            #pragma omp critical(job)
                            graphsQueue.push(move(newGraph));
                        }
                    }
                    // check founded in fwd but not founded in bwd size
                    if(verticesFoundedInBwdButNotInFwd.size() == 1)
                    {
                        CGraph::VerticesSet simpleComponent;
                        simpleComponent.insert(*(verticesFoundedInBwdButNotInFwd.begin()));
                        #pragma omp critical(componentsAdding)
                        components.push_back(move(simpleComponent));
                    }
                    else
                    {
                        if(!verticesFoundedInBwdButNotInFwd.empty())
                        {
                            CGraph newGraph = graph.CreateGraphFromVertices(verticesFoundedInBwdButNotInFwd);
                            #pragma omp critical(job)
                            graphsQueue.push(move(newGraph));
                        }
                    }
                    // check unvisited size
                    if(unvisited.size() == 1)
                    {
                        CGraph::VerticesSet simpleComponent;
                        simpleComponent.insert(*(unvisited.begin()));
                        #pragma omp critical(componentsAdding)
                        components.push_back(move(simpleComponent));   
                    }
                    else
                    {
                        if(!unvisited.empty())
                        {
                            CGraph newGraph = graph.CreateGraphFromVertices(unvisited);
                            #pragma omp critical(job)
                            graphsQueue.push(move(newGraph));
                        }   
                    }
                    CompliteJob();
                    delete pGraph;
                }
                else
                {
                    #pragma omp critical(job)
                    {
                        if(!runnedJobsCount)
                        {
                            isExit = true;
                        }
                    }
                }
            }
        }
        
        omp_set_nested(0);
        
        cout << "result: " << endl;
        for(vector<CGraph::VerticesSet>::iterator pComponent = components.begin(); pComponent!= components.end(); pComponent++)
        {
            
            for(CGraph::VerticesSet::iterator pVertex = pComponent->begin(); pVertex != pComponent->end(); pVertex++)
            {
                cout << *pVertex << " ";
            }
            cout << endl;
        }
    }
    /*catch(exception& ex)
    {
        cout << ex.what() << endl;
    }*/
    return 0;
}
