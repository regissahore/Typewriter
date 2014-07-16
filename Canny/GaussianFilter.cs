using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Canny
{
    class GaussianFilter
    {
        public static void filter(double[,] origin, out double[,] delt, int rowNum = 3, int colNum = 3, double sigma = 1.0)
        {
            GaussianMask mask = new GaussianMask(rowNum, colNum, sigma);
            delt = new double[origin.GetLength(0), origin.GetLength(1)];
            int midRow = rowNum >> 1;
            int midCol = colNum >> 1;
            for (int r = 0; r < origin.GetLength(0); ++r)
            {
                for (int c = 0; c < origin.GetLength(1); ++c)
                {
                    double filtered = 0.0;
                    for (int i = 0; i < rowNum; ++i)
                    {
                        for (int j = 0; j < colNum; ++j)
                        {
                            int shiftRow = (r + i - midRow + origin.GetLength(0)) % origin.GetLength(0);
                            int shiftCol = (c + j - midCol + origin.GetLength(1)) % origin.GetLength(1);
                            filtered += origin[shiftRow, shiftCol] * mask.mask[i, j];
                        }
                    }
                    delt[r, c] = filtered;
                }
            }
        }
    }
}
