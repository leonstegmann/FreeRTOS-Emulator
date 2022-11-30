/*include Guards to ensure  initialising Header files only once*/
#ifndef __SHAPES_H__  
#define __SHAPES_H__

/* Library includes */
#include"stdio.h"
#include"stdlib.h"
#include"math.h"

/* TUM_Library includes  */
#include"TUM_Draw.h"

/* Project includes  */
#include"defines.h"

/**
 * @brief Properties that every shape has -> inheritance
 * @param starting_position starting location
 * @param location location of theshape
 * @param pixelLocation rounded location for the display in pixels
 * @param dx horizontal speed
 * @param dy vertical speed
 * @param colour shape colour
 */
typedef struct shape shape_t;

/// Object structures
typedef struct circle circle_t;
typedef struct triangle triangle_t;
typedef struct square square_t;

struct shape {
    coord_t starting_position;
    coord_t location; /**< Absolute location */
    coord_t pixelLocation;  /**< Pixel coord on screen */
    unsigned int colour; /**< Hex RGB colour */
    float dx; /**< X axis speed in pixels/second */
    float dy; /**< Y axis speed in pixels/second */
};

struct circle {
    shape_t shape; /**< Inheriting properties from struct shape*/
    unsigned short radius; /**< Radius in pixels */
};

struct triangle {
    shape_t shape; /**< Inheriting properties from struct shape*/
    coord_t corners[3]; /**< Coordinates of the 3 corners of a triangle */
};

struct square {
    shape_t shape; /**< Inheriting properties from struct shape*/
    unsigned short width; /**< Width of square */
    unsigned short height; /**< Height of square */
};

/// Instantiates and initalizes the objects
circle_t* createCircle(coord_t , unsigned short ,unsigned int );
square_t* createSquare(coord_t ,  unsigned short , unsigned short , unsigned int );
triangle_t* createTriangle(coord_t , coord_t* , unsigned int );

/// Draws the objects to the GUI using the TUM_Draw library
int drawCircle(circle_t* );
int drawSquare(square_t* );
int drawTriangle(triangle_t* );

/**
 * @brief updates the position due to its velocity and the time passed since last refresh
 * @param shape pointer to a Objects with a "shape_t" 
 * @param milli_seconds as "unsigned int"
 */
void moveShape(shape_t* , unsigned int );

/**
 * @brief sets the speed of the object
 * @param shape pointer to a Objects with a "shape_t" 
 * @param dx horizontal speed
 * @param dy vertical speed
 */
void setSpeed(shape_t* , float ,float );

/**
 * @brief upsates the position due to an given offset
 * @param shape pointer to a Objects with a "shape_t" 
 * @param offset {x,y} offset as "coord_t"
 */
void updateLocation(shape_t*, coord_t);


#endif //__SHAPES_H__