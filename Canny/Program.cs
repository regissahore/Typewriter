using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Canny
{
    class Program
    {
        static void Main(string[] args)
        {
            Bitmap bitmap = new Bitmap("test7.jpg");
            Bitmap edge;
            CannyDetector.detect(bitmap, out edge);
            edge.Save("edge.jpg");
        }
    }
}
