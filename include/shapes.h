#ifndef __SHAPES_H__  
#define __SHAPES_H__

#include"TUM_Draw.h"

typedef struct circle {

    unsigned short radius; /**< Radius of the ball in pixels */

    coord_t location; /**< Absolute location of circle */

    float dx; /**< X axis speed in pixels/second */
    float dy; /**< Y axis speed in pixels/second */

    unsigned int colour; /**< Hex RGB colour of the ball */

} circle_t;

typedef struct triangle {

    coord_t corners[3];

    coord_t location; /**< Absolute location of circle */


    float dx; /**< X axis speed in pixels/second */
    float dy; /**< Y axis speed in pixels/second */

    unsigned int colour; /**< Hex RGB colour of the ball */

} triangle_t;

typedef struct square {

    unsigned short width; /**< Width of square */
    unsigned short height; /**< Height of square */
    
    coord_t location; /**< Absolute location of circle */

    float dx; /**< X axis speed in pixels/second */
    float dy; /**< Y axis speed in pixels/second */

    unsigned int colour; /**< Hex RGB colour of the ball */

} square_t;

circle_t* createCircle(coord_t , unsigned short ,unsigned int );

square_t* createSquare(coord_t ,  unsigned short , unsigned short , unsigned int );

triangle_t* createTriangle(coord_t , coord_t* , unsigned int );

int drawCircle(circle_t* );

int drawSquare(square_t* );

int drawTriangle(triangle_t* );

#endif //__SHAPES_H__