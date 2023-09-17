#ifndef __COMMON_H_
#define __COMMON_H_
#include <atomic>
#include <sys/sdt.h>
#include "mdspan.hpp"

template<typename T>
using matrix = std::mdspan<T,std::extents<size_t,std::dynamic_extent,std::dynamic_extent>, std::layout_left>;


namespace std{
  float conj(const float& in){
    return in;
  }
  double conj(const double& in){
    return in;
  }
}

static std::atomic<long long> global_flops_counter(0);
static std::atomic<long long> global_bytes_read_counter(0);
static std::atomic<long long> global_bytes_written_counter(0);
#define INCREMENT_FLOPS(x) (global_flops_counter += (x))
#define INCREMENT_MEMORY_READS(x) (global_bytes_read_counter += (x))
#define INCREMENT_MEMORY_WRITES(x) (global_bytes_written_counter += (x))

#define SCOPED_TRACE(x) \
  struct x { public: \
    x(){DTRACE_PROBE(scoped_trace,x##_entry);} \
    ~x(){DTRACE_PROBE(scoped_trace,x##_exit);} \
  } x##_v




#endif
