#include "CommonTypes.h"
#include "services.h"

typedef void (*pServiceCallBack)(u8 PureData[],u32 DataLen);
typedef enum 
{
    eNotSupported,
    eSupported,
}eServiceSup;
typedef struct 
{
    u8 DefaultSessionSupport;
    u8 ProgramSessionSupport;
    u8 ExtendSessionSupport;
    u8 EcuSessionSupport;
    u8 ReserverSessionSupport;
}tSessionSupport;
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
typedef enum 
{
    ePhy=0x01,
    eFunc=0x02,
    ePhyFunc=0x03,
}eMaskReqType;
typedef struct 
{
    tServiceId Id;
    pServiceCallBack ServiceCallBack;
    eMaskReqType RequestType;//functional,physical
    tSessionSupport AppModeSession;
}tService;

static void UdsServiceSessionControl(u8 PureData[],u32 DataLen);
static void UdsServiceEcuReset(u8 PureData[],u32 DataLen);
static void UdsServiceClearDtcInfo(u8 PureData[],u32 DataLen);
static void UdsServiceReadDtcinfo(u8 PureData[],u32 DataLen);
static void UdsServiceReadDataByIdentifier(u8 PureData[],u32 DataLen);
static void UdsServiceSecurityAccess(u8 PureData[],u32 DataLen);
static void UdsServiceWriteDataByIdentifier(u8 PureData[],u32 DataLen);
static void UdsServiceIoControl(u8 PureData[],u32 DataLen);
static void UdsServiceRoutineControl(u8 PureData[],u32 DataLen);
static void UdsServiceRequestTransferDownload(u8 PureData[],u32 DataLen);
static void UdsServiceTransferData(u8 PureData[],u32 DataLen);
static void UdsServiceTransferDataExit(u8 PureData[],u32 DataLen);
static void UdsServiceTesterPresent(u8 PureData[],u32 DataLen);



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

static void UdsServiceSessionControl(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceEcuReset(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceClearDtcInfo(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceReadDtcinfo(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceReadDataByIdentifier(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceSecurityAccess(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceWriteDataByIdentifier(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceIoControl(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceRoutineControl(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceRequestTransferDownload(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceTransferData(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceTransferDataExit(u8 PureData[],u32 DataLen)
{
}
static void UdsServiceTesterPresent(u8 PureData[],u32 DataLen)
{
}
void UdsMsgRecv(const u8 data[],const u8 length)
{

}
void UdsMain(void)
{

}
void UdsInit(void)
{

}
void UdsDeInit(void)
{

}
void UdsTimer(void)//1ms task
{

}