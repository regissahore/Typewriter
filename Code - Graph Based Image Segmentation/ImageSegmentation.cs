using System;
using System.Drawing;
using System.Collections.Generic;

namespace ImageSegmentation
{
    class ImageSegmentation
    {
        struct Edge
        {
            public int u, v;
            public double w;
        }
        private Edge[] edge;
        private int edgeNum;
        private int width;
        private int height;
        private int[] component;
        private int[] size;
        private double[] innerDist;
        private static double K = 100.0;
        private static double M = 1.0;

        public ImageSegmentation()
        {
        }

        public void segment(ref LabBitmap origin)
        {
            LabBitmap bitmap;
            GaussianFilter.filter(origin, out bitmap, 3, 3, 0.8);
            width = bitmap.Width();
            height = bitmap.Height();
            edgeNum = 0;
            edge = new Edge[(width - 1) * height + width * (height - 1) + (width - 1) * (height - 1) * 2];
            for (int x = 0; x < width; ++x)
            {
                for (int y = 0; y < height - 1; ++y)
                {
                    addEdge(getStatus(x, y), getStatus(x, y + 1), Math.Abs(bitmap.GetPixel(x, y).L - bitmap.GetPixel(x, y + 1).L));
                }
            }
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width - 1; ++x)
                {
                    addEdge(getStatus(x, y), getStatus(x + 1, y), Math.Abs(bitmap.GetPixel(x, y).L - bitmap.GetPixel(x + 1, y).L));
                }
            }
            for (int x = 0; x < width - 1; ++x)
            {
                for (int y = 0; y < height - 1; ++y)
                {
                    addEdge(getStatus(x, y), getStatus(x + 1, y + 1), Math.Abs(bitmap.GetPixel(x, y).L - bitmap.GetPixel(x + 1, y + 1).L));
                }
            }
            for (int x = 1; x < width; ++x)
            {
                for (int y = 0; y < height - 1; ++y)
                {
                    addEdge(getStatus(x, y), getStatus(x - 1, y + 1), Math.Abs(bitmap.GetPixel(x, y).L - bitmap.GetPixel(x - 1, y + 1).L));
                }
            }
            sort(0, edgeNum - 1);
            component = new int[bitmap.Width() * bitmap.Height()];
            size = new int[bitmap.Width() * bitmap.Height()];
            innerDist = new double[bitmap.Width() * bitmap.Height()];
            for (int x = 0; x < width; ++x)
            {
                for (int y = 0; y < height; ++y)
                {
                    component[getStatus(x, y)] = getStatus(x, y);
                    size[getStatus(x, y)] = 1;
                    innerDist[getStatus(x, y)] = 0.0;
                }
            }
            for (int i = 0; i < edgeNum; ++i)
            {
                int u = find(edge[i].u);
                int v = find(edge[i].v);
                if (u != v)
                {
                    double dist = M * Math.Min(innerDist[u] + K / size[u], innerDist[v] + K / size[v]);
                    if (edge[i].w < dist)
                    {
                        combine(u, v);
                        innerDist[u] = Math.Max(innerDist[u], edge[i].w);
                    }
                }
            }
        }

        public int getComponent(int x, int y)
        {
            return component[getStatus(x, y)];
        }

        public Bitmap getSegmentBitmap()
        {
            Bitmap bitmap = new Bitmap(width, height);
            Dictionary<int, Color> dict = new Dictionary<int, Color>();
            Random random = new Random();
            for (int x = 0; x < width; ++x)
            {
                for (int y = 0; y < height; ++y)
                {
                    int c = component[find(getStatus(x, y))];
                    Color color = new Color();
                    if (!dict.TryGetValue(c, out color))
                    {
                        color = Color.FromArgb(random.Next(256), random.Next(256), random.Next(256));
                        dict.Add(c, color);
                    }
                    bitmap.SetPixel(x, y, color);
                }
            }
            return bitmap;
        }

        private void addEdge(int u, int v, double w)
        {
            edge[edgeNum].u = u;
            edge[edgeNum].v = v;
            edge[edgeNum].w = w;
            ++edgeNum;
        }

        private int getStatus(int x, int y)
        {
            return x + y * width;
        }

        private int getX(int status)
        {
            return status % width;
        }

        private int getY(int status)
        {
            return status / width;
        }

        private void sort(int left, int right)
        {
            if (left < right)
            {
                int i = left - 1;
                int j = right + 1;
                double mid = edge[left].w;
                while (true)
                {
                    while (edge[++i].w < mid) ;
                    while (edge[--j].w > mid) ;
                    if (i >= j)
                    {
                        break;
                    }
                    Edge temp = edge[i];
                    edge[i] = edge[j];
                    edge[j] = temp;
                }
                sort(left, i - 1);
                sort(j + 1, right);
            }
        }

        private int find(int x)
        {
            if (x == component[x])
            {
                return x;
            }
            return component[x] = find(component[x]);
        }

        private void combine(int x, int y)
        {
            x = find(x);
            y = find(y);
            size[x] += size[y];
            innerDist[x] = Math.Max(innerDist[x], innerDist[y]);
            component[y] = x;
        }
    }
}
