using System;
using System.Runtime.InteropServices;

namespace cs.ndll
{
	class DelegateConverter<T> : IDisposable
    {
        private T func;
        private IntPtr funcPtr;
        private GCHandle handle;
        private bool initialized;

        internal DelegateConverter(T func)
        {
            this.func = func;
            initialized = false;
        }

        ~DelegateConverter()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (!initialized)
                return;

            handle.Free();
            initialized = false;
        }

        internal IntPtr ToPointer()
        {
            if (!initialized)
            {
                funcPtr = Marshal.GetFunctionPointerForDelegate(func as Delegate);
                handle = GCHandle.Alloc(funcPtr, GCHandleType.Pinned);
                initialized = true;
            }
            return (IntPtr)handle.Target;
        }
    }
}