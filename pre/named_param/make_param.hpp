#pragma once

#include <pre/fwd/fwd.hpp>

namespace pre::named_param {

  template<template <class> class Template>
  struct make_param_t {
      template<typename Handler>
      constexpr Template<Handler> operator()(Handler handler) const {return Template<Handler>(handler);}
      template<typename NamedParameter>
      constexpr Template<NamedParameter> operator= (NamedParameter handler) const {return Template<NamedParameter>(handler);}
  };

  struct named_parameter {};

  template <class T>
  struct value_ : named_parameter {

    explicit value_(T v) : v_(v) {}

    operator T() const {
      return v_;
    }

    T v_;
  };

  template <class Callable>
  struct nary_ : named_parameter
  {
    explicit nary_(Callable f) : f_(f) {}

    template<class... TReturn>
    void operator()(TReturn&&... e)
    {
        f_(PRE_FWD(e)...);
    }

    template<class... TReturn>
    void operator()(TReturn&&... e) const
    {
        f_(PRE_FWD(e)...);
    }

    private:
    Callable f_;
  };

}