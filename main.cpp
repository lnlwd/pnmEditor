/*
 * INF 110 - Trabalho prático 03
 * Date: Mon, May 30 2016
 */

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "def.h"

int main(int argc, char** argv)
{
	bool color;
	int width, height;
	std::string fname;

	unsigned char red[MAXH][MAXW], green[MAXH][MAXW], blue[MAXH][MAXW];

	if(argc != 2)
	{
		std::cout << "Nome do arquivo para abrir: ";
		std::cin >> fname;
	} else
	{
		fname = argv[1];
	}

	if(loadPNM(fname, width, height, color, red, green, blue) == false)
	{
		std::cout << "Erro ao carregar imagem." << std::endl;
		exit(-1);
	}

	/*
	 * Fim da parte chata.
	 * Início da parte divertida.
	 */

	std::cout << "Comandos disponíveis -" << std::endl;
	std::cout << "- (qi) Clarear ou escurecer imagem. " << std::endl;
	std::cout << "- (qc) Clarear ou escurer banda de cor. " << std::endl;
	std::cout << "- (ei) Espelhar imagem. " << std::endl;
	std::cout << "- (ec) Espelhar banda. " << std::endl;
	std::cout << "- (ni) Aplicar filtro negativo na imagem. " << std::endl;
	std::cout << "- (nc) Aplicar filtro negativo numa banda. " << std::endl;
	std::cout << "- (fa) Um filtro aí. " << std::endl;
	std::cout << "- (s2) Exportar o buffer atual como P2 (greyscale). " << std::endl;
	std::cout << "- (s3) Exportar o buffer atual como P3 (colorida). " << std::endl;
	std::cout << "- (Qq) Sair do programa. " << std::endl;
	std::cout << std::endl;

	std::string act;
	do
	{
		std::cout << "Comando) ";
		std::cin >> act;
		
		int b[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};

		if(act == "qi" || act == "qc")
		{
			int aux;
			std::cin >> aux;

			lighten(red, width, height, aux);

			if(act == "qi")
			{
				lighten(green, width, height, aux);
				lighten(blue, width, height, aux);
			}
		}

		else if(act == "ei" || act == "ec")
		{
			mirror(red, width, height);

			if(act == "qi")
			{
				mirror(green, width, height);
				mirror(blue, width, height);
			}
		}

		else if(act == "ni" || act == "nb")
		{
			negative(red, width, height);

			if(act == "ni")
			{
				negative(green, width, height);
				negative(blue, width, height);
			}
		}

		else if(act == "s2" || act == "s3")
		{
			std::string fout;

			std::cout << "Nome do arquivo: ";
			std::cin >> fout;

			if(act == "s2")
			{
				exportP2(red, width, height, fout);
			}
			else
			{
				exportP3(red, green, blue, width, height, fout);
			}

			std::cout << "✓" << std::endl;
		}

		else if(act == "fa")
		{
			filter(red, width, height, b);
			filter(green, width, height, b);
			filter(blue, width, height, b);
		}

	} while(act != "Qq");

	return 0;
}
