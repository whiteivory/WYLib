//两个const的判断
//operator的添加
//构造函数的添加
//问题，vector有没有实现operator==
#include<iostream>
#include<vector>
using namespace std;
class Triangular_iterator{
public:
	Triangular_iterator(int index) :_index(index - 1){}

	Triangular_iterator& operator++();
	Triangular_iterator operator++(int);
	int operator*()const;                        //const不要忘
	bool operator==(Triangular_iterator& rhs)const;   //必须要实现，因为需要判断！=end
	bool operator!=(Triangular_iterator& rhs)const;   //注意返回类型和实现方法。

private:
	bool check_integrity() const;                //一开始忘记加const了

	int _index;
};
class Triangular{
	friend class Triangular_iterator;            //这个放在public或者private里面都无所谓。
public:
	typedef Triangular_iterator iterator;//要放到public里面
	Triangular(int len=1, int beg_pos=1);
	Triangular& operator=(const Triangular& rhs);

	static bool is_elem(int value);
	static int elem(int pos);                    //static肯定不需要加const，因为不会有不会用到对象
	static bool gen_elem(int length);
	static void display(int beg_pos, int length, ostream& os = cout);

	bool next(int& value)const;                  //注意虽然是mutable变量也要加const
	bool reset_next()const{ _next = 0; }
	int size()const{ return _elems.size(); }
	iterator begin();
	iterator end();
private:
	static vector<int> _elems;

	mutable int _next;
	int _beg_pos;
	int _length;
	// static const int   _max_elems = 1024;          //这个写法不行
	static const int max;                             //应该这么写，然后在class外面定义。static变量都需要在class外面进行定义，包括上面的_elems[]
	enum{max_size=1024};

public:
	int beg_pos(){ return _beg_pos; }
	int length(){ return _length; }
};
vector<int> Triangular::_elems;
const int Triangular::max = 1024;
class iterator_overflow{};
bool Triangular_iterator::check_integrity()const{     //实现也要加上const，否则就是重载了,并不只需要进行边界检测，还要根据情况做一些行为
	if (_index > Triangular::max_size)
		throw iterator_overflow();
	if (_index >= Triangular::_elems.size())
		Triangular::gen_elem(_index + 1);
}
Triangular_iterator& Triangular_iterator::operator++(){
	check_integrity();                                      //虽然书上放到_index++下面，但是我认为这里应该放到上面
	_index++;
	return *this;
}
Triangular_iterator Triangular_iterator::operator++(int){
	Triangular_iterator tmp = Triangular_iterator(*this);            //测试一下这里，=和复制函数的默认应该是一样的
	check_integrity();
	_index++;
	return tmp;
}
bool Triangular_iterator::operator==(Triangular_iterator&rhs)const{
	return _index == rhs._index;
}
bool Triangular_iterator::operator!=(Triangular_iterator&rhs)const{
	return (!(*this == rhs));
}
int Triangular_iterator::operator*()const{
	return Triangular::_elems[_index];
}
ostream& operator<<(ostream&os , Triangular&rhs){
	os << '(' << rhs.beg_pos() << ',' << rhs.length() << ')';
	rhs.display(rhs.beg_pos(), rhs.length());
	return os;
}

Triangular::Triangular(int len, int beg_pos):
	_length(len>0?len:1),_beg_pos(beg_pos>0?beg_pos:0){   //一定要对所有的用户输入进行检验
	_next = beg_pos;                                      //一定要考虑到所有的data
	int size = len + beg_pos;
	if (size > _elems.size())
		gen_elem(size);
}
Triangular&Triangular::
operator=(const Triangular &rhs)    //之所以要重载这个符号是因为迭代_next需要进行重置
{									//所以要特别留心个别data
	if (this != &rhs) {
		_length = rhs._length;
		_beg_pos = rhs._beg_pos;
		_next = 0;
	}

	return *this;
};
bool Triangular::gen_elem(int length){
	if (length > max_size){
		cerr << "Triangular Sequence: Oops,invalid size: " << length <<
			"\nMax size is" << max_size << "\n";
		return false;
	}
	for (int i = _elems.size(); i < length; i++){
		_elems.push_back(i*(i - 1) / 2);
	}
	return true;
}
//待实现，需要根据value生成到那个值
bool Triangular::is_elem(int value){
	return true;
}
int Triangular::elem(int pos){
	if (pos > max_size) cerr << "invalid size\n";
	if (pos > _elems.size()){
		gen_elem(pos);
	}
	return _elems[pos - 1];
}
void Triangular::display(int beg, int length, ostream& os){
	if ((beg + length) > max_size){
		cerr << "Triangular Sequence: Oops,invalid size: " << beg+length <<
			"\nMax size is" << max_size << "\n";
	}
	for (int i = beg; i < beg + length; i++){
		os << _elems[i - 1];
	}
}
bool Triangular::next(int&val)const{
	if (_next > max_size) return false;
	val = _elems[_next++];
	return true;
}

Triangular::iterator Triangular::begin(){
	return Triangular::iterator(_beg_pos);
}
Triangular::iterator Triangular::end(){
	return Triangular::iterator(_beg_pos + _length);
}

void main(){
	Triangular t(10, 1);
	Triangular::iterator it = t.begin();
	Triangular::iterator it2 = t.end();
	for (; it != t.end(); it++){
		cout << *it << ' ';
	}
	cout << endl;
	//cout << t2;

}