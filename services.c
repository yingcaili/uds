#include "CommonTypes.h"
#include "services.h"

typedef void (*pServiceCallBack)(const u8 PureData[],const u32 DataLen);
typedef enum 
{
    eNotSupported,
    eSupported,
}tServiceSup;
typedef struct 
{
    tServiceSup DefaultSessionSupport;
    tServiceSup ProgramSessionSupport;
    tServiceSup ExtendSessionSupport;
    tServiceSup EcuSessionSupport;
    tServiceSup ReserverSessionSupport;
}tSessionSupport;
typedef enum 
{
    eDefaultSession=0x01,
    eProgramSession=0x02,
    eExtendSession=0x03,
    eEcuSession=0x04,
    eInvalidSession=0xff,
}tSession;
typedef enum 
{
    eIDSessionControl=0x10,
    eIDEcuReset=0x11,
    eIDClearDtcInfo=0x14,
    eIDReadDtcinfo=0x19,
    eIDReadDataByIdentifier=0x22,
    eIDSecurityAccess=0x27,
    eIDWriteDataByIdentifier=0x2E,
    eIDIoControl=0x2F,
    eIDRoutineControl=0x31,
    eIDRequestTransferDownload=0x34,
    eIDTransferData=0x36,
    eIDTransferDataExit=0x37,
    eIDTesterPresent=0x3E, 
    eIDInvalid=0xff,   
}tServiceId;

typedef struct 
{
    tServiceId Id;
    pServiceCallBack ServiceCallBack;
    tUdsReqType RequestType;//functional,physical
    tSessionSupport AppModeSession;
}tService;

static void UdsServiceSessionControl(const u8 PureData[],const u32 DataLen);
static void UdsServiceEcuReset(const u8 PureData[],const u32 DataLen);
static void UdsServiceClearDtcInfo(const u8 PureData[],const u32 DataLen);
static void UdsServiceReadDtcinfo(const u8 PureData[],const u32 DataLen);
static void UdsServiceReadDataByIdentifier(const u8 PureData[],const u32 DataLen);
static void UdsServiceSecurityAccess(const u8 PureData[],const u32 DataLen);
static void UdsServiceWriteDataByIdentifier(const u8 PureData[],const u32 DataLen);
static void UdsServiceIoControl(const u8 PureData[],const u32 DataLen);
static void UdsServiceRoutineControl(const u8 PureData[],const u32 DataLen);
static void UdsServiceRequestTransferDownload(const u8 PureData[],const u32 DataLen);
static void UdsServiceTransferData(const u8 PureData[],const u32 DataLen);
static void UdsServiceTransferDataExit(const u8 PureData[],const u32 DataLen);
static void UdsServiceTesterPresent(const u8 PureData[],const u32 DataLen);

static u8 u8UdsCurrSession;

static tService stServiceList[]={
    {
        eIDSessionControl,
        UdsServiceSessionControl, 
        ePhyFunc, 
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDEcuReset, 
        UdsServiceEcuReset,
        ePhyFunc,   
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDClearDtcInfo, 
        UdsServiceClearDtcInfo,
        ePhyFunc,   
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDReadDtcinfo, 
        UdsServiceReadDtcinfo,
        ePhyFunc,  
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDReadDataByIdentifier, 
        UdsServiceReadDataByIdentifier, 
        ePhyFunc,  
        {eSupported,eSupported,eSupported,eSupported,eSupported}},
    {
        eIDSecurityAccess, 
        UdsServiceSecurityAccess,
        ePhyFunc,   
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDWriteDataByIdentifier,
        UdsServiceWriteDataByIdentifier ,
        ePhyFunc,   
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDIoControl, 
        UdsServiceIoControl,
        ePhyFunc,   
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDRoutineControl, 
        UdsServiceRoutineControl,
        ePhyFunc,   
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDRequestTransferDownload, 
        UdsServiceRequestTransferDownload,
        ePhyFunc,   
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDTransferData, 
        UdsServiceTransferData,
        ePhyFunc,   {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDTransferDataExit, 
        UdsServiceTransferDataExit,
        ePhyFunc,  
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },
    {
        eIDTesterPresent, 
        UdsServiceTesterPresent,
        ePhyFunc,   
        {eSupported,eSupported,eSupported,eSupported,eSupported}
    },

};

static void UdsServiceSessionControl(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceEcuReset(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceClearDtcInfo(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceReadDtcinfo(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceReadDataByIdentifier(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceSecurityAccess(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceWriteDataByIdentifier(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceIoControl(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceRoutineControl(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceRequestTransferDownload(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceTransferData(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceTransferDataExit(const u8 PureData[],const u32 DataLen)
{
}
static void UdsServiceTesterPresent(const u8 PureData[],const u32 DataLen)
{
}
static u8 UdsLocateServiceIndex(tServiceId Id)
{
    u8 u8NotFound=1;
    u8 index=0xff;
    for(u8 i=0;(i<sizeof(stServiceList)/sizeof(stServiceList[0]))&&(u8NotFound);i++)
    {
        if(stServiceList[i].Id==Id)
        {
            u8NotFound=0;
            index=i;
        }
    }
    return index;
}
static tServiceSup UdsIsSessionSupport(u8 ServiceListIndex)
{
    tServiceSup ret=eNotSupported;
    switch(u8UdsCurrSession)
    {
        case eDefaultSession:ret=stServiceList[ServiceListIndex].AppModeSession.DefaultSessionSupport;break;
        case eProgramSession:ret=stServiceList[ServiceListIndex].AppModeSession.ProgramSessionSupport;break;
        case eExtendSession:ret=stServiceList[ServiceListIndex].AppModeSession.ExtendSessionSupport;break;
        case eEcuSession:ret=stServiceList[ServiceListIndex].AppModeSession.EcuSessionSupport;break;
        default:break;
    }
    return ret;
}
static u8 UdsIsSubFunctionSupport(u8 ServiceListIndex)
{

}
typedef struct 
{
    tServiceId Id;
    u32 MinLen;
    u32 MaxLen;
}tServiceLen;
static tServiceLen stServiceListLen[]=
{
    {eIDSessionControl,2 ,2},
    {eIDEcuReset, 2,2},
    {eIDClearDtcInfo, 2,2},
    {eIDReadDtcinfo, 2,2},
    {eIDReadDataByIdentifier, 2,2},
    {eIDSecurityAccess, 2,2},
    {eIDWriteDataByIdentifier, 2,2},
    {eIDIoControl, 2,2},
    {eIDRoutineControl, 2,2},
    {eIDRequestTransferDownload, 2,2},
    {eIDTransferData, 2,2},
    {eIDTransferDataExit, 2,2},
    {eIDTesterPresent, 2,2}, 
};
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
static u8 UdsIsInvalidLengthOrFormat(u8 ServiceListIndex,const u32 length)
{
    u8 u8NotFound=1;
    u8 u8IsValid=0;
    for(u8 i=0;(i<sizeof(stServiceListLen)/sizeof(stServiceListLen[0]))&&(u8NotFound);i++)
    {
        if(stServiceList[ServiceListIndex].Id==stServiceListLen[i].Id)
        {
            u8NotFound=0;
            if(stServiceListLen[i].MinLen<=length 
            && stServiceListLen[i].MaxLen>=length )
            {
                u8IsValid=1;
            }
        }
    }
    return u8IsValid;
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
void UdsMsgRecv(const u8 data[],const u32 length)
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
void UdsMain(void)
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
void UdsInit(void)
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
void UdsDeInit(void)
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
void UdsTimer(void)//1ms task
{

}