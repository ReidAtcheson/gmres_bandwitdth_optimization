#include <random> 
#include <limits>
#include <complex>
#include "ut/ut.hpp"
#include "mdspan.hpp"
#include "common.h"
#include "linear_algebra.h"
int main(int argc,char** argv){
  using namespace boost::ut;
  "ut test"_test = []{
    expect(true==true);
  };
  "mdspan test"_test = []{
    namespace stdex=std::experimental;
    std::array d{
    0, 5, 1,
    3, 8, 4,
    2, 7, 6,
  };
    stdex::mdspan m{d.data(), stdex::extents{3, 3}};
    expect(m(0,2)==1);
  };
  "mdspan column major"_test = []{
    namespace stdex=std::experimental;
    std::array d{
    0, 5, 1,
    3, 8, 4,
    2, 7, 6,
  };
    std::mdspan<int,stdex::extents<size_t,3,3>,stdex::layout_left> m{d.data()};
    expect(m(2,0)==1);
  };
  "mdspan matrix typedef"_test = []{
    std::array d{
    0.0, 5.0, 1.0,
    3.0, 8.0, 4.0,
    2.0, 7.0, 6.0,
  };
    matrix<double> m(d.data(), std::extents(3,3));
    expect(m(2,0)==1.0);
  };

  "dot float symmetric"_test = []{
    using T = float;
    T eps = std::numeric_limits<T>::epsilon();
    size_t m=512;
    //Make two random vectors of length `m` 
    //using <random> with seeded rng
    std::vector<T> av(m),bv(m);
    std::mt19937 gen(0);
    std::uniform_real_distribution<T> dis(0.0,1.0);
    for(size_t i=0;i<m;i++){
      av[i]=dis(gen);
      bv[i]=dis(gen);
    }
    matrix<const T> a(av.data(),std::extents(m,1));
    matrix<const T> b(bv.data(),std::extents(m,1));
    //Check that the two results are the same
    expect( std::abs(dot(a,b)-dot(b,a))/std::abs(dot(a,b)) < 2*eps );
  };
  "dot double symmetric"_test = []{
    using T = double; 
    T eps = std::numeric_limits<T>::epsilon();
    size_t m=512;
    //Make two random vectors of length `m` 
    //using <random> with seeded rng
    std::vector<T> av(m),bv(m);
    std::mt19937 gen(0);
    std::uniform_real_distribution<T> dis(0.0,1.0);
    for(size_t i=0;i<m;i++){
      av[i]=dis(gen);
      bv[i]=dis(gen);
    }
    matrix<const T> a(av.data(),std::extents(m,1));
    matrix<const T> b(bv.data(),std::extents(m,1));
    //Check that the two results are the same
    expect( std::abs(dot(a,b)-dot(b,a))/std::abs(dot(a,b)) < 2*eps );
  };

  "dot complex float conjugate symmetric"_test = []{
    using R = float;
    using T = std::complex<R>;
    R eps = std::numeric_limits<R>::epsilon();
    size_t m=512;
    //Make two random vectors of length `m` 
    //using <random> with seeded rng
    std::vector<T> av(m),bv(m);
    std::mt19937 gen(0);
    std::uniform_real_distribution<R> dis(0.0,1.0);
    for(size_t i=0;i<m;i++){
      av[i]=T(dis(gen),dis(gen));
      bv[i]=T(dis(gen),dis(gen));
    }
    matrix<const T> a(av.data(),std::extents(m,1));
    matrix<const T> b(bv.data(),std::extents(m,1));
    //Check that the two results are the same
    expect( std::abs(dot(a,b)-std::conj(dot(b,a)))/std::abs(dot(a,b)) < 2*eps );
  };

  "dot complex double conjugate symmetric"_test = []{
    using R = double;
    using T = std::complex<R>;
    R eps = std::numeric_limits<R>::epsilon();
    size_t m=512;
    //Make two random vectors of length `m` 
    //using <random> with seeded rng
    std::vector<T> av(m),bv(m);
    std::mt19937 gen(0);
    std::uniform_real_distribution<R> dis(0.0,1.0);
    for(size_t i=0;i<m;i++){
      av[i]=T(dis(gen),dis(gen));
      bv[i]=T(dis(gen),dis(gen));
    }
    matrix<const T> a(av.data(),std::extents(m,1));
    matrix<const T> b(bv.data(),std::extents(m,1));
    //Check that the two results are the same
    expect( std::abs(dot(a,b)-std::conj(dot(b,a)))/std::abs(dot(a,b)) < 2*eps );
  };






  return 0;
}
