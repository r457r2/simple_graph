#ifndef TASK_ONE_H
#define TASK_ONE_H
#include <Graph.h>

//Интерфейс АТД «Задача 1» включает операции:
//Конструктор (g) - создает объект задачи 1, ассоциированный с графом  g, и выполняет решение задачи для графа g,
//Конструктор (T) - конструктор копирования создает копию объекта – задачи T,
//Деструктор () - уничтожает внутренние структуры объекта задачи,
//Set (g) – связывает объект задачи с графом g и выполняет решение задачи 1 для графа g,
//Restart ( ) – повторно выполняет решение задачи 1 для графа g,
//Result( ) –  возвращает результат решения задачи 1

//Варианты задачи 1:
//1)	формирование списка ребер неориентированного графа в порядке двухпроходного эйлерова цикла,

template <typename Vertex_t, typename Edge_t>
class TaskOne
{
private:
	Graph<Vertex_t,Edge_t>* pgraph;
	QVector<Edge_t*> edges;

	QVector<Edge_t*>& solve(){}

public:
	TaskOne(Graph<Vertex_t,Edge_t>* _pgraph) : pgraph(_pgraph)
	{
		this->solve();
	}

	TaskOne(TaskOne& other)
	{
		this->pgraph = other.pgraph;
	}

	~TaskOne(){}

	QVector<Edge_t*>& set(Graph<Vertex_t,Edge_t>* _pgraph)
	{
		this->pgraph = _pgraph;
		return (this->solve());
	}

	QVector<Edge_t*>& restart()
	{
		return (this->solve());
	}

	QVector<Edge_t*>& result()
	{
		return edges;//is it rigth?
	}
};

#endif // TASK_ONE_H
