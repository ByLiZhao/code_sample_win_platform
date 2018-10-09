using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace test_pipe
{
    public enum order_type : Int32
    {
        Pose = 0, Reset = 10, Yaw = 20, Pitch = 30, Rotation = 40, Spin = 50
    };
    public struct reply
    {
        public order_type order_type;
        public bool is_completed;
        public float yaw_degree;
        public float pitch_degree;
    }
    public static class util
    {
        public static byte[] form_byte_array(
            order_type order_type,
            bool para_bool,
            float para_float1,
            float para_float2)
        {
            byte[] arr = new byte[16];
            byte[] t = new byte[4];
            switch (order_type)
            {
                case order_type.Pose:
                    t = BitConverter.GetBytes((Int32)order_type.Pose);
                    break;
                case order_type.Reset:
                    t = BitConverter.GetBytes((Int32)order_type.Reset);
                    break;
                case order_type.Yaw:
                    t = BitConverter.GetBytes((Int32)order_type.Yaw);
                    break;
                case order_type.Pitch:
                    t = BitConverter.GetBytes((Int32)order_type.Pitch);
                    break;
                case order_type.Rotation:
                    t = BitConverter.GetBytes((Int32)order_type.Rotation);
                    break;
                case order_type.Spin:
                    t = BitConverter.GetBytes((Int32)order_type.Spin);
                    break;
                default:
                    break;
            }
            Array.Copy(t, 0, arr, 0, 4);
            if (para_bool)
            {
                Int32 i = 1;
                t = BitConverter.GetBytes(i);
            }
            else
            {
                Int32 i = 0;
                t = BitConverter.GetBytes(i);
            }
            Array.Copy(t, 0, arr, 4, 4);
            t = BitConverter.GetBytes(para_float1);
            Array.Copy(t, 0, arr, 8, 4);
            t = BitConverter.GetBytes(para_float2);
            Array.Copy(t, 0, arr, 12, 4);
            return arr;
        }

        public static byte[] sub_array(byte[] data, int index, int length)
        {
            byte[] result = new byte[length];
            Array.Copy(data, index, result, 0, length);
            return result;
        }

        public static reply convert_to_reply(byte[] arr)
        {
            byte[] op = new byte[4];
            byte[] is_sc = new byte[4];
            byte[] yaw = new byte[4];
            byte[] pitch = new byte[4];
            op = sub_array(arr, 0, 4);
            is_sc = sub_array(arr, 4, 4);
            yaw = sub_array(arr, 8, 4);
            pitch = sub_array(arr, 12, 4);
            reply pack = new reply();
            Int32 op_int = BitConverter.ToInt32(op, 0);
            Int32 is_sc_int = BitConverter.ToInt32(is_sc, 0);
            float yaw_float = BitConverter.ToSingle(yaw, 0);
            float pitch_float = BitConverter.ToSingle(pitch, 0);
            switch (op_int)
            {
                case 0:
                    pack.order_type = order_type.Pose;
                    break;
                case 10:
                    pack.order_type = order_type.Reset;
                    break;
                case 20:
                    pack.order_type = order_type.Yaw;
                    break;
                case 30:
                    pack.order_type = order_type.Pitch;
                    break;
                case 40:
                    pack.order_type = order_type.Rotation;
                    break;
                case 50:
                    pack.order_type = order_type.Spin;
                    break;
                default:
                    break;
            }
            if (is_sc_int == 1)
            {
                pack.is_completed = true;
            }
            else
            {
                pack.is_completed = false;
            }
            pack.yaw_degree = yaw_float;
            pack.pitch_degree = pitch_float;
            return pack;
        }
    }
}

