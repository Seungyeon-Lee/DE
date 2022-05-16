#include <algorithm>
#include "gtest/gtest.h"
#include "Helper.h"
#include "Math/VEMatrix3.h"
#include "Math/VEMatrix4.h"
#include "Math/VEAffineTransform2.h"
#include "Math/VEAffineTransform3.h"

TEST(AffineTransform, Equal)
{
    auto body = [](auto at, auto m)
    {
        using AT = decltype(at);
        using M = decltype(m);
        M a, b, c;
        RendomObjectsWithValuesForEqualTest<M>(a, b, c);
        AT a2(a);
        AT b2(a);
        AT c2(c);
        EXPECT_EQ(true, a2 == b2);
        EXPECT_EQ(false, a2 == c2);
    };
    body(VEAffineTransform2(), VEMatrix3());
    body(VEAffineTransform3(), VEMatrix4());
}

TEST(AffineTransform, NotEqual)
{
    auto body = [](auto at, auto m)
    {
        using AT = decltype(at);
        using M = decltype(m);
        M a, b, c;
        RendomObjectsWithValuesForEqualTest<M>(a, b, c);
        AT a2(a);
        AT b2(a);
        AT c2(c);
        EXPECT_EQ(false, a2 != b2);
        EXPECT_EQ(true, a2 != c2);
    };
    body(VEAffineTransform2(), VEMatrix3());
    body(VEAffineTransform3(), VEMatrix4());
}

TEST(AffineTransform, Translate)
{
    auto body = [](auto at, auto m, auto v)
    {
        using AT = decltype(at);
        using M = decltype(m);
        using V = decltype(v);
        m = RendomObjectWithValues<M>();
        v = RendomObjectWithValues<V>();
        at = AT(m);
        at.Translate(v);
        auto r = AT(m);

        int size = sizeof(r.translation.value) / sizeof(r.translation.value[0]);
        for (int i = 0; i < size; ++i)
        {
            r.translation.value[i] += v.value[i];
        }
        EXPECT_EQ(r, at);
    };
    body(VEAffineTransform2(), VEMatrix3(), VEVector2());
    body(VEAffineTransform3(), VEMatrix4(), VEVector3());
}
