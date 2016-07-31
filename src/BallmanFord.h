#pragma once
void BallmanFord(const std::size_t *pSrc, 
                 const std::size_t *pDst, 
                 std::size_t pivot,
                 int *pAttainabilities, 
                 std::size_t edgesCount, 
                 std::size_t verticesCount,
                 int threadsCount
);