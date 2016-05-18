using System;
using System.Runtime.InteropServices;

namespace cs.ndll
{
    class NativeMethods
    {
        public static IntPtr LoadLibraryWrap(String filename)
        {
#if true
            return LoadLibrary(filename + ".ndll");
#else
            return dlopen(filename, RTLD_NOW);
#endif
        }

        public static void FreeLibraryWrap(IntPtr handle)
        {
#if true
            FreeLibrary(handle);
#else
            dlclose(handle);
#endif
        }

        public static IntPtr GetProcAddressWrap(IntPtr handle, String symbol)
        {
#if true
            return GetProcAddress(handle, symbol);
#else
            return dlsym(handle, symbol);
#endif
        }

        internal const int RTLD_NOW = 2;

#if true
        [DllImport("kernel32", CharSet = CharSet.Unicode, SetLastError = true)]
        private static extern IntPtr LoadLibrary(String lpFileName);
        [DllImport("kernel32", SetLastError = true)]
        private static extern bool FreeLibrary(IntPtr hModule);
        [DllImport("kernel32", SetLastError = true, ExactSpelling = false, BestFitMapping = false, ThrowOnUnmappableChar = true)]
        private static extern IntPtr GetProcAddress(IntPtr hModule, [MarshalAs(UnmanagedType.LPStr)]String lpProcName);
#else
        [DllImport("dl", BestFitMapping = false, ThrowOnUnmappableChar = true)]
        private static extern IntPtr dlopen([MarshalAs(UnmanagedType.LPTStr)]String filename, int flags);
        [DllImport("dl")]
        private static extern int dlclose(IntPtr handle);
        [DllImport("dl", BestFitMapping = false, ThrowOnUnmappableChar = true)]
        private static extern IntPtr dlsym(IntPtr handle, [MarshalAs(UnmanagedType.LPTStr)] String symbol);
#endif
    }
}
