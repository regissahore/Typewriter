using System;
using System.Drawing;

namespace ImageSegmentation
{
    class LabBitmap
    {
        private LabColor[,] image;

        public LabBitmap(int width, int height)
        {
            this.image = new LabColor[width, height];
        }

        public LabBitmap(string filename)
        {
            Bitmap bitmap = new Bitmap(filename);
            this.image = new LabColor[bitmap.Width, bitmap.Height];
            for (int i = 0; i < bitmap.Width; ++i)
            {
                for (int j = 0; j < bitmap.Height; ++j)
                {
                    this.image[i, j] = new LabColor(bitmap.GetPixel(i, j));
                }
            }
        }

        public int Width()
        {
            return image.GetLength(0);
        }

        public int Height()
        {
            return image.GetLength(1);
        }

        public LabColor GetPixel(int x, int y)
        {
            return this.image[x, y];
        }

        public void SetPixel(int x, int y, LabColor color)
        {
            this.image[x, y] = color;
        }

        public void Save(string filename)
        {
            Bitmap bitmap = new Bitmap(this.Width(), this.Height());
            for (int i = 0; i < this.Width(); ++i)
            {
                for (int j = 0; j < this.Height(); ++j)
                {
                    bitmap.SetPixel(i, j, this.image[i, j].RGB());
                }
            }
            bitmap.Save(filename);
        }
    }
}
