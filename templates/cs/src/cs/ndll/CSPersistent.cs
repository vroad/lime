using System;
using System.Runtime.InteropServices;

namespace cs.ndll
{
    class CSPersistent : IDisposable
    {
        internal object Value { get; private set; }
        internal GCHandle Handle { get; private set; }
        private bool disposed;

        internal CSPersistent(object value)
        {
            Value = value;
            Handle = GCHandle.Alloc(this);
            disposed = false;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (disposed)
                return;
            
            Handle.Free();
            disposed = true;
        }

        ~CSPersistent()
        {
            Dispose(false);
        }
    }
}
