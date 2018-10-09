using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Text;

namespace test_pipe
{
    static class Program
    {
        static void Main()
        {
            NamedPipeServerStream pipe_server = new NamedPipeServerStream("AC_pipe");
            pipe_server.WaitForConnection();
            byte[] command = new byte[16];
            while (true)
            {
                pipe_server.Read(command, 0, command.Length);
                //server do some work according to command received
                //here simply echo command
                reply reply = util.convert_to_reply(command);
                byte[] echo_msg = util.form_byte_array(reply.order_type,
                    reply.is_completed, reply.yaw_degree, reply.pitch_degree);

                if (pipe_server.IsConnected)
                {
                    pipe_server.Write(echo_msg, 0, echo_msg.Length);
                }
                else
                {
                    break;
                }

            }

        }
    }
}

