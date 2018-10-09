using System;
using System.Runtime.InteropServices;
using AForge.Imaging.Filters;
using AForge.Imaging;
using System.Drawing;
using System.Drawing.Imaging;

namespace some_lib_wrap
{
    [StructLayout(LayoutKind.Sequential, Pack = 8)]
    public struct data
    {
        [MarshalAs(UnmanagedType.I1)]
        public bool is_data_corrupted;
        [MarshalAs(UnmanagedType.U1)]
        public byte counter;
        [MarshalAs(UnmanagedType.R4)]
        public float X;
        [MarshalAs(UnmanagedType.R4)]
        public float Y;
        [MarshalAs(UnmanagedType.R4)]
        public float Z;
    };

    public class device : IDisposable
    {
        public Bitmap image_rgb { private set; get; }
        public data[] data_set1 { private set; get; } = new data[160];
        public data[] data_set2 { private set; get; } = new data[160];
        public byte[,] RGGB_image { private set; get; } = new byte[320, 320];
        private IntPtr unmanaged_RGGB_ptr = Marshal.AllocHGlobal(320 * 320);
        private IntPtr unmanaged_data_set1_ptr = Marshal.AllocHGlobal(160 * Marshal.SizeOf(typeof(data)));
        private IntPtr unmanaged_gyr_data_ptr = Marshal.AllocHGlobal(160 * Marshal.SizeOf(typeof(data)));
        bool disposed = false;      // Flag: Has Dispose already been called?

        public device()
        {
            init_device();
        }

        private long init_device()
        {
            return PInvokeDll.init_device();
        }
        private long clean_up_device()//implement IDisposable here instead
        {
            Marshal.FreeHGlobal(this.unmanaged_RGGB_ptr);   //if IntPtr is IntPrt.Zero, FreeHGlobal does nothing
            this.unmanaged_RGGB_ptr = IntPtr.Zero;
            Marshal.FreeHGlobal(this.unmanaged_data_set1_ptr);
            this.unmanaged_data_set1_ptr = IntPtr.Zero;
            Marshal.FreeHGlobal(this.unmanaged_gyr_data_ptr);
            this.unmanaged_gyr_data_ptr = IntPtr.Zero;
            return PInvokeDll.clean_up_device();
        }
        public unsafe long get_data()
        {
            Int64 rest = PInvokeDll.get_data(
                this.unmanaged_RGGB_ptr,
                this.unmanaged_data_set1_ptr,
                this.unmanaged_gyr_data_ptr);
            if (rest != 1)
            {
                return -1;
            }

            for (int i = 0; i < 160; i++)
            {
                this.data_set1[i] = (data)
                    Marshal.PtrToStructure(this.unmanaged_data_set1_ptr + i * Marshal.SizeOf(typeof(data)), typeof(data));
                this.data_set2[i] = (data)
                    Marshal.PtrToStructure(this.unmanaged_gyr_data_ptr + i * Marshal.SizeOf(typeof(data)), typeof(data));
            }
            Bitmap bitmap_grayscale = new Bitmap(320, 320, PixelFormat.Format8bppIndexed);
            BitmapData bitmap_data = null;
            try
            {
                bitmap_data = bitmap_grayscale.LockBits(
                 new Rectangle(0, 0, bitmap_grayscale.Width, bitmap_grayscale.Height),
                 ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
                for (int y = 0; y < bitmap_grayscale.Height; ++y)
                {
                    byte* targetRow = (byte*)bitmap_data.Scan0 + (y * bitmap_data.Stride);
                    for (int x = 0; x < bitmap_grayscale.Width; ++x)
                    {
                        targetRow[x] = Marshal.ReadByte(this.unmanaged_RGGB_ptr, y * bitmap_grayscale.Width + x);
                    }
                }
            }
            finally
            {
                if (bitmap_data != null)
                    bitmap_grayscale.UnlockBits(bitmap_data);
            }
            BayerFilter bayer_filter = new BayerFilter();
            bayer_filter.BayerPattern = new int[2, 2] { { RGB.R, RGB.G }, { RGB.G, RGB.B } };
            this.image_rgb = bayer_filter.Apply(bitmap_grayscale);
            return 1;
        }

        // Public implementation of Dispose pattern callable by consumers.
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        // Protected implementation of Dispose pattern.
        protected virtual void Dispose(bool disposing)
        {
            if (disposed)
                return;
            if (disposing)
            {
                // Free any other managed objects here.
            }
            clean_up_device();
            this.disposed = true;
        }

        ~device()
        {
            Dispose(false);
        }
    }

    public class PInvokeDll
    {
        [DllImport("some_lib.dll", EntryPoint = "init_device", CallingConvention = CallingConvention.Cdecl)]
        public static extern Int64 init_device();

        [DllImport("some_lib.dll", EntryPoint = "get_data", CallingConvention = CallingConvention.Cdecl)]
        unsafe public static extern Int64 get_data(
            IntPtr RGGB_image_ptr,
            IntPtr data_set1_ptr,
            IntPtr data_set2_ptr);

        [DllImport("some_lib.dll", EntryPoint = "clean_up_device", CallingConvention = CallingConvention.Cdecl)]
        public static extern Int64 clean_up_device();
    }
}
