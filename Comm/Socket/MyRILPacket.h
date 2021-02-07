#ifndef MY_RIL_PACKET_DEF_H__
#define MY_RIL_PACKET_DEF_H__

/*****************************************************
socket propery define
*****************************************************/

#define RIL_SRV_ADDRESS          "127.0.0.1"
//#define RIL_SRV_PORT             39829
#define RIL_USIM_OTA_SRV_PORT     6172
#define RIL_SRV_MAX_CLIENT_COUNT 5

/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*                                                                                                                 */ 
/* RIL Service Message Definition                                                                                  */ 
/*                                                                                                                 */ 
/*******************************************************************************************************************/
/*******************************************************************************************************************/
#define RIL_MSG_TYPE_MASK  0xF000

/*-----------------------------------------------------------------------------------------------------------------*/
/* MSG Request (Client=>Server=>RIL)                                                                               */
/*-----------------------------------------------------------------------------------------------------------------*/
#define RIL_SRV_REQ_MSG_MASK              0x1000 

#define RIL_SRV_REQ_IS_RIL_READY          0x1001  /* check if RIL can send and receive packet with gct_rilsrv */
#define RIL_SRV_REQ_USIM_RIL_OTA_STATUS   0x1002 
#define RIL_SRV_REQ_RIL_RESTART           0x1003  
#define RIL_SRV_REQ_OTA_USIM_REGI         0x1004  /* This is valid only when NEED_USIM_REGI is ON */
#define RIL_SRV_REQ_UPDATE_USIM_RIL_OTA_STATUS   0x1005 

#define RIL_SRV_REQ_USIM_IMSI                        0x1011 
#define RIL_SRV_REQ_USIM_MSISDN                   0x1012 
#define RIL_SRV_REQ_USIM_GET_WEBCM_STATUS  0x1013 
#define RIL_SRV_REQ_USIM_IS_LOCK                   0x1014 
#define RIL_SRV_REQ_USIM_SET_LOCK                 0x1015 
#define RIL_SRV_REQ_USIM_GET_REMAIN_COUNT  0x1016 
#define RIL_SRV_REQ_USIM_PIN_CHANGE             0x1017
#define RIL_SRV_REQ_SEND_COMMAND              0x1018


#define RIL_SRV_USIMOTA_REQ_DISPLAY_SCREEN      0x1501 
     #define  USIMOTA_SCREEN_ID_1      0x100            // "번호등록후 사용가능합니다. 번호등록버튼을 눌러주시기 바랍니다"
     #define  USIMOTA_SCREEN_ID_2      0x200            // "신호세기가 미약하여 서비스가 불가능합니다."
     #define  USIMOTA_SCREEN_ID_3      0x300            // "번호를 등록중입니다."
     #define  USIMOTA_SCREEN_ID_4      0x400            // "카드에 해당번호를 등록하였습니다. 리셋이 필요합니다."
     #define  USIMOTA_SCREEN_ID_5      0x500            // "번호등록이 실패하였습니다. 재시도하겠습니까?"
     #define  USIMOTA_SCREEN_ID_6      0x600            // "카드에 정보 등록을 실패하였습니다."
     #define  USIMOTA_SCREEN_ID_7      0x700            // "망접속에 실패하였습니다 . 리셋이 필요합니다."

     #define  USIMOTA_BUTTON_ID_1_EMERGENCY           0x110       // 0x110  “비상”      화면0x100 에 표출
     #define  USIMOTA_BUTTON_ID_1_NUMBER_REGISTER  0x111       // 0x111  “번호등록”   화면0x100 에 표출 
     #define  USIMOTA_BUTTON_ID_4_OK                    0x410       // 0x410  “확인”  화면 0x400 에 표출 
     #define  USIMOTA_BUTTON_ID_5_YES_OK              0x510       // 0x510  “예+확인” 을 의미함,  화면 0x500 에 표출 
     #define  USIMOTA_BUTTON_ID_5_NO_OK              0x511       // 0x511  “아니오+확인”을 의미함,  화면 0x500 에 표출 
     #define  USIMOTA_BUTTON_ID_5_CANCEL             0x512       // 0x512  “취소”을 의미함,  화면 0x500 에 표출 
     #define  USIMOTA_BUTTON_ID_6_OK                    0x610      //0x610  “확인”  화면 0x600 에 표출 
     #define  USIMOTA_BUTTON_ID_7_OK                    0x710      //0x710  “확인”  화면 0x700 에 표출 

#define RIL_SRV_USIMOTA_REQ_JAVA_APP_EXIT         0x1502

/*-----------------------------------------------------------------------------------------------------------------*/
/* MSG Response (RIL=>Server=>Client)                                                                              */
/*-----------------------------------------------------------------------------------------------------------------*/
#define RIL_SRV_RESP_RESULT_SUCCESS    0
#define RIL_SRV_RESP_RESULT_ERROR     -1
#define RIL_SRV_RESP_RESULT_RIL_NOT_READY -2

#define RIL_SRV_RESP_MSG_MASK             0x2000 

#define RIL_SRV_RESP_IS_RIL_READY         0x2001 
      /*   
           struct ril_srv_packet_payload_resp * p_payload_resp = (struct ril_srv_packet_payload_resp *)RIL_SRV_PACKET_GET_PAYLOAD_PTR(pack_buf);
           int result = p_payload_resp->int_param[0]; 
           if(result == 1)  printf("RIL is Ready");
           else             printf("RIL is not Ready");
      */
      
#define RIL_SRV_RESP_USIM_RIL_OTA_STATUS  0x2002
      /*  struct ril_srv_packet_payload_resp * p_payload_resp = (struct ril_srv_packet_payload_resp *)RIL_SRV_PACKET_GET_PAYLOAD_PTR(pack_buf);   */
      /* unsigned int result = p_payload_resp->res;  0:SUCCESS  -1:ERROR  -2:RIL_NOT_READY    */

      /* unsigned int usim_status = p_payload_resp->int_param[0]; */
      #define USIM_OTA_STATUS_NORMAL                         0x000  /* Invalid USIM */
      #define USIM_OTA_STATUS_NEED_OTA_REGISTER              0x001  /* This USIM is needed to register via OTA */

      /* unsigned int ril_ota_status = p_payload_resp->int_param[1]; */
      #define RIL_OTA_STATUS_INIT                            0x100  /* ril is in init */
      #define RIL_OTA_STATUS_WORKING                         0x101  /* ril is working     */
      #define RIL_OTA_STATUS_WAIT_APP_REQ_RIL_RESTART        0x102  /* ril is waiting, App(clinet) must send 'RIL_SRV_REQ_RIL_START' */
      #define RIL_OTA_STATUS_WAIT_APP_REQ_AFTER_ATTACHED     0x103  /* After Attached, RIL waits for reciving CMD from APP  ex)RIL_SRV_RESP_OTA_USIM_REGI */

#define RIL_SRV_RESP_RIL_RESTART          0x2003  /* This is valid only when NEED_USIM_REGI is ON */
#define RIL_SRV_RESP_OTA_USIM_REGI        0x2004  /* This is valid only when NEED_USIM_REGI is ON */
#define RIL_SRV_RESP_UPDATE_USIM_RIL_OTA_STATUS   0x2005 

#define RIL_SRV_RESP_USIM_IMSI                        0x2011
#define RIL_SRV_RESP_USIM_MSISDN                   0x2012
#define RIL_SRV_RESP_USIM_GET_WEBCM_STATUS  0x2013 
#define RIL_SRV_RESP_USIM_IS_LOCK                   0x2014 
#define RIL_SRV_RESP_USIM_SET_LOCK                 0x2015 
#define RIL_SRV_RESP_USIM_GET_REMAIN_COUNT  0x2016 
#define RIL_SRV_RESP_USIM_PIN_CHANGE             0x2017
#define RIL_SRV_RESP_SEND_COMMAND              0x2018


#define RIL_SRV_USIMOTA_RESP_DISPLAY_SCREEN      0x2501 
#define RIL_SRV_USIMOTA_RESP_JAVA_APP_EXIT         0x2502


/*-----------------------------------------------------------------------------------------------------------------*/
/* MSG Notify (Server=>Client)                                                                                     */
/*-----------------------------------------------------------------------------------------------------------------*/
#define RIL_SRV_NOTI_MSG_MASK            0x3000 
#define RIL_SRV_NOTI_AUTOCM_STATUS       0x3001 
#define RIL_SRV_NOTI_VSC_RESULT          0x3002 
        #define RIL_VSC_RESULT_SUCCESS           0       /* GCT OTA-TEST GUIDE_KT_v.1.2.docx */
        #define RIL_VSC_RESULT_REFRESH_CMD_FAIL  6 
        #define RIL_VSC_RESULT_USER_REGI_TIMEOUT 7
        #define RIL_VSC_RESULT_SUCCESS_WITHOUT_UEREBOT 8

#define RIL_SRV_USIMOTA_NOTI_CLICK_BUTTON         0x3501

/*-----------------------------------------------------------------------------------------------------------------*/
/* MSG Request (Socket_Client=>Server=>CM)                                                                                */
/*-----------------------------------------------------------------------------------------------------------------*/
#define RIL_SRV_CM_REQ_MSG_MASK                  0x4000 
#define RIL_SRV_CM_REQ_USERDATA                   0x4001 
#define RIL_SRV_CM_REQ_RIL_POWER_CONTROL    0x4002 
#define RIL_SRV_CM_REQ_USIM_POWER_CONTROL 0x4003 
#define RIL_SRV_CM_REQ_DM_LOG_EXT_RSP          0x4004 
#define RIL_SRV_CM_REQ_RUN_COMMAND           0x4005 

/*-----------------------------------------------------------------------------------------------------------------*/
/* MSG Response (CM=>Server=>Socket_Client)                                                                               */
/*-----------------------------------------------------------------------------------------------------------------*/
#define RIL_SRV_CM_RESP_MSG_MASK                  0x5000
#define RIL_SRV_CM_RESP_USERDATA                   0x5001 
#define RIL_SRV_CM_RESP_RIL_POWER_CONTROL    0x5002
#define RIL_SRV_CM_RESP_USIM_POWER_CONTROL 0x5003
#define RIL_SRV_CM_RESP_DM_LOG_EXT_RSP          0x5004 
#define RIL_SRV_CM_RESP_RUN_COMMAND           0x5005 
        #define RIL_RUN_COMMAND_RESULT_SUCCESS           0 
        #define RIL_RUN_COMMAND_RESULT_ERROR_CMD      -1  /* fail to run cmd */
        

/*-----------------------------------------------------------------------------------------------------------------*/
/* MSG Request (User=>Server=>CM)                                                                                */
/*-----------------------------------------------------------------------------------------------------------------*/
#define RIL_SRV_USER_REQ_MSG_MASK                  0x6000 
#define RIL_SRV_USER_REQ_RUN_COMMAND           0x6001 

/*-----------------------------------------------------------------------------------------------------------------*/
/* MSG Response (CM=>Server=>User)                                                                               */
/*-----------------------------------------------------------------------------------------------------------------*/
#define RIL_SRV_USER_RESP_MSG_MASK                  0x7000
#define RIL_SRV_USER_RESP_RUN_COMMAND           0x7001 
        //#define RIL_RUN_COMMAND_RESULT_SUCCESS           0 
        //#define RIL_RUN_COMMAND_RESULT_ERROR_CMD      -1  /* fail to run cmd */

/*-----------------------------------------------------------------------------------------------------------------*/
/* Check MSG Type                                                                                                  */
/*-----------------------------------------------------------------------------------------------------------------*/
#define RIL_SRV_IS_REQ_MSG(msg) ((msg&RIL_MSG_TYPE_MASK)==RIL_SRV_REQ_MSG_MASK)
#define RIL_SRV_IS_RESP_MSG(msg) ((msg&RIL_MSG_TYPE_MASK)==RIL_SRV_RESP_MSG_MASK)
#define RIL_SRV_IS_NOTI_MSG(msg) ((msg&RIL_MSG_TYPE_MASK)==RIL_SRV_NOTI_MSG_MASK)
#define RIL_SRV_IS_CM_REQ_MSG(msg) ((msg&RIL_MSG_TYPE_MASK)==RIL_SRV_CM_REQ_MSG_MASK)
#define RIL_SRV_IS_CM_RESP_MSG(msg) ((msg&RIL_MSG_TYPE_MASK)==RIL_SRV_CM_RESP_MSG_MASK)
#define RIL_SRV_IS_USER_REQ_MSG(msg) ((msg&RIL_MSG_TYPE_MASK)==RIL_SRV_USER_REQ_MSG_MASK)
#define RIL_SRV_IS_USER_RESP_MSG(msg) ((msg&RIL_MSG_TYPE_MASK)==RIL_SRV_USER_RESP_MSG_MASK)


/*****************************************************
packet header sturctur
*****************************************************/
#define RIL_SRV_PACK_KEY 0xAAAA0000
struct ril_srv_packet_header {
    unsigned int key;
    unsigned int token;
    unsigned int msg;
    unsigned int payload_size;
};

/*****************************************************
packet payload request
*****************************************************/
struct ril_srv_packet_payload_req {
    unsigned int int_param[16];
    char data1[256];
};

#define RIL_SRV_PACKET_PAYLOAD_RUN_CMD_MAX_SIZE 32
#define RIL_SRV_PACKET_PAYLOAD_RUN_ARG_MAX_SIZE  128
struct ril_srv_packet_payload_req_run_cmd {
    char cmd[RIL_SRV_PACKET_PAYLOAD_RUN_CMD_MAX_SIZE +4];   /* cmd max 32 byte */
    char arg[RIL_SRV_PACKET_PAYLOAD_RUN_ARG_MAX_SIZE +4];  /*argument max 128 byte*/
};

/*****************************************************
packet payload response
*****************************************************/
struct ril_srv_packet_payload_resp {
    int res; /* 0 : Success  -1 : Error */
    unsigned int int_param[15];
    char data1[256];
};

/*****************************************************
packet payload notify
*****************************************************/
struct ril_srv_packet_payload_notify {
    unsigned int status;
    unsigned int int_param[15];
    char data1[256];
};

/*****************************************************
packet buffer sturctur
*****************************************************/
#define RIL_SRV_PACKET_BUF_SIZE  512

#define RIL_SRV_PACKET_HEADER_BYTE_IDX      (0)
#define RIL_SRV_PACKET_HEADER_BYTE_SIZE     (16)

#define RIL_SRV_PACKET_PAYLOAD_BYTE_IDX     (RIL_SRV_PACKET_HEADER_BYTE_SIZE)
#define RIL_SRV_PACKET_PAYLOAD_BYTE_SIZE    (RIL_SRV_PACKET_BUF_SIZE-RIL_SRV_PACKET_HEADER_BYTE_SIZE-RIL_SRV_PACKET_CHECKSUM_BYTE_SIZE) 

#define RIL_SRV_PACKET_CHECKSUM_BYTE_IDX    (RIL_SRV_PACKET_BUF_SIZE-RIL_SRV_PACKET_CHECKSUM_BYTE_SIZE)
#define RIL_SRV_PACKET_CHECKSUM_INT_IDX     (RIL_SRV_PACKET_CHECKSUM_BYTE_IDX>>2)
#define RIL_SRV_PACKET_CHECKSUM_BYTE_SIZE   (4)


/*****************************************************
packet function 
*****************************************************/

static inline unsigned int  RIL_SRV_PACKET_CAL_CHECKSUM(const unsigned char* pack_buf) 
{
    int  i;
    unsigned int check_sum=0;
    unsigned int *intbuf=(unsigned int*)pack_buf;
    for(i = 0; i < RIL_SRV_PACKET_CHECKSUM_INT_IDX; i++) check_sum += intbuf[i];
    return check_sum;
}

static inline unsigned int RIL_SRV_PACKET_READ_CHECKSUM(const unsigned char* pack_buf)  
{
    unsigned int check_sum=0;
    unsigned char* char_buf=(unsigned char*)pack_buf;
    memcpy((void*)&check_sum, (void*)&char_buf[RIL_SRV_PACKET_CHECKSUM_BYTE_IDX], 4);
    return check_sum;
}

#define RIL_SRV_PACKET_WRITE_CHECKSUM(pack_buf, check_sum)  \
({\
    int _ret=0;\
    unsigned char* char_buf=(unsigned char*)pack_buf;\
    memcpy((void*)&char_buf[RIL_SRV_PACKET_CHECKSUM_BYTE_IDX], (void*)&check_sum, 4);\
    _ret;\
})

#define RIL_SRV_PACKET_UPDATE_CHECKSUM(pack_buf)  \
({\
    int _ret=0;\
    unsigned int check_sum = RIL_SRV_PACKET_CAL_CHECKSUM(pack_buf);\
    RIL_SRV_PACKET_WRITE_CHECKSUM(pack_buf, check_sum);\
    _ret;\
})

static bool RIL_SRV_PACKET_IS_VALID(const unsigned char* pack_buf) 
{
    bool is_valid=true;
    unsigned int check_sum1, check_sum2;
    struct ril_srv_packet_header* p_header = (struct ril_srv_packet_header*)pack_buf;
    check_sum1 = RIL_SRV_PACKET_CAL_CHECKSUM(pack_buf);
    check_sum2 = RIL_SRV_PACKET_READ_CHECKSUM(pack_buf);
    if(check_sum1 != check_sum2) is_valid=false;
    if(p_header->key != RIL_SRV_PACK_KEY) is_valid=false;
    return is_valid;
}

static inline unsigned char* RIL_SRV_PACKET_GET_HEADER_PTR(unsigned char* pack_buf)  
{
    unsigned char* p_payload=NULL;
    unsigned char* byte_buf=(unsigned char*)pack_buf;
    p_payload = (unsigned char*)&byte_buf[RIL_SRV_PACKET_HEADER_BYTE_IDX];
    return p_payload;
}

static inline unsigned char* RIL_SRV_PACKET_GET_PAYLOAD_PTR(unsigned char*  pack_buf)
{
    unsigned char* p_payload=NULL;
    unsigned char* byte_buf=(unsigned char*)pack_buf;
    p_payload = (unsigned char*)&byte_buf[RIL_SRV_PACKET_PAYLOAD_BYTE_IDX];
    return p_payload;
}


static inline int  RIL_SRV_PACKET_MAKE(unsigned char *pack_buf, unsigned int token, unsigned int msg, unsigned int payload_size, struct ril_srv_packet_payload_req* p_payload)
{
    //int i;
    unsigned int check_sum=0;
    struct ril_srv_packet_header* p_header = (struct ril_srv_packet_header*)pack_buf;
    unsigned char* char_buf=(unsigned char*)pack_buf;
    unsigned char* payload_buf=RIL_SRV_PACKET_GET_PAYLOAD_PTR(pack_buf);
    memset(char_buf, 0xCC, RIL_SRV_PACKET_BUF_SIZE);
    p_header->key = RIL_SRV_PACK_KEY;
    p_header->token = token;
    p_header->msg = msg;
    p_header->payload_size = payload_size;
    if(payload_size>0) memcpy(payload_buf, p_payload, payload_size);
    check_sum = RIL_SRV_PACKET_CAL_CHECKSUM(pack_buf);
    memcpy((void*)&char_buf[RIL_SRV_PACKET_CHECKSUM_BYTE_IDX], (void*)&check_sum, 4);
    return check_sum;
}


#endif
