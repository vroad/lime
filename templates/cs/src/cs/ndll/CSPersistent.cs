using System.Runtime.InteropServices;

namespace cs.ndll
{
    class CSPersistent
    {
        internal object Value { get; private set; }
        internal System.Collections.Generic.LinkedListNode<CSPersistent> Node;
        internal GCHandle Handle { get; private set; }

        internal CSPersistent(object value)
        {
            Value = value;
            Handle = GCHandle.Alloc(this);
        }

        internal void Destroy()
        {
            if (!Handle.IsAllocated)
                return;
            
            Handle.Free();
        }
    }
}
