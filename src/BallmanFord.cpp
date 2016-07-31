#include "BallmanFord.h"

#define ALLOC alloc_if(1) free_if(0)
#define FREE alloc_if(0) free_if(1)
#define REUSE alloc_if(0) free_if(0)

using namespace std;

bool phiIsUsing = false;


void BallmanFordPhi(const size_t *pSrc, 
                    const size_t *pDst, 
                    int *pAttainabilities, std::size_t edgesCount, 
                    size_t verticesCount
)
{
    #pragma offload target(mic:0) \
    in(src: length(edgesCount) ALLOC) \
    in(dst: length(edgesCount) ALLOC) \
    in(pAttainabilities: length(verticesCount) ALLOC)
    {
        bool any = false;
        do
        {
            any = false;
            
            #pragma omp parallel for num_threads(244) schedule(static)
            for (size_t j = 0; j < edgesCount; j++)
                if (!pAttainabilities[dst[j]] & pAttainabilities[src[j]])
                {
                        pAttainabilities[src[j]] = 0;
                        any = true;
                }
        } while (any);
    }
    #pragma offload target(mic:0) \
    out(pAttainabilities: length(0) FREE)
    return;
}

void BallmanFordCPU(const size_t *pSrc, 
                    const size_t *pDst, 
                    int *pAttainabilities, std::size_t edgesCount, 
                    size_t verticesCount,
                    int threadsCount
)
{
    omp_set_num_threads(threadsCount);
    bool any = false;
    do
    {
        any = false;
        
        #pragma omp parallel for num_threads(threadsCount) schedule(static)
        for (size_t j = 0; j < edgesCount; j++)
            if (!pAttainabilities[dst[j]] & pAttainabilities[src[j]])
            {
                    pAttainabilities[src[j]] = 0;
                    any = true;
            }
    } while (any);
    
    return;
}

void BallmanFord(const size_t *pSrc, 
                 const size_t *pDst, 
                 size_t pivot,
                 int *pAttainabilities, 
                 size_t edgesCount, 
                 size_t verticesCount,
                 int threadsCount
)
{
    pAttainabilities[pivot] = 0;
    
    bool isUsePhi = false;
    #pragma omp critical
    {
        if(!phiIsUsing)
        {
            isUsePhi = true;
            phiIsUsing = true;
        }
    }
    
    if(isUsePhi)
    {
        BallmanFordPhi(pSrc, pDst, pAttainabilities, edgesCount, verticesCount);
    }
    else
    {
        BallmanFordCPU(pSrc, pDst, pAttainabilities, edgesCount, verticesCount, threadsCount);
    }
    return;
}