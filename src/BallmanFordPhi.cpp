#include "BallmanFordPhi.h"

#define ALLOC alloc_if(1) free_if(0)
#define FREE alloc_if(0) free_if(1)
#define REUSE alloc_if(0) free_if(0)

using namespace std;

void BallmanFordPhi(const std::size_t *pSrc, const std::size_t *pDst, 
                    const int *pAttainabilities, std::size_t edgesCount, 
                    std::size_t verticesCount
)
{
    #pragma offload target(mic:0) \
    in(src: length(edgesCount) ALLOC) \
    in(dst: length(edgesCount) ALLOC) \
    nocopy(pAttainabilities: length(verticesCount) ALLOC)
    {
        bool any = false;
        do
        {
            any = false;
            
            #pragma omp parallel for num_threads(244) schedule(static)
            for (size_t j = 0; j < edgesCount; j++)
                if (!d[dst[j]] & d[src[j]])
                {
                        d[src[j]] = 0;
                        any = true;
                }
        } while (any);
    }
    #pragma offload target(mic:0) \
    out(pAttainabilities: length(0) FREE)
    return;
}