//д��ʱ�������Ǽ�const��
#include<iostream>
#include<vector>
using namespace std;

class num_sequence{
public:
	virtual ~num_sequence(){};                           //����һ��Ҫ�ӷֺ�ô
	virtual void gen_elem(int length)const = 0;              //ע�������const����Ϊ���ö�����������
	virtual ostream& print(ostream&os = cout)const=0;           //ע������ͷ���ֵ,ostream ��������Ϊconst        
	int elem(int pos)const;
    bool is_elem(int value)const;                        //֮�������ﲻ�ܱ�������static����Ϊ��������vector���ɵĹ�ϵ����û��static member
	
	bool check_ingrety(int beg,int len)const;                         //���ʵ����exception��Ͳ��÷���ֵ�ˡ�

	typedef vector<int>::iterator iterator;
	iterator begin()const{ return _rvec.begin(); }
	iterator end()const { return _rvec.end(); }

	virtual num_sequence* clone()const=0;
protected:
	num_sequence(int beg_pos, int length,vector<int>& v) :_beg_pos(beg_pos), _length(length),_rvec(v){}
	enum{ max_size = 1024 };
private:
	int _beg_pos;
	int _length;
	vector<int>& _rvec;                                   //�������Ĺ��캯��������static������Ӧ�ü���
public:                                                   //���߰���Щ����������protected��������һ���ġ�
	int beg_pos()const{ return _beg_pos; }
	int length()const{ return _length; }
	void beg_pos(int b){ _beg_pos = b; }
	void length(int l){ _length = l; }
};

/*
* ����beg��length������set��������Щ�ط�����ֻ�����������Ա����Ҫ����pos�����͸���length
* ���о���check���ڹ��캯����set��������м�黹����������Ҫ����λ�õĺ������м���ǳ���Ա�Լ������ģ����Ǻ������Ը��ã�������Ӧ�仯
* ���������������еㆪ�£�����ʵ��
*/
bool num_sequence::check_ingrety(int beg, int len)const{           
	int pos = beg + len;
	if (pos <= 0 || pos > max_size){
		cerr << "invalid pos!" << endl;
		return false;
	}
	if (pos > _rvec.size()){
		gen_elem(pos);
	}
	return true;
}
ostream& operator<<(ostream& os, num_sequence& ns){       //��member function
	ns.print();
	return os;
}
ostream& num_sequence::print(ostream& os)const{   //Ĭ��ֵ��ʵ�ֵĵط�һ������д�����ظ�����Ĭ��ֵ
	if (check_ingrety(_beg_pos, _length)){
		os << "(" << _beg_pos << "," << _length << "): ";
		for (int i = _beg_pos; i < (_beg_pos + _length - 1); i++){
			os << _rvec[i];
		}
		os << endl;
	}
	return os;
}
int num_sequence::elem(int pos)const{
	if (!check_ingrety(_beg_pos, pos)) return 0;
	return _rvec[_beg_pos + pos - 1];
}
//δʵ��
bool num_sequence::is_elem(int value)const{
	return true;
}

class Fibonacci :public num_sequence{
public:
	Fibonacci(int beg_pos, int length) :num_sequence(beg_pos, length, _elems){}
	virtual ostream& print(ostream&os = cout)const;
	virtual void gen_elem(int length)const;
	 Fibonacci* clone()const;                //clone ���ص���new�ģ���Ҫ�����ڴ����
private:
	static vector<int> _elems;
};
vector<int> Fibonacci::_elems;                   //�ⲿ����
void Fibonacci::gen_elem(int length)const{
	if (_elems.empty()){
		_elems.push_back(1);
		_elems.push_back(1);
	}
	int n_1 = _elems[_elems.size() - 2];
	int n_2 = _elems[_elems.size() - 1];
	for (int i = _elems.size(); i < length; i++){
		int n = n_1 + n_2;
		_elems.push_back(n);
		n_1 = n_2;
		n_2 = n;
	}
}
ostream& Fibonacci::print(ostream&os)const{
	if (check_ingrety(beg_pos(), length())){
		os << "(" << beg_pos() << "," << length() << "): ";
		for (int i = beg_pos(); i < (beg_pos() + length() - 1); i++){
			os << _elems[i];
		}
		os << endl;
	}
	return os;
}
Fibonacci* Fibonacci::clone()const{                  //��Ȼ����������һ�����ã��������õ��ǹ����ڴ�static�������������delete����ʧ�����Բ���Ҫ����copy operator��ֱ�Ӹ��ƹ�ȥ���þͿ�����
	return new Fibonacci(*this);
}

void main(){
	Fibonacci *cf;
	while (1){
		Fibonacci f(1, 10);
		cf = f.clone();
		break;
	}
	cout << *cf;
}

