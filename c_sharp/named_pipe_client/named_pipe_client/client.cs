using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Text;
using System.Diagnostics;

namespace test_pipe
{
    class Program
    {
        static void Main(string[] args)
        {
            foreach (var process in Process.GetProcessesByName("named_pipe_server"))
            {
                process.Kill();
            }
            //run named pipe server 
            ProcessStartInfo start_info = new ProcessStartInfo();
            start_info.CreateNoWindow = true;
            start_info.UseShellExecute = true;
            start_info.FileName = "..\\..\\..\\named_pipe_server\\bin\\Debug\\named_pipe_server.exe";
            Process ac_process = Process.Start(start_info);
            //connect to named pipe
            NamedPipeClientStream pipe_client = new NamedPipeClientStream("AC_pipe");
            pipe_client.Connect();

            float yaw_degree = 0.0f;
            float pitch_degree = 0.0f;
            Random i = new Random();
            Random j = new Random();
            yaw_degree = (float)i.Next() + (float)j.Next() / 10.0f;
            pitch_degree = (float)j.Next() + (float)i.Next() / 10.0f;
            byte[] command = util.form_byte_array(order_type.Pose, false, yaw_degree, pitch_degree);
            Console.WriteLine("send: "
                + order_type.Reset.ToString()
                + ", "
                + true.ToString()
                + ", "
                + yaw_degree.ToString()
                + ", "
                + pitch_degree.ToString());
            pipe_client.Write(command, 0, 16);
            //read reply form server
            byte[] reply = new byte[16];
            pipe_client.Read(reply, 0, 16);
            reply pack = util.convert_to_reply(reply);
            Console.WriteLine("received: "
                + pack.order_type.ToString()
                + ", "
                + pack.is_completed.ToString()
                + ", "
                + pack.yaw_degree.ToString()
                + ", "
                + pack.pitch_degree.ToString());

            Console.ReadKey();
        }
    }
}
