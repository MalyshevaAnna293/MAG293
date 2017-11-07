#include "stdio.h"
#include <iostream>

int main()
{// ����� � ������ ������� � ����������� � ������������ �����.
	const int N = 1000;
	char s[N];
	int min = 0;
	int max = 0;
	char format[] = "max = %c, min = %c\n";
	char con[] = "Please, enter your string ";
	char emptyStringMassage[] = "Empty string \n";
	
	

	__asm
	{
	
		lea		edx, con    //����� ������ ����
		push	edx
		call	dword ptr printf
		add		esp, 4

		
		mov		edx, N //������ ������ ������ � ���� 
		push edx
		lea		edx, s
		push	edx
		call	 gets_s // �������� ���� ������
		add		esp, 8

		lea		ebx, s; //������ �������
		mov		dl, [ebx];  
		mov		dh, dl;  
		cmp		dl, 0;	
		jne		search;

		lea		edx, emptyStringMassage  //����� ������ ����
			push	edx
			call	dword ptr printf
			add		esp, 4
		jmp END;

		search :
		; //���� ��� � ����
			mov		al, [ebx];  //������� ��������
			inc		ebx
			cmp		al, 0; //�������� �� ����
			je		print; //����� �� �����
			cmp		al, dl
			jb		setmin

			retmin :
		cmp		dh, al
			jb		setmax //���������� ���� 1�� < 2�� �� ������� � setmax

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
			mov		al, dl //������� min, max ��������
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