// Copyright 2019 Sheldon Robinson. All Rights Reserved.

#ifndef XIC_DEFINNES_H_
#define XIC_DEFINNES_H_

#include <boost/predef/hardware/simd.h>
#include <boost/predef/make.h>
#include <boost/preprocessor/stringize.hpp>

#if BOOST_PREDEF_MAKE_10_VRP(BOOST_HW_SIMD_X86) >= BOOST_PREDEF_MAKE_10_VRP(BOOST_HW_SIMD_X86_SSE4_1_VERSION)
#define BOOST_UUID_USE_SSE41 1
#elif BOOST_PREDEF_MAKE_10_VRP(BOOST_HW_SIMD_X86) >= BOOST_PREDEF_MAKE_10_VRP(BOOST_HW_SIMD_X86_SSE3_VERSION)
#define BOOST_UUID_USE_SSE3 1
#elif BOOST_PREDEF_MAKE_10_VRP(BOOST_HW_SIMD_X86) >= BOOST_PREDEF_MAKE_10_VRP(BOOST_HW_SIMD_X86_SSE2_VERSION)
#define  BOOST_UUID_USE_SSE2 1
#endif

#include <boost/uuid/uuid.hpp>

#endif //XIC_DEFINNES_H_
