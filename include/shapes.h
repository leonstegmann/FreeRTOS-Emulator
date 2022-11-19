#ifndef __SHAPES_H__  
#define __SHAPES_H__

#include"stdio.h"
#include"TUM_Draw.h"

typedef struct shape {

    coord_t pixelLocation;  /**< Pixel coord on screen */
    coord_t location; /**< Absolute location */
    float dx; /**< X axis speed in pixels/second */
    float dy; /**< Y axis speed in pixels/second */
    unsigned int colour; /**< Hex RGB colour */

} shape_t;


typedef struct circle {

    shape_t shape; /**< Inheriting properties from struct shape*/
    unsigned short radius; /**< Radius in pixels */
 
} circle_t;


typedef struct triangle {

    shape_t shape; /**< Inheriting properties from struct shape*/
    coord_t corners[3];

} triangle_t;


typedef struct square {

    shape_t shape; /**< Inheriting properties from struct shape*/
    unsigned short width; /**< Width of square */
    unsigned short height; /**< Height of square */
    
} square_t;

circle_t* createCircle(coord_t , unsigned short ,unsigned int );

square_t* createSquare(coord_t ,  unsigned short , unsigned short , unsigned int );

triangle_t* createTriangle(coord_t , coord_t* , unsigned int );

int drawCircle(circle_t* );

int drawSquare(square_t* );

int drawTriangle(triangle_t* );

void moveShape(shape_t* , unsigned int );

void setSpeed(shape_t* , float ,float );

#endif //__SHAPES_H__