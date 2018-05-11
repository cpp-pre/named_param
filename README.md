# cpp-pre::named_param
A small header to create named_parameter in C++.

This is useful when implementing API with many parameters, sometimes optional ones, it allows to specify the name of the parameter on the call-site.

An example would be : 

```cpp
  http_get("http://github.com", on_success = [](auto&& result) {
    std::cout << "The result is : " << result.http_code << std::endl;
  });
```

## Usage
See [INSTALL](./INSTALL.md) and [simple_named_parameter.cpp](./examples/simple_named_parameter.cpp) for an example.

# License
[Boost Sofware License](./LICENSE.md), please just reproduce copyrights : 
```
Copyright (c) 2018 Damien Buhl alias daminetreg
```

