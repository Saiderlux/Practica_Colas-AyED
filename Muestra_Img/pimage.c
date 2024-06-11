#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "cambioconsol.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void displayImage(const char *filename) {
    int width, height, channels;
    unsigned char *image = stbi_load(filename, &width, &height, &channels, 0);
    if (image != NULL) {
        // Mostrar la imagen, por ejemplo, imprimir los primeros píxeles
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int pixel_index = (y * width + x) * channels;
                // Suponiendo una imagen RGB donde channels = 3
                printf("\033[48;2;%d;%d;%dm  ", image[pixel_index], image[pixel_index + 1], image[pixel_index + 2]);
            }
            printf("\n");
        }
        stbi_image_free(image);
    } else {
        printf("Error cargando la imagen %s\n", filename);
    }
}

int main() {
    const char *filename = "img.png";  // Reemplaza con tu archivo de imagen estática
    displayImage(filename);
    sleep(2);
    system("cls");
    return 0;
}