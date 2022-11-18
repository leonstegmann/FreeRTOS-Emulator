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

    ret->location = initial_location;
    ret->colour = colour;
    ret->radius = radius;
    ret->dx = 0;
    ret->dy = 0;    

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

    ret->location = initial_location;
    ret->colour = colour;
    ret->width = initial_width;
    ret->height = initial_height;
    ret->dx = 0;
    ret->dy = 0;    

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

    ret->location = initial_location;
    ret->corners[0] = *initial_corners;
    ret->corners[1] = *(initial_corners+1);
    ret->corners[2] = *(initial_corners+2);
    ret->colour = colour;
    ret->dx = 0;
    ret->dy = 0;    

    return ret;
}

int drawCircle(circle_t *circle){
    tumDrawCircle( circle->location.x, circle->location.y, circle->radius, circle->colour);
    return 0;
}

int drawSquare(square_t *square){
    tumDrawFilledBox( square->location.x - square->width/2 ,square->location.y - square->height/2, square->width, square->height, square->colour);
    return 0;
}

int drawTriangle(triangle_t *triangle){
    coord_t coordsCentered[3];
    for (int i=0; i<3; i++){
        coordsCentered[i].x = triangle->corners[i].x + SCREEN_WIDTH / 2  ;
        coordsCentered[i].y = triangle->corners[i].y + SCREEN_HEIGHT / 2 ;
    }
    tumDrawTriangle(coordsCentered, triangle->colour);
    return 0;
}
