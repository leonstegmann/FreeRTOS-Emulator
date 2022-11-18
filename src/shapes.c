#include <stdio.h>
#include"stdlib.h"

#include"TUM_Draw.h"

#include"shapes.h"

circle_t *createCircle(coord_t initial_location, unsigned short radius,
                   unsigned int colour)
{
    circle_t *ret = calloc(1, sizeof(circle_t));

    if (!ret) {
        fprintf(stderr, "Creating ball failed\n");
        exit(EXIT_FAILURE);
    }

    ret->shape.location = initial_location;
    ret->shape.colour = colour;
    ret->shape.dx = 0;
    ret->shape.dy = 0;    
    ret->radius = radius;

    return ret;
}

square_t *createSquare(coord_t initial_location,  unsigned short initial_width,
                    unsigned short initial_height, unsigned int colour)
{
    square_t *ret = calloc(1, sizeof(square_t));

    if (!ret) {
        fprintf(stderr, "Creating ball failed\n");
        exit(EXIT_FAILURE);
    }

    ret->shape.location = initial_location;
    ret->shape.colour = colour;
    ret->shape.dx = 0;
    ret->shape.dy = 0;    
    ret->width = initial_width;
    ret->height = initial_height;

    return ret;
}

triangle_t *createTriangle(coord_t initial_location, coord_t* initial_corners,
                   unsigned int colour)
{
    triangle_t *ret = calloc(1, sizeof(triangle_t));

    if (!ret) {
        fprintf(stderr, "Creating ball failed\n");
        exit(EXIT_FAILURE);
    }

    ret->shape.location = initial_location;
    ret->shape.colour = colour;
    ret->shape.dx = 0;
    ret->shape.dy = 0;    
    ret->corners[0] = *initial_corners;
    ret->corners[1] = *(initial_corners+1);
    ret->corners[2] = *(initial_corners+2);

    return ret;
}

int drawCircle(circle_t *circle){
    tumDrawCircle( circle->shape.location.x, circle->shape.location.y,
                    circle->radius, circle->shape.colour);
    return 0;
}

int drawSquare(square_t *square){
    tumDrawFilledBox( square->shape.location.x - square->width/2,
                        square->shape.location.y - square->height/2,
                        square->width, square->height, square->shape.colour);
    return 0;
}

int drawTriangle(triangle_t *triangle){
    coord_t coordsCentered[3];
    for (int i=0; i<3; i++){
        coordsCentered[i].x = triangle->corners[i].x + triangle->shape.location.x ;
        coordsCentered[i].y = triangle->corners[i].y + triangle->shape.location.y ;
    }
    tumDrawTriangle(coordsCentered, triangle->shape.colour);
    return 0;
}

//void rotateShape