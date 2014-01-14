using System;
using System.Drawing;

namespace SLIC
{
    class XYZColor
    {
        public double X;
        public double Y;
        public double Z;

        public static readonly XYZColor D65 = new XYZColor(0.9505, 1.0, 1.0890);

        public XYZColor(Color color)
        {
            double R = color.R / 255.0;
            double G = color.G / 255.0;
            double B = color.B / 255.0;

            this.X = 0.4674162 * R + 0.2944512 * G + 0.1886026 * B;
            this.Y = 0.2410115 * R + 0.6835475 * G + 0.0754410 * B;
            this.Z = 0.0219101 * R + 0.0736128 * G + 0.9933071 * B;
        }

        public XYZColor(double X, double Y, double Z)
        {
            this.X = X;
            this.Y = Y;
            this.Z = Z;
        }

        public Color RGB()
        {
            double r = 2.7454669 * X - 1.1358136 * Y - 0.4350269 * Z;
            double g = -0.9692660 * X + 1.8760108 * Y + 0.0415560 * Z;
            double b = 0.0112723 * X - 0.1139754 * Y + 1.0132541 * Z;

            byte R = (byte)(r * 255.0);
            byte G = (byte)(g * 255.0);
            byte B = (byte)(b * 255.0);

            return Color.FromArgb(R, G, B);
        }
    }
}
