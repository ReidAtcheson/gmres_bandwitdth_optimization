#include "ut/ut.hpp"
#include "mdspan.hpp"
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
  return 0;
}
