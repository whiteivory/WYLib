#define STARTTIME 2037
#include<iostream>
#include<vector>
#include<string>

using namespace std;

typedef vector<unsigned int>* pvec;
typedef vector<unsigned int>* (*pfunc)(int);

extern pfunc gen_elems[];
extern char* name_seqs[];
extern char* wrong_msgs[];
extern int level[];

enum num_sequence{
	ns_unk,
	ns_fib, ns_pell, ns_lucas, ns_tri, ns_sq, ns_pent,
	ns_cnt = 6, ns_wrong_message
};

struct user_profile
{
	string name;
	int guess;
	int correct;
	int level;

	pvec cur_sql_vec;
	num_sequence cur_seq;
	int pos;
};

extern bool greet_user(user_profile* up);
extern void play_game(user_profile* up);
extern void display_statistics(user_profile*);

extern pvec fibonacci_gen_elems(int);
extern pvec pell_gen_elems(int);
extern pvec lucas_gen_elems(int);
extern pvec triangle_gen_elems(int);
extern pvec square_gen_elems(int);
extern pvec pentagonal_gen_elems(int);

extern void init_user(user_profile* user, string& name, int level);
extern void reset_seq(user_profile*);
extern bool correct_guess(user_profile*, unsigned int anser);

inline num_sequence gen_seq(unsigned int ui){
	srand(ui++);
	return static_cast<num_sequence>((rand() % ns_cnt) + 1);
}

inline void set_seq_vec(user_profile* up, pvec pv){
	up->cur_sql_vec = pv;
}
inline pvec seq_vec(user_profile* up){
	return up->cur_sql_vec;
}
inline string username(user_profile* up){ return up->name; }
inline void set_seq(user_profile*up, num_sequence ns){ up->cur_seq = ns; }
inline num_sequence seq(user_profile* up){ return up->cur_seq; }
inline void bump_correct(user_profile*up){ up->correct++;}
inline void bump_guess(user_profile*up){
	up->guess++;
}

inline bool check_intergrity(int pos){
	const int max_pos = 512;
	if (pos<0 || pos>max_pos){
		cerr << "!!invalid pos :" << pos << " can not honor request\n";
		return false;
	}
	return true;
}
inline num_sequence check_sequence(int id){
	if (id <= 0 || id > ns_cnt) {
		cerr << "!!Invalid sequence value: " << id << " Chosing one at radoom\n";
		id = (id%ns_cnt) + 1;
	}
	return static_cast<num_sequence>(id);
}