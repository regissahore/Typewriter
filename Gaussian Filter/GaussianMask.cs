using System;

namespace Gaussian
{
    class GaussianMask
    {
        public double[,] mask;

        public GaussianMask(int rowNum, int colNum, double sigma)
        {
            int mr = rowNum >> 1;
            int mc = colNum >> 1;
            this.mask = new double[rowNum, colNum];
            double constant1 = -1.0 / (2.0 * sigma * sigma);
            double constant2 = 1.0 / (2 * Math.PI * sigma * sigma);
            double sum = 0.0;
            for (int r = 0; r < rowNum; ++r)
            {
                for (int c = 0; c < colNum; ++c)
                {
                    int dr = r - mr;
                    int dc = c - mc;
                    this.mask[r, c] = Math.Exp((dr * dr + dc * dc) * constant1) * constant2;
                    sum += this.mask[r, c];
                }
            }
            for (int r = 0; r < rowNum; ++r)
            {
                for (int c = 0; c < colNum; ++c)
                {
                    this.mask[r, c] /= sum;
                }
            }
        }

        public int rowNum()
        {
            return mask.GetLength(0);
        }

        public int colNum()
        {
            return mask.GetLength(1);
        }
    }
}
