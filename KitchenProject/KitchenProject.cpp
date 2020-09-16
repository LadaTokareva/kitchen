#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
ifstream f;
// абстрактный класс kitchenware(кухонная утварь)
class Kitchenware {
public:
	// инвентарный номер
	int inventory_number;

	// конструктор
	Kitchenware(int inventory_number) {
		this->inventory_number = inventory_number;
	}

	// функция вывода инвентарного номера
	virtual void print()
	{
		cout << "Инвентарный номер: " << this->inventory_number << endl;
	}

	virtual ~Kitchenware()
	{

	}
};

// класс "Плита" виртуально наследуется от класса kitchenware
class Stove : virtual public Kitchenware {
	// строка, которая содержит информцацию о цвете плиты
	string color;
public:

	// конструктор класса Stove
	Stove(int inventory_number, string color) : Kitchenware(inventory_number) {
		this->color = color;
	}

	virtual void print() {

		// Выводим информацию о классе родителе
		Kitchenware::print();

		// Выводим цвет плиты
		cout << "Цвет: " << this->color << endl;
	}
};

// класс "кастрюля". Виртуальное наследуется от класса "Kitchenware"
class Pan : virtual public Kitchenware {
	// объём
	int capacity;
public:
	// конструктор класса
	Pan(int inventory_number, int capacity) : Kitchenware(inventory_number) {
		this->capacity = capacity;
	}

	// Вывод информации о кастрюле + информация из класса-родителя
	virtual void print() {
		Kitchenware::print();
		cout << "Объем: " << this->capacity << endl;
	}
};

// Електрическая плита. наследуется от класса "плита"
class ElectricStove : public Stove {
	// мощность
	int power;
public:
	// конструктор класса
	ElectricStove(int inventory_number, string color, int power) : Stove(inventory_number, color), Kitchenware(inventory_number) {
		this->power = power;
	}

	// вывод информации о плите
	virtual void print() {
		Stove::print();
		cout << "Мощность: " << this->power << endl;
	}
};


// газовая плита. наследуется от класса "плита"
class GasStove : public Stove {

	// потребление газа
	int gas_consumption;
public:
	// конструктор класса.
	GasStove(int inventory_number, string color, int gas_consumption) : Stove(inventory_number, color), Kitchenware(inventory_number) {
		this->gas_consumption = gas_consumption;
	}

	// вывод информации о газовой плите
	virtual void print() {
		Stove::print();
		cout << "Расход газа: " << this->gas_consumption << endl;
	}
};

// мультиварка. Наследуется от класса "Электрическая плита" и от класса "кастрюля"
class MultiCook : public ElectricStove, public Pan {
	bool has_pressure_cooker;
public:

	MultiCook(int inventory_number, string color, int power, int capacity, bool has_pressure_cooker) : ElectricStove(inventory_number, color, power), Pan(inventory_number, capacity), Kitchenware(inventory_number) {
		this->has_pressure_cooker = has_pressure_cooker;
	}
	virtual void print() {
		ElectricStove::print();
		Pan::print();
		cout << "Имеет ли функцию скороварки: " << this->has_pressure_cooker << endl;
	}
};
class Tree {
public:
	struct Node
	{
		Kitchenware* kitchenware;
		Node* left;
		Node* right;
	};
	typedef Node* PNode;

	PNode Root;
	Tree() {
		this->Root = nullptr;
	}

	void add(Kitchenware* data) {
		AddNode(Root, data);
	}
	void AddNode(PNode& Tree, Kitchenware* kitchenware)
	{
		// если дерево пустое, создаём новое
		if (Tree == nullptr) {
			Tree = new (Node);
			Tree->left = nullptr;
			Tree->right = nullptr;
			Tree->kitchenware = kitchenware;
			return;
		}

		// если номер инвентарного номера меньше больше значения инвентарного номера в вершине,
		// то переходим в правое поддерево, иначе в правое
		if (kitchenware->inventory_number > Tree->kitchenware->inventory_number)
			AddNode(Tree->right, kitchenware);
		else AddNode(Tree->left, kitchenware);
	}

///*****
// находим в левом поддереве самый правый узел
	void DeleteNode(PNode& r, PNode& q)
	{

		if (r->right != nullptr)
			DeleteNode(r->right, q);
		else
		{
			q->kitchenware = r->kitchenware;
			q = r;
			r = r->left;
		}
	}
	//******
	void Delete(PNode& Tree, int a)
	{
		if (Tree == nullptr)
		{
			cout << "Дерево пустое" << endl;
		}
		// если элемент меньше, то переходим в левое поддерево
		if (a < Tree->kitchenware->inventory_number)
			Delete(Tree->left, a);
		// если больше, то переходим в правое поддерево
		else if (a > Tree->kitchenware->inventory_number)
			Delete(Tree->right, a);
		else
		{
			PNode q = Tree;

			// если отсутствует левое поддерево, то присоваиваем правое
			if (q->left == nullptr)
				Tree = q->right;
			// иначе присваиваем левое
			else if (q->right == nullptr)
				Tree = q->left;
			// если оба поддерева присутствуют, то переходим во вспомогательную функцию
			else
				DeleteNode(q->left, q);
			delete q->kitchenware;
			delete q;
		}
	}

	void Clear(PNode Tree) {
		if (Tree == nullptr)
			return;
		Clear(Tree->left);
		Clear(Tree->right);
		delete Tree;
	}

	string printStr(PNode Root) {
		return to_string(Root->kitchenware->inventory_number) + (Root->left != nullptr || Root->right != nullptr ?
			("(" + (Root->left != nullptr ?
				printStr(Root->left) :
				"_") + ", "
				+ (Root->right != nullptr ?
					printStr(Root->right) :
					"_") + ")") :
			"");
	}

	PNode search(PNode& Tree, int x) {
		if (Tree == nullptr)
			return nullptr;

		if (x < Tree->kitchenware->inventory_number)
			return search(Tree->left, x);
		else if (x > Tree->kitchenware->inventory_number)
			return search(Tree->right, x);

		return Tree;
	}

	void remove(int x) {
		Delete(Root, x);
	}

	bool find(int x, Kitchenware*& data) {
		PNode temp = search(Root, x);
		if (temp != nullptr) {
			data = temp->kitchenware;
			return true;
		}
		return false;
	}

	void preOrder(PNode& p)
	{
		if (p == nullptr)
			return;
		p->kitchenware->print();
		cout << '\n';
		preOrder(p->left);
		preOrder(p->right);
	}

	void preOrder()
	{
		preOrder(Root);
	}

	void inOrder(PNode& p)
	{
		if (p == nullptr)
			return;

		inOrder(p->left);
		p->kitchenware->print();
		cout << '\n';

		inOrder(p->right);
	}

	void inOrder()
	{
		inOrder(Root);
	}

	void postOrder(PNode& p)
	{
		if (p == nullptr)
			return;
		postOrder(p->left);
		postOrder(p->right);
		p->kitchenware->print();
		cout << '\n';
	}

	void postOrder()
	{
		postOrder(Root);
	}
	void print() {
		cout << printStr(Root);
	}

	~Tree() {
		Clear(Root);
	}
};

string getString(int type_work, string text_query)
{
	if (type_work == '1')
	{
		cout << text_query;
		string temp;
		cin >> temp;
		return temp;
	}
	else
	{
		string temp, line;
		while (getline(f, line)) {
			stringstream ss(line);
			getline(ss, temp);
			if (temp.size() > 0)
				break;
		}

		cout << text_query << temp << endl;
		return temp;
	}
}

int getNumber(int type_work, string text_query)
{
	if (type_work == '1')
	{
		cout << text_query;
		int temp;
		cin >> temp;
		return temp;
	}
	else
	{
		string res = getString(type_work, text_query);
		if (res.empty())
			return 4;
		return  atoi(res.c_str());
	}
}
int main() {
	bool is_file = false;
	setlocale(LC_ALL, "Russian");
	Tree* tree = new Tree();
	string t;


	bool isDoneSession = true;
	bool isDone = true;
	string filename;
	while (isDone)
	{
		while (true)
		{
			cout << "1. Ввод из консоли 2. Ввод из файла 3. Выход  : ";
			cin >> t;
			if (t.size() > 1)
			{
				cout << "неверный номер" << endl;
				continue;
			}
			break;
		}
		if (t[0] == '1')
			isDoneSession = true;
		if (t[0] == '2')
		{
			cout << "имя файла: ";
			is_file = true;
			isDoneSession = true;
			cin >> filename;
			if (filename.size() == 0)
				filename = "test.txt";

			f.open(filename, ios_base::beg);
			if (!f.is_open())
			{
				isDoneSession = false;
				cout << "Не удалось открыть файл";
			}
		}
		else if (t[0] == '3')
		{
			isDone = false;
			isDoneSession = false;
		}
		cout << endl << endl;
		while (isDoneSession)
		{


			switch (getNumber(t[0], "1. Добавить; 2. Удалить; 3. Вывести; 4. Выход : "))
			{
			case 1:
			{
				int type_ware = getNumber(t[0], "Утварь: 1 - Плита; 2 - Кастрюля; 3 - Электрическая плита; 4 - Газовая плита; 5 - Мультиварка : ");
				int inventoryNumber = getNumber(t[0], "Введите инвертарный номер: ");

				Kitchenware* temp;
				if (tree->find(inventoryNumber, temp)) {
					cout << "Утварь с таким номером уже есть: " << endl;
					temp->print();
					cout << endl;
				}
				else {
					switch (type_ware)
					{
					case 1:
						temp = new Stove(inventoryNumber, getString(t[0], "Цвет: "));
						break;
					case 2:
						temp = new Pan(inventoryNumber, getNumber(t[0], "Объем: "));
						break;
					case 3:
						temp = new ElectricStove(inventoryNumber, getString(t[0], "Цвет: "), getNumber(t[0], "Мощость: "));
						break;
					case 4:
						temp = new GasStove(inventoryNumber, getString(t[0], "Цвет: "), getNumber(t[0], "Потребление газа: "));
						break;
					case 5:
						temp = new MultiCook(inventoryNumber, getString(t[0], "Цвет: "), getNumber(t[0], "Мощность: "),
							getNumber(t[0], "Объем: "), getNumber(t[0], "Функция скороварки: ") == 1);
						break;
					default:
						temp = NULL;
					}
					if (temp != NULL)
						tree->add(temp);
				}
			}
			break;

			case 2:
				tree->remove(getNumber(t[0], "Инвертарный номер: "));
				break;
			case 3:
			{
				switch (getNumber(t[0], "Тип обхода: 1. Прямой, 2. Центрированный, 3. Обратный, 4. Дополнительный: "))
				{
				case 1:
					tree->preOrder();
					break;
				case 2:
					tree->postOrder();
					break;
				case 3:
					tree->inOrder();
					break;
				case 4:
					tree->print();
				default:
					break;
				}
			}
			break;
			case 4:
				if (is_file)
				{
					is_file = false;
					t[0] = '1';
					f.close();
					
				}
				isDoneSession = false;
				break;
			}
		}
	}
	delete tree;
	std::system("pause");
	return 0;
}
