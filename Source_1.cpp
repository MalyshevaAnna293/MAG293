//8.	Вычислить значение определенного интеграла функции на отрезке  [a,b],
// 		методом прямоугольников с шагом step. Чтобы вычислить значение функции, кроме
// 		многочленов, можно воспользоваться стандартной библиотекой.
// 		Решение оформить в виде функции
// 		double имя_метода(double a, double b, double (*pf)(double), double  step= 1e-2);
// 		В качестве примера, реализовать вычисление интеграла cos(x), x, exp(x).
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>

double cos_x(double x)
{
	__asm {
		finit		//высчитываем cos(x)
		fld		x
		fcos
	}
}

double usual_x(double x)
{
	__asm {
		finit		//кладём х в вершину стека
		fld		x
	}
}

double exponenta(double x)
{
	double one = 1.0;
	int z1 = 0;
	__asm {
		finit
		fld		x
		fabs			//модуль
		fldl2e			//кладём log2e в вершину стека
		fmul
		xor		ecx, ecx

		CYCLE :
		fcom	one		//сравниваем с 1
			fstsw	ax
			sahf
			jp		ERR		//вытаскивается флаг состояния в ax, сравнием число бит, если четное, ошибка
			jc		LESS	//если случается переполнение, то идем в LESS
			fsub	one		//-1
			inc		ecx
			jmp		CYCLE

			LESS :

		f2xm1					//Вычисление выражения y=2^(x)-1
			fadd	one
			mov		z1, ecx
			fild	z1				//Загрузка целочисленного операнда в вершину стека
			fld1					//Загрузка 1
			fscale					//Масштабирование по степеням 2
			fmul	st(0), st(2)

			//В вершине стека сопроцессора - 2 ^ (х*log2(e)) = exp(| х | )
			//	если х < 0, то exp(х) = 1 / exp(| х | )

			fldz			//0 в вершину
			fcomp	x		//Сравниваем с 0
			fstsw	ax		//Флаги состояния в ax
			sahf			//Смотрим флаги
			jc		END		//Если случается переполнение, то конец

			fld1					//в стек 1
			fdivrp	st(1), st(0)	//Деление с выталкиванием

			ERR:
	END:
	}
}

double Integral(double a, double b, double(*pf)(double), double  step = 1e-2)
{
	double half = 0.5;
	double res = 0;
	__asm {
		finit
		fldz
		fcomp	step		//Сравнение с шагом
		fstsw	ax
		sahf
		jnc		BAD_STEP


		fld		a			// a
		fld		step		// a | step
		fld		half		// a | step | half
		fmul				// a | step*half
		fadd
		fstp	a			//Сохранение вершины стека в память с выталкиванием

		CYCLE :

		fld		a			// a
			fld		b			// a | b
			fcomp	st(1)		//сравниваем с а
			fstsw	ax
			sahf
			jc		END
			fstp	qword ptr[esp]	//Сохранение вершины стека в ячейку памяти с выталкиванием
			call	dword ptr pf	//Передаем вызов функции 
			fld		step
			fmul
			fadd	res
			fstp	res
			fld		a
			fadd	step
			fstp	a
			jmp		CYCLE

			BAD_STEP :
	END:
	}
	return res;

}

void main()
{
	double step = 1e-2;
	double a = 0, b = 0, r1 = 0, r2 = 0, r3 = 0;
	char c1;
	do
	{
		system("cls");
		printf("\t\tMenu\n\t1.X_integral\n\t2.COS_integral\n\t3.EXP_integral\n\t4.Exit\n");
		c1 = _getch();
		switch (c1)
		{
		
		case '1':
			system("cls");
			printf("Enter a boundary\n");
			scanf_s("%lf %lf", &a, &b);
			r1 = Integral(a, b, usual_x, step);
			printf("integral(x) from %lf to %lf is equal %lf\nStep = %lf\n", a, b, r1, step);
			_getch();
			break;
		case '2':
			system("cls");
			printf("Enter a boundary\n");
			scanf_s("%lf %lf", &a, &b);
			r2 = Integral(a, b, cos_x, step);
			printf("integral(x) from %lf to %lf is equal %lf\nStep = %lf\n", a, b, r2, step);
			_getch();
			break;
		case '3':
			system("cls");
			printf("Enter a boundary\n");
			scanf_s("%lf %lf", &a, &b);
			r3 = Integral(a, b, exponenta, step);
			printf("integral(x) from %lf to %lf is equal %lf\nStep = %lf\n", a, b, r3, step);
			_getch();
			break;
		}
	} while (c1 != '4');
}
