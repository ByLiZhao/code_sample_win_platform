using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using some_lib_wrap;

namespace test_some_lib
{
    class Program
    {
        static void Main(string[] args)
        {
            device my_device = new device();
            my_device.get_data();
            Console.ReadKey();
        }
    }
}
