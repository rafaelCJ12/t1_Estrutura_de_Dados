#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct image_ppm {
    char tipo[3];
    
    unsigned int linhas, colunas;
    
    unsigned char *matriz;
};

Image* create(int rows, int cols, char type[]) {
    int i;
    
    Image *ppm = (Image *) (malloc(sizeof(Image)));
        
    unsigned char *ptr;
    
    if((strcmp(type, "P3") == 0) || (strcmp(type, "P2") == 0)) {
        srand((unsigned)time(NULL));
        
        if(strcmp(type, "P3") == 0) {
            ptr =  (unsigned char *) malloc(rows * cols * 3 * sizeof(unsigned char));
            
            for(i = 0; i < rows * cols * 3; i++) {
                ptr[i] = (unsigned int) rand() % 256;
            }
            
            strcpy(ppm -> tipo, "P3");
            
        }
        
        if(strcmp(type, "P2") == 0) {
            ptr = (unsigned char *) malloc(rows * cols * sizeof(unsigned char));
            
            for(i = 0; i < rows * cols; i++) {
                ptr[i] = (unsigned int) (rand() % 255) + (rand() % 2);
            }
            
            strcpy(ppm -> tipo, "P2");
        }
        
        ppm -> linhas = rows;
        
        ppm -> colunas = cols;
        
        ppm -> matriz = ptr;
        
        return ppm;
    }
    
    return NULL;
    
}

Image* load_from_ppm(const char* filename) {
    Image *image;
    
    FILE *file = fopen(filename, "r");
    
    char tipo_i[3], caracter, *Linhas, *token, *stop, *linha;
    
    const char separador[2] = " ";
    
    int i = 0, j = 0, k;
    
    unsigned int lin, col;
    
    unsigned char *elementos;
    
    if(file == NULL) {
        fprintf(stderr, "Erro na leitura do arquivo: %s\n", filename);
        return NULL;
    }
    
    fgets(tipo_i, 3, file);
    
    while(caracter != '\n') {
        caracter = fgetc(file);
        
    }
    
    while(caracter != '#') {
        caracter = fgetc(file);
        
        i++;
        
    }
    
    fclose(file);
    
    linha = (char *) malloc(i * sizeof(char));
    
    file = fopen(filename, "r");
    
    while(caracter != '\n') {
        caracter = fgetc(file);
    }
    
    fgets(linha, i, file);
    
    token = strtok(linha, " ");
    
    col = (unsigned int) strtoul(token, &stop, 10);
    
    token = strtok(NULL, separador);
    
    lin = (unsigned int) strtoul(token, &stop, 10);
    
    free(linha);
    
    fclose(file);
    
    file = fopen(filename, "r");
    
    i = 0;
    
    if(strcmp(tipo_i, "P3") == 0) {

        elementos = (unsigned char *) malloc(lin * col * 3 * sizeof(unsigned char));
        
        while(i < 3) {
            caracter = fgetc(file);
            
            if(caracter == '\n') {
                i++;
            }
            
        }
            
        Linhas = (char *) malloc(14 * col * lin * sizeof(char));
        
        i = 0;
                
        while(i < lin) {
            fgets(Linhas, (14 * lin * col), file);
            
            for(k = 0; k < strlen(Linhas); k++) {
                if(Linhas[k] == '\n') {
                    Linhas[k] = ' ';
                    i++;
                    
                }
            }
            
            token = strtok(Linhas, " ");
            
            while(token != NULL) {
                elementos[j] = (unsigned char) strtoul(token, &stop, 10);
                
                token = strtok(NULL, separador);
                
                j++;
            }
        
        }
    }
    
    if(strcmp(tipo_i, "P2") == 0) {
        elementos = (unsigned char *) malloc(lin * col * sizeof(unsigned char));
        
        while(i < 3) {
            caracter = fgetc(file);
            
            if(caracter == '\n') {
                i++;
            }
            
        }
            
        Linhas = (char *) malloc(4 * col * lin * sizeof(char));
        
        i = 0;
                
        while(i < lin) {
            fgets(Linhas, (4 * lin * col), file);
            
            for(k = 0; k < strlen(Linhas); k++) {
                if(Linhas[k] == '\n') {
                    Linhas[k] = ' ';
                    i++;
                    
                }
            }
            
            token = strtok(Linhas, " ");
            
            while(token != NULL) {
                elementos[j] = (unsigned char) strtoul(token, &stop, 10);
                
                token = strtok(NULL, separador);
                
                j++;
            }
        
        }
        
    }

    free(Linhas);
    
    fclose(file);
    
    if(((strcmp(tipo_i, "P3") == 0) || (strcmp(tipo_i, "P2") == 0)) && (lin != 0) && (col != 0)) {
        image = (Image *) (malloc(sizeof(Image)));
        
        strcpy(image -> tipo, tipo_i);
        
        image -> linhas = lin;
        
        image -> colunas = col;
        
        image -> matriz = elementos;
        
        return image;
        
    }

    return NULL;
    
}

void write_to_ppm(Image* image, const char* filename) {
    int i, j, k, l;
    
    unsigned char *ptr = image -> matriz;
    
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "Erro na abertura do arquivo para escrita: %s\n", filename);
        return;
    }
    
    if((strcmp(image -> tipo, "P3") == 0) || (strcmp(image -> tipo, "P2") == 0)) {
        // Write the PPM header
        fprintf(file, "%s # Tipo\n", image -> tipo);
        fprintf(file, "%i %i # Dimensões (largura x altura)\n", image -> colunas, image -> linhas);
        fprintf(file, "255 # Valor máximo do pixel\n");
        
        if(strcmp(image -> tipo, "P3") == 0) {
            for(i = 0; i < image-> linhas; i++) {
                for(j = 0; j < image -> colunas; j++) {
                    for(k = 0; k < 1; k++) {
                        for(l = 0; l < 3; l++) {
                            fprintf(file, "%i ", *(ptr));
                            ptr++;
                        }
                    }
                    fprintf(file, "  ");
                }
                fprintf(file, "\n");
                
            }
        }
        
        if(strcmp(image -> tipo, "P2") == 0) {
            for(i = 0; i < image -> linhas; i++) {
                for(j = 0; j < image -> colunas; j++) {
                    fprintf(file, "%i ", *(ptr));
                    ptr++;
                }
                fprintf(file, "\n");
            }
        }
    
    }
    
    fclose(file);
}

void rgb_to_gray(Image* image_rgb, Image* image_gray) {
    int i, j, k, l;
    
    unsigned char *ptr0, ****ptr, **ptr2;;
    
    if(strcmp(image_rgb -> tipo, "P3") == 0) {
        ptr = (unsigned char ****) malloc(image_rgb -> linhas * sizeof(unsigned char ***));
        
        ptr0 = image_rgb -> matriz;
        
        for(i = 0; i < image_rgb -> linhas; i++) {
            ptr[i] = (unsigned char ***) malloc(image_rgb -> colunas * sizeof(unsigned char **));
            
            for(j = 0; j < image_rgb -> colunas; j++) {
                ptr[i][j] = (unsigned char **) malloc(sizeof(unsigned char *));
                
                for(k = 0; k < 1; k++) {
                    ptr[i][j][k] = (unsigned char *) malloc(3 * sizeof(unsigned char));
                    
                    for(l = 0; l < 3; l++) {
                        ptr[i][j][k][l] = (unsigned char) *(ptr0);
                        
                        ptr0++;
                    }
                }
            }
            
        }
    }
    
    if((strcmp(image_gray -> tipo, "P2") == 0) && (image_gray -> linhas == image_rgb -> linhas) && (image_gray -> colunas == image_rgb -> colunas)) {
        ptr2 = (unsigned char **) malloc(image_gray -> linhas * sizeof(unsigned char *));
        
        ptr0 = image_gray -> matriz;
        
        for(i = 0; i < image_gray -> linhas; i++) {
            ptr2[i] = (unsigned char *) malloc(image_gray -> colunas * sizeof(unsigned char));
            
            for(j = 0; j < image_gray -> colunas; j++) {
                ptr2[i][j] = (unsigned char) (0.299 * ptr[i][j][0][0]) + (0.587 * ptr[i][j][0][1]) + (0.114 * ptr[i][j][0][2]);
                
                *ptr0 = (unsigned char) ptr2[i][j];
                
                ptr0++;
            }
        }
        
        for (i = 0; i < image_gray -> linhas; i++) {
            free(ptr2[i]);
            
        }
        
        free(ptr2);
    }
    
    for(i = 0; i < image_rgb -> linhas; i++) {
        for(j = 0; j < image_rgb -> colunas; j++) {
            for(k = 0; k < 1; k++) {
                free(ptr[i][j][k]);
            }
            
            free(ptr[i][j]);
            
        }
        free(ptr[i]);
        
    }
    
    free(ptr);
    
}