/*һ����return false�����쳣���ļ�stack��ģ��ʵ�֣�
Ҫ�������쳣����ģ����ա�*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Stack{
public:
	bool push(const string &str);
	bool pop(string &elem);
	bool peak(string &elem);

	bool full();
	bool empty();
	int size(){ return _elems.size(); }
private:
	vector<string> _elems;

};
bool Stack::full(){
	return _elems.size() == _elems.max_size();
}
bool Stack::empty(){
	return _elems.empty();
}
bool Stack::push(const string&str){
	if (full()) return false;
	_elems.push_back(str);
	return true;
}
bool Stack::pop(string& str){
	if (empty()) return false;
	str = _elems.back();
	_elems.pop_back();
	return true;
}
bool Stack::peak(string& str){
	if (empty()) return false;
	str = _elems.back();
	return true;
}
