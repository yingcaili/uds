

typedef enum 
{
    ePhy=0x01,
    eFunc=0x02,
    ePhyFunc=0x03,
}tUdsReqType;


#define mCanPhysicalRequestId 0xffffffff
#define mCanPhysicalResponseId 0xffffffff
#define mCanFunctionalReqId 0xffffffff

#define UDS_RUN_MODE_APP 1
#define UDS_RUN_MODE_BOOTLOADER 2

#define mNetWorkMsgSend(data,length) //can_send_interface(mCanPhysicalResponseId,data,length) 
#define UDS_RUN_MODE UDS_RUN_MODE_APP
#if (UDS_RUN_MODE==UDS_RUN_MODE_APP)
#define mNetWorkBlockSize (8)
#define mFrameStMin (0x19)
#define mNetWorkAsync (1)
#else 
#define mNetWorkBlockSize (0)
#define mFrameStMin (0)
#define mNetWorkAsync (0)
#endif
extern void NetWorkMsgRecv(const u8 data[],const u8 length);

