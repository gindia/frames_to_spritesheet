#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

typedef unsigned char u8;

int
main(int argc, char **argv)
{
    if (argc <= 1) {
        printf("did not pass any args.\n");
        return 0;
    }

    for (int i = 0 ; i < argc ; i++) {
        printf("-- %s\n", argv[i]);
    }

    int number_of_images = argc - 1;

    u8 **raw_images = malloc(number_of_images);
    int *w= malloc(sizeof(int)*(number_of_images));
    int *h= malloc(sizeof(int)*(number_of_images));
    int *c= malloc(sizeof(int)*(number_of_images));

    u8 *out_raw;
    int out_w = 0;
    int out_h = 0;
    int out_c = 0;

    for (int i = 0 ; i < number_of_images ; i++) {
        raw_images[i] = stbi_load(argv[i+1], &w[i], &h[i], &c[i], 0);
        if (!raw_images[i]) {
            printf("failed to open file %s\n", argv[i+1]);
            return 1;
        }

        out_w += w[i];
    }
    out_h  = h[0];
    out_c  = c[0];

    out_raw = malloc(out_w * out_h * out_c);

    size_t offset = 0;
    for (int line = 1 ; line <= out_h ; line++) {
        for (int i = 0 ; i < number_of_images ; i++) {
            memcpy(out_raw + offset, raw_images[i] + ((line - 1)*w[i]*c[i]), w[i]*c[i]);
            offset += (w[i] * c[i]);
        }
    }

    if (offset != (out_w * out_h * out_c)) {
       printf("offset != (out_w * out_h * out_c)\n");
       return 1;
    }

    return (stbi_write_png("out.png", out_w, out_h, out_c, out_raw, 0) != 1);
}
