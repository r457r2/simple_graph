#ifndef REPRESENTATION_H
#define REPRESENTATION_H
//нет реализаций итераторов.
template <typename Vertex_t, typename Edge_t>
class Representation
{
	protected:
        Vertex_t** vectorOfVertex;
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
        virtual bool deleteVertex (Vertex_t _vertex1) = 0;
        virtual bool insertEdge (Vertex_t _vertex1, Vertex_t _vertex2) = 0;
        virtual bool deleteEdge (Vertex_t _vertex1, Vertex_t _vertex2) = 0;

	class GraphsVertexIterator
	{
		private:
			bool isSet;
            Vertex_t* master;

		public:
			GraphsVertexIterator (){}

			GraphsVertexIterator* begin (){}
			GraphsVertexIterator* end (){}
			bool operator++ (){}
            Vertex_t* operator* (){}
	};

//	class GraphsEdgeIterator
//	{
//		private:
//			bool isSet;
//			Edge_t* master;

//		public:
//			GraphsEdgeIterator (){}

//			GraphsEdgeIterator* begin (){}
//			GraphsEdgeIterator* end (){}
//			bool operator++ (){}
//			Edge_t* operator* (){}
//	};

//	class VertexsComingEdgeIterator
//	{
//		private:
//			bool isSet;
//			Vertex_t* masterVertex;
//			Edge_t* master;

//		public:
//			VertexsComingEdgeIterator (Vertex_t* _masterVertex){}

//			VertexsComingEdgeIterator* begin (){}
//			VertexsComingEdgeIterator* end (){}
//			bool operator++ (){}
//			Edge_t* operator* (){}
//	};

//	class VertexsIncomingEdgeIterator
//	{
//		private:
//			bool isSet;
//			Vertex_t* masterVertex;
//			Edge_t* master;

//		public:
//			VertexsIncomingEdgeIterator (Vertex_t* _masterVertex){}

//			VertexsIncomingEdgeIterator* begin (){}
//			VertexsIncomingEdgeIterator* end (){}
//			bool operator++ (){}
//			Edge_t* operator* (){}
//	};
};

#endif // REPRESENTATION_H
