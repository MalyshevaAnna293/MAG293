#include "stdio.h"
#include <iostream>

int main()
{// Найти в строке символы с минимальным и максимальным кодом.
	const int N = 1000;
	char s[N];
	int min = 0;
	int max = 0;
	char format[] = "max = %c, min = %c\n";
	char con[] = "Please, enter your string ";
	char emptyStringMassage[] = "Empty string \n";
	
	

	__asm
	{
	
		lea		edx, con    //вывод строку меню
		push	edx
		call	dword ptr printf
		add		esp, 4

		
		mov		edx, N //кладем размер строки в стек 
		push edx
		lea		edx, s
		push	edx
		call	 gets_s // вызываем ввод строки
		add		esp, 8

		lea		ebx, s; //индекс массива
		mov		dl, [ebx];  
		mov		dh, dl;  
		cmp		dl, 0;	
		jne		search;

		lea		edx, emptyStringMassage  //вывод строку меню
			push	edx
			call	dword ptr printf
			add		esp, 4
		jmp END;

		search :
		; //ищем мин и макс
			mov		al, [ebx];  //счетчик символов
			inc		ebx
			cmp		al, 0; //проверка на ноль
			je		print; //выход из цикла
			cmp		al, dl
			jb		setmin

			retmin :
		cmp		dh, al
			jb		setmax //сравниваем если 1оп < 2оп то переход к setmax

			retmax :
		loop	search

			setmin :
		mov		dl, al
			jmp		retmin

			setmax :
		mov		dh, al
			jmp		retmax

			print :
		xor		eax, eax
			mov		al, dl //выводим min, max элементы
			push	eax
			mov		al, dh
			push	eax
			lea		eax, format
			push	eax
			call	dword ptr printf
			add		esp, 12
		END:

	}

	system("pause");
}