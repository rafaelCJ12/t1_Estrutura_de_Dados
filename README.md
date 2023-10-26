# t1_Estrutura_de_Dados
A execução do programa deve ser feita pelo programa que contém a função main, cujo nome também é main. Esse programa é o responsável por testar as funções que manipulam os arquivos txt que podem representar tanto imagens coloridas quanto em nível de cinza. O uso dessas funções é feito através da importação da biblioteca image.h, cujo as funções são: 

1. Image* create(int rows, int cols, char type[]);

Essa função é responsável por criar uma estrutura que representa uma imagem colorida quanto em nível de cinza, recebendo como parâmetros: o número de linhas, o número de colunas e o tipo que pode ser P2 (nível de cinza) ou P3 (colorida). Os valores gerados são aleatórios, variando de 0 até 255, inclusive.

2. Image* load_from_ppm(const char* filename);

Transforma uma imagem representada em um arquivo texto em uma estrutura que representa essa imagem, retornando o ponteiro para essa estrutura. Essa função recebe o nome do arquivo texto.

3. void write_to_ppm(Image* image, const char* filename);

Escreve em arquivo texto uma imagem, recebendo a estrutura que contém as informações da imagem e o arquivo que a receberá.

4. void rgb_to_gray(Image* image_rgb, Image* image_gray); 

Transforma uma imagem colorida em uma imagem em nível de cinza. Recebendo a imagem colorida a ser alterada e uma imagem em nível de cinza que receberá essa conversão. Se for passado uma imagem que não é do tipo P2 para image_gray, ou se image_gray tiver o número de linhas ou de colunas diferente de image_rgb, ela permanecerá inalterada.
