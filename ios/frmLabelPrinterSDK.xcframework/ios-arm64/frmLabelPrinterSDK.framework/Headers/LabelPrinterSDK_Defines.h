
/**************************************************************************************************
 *  Define Result Code
 *************************************************************************************************/
typedef NS_ENUM(long, __SDK_RESULT_CODES_) {
    _SDK_RESULT_SUCCESS                     = 0x0000,
    _SDK_RESULT_FAIL                        = 0xF000,
    _SDK_RESULT_FAIL_NOT_SUPPORT_FUNCTION  ,// = 0xF002,
    _SDK_RESULT_FAIL_NO_OPEN               ,
    _SDK_RESULT_FAIL_OPEN_ALREADY          ,
    _SDK_RESULT_FAIL_NO_CONNECT            ,
    _SDK_RESULT_FAIL_CONNECT_ALREADY       ,
    _SDK_RESULT_FAIL_WRITE_ERROR           ,
    _SDK_RESULT_FAIL_READ_ERROR            ,
    _SDK_RESULT_FAIL_INVALID_PARAMETER     ,
    _SDK_RESULT_FAIL_NO_RESPONSE           ,
};

/////////////////////////////////////////////////////////////////////
// InterfaceType
/////////////////////////////////////////////////////////////////////
typedef NS_ENUM(NSUInteger, __SDK_INTERFACE_TYPE) {
    _SDK_INTERFACETYPE_WIFI           = 1,
    _SDK_INTERFACETYPE_ETHERNET       = 2,
    _SDK_INTERFACETYPE_BLUETOOTH      = 4,
    _SDK_INTERFACETYPE_BLUETOOTH_NON_EXCLUSIVE      = 0xF0+_SDK_INTERFACETYPE_BLUETOOTH,
    
    _SDK_INTERFACETYPE_BROADCAST      = 8,
    _SDK_INTERFACETYPE_BLUETOOTH_BLE  = 10,
    
    
};
/**************************************************************************************************
 *  Define Alignment List
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_ALIGNMENTS) {
    _SDK_ALIGNMENT_LEFT                     = 0,
    _SDK_ALIGNMENT_RIGHT                    = 1,
    _SDK_ALIGNMENT_CENTER                   = 2,    //  Device Text is not support
    _SDK_ALIGNMENT_STRING_FROM_RIGHT_2_LEFT = 2,    //  Vector Text is not support
};


/**************************************************************************************************
 *  Define Barcode Text Postion and FontSize
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_BARCODE_HRI) {
    _SDK_BARCODE_HRI_NONE                     = 0,
    _SDK_BARCODE_HRI_BELOW_FONTSIZE1          = 1,
    _SDK_BARCODE_HRI_ABOVE_FONTSIZE1          = 2,
    _SDK_BARCODE_HRI_BELOW_FONTSIZE2          = 3,
    _SDK_BARCODE_HRI_ABOVE_FONTSIZE2          = 4,
    _SDK_BARCODE_HRI_BELOW_FONTSIZE3          = 5,
    _SDK_BARCODE_HRI_ABOVE_FONTSIZE3          = 6,
    _SDK_BARCODE_HRI_BELOW_FONTSIZE4          = 7,
    _SDK_BARCODE_HRI_ABOVE_FONTSIZE4          = 8,
};

/**************************************************************************************************
 *  set Printing Type
 *************************************************************************************************/
typedef NS_ENUM(char, __SDK_PRINTING_TYPE) {
    _SDK_PRINTING_TYPE_DIRECT_THERMAL      = 'd',
    _SDK_PRINTING_TYPE_THERMAL_TRANSFER    = 't',
};



/**************************************************************************************************
 *  Media Type  for parameter in 'setLength'
 *************************************************************************************************/
typedef NS_ENUM(char, __SDK_MEDIA_TYPE) {
    _SDK_MEDIA_TYPE_GAP                    = 'G',
    _SDK_MEDIA_TYPE_CONTINUOUS             = 'C',
    _SDK_MEDIA_TYPE_BLACK_MARK             = 'B',
};



/**************************************************************************************************
 *  Speed  for parameter in 'setSpeed'
 *************************************************************************************************/
typedef NS_ENUM(NSInteger, __SDK_SPEED_VALUE) {
    _SDK_SPEED_VALUE_1_0_IPS               = 7,
    _SDK_SPEED_VALUE_2_0_IPS               = 8,
    _SDK_SPEED_VALUE_2_5_IPS               = 0,
    _SDK_SPEED_VALUE_3_0_IPS               = 1,
    _SDK_SPEED_VALUE_4_0_IPS               = 2,
    _SDK_SPEED_VALUE_5_0_IPS               = 3,
    _SDK_SPEED_VALUE_6_0_IPS               = 4,
    _SDK_SPEED_VALUE_7_0_IPS               = 5,
    _SDK_SPEED_VALUE_8_0_IPS               = 6,
    _SDK_SPEED_VALUE_9_0_IPS               = 9,
    _SDK_SPEED_VALUE_10_0_IPS              = 10,
    _SDK_SPEED_VALUE_11_0_IPS              = 11,
    _SDK_SPEED_VALUE_12_0_IPS              = 12,
    _SDK_SPEED_VALUE_13_0_IPS              = 13,
    _SDK_SPEED_VALUE_14_0_IPS              = 14
};


/**************************************************************************************************
 *  Define Barcode Text Postion and FontSize
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_BARCODE_TYPE) {
    _SDK_BARCODE_TYPE_CODE39                   = 0,
    _SDK_BARCODE_TYPE_CODE128                  = 1,
    _SDK_BARCODE_TYPE_I2Of5                    = 2,
    _SDK_BARCODE_TYPE_CODABAR                  = 3,
    _SDK_BARCODE_TYPE_CODE93                   = 4,
    _SDK_BARCODE_TYPE_UPC_A                    = 5,
    _SDK_BARCODE_TYPE_UPC_E                    = 6,
    _SDK_BARCODE_TYPE_EAN13                    = 7,
    _SDK_BARCODE_TYPE_EAN8                     = 8,
    _SDK_BARCODE_TYPE_EAN128                   = 9,
    _SDK_BARCODE_TYPE_CODE11                   = 10,
    _SDK_BARCODE_TYPE_PLANET                   = 11,
    _SDK_BARCODE_TYPE_INDUSTRIAL_2Of5          = 12,
    _SDK_BARCODE_TYPE_STANDARD_2Of5            = 13,
    _SDK_BARCODE_TYPE_LOGMARS                  = 14,
    _SDK_BARCODE_TYPE_UPC_EAN_EXTENSIONS       = 15,
    _SDK_BARCODE_TYPE_POSTNET                  = 16,
};

/**************************************************************************************************
 *  Define MEXI CODE MODE
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_MEXICODE_MODE) {
    _SDK_MEXICODE_MODE_0                     = 0,
    _SDK_MEXICODE_MODE_2                     = 2,
    _SDK_MEXICODE_MODE_3                     = 3,
    _SDK_MEXICODE_MODE_4                     = 4,
};

/**************************************************************************************************
 *  Define BARCODE Origin point
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_BARCODE_ORIGIN_POINT) {
    _SDK_BARCODE_ORIGIN_POINT_CENTER         = 0,
    _SDK_BARCODE_ORIGIN_POINT_UpperLeft      = 1,
};
/**************************************************************************************************
 *  Define Error Correction Level
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_ERROR_CORRECTION_LEVEL) {
    _SDK_ERROR_CORRECTION_LEVEL0           = 0,
    _SDK_ERROR_CORRECTION_LEVEL1           = 1,
    _SDK_ERROR_CORRECTION_LEVEL2           = 2,
    _SDK_ERROR_CORRECTION_LEVEL3           = 3,
    _SDK_ERROR_CORRECTION_LEVEL4           = 4,
    _SDK_ERROR_CORRECTION_LEVEL5           = 5,
    _SDK_ERROR_CORRECTION_LEVEL6           = 6,
    _SDK_ERROR_CORRECTION_LEVEL7           = 7,
    _SDK_ERROR_CORRECTION_LEVEL8           = 8,
};

/**************************************************************************************************
 *  Define Data Compression Method
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_DATA_COMPRESSION_METHOD) {
    _SDK_DATA_COMPRESSION_METHOD_TEXT       = 0,
    _SDK_DATA_COMPRESSION_METHOD_NUMERIC    = 1,
    _SDK_DATA_COMPRESSION_METHOD_BINARY     = 2,
};

/**************************************************************************************************
 *  Define QR CODE MODEL
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_QRCODE_MODE) {
    _SDK_QRCODE_MODEL_1                     = 1,
    _SDK_QRCODE_MODEL_2                     = 2,
};

/**************************************************************************************************
 *  Define Code49 STARTING MODE
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_STARTING_MODE) {
    _SDK_STARTINGMODE_REGULAR_ALPHANUMERIC      = 0,
    _SDK_STARTINGMODE_MULTIPLE_READ_ALPHANUMERIC= 1,
    _SDK_STARTINGMODE_REGULAR_NUMERIC           = 2,
    _SDK_STARTINGMODE_GROUP_ALPHANUMERIC        = 3,
    _SDK_STARTINGMODE_REGULAR_ALPHANUMRIC_SHIFT1= 4,
    _SDK_STARTINGMODE_REGULAR_ALPHANUMRIC_SHIFT2= 5,
    _SDK_STARTINGMODE_AUTOMATIC                 = 7,
};


/**************************************************************************************************
 *  Define CODABLOCK MODE
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_CODABLACK_MODE) {
    _SDK_CODABLACK_MODE_A                   = 'A',
    _SDK_CODABLACK_MODE_E                   = 'E',
    _SDK_CODABLACK_MODE_F                   = 'F',
    
};


/**************************************************************************************************
 *  Define CHECK DIGIT OPTION
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, _SDK_CHECKDIGIT) {
    _SDK_CHECKDIGIT_NONE                    = 0,
    _SDK_CHECKDIGIT_1MOD10                  = 1,
    _SDK_CHECKDIGIT_2MOD10                  = 2,
    _SDK_CHECKDIGIT_1MOD11_AND_1MOD_10      = 3,
    
};


/**************************************************************************************************
 *  Define RSS Barcode Type
 *************************************************************************************************/
typedef NS_ENUM(NSUInteger, __SDK_RSS_BARCODE_TYPE) {
    _SDK_RSS_BARCODE_TYPE_RSS14                = 0,
    _SDK_RSS_BARCODE_TYPE_RSS14_TRUNCATED      = 1,
    _SDK_RSS_BARCODE_TYPE_RSS14_STACKED        = 2,
    _SDK_RSS_BARCODE_TYPE_RSS14_STACKED_OMNIDIRECTIONAL = 3,
    _SDK_RSS_BARCODE_TYPE_RSS_LIMITED          = 4,
    _SDK_RSS_BARCODE_TYPE_RSS_EXPANDED         = 5,
    _SDK_RSS_BARCODE_TYPE_UPC_A                = 6,
    _SDK_RSS_BARCODE_TYPE_UPC_E                = 7,
    _SDK_RSS_BARCODE_TYPE_EAN13                = 8,
    _SDK_RSS_BARCODE_TYPE_EAN8                 = 9,
    _SDK_RSS_BARCODE_TYPE_UCC_EAN128_CC_A_B    = 10,
    _SDK_RSS_BARCODE_TYPE_UCC_EAN128_CC_C      = 11,
    
};

/**************************************************************************************************
 *  Define Font Attributes List
 *************************************************************************************************/
typedef enum{
    _SDK_ROTATION_DEGREES_0                 = 0,
    _SDK_ROTATION_DEGREES_90                = 1,
    _SDK_ROTATION_DEGREES_180               = 2,
    _SDK_ROTATION_DEGREES_270               = 3,
}__SDK_ROTATION_DEGREES;

/**************************************************************************************************
 *  Define Orientation List
 *************************************************************************************************/
typedef enum{
    _SDK_ORIENTATION_TOP_BOTTOM             = 0,
    _SDK_ORIENTATION_BOTTOM_TOP             = 1,
}__SDK_ORIENTAIONS;



/**************************************************************************************************
 *  Define Device Fonts List
 *************************************************************************************************/
typedef enum {
    _SDK_DEVICE_FONT_6PT                   ='0',         //    9 X 15 (dots)
    _SDK_DEVICE_FONT_8PT                   ='1',         //   12 X 20 (dots)
    _SDK_DEVICE_FONT_10PT                  ='2',         //   16 X 25 (dots)
    _SDK_DEVICE_FONT_12PT                  ='3',         //   19 X 30 (dots)
    _SDK_DEVICE_FONT_15PT                  ='4',         //   24 X 38 (dots)
    _SDK_DEVICE_FONT_20PT                  ='5',         //   32 X 40 (dots)
    _SDK_DEVICE_FONT_30PT                  ='6',         //   48 X 76 (dots)
    _SDK_DEVICE_FONT_14PT                  ='7',         //   22 X 34 (dots)
    _SDK_DEVICE_FONT_18PT                  ='8',         //   28 X 44 (dots)
    _SDK_DEVICE_FONT_24PT                  ='9',         //   37 X 58 (dots)
    _SDK_DEVICE_FONT_KOREAN1               ='a',         //   16 X 16 (dots)  (ascii  9 X 15)
    _SDK_DEVICE_FONT_KOREAN2               ='b',         //   24 X 24 (dots)  (ascii 12 X 24)
    _SDK_DEVICE_FONT_KOREAN3               ='c',         //   20 X 20 (dots)  (ascii 12 X 20)
    _SDK_DEVICE_FONT_KOREAN4               ='d',         //   26 X 26 (dots)  (ascii 16 X 30)
    _SDK_DEVICE_FONT_KOREAN5               ='e',         //   20 X 26 (dots)  (ascii 16 X 30)
    _SDK_DEVICE_FONT_KOREAN6               ='f',         //   38 X 38 (dots)  (ascii 22 X 34)
    _SDK_DEVICE_FONT_GB2312                ='m',         //   24 X 24 (dots)  (ascii 12 X 24)
    _SDK_DEVICE_FONT_BIG5                  ='n',         //   24 X 24 (dots)  (ascii 12 X 24)
    _SDK_DEVICE_FONT_SHIFT_JIS             ='j',         //   24 X 24 (dots)  (ascii 12 X 24)
}__SDK_DEVICE_FONT;


/**************************************************************************************************
 *  Define Vector Fonts List
 *************************************************************************************************/
typedef enum {
    
    _SDK_VECTOR_FONT_ASCII                  ='U',
    _SDK_VECTOR_FONT_KS5601                 ='K',
    _SDK_VECTOR_FONT_BIG5                   ='B',
    _SDK_VECTOR_FONT_GB2312                 ='G',
    _SDK_VECTOR_FONT_SHIFT_JIS              ='J',
    _SDK_VECTOR_FONT_OCR_A                  ='a',
    _SDK_VECTOR_FONT_OCR_B                  ='b',
    
}__SDK_VECTOR_FONT;


/**************************************************************************************************
 *  Define Block draw options List
 *************************************************************************************************/
typedef enum {
    _SDK_DRAW_BLOCK_OPTION_LINE_OVERWRITING ='O',
    _SDK_DRAW_BLOCK_OPTION_LINE_EXCLUSIVE_OR='E',
    _SDK_DRAW_BLOCK_OPTION_LINE_DELETE      ='D',
    _SDK_DRAW_BLOCK_OPTION_SLOPE            ='S',
    _SDK_DRAW_BLOCK_OPTION_BOX              ='B',
}__SDK_DRAW_BLOCK_OPTION;


/**************************************************************************************************
 *  Define Circle sizes List
 *************************************************************************************************/
typedef enum {
    _SDK_DRAW_CIRCLE_SIZE_40X40             = 1,    //  5(mm) diameter
    _SDK_DRAW_CIRCLE_SIZE_56X56             = 2,
    _SDK_DRAW_CIRCLE_SIZE_72X72             = 3,
    _SDK_DRAW_CIRCLE_SIZE_88X88             = 4,
    _SDK_DRAW_CIRCLE_SIZE_104X104           = 5,
    _SDK_DRAW_CIRCLE_SIZE_168X168           = 6,
}__SDK_DRAW_CIRCLE_SIZE;



/**************************************************************************************************
 *  Define International Character Set
 *************************************************************************************************/
typedef enum {
    _SDK_CONFIG_ICS_USA                    = 0,
    _SDK_CONFIG_ICS_FRANCE                 = 1,
    _SDK_CONFIG_ICS_GERMANY                = 2,
    _SDK_CONFIG_ICS_UK                     = 3,
    _SDK_CONFIG_ICS_DENMARK_I              = 4,
    _SDK_CONFIG_ICS_SWEDEN                 = 5,
    _SDK_CONFIG_ICS_ITALY                  = 6,
    _SDK_CONFIG_ICS_SPAIN_I                = 7,
    _SDK_CONFIG_ICS_NORWAY                 = 8,
    _SDK_CONFIG_ICS_DENMARK_II             = 9,
    _SDK_CONFIG_ICS_JAPAN                  = 10,
    _SDK_CONFIG_ICS_SPAIN_II               = 11,
    _SDK_CONFIG_ICS_LATIN_AMERICA          = 12,
    _SDK_CONFIG_ICS_KOREA                  = 13,
    _SDK_CONFIG_ICS_SLOVENIA_CROATIA       = 14,
    _SDK_CONFIG_ICS_CHINA                  = 15,
}__SDK_CONFIG_ICS;

/**************************************************************************************************
 *  Define Code pages
 *************************************************************************************************/
typedef enum {
    _SDK_CONFIG_CODEPAGE_CP437             = 0,
    _SDK_CONFIG_CODEPAGE_CP850             = 1,
    _SDK_CONFIG_CODEPAGE_CP852             = 2,
    _SDK_CONFIG_CODEPAGE_CP860             = 3,
    _SDK_CONFIG_CODEPAGE_CP863             = 4,
    _SDK_CONFIG_CODEPAGE_CP865             = 5,
    _SDK_CONFIG_CODEPAGE_CP1252            = 6,
    _SDK_CONFIG_CODEPAGE_CP865_WCP1252     = 7,
    _SDK_CONFIG_CODEPAGE_CP857             = 8,
    _SDK_CONFIG_CODEPAGE_CP737             = 9,
    _SDK_CONFIG_CODEPAGE_WPC1250           = 10,
    _SDK_CONFIG_CODEPAGE_WPC1253           = 11,
    _SDK_CONFIG_CODEPAGE_WPC1254           = 12,
    _SDK_CONFIG_CODEPAGE_CP855             = 13,
    _SDK_CONFIG_CODEPAGE_CP862             = 14,
    _SDK_CONFIG_CODEPAGE_CP866             = 15,
    _SDK_CONFIG_CODEPAGE_WCP1251           = 16,
    _SDK_CONFIG_CODEPAGE_WCP1255           = 17,
    _SDK_CONFIG_CODEPAGE_CP928             = 18,
    _SDK_CONFIG_CODEPAGE_CP864             = 19,
    _SDK_CONFIG_CODEPAGE_CP775             = 20,
    _SDK_CONFIG_CODEPAGE_WCP1257           = 21,
    _SDK_CONFIG_CODEPAGE_CP858             = 22,
}__SDK_CONFIG_CODEPAGE;


/**************************************************************************************************
* Dithering Type Option  (This defines will be use to when convert NSString to char)
*************************************************************************************************/
typedef enum {
    _SDK_COMPRESS_TYPE_NONE = 0,
    _SDK_COMPRESS_TYPE_RLE,
    _SDK_COMPRESS_TYPE_LZMA
}__SDK_COMPRESS_TYPE;

/**************************************************************************************************
 *  Define Endcoding Options (This defines will be use to when convert NSString to char)
 *************************************************************************************************/
typedef NS_ENUM(NSStringEncoding, __SDK_ENCODING_OPTIONS) {
    _SDK_ENCODING_OPTION_AUTOMATIC      = 0xFFFFFFFF,
    _SDK_ENCODING_OPTION_ASCII          = 0x00000001,
    _SDK_ENCODING_OPTION_KSC5601        = 0x80000422,
    _SDK_ENCODING_OPTION_SHIFT_JIS      = 0x00000008,
    _SDK_ENCODING_OPTION_BIG5           = 0x80000a03,
    _SDK_ENCODING_OPTION_GB2312         = 0x80000421,
    _SDK_ENCODING_OPTION_GB18030        = 0x80000632,
    
};


/**************************************************************************************************
 *  Define Status
 *************************************************************************************************/
typedef NS_OPTIONS(NSInteger, __SDK_STATUS) {
    _SDK_STATUS_PRINTER_PAPEREMPTY          = 0x0080,
    _SDK_STATUS_PRINTER_COVEROPEN           = 0x0040,
    _SDK_STATUS_PRINTER_CUTTER_JAMMED       = 0x0020,
    _SDK_STATUS_PRINTER_TPH_OVERHEAT        = 0x0010,
    _SDK_STATUS_PRINTER_GAP_ERROR           = 0x0008,   // Media Calibration (Detection) Error (Contains Paper Jam detection)
    _SDK_STATUS_PRINTER_RIBBON_END          = 0x0004,
    _SDK_STATUS_PRINTER_ROLL_NEAREMPTY      = 0x0002,   // Roll Near Empty
    _SDK_STATUS_PRINTER_BUILDING_LABEL      = 0x8000,
    _SDK_STATUS_PRINTER_PRINTING_LABEL      = 0x4000,
    _SDK_STATUS_PRINTER_ISSUED_LABEL        = 0x2000,
    _SDK_STATUS_PRINTER_PAUSE               = 0x1000,   // Stand-by
    _SDK_STATUS_PRINTER_PAUSE2              = 0x0800    // Pause
};

/**************************************************************************************************
 *  Define blocks type
 *************************************************************************************************/
typedef void (^blockType1)(NSInteger Parameter);
typedef void (^blockType2)(NSData* Parameter);

/**************************************************************************************************
 *  Define Widths
 *************************************************************************************************/
#define _SDK_WIDTH_FULL         -1










