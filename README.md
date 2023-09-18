# (WIP): gmres_bandwitdth_optimization
optimizing bandwidth utilization for restarted gmres


This will implement a bare-bones restarted gmres. I will go through a sequence of optimizations intended to explore how to better
handle the memory bandwidth requirements of restarted GMRES. This is just a work in progress but here are some themes I intend to explore


1. reusing arnoldi basis from previous iterations to eliminate dot products on future iterations
  - reduce memory reads
2. time-blocking gmres iterations
  - speculative but I believe it's possible to partially fuse inner GMRES iterations and avoid redundant reads of a sparse matrix
3. Tridiagonalize the arnoldi basis
  - also speculative but if possible this can turn the `O(m*k^2)` cost of generating an arnoldi basis to `O(m*k)`



All of the above rests on an observation I have made that after computing an arnoldi factorization for a matrix A as

`A*Vk = V*H`

where `V = [Vk, v]` is `m by k+1` and orthonormal and `H` is `k+1 by k` then the matrix `H` can be _reused_ in later iterations to generate new basis
vectors `W` that are no longer orthonormal but still satisfy `A*Wk = W*H` and this basis appears to be stable in the sense that the condition number of
`W` is not very large.


