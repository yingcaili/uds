#include "CommonTypes.h"
#include "Flash.h"
typedef struct FlashDataInfo
{
    u32 u32DataLen;
    u32 u32StartAddress;
}tFlashDataInfo;
tFlashDataInfo stFlashDataInfo;


void FlashSaveData(const u32 u32StartAddress,const u32 u32DataLen)
{
    stFlashDataInfo.u32StartAddress=u32StartAddress;
    stFlashDataInfo.u32DataLen=u32DataLen;
}