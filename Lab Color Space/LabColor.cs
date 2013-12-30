using System;
using System.Drawing;

namespace ColorEnhancement
{
    class LabColor
    {
        public double L;
        public double a;
        public double b;

        private double f(double t)
        {
            if (t > 0.008856)
            {
                return Math.Pow(t, 1.0 / 3.0);
            }
            return 7.787 * t + 16.0 / 116.0;
        }

        public LabColor(Color color)
        {
            XYZColor xyz = new XYZColor(color);
            this.L = 116.0 * f(xyz.Y / XYZColor.D65.Y) - 16.0;
            this.a = 500.0 * (f(xyz.X / XYZColor.D65.X) - f(xyz.Y / XYZColor.D65.Y));
            this.b = 200.0 * (f(xyz.Y / XYZColor.D65.Y) - f(xyz.Z / XYZColor.D65.Z));
        }

        public LabColor(double L, double a, double b)
        {
            this.L = L;
            this.a = a;
            this.b = b;
        }

        public Color RGB()
        {
            double delta = 6.0 / 29.0;
            double fy = (this.L + 16) / 116.0;
            double fx = fy + (this.a / 500.0);
            double fz = fy - (this.b / 200.0);

            double X = fx > delta ? XYZColor.D65.X * Math.Pow(fx, 3.0) : (fx - 16.0 / 116.0) * 3 * (delta * delta) * XYZColor.D65.X;
            double Y = fy > delta ? XYZColor.D65.Y * Math.Pow(fy, 3.0) : (fy - 16.0 / 116.0) * 3 * (delta * delta) * XYZColor.D65.Y;
            double Z = fz > delta ? XYZColor.D65.Z * Math.Pow(fz, 3.0) : (fz - 16.0 / 116.0) * 3 * (delta * delta) * XYZColor.D65.Z;

            return new XYZColor(X, Y, Z).RGB();
        }
    }
}
