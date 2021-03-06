#ifndef _TDMB_H_
#define _TDMB_H_
/*
 * tdmb.h
 *
 * - klaatu
 *
 *
*/
#include <linux/types.h>

extern int IsTDMBPowerOn(void);
extern int TDMB_PowerOn(void);
extern void TDMB_PowerOff(void);
extern void TDMB_drv_gct_set_freq_channel (unsigned long  dEnsembleFreq_subCh);

typedef struct{ 
	int b_isTDMB_Enable;
}tdmb_type;

// need to check --------------------

#define DMB_TS_COUNT	40
#define DMB_TS_SIZE			188

#define GDM_TS_BUF_MAX		(DMB_TS_SIZE*DMB_TS_COUNT)

#define GDM_MSC_BUF_MAX		(188*40)
#define GDM_DM_BUF_MAX		(512)
#define GDM_FIC_BUF_MAX		(384)
//---------------------------------------


#define TS_BUFFER_SIZE 		GDM_TS_BUF_MAX

#define TDMB_RING_BUFFER_SIZE (188 * 100 + 4 + 4) //(188*30 + 4 + 4) 
#define TDMB_RING_BUFFER_MAPPING_SIZE (((TDMB_RING_BUFFER_SIZE - 1) / PAGE_SIZE + 1 ) * PAGE_SIZE)

/* commands */
typedef enum{ 
    IOCTL_TDMB_GET_DATA_BUFFSIZE     = 0xffff0000,
    IOCTL_TDMB_GET_CMD_BUFFSIZE     ,
    IOCTL_TDMB_POWER_ON             ,
    IOCTL_TDMB_POWER_OFF            ,
    IOCTL_TDMB_SCAN_FREQ_ASYNC      ,
    IOCTL_TDMB_SCAN_FREQ_SYNC       ,
    IOCTL_TDMB_SCANSTOP             ,
    IOCTL_TDMB_ASSIGN_CH            ,
    IOCTL_TDMB_GET_DM               ,
    IOCTL_TDMB_ASSIGN_CH_TEST		,
    IOCTL_TDMB_MAX
};

#define TDMB_SUCCESS			 0
#define TDMB_ERROR				-1

typedef struct{ 
    unsigned int    rssi;
    unsigned int    BER;
    unsigned int    PER;
    unsigned int    antenna;
}tdmb_dm;

// FIG

#define MAX_ENSEMBLE_NUM             21
#define SUB_CH_NUM_MAX               64

#define ENSEMBLE_LABEL_SIZE_MAX      16
#define SERVICE_LABEL_SIZE_MAX       16
#define USER_APPL_DATA_SIZE_MAX      24
#define USER_APPL_NUM_MAX            12

typedef enum TMID_type{
    TMID_MSC_STREAM_AUDIO       = 0x00,
    TMID_MSC_STREAM_DATA        = 0x01,
    TMID_FIDC                   = 0x02,
    TMID_MSC_PACKET_DATA        = 0x03
}TMID_TYPE;

typedef enum{ 
    DSCTy_TDMB                  = 0x18,
    DSCTy_UNSPECIFIED           = 0x00 //Used for All-Zero Test
}DSCTy_TYPE;

typedef struct tag_SubChInfoType
{
// Sub Channel Information
  unsigned char SubChID; // 6 bits
  unsigned short StartAddress; // 10 bits
  unsigned short FormSizeProtectionlevel; // 1 bit, 7/15 bits (Form,Size,protection level)
// FIG 0/2  
  unsigned char TMId; // 2 bits
  unsigned char Type; // 6 bits
//useless unsigned char PrimarySecondary;
  unsigned long ServiceID; // 16/32 bits
  unsigned char ServiceLabel[SERVICE_LABEL_SIZE_MAX]; //16*8 bits
// FIG 0/3
//useless unsigned short ServiceComponentID; // 6/12 bits
//useless unsigned short PacketAddress; //// FIG 0/8
//useless unsigned char SCIds;
// FIG 0/13
  unsigned char NumberofUserAppl; // MAX 12
  unsigned short UserApplType[USER_APPL_NUM_MAX];
  unsigned char UserApplLength[USER_APPL_NUM_MAX];
  unsigned char UserApplData[USER_APPL_NUM_MAX][USER_APPL_DATA_SIZE_MAX]; // max size 24 bytes

  unsigned char bVisualRadio; // 1 bits
} SubChInfoType;

typedef struct tag_EnsembleInfoType
{
  unsigned long EnsembleFrequency; // 4 bytes
  unsigned char TotalSubChNumber; // MAX: 64

  unsigned short EnsembleID;
  unsigned char EnsembleLabelCharField[ENSEMBLE_LABEL_SIZE_MAX+1]; //LOMO_PREVENT_FIX_#32261 by JYRYU_20080425
//useless unsigned short EnsembleLabelCharFlagField;
  SubChInfoType SubChInfo[SUB_CH_NUM_MAX];
} EnsembleInfoType;



#define TDMB_CMD_START_FLAG			0x7F
#define TDMB_CMD_END_FLAG			0x7E
#define TDMB_CMD_SIZE				30

/* -------------------------------------------------------------------------- */
/*  DMB Commands	 												 	         */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*   FIC	                                                                                                                         */
/* -------------------------------------------------------------------------- */
// DMB to AP

// Result Value
#define DMB_FIC_RESULT_FAIL	    0x00
#define DMB_FIC_RESULT_DONE	    0x01
#define DMB_TS_PACKET_RESYNC    0x02

//typedef struct
//{
//    
//} dmbDriverCmdHeader;


/* to implement driver-platform inferface */
//#define TDMB_FROM_FILE
#endif
