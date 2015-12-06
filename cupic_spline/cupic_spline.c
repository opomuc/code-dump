#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <malloc.h>
#include <time.h>

#define POINT_NUM 10

typedef struct {
		double a, b, c, d, x;
} spline_tuple;

typedef struct {
	// Структура, описывающая сплайн на каждом сегменте сетки	
	spline_tuple* splines; // Сплайн
	int n; // Количество узлов сетки

} Spline;

void free_mem(Spline* this); // Освобождение памяти
void construct_cubic_spline(Spline* This); //конструктор
void destruct_cubic_spline(Spline* this); //деструктор

	// Построение сплайна
	// x - узлы сетки, должны быть упорядочены по возрастанию, кратные узлы запрещены
	// y - значения функции в узлах сетки
	// n - количество узлов сетки
void build_spline(Spline* this, const double *x, const double *y, int n);

	// Вычисление значения интерполированной функции в произвольной точке
double get_spline(Spline* this, double x);

void construct_cubic_spline(Spline* this) {
  this->splines = NULL;
}

void destruct_cubic_spline(Spline* this)
{
	free_mem(this);
}

void free_mem(Spline* this)
{
	free(this->splines);
	this->splines = NULL;
}

void build_spline(Spline* this, const double *x, const double *y, int n)
{
	free_mem(this);

	this->n = n;

	// Инициализация массива сплайнов
	this->splines = calloc(n, sizeof(spline_tuple));
	for (int i = 0; i < n; ++i)
	{
		this->splines[i].x = x[i];
		this->splines[i].a = y[i];
	}
	this->splines[0].c = 0.;

	// Решение СЛАУ относительно коэффициентов сплайнов c[i] методом прогонки для трехдиагональных матриц
	// Вычисление прогоночных коэффициентов - прямой ход метода прогонки
	double *alpha = calloc(n - 1, sizeof(double));
	double *beta = calloc(n - 1, sizeof(double));
	double A, B, C, F, h_i, h_i1, z;
	alpha[0] = beta[0] = 0.;
	for (int i = 1; i < n - 1; ++i)
	{
		h_i = x[i] - x[i - 1], h_i1 = x[i + 1] - x[i];
		A = h_i;
		C = 2. * (h_i + h_i1);
		B = h_i1;
		F = 6. * ((y[i + 1] - y[i]) / h_i1 - (y[i] - y[i - 1]) / h_i);
		z = (A * alpha[i - 1] + C);
		alpha[i] = -B / z;
		beta[i] = (F - A * beta[i - 1]) / z;
	}

	this->splines[n - 2].c = (F - A * beta[n - 2]) / (C + A * alpha[n - 2]);

	// Нахождение решения - обратный ход метода прогонки
	for (int i = n - 2; i > 0; --i)
		this->splines[i].c = alpha[i] * this->splines[i + 1].c + beta[i];

	// Освобождение памяти, занимаемой прогоночными коэффициентами
	free(beta);
	free(alpha);

	// По известным коэффициентам c[i] находим значения b[i] и d[i]
	for (int i = n - 1; i > 0; --i)
	{
		double h_i = x[i] - x[i - 1];
		this->splines[i].d = (this->splines[i].c - this->splines[i - 1].c) / h_i;
		this->splines[i].b = h_i * (2. * this->splines[i].c + this->splines[i - 1].c) / 6. + (y[i] - y[i - 1]) / h_i;
	}
}

double get_spline(Spline* this, double x) {
	if (!this->splines)
		return 0; // Если сплайны ещё не построены - возвращаем NaN

	spline_tuple *s;
	if (x <= this->splines[0].x) // Если x меньше точки сетки x[0] - пользуемся первым эл-том массива
		s = this->splines + 1;
	else if (x >= this->splines[this->n - 1].x) // Если x больше точки сетки x[n - 1] - пользуемся последним эл-том массива
		s = this->splines + this->n - 1;
	else // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
	{
		int i = 0, j = this->n - 1;
		while (i + 1 < j)
		{
			int k = i + (j - i) / 2;
			if (x <= this->splines[k].x)
				j = k;
			else
				i = k;
		}
		s = this->splines + j;
	}

	double dx = (x - s->x);
	return s->a + (s->b + (s->c / 2. + s->d * dx / 6.) * dx) * dx; // Вычисляем значение сплайна в заданной точке.
}

int main() {

  Spline my_spline;
  construct_cubic_spline(&my_spline);
  
  srand(10);
  
  double x[POINT_NUM];
  double y[POINT_NUM];
  FILE* out = fopen("input.txt", "w");

  for(int i = 0; i < POINT_NUM; i++) {
    x[i] = i;
    y[i] = rand();
    fprintf(out, "%f %f\n", x[i], y[i]);
  }
  
  build_spline(&my_spline, x, y, POINT_NUM);

  for(double i = 0; i < POINT_NUM; ) {
    i += 0.1;
    fprintf(out, "%f\n", get_spline(&my_spline, i));
  }  
  for(double i = 0; i < POINT_NUM; ) {
    i += 0.1;
    fprintf(out, "%f\n", i);
  }
  
  destruct_cubic_spline(&my_spline);
  return 0;
}