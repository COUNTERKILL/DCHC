#pragma once
void BallmanFordPhi(const std::size_t *pSrc, const std::size_t *pDst, 
                    const int *pAttainabilities, std::size_t edgesCount, 
                    std::size_t verticesCount
);