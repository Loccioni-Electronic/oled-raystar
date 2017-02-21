/******************************************************************************
 * Copyright (C) 2016-2017 AEA s.r.l. Loccioni Group - Elctronic Design Dept.
 *
 * Authors:
 *  Simon Schuster <s.schuster@loccioni.com>
 *  Marco Giammarini <m.giammarini@loccioni.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ******************************************************************************/

/**
 * @mainpage OLED Raystar library based on @a libohiboard
 *
 * This project...
 *
 * @section changelog ChangeLog
 *
 * @li v1.0 of 2017/02/21 - First release
 *
 * @section library External Library
 *
 * The library use the following external library
 * @li libohiboard https://github.com/ohilab/libohiboard a C framework for
 * NXP Kinetis microcontroller
 *
 * @section thanksto Thanks to...
 *
 * @li Simon Schuster
 * @li Marco Giammarini
 *
 */

#ifndef __LOCCIONI_OLEDRAYSTAR_H
#define __LOCCIONI_OLEDRAYSTAR_H

#define LOCCIONI_OLEDRAYSTAR_LIBRARY_VERSION     "1.0"
#define LOCCIONI_OLEDRAYSTAR_LIBRARY_VERSION_M   1
#define LOCCIONI_OLEDRAYSTAR_LIBRARY_VERSION_m   0
#define LOCCIONI_OLEDRAYSTAR_LIBRARY_TIME        1487671913

#include "libohiboard.h"

//#include "cli/cli.h"

/**
 * The enum define all the possible error for the framework.
 */
typedef enum _OledRaystar_Errors
{
    OLEDRAYSTAR_ERRORS_OK,
    OLEDRAYSTAR_ERRORS_WRONG_POSITION,
    OLEDRAYSTAR_ERRORS_WRONG_VALUE,

} OledRaystar_Errors;

/**
 * A usefull enum that define all the possbile color for each pixel.
 */
typedef enum _OledRaystar_GrayScale
{
    OLEDRAYSTAR_GRAYSCALE_0  = 0,
    OLEDRAYSTAR_GRAYSCALE_1  = 1,
    OLEDRAYSTAR_GRAYSCALE_2  = 2,
    OLEDRAYSTAR_GRAYSCALE_3  = 3,
    OLEDRAYSTAR_GRAYSCALE_4  = 4,
    OLEDRAYSTAR_GRAYSCALE_5  = 5,
    OLEDRAYSTAR_GRAYSCALE_6  = 6,
    OLEDRAYSTAR_GRAYSCALE_7  = 7,
    OLEDRAYSTAR_GRAYSCALE_8  = 8,
    OLEDRAYSTAR_GRAYSCALE_9  = 9,
    OLEDRAYSTAR_GRAYSCALE_10 = 10,
    OLEDRAYSTAR_GRAYSCALE_11 = 11,
    OLEDRAYSTAR_GRAYSCALE_12 = 12,
    OLEDRAYSTAR_GRAYSCALE_13 = 13,
    OLEDRAYSTAR_GRAYSCALE_14 = 14,
    OLEDRAYSTAR_GRAYSCALE_15 = 15,
} OledRaystar_GrayScale;

/**
 * All managed devices from the library.
 */
typedef enum _OledRaystar_Model
{
    OLEDRAYSTAR_MODEL_REX012864F,
} OledRaystar_Model;

typedef struct _OledRaystar_Device
{
    Gpio_Pins rd;
    Gpio_Pins dc;
    Gpio_Pins rs;
    Gpio_Pins cs;
    Gpio_Pins wr;

    Gpio_Pins d0;
    Gpio_Pins d1;
    Gpio_Pins d2;
    Gpio_Pins d3;
    Gpio_Pins d4;
    Gpio_Pins d5;
    Gpio_Pins d6;
    Gpio_Pins d7;

    OledRaystar_Model model;

    uint8_t columns;
    uint8_t rows;

    uint8_t xPosition;
    uint8_t yPosition;

    bool isVertical;

    void (*delayTime)(uint32_t delay);       /**< Function for blocking delay */

    // TODO: fixed dimensions?
    uint8_t dump [64][64];          /**< Buffer to store display modification */
    uint8_t dumpOld [64][64];         /**< Buffer to store old display status */

} OledRaystar_Device;

/**
 * The function initialize the device and all related pin of the
 * microcontroller.
 *
 * @param[in] dev The handle of the device
 */
void OledRaystar_init (OledRaystar_Device* dev);

/**
 * The function switch on the display.
 *
 * @param[in] dev The handle of the device
 */
void OledRaystar_setDisplayOn (OledRaystar_Device* dev);

/**
 * The function switch off the display.
 *
 * @param[in] dev The handle of the device
 */
void OledRaystar_setDisplayOff (OledRaystar_Device* dev);

/**
 * The function set the current contrast of the display. The chip has
 * 128 contrast steps from 00H to 7FH.
 *
 * @param[in] dev The handle of the device
 * @param[in] value The level of the contrast
 * @return An error if the value is greater than the maximum allowed,
 *         OLEDRAYSTAR_ERRORS_OK otherwise.
 */
OledRaystar_Errors OledRaystar_setContrast (OledRaystar_Device* dev, uint8_t value);

/**
 * The function set the color of the pixel in the selected position.
 *
 * @param[in] dev The handle of the device
 * @param[in] xPosition The x position of the display
 * @param[in] yPosition The y position of the display
 * @param[in] grayscale The color of the pixel
 * @return An error if the value is greater than the maximum allowed,
 *         OLEDRAYSTAR_ERRORS_OK otherwise.
 */
OledRaystar_Errors OledRaystar_setPixel (OledRaystar_Device* dev,
                                         uint8_t xPosition,
                                         uint8_t yPosition,
                                         OledRaystar_GrayScale grayscale);

/**
 * The function print a char in the selected position with the selected
 * color.
 *
 * @param[in] dev The handle of the device
 * @param[in] c The char to be printed
 * @param[in] xPosition The x position of the display
 * @param[in] yPosition The y position of the display
 * @param[in] grayscale The color of the char
 */
void OledRaystar_putChar (OledRaystar_Device* dev,
                          uint8_t c,
                          uint8_t xPosition,
                          uint8_t yPosition,
                          OledRaystar_GrayScale grayscale);

/**
 * The function print a string in the selected position with the selected
 * color. The string must be terminated with '\0' or '\n'.
 *
 * @param[in] dev The handle of the device
 * @param[in] string The string to be printed
 * @param[in] xPosition The x position of the display
 * @param[in] yPosition The y position of the display
 * @param[in] grayscale The color of the char
 */
void OledRaystar_putString (OledRaystar_Device* dev,
                            uint8_t* string,
                            uint8_t xPosition,
                            uint8_t yPosition,
                            OledRaystar_GrayScale grayscale);

/**
 * The function draw a rectangle in the selected position with the selected
 * color. The dimensions of the rectangle are defined by the initial and final
 * position of x and y.
 *
 * @param[in] dev The handle of the device
 * @param[in] xPositionStart The x start position
 * @param[in] xPositionStop The x stop position
 * @param[in] yPositionStart The y start position
 * @param[in] yPositionStop The y stop position
 * @param[in] color The fill color of the rectangle
 * @return An error if the values are greater than the maximum allowed,
 *         OLEDRAYSTAR_ERRORS_OK otherwise.
 */
OledRaystar_Errors OledRaystar_drawRectangle (OledRaystar_Device* dev,
                                              uint8_t xPositionStart,
                                              uint8_t xPositionStop,
                                              uint8_t yPositionStart,
                                              uint8_t yPositionStop,
                                              OledRaystar_GrayScale color);
/**
 * The function draw the picture passed as argument. This function write directly into
 * the buffer, where every byte of the matrix is the pair of two segment. The dimension of the
 * matrix must be the same of the internal buffer: right now is 64x64.
 *
 * @param[in] dev The handle of the device
 * @param[in] xPosition The x start position
 * @param[in] yPosition The y start position
 * @param[in] xDimension The x dimension of the picture matrix
 * @param[in] yDimension The y dimension of the picture matrix
 * @param[in] picture The picture matrix pointer
 * @return An error if the values are greater than the maximum allowed,
 *         OLEDRAYSTAR_ERRORS_OK otherwise.
 */
OledRaystar_Errors OledRaystar_drawPicture (OledRaystar_Device* dev,
                                            uint8_t xPosition,
                                            uint8_t yPosition,
                                            uint8_t xDimension,
                                            uint8_t yDimension,
                                            uint8_t* picture);

/**
 * The function writes the buffer content to the display.
 *
 * @param[in] dev The handle of the device
 */
void OledRaystar_flush (OledRaystar_Device* dev);

#endif /* __LOCCIONI_OLEDRAYSTAR_H */
