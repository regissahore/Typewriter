using System;
using System.Drawing;

namespace Gaussian
{
    class GaussianFilter
    {
        public static void filter(Bitmap origin, out Bitmap delt, int rowNum, int colNum, double sigma)
        {
            GaussianMask mask = new GaussianMask(rowNum, colNum, sigma);
            delt = new Bitmap(origin.Width, origin.Height);
            int midRow = rowNum >> 1;
            int midCol = colNum >> 1;
            for (int r = 0; r < origin.Height; ++r)
            {
                for (int c = 0; c < origin.Width; ++c)
                {
                    double red = 0.0;
                    double green = 0.0;
                    double blue = 0.0;
                    for (int i = 0; i < rowNum; ++i)
                    {
                        for (int j = 0; j < colNum; ++j)
                        {
                            int shiftRow = (r + i - midRow + origin.Height) % origin.Height;
                            int shiftCol = (c + j - midCol + origin.Width) % origin.Width;
                            Color color = origin.GetPixel(shiftCol, shiftRow);
                            red += color.R * mask.mask[i, j];
                            green += color.G * mask.mask[i, j];
                            blue += color.B * mask.mask[i, j];
                        }
                    }
                    delt.SetPixel(c, r, Color.FromArgb((int)red, (int)green, (int)blue));
                }
            }
        }
    }
}
