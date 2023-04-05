#include <iostream>
#include <fstream>
using namespace std;


template <typename T>
struct Triangle
{
	T side_1;
	T side_2;
	T side_3;
	Triangle* next;
	Triangle(T side_1, T side_2, T side_3) : side_1(side_1), side_2(side_2), side_3(side_3), next(nullptr) {}

	T triangle_area() const
	{
		T s = (side_1 + side_2 + side_3) / 2.0;
		return sqrt(s * (s - side_1) * (s - side_2) * (s - side_3));
	}
	T getPerimeter() const {
		return side_1 + side_2 + side_3;
	}
};

template <typename T>
class List
{
	Triangle<T>* head;
	Triangle<T>* tail;
	size_t sz;
public:
	List() : head(nullptr), tail(nullptr), sz(0) {}

	List(const List& other) {
		Triangle* curr = other.head;
		while (curr != nullptr) {
			add(curr->side_1, curr->side_2, curr->side_3);
			curr = curr->next;
		}
	}

	List(List&& other) noexcept {
		head = other.head;
		tail = other.tail;
		sz = other.sz;
		other.head = nullptr;
		other.tail = nullptr;
		other.sz = 0;
	}

	~List()
	{
		Triangle<T>* current = head;
		while (current != nullptr)
		{
			Triangle<T>* temp = current;
			current = current->next;
			delete temp;
		}
	}

	bool remove(Triangle<T>* Triangle_to_remove)
	{
		if (Triangle_to_remove == nullptr || head == nullptr)
		{
			return false;
		}

		if (Triangle_to_remove == head)
		{
			head = head->next;
		}
		else
		{
			Triangle* current = head;
			while (current->next != Triangle_to_remove)
			{
				current = current->next;
				if (current == nullptr)
				{
					return false;
				}
			}
			current->next = Triangle_to_remove->next;

			if (Triangle_to_remove == tail)
			{
				tail = current;
			}
		}

		delete Triangle_to_remove;
		sz--;
		return true;
	}

	void add(Triangle<T> t)
	{
		Triangle<T>* new_Triangle = new Triangle<T>(t);

		if (head == nullptr)
		{
			head = new_Triangle;
			tail = new_Triangle;
		}
		else
		{
			tail->next = new_Triangle;
			tail = new_Triangle;
		}
		sz++;
	}

	Triangle<T>* find(T side_1, T side_2, T side_3)
	{
		Triangle* current = head;
		while (current != nullptr) {
			if (current->side_1 == side_1 && current->side_2 == side_2 && current->side_3 == side_3) {
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}

	void writeToFile(string filename) {
		ofstream out(filename);
		Triangle<T>* current = head;
		while (current != nullptr) {
			out << current->triangle_area() << " " << current->getPerimeter() << endl;
			current = current->next;
		}
		out.close();
	}


	bool empty() const { return head == nullptr; }
	size_t size() const { return sz; }

	friend std::ostream& operator << (std::ostream& os, const List& l)
	{
		l.print(os);
		return os;
	}

private:
	void print(std::ostream& os) const
	{
		Triangle<T>* current = head;
		while (current != nullptr) {
			os << "Side 1: " << current->side_1 << endl << "Side 2: " << current->side_2 << endl << "Side 3: " << current->side_3 << endl;
			current = current->next;
		}
		os << std::endl;
	}

};

int main() {
	List <double> list;

	ifstream in("triangles.txt");

	double side_1, side_2, side_3;

	while (in >> side_1 >> side_2 >> side_3) {
		Triangle<double> t(side_1, side_2, side_3);
		list.add(t);
	}

	in.close();

	list.writeToFile("filtered_triangles.txt");

	cout << list;


	return 0;
}