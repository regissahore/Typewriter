using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Train
{
    class Train
    {
        struct Feature
        {
            public double L, a, b;
            public double Lg, ag, bg;
            public void setColor(LabColor color)
            {
                L = color.L;
                a = color.a;
                b = color.b;
            }

            public void setGradient(LabColor gradient)
            {
                Lg = gradient.L;
                ag = gradient.a;
                bg = gradient.b;
            }
        }
        private List<Feature> lowFeature = new List<Feature>();
        private List<Feature> highFeature = new List<Feature>();

        public Train(string lowPath, string highPath, string savePath)
        {
            loadFeatures(lowPath, highPath);
        }

        private void loadFeatures(string lowPath, string highPath)
        {
            foreach (string fileName in Directory.GetFiles(lowPath))
            {
                if (File.Exists(highPath + "/" + fileName))
                {
                    loadFeature(lowPath + "/" + fileName, highPath + "/" + fileName);
                }
            }
            foreach (string dirName in Directory.GetDirectories(lowPath))
            {
                if (Directory.Exists(highPath + "/" + dirName))
                {
                    loadFeatures(lowPath + "/" + dirName, highPath + "/" + dirName);
                }
            }
        }

        private void loadFeature(string lowPath, string highPath)
        {
            Bitmap filtered;
            Bitmap bitmap = new Bitmap(lowPath);
            GaussianFilter.filter(bitmap, out filtered, 5, 5, 2.0);
            LabBitmap lowLab = new LabBitmap(bitmap);
            bitmap = new Bitmap(highPath);
            GaussianFilter.filter(bitmap, out filtered, 5, 5, 2.0);
            LabBitmap highLab = new LabBitmap(bitmap);
            bitmap.Dispose();
            filtered.Dispose();
            if (lowLab.Width() == highLab.Width() && lowLab.Height() == highLab.Height())
            {
                LabGradient lowGradient = new LabGradient(lowLab);
                LabGradient highGradient = new LabGradient(highLab);
                for (int x = 0; x < lowLab.Width(); ++x)
                {
                    for (int y = 0; y < lowLab.Height(); ++y)
                    {
                        Feature feature = new Feature();
                        feature.setColor(lowLab.GetPixel(x, y));
                        feature.setGradient(lowGradient.getMagnitude(x, y));
                        lowFeature.Add(feature);
                        feature = new Feature();
                        feature.setColor(highLab.GetPixel(x, y));
                        feature.setGradient(highGradient.getMagnitude(x, y));
                        highFeature.Add(feature);
                    }
                }
            }
        }
    }
}
