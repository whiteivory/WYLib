//����const���ж�
//operator�����
//���캯�������
//���⣬vector��û��ʵ��operator==
#include<iostream>
#include<vector>
using namespace std;
class Triangular_iterator{
public:
	Triangular_iterator(int index) :_index(index - 1){}

	Triangular_iterator& operator++();
	Triangular_iterator operator++(int);
	int operator*()const;                        //const��Ҫ��
	bool operator==(Triangular_iterator& rhs)const;   //����Ҫʵ�֣���Ϊ��Ҫ�жϣ�=end
	bool operator!=(Triangular_iterator& rhs)const;   //ע�ⷵ�����ͺ�ʵ�ַ�����

private:
	bool check_integrity() const;                //һ��ʼ���Ǽ�const��

	int _index;
};
class Triangular{
	friend class Triangular_iterator;            //�������public����private���涼����ν��
public:
	typedef Triangular_iterator iterator;//Ҫ�ŵ�public����
	Triangular(int len=1, int beg_pos=1);
	Triangular& operator=(const Triangular& rhs);

	static bool is_elem(int value);
	static int elem(int pos);                    //static�϶�����Ҫ��const����Ϊ�����в����õ�����
	static bool gen_elem(int length);
	static void display(int beg_pos, int length, ostream& os = cout);

	bool next(int& value)const;                  //ע����Ȼ��mutable����ҲҪ��const
	bool reset_next()const{ _next = 0; }
	int size()const{ return _elems.size(); }
	iterator begin();
	iterator end();
private:
	static vector<int> _elems;

	mutable int _next;
	int _beg_pos;
	int _length;
	// static const int   _max_elems = 1024;          //���д������
	static const int max;                             //Ӧ����ôд��Ȼ����class���涨�塣static��������Ҫ��class������ж��壬���������_elems[]
	enum{max_size=1024};

public:
	int beg_pos(){ return _beg_pos; }
	int length(){ return _length; }
};
vector<int> Triangular::_elems;
const int Triangular::max = 1024;
class iterator_overflow{};
bool Triangular_iterator::check_integrity()const{     //ʵ��ҲҪ����const���������������,����ֻ��Ҫ���б߽��⣬��Ҫ���������һЩ��Ϊ
	if (_index > Triangular::max_size)
		throw iterator_overflow();
	if (_index >= Triangular::_elems.size())
		Triangular::gen_elem(_index + 1);
}
Triangular_iterator& Triangular_iterator::operator++(){
	check_integrity();                                      //��Ȼ���Ϸŵ�_index++���棬��������Ϊ����Ӧ�÷ŵ�����
	_index++;
	return *this;
}
Triangular_iterator Triangular_iterator::operator++(int){
	Triangular_iterator tmp = Triangular_iterator(*this);            //����һ�����=�͸��ƺ�����Ĭ��Ӧ����һ����
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
	_length(len>0?len:1),_beg_pos(beg_pos>0?beg_pos:0){   //һ��Ҫ�����е��û�������м���
	_next = beg_pos;                                      //һ��Ҫ���ǵ����е�data
	int size = len + beg_pos;
	if (size > _elems.size())
		gen_elem(size);
}
Triangular&Triangular::
operator=(const Triangular &rhs)    //֮����Ҫ���������������Ϊ����_next��Ҫ��������
{									//����Ҫ�ر����ĸ���data
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
//��ʵ�֣���Ҫ����value���ɵ��Ǹ�ֵ
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