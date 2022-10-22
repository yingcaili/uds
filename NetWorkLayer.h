


#define UDS_RUN_MODE_APP 1
#define UDS_RUN_MODE_BOOTLOADER 2


#define UDS_RUN_MODE UDS_RUN_MODE_APP
#if (UDS_RUN_MODE==UDS_RUN_MODE_APP)
#define mNetWorkBlockSize (8)
#define mFrameStMin (0x19)
#else 
#define mNetWorkBlockSize (0)
#define mFrameStMin (0)
#endif
extern void NetWorkMsgRecv(const u8 data[],const u8 length);

