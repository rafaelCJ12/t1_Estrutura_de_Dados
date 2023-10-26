#ifndef IMAGE_H
#define IMAGE_H

typedef struct image_ppm Image;

Image* create(int rows, int cols, char type[]);

Image* load_from_ppm(const char* filename);

void write_to_ppm(Image* image, const char* filename);

void rgb_to_gray(Image* image_rgb, Image* image_gray);

#endif






