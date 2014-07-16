using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Canny
{
    class CannyDetector
    {
        private static int[] STEP_X = new int[8] { 1, 0, -1, 0, 1, 1, -1, -1 };
        private static int[] STEP_Y = new int[8] { 0, 1, 0, -1, 1, -1, 1, -1 };

        public static void detect(Bitmap image, out Bitmap edge, double lowRatio = 0.4, double highRatio = 0.95)
        {
            double[,] gray = new double[image.Width, image.Height];
            for (int x = 0; x < image.Width; ++x)
            {
                for (int y = 0; y < image.Height; ++y)
                {
                    gray[x, y] = image.GetPixel(x, y).GetBrightness();
                }
            }
            double[,] filtered;
            GaussianFilter.filter(gray, out filtered);
            double[,] mag = new double[image.Width, image.Height];
            double[,] ang = new double[image.Width, image.Height];
            for (int x = 0; x < image.Width - 1; ++x)
            {
                for (int y = 0; y < image.Height - 1; ++y)
                {
                    double P = filtered[x, y + 1] + filtered[x + 1, y + 1] - filtered[x, y] - filtered[x + 1, y];
                    double Q = filtered[x, y] + filtered[x, y + 1] - filtered[x + 1, y] - filtered[x + 1, y + 1];
                    mag[x, y] = Math.Sqrt(P * P + Q * Q);
                    ang[x, y] = Math.Atan2(Q, P);
                    if (ang[x, y] < 0.0)
                    {
                        ang[x, y] += Math.PI;
                    }
                }
            }
            int[] tx = new int[2];
            int[] ty = new int[2];
            bool[,] maximal = new bool[image.Width, image.Height];
            for (int x = 0; x < image.Width; ++x)
            {
                for (int y = 0; y < image.Height; ++y)
                {
                    int dirX, dirY;
                    if (ang[x, y] <= Math.PI * 0.125 || ang[x, y] >= Math.PI * 0.875)
                    {
                        dirX = 0;
                        dirY = 1;
                    }
                    else if (ang[x, y] < Math.PI * 0.375)
                    {
                        dirX = 1;
                        dirY = -1;
                    }
                    else if (ang[x, y] < Math.PI * 0.625)
                    {
                        dirX = 1;
                        dirY = 0;
                    }
                    else
                    {
                        dirX = 1;
                        dirY = 1;
                    }
                    tx[0] = x + dirX;
                    tx[1] = x - dirX;
                    ty[0] = y + dirY;
                    ty[1] = y - dirY;
                    maximal[x, y] = true;
                    for (int k = 0; k < 2; ++k)
                    {
                        if (tx[k] >= 0 && tx[k] < image.Width)
                        {
                            if (ty[k] >= 0 && ty[k] < image.Height)
                            {
                                if (mag[x, y] < mag[tx[k], ty[k]])
                                {
                                    maximal[x, y] = false;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            int[] histogram = new int[100];
            for (int x = 0; x < image.Width; ++x)
            {
                for (int y = 0; y < image.Height; ++y)
                {
                    if (!maximal[x, y])
                    {
                        mag[x, y] = 0.0;
                    }
                    histogram[(int)Math.Floor(mag[x, y] * 50)] += 1;
                }
            }
            double highThreshold = 0.0;
            for (int i = 1; i < 100; ++i)
            {
                histogram[i] += histogram[i - 1];
                if (1.0 * histogram[i] / image.Width / image.Height > highRatio)
                {
                    highThreshold = (i + 1) / 50.0;
                    break;
                }
            }
            double lowThreshold = lowRatio * highThreshold;
            bool[,] highEdge = new bool[image.Width, image.Height];
            bool[,] lowEdge = new bool[image.Width, image.Height];
            int test = 0;
            for (int x = 0; x < image.Width; ++x)
            {
                for (int y = 0; y < image.Height; ++y)
                {
                    highEdge[x, y] = mag[x, y] > highThreshold;
                    if (mag[x, y] > highThreshold)
                    {
                        test += 1;
                    }
                    lowEdge[x, y] = mag[x, y] > lowThreshold;
                }
            }
            bool[,] exEdge = new bool[image.Width, image.Height];
            bool[,] visit = new bool[image.Width, image.Height];
            for (int x = 0; x < image.Width; ++x)
            {
                for (int y = 0; y < image.Height; ++y)
                {
                    if (highEdge[x, y])
                    {
                        extend(x, y, lowEdge, visit, exEdge);
                    }
                }
            }
            edge = new Bitmap(image.Width, image.Height);
            for (int x = 0; x < image.Width; ++x)
            {
                for (int y = 0; y < image.Height; ++y)
                {
                    if (exEdge[x, y])
                    {
                        edge.SetPixel(x, y, Color.White);
                    }
                    else
                    {
                        edge.SetPixel(x, y, Color.Black);
                    }
                }
            }
        }

        private static void extend(int x, int y, bool[,] lowEdge, bool[,] visit, bool[,] exEdge)
        {
            if (!visit[x, y])
            {
                visit[x, y] = true;
                exEdge[x, y] = true;
                for (int k = 0; k < 8; ++k)
                {
                    int tx = x + STEP_X[k];
                    int ty = y + STEP_Y[k];
                    if (tx >= 0 && tx < lowEdge.GetLength(0))
                    {
                        if (ty >= 0 && ty < lowEdge.GetLength(1))
                        {
                            if (lowEdge[tx, ty])
                            {
                                extend(tx, ty, lowEdge, visit, exEdge);
                            }
                        }
                    }
                }
            }
        }
    }
}
