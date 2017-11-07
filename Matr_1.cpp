/*
*С помощью ассемблерных  вставок  необходимо реализовать  функции:
*		создать матрицу;+
*		удалить матрицу;+
*		прочитать, изменить	элемент,  стоящий на пересечении i-той строки и j-го столбца;+
*		печать матрицы;+
*		посчитать количество столбцов, все элементы которых меньше по  модулю заданного числа;
Матрица представлена массивом строк.
*/

#include <stdio.h>
#include <iostream>

struct Matrix
{
	int	size;
	int** Mat;
};

void main()
{
	//int		S = 0;
	int		element = 0;
	int		argumentForColumns = 0; //число для поиска
	int		sizeOfMatrix = 0;
	char	badarg[] = "Bad argument!\n";
	char	again[] = "Do u wanna create new matrix? yes(1), no(any other)\n";
	char	creating[] = "creating(1.size 2.elements):\n";
	char	asknumber[] = "input number:\n";

	char	askIJ[] = "input elemnt [i][j] : \n";
	char	askIJandNew[] = "input elemnt [i][j] and new element: \n";
	char	resultOfFunction[] = "result is : \n";

	char	probel[] = " ";
	char	end[] = "\n";
	char	menu[] = "Menu:\n1.Print matrix\n2.Show (i,j)\n3.Edit (i,j)\n4.Delete matrix\n5. Function\n6.Exit\n";
	char	strform[] = "%s";
	char	intform[] = "%d";
	_asm {

	START:
		//просим размер и элементы матрицы
			lea		eax, creating
			push	eax
			call	dword ptr printf
			add		esp, 4

		CREATE:
		//читаем размерность
			lea		eax, sizeOfMatrix
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr scanf_s
			call	dword ptr _flushall
			add		esp, 8

			cmp		sizeOfMatrix, 0
			jle		BAD_ARG

			//выделяем память на структуру
			mov		eax, SIZE Matrix
			push	eax
			call	dword ptr malloc
			add		esp, 4
			cmp 	eax, 0
			je		NO_MEM
			mov		edi, eax

			//заполняем поле размерности
			mov		eax, sizeOfMatrix
			mov[edi], eax

			//выделяем память на массив указателей на строки
			shl		eax, 2
			push	eax
			call	dword ptr malloc
			add		esp, 4
			cmp		eax, 0
			je		NO_MEM

			//заполняем поле указателя
			mov[edi + 4], eax

			//выделяем память под строки
			xor		esi, esi
			mov		ebx, sizeOfMatrix
			shl		ebx, 2

			push	ebx

		CYCLE1 :
		call	dword ptr malloc
			mov		ecx, [edi + 4]
			mov[ecx][4 * esi], eax
			inc		esi
			cmp		esi, sizeOfMatrix
			jge		END1

			jmp		CYCLE1

		END1 :

		add		esp, 4
			xor esi, esi

			//заполнение	матрицы
		CYCLE2 :
		mov		ecx, [edi + 4]
			mov		ebx, [ecx][4 * esi]
			xor		edx, edx

		CYCLE3 :
		push	edx
			lea		eax, element
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr scanf_s
			call	dword ptr _flushall
			add		esp, 8
			pop		edx
			mov		eax, element
			mov[ebx][4 * edx], eax

			inc		edx
			cmp		edx, sizeOfMatrix
			jge		END3

			jmp		CYCLE3
		END3 :

		inc		esi
			cmp		esi, [edi]
			jge		END2

			jmp		CYCLE2
		END2 :

		xor		esi, esi

			jmp		MENU

		PRINT :
		//печать матрицы
		xor		esi, esi

		CYCLE4 :
		lea		eax, end
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		ecx, [edi + 4]
			mov		ebx, [ecx][4 * esi]
			xor edx, edx

		CYCLE5 :
		push	edx
			mov		eax, [ebx][edx * 4]
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr printf
			call	dword ptr _flushall
			add		esp, 8

			lea		edx, probel
			push	edx
			call	dword ptr printf
			add		esp, 4

			pop		edx

			inc		edx
			cmp		edx, [edi]
			jge		END5

			jmp		CYCLE5
		END5 :

		inc		esi
			cmp		esi, [edi]
			jge		END4

			jmp		CYCLE4

		END4 :
		jmp		MENU

		GET_I_J :
		//просим строчку
		lea		eax, askIJ
			push	eax
			call	dword ptr printf
			add		esp, 4

		lea		eax, sizeOfMatrix
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr scanf_s
			call	dword ptr _flushall
			add		esp, 8

			//просим столбец
			lea		eax, element
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr scanf_s
			call	dword ptr _flushall
			add		esp, 8

			lea		eax, resultOfFunction
			push	eax
			call	dword ptr printf
			add		esp, 4

			mov		ebx, sizeOfMatrix

			cmp		sizeOfMatrix, 0
			jle		BAD_ARG
			cmp		ebx, [edi]
			jg		BAD_ARG

			mov		edx, element

			cmp		element, 0
			jle		BAD_ARG
			cmp		edx, [edi]
			jg		BAD_ARG

			dec		ebx
			dec		edx

			mov		ecx, [edi + 4]

			

			mov		esi, [ecx][4 * ebx]
			mov		ecx, [esi][4 * edx]
			push	ecx
			lea		eax, intform
			push	eax
			call	dword ptr printf
			call	dword ptr _flushall
			add		esp, 8

			jmp		MENU

		CHANGE_I_J :
		//просим строчку
			lea		eax, askIJandNew
			push	eax
			call	dword ptr printf
			add		esp, 4

			lea		eax, sizeOfMatrix
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr scanf_s
			call	dword ptr _flushall
			add		esp, 8

			//просим столбец
			lea		eax, element
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr scanf_s
			call	dword ptr _flushall
			add		esp, 8


			//просим число новое
			lea		eax, argumentForColumns
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr scanf_s
			call	dword ptr _flushall
			add		esp, 8

			mov		ebx, sizeOfMatrix


			cmp		sizeOfMatrix, 0
			jle		BAD_ARG
			cmp		ebx, [edi]
			jg		BAD_ARG

			mov		edx, element

			cmp		element, 0
			jle		BAD_ARG
			cmp		edx, [edi]
			jg		BAD_ARG

			dec		ebx
			dec		edx

			

			mov		ecx, [edi + 4]
			mov		esi, [ecx][4 * ebx]
			lea		ecx, [esi + 4 * edx]
			mov		eax, argumentForColumns
			mov[ecx], eax

			jmp		MENU

		FUNCTION :
			lea		eax, asknumber
			push	eax
			lea		eax, strform
			push	eax
			call	dword ptr printf
			call	dword ptr _flushall
			add		esp, 8

			lea		eax, argumentForColumns
			push	eax
			lea		eax, intform
			push	eax
			call	dword ptr scanf_s
			call	dword ptr _flushall
			add		esp, 8

			lea		eax, resultOfFunction
			push	eax
			lea		eax, strform
			push	eax
			call	dword ptr printf
			call	dword ptr _flushall
			add		esp, 8

			xor		ecx, ecx
			xor		edx, edx
			mov		esi, [edi + 4]

		FCYCLE1:
				cmp		ecx, [edi]
				jge		END_FCYCLE1
				xor		eax, eax
				xor		ebx, ebx

			FCYCLE2 :
				cmp		ebx, [edi]
				jge		END_FCYCLE2
				mov		eax, [esi][4 * ebx]
				mov		eax, [eax][4 * ecx]
				cmp		eax, 0
				jge		POSITIVE
				not eax
				inc		eax

			POSITIVE :
				cmp		eax, argumentForColumns
				jge		END_FCYCLE2
				inc		ebx
				jmp		FCYCLE2

			END_FCYCLE2 :
				cmp		ebx, [edi]
				je		UP
				inc		ecx
				jmp		FCYCLE1

			UP :
				inc		edx
				inc		ecx
				jmp		FCYCLE1

			END_FCYCLE1 :


				push	edx
				lea		eax, intform
				push	eax			
				call	dword ptr printf
				add		esp, 8

				jmp		MENU

			DELETE_MATRIX :
				mov		esi, [edi + 4]
				xor edx, edx

			DELETE_MATRIX_CYCLE :
				mov		ebx, [esi][edx * 4]
				push	ebx
				call	dword ptr free
				add		esp, 4

				inc		edx
				cmp		edx, [edi]
				jge		END_OF_DELETE_MATRIX_CYCLE
				jmp		DELETE_MATRIX_CYCLE

			END_OF_DELETE_MATRIX_CYCLE :
				lea		eax, again
				push	eax
				call	dword ptr printf
				add		esp, 4

				lea		eax, argumentForColumns
				push	eax
				lea		eax, intform
				push	eax
				call	dword ptr scanf_s
				call	dword ptr _flushall
				add		esp, 8

				cmp		argumentForColumns, 1
				je		START
				jmp		END

			MENU :
				lea		eax, menu
				push	eax
				call	dword ptr printf
				call	dword ptr _flushall
				add		esp, 4

				lea		eax, end
				push	eax
				call	dword ptr printf
				call	dword ptr _flushall
				add		esp, 4

			CHTO_DELAT:
				lea		eax, element
				push	eax
				lea		eax, intform
				push	eax
				call	dword ptr scanf_s
				call	dword ptr _flushall
				add		esp, 8

				cmp		column, 6
				je		END
				cmp		column, 5
				je		FUNCTION
				cmp		column, 4
				je		DELETE_MATRIX
				cmp		column, 3
				je		CHANGE_I_J
				cmp		column, 2
				je		GET_I_J
				cmp		column, 1
				je		PRINT
				jmp		CHTO_DELAT

			BAD_ARG :
				lea		eax, badarg
				push	eax
				call	dword ptr printf
				add		esp, 4

			NO_MEM :

			   END :
	}
}











