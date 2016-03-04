//写的时候又忘记加const了
#include<iostream>
#include<vector>
using namespace std;

class num_sequence{
public:
	virtual ~num_sequence(){};                           //这里一定要加分好么
	virtual void gen_elem(int length)const = 0;              //注意这里的const，因为引用而并不是数组
	virtual ostream& print(ostream&os = cout)const=0;           //注意参数和返回值,ostream 不能设置为const        
	int elem(int pos)const;
    bool is_elem(int value)const;                        //之所以这里不能被声明称static是因为用了引用vector技巧的关系，并没有static member
	
	bool check_ingrety(int beg,int len)const;                         //如果实现了exception类就不用返回值了。

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
	vector<int>& _rvec;                                   //结合子类的构造函数体会关于static变量的应用技巧
public:                                                   //或者把这些变量声明称protected，作用是一样的。
	int beg_pos()const{ return _beg_pos; }
	int length()const{ return _length; }
	void beg_pos(int b){ _beg_pos = b; }
	void length(int l){ _length = l; }
};

/*
* 由于beg和length都可以set，所以有些地方不能只检查这两个成员，需要根据pos来检查和更改length
* 还有决定check是在构造函数和set函数里进行检查还是在所有需要引用位置的函数进行检查是程序员自己决定的，但是后者明显更好，更能适应变化
* 用两个参数可能有点啰嗦，但更实用
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
ostream& operator<<(ostream& os, num_sequence& ns){       //非member function
	ns.print();
	return os;
}
ostream& num_sequence::print(ostream& os)const{   //默认值在实现的地方一定不能写，是重复声明默认值
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
//未实现
bool num_sequence::is_elem(int value)const{
	return true;
}

class Fibonacci :public num_sequence{
public:
	Fibonacci(int beg_pos, int length) :num_sequence(beg_pos, length, _elems){}
	virtual ostream& print(ostream&os = cout)const;
	virtual void gen_elem(int length)const;
	 Fibonacci* clone()const;                //clone 返回的是new的，需要进行内存管理
private:
	static vector<int> _elems;
};
vector<int> Fibonacci::_elems;                   //外部定义
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
Fibonacci* Fibonacci::clone()const{                  //虽然基类里面有一个引用，但是引用的是公共内存static，不会随着类的delete而消失，所以不需要重载copy operator，直接复制过去引用就可以了
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

