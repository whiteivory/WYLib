#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;

vector<int> filter_less(vector<int> &v,int less_value){
	vector<int> rvec;
	for(int i = 0; i < v.size(); i++){
		if(v[i] < less_value)
			rvec.push_back(v[i]);
	}
	return rvec;
}
bool less_than(int a, int b){
	if(a<b) return true;
	return false;
}
vector<int> filter_less_ver2(vector<int>& v,int less_value, bool (*pfunc)(int,int)){
	vector<int> rvec;
	for(int i = 0; i < v.size(); i++){
		if(pfunc(v[i],less_value))
			rvec.push_back(v[i]);
	}
	return rvec;
}
vector<int> filter_less_ver3(vector<int>& v,int less_value, less<int>&lt){
	vector<int> rvec;
	for(int i = 0; i < v.size(); i++){
		if(lt(v[i],less_value))
			rvec.push_back(v[i]);
	}
	return rvec;
}
template<typename InputIterator, typename OutputIterator,
	typename ElemType, typename Comp>
OutputIterator filter( InputIterator first, InputIterator last, ElemType value, OutputIterator at, Comp& cp){
	for(InputIterator it = first; it != last; it++){
		if(cp(*it,value)){
			*at=*it;
			at++;
		}
	}
	return at;
}

template<typename InputIterator, typename OutputIterator,
	typename ElemType, typename Comp>
OutputIterator filter_v2( InputIterator first, InputIterator last, ElemType value, OutputIterator at, Comp& cp){
	while((first = find_if(first,last,bind2nd(cp,value))) != last) *at++=*first++;
	return at;
}

template<typename InputIterator, typename OutputIterator,
	typename ElemType, typename Comp>
OutputIterator filter_v3( InputIterator first, InputIterator last, ElemType value, OutputIterator at, Comp& cp){
	sort(first,last);
	InputIterator it = find_if(first,last,not1(bind2nd(cp,value)));
	at = copy(first,it,at);
	return at;
}
template<typename InputIterator, typename OutputIterator,
	typename ElemType, typename Comp>
OutputIterator filter2( InputIterator first, InputIterator last, const ElemType &value, OutputIterator at, Comp& cp){
	while((first =  
		find_if( first, last, 
			bind2nd(cp,value))) != last)
			*at++=*first++;
	return at;
}

int main(){
	int a[] = {4, 3, 12, 9, 17, 22};
	vector<int> v(a,a+6);
	vector<int> rv(6);
	vector<int>::iterator it = filter_v3(v.begin(),v.end(),10,rv.begin(),less<int>());
	for(vector<int>::iterator i=rv.begin();i<it;i++) cout<<*i<<' ';
	cout<<'\n';
	//第二种方式
		vector<int> ivec2;
	filter_v2(v.begin(),v.end(),10,back_inserter(ivec2),greater<int>() );

	//下面这样赋值不行怎么办
	vector<int> rv2;
	vector<int>::iterator it2 = filter_v2(v.begin(),v.end(),10,back_inserter(rv2),less<int>());
	for(vector<int>::iterator i2=rv2.begin();i2<it2;i2++) cout<<*i2<<' ';


	return 0;
}