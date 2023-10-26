#include <stdio.h>
#include "image.h"


int main(void)
{
    Image *teste = create(3, 4, "P3"), *teste_gray = create(3, 4, "P2");

    write_to_ppm(teste, "teste_rgb");
    
    char opcao = '?', opcao2 = '?', str[100];
    
    while(opcao != 's') {
        printf("O que deseja fazer?\n");
        
        printf("1. Carregar uma imagem (digite 1)\n");
        
        printf("2. Converter uma imagem colorida para niveis de cinza (digite 2)\n");
        
        printf("3. Gravar uma imagem (digite 3)\n");
        
        printf("EXIT - Sair do programa (digite s)\n");

        scanf("%c ", &opcao);
        
        if(opcao == '1') {
            printf("\n1.A. Carregar uma imagem do caminho padrao (digite A) \n");
            
            printf("1.B. Carregar uma imagem de outro lugar (digite B)\n");

            scanf("%c ", &opcao2);
            
            if((opcao2 == 'a') || (opcao2 == 'A')) {
                teste = load_from_ppm("teste_rgb");
            }

            if ((opcao2 == 'b') || (opcao2 == 'B')) {
                printf("1.B.1. Digite o local da imagem que voce deseja abir:\n");

                fgets(str, 100, stdin);

                teste = load_from_ppm(str);

                if(teste == NULL) {
                    printf("\nErro ao abrir a imagem!\n");
                }
            }   
            
        }

        if(opcao == '2') {
            if(teste == NULL) {
                printf("\nErro ao fazer a conversao!\n");

            }

            else {
                rgb_to_gray(teste, teste_gray);
            }
        }

        if(opcao == '3') {
             printf("\n3.A. Gravar uma imagem no caminho padrao (digite A) \n");
             
             printf("3.B. Gravar uma imagem em outro lugar (digite B)\n");
             
             scanf("%c ", &opcao2);

             if((opcao2 == 'a') || (opcao2 == 'A')) {
                write_to_ppm(teste, "saida");
            }

            if ((opcao2 == 'b') || (opcao2 == 'B')) {
                printf("1.B.1. Digite o local em que voce deseja gravar a imagem:\n");

                fgets(str, 100, stdin);

                teste = load_from_ppm(str);

                if(teste == NULL) {
                    printf("\nErro ao abrir a imagem!\n");
                }
            }

        }

        printf("......................................................................................................................");

    }
    
    
    
    
    

    

    return 0;
}