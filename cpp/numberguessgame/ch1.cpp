#include"ch1.h"

pvec fibonacci_gen_elems(int pos){
	static vector<unsigned int> _elems;
	if (!check_intergrity(pos)) return 0;//×¢Òâ·µ»ØÖµ
	if (_elems.empty()){
		_elems.push_back(1);
		_elems.push_back(1);
	}
	if (_elems.size() < pos){
		int ix = _elems.size();
		int n1 = _elems[ix - 1];
		int n2 = _elems[ix - 2];
		int elem;
		for (; ix < pos; ix++){
			elem = n1 + n2;
			_elems.push_back(elem);
			n2 = n1;
			n1 = elem;
		}

	}
	return &_elems;
}


pvec pell_gen_elems(int pos)
{
	static vector< unsigned int> _elems;

	if (!check_intergrity(pos))
		return 0;

	if (_elems.empty())
	{
		_elems.push_back(1); _elems.push_back(2);
	}

	if (_elems.size() < pos)
	{
		int ix = _elems.size();
		int n_2 = _elems[ix - 2],
			n_1 = _elems[ix - 1];

		int elem;
		for (; ix < pos; ++ix){
			elem = n_2 + 2 * n_1;
			_elems.push_back(elem);
			n_2 = n_1; n_1 = elem;
		}
	}

	return &_elems;
}

pvec lucas_gen_elems(int pos)
{
	static vector<unsigned int> _elems;

	if (!check_intergrity(pos))
		return 0;

	if (_elems.empty())
	{
		_elems.push_back(1); _elems.push_back(3);
	}

	if (_elems.size() < pos)
	{
		int ix = _elems.size();
		int n_2 = _elems[ix - 2],
			n_1 = _elems[ix - 1];

		int elem;
		for (; ix < pos; ++ix){
			elem = n_2 + n_1;
			_elems.push_back(elem);
			n_2 = n_1; n_1 = elem;
		}
	}

	return &_elems;
}

pvec triangle_gen_elems(int pos)
{
	static vector<unsigned int> _elems;

	if (!check_intergrity(pos))
		return 0;

	if (_elems.size() < pos)
	{
		int ix = _elems.size() ? _elems.size() + 1 : 1;
		for (; ix <= pos; ++ix)
			_elems.push_back(ix*(ix + 1) / 2);
	}

	return &_elems;
}

pvec square_gen_elems(int pos)
{
	static vector<unsigned int> _elems;

	if (!check_intergrity(pos))
		return 0;

	if (_elems.size() < pos)
	{
		int ix = _elems.size() ? _elems.size() + 1 : 1;
		for (; ix <= pos; ++ix)
			_elems.push_back(ix*ix);
	}

	return &_elems;
}

pvec pentagonal_gen_elems(int pos)
{
	static vector<unsigned int> _elems;

	if (!check_intergrity(pos))
		return 0;

	if (_elems.size() < pos)
	{
		int ix = _elems.size() ? _elems.size() + 1 : 1;
		for (; ix <= pos; ++ix)
			_elems.push_back(ix*(3 * ix - 1) / 2);
	}

	return &_elems;
}

pfunc gen_elems[] = {
	0,
	fibonacci_gen_elems,
	pell_gen_elems,
	lucas_gen_elems,
	triangle_gen_elems,
	square_gen_elems,
	pentagonal_gen_elems
};
char* name_seqs[] = {
	"Invalid Sequence",
	"Fibonacci", "Pell", "Lucas",
	"Triangular", "Square", "Pentagonal"
};
char* wrong_msgs[] = {
	"Oops! Nice guess but not quite it.",
	"Hmm. Sorry. Wrong again.",
	"Ah, this is harder than it looks, isn't it?",
	"It must be getting pretty frustrating by now!"
};
int level[] = { 8, 16, 32, 128, 512 };

void display_statistics(user_profile* up){
	cout << "Statics for user : " << up->name
		<< "\nCorrect ;" << up->correct
		<< "\nGuess : " << up->guess
		<< "\n %Correct : " << static_cast<float>(up->correct) / (up->guess);
}

bool greet_user(user_profile* up){
	string nm;
	cout << "Hello, what's your name:";
	cin >> nm;
	if (nm.empty() || nm[0] == ' '){
		cout << "Ok, it seems you dont want to play\n";
		return false;
	}
	cout << "\n\n" << "Hey, that's great, " << nm << ".\n"
		<< "We'll start in just a moment.\nIt\'s simple, really!\n"
		<< "I will print out two elements of a sequence\n"
		<< "You just answer with the element value that comes next!\n\n";

	cout << "Oh, by the way, do you consider yourself a\n\t"
		<< "beginner     -- enter 1\n\t"
		<< "intermediate -- enter 2\n\t"
		<< "advanced     -- enter 3\n\t"
		<< "guru         -- enter 4\n\t" << endl;
	int level;
	cin >> level;

	if (level < 1 || level>4) level = 4;
	init_user(up, nm, level);
	return true;
}

void init_user(user_profile* up, string& name, int level){
	up->name = name;
	up->level = level;
	up->guess = 0;
	up->correct = 0;

	reset_seq(up);
}
void setup_index(user_profile* up){
	up->pos = rand() % level[up->level];
	if (up->pos < 3) up->pos = up->pos + 3;

	set_seq_vec(up, gen_elems[(up->cur_seq)](up->pos));
}
void reset_seq(user_profile* up){
	int new_id = gen_seq(reinterpret_cast<unsigned int>(up));
	if (new_id == up->cur_seq){
		new_id = new_id < ns_cnt ? new_id+1 : 1;
	}
	up->cur_seq = static_cast<num_sequence>(new_id);
	setup_index(up);
}
bool correct_guess(user_profile* up, unsigned int guess){
	pvec v = seq_vec(up);
	if (guess == (*v)[up->pos - 1]) return true;
	return false;
}

void display_seq(user_profile* up){
	cout << "the first two elements of the seq are :" << (*up->cur_sql_vec)[up->pos - 3] << " and "
		<< (*up->cur_sql_vec)[up->pos - 2] << "\nWhat is the next num?\n";
}

void play_game(user_profile* up){
	bool next_seq = true;
	bool got_it = false;
	bool go_for_it = true;
	int num_tries;

	while (next_seq == true){
		num_tries = 0;
		while (got_it == false && go_for_it == true){
			display_seq(up);
			int user_result;
			cin >> user_result;
			if (correct_guess(up, user_result)){
				got_it = true;
				bump_correct(up);
				bump_guess(up);
				cout << "yes! exactly!\n";
			}
			else
			{
				got_it = false;
				bump_guess(up);
				cout << wrong_msgs[num_tries < ns_wrong_message ? num_tries : 3] << "\n"
					<< "Do you want to try again?[y/n]";
				char ans;
				cin >> ans;
				if (ans == 'y' || ans == 'Y') go_for_it = true;
				else go_for_it = false;
			}
		}
		cout << "Want to try another sequence? (y/n) ";
		char try_again;
		cin >> try_again;

		if (try_again == 'N' || try_again == 'n')
			next_seq = false;
		else { got_it = false; reset_seq(up); }
	}
}