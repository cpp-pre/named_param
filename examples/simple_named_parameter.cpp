#include <iostream>
#include <pre/named_param/make_param.hpp>

// Your named parameter
constexpr pre::named_param::make_param_t<pre::named_param::value_> x; 
constexpr pre::named_param::make_param_t<pre::named_param::value_> y; 
constexpr pre::named_param::make_param_t<pre::named_param::nary_> special_callback_named;

// Your API that you want to define a named callback for
int simple_api (pre::named_param::value_<int> x, pre::named_param::value_<int> y) {
  return (x + y);
}

template <class CallbackType>
inline void same_api_with_callback( pre::named_param::value_<int> x, pre::named_param::value_<int> y, pre::named_param::nary_<CallbackType> named ) {
  named(x + y);
}

int main(int argc, char** argv) {

  std::cout << "The result is : " <<
  
   simple_api(x = 4, y = 1) 
   
   
   << std::endl;
  
  same_api_with_callback(
    x = 1,
    y = 2, 
    special_callback_named = [](auto&& result) {
    std::cout << "The result is : " << result << std::endl;
    std::cout << "This works because constexpr assignement happens on compile time." << std::endl;
  });


  return 0;
}