using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SLIC
{
    static class Program
    {
        static void Main()
        {
            for (int k = 100; k <= 1000; k += 100)
            {
                LabBitmap bitmap = new LabBitmap("test.jpg");
                ImageSegment segment = new ImageSegment();
                int[,] belong = segment.segment(bitmap, k);
                for (int i = 0; i < bitmap.Width() - 1; ++i)
                {
                    for (int j = 0; j < bitmap.Height() - 1; ++j)
                    {
                        if (belong[i, j] != belong[i + 1, j] || belong[i, j] != belong[i, j + 1])
                        {
                            LabColor color = bitmap.GetPixel(i, j);
                            color.L = 0.0;
                            bitmap.SetPixel(i, j, new LabColor(Color.FromArgb(0, 255, 0)));
                        }
                    }
                }
                bitmap.Save("test" + (k / 100) + ".jpg");
            }
        }
    }
}
