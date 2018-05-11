#pragma once

namespace pre::named_param {

  template<template <class> class Template>
  struct make_param_t {
      template<typename NamedParameter>
      constexpr Template<NamedParameter> operator= (NamedParameter handler) const {return Template<NamedParameter>(handler);}
  };

  struct named_parameter {};

  template <class Callable>
  struct unary_ : named_parameter
  {
    explicit unary_(Callable f) : f_(f) {}

    template<class TReturn>
    void operator()(TReturn&& e)
    {
        f_(XXHR_FWD(e));
    }

    private:
    Callable f_;
  };

}