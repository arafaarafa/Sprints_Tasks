#ifndef STD_TYPES_H
#define	STD_TYPES_H



/* section : includes*/






/* section : Data Types Declarations*/
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef signed char sint8_t;
typedef signed short sint16;
typedef signed int sint32;
typedef uint8_t Std_ReturnType;

/* section : Macro Declaration*/
#define STD_HIGH        0x01
#define STD_LOW         0x00
#define STD_ON          0x01
#define STD_OFF         0x00
#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define E_OK            (Std_ReturnType)0x00
#define E_NOT_OK        (Std_ReturnType)0x01
#define NULL            '\0'

/* section : Macro Functions Declarations*/

/* section : Function Declaration*/

#endif	/* STD_TYPES_H */
