using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Train
{
    class LabGradient
    {
        private LabColor[,] mag;
        private LabColor[,] ang;

        public LabGradient(LabBitmap bitmap)
        {
            this.mag = new LabColor[bitmap.Width(), bitmap.Height()];
            this.ang = new LabColor[bitmap.Width(), bitmap.Height()];
            for (int x = 0; x < bitmap.Width() - 1; ++x)
            {
                for (int y = 0; y < bitmap.Height() - 1; ++y)
                {
                    LabColor color00 = bitmap.GetPixel(x, y);
                    LabColor color01 = bitmap.GetPixel(x, y + 1);
                    LabColor color10 = bitmap.GetPixel(x + 1, y);
                    LabColor color11 = bitmap.GetPixel(x + 1, y + 1);
                    LabColor p = (color01 - color00 + color11 - color10) * 0.5;
                    LabColor q = (color00 - color10 + color01 - color11) * 0.5;
                    LabColor t = p * p + q * q;
                    this.mag[x, y].L = Math.Sqrt(t.L);
                    this.mag[x, y].a = Math.Sqrt(t.a);
                    this.mag[x, y].b = Math.Sqrt(t.b);
                    this.ang[x, y].L = Math.Atan2(q.L, p.L);
                    this.ang[x, y].a = Math.Atan2(q.a, p.a);
                    this.ang[x, y].b = Math.Atan2(q.b, p.b);
                }
            }
        }

        public LabColor getMagnitude(int x, int y)
        {
            return this.mag[x, y];
        }

        public LabColor getAngle(int x, int y)
        {
            return this.ang[x, y];
        }
    }
}
