using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace normal_distribution
{
    public class rand_normal
    {//use  Box-Muller transform
        private static Random rand;
        public double std_var { get; private set; } = 1.0f;
        public double mean { get; private set; } = 0.0f;

        public rand_normal()
        {
            rand = new Random();
        }

        public rand_normal(double std_var)
        {
            rand = new Random();
            this.std_var = Math.Abs(std_var);
        }

        public rand_normal(double mean, double std_var)
        {
            rand = new Random();
            this.mean = mean;
            this.std_var = Math.Abs(std_var);
        }
        public double next()
        {
            double u1 = 1.0 - rand.NextDouble(); //uniform(0,1] random doubles
            double u2 = 1.0 - rand.NextDouble();
            double rand_std_normal = Math.Sqrt(-2.0 * Math.Log(u1)) *
                         Math.Sin(2.0 * Math.PI * u2); //random normal(0,1)
            double rand_normal =
                         this.mean + this.std_var * rand_std_normal; //random normal(Mean,Std_var)
            return rand_normal;
        }
    }
}
