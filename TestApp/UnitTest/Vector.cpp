#include "gtest/gtest.h"
#include "Helper.h"

#include "VEVector2.h"
#include "VEVector3.h"
#include "VEVector4.h"

#include "VEMatrix2.h"
#include "VEMatrix3.h"
#include "VEMatrix4.h"

TEST(Vector, Equal)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a, b, c;
        RendomObjectsWithValuesForEqualTest<V>(a, b, c);
        EXPECT_EQ(true, a == b);
        EXPECT_EQ(false, a == c);
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}

TEST(Vector, NotEqual)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a, b, c;
        RendomObjectsWithValuesForEqualTest<V>(a, b, c);
        EXPECT_EQ(false, a != b);
        EXPECT_EQ(true, a != c);
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}

TEST(Vector, Add)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RendomObjectWithValues<V>();
        V b = RendomObjectWithValues<V>();
        V r = SumEachValueOfObject<V>(a, b);
        EXPECT_EQ(r, a + b);
        a += b;
        EXPECT_EQ(r, a);
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}

TEST(Vector, Sub)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RendomObjectWithValues<V>();
        V b = RendomObjectWithValues<V>();
        V r = SubEachValueOfObject<V>(a, b);
        EXPECT_EQ(r, a - b);
        a -= b;
        EXPECT_EQ(r, a);
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}

TEST(Vector, ScalarMultiply)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RendomObjectWithValues<V>();
        float s = RendomFloat();
        V r = MulEachValueOfObject<V>(a, s);
        EXPECT_EQ(r, a * s);
        a *= s;
        EXPECT_EQ(r, a);
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}

TEST(Vector, Dot)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RendomObjectWithValues<V>();
        V b = RendomObjectWithValues<V>();
        int dimension = sizeof(a.value) / sizeof(a.value[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += a.value[i] * b.value[i];
        }
        EXPECT_EQ(r, V::Dot(a, b));
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}

TEST(Vector, Cross)
{
    VEVector3 v1{ 1.f, 0.f, 0.f };
    VEVector3 v2{ 0.f, 1.f, 0.f };
    VEVector3 answer{0.f, 0.f, 1.f};
    EXPECT_EQ(answer, VEVector3::Cross(v1, v2));
}

TEST(Vector, MulMatrix)
{
    auto body = [](auto v, auto m)
    {
        using V = decltype(v);
        using M = decltype(m);
        v = RendomObjectWithValues<V>();
        m = RendomObjectWithValues<M>();
        int vDimension = sizeof(v.value) / sizeof(v.value[0]);
        int mDimension = sizeof(m.m[0]) / sizeof(m.m[0][0]);
        V r;
        for (int i = 0; i < vDimension; ++i)
        {
            for (int j = 0; j < mDimension; ++j)
            {
                r.value[i] += v.value[j] * m.m[j][i];
            }
        }
        EXPECT_EQ(r, v * m);
    };
    body(VEVector2(), VEMatrix2());
    body(VEVector3(), VEMatrix3());
    body(VEVector4(), VEMatrix4());
}

TEST(Vector, Length)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RendomObjectWithValues<V>();
        int dimension = sizeof(v.value) / sizeof(v.value[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += v.value[i] * v.value[i];
        }
        EXPECT_EQ(sqrtf(r), v.Length());
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}

TEST(Vector, LengthSq)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RendomObjectWithValues<V>();
        int dimension = sizeof(v.value) / sizeof(v.value[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += v.value[i] * v.value[i];
        }
        EXPECT_EQ(r, v.LengthSq());
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}

TEST(Vector, Normalize)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RendomObjectWithValues<V>();
        V r = v;

        float lenSq = v.LengthSq();
        if (lenSq > 0.0f)
        {
            float lenInv = 1.0f / sqrt(lenSq);
            int vSize = sizeof(v.value) / sizeof(v.value[0]);
            for (int i = 0; i < vSize; ++i)
            {
                r.value[i] *= lenInv;
            }
        }

        EXPECT_EQ(r, v.Normalize());
    };
    body(VEVector2());
    body(VEVector3());
    body(VEVector4());
}
