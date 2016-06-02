/*
 * INF 110 - Trabalho prático 03
 * Author: Lenilson Nascimento, Raphael Carmo
 */

#ifndef _DEF_H_
#define _DEF_H_

#include <string>

/*
 * Limita um valor A entre B e C, ou seja, B <= A <= C.
 */
#define CLAMP(A,B,C) (A <= B ? B : A >= C ? C : A)

#define MAXW 1024
#define MAXH 1024

/*
 * Define as matrizes dos filtros: focus(Realçar), gaussianBlur(Desfoque Gaussiano)
 * sobel, e laplace.
 */

namespace Filters
{
	extern int Focus[3][3];

	extern int Box[3][3];
	extern int Gaussian[3][3];

	extern int Laplace[3][3];

	extern int SobelY[3][3];
	extern int SobelX[3][3];
}

/*
 * Abre o arquivo @filename para leitura e carrega seus pixels nos vetores
 * @red, @green e @blue. A largura e altura serão guardadas, respectivamente,
 * nas variáveis @width e @height, e @color será true se a imagem for
 * colorida.
 *
 * Retorna true em caso de sucesso.
 */
bool loadPNM(
	const std::string &filename,

	int &width,
	int &height,

	bool &color,

	unsigned char red[MAXH][MAXW],
	unsigned char green[MAXH][MAXW],
	unsigned char blue[MAXH][MAXW]
);

/*
 * Escurece (@mod < 0) ou clareia (@mod > 0) um arranjo de cores.
 */
void lighten(
	unsigned char pixels[MAXH][MAXW],
	int width, int height, int mod
);

/*
 * Espelha um arranjo de cores.
 */
void mirror(
	unsigned char pixels[MAXH][MAXW],
	int width, int height
);

/*
 * Inverte as cores de cada pixel em uma banda de cor.
 */
void negative(
	unsigned char pixels[MAXH][MAXW],
	int width, int height
);

/*
 * Aplica o filtro de sobel em @pixels.
 * @in e @out devem ser diferentes.
 */
void sobel(
	unsigned char in[MAXH][MAXW],
	unsigned char out[MAXH][MAXW],
	int width, int height
);

/*
 * Aplica um filtro @f 3*3 na matriz @in e guarda o resultado da operação
 * na matriz @out. 
 */
void filter(
	unsigned char in[MAXH][MAXW], unsigned char out[MAXH][MAXW],
	int width, int height, int f[3][3], float normalization = 1.0f
);

/*
 * Exporta uma banda de cores como uma imagem preto-e-branco.
 */
void exportP2(
	unsigned char pixels[MAXH][MAXW],
	int width, int height, const std::string &fo
);

/*
 * Exporta as bandas @red @green e @blue como uma imagem colorida.
 */
void exportP3(
	unsigned char red[MAXH][MAXW],
	unsigned char green[MAXH][MAXW],
	unsigned char blue[MAXH][MAXW],
	int width, int height, const std::string &fo
);

#endif