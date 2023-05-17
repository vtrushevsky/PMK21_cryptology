#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
class Book {
public:
    string _name;
    string _author;
    double _price;

    Book (string name, string author, double price){
        _name = name;
        _author = author;
        _price = price;
    }
    Book() {};

};

class Shop {
public:
    string _name;
    vector<Book> books;
    int head = 0;
    int size = 0;
    double capital = 0;
public:
    Shop(string name){
        _name = name;
    };
    bool CheckSpace(){
        return size != 9;
    }
    bool addToShop (Book& book){
        if (CheckSpace()){
            books.push_back(book);
            head ++;
            size++;
            return true;
        }
        return false;
    }
    string GetName(){
        return _name;
    }
    double countCapital(){
        for (auto it: books){
            capital += it._price;
        }
        return capital;
    }

};
Shop& findByName(vector<Shop>& shops, string name){
    auto result =  find_if(shops.begin(), shops.end(), [&name](auto shop) {return shop.GetName() == name;} );
    cout << "Shop's capital: " << result->countCapital() << endl;
    return *result;
}

vector<Book> findByAuthor(vector<Shop>& shops, string author){
    vector<Book> books_author;
    for(auto shop: shops){
        for (auto book: shop.books){
            if (book._author == author){
                books_author.push_back(book);
            }
        }
    }
    return books_author;
}

int filterByPrice(vector<Book> authorBooks, int price1, int price2){
    vector<Book> suitablebooks;
    for (auto book: authorBooks){
        if( price1 < book._price and book._price < price2){
            suitablebooks.push_back(book);
        }
    }

    return suitablebooks.size();
}

bool write_to_file(Book& book, ofstream& file_to_write) {
    if (!file_to_write.is_open()) {
        cerr << "Error: file not open for writing\n";
        return false;
    }

    file_to_write << "Name: " <<  book._name << endl;
    file_to_write << "Author: " <<  book._author << endl;
    file_to_write << "Price: " <<  book._price << endl;
    file_to_write << endl;

    return true;
}

vector<Book> findMaxMin(vector<Shop>& shops) {
    vector<Book> allBooks;
    for (auto shop: shops){
        for(auto book: shop.books){
            allBooks.push_back(book);
        }
    }
    vector<Book> result;
    struct
    {
        bool operator()(Book a, Book b) const { return a._price < b._price; }
    }
            customGreater;

    auto resultMax = max_element(allBooks.begin(), allBooks.end(),customGreater);
    auto resultMin = min_element(allBooks.begin(), allBooks.end(),customGreater);

    result.push_back(*resultMax);
    result.push_back(*resultMin);
    return result;

}
Book& CheckColision(Shop& one, Shop& two){
    for (auto book: two.books){
        auto res = find_if(one.books.begin(), one.books.end(), [book](Book el){
            return (el._name == book._name) and (el._price < book._price);
        });
        return *res;
    }
}

vector<Book> CheckDoublePriceSingle(Shop& shop){
    auto books = shop.books;
    vector<Book> res;
    for (auto book: books){
        for (auto book1: books){
            if ((book._price / book1._price) == 2){
                res.push_back(book);
                res.push_back(book1);
                return res;
            }
        }
    }
}

vector<Book> CheckDoublePrice(Shop& shop, Shop& shop1){
    vector<Book> res;
    for (auto book1: shop.books){
        for (auto book2: shop1.books){
            if ((book1._price / book2._price) == 2){
                res.push_back(book1);
                res.push_back(book2);
                return res;
            }
        }
    }
}

int main() {
    vector<Shop> shops;

    Shop shop1("Shop1");
    Shop shop2("Shop2");

/// READ FROM FILE AND ADD BOOKs TO FIRST SHOP

    ifstream file("/home/dmytro/CLionProjects/algorithm/text");
    if (!file.is_open()) {
        cout << "Error with file" << endl;
    }
    while (!file.eof()){
        string name, author;
        double price;
        file >> name;
        file >> author;
        file >> price;
        Book book1 = *new Book (name , author,price);
        shop1.addToShop(book1);
    }

/// READ FROM FILE AND ADD BOOKs TO SECOND SHOP

    ifstream file1("/home/dmytro/CLionProjects/algorithm/text2");
    if (!file1.is_open()) {
        cout << "Error with file" << endl;
    }
    while (!file1.eof()){
        string name, author;
        double price;
        file1 >> name;
        file1 >> author;
        file1 >> price;
        Book book1 = *new Book (name , author,price);
        shop2.addToShop(book1);
    }


    shops.push_back(shop1);
    shops.push_back(shop2);
    findByName(shops, "Shop1");
    vector<Book> found_books;

    found_books = findByAuthor(shops, "Author1");
    ofstream file_to_write("/home/dmytro/CLionProjects/algorithm/written");
    for (auto book: found_books){
        write_to_file(book, file_to_write);
    }

    int price1 = 5;
    int price2 = 10000;

    int count = filterByPrice(found_books, price1, price2);
    cout <<"Number of books that in range from " << price1 << " to " << price2 << " --> " <<  count << endl;



      vector<Book> maxminbooks = findMaxMin(shops);
    cout << endl << "[Max and Min]" << endl << endl;
    for (auto book: maxminbooks){
        cout << "Name: " <<  book._name << endl;
        cout << "Author: " <<  book._author << endl;
        cout << "Price: " <<  book._price << endl;
        cout << endl;
    }



    auto haveBooks = [](auto shop) { return shop.books.size() >= 3;};
    auto result = find_if(shops.begin(), shops.end(), haveBooks);
    cout << "Shop with 3+ books >> " <<  result->_name << endl << endl;

    cout << "[Books with double prices]" << endl;
    auto result_double_price = CheckDoublePriceSingle(shop1);
    for (auto book: result_double_price){
        cout << "[Book]" << endl;
        cout << "Name: " <<  book._name << endl;
        cout << "Author: " <<  book._author << endl;
        cout << "Price: " <<  book._price << endl;
        cout << endl;
    }
    auto res = CheckColision(shop1, shop2);
    cout << "Book colision in Shop1 and Shop2 -->  " << res._name  << " Lowest price " << res._price << endl << endl;

    cout << "[Books with double prices twoo shops]" << endl;
    auto resDoublePriceTwoShops = CheckDoublePrice(shop1, shop2);

    for (auto book: resDoublePriceTwoShops){
        cout << "[Book]" << endl;
        cout << "Name: " <<  book._name << endl;
        cout << "Author: " <<  book._author << endl;
        cout << "Price: " <<  book._price << endl;
        cout << endl;
    }



}
