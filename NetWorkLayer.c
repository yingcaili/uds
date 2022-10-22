#include "NetWorkLayer-h"

typedef enum 
{
    eNetWorkIdle,
    eNetWorkRecving,
    eNetWorkWaitingFlowControl,
    eNetWorkWaitingConsecutiveFrame,

}tNetWorkRecvSt;
typedef enum 
{
    eSuccess,
    eFailure,
    eError,
}tNetWorkStCode;
typedef enum 
{
	eFlowControlContinueToSend = 0, /* ContinueToSend */
	eFlowControlWait,      /* Wait */
	eFlowControlOverFlow,   /* OverFlow */
	eFlowControlReserved
}tFlowControlType;


#define mPciFirstFrame (0x00)
#define mPciSingleFrame (0x10)
#define mPciConsecutiveFrame (0x20)
#define mPciFlowControlFrame (0x30)
#define mMsgRecvMax (0xFFF)
static tNetWorkStCode NetWorkMsgFirstFrame(const u8 data[],const u8 length);
static tNetWorkStCode NetWorkMsgSingleFrame(const u8 data[],const u8 length);
static tNetWorkStCode NetWorkMsgConsecutiveFrame(const u8 data[],const u8 length);
static tNetWorkStCode NetWorkMsgFlowControlFrame(const u8 data[],const u8 length);
static tNetWorkStCode NetWorkMsgSend(const u8 data[],const u8 length);
static void NetWorkMsgBuf(const u8 u8FrameType,const u8 realdata[],const u16 reallength);

static tNetWorkRecvSt eRecvState=eNetWorkIdle;
static u8 u8UdsNetworkMsg[mMsgRecvMax];
/*Index for testing CAN msg */
static u16 u16NetWorkMsgIndexIn=0;
static u16 u16NetWorkMsgIndexOut=0;
static u8 u8FrameBlockSizeCounter=0;/*less than block size*/
static u8 u8FrameConsecutiveSn=0; /*0~0xf*/
static u16 u16FrameConsecutiveLength=0;
static u16 u16FrameConsecutiveLengthCounter=0;
typedef enum
{
    ePciTypeSingle,
    ePciTypeFirstFrame,
    ePciTypeConsecutiveFrame,
    ePciTypeFlowControlFrame,
    ePciTypeError,
}tNetWorkMsgPciType;
typedef struct 
{
    u16 length;
    u8 *data;
    tNetWorkMsgPciType PciType;
}tNetWorkMsg;
tNetWorkMsg stNetWorkMsgList={0,&u8UdsNetworkMsg[0],ePciTypeError};
extern void NetWorkInit(void)
{
    u16NetWorkMsgIndexIn=0;
    u16NetWorkMsgIndexOut=0;
    eRecvState=eNetWorkIdle;
}
extern void NetWorkDeInit(void)
{
    u16NetWorkMsgIndexIn=0;
    u16NetWorkMsgIndexOut=0;
    eRecvState=eNetWorkIdle;
}
static void NetWorkReset(void)
{
    u16NetWorkMsgIndexIn=0;
    u16NetWorkMsgIndexOut=0;
    eRecvState=eNetWorkIdle;

}
static void NetWorkMsgBuf(const u8 u8FrameType,const u8 realdata[],const u16 reallength)
{
    stNetWorkMsgList.PciType=u8FrameType;
    for(u8 i=0;i<reallength;i++)
    {
    stNetWorkMsgList.data[i]=realdata[i];
    }
    stNetWorkMsgList.length=reallength;
    u16NetWorkMsgIndexIn++;
    if(u16NetWorkMsgIndexIn>=mMsgRecvMax)
    {
        u16NetWorkMsgIndexIn=0;
    }
}
extern void NetWorkMsgRecv(const u8 data[],const u8 length)
{
    u8 i=0;
    u8 u8FrameType = 0;

    u8FrameType = data[0];

    switch (u8FrameType)
    {
    case mPciFirstFrame:
        if(eRecvState==eNetWorkIdle)
        {  
            if(eSuccess==NetWorkMsgFirstFrame(data,length))
            {
                NetWorkReset();
                eRecvState=eNetWorkWaitingConsecutiveFrame;
            }
        }
        else 
        {
            /*nothing*/
        }
        break;
    case mPciSingleFrame:
        if(eRecvState==eNetWorkIdle)
        {  
            if(eSuccess==NetWorkMsgSingleFrame(data,length))
            {
                NetWorkReset();
                eRecvState=eNetWorkIdle;
            }

        }
        else 
        {
            /*nothing*/
        }
        break;
    case mPciConsecutiveFrame:
        if(eNetWorkWaitingConsecutiveFrame==eRecvState)
        {
            if(eSuccess==NetWorkMsgConsecutiveFrame(data,length))
            {
                NetWorkReset();
                eRecvState=eNetWorkIdle;
            }
        }

        break;
    case mPciFlowControlFrame:
        NetWorkMsgFlowControlFrame(data,length);
        break;
    default:
        u8FrameType=0xff;
        break;
    }

}
extern void NetWorkMsgAnalyse(void)
{

}
extern void NetWorkMsgHandle(void)
{
    while(u16NetWorkMsgIndexIn!=u16NetWorkMsgIndexOut)//new msg arrived
    {

    }
}
static tNetWorkStCode NetWorkMsgIndication(const u8 data[],const u8 length)
{

}
static tNetWorkStCode NetWorkSendFlowControl(tFlowControlType eType)
{
    u8 data[8];
    u8 datalength;
    switch (eType)
    {
    case eFlowControlContinueToSend:
        NetWorkMsgSend(data,datalength);
        break;
    case eFlowControlWait:
    break;
    case eFlowControlOverFlow:
    break;
    case eFlowControlReserved:break;
    default:
        break;
    }
}
static tNetWorkStCode NetWorkMsgFirstFrame(const u8 data[],const u8 length)
{
    u16 u16DataLen;
    tNetWorkStCode ret=eError;
    u16DataLen=((data[0]&0x0f)<<8)+data[1];

    if(u16DataLen<8) /*consecutive frame length should > 8*/
    {
        ret=eError;
    }
    else if (u16DataLen >= mMsgRecvMax)
    {
        NetWorkSendFlowControl(eFlowControlOverFlow);
        ret=eError;
    }
    else
    {
        NetWorkMsgBuf(ePciTypeFirstFrame,data,u16DataLen);
        u16FrameConsecutiveLength=u16DataLen;
        ret=eSuccess;
    }
    return ret;
}
static tNetWorkStCode NetWorkMsgSingleFrame(const u8 data[],const u8 length)
{
    u8 u8DataLen;
    tNetWorkStCode ret=eError;
    u8DataLen=(data[0]&0x0f);

    if(u8DataLen>7 ||u8DataLen<=0)
    {
        ret=eError;
    }
    else 
    {
        NetWorkMsgBuf(mPciFirstFrame,&data[1],u8DataLen);
    }

    

}
static tNetWorkStCode NetWorkMsgConsecutiveFrame(const u8 data[],const u8 length)
{
    u8 u8Sn=0;
    u8 u8ConsectiveDataLen=0;
    tNetWorkStCode ret=eError;
    u8Sn=(data[0]&0x0f);

    u8FrameConsecutiveSn++;
    if(u8FrameConsecutiveSn>0x0f)
    {
        u8FrameConsecutiveSn=0;
    }
    if(u8FrameConsecutiveSn!=u8Sn)
    {
        ret=eError;
    }
    else  
    {
        u8ConsectiveDataLen=(length-2);
        NetWorkMsgBuf(ePciTypeConsecutiveFrame,data,u8ConsectiveDataLen);
        u16FrameConsecutiveLengthCounter+=u8ConsectiveDataLen;
        if(u16FrameConsecutiveLengthCounter<u16FrameConsecutiveLength)
        {
            if(mNetWorkBlockSize>0)
            {
                u8FrameBlockSizeCounter++;
                if(u8FrameBlockSizeCounter>=mNetWorkBlockSize)
                {
                    u8FrameBlockSizeCounter=0;
                    NetWorkSendFlowControl(eFlowControlContinueToSend);
                }
            }
        }
        else
        {
            ret=eSuccess;
        }

        
    }

}


typedef struct FlashDataInfo
{
    u32 u32DataLen;
    u32 u32StartAddress;
}tFlashDataInfo;
tFlashDataInfo gstFlashDataInfo;
u32 DataTransformBit32(const u8 data[])
{
    u32 ret=0;
    ret+=(data[0]<<24);
    ret+=(data[1]<<16);
    ret+=(data[2]<<8);
    ret+=(data[3]<<0);
    return ret;
}
static void FlashSaveData(const u32 u32StartAddress,const u32 u32DataLen)
{
    gstFlashDataInfo.u32StartAddress=u32StartAddress;
    gstFlashDataInfo.u32DataLen=u32DataLen;
   
}
static void NetWorkMsgRecvInfo(const u8 data[],const u8 length)
{
    FlashSaveData(DataTransformBit32(&data[0]),DataTransformBit32(&data[4]));
}
static void NetWorkMsgTransfer(const u8 data[],const u8 length)
{
    static u16 u16RecvLen=0;
    static u8 ArrValidData[0xfff];
    const u16 u16FlashWriteDataLen=0x400;

    for(u8 i=0;i<length;i++)
    {
        ArrValidData[u16RecvLen]=data[i];
        u16RecvLen++;
        if(u16RecvLen>=0xfff)
        {
            u16RecvLen=0;
        }
    }

    if(u16RecvLen==u16FlashWriteDataLen)
    {

    }
}

/*
1:receive data info: startaddress ,size
2:
*/


static tNetWorkStCode NetWorkMsgSend(const u8 data[],const u8 length)
{

}