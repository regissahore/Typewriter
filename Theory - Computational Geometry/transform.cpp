#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct TransformVector
{
    double data[3];
    double x() const
    {
        return data[0];
    }
    double y() const
    {
        return data[1];
    }
};

struct TransformMatrix
{
    double data[3][3];
};

TransformMatrix getIdentityMatrix()
{
    TransformMatrix mat;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            mat.data[i][j] = 0.0;
        }
        mat.data[i][i] = 1.0;
    }
}

TransformMatrix getTranslationMatrix(double tx, double ty)
{
    TransformMatrix mat = getIdentityMatrix();
    mat.data[0][2] = tx;
    mat.data[1][2] = ty;
    return mat;
}

TransformMatrix getScalingMatrix(double sx, double sy)
{
    TransformMatrix mat = getIdentityMatrix();
    mat.data[0][0] = sx;
    mat.data[1][1] = sy;
    return mat;
}

TransformMatrix getRotationMatrix(double theta)
{
    TransformMatrix mat = getIdentityMatrix();
    mat.data[0][0] = cos(theta);
    mat.data[0][1] = -sin(theta);
    mat.data[1][0] = sin(theta);
    mat.data[1][1] = cos(theta);
    return mat;
}

TransformMatrix operator *(const TransformMatrix &a, const TransformMatrix &b)
{
    TransformMatrix c;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            c.data[i][j] = 0.0;
            for (int k = 0; k < 3; ++k)
            {
                c.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return c;
}

TransformVector operator *(const TransformMatrix &a, const TransformVector &b)
{
    TransformVector c;
    for (int i = 0; i < 3; ++i)
    {
        c.data[i] = 0.0;
        for (int j = 0; j < 3; ++j)
        {
            c.data[i] += a.data[i][j] * b.data[j];
        }
    }
    return c;
}

int main()
{
    return 0;
}
