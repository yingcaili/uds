#ifndef COMMONTYPES_H
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
//protocal control information


extern void LibDebugPrintf(const char *Msg);
extern u32 DataTransformBit32(const u8 data[]);
#endif