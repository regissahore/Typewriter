using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Train
{
    class CannyEdge
    {
        private bool[,] edge;

        public CannyEdge(LabBitmap bitmap)
        {
            this.edge = new bool[bitmap.Width(), bitmap.Height()];
            LabGradient gradient = new LabGradient(bitmap);
            for (int x = 1; x < bitmap.Width() - 1; ++x)
            {
                for (int y = 1; y < bitmap.Height() - 1; ++y)
                {
                    bool flag = true;
                    for (int i = -1; i <= 1; ++i)
                    {
                        for (int j = -1; j <= 1; ++j)
                        {
                            if (i != 0 || j != 0)
                            {
                                if (gradient.getMagnitude(x, y).L < gradient.getMagnitude(x + i, y + j).L)
                                {
                                    flag = false;
                                }
                            }
                        }
                    }
                    if (flag)
                    {
                        this.edge[x, y] = true;
                    }
                }
            }
        }

        bool isGradient(int x, int y)
        {
            return this.edge[x, y];
        }
    }
}
