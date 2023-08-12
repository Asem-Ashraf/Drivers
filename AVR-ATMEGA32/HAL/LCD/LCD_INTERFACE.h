 /* LCD_INTERFACE_H_ */
/**
 * @file LCD_Interface.h
 *
 * @brief This file contains the interface for controlling an LCD display.
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "../../LIB/STD_TYPE.h"
#include "../../LIB/ERR_TYPE.h"

/**
 * @struct LCD_t
 *
 * @brief This struct contains the configuration settings for an LCD display.
 */
typedef struct {
    // MODE
    u8 LCD_u8Mode;          /**< LCD_u8MODE_8BIT, LCD_u8MODE_4BIT */


    // CURSOR
    u8 LCD_u8Cursor;        /**< LCD_u8CURSOR_ON, LCD_u8CURSOR_OFF */
    u8 LCD_u8CursorBlink;   /**< LCD_u8CURSOR_BLINK_ON, LCD_u8CURSOR_BLINK_OFF */


    // LINES
    u8 LCD_u8LinesNum;      /**< LCD_u8LINES_2, LCD_u8LINES_1 */


    // BLOCK
    u8 LCD_u8BlockSize;     /**< LCD_u8BLOCK_SIZE_5x10, LCD_u8BLOCK_SIZE_5x7 */


    // CONTROL
    u8 LCD_u8RSPort;
    u8 LCD_u8RSPin;

    u8 LCD_u8RWPort;
    u8 LCD_u8RWPin;

    u8 LCD_u8EPort;
    u8 LCD_u8EPin;


    // DATA
    u8 LCD_u8DB0Port;
    u8 LCD_u8DB0Pin;

    u8 LCD_u8DB1Port;
    u8 LCD_u8DB1Pin;

    u8 LCD_u8DB2Port;
    u8 LCD_u8DB2Pin;

    u8 LCD_u8DB3Port;
    u8 LCD_u8DB3Pin;

    u8 LCD_u8DB4Port;
    u8 LCD_u8DB4Pin;

    u8 LCD_u8DB5Port;
    u8 LCD_u8DB5Pin;

    u8 LCD_u8DB6Port;
    u8 LCD_u8DB6Pin;

    u8 LCD_u8DB7Port;
    u8 LCD_u8DB7Pin;
} LCD_t;


/**
 * @brief Initializes the LCD display.
 *
 * This function initializes the LCD display using the configuration settings in 
 * the provided LCD_t struct.
 *
 * @param None.
 *
 * @return ES_t - Error status.
 *         ES_OK if initialization is successful, ES_NOK otherwise.
 */
ES_t LCD_enuInit(void);


/**
 * @brief Moves the cursor to a specified position on the LCD display.
 *
 * This function moves the cursor to the specified position (x,y) on the LCD 
 * display.
 *
 * @param LCD_pstructDisplay - Pointer to an LCD_t struct containing the LCD 
 * display configuration settings.
 *        x - Column number (0-15) to move the cursor to.
 *        y - Row number (0-1) to move the cursor to.
 *
 * @return ES_t - Error status.
 *         ES_NULL_POINTER if any of the args are nulls
 *         ES_OUT_OF_RANGE if the pointer to the lcd struct is invalid
 *         ES_OK if the cursor is moved successfully, ES_NOK otherwise.
 */ 
ES_t LCD_enuGotoPosition(LCD_t* LCD_pstructDisplay, u8 x, u8 y);


/**
 * @brief Writes a character to the LCD display.
 *
 * This function writes the provided character to the LCD display at the 
 * current cursor position.
 *
 * @param LCD_pstructDisplay - Pointer to an LCD_t struct containing the LCD d
 * isplay configuration settings.
 *        Data - The character to write to the LCD display.
 *
 * @return ES_t - Error status.
 *         ES_OK if the character is written successfully
 *         ES_NULL_POINTER if any of the args are nulls
 *         ES_OUT_OF_RANGE if the pointer to the lcd struct is invalid
 *         ES_NOK otherwise.
 */
ES_t LCD_enuWriteChar(LCD_t* LCD_pstructDisplay, u8 Data);

/**
 * @brief Writes a string to the LCD display.
 *
 * This function writes the provided string to the LCD display starting at the 
 * current cursor position. If the string is bigger than the remaining line, 
 * the remaining of the string will NOT be shown on the screen.
 *
 * @param LCD_pstructDisplay - Pointer to an LCD_t struct containing the LCD 
 * display configuration settings.
 * @param Data - Pointer to the string to write to the LCD display.
 *
 * @return ES_t - Error status.
 *         ES_OK if the character is written successfully
 *         ES_NULL_POINTER if any of the args are nulls
 *         ES_OUT_OF_RANGE if the pointer to the lcd struct is invalid
 *         ES_NOK otherwise.
 */
ES_t LCD_enuWriteString(LCD_t* LCD_pstructDisplay,u8* Data);

/**
 * @brief Clears the LCD display.
 *
 * This function clears the entire LCD display.
 *
 * @param LCD_pstructDisplay - Pointer to an LCD_t struct containing the LCD 
 * display configuration settings.
 *
 * @return ES_t - Error status.
 *         ES_NULL_POINTER if any of the args are nulls
 *         ES_OUT_OF_RANGE if the pointer to the lcd struct is invalid
 *         ES_OK if the display is cleared successfully, ES_NOK otherwise.
 */
ES_t LCD_enuClear(LCD_t* LCD_pstructDisplay);


/**
 * @brief Turns on the LCD display.
 *
 * This function turns on the LCD display.
 *
 * @param LCD_pstructDisplay - Pointer to an LCD_t struct containing the LCD 
 * display configuration settings.
 *
 * @return ES_t - Error status.
 *         ES_NULL_POINTER if any of the args are nulls
 *         ES_OUT_OF_RANGE if the pointer to the lcd struct is invalid
 *         ES_OK if the display is turned on successfully, ES_NOK otherwise.
 */
ES_t LCD_enuDisplayOn(LCD_t* LCD_pstructDisplay);


/**
 * @brief Turns off the LCD display.
 *
 * This function turns off the LCD display.
 *
 * @param LCD_pstructDisplay - Pointer to an LCD_t struct containing the LCD 
 * display configurationsettings.
 *
 * @return ES_t - Error status.
 *         ES_NULL_POINTER if any of the args are nulls
 *         ES_OUT_OF_RANGE if the pointer to the lcd struct is invalid
 *         ES_OK if the display is turned off successfully, ES_NOK otherwise.
 */
ES_t LCD_enuDisplayOff(LCD_t* LCD_pstructDisplay);


/**
 * @brief Sends a write command to the LCD display.
 *
 * This function sends the provided command code to the LCD display.
 *
 * @param LCD_pstructDisplay - Pointer to an LCD_t struct containing the LCD 
 * display configuration settings.
 *        Command - The command code to send to the LCD display.
 *
 * @return ES_t - Error status.
 *         ES_NULL_POINTER if any of the args are nulls
 *         ES_OUT_OF_RANGE if the pointer to the lcd struct is invalid
 *         ES_OK if the command is sent successfully, ES_NOK otherwise.
 */
ES_t LCD_enuSendWriteCommand(LCD_t* LCD_pstructDisplay, u8 Command);


#endif /* LCD_INTERFACE_H_ */
