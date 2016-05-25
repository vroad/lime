#ifndef HX_CFFIEXT_INCLUDED
#define HX_CFFIEXT_INCLUDED

#include <hx/CFFI.h>

extern void *LoadFunc(const char *inName);

#define DEFFUNC_EXT(name,ret,def_args,call_args) \
   typedef ret (*FUNC_##name)def_args; \
   FUNC_##name IMPL_##name = NULL; \
   bool LOADED_##name = false; \
   bool HAS_##name () \
   { \
     if (!LOADED_##name && IMPL_##name == NULL) \
     { \
       IMPL_##name = (FUNC_##name)LoadFunc(#name); \
       LOADED_##name = true; \
     } \
     return IMPL_##name != NULL; \
   } \
   ret EXT_##name def_args \
   { \
      if (!HAS_##name()) \
      { \
        fprintf(stderr,"Could not find external function:" #name " \n"); \
        abort(); \
      } \
      return IMPL_##name call_args; \
   }

#define DEFFUNC_EXT_0(ret,name) DEFFUNC_EXT(name,ret, (), ())
#define DEFFUNC_EXT_1(ret,name,t1) DEFFUNC_EXT(name,ret, (t1 a1), (a1))
#define DEFFUNC_EXT_2(ret,name,t1,t2) DEFFUNC_EXT(name,ret, (t1 a1, t2 a2), (a1,a2))
#define DEFFUNC_EXT_3(ret,name,t1,t2,t3) DEFFUNC_EXT(name,ret, (t1 a1, t2 a2, t3 a3), (a1,a2,a3))
#define DEFFUNC_EXT_4(ret,name,t1,t2,t3,t4) DEFFUNC_EXT(name,ret, (t1 a1, t2 a2, t3 a3, t4 a4), (a1,a2,a3,a4))
#define DEFFUNC_EXT_5(ret,name,t1,t2,t3,t4,t5) DEFFUNC_EXT(name,ret, (t1 a1, t2 a2, t3 a3, t4 a4,t5 a5), (a1,a2,a3,a4,a5))

DEFFUNC_EXT_1(value,pin_buffer,buffer);
DEFFUNC_EXT_1(void,unpin_buffer,value);

#endif