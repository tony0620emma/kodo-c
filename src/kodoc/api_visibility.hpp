// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#if defined(_MSC_VER)
    #if defined(KODOC_DLL_EXPORTS)
        #define KODOC_API __declspec(dllexport)
    #else
        #define KODOC_API __declspec(dllimport)
    #endif
#else
  #if __GNUC__ >= 4
    #define KODOC_API __attribute__ ((visibility ("default")))
  #else
    #define KODOC_API
  #endif
#endif
