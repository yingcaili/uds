#include "CommonTypes.h"
extern void LibDebugPrintf(const char *Msg)
{
    
}

u32 DataTransformBit32(const u8 data[])
{
    u32 ret=0;
    ret+=(data[0]<<24);
    ret+=(data[1]<<16);
    ret+=(data[2]<<8);
    ret+=(data[3]<<0);
    return ret;
}