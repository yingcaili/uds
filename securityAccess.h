#ifndef SECURITYACCESS_H

#define mRandomSeedSource()  0xffffffff
typedef enum 
{
    eSecurityLevelDefault=0,
    eSecurityLevel1=0x01,
    eSecurityLevel2,
    eSecurityLevel3,
    eSecurityLevel4,
    eSecurityLevel5,
    eSecurityLevel6,
    eSecurityLevel7,
    eSecurityLevel8,
    eSecurityLevel8,
    eSecurityLevel9,
    eSecurityLevelInvalid=0xff,
}tSecurityLevel;
extern tSecurityLevel SecurityAccessGetLevel(void);
extern void SecurityAccessRandomSeed(u8 Seed[],const u8 SeedLen,const tSecurityLevel  eReqSecurityLevel);
extern u8 SecurityAccessIsKeyCorrect(const u8 ClientKey[],const u8 KeyLen,tSecurityLevel eReqSecurityLevel);
extern void SecurityAccessInit(void);
extern void SecurityAccessDeinit(void);
#endif