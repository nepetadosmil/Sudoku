#include <iostream>

#include "sudoku.h"

Sudoku::Sudoku(int sudoku[BOARD_SIZE][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			this->tablero[i][j] = sudoku[i][j];
}

Sudoku::~Sudoku()
{

}

void Sudoku::resolver()
{
	int x = -1, y = -1;

	//Busca las 'coordenadas' de las que la correspondiente llamada
	//a la funci�n se va a encargar
	for (int i = 0; i < BOARD_SIZE && x == -1; ++i)
		for (int j = 0; j < BOARD_SIZE && y == -1; ++j)
			if (this->tablero[i][j] == START_VALUE) {//Comprueba que est� vac�a la casilla (quitado de funci�n 'esValido')
				x = i;
				y = j;
			}
	//Si ya no quedan filas, se ha completado correctamente
	if (x == -1)
		return;

	//Prueba todos los numeros posibles hasta encontrar uno v�lido
	//Adem�s, todos los siguientes deben serlo tambi�n. De no ser as�,
	//prueba con el siguiente n�mero. Si no vale ninguna combinaci�n, vuelve a la llamada anterior
	for (int num = 1; num <= BOARD_SIZE; ++num) {
		if (this->esValido(x, y, num)) {
			this->tablero[x][y] = num;
			this->resolver();
			if (!this->quedanVacias())//Si todos los dem�s son v�lidos 'backtrack'.
				return;
		}

	}
	//Si no se ha encontrado ning�n n�mero v�lido, volver al valor por defecto
	//para que la llamada anterior vea que no se ha completado el tablero
	this->tablero[x][y] = -1;
}


bool Sudoku::quedanVacias()
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			if (this->tablero[i][j] == START_VALUE)
				return true;

	return false;
}

void Sudoku::mostrar()
{
	std::cout << "-------------------------------------------------------" << std::endl;
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			if (j == 0)
				std::cout << "|  ";
			std::cout << this->tablero[i][j];
			if ((j + 1) % 3 == 0)
				std::cout << "  |  ";
			else
				std::cout << "     ";
		}
		std::cout << std::endl;
		if ((i + 1) % 3 == 0)
			std::cout << "-------------------------------------------------------" << std::endl;
	}
	std::cout << std::endl;
}


bool Sudoku::esValido(int fila, int columna, int valor) {

	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (this->tablero[fila][i] == valor) return false;
		if (this->tablero[i][columna] == valor) return false;
	}

	int despFila = (fila / 3) * 3;
	int despColumna = (columna / 3) * 3;

	for (int i = despFila; i < despFila + 3; ++i)
		for (int j = despColumna; j < despColumna + 3; ++j)
			if (this->tablero[i][j] == valor) return false;

	return true;
}
