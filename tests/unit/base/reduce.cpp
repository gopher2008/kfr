/**
 * KFR (https://www.kfrlib.com)
 * Copyright (C) 2016-2023 Dan Cazarin
 * See LICENSE.txt for details
 */

#include "kfr/base/tensor.hpp"
#include <kfr/base/reduce.hpp>
#include <kfr/base/simd_expressions.hpp>
#include <kfr/base/univector.hpp>

namespace kfr
{
inline namespace CMT_ARCH_NAME
{

TEST(reduce)
{
    testo::epsilon_scope<void> e(100);
    {
        univector<float, 6> a({ 1, 2, 3, 4, 5, -9 });
        CHECK(sum(a) == 6);
        CHECK(mean(a) == 1);
        CHECK(minof(a) == -9);
        CHECK(maxof(a) == 5);
        CHECK(absminof(a) == 1);
        CHECK(absmaxof(a) == 9);
        CHECK(sumsqr(a) == 136);
        CHECK(rms(a) == 4.760952285695233f);
        CHECK(product(a) == -1080);
    }
    {
        univector<double, 6> a({ 1, 2, 3, 4, 5, -9 });
        CHECK(sum(a) == 6);
        CHECK(mean(a) == 1);
        CHECK(minof(a) == -9);
        CHECK(maxof(a) == 5);
        CHECK(absminof(a) == 1);
        CHECK(absmaxof(a) == 9);
        CHECK(sumsqr(a) == 136);
        CHECK(rms(a) == 4.760952285695233);
        CHECK(product(a) == -1080);
    }
    {
        univector<int, 6> a({ 1, 2, 3, 4, 5, -9 });
        CHECK(sum(a) == 6);
        CHECK(mean(a) == 1);
        CHECK(minof(a) == -9);
        CHECK(maxof(a) == 5);
        CHECK(absminof(a) == 1);
        CHECK(absmaxof(a) == 9);
        CHECK(sumsqr(a) == 136);
        CHECK(product(a) == -1080);
    }
}

TEST(dotproduct)
{
    univector<float, 177> v1 = counter();
    univector<float, 177> v2 = counter() * 2 + 10;
    CHECK(dotproduct(v1, v2) == 3821312);
}

TEST(reduce_multidim)
{
    CHECK(sum(tensor<int, 2>(shape{ 3, 3 }, { 1, 2, 3, 4, 5, 6, 7, 8, 9 })) == 45); //
    CHECK(sum(tensor<int, 3>(shape{ 2, 2, 2 }, { 1, 2, 3, 4, 5, 6, 7, 8 })) == 36); //

    CHECK(maxof(tensor<int, 3>(shape{ 2, 2, 2 }, { 1, 2, 3, 4, 5, 6, 7, 8 })) == 8); //
    CHECK(minof(tensor<int, 3>(shape{ 2, 2, 2 }, { 1, 2, 3, 4, 5, 6, 7, 8 })) == 1); //
    CHECK(product(tensor<int, 3>(shape{ 2, 2, 2 }, { 1, 2, 3, 4, 5, 6, 7, 8 })) == 40320); //
}

} // namespace CMT_ARCH_NAME
} // namespace kfr
