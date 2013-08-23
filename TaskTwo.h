#ifndef TASKTWO_H
#define TASKTWO_H
#include <Graph.h>

//Интерфейс АТД «Задача 2» включает операции:
//Конструктор (g) - создает объект задачи 2, ассоциированный с графом  g, и выполняет решение задачи для графа g,
//Конструктор (T) - конструктор копирования создает копию объекта – задачи T,
//Деструктор () - уничтожает внутренние структуры объекта задачи,
//Set (g) – связывает объект задачи с графом g и выполняет решение задачи 2 для графа g,
//Restart ( ) – повторно выполняет решение задачи 2 для графа g,
//Result( ) –  возвращает результат решения задачи 2

//Варианты алгоритмов:
//1)	определение списка вершин, которые лежат в пределах заданного расстояния d от заданной вершины
//взвешенного орграфа с отрицательной весовой функции на основе алгоритма Беллмана-Форда,

template <typename Vertex_t, typename Edge_t>
class TaskTwo
{
private:
	Graph<Vertex_t,Edge_t>* pgraph;
	QVector<Vertex_t*> vertexes;

public:
	TaskTwo(Graph<Vertex_t,Edge_t>* _pgraph)
	{
		this->set(_pgraph);
	}

	TaskTwo(TaskTwo& other)
	{
		this->pgraph = other.pgraph;
	}

	~TaskTwo(){}

	QVector<Vertex_t*>& set(Graph<Vertex_t,Edge_t>* other) {}

	QVector<Vertex_t*>& restart() {}

	QVector<Vertex_t*>& result() {}
};

#endif // TASKTWO_H
