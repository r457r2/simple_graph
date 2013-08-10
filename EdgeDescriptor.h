#ifndef EDGE_DESCRIPTOR_H
#define EDGE_DESCRIPTOR_H
//в этом классе реализованы все методы.
template <typename V, typename W, typename D>//vertex,weight,data
class EdgeDescriptor
{
    private:
		V* to;
		V* from;
		W weight;
		D data;

	public:
		EdgeDescriptor (V* _in, V* _out) : to(_in), from(_out){}
		EdgeDescriptor (V* _in, V* _out, W _weight) : to(_in), from(_out), weight(_weight){}
		EdgeDescriptor (V* _in, V* _out, W _weight, D _data) : to(_in), from(_out), weight(_weight), data(_data){}
		~EdgeDescriptor (){}

		V* getBegin (){return from;}
		void setBegin (V* _vertex){from = _vertex;}

		V* getEnd (){return to;}
		void setEnd (V* _vertex){to = _vertex;}

		W getWeight (){return weight;}
		void setWeight (W _weight){weight = _weight;}

		D getData (){return data;}
		void setData (D _data){data = _data;}

		bool isComingTo (V* _vertex){return ((to == _vertex)? true : false);}
		bool isComingFrom (V* _vertex){return ((from == _vertex)? true : false);}
};

#endif // EDGE_DESCRIPTOR_H
