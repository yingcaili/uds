#include "CommonTypes.h"
#include "securityAccess.h"
#define mSecurityAccessTaskPeriod (1)   //1ms
#define mSecurityAccessRetryMaxTimer (10000/mSecurityAccessTaskPeriod)//10s

static tSecurityLevel eSecurityCurrLevel;
static u8 u8SecuriyAccessFailCount;
static u32 u32SecurityAccessFailTimer;

static u8 SecurityAccessAlgorithm(const u8 ClientKey[],const u8 KeyLen,tSecurityLevel eReqSecurityLevel);


static void SecurityAccessStartTimer(void)
{
    u32SecurityAccessFailTimer=mSecurityAccessRetryMaxTimer;
}
static void SecurityAccessStopTimer(void)
{
    u32SecurityAccessFailTimer=0;
}

extern void SecurityAccessInit(void)
{

}
extern void SecurityAccessDeinit(void)
{

}
extern tSecurityLevel SecurityAccessGetLevel(void)
{
    return eSecurityCurrLevel;
}
//=====================================
//FunctionName:
//Input:
//      KeyLen
//Output:
//      ServerKey[]:
//
//Description:
//
//Author:
//=====================================
static u8 SecurityAccessAlgorithm(const u8 ClientKey[],const u8 KeyLen,tSecurityLevel eReqSecurityLevel)
{

}
//=====================================
//FunctionName:
//Input:
//
//Output:
//
//Description:
//
//Author:
//=====================================
extern void SecurityAccessRandomSeed(u8 Seed[],const u8 SeedLen,const tSecurityLevel eReqSecurityLevel)
{
    u32 u32RandomSeed;
    u32RandomSeed=mRandomSeedSource();
    for(u8 i=0;i<SeedLen;i++)
    {
        if(eReqSecurityLevel==eSecurityCurrLevel)
        {
            Seed[i]=0x00;
        }
        else
        {
            Seed[i]=(u8)(u32RandomSeed & 0xfff);
            u32RandomSeed>>=1;
        }
    }
}
//=====================================
//FunctionName:
//Input:
//
//Output:
//
//Description:
//
//Author:
//=====================================
extern u8 SecurityAccessIsKeyCorrect(const u8 ClientKey[],const u8 KeyLen,tSecurityLevel eReqSecurityLevel)
{
    u8 u8Ret=0;
    if(eSecurityLevelDefault<eReqSecurityLevel && eReqSecurityLevel<eSecurityLevelInvalid)
    {
        u8Ret = SecurityAccessAlgorithm(ClientKey,KeyLen,eReqSecurityLevel);
        if(u8Ret)
        {
            eSecurityCurrLevel=eReqSecurityLevel;
        }
        else 
        {
            u8SecuriyAccessFailCount++;
        }
    }
}
//=====================================
//FunctionName:
//Input:
//
//Output:
//
//Description:
//
//Author:
//=====================================
static u8 SecurityAccessIsFailTimeElapsed(void)
{
    return (u32SecurityAccessFailTimer==0);
}
//=====================================
//FunctionName:
//Input:
//
//Output:
//
//Description:
//
//Author:
//=====================================
void SecurityAccessTimerTask(void)
{
    if(u32SecurityAccessFailTimer)
    {
        u32SecurityAccessFailTimer--;
    }

}
