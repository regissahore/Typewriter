using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Train
{
    class ImageSegment
    {
        private LabBitmap bitmap;
        private int width;
        private int height;
        private int[,] l;
        private double[,] d;
        private int k;
        private int s;
        private struct Center
        {
            public double l, a, b, x, y;
        }
        private Center[] c;
        private bool[,] visit;

        public ImageSegment()
        {
        }

        public int[,] segment(LabBitmap bitmap, int k)
        {
            this.bitmap = bitmap;
            this.width = bitmap.Width();
            this.height = bitmap.Height();
            this.l = new int[this.width, this.height];
            this.d = new double[this.width, this.height];
            this.k = k;
            this.initCenter();
            this.kmeans();
            this.connect();
            return this.l;
        }

        private void initCenter()
        {
            s = (int)Math.Sqrt(this.width * this.height / k);
            int shift = s >> 1;
            int xn = 0;
            int yn = 0;
            double t = shift;
            while (t < width)
            {
                ++xn;
                t += s;
            }
            t = shift;
            while (t < height)
            {
                ++yn;
                t += s;
            }
            c = new Center[xn * yn];
            k = 0;
            for (int i = 0; i < xn; ++i)
            {
                for (int j = 0; j < yn; ++j)
                {
                    int x = shift + i * s;
                    int y = shift + j * s;
                    Center center = new Center();
                    center.l = bitmap.GetPixel(x, y).L;
                    center.a = bitmap.GetPixel(x, y).a;
                    center.b = bitmap.GetPixel(x, y).b;
                    center.x = x;
                    center.y = y;
                    c[k++] = center;
                }
            }
        }

        private void kmeans()
        {
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    l[i, j] = -1;
                    d[i, j] = 1e100;
                }
            }
            double invwt = 1.0 / (s * s / 800.0);
            for (int n = 0; n < 20; ++n)
            {
                for (int m = 0; m < k; ++m)
                {
                    for (int i = -2 * s; i <= 2 * s; ++i)
                    {
                        for (int j = -2 * s; j <= 2 * s; ++j)
                        {
                            int x = (int)c[m].x + i;
                            int y = (int)c[m].y + j;
                            if (x >= 0 && x < width)
                            {
                                if (y >= 0 && y < height)
                                {
                                    double dc = (c[m].l - bitmap.GetPixel(x, y).L) * (c[m].l - bitmap.GetPixel(x, y).L) +
                                        (c[m].a - bitmap.GetPixel(x, y).a) * (c[m].a - bitmap.GetPixel(x, y).a) +
                                        (c[m].b - bitmap.GetPixel(x, y).b) * (c[m].b - bitmap.GetPixel(x, y).b);
                                    double ds = (c[m].x - x) * (c[m].x - x) + (c[m].y - y) * (c[m].y - y);
                                    double D = dc + ds * invwt;
                                    if (D < d[x, y])
                                    {
                                        d[x, y] = D;
                                        l[x, y] = m;
                                    }
                                }
                            }
                        }
                    }
                }
                Center[] newC = new Center[k];
                int[] num = new int[k];
                for (int m = 0; m < k; ++m)
                {
                    newC[m] = new Center();
                    num[m] = 0;
                }
                for (int i = 0; i < width; ++i)
                {
                    for (int j = 0; j < height; ++j)
                    {
                        newC[l[i, j]].l += bitmap.GetPixel(i, j).L;
                        newC[l[i, j]].a += bitmap.GetPixel(i, j).a;
                        newC[l[i, j]].b += bitmap.GetPixel(i, j).b;
                        newC[l[i, j]].x += i;
                        newC[l[i, j]].y += j;
                        ++num[l[i, j]];
                    }
                }
                double E = 0.0;
                for (int m = 0; m < k; ++m)
                {
                    newC[m].l /= num[m];
                    newC[m].a /= num[m];
                    newC[m].b /= num[m];
                    newC[m].x /= num[m];
                    newC[m].y /= num[m];
                    E += (newC[m].x - c[m].x) * (newC[m].x - c[m].x) + (newC[m].y - c[m].y) * (newC[m].y - c[m].y);
                    c[m] = newC[m];
                }
                if (E < 5.0)
                {
                    break;
                }
            }
        }

        private void connect()
        {
            visit = new bool[width, height];
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    visit[i, j] = false;
                }
            }
            for (int i = 0; i < k; ++i)
            {
                dfs((int)c[i].x, (int)c[i].y, i);
            }
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    if (!visit[i, j])
                    {
                        d[i, j] = 1e100;
                        for (int m = 0; m < k; ++m)
                        {
                            double D = (i - c[m].x) * (i - c[m].x) + (j - c[m].y) * (j - c[m].y);
                            if (D < d[i, j])
                            {
                                d[i, j] = D;
                                l[i, j] = m;
                            }
                        }
                    }
                }
            }
        }

        private void dfs(int x, int y, int color)
        {
            if (x >= 0 && x < width)
            {
                if (y >= 0 && y < height)
                {
                    if (!visit[x, y])
                    {
                        if (l[x, y] == color)
                        {
                            visit[x, y] = true;
                            dfs(x + 1, y, color);
                            dfs(x - 1, y, color);
                            dfs(x, y + 1, color);
                            dfs(x, y - 1, color);
                        }
                    }
                }
            }
        }
    }
}
