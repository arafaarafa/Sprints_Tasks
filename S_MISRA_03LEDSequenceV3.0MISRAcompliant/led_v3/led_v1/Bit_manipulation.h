#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

#define HWREG8(_X)      (*((volatile uint8_t *)(_X)))
#define BIT_MASK        0x01

#define CLEAR_BIT(REG, BIT_POSN)            (REG &= (~(BIT_MASK << BIT_POSN)))  /*clear a specific bit in reg*/
#define SET_BIT(REG, BIT_POSN)              (REG |= (BIT_MASK << BIT_POSN))     /*set a specific bit in reg*/
#define TOGGLE_BIT(REG, BIT_POSN)           (REG ^= (BIT_MASK << BIT_POSN))     /*toggle specific bit in reg*/
#define READ_BIT(REG, BIT_POSN)             (((REG >> BIT_POSN) & BIT_MASK))    /*read a specific bit in reg*/
#define SET_LOW_NIBBLE_BITS(REG, DATA)      (REG = ((REG&0xF0)|(DATA&0x0F)))
#define SET_HIGH_NIBBLE_BITS(REG, DATA)     (REG = ((REG&0x0F)|(DATA&0xF0)))



#endif  // BIT_MANIPULATION_H
