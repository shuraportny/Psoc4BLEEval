/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"


/* SENSOR DATA MAP */
//#define MODBUSADDRMSB       0
//#define MODBUSADDRLSB       1

#define DEVTYPEMSB          2
#define DEVTYPELSB          3

#define SYSREADING1         4
#define SYSREADING2         5
#define SYSREADING3         6
#define SYSREADING4         7
#define STATUSMSB           8
#define STATUSLSB           9
#define TEMPERATUREMSB     10
#define TEMPERATURELSB     11
#define HUMIDTYMSB         12
#define HUMIDTYLSB         13
#define PRESSUREMSB        14
#define PRESSURELSB        15

#define NA7MSB             16
#define NA7LSB             17
#define NA8MSB             18
#define NA8LSB             19
#define NA9MSB             20
#define NA9LSB             21
#define NA10MSB            22
#define NA10LSB            23
    
    //calib data
#define    SYSREMOTEMSB    24 //12
#define    SYSREMOTELSB    25
#define    CALSTATUSMSB    26 //13
#define    CALSTATUSLSB    27
#define    ZEROCALDATEMSB  28 //14
#define    ZEROCALDATELSB  29
#define    SPANCALDATEMSB  30 //15
#define    SPANCALDATELSB  31
#define    SENSORLIFEMSB   32 //16
#define    SENSORLIFELSB   33
#define    SPANASFOUND1    34 // 17 -18
#define    SPANASFOUND2    35
#define    SPANASFOUND3    36
#define    SPANASFOUND4    37
#define    NA18MSB         38 //19
#define    NA18LSB         39
#define    NA19MSB         40 //20
#define    NA19LSB         41
#define    NA20MSB         42 //21
#define    NA20LSB         43
    
    //static data

#define   RESOLUTIONMSB     44 //22
#define   RESOLUTIONLSB     45
#define   FULLSCALERANGE1   46 //23-24
#define   FULLSCALERANGE2   47
#define   FULLSCALERANGE3   48
#define   FULLSCALERANGE4   49
#define   COMPAUND1         50 // 25-29
#define   COMPAUND2         51
#define   COMPAUND3         52
#define   COMPAUND4         53
#define   COMPAUND5         54
#define   COMPAUND6         55
#define   COMPAUND7         56
#define   COMPAUND8         57
#define   COMPAUND9         58
#define   COMPAUND10        59
#define   UNIT1             60 //30-31
#define   UNIT2             61
#define   UNIT3             62
#define   UNIT4             63
#define   SERIALNUMBER1     64 //32-34
#define   SERIALNUMBER2     65
#define   SERIALNUMBER3     66
#define   SERIALNUMBER4     67
#define   SERIALNUMBER5     68
#define   SERIALNUMBER6     69
#define   WARMUPTIMEMSB     70 // 35
#define   WARMUPTIMELSB     71
#define   na72              72 //36
#define   na73              73


//config data 
#define   ALARM1MSB         74 //37
#define   ALARM1LSB         75
#define   ALARM1ASCMSB      76 //38
#define   ALARM1ASCLSB      77
#define   ALARM2MSB         78 //39
#define   ALARM2LSB         79
#define   ALARM2ASCMSB      80 //40
#define   ALARM2ASCLSB      81
#define   ALARM3MSB         82 //41
#define   ALARM3LSB         83
#define   ALARM3ASCMSB      84 //42
#define   ALARM3ASCLSB      85 
#define   CALLEVEL1         86 //43-44
#define   CALLEVEL2         87
#define   CALLEVEL3         88
#define   CALLEVEL4         89
#define   RESPFACTORMSB     90 //45
#define   RESPFACTORLSB     91

#define   na92             92  //46 -50       
#define   na93             93

//debug data
#define   na94             94
#define   na95             95
#define   na96             96
#define   na97             97
#define   na98             98
#define   na99             99
#define   na100            100
#define   na101            101
    
#define DATA_LENGTH         110 // [0-106]

#define SENSOR_TAG_LENGTH                   ( 20u )
#define FALSE                               ( 0u )
#define TRUE                                ( 1u )



typedef struct {
    uint32_t sysReading;
    uint16_t status;
    uint16_t temperature;
    uint16_t humidty;
    uint16_t pressure;
}S_Readings;

typedef struct {
    uint16_t sysRemote;
    uint16_t calStatus;
    uint16_t zeroCalDate;
    uint16_t spanCalDate;
    uint16_t sensorLife;
}S_Calib;

typedef struct {
    uint16_t devType;
    uint16_t resolution;
    uint16_t fullScaleRange;
    char compaund[10];
    char unit[4];
    char serialNumber[6];
    uint16_t warmUpTime;
    uint16_t alarm1;
    uint16_t alarm1asc;
    uint16_t alarm2;
    uint16_t alarm2asc;
    uint16_t alarm3;
    uint16_t alarm3asc;
}S_Static;

typedef struct {
    uint16_t calLevel;
    uint16_t RF;
}S_Cfg;

typedef struct {
    uint16_t dbg1;
    uint16_t dbg2;
    uint16_t dbg3;
    uint16_t dbg4;
    uint16_t dbg5;
    uint16_t dbg6;
    uint16_t dbg7;
    uint16_t dbg8;
    uint16_t dbg9;
    uint16_t dbg10;
}S_Debug;

typedef struct {
//    S_Readings readings;
//    S_Calib calib;
//    S_Static stat;
//    S_Cfg cfg;
//    S_Debug debug;
    
    // sys reading data
    uint32_t sysReading; //1 -2
    
    uint16_t status;        //3
    uint16_t temperature;   //4
    uint16_t humidty;       //5
    uint16_t pressure;      //6
    uint16_t na7;           //7
    uint16_t na8;           //8
    uint16_t na9;           //9
    uint16_t na10;          //10
    
    //calib data
    uint16_t sysRemote;     //11
    uint16_t calStatus;     //12
    uint16_t zeroCalDate;   //13
    uint16_t spanCalDate;   //14
    uint16_t sensorLife;    //15
    uint16_t na16;          //16
    uint16_t na17;          //17
    uint16_t na18;          //18
    uint16_t na19;          //19
    uint16_t na20;          //20
    
    //static data
    uint16_t devType;       //21
    uint16_t resolution;    //22
    uint16_t fullScaleRange;//23
    char compaund[10];      //24 - 28
    char unit[4];           //29-30
    char serialNumber[6];   //31 -33
    uint16_t warmUpTime;    //34
    uint16_t alarm1;        //35
    uint16_t alarm1asc;     //36
    uint16_t alarm2;        //37
    uint16_t alarm2asc;     //38
    uint16_t alarm3;        //39
    uint16_t alarm3asc;     //40
    
    //config data 
    uint16_t calLevel;      //41
    uint16_t RF;            //42
//    uint16_t na43;          //43         
//    uint16_t na44;          //44
//    uint16_t na45;          //45
//    uint16_t na46;          //46
//    uint16_t na47;          //47
//    uint16_t na48;          //48
//    uint16_t na49;          //49
//    uint16_t na50;          //50
//    
//    //debug data
//    uint16_t na51;          //51
//    uint16_t na52;          //52
//    uint16_t na53;          //53
//    uint16_t na54;          //54
//    uint16_t na55;          //55
//    uint16_t na56;          //56
//    uint16_t na57;          //57
//    uint16_t na58;          //58
//    uint16_t na59;          //59
//    uint16_t na60;          //60
    
}S_Sensor;


struct {
    uint16 PidCurrent;
    uint16 PidUnderCurrent;
    uint8  PidBuffer[10];
    uint8  Type;
    uint8  Mfg;
    int16  Reading;
    int16  ReadingPrevious;
    float  ReadingRaw;
    float  ReadingLinear;
    float  ReadingFloat;
    float  ReadingScaled;
    float  ReadingScaledPrevious;
    uint16 Status;
    uint16 StatusPrevious;
    
    int8   Life;
    int8   LifePrevious;
    int8   Temperature;
    int8   TemperaturePrevious;
    int8   TemperatureAtZero;
    int8   TemperatureAtSpan;
    uint16 MaOutput;
    uint16 HwStatus;
    uint16 CountsZeroScale;
    uint16 CountsHalfScale;
    int8   ZeroBlock;
    int16  CalLevel;
    int16  CalLevelPrevious;
    uint16 Gain;
    uint8  CalResult;
    int16  TemperatureOffset;
    int16  TemperatureLowFault;
    int16  TemperatureHighFault;
    uint16 ZeroCalTime;
    int16  ZeroCalTollerance;
    uint16 SpanCalApplyTime;
    int16  SpanCalApplyThreshold;
    uint16 SpanCalLeveloffTime;
    uint16 SpanCalStableTime;
    int16  SpanCalStableThreshold;
    uint16 SpanCalRemoveTime;
    uint16 SpanCalRemoveThreshold;
    uint16 Alert1;
    uint16 Alert2;
    uint16 Alert1Ascending;
    uint16 Alert2Ascending;
    uint16 Linear1Level;
    float  Linear1Value;
    uint16 Linear2Level;
    float  Linear2Value;
    uint16 Linear3Level;
    float  Linear3Value;
    float  Ztc_n10;
    float  Ztc_p35;
    float  Ztc_p50;
    float  Stc_n10;
    float  Stc_p35;
    float  Stc_p50;
    float  Ztc_curve_1;
    float  Ztc_curve_2;
    float  Ztc_curve_3;
    float  Stc_curve_1;
    float  Stc_curve_2;
    float  Stc_curve_3;
    float  Zero_adjust;
    float  Span_adjust;
    float  Ztc_apply;
    float  Stc_apply;
    uint16 VrefTollerance;
    uint16 WarmupTime;
    uint64 UpSerialNumber;
    uint64 DnSerialNumberH;
    uint64 DnSerialNumberL;
    char  SerialNumber[12];
    uint16 Range;
    char   GasNote[10];
    /* Sensor type specific below */
    uint16 CbBridgeVolts;
    uint16 CbBridgeVoltsToll;
    uint16 CbBridgeMamps;
    uint16 CbBridgeMampsToll;
    uint16 EcTiaReg;
    uint16 EcRefReg;
    uint16 EcModeReg;
    int16  AutoZeroMax;
    int16  AutoZeroDisable;
    uint16 Fractional;
} Sensor;


struct {
   uint8  BleControl;
    uint8  BleControlPrevious;
    uint8  BleNotifyReading;
    uint8  BleNotifyStatus;
    uint8  BleNotifyAlertStatus;
    uint8  BleNotifyControl;
    uint8  BleNotifyTemperature;
    uint8  BleNotifyLife;
    uint8  BleNotifyCalLevel;
    uint8  BleNotifyCalAsFound;
    uint8  BleNotifyCalAdjusted;
    uint8  BleNotifyCalZeroError;
    uint8  BleNotifyCalStep;
    uint8  BleNotifyCalSpeed;
    uint8  BleNotifyCalClearing;
    uint8  BleNotifyCalSpanError;
    uint8  BleNotifyReadingScaled;
    uint8  BleNotifyCalibrationStatus;
    uint8  BleNotifyAdcCounts;
    uint8  BleInAuxCalState;
    int16  Reading;
    uint16 AdcCounts;
    uint16 AdcCountsPrevious;
    uint16 Status;
    uint16 StatusPrevious;
    uint8  AlertStatus;
    uint8  AlertStatusPrevious;
    uint8  SysSerialNumber[8];
    char   SysSerialNumberString[16];
    char   ADFESerialNumberString[32];
    uint64 SensorSnL64;
    uint64 SensorSnU64;
    uint16 SysMa2;
    uint16 SysMa4;
    uint16 SysMa20;
    uint16 SysMaWarmup;
    uint16 SysMaOverRange;
    float  SysMaPerPctFullScale;
    uint8  CanNodeId;
    uint8  CanChannel;
    uint8  CanControl;
    uint16 BleCalLoop;
    char   SensorTag[20];
    int8  CalAsFound;
    int8  CalAsFoundPrevious;
    int8  CalAdjusted;
    int8  CalAdjustedPrevious;
    uint8  CalibrationStatus;
    uint8  CalibrationStatusPrevious;
    uint16 CalZCounts;
    uint8  CalZeroError;
    uint8  CalZeroErrorPrevious;
    uint8  CalStep;
    uint8  CalStepPrevious;
    uint16 CalSpeed;
    uint16 CalSpeedPrevious;
    uint16 CalCounts;
    uint16 CalClearing;
    uint16 CalClearingPrevious;
    uint8  CalSpanError;
    uint8  CalSpanErrorPrevious;
    char   Pin[4];
    uint8  DemoState;
    uint16 TestStatus;
    uint16 TestStatusPrevious;
    uint8  NumberOfSensors;
    uint16 FlowRate;
} System;


void initSensor(void);


/* [] END OF FILE */
