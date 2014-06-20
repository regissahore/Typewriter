using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Train
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length >= 1)
            {
                if (args[0] == "train")
                {
                    if (args.Length >= 4)
                    {
                        new Train(args[1], args[2], args[3]);
                    }
                    else
                    {
                        Console.WriteLine("train <low> <high> <save>");
                    }
                }
                else if (args[0] == "enhance")
                {
                    if (args.Length >= 3)
                    {
                        new Enhance(args[1], args[2]);
                    }
                    else
                    {
                        Console.WriteLine("enhance <input> <output>");
                    }
                }
            }
            else
            {
                Console.WriteLine("train/enhance <parameters>");
            }
        }
    }
}
