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



I have found that reusing `H` in this way barely impacts the convergence rate of restarted GMRES but at the cost of having to "reorthogonalize" `W` which implicitly occurs
when solving least-squares systems with this matrix (because least-squares methods mostly use householder QR). So we gain in no longer needing to do dot products in the formation
of `H` which eliminates a significant number of memory reads, but it also elminates a loop-carried data dependency that previously prevented the fusion of inner gmres iterations.
Reorthogonalization of `W` comes with a cost but since we can accomplish that with level-3 BLAS operations and only requires reading in `W` once, an `O(m*k)` number of reads, as opposed
to computing `O(k^2)` dot products which requires `O(m*k^2)` reads and can not be cached because of the data dependencies of gram-schmidt orthogonalization used to compute `H`
