using System;
using System.Drawing;

namespace ImageSegmentation
{
    class GaussianFilter
    {
        public static void filter(LabBitmap origin, out LabBitmap delt, int rowNum, int colNum, double sigma)
        {
            GaussianMask mask = new GaussianMask(rowNum, colNum, sigma);
            delt = new LabBitmap(origin.Width(), origin.Height());
            int midRow = rowNum >> 1;
            int midCol = colNum >> 1;
            for (int r = 0; r < origin.Height(); ++r)
            {
                for (int c = 0; c < origin.Width(); ++c)
                {
                    double L = 0.0;
                    double a = 0.0;
                    double b = 0.0;
                    for (int i = 0; i < rowNum; ++i)
                    {
                        for (int j = 0; j < colNum; ++j)
                        {
                            int shiftRow = (r + i - midRow + origin.Height()) % origin.Height();
                            int shiftCol = (c + j - midCol + origin.Width()) % origin.Width();
                            LabColor color = origin.GetPixel(shiftCol, shiftRow);
                            L += color.L * mask.mask[i, j];
                            a += color.a * mask.mask[i, j];
                            b += color.b * mask.mask[i, j];
                        }
                    }
                    delt.SetPixel(c, r, new LabColor(L, a, b));
                }
            }
        }
    }
}
