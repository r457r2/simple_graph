#ifndef EDGE_DESCRIPTOR_H
#define EDGE_DESCRIPTOR_H
//в этом классе реализованы все методы.
template <typename Vertex_t, typename Weight_t, typename Data_t>
class EdgeDescriptor
{
private:	
	Vertex_t* from;
	Vertex_t* to;
	Weight_t weight;
	Data_t data;

public:
	EdgeDescriptor (Vertex_t* _from, Vertex_t* _to) : from(_from), to(_to){}

	EdgeDescriptor (Vertex_t* _from, Vertex_t* _to, Weight_t _weight) :
		from(_from), to(_to), weight(_weight){}

	EdgeDescriptor (Vertex_t* _from, Vertex_t* _to, Weight_t _weight, Data_t _data) :
		from(_from), to(_to), weight(_weight), data(_data){}

	~EdgeDescriptor (){}

	Vertex_t* getBegin (){return from;}
	void setBegin (Vertex_t* _pvertex){from = _pvertex;}

	Vertex_t* getEnd (){return to;}
	void setEnd (Vertex_t* _pvertex){to = _pvertex;}

	Weight_t getWeight (){return weight;}
	void setWeight (Weight_t _weight){weight = _weight;}

	Data_t getData (){return data;}
	void setData (Data_t _data){data = _data;}

	bool isComingTo (Vertex_t* _pvertex){return ((to == _pvertex)? true : false);}
	bool isComingFrom (Vertex_t* _pvertex){return ((from == _pvertex)? true : false);}

	Vertex_t* other (Vertex_t* pvertex)
	{
		if (pvertex == this->getBegin())
			return getEnd();

		return NULL;
	}

};

#endif // EDGE_DESCRIPTOR_H
