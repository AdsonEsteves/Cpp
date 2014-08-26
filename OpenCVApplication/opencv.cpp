#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>


using namespace cv;

Mat escala_cinza(Mat imagem, bool mostrar);
void negativa(Mat imagem);
void limiarizacao(Mat imagem, int limiar);
void somar(Mat imagem1, Mat imagem2);
void subtrair(Mat imagem1, Mat imagem2);
void mostrarImagem(char* janela, Mat imagem);

int main(int argc, char** argv)
{
	/*char* nome_imagem = "casa.jpg";
	char* nome_imagem2 = "soma.jpg";*/

	char* nome_imagem = "janela2.png";
	char* nome_imagem2 = "janela1.png";

	int limiar = 100;

	Mat imagem = imread(nome_imagem);
	Mat imagem2 = imread(nome_imagem2);
	escala_cinza(imagem, true);
	negativa(imagem);
	limiarizacao(imagem, limiar);
	somar(imagem, imagem2);
	subtrair(imagem, imagem2);

	waitKey(0);
}

void somar(Mat imagem1, Mat imagem2)
{
	Mat imagemResultado;
	if (imagem1.size().area() > imagem2.size().area())
		imagem1.copyTo(imagemResultado);
	else
		imagem2.copyTo(imagemResultado);

	for (int i = 0; i < imagemResultado.rows - 1; i++)
		for (int j = 0; j < imagemResultado.cols - 1; j++)
		{
		if (imagem2.rows > i && imagem2.cols > j)
		{
			imagemResultado.at<Vec3b>(i, j)[0] = (imagem1.at<Vec3b>(i, j)[0] + imagem2.at<Vec3b>(i, j)[0]) / 2;
			imagemResultado.at<Vec3b>(i, j)[1] = (imagem1.at<Vec3b>(i, j)[1] + imagem2.at<Vec3b>(i, j)[1]) / 2;
			imagemResultado.at<Vec3b>(i, j)[2] = (imagem1.at<Vec3b>(i, j)[2] + imagem2.at<Vec3b>(i, j)[2]) / 2;
		}
		else
		{
			imagemResultado.at<Vec3b>(i, j)[0] = (imagem1.at<Vec3b>(i, j)[0]);
			imagemResultado.at<Vec3b>(i, j)[1] = (imagem1.at<Vec3b>(i, j)[1]);
			imagemResultado.at<Vec3b>(i, j)[2] = (imagem1.at<Vec3b>(i, j)[2]);
		}
		}

	mostrarImagem("soma", imagemResultado);
}

void subtrair(Mat imagem1, Mat imagem2)
{
	Mat imagemResultado;
	if (imagem1.size().area() > imagem2.size().area())
		imagem1.copyTo(imagemResultado);
	else
		imagem2.copyTo(imagemResultado);

	for (int i = 0; i < imagemResultado.rows - 1; i++)
		for (int j = 0; j < imagemResultado.cols - 1; j++)
		{
		if (imagem2.rows > i && imagem2.cols > j)
		{
			imagemResultado.at<Vec3b>(i, j)[0] = (imagem1.at<Vec3b>(i, j)[0] - imagem2.at<Vec3b>(i, j)[0]);
			imagemResultado.at<Vec3b>(i, j)[1] = (imagem1.at<Vec3b>(i, j)[1] - imagem2.at<Vec3b>(i, j)[1]);
			imagemResultado.at<Vec3b>(i, j)[2] = (imagem1.at<Vec3b>(i, j)[2] - imagem2.at<Vec3b>(i, j)[2]);

			int diferencaR = imagemResultado.at<Vec3b>(i, j)[0] - imagem1.at<Vec3b>(i, j)[0];
			int diferencaG = imagemResultado.at<Vec3b>(i, j)[1] - imagem1.at<Vec3b>(i, j)[1];
			int diferencaB = imagemResultado.at<Vec3b>(i, j)[2] - imagem1.at<Vec3b>(i, j)[2];

			if (
				(!(imagemResultado.at<Vec3b>(i, j)[0] == 0 &&
				imagemResultado.at<Vec3b>(i, j)[1] == 0 &&
				imagemResultado.at<Vec3b>(i, j)[2] == 0))
				)
			{
				imagemResultado.at<Vec3b>(i, j)[0] = (imagem1.at<Vec3b>(i, j)[0]);
				imagemResultado.at<Vec3b>(i, j)[1] = (imagem1.at<Vec3b>(i, j)[1]);
				imagemResultado.at<Vec3b>(i, j)[2] = (imagem1.at<Vec3b>(i, j)[2]);
			}
		}
		else
		{
			imagemResultado.at<Vec3b>(i, j)[0] = (imagem1.at<Vec3b>(i, j)[0]);
			imagemResultado.at<Vec3b>(i, j)[1] = (imagem1.at<Vec3b>(i, j)[1]);
			imagemResultado.at<Vec3b>(i, j)[2] = (imagem1.at<Vec3b>(i, j)[2]);
		}
		}


	mostrarImagem("subtrair", imagemResultado);
}
void negativa(Mat imagem)
{
	Mat negativa;
	imagem.copyTo(negativa);

	for (int i = 0; i < negativa.rows - 1; i++)
		for (int j = 0; j < negativa.cols - 1; j++)
		{
		negativa.at<Vec3b>(i, j)[0] = 255 - negativa.at<Vec3b>(i, j)[0];
		negativa.at<Vec3b>(i, j)[1] = 255 - negativa.at<Vec3b>(i, j)[1];
		negativa.at<Vec3b>(i, j)[2] = 255 - negativa.at<Vec3b>(i, j)[2];
		}


	mostrarImagem("Negativa", negativa);
}

void limiarizacao(Mat imagem, int limiar)
{
	Mat imagem_limiar;
	Mat imagem_cinza = escala_cinza(imagem, false);

	imagem_cinza.copyTo(imagem_limiar);

	for (int i = 0; i < imagem_cinza.rows - 1; i++)
		for (int j = 0; j < imagem_cinza.cols - 1; j++)
		{
		if (imagem_limiar.at<Vec3b>(i, j)[0] > limiar)
		{
			imagem_limiar.at<Vec3b>(i, j)[0] = 255;
			imagem_limiar.at<Vec3b>(i, j)[1] = 255;
			imagem_limiar.at<Vec3b>(i, j)[2] = 255;
		}
		else
		{
			imagem_limiar.at<Vec3b>(i, j)[0] = 0;
			imagem_limiar.at<Vec3b>(i, j)[1] = 0;
			imagem_limiar.at<Vec3b>(i, j)[2] = 0;
		}



		}

	mostrarImagem("Limiarizacao", imagem_limiar);
}

Mat escala_cinza(Mat imagem, bool mostrar)
{
	Mat escala_cinza;
	imagem.copyTo(escala_cinza);

	for (int i = 0; i < escala_cinza.rows - 1; i++)
		for (int j = 0; j < escala_cinza.cols - 1; j++)
		{
		int r = escala_cinza.at<Vec3b>(i, j)[0];
		int g = escala_cinza.at<Vec3b>(i, j)[1];
		int b = escala_cinza.at<Vec3b>(i, j)[2];
		int tom_cinza = (r * 0.299) + (g * 0.587) + (b * 0.114);

		escala_cinza.at<Vec3b>(i, j)[0] = tom_cinza;
		escala_cinza.at<Vec3b>(i, j)[1] = tom_cinza;
		escala_cinza.at<Vec3b>(i, j)[2] = tom_cinza;

		}

	if (mostrar)
		mostrarImagem("Escala Cinza", escala_cinza);

	return escala_cinza;
}

void mostrarImagem(char* janela, Mat imagem)
{
	namedWindow(janela);
	imshow(janela, imagem);
}

#ifdef _EiC
main(1, "drawing.c");
#endif