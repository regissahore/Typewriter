#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
/**
 * Y_{n+1} = Y_{n} + h / 6 * (K_1 + 2 * K_2 + 2 * K_3 + K_4)
 * K_1 = F(x_n Y_n)
 * K_2 = F(x_n + h / 2, Y_n + h / 2 * K1)
 * K_3 = F(x_n + h / 2, Y_n + h / 2 * K2)
 * K_4 = F(x_n + h, Y_n + h * K3)
 */

class RungeKutta
{
public:
    RungeKutta(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            y.push_back(0.0);
        }
        x = 0.0;
    }
    void setX(double value)
    {
        x = value;
    }
    void setY(int index, double value)
    {
        y[index] = value;
    }
    void setH(double value)
    {
        h = value / 10;
    }
    double getY(int index) const
    {
        return y[index];
    }
    vector<double>& getY()
    {
        return y;
    }
    void nextStep()
    {
        for (int i = 0; i < 10; ++i)
        {
            vector<double> K1 = F(x, y);
            vector<double> K2 = F(x + h / 2, add(y, mul(h / 2, K1)));
            vector<double> K3 = F(x + h / 2, add(y, mul(h / 2, K2)));
            vector<double> K4 = F(x + h, add(y, mul(h, K3)));
            y = add(y, mul(h / 6, add(add(K1, mul(2, K2)), add(mul(2, K3), K4))));
            x += h;
        }
    }
protected:
    virtual vector<double> F(double x, vector<double> y)
    {
        return y;
    }
private:
    double x;
    vector<double> y;
    double h;
    vector<double> mul(double x, vector<double> y)
    {
        vector<double> z;
        for (int i = 0; i < y.size(); ++i)
        {
            z.push_back(x * y[i]);
        }
        return z;
    }
    vector<double> add(vector<double> x, vector<double> y)
    {
        vector<double> z;
        for (int i = 0; i < y.size(); ++i)
        {
            z.push_back(x[i] + y[i]);
        }
        return z;
    }
};

class RungeKuttaBreakdown3 : public RungeKutta
{
public:
    RungeKuttaBreakdown3() : RungeKutta(4)
    {
        this->setY(0, 1.0);
    }
    void setLambda(double l1, double l2, double l3)
    {
        lambda1 = l1;
        lambda2 = l2;
        lambda3 = l3;
    }
    void setMu(double m1, double m2, double m3)
    {
        mu1 = m1;
        mu2 = m2;
        mu3 = m3;
    }
protected:
    vector<double> F(double x, vector<double> y)
    {
        vector<double> z;
        z.push_back(-(lambda1 + lambda2 + lambda3) * y[0] + mu1 * y[1] + mu2 * y[2] + mu3 * y[3]);
        z.push_back(lambda1 * y[0] - mu1 * y[1]);
        z.push_back(lambda2 * y[0] - mu2 * y[2]);
        z.push_back(lambda3 * y[0] - mu3 * y[3]);
        return z;
    }
private:
    double lambda1, lambda2, lambda3;
    double mu1, mu2, mu3;
};

class RungeKuttaBreakdown4 : public RungeKutta
{
public:
    RungeKuttaBreakdown4() : RungeKutta(5)
    {
        this->setY(0, 1.0);
    }
    void setLambda(double l1, double l2, double l3, double l4)
    {
        lambda1 = l1;
        lambda2 = l2;
        lambda3 = l3;
        lambda4 = l4;
    }
    void setMu(double m1, double m2, double m3, double m4)
    {
        mu1 = m1;
        mu2 = m2;
        mu3 = m3;
        mu4 = m4;
    }
protected:
    vector<double> F(double x, vector<double> y)
    {
        vector<double> z;
        z.push_back(-(lambda1 + lambda2 + lambda3 + lambda4) * y[0] + mu1 * y[1] + mu2 * y[2] + mu3 * y[3] + mu4 * y[4]);
        z.push_back(lambda1 * y[0] - mu1 * y[1]);
        z.push_back(lambda2 * y[0] - mu2 * y[2]);
        z.push_back(lambda3 * y[0] - mu3 * y[3]);
        z.push_back(lambda4 * y[0] - mu4 * y[4]);
        return z;
    }
private:
    double lambda1, lambda2, lambda3, lambda4;
    double mu1, mu2, mu3, mu4;
};

int main()
{
    RungeKuttaBreakdown4 breakdown;
    breakdown.setLambda(0.1, 0.2, 0.3, 0.4);
    breakdown.setMu(0.4, 0.5, 0.6, 0.7);
    breakdown.setH(1);
    for (int i = 1; i < 500; ++i)
    {
        breakdown.nextStep();
        printf("%d: ", i);
        for (int j = 0; j < 4; ++j)
        {
            printf("%.10lf ", breakdown.getY(j));
        }
        printf("\n");
    }
    return 0;
}
