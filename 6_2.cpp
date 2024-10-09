#include <iostream>
#include <vector>
using namespace std;

void check(int& i) {
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> i;
	} while (cin.fail());
}


int checkchoice()
{
	int x;
	cin >> x;
	while (cin.fail() || cin.get() != '\n' || x < 0 || x > 7)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Ошибка ввода! Пожалуйста, повторите ввод: ";
		cin >> x;
	}
	return x;
}

struct tree
{
	int value;
	int h;
	tree* left;
	tree* right;
	tree(int v) { value = v; left = right = NULL; h = 1; }
};

int height(tree* r)
{
	if (r) return r->h;
	else return 0;
}

int bfactor(tree* r)
{
	return height(r->right) - height(r->left);
}

void fixh(tree* r)
{
	int hl = height(r->left);
	int hr = height(r->right);
	if (hl > hr) r->h = hl + 1;
	else r->h = hr + 1;
}

tree* rightrotate(tree* p)
{
	tree* q = p->left;
	p->left = q->right;
	q->right = p;
	fixh(p);
	fixh(q);
	return q;
}

tree* leftrotate(tree* q)
{
	tree* p = q->right;
	q->right = p->left;
	p->left = q;
	fixh(q);
	fixh(p);
	return p;
}

tree* balance(tree* r)
{
	fixh(r);
	if (bfactor(r) == 2)
	{
		if (bfactor(r->right) < 0)
			r->right = rightrotate(r->right);
		return leftrotate(r);
	}
	if (bfactor(r) == -2)
	{
		if (bfactor(r->left) > 0)
			r->left = leftrotate(r->left);
		return rightrotate(r);
	}
	return r;
}

tree* insert(tree* r, int val)
{
	if (!r) return new tree(val);
	if (val < r->value) r->left = insert(r->left, val);
	else r->right = insert(r->right, val);
	return balance(r);
}

tree* findmin(tree* r)
{
	if (r->left) findmin(r->left);
	else return r;
}

tree* removemin(tree* r)
{
	if (!r->left) return r->right;
	r->left = removemin(r->left);
	return balance(r);
}

tree* erase(tree* rr, int val)
{
	if (!rr) return 0;
	if (val < rr->value) rr->left = erase(rr->left, val);
	else if (val > rr->value) rr->right = erase(rr->right, val);
	else
	{
		tree* l = rr->left;
		tree* r = rr->right;
		delete rr;
		if (!r) return l;
		tree* min = findmin(r);
		min->right = removemin(r);
		min->left = l;
		return balance(min);
	}
	return balance(rr);
}

void showtree(tree* r, int l)
{
	if (r)
	{
		showtree(r->right, l + 1);
		for (int i = 1; i <= l; i++) cout << "   " << " ";
		cout << r->value << endl;
		showtree(r->left, l + 1);
	}
}

void task_support(tree* r, int& j, vector<int>& abu)
{

	if (!r) return;
	task_support(r->left, j, abu);

	j++;
	if (j % 2 == 1)
	{
		abu.push_back(r->value);
	}

	task_support(r->right, j, abu);
}

void maintask(tree* r, int& j, vector<int>& abu)
{
	int l = 5;
	showtree(r, 0);
	while (r->right != NULL && r->left != NULL)
	{
		task_support(r, j, abu);
		int n = size(abu);
		for (int i = 0; i < n; i++)
		{
			cout << "Элемент " << abu[i] << " удален" << endl;
			r = erase(r, abu[i]);
		}
		for (int i = 0; i < n; i++)
			abu.pop_back();

		showtree(r, l);
		l += 5;
		j = 0;
	}

	if (r->left) {
		cout << "Элемент " << r->left->value << " удален" << endl;
		r = erase(r, r->left->value);
	}
	else {
		cout << "Элемент " << r->value << " удален" << endl;
		r = erase(r, r->value);
	}
	showtree(r, l);
}

tree* search(tree*& R, int val, int k) {
	if (R != NULL) {
		if (val == R->value) {
			cout << "Кол-во шагов: " << k++ << endl;
			return R;
		}
		k++;
		if (val < R->value) {
			if (R->left == NULL) {
				return NULL;
			}
			search(R->left, val, k);
		}
		else {
			if (R->right == NULL) {
				return NULL;
			}
			search(R->right, val, k);
		}
	}
	else return R;
}


void print_arr(tree* root) {
	if (root == NULL) return;
	print_arr(root->left);
	cout << root->value << " " << " ";
	print_arr(root->right);
}

int main()
{
	setlocale(LC_ALL, "rus");
	const int n = 10;
	vector <int> abu;
	int m = 0;
	tree* r = NULL;
	int step = 0, j = 0;
	int elem = 0;
	int choice = 1;
	int deepchoice = 0;
	int val = 0;

	while (choice != 0)
	{

		cout << "МЕНЮ"<<endl;
		cout << "1) Добавить элемент" << endl;
		cout << "2) Удалить элемент" << endl;
		cout << "3) Поиск элемента" << endl;
		cout << "4) Вывод дерева" << endl;
		cout << "5) Вывести список элементов" << endl;
		cout << "6) Циклично удалить каждый нечетный узел дерева" << endl;
		cout << "0) Выход" << endl;
		cout << "Выберите пункт меню: "; choice = checkchoice();

		switch (choice)
		{
		case 1:
			cout << "Ввести случайные числа или вручную?" << endl;
			cout << "1. Случайные числа" << endl;
			cout << "2. Вручную" << endl;
			deepchoice = checkchoice();
			if (deepchoice == 2)
			{
				cout << "Введите новый элемент:" << endl;
				check(val);

				if (search(r, val, 0) != NULL) cout << "Одинаковых элементов не должно быть в дереве!!!" << endl;
				else {

					r = insert(r, val);

				}
			}
			else if (deepchoice == 1)
			{
				for (int i = 0; i < n; i++) {
					val = rand() % 60;

					if (search(r, val, 0) != NULL) cout << "Пропущено повторяющееся число" << endl;
					else {
						r = insert(r, val);
					}
				}

				cout << "Элементы успешно добавлены!!!" << endl;
			}
			else cout << "Введено некорректное значение" << endl;
			break;
		
		case 2:
			if (r)
			{
				cout << "Введите элемент, который хотите удалить: ";
				cin >> elem;
				if (search(r, elem, 0) != NULL) {
					r = erase(r, elem);
					step = 0;
				}
				else
					cout << "Данного элемента нет в таблице!\n";
				
			}
			else cout << "Дерево пустое!\n";
			system("pause");
			break;

		case 3:
			if (r)
			{
				cout << "Введите элемент, который хотите найти: "; check(val);
				if (search(r, val, 0) != NULL) cout << "Элемент найден\n";
				else cout << "Элемент не найден\n";
			}
			else cout << "Дерево пустое!\n";
			system("pause");
			break;

		case 4:
			if (r)
			{
				showtree(r, 0);
				cout << endl;
			}
			else cout << "Дерево пустое!\n";
			system("pause");
			break;

		case 5:
			if (r)
			{
				cout << "Список, соответствующий симметричному обходу:\n";
				print_arr(r);
				cout << endl;
			}
			else cout << "Дерево пустое!\n";
			j = 0;
			system("pause");
			break;

		case 6:
			maintask(r, m, abu);
			system("pause");
			break;
		
		case 0:
			exit(0);
			break;
		}
	}

	return 0;
}