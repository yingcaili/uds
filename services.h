#ifndef SERVICES_H
#define mServiceDiagnosticSessionControl                   (0x10)
#define mServiceEcuReset                                   (0x11)
#define mServiceSecurityAccess                             (0x27)
#define mServiceTesterPresent                              (0x3E)
#define mServiceControlDTCSetting                          (0x85)
#define mServiceReadDataByIdentifier                       (0x22)
#define mServiceReadMemoryByAddress                        (0x23)
#define mServiceWriteDataByIdentifier                      (0x2E)
#define mServiceWriteMemoryByAddress                       (0x3D)
#define mServiceClearDiagnosticInformation                 (0x14)
#define mServiceReadDTCInformation                         (0x19)
#define mServiceInputOutputControlByIdentifier             (0x2F)
#define mServiceRoutineControl                             (0x31)
#define	mServiceRequestDownLoad                            (0x34)
#define	mServiceRequestUpLoad                              (0x35)
#define	mServiceTransferData                               (0x36)
#define	mServiceRequestTransferExit                        (0x37)

#define mNRC_ServiceIsCorrect                             (0x00)
#define mNRC_ServiceNotSupported                          (0x11)
#define mNRC_SubFunctionNotSupported                      (0x12)
#define mNRC_IncorrectMessageLengthOrInvalidFormat        (0x13)
#define mNRC_ResponseTooLong                              (0x14)
#define mNRC_BusyRepeatRequest                            (0x21)
#define mNRC_ConditionsNotCorrect                         (0x22)
#define mNRC_RequestSequenceError                         (0x24)
#define mNRC_NoResponseFromSubnetComponent                (0x25)
#define mNRC_FailurePreventsExecutionOfRequestedAction    (0x26)
#define mNRC_RequestOutOfRange                            (0x31)
#define mNRC_SecurityAccessDenied                         (0x33)
#define mNRC_InvalidKey                                   (0x35)
#define mNRC_ExceedNumberOfAttempts                       (0x36)
#define mNRC_RequiredTimeDelayNotExpired                  (0x37)
#define mNRC_UploadDownloadNotAccepted                    (0x70)
#define mNRC_TransferDataSuspended                        (0x71)
#define mNRC_GeneralProgrammingFailure                    (0x72)
#define mNRC_WrongBlockSequenceCounter                    (0x73)
#define mNRC_ResponsePending                              (0x78)
#define mNRC_SubFunctionNotSupportedInActiveSession       (0x7E)
#define mNRC_ServiceNotSupportedInActiveSession           (0x7F)
#define mNRC_VoltageTooHigh                               (0x92)
#define mNRC_VoltageTooLow                                (0x93)



extern void UdsMsgRecv(const u8 data[],const u8 length);
extern void UdsMain(void);
extern void UdsInit(void);
extern void UdsDeInit(void);
extern void UdsTimer(void);//1ms task

#define UdsMsgSend(data,length)  

#endif