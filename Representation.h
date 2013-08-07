#ifndef REPRESENTATION_H
#define REPRESENTATION_H
//нет реализаций итераторов.
template <typename V, typename E>//vertex,edge
class Representation
{
	protected:
		V** vectorOfVertex;
		int lenthOfVector;
		bool oriented;

    public:
		Representation (){}
		Representation (int numberOfVertex, bool _oriented){}
		Representation (int numberOfVertex, int numberOfEge, bool _oriented){}
		Representation (Representation &one){}
		virtual ~Representation () {delete []vectorOfVertex;}

		virtual int numberOfVertex () = 0;
		virtual int numberOfEdge () = 0;
		virtual bool isDirected () = 0;
		virtual float getSaturationCoefficent () = 0;//коэффицент насыщенности
		virtual bool insertVertex () = 0;
		virtual bool deleteVertex (V _vertex1) = 0;
		virtual bool insertEdge (V _vertex1, V _vertex2) = 0;
		virtual bool deleteEdge (V _vertex1, V _vertex2) = 0;

	class GraphsVertexIterator
	{
		private:
			bool isSet;
			V* master;

		public:
			GraphsVertexIterator (){}

			GraphsVertexIterator* begin (){}
			GraphsVertexIterator* end (){}
			bool operator++ (){}
			V* operator* (){}
	};

//	class GraphsEdgeIterator
//	{
//		private:
//			bool isSet;
//			E* master;

//		public:
//			GraphsEdgeIterator (){}

//			GraphsEdgeIterator* begin (){}
//			GraphsEdgeIterator* end (){}
//			bool operator++ (){}
//			E* operator* (){}
//	};

//	class VertexsComingEdgeIterator
//	{
//		private:
//			bool isSet;
//			V* masterVertex;
//			E* master;

//		public:
//			VertexsComingEdgeIterator (V* _masterVertex){}

//			VertexsComingEdgeIterator* begin (){}
//			VertexsComingEdgeIterator* end (){}
//			bool operator++ (){}
//			E* operator* (){}
//	};

//	class VertexsIncomingEdgeIterator
//	{
//		private:
//			bool isSet;
//			V* masterVertex;
//			E* master;

//		public:
//			VertexsIncomingEdgeIterator (V* _masterVertex){}

//			VertexsIncomingEdgeIterator* begin (){}
//			VertexsIncomingEdgeIterator* end (){}
//			bool operator++ (){}
//			E* operator* (){}
//	};
};

#endif // REPRESENTATION_H
