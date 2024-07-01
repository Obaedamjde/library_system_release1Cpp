#include <iostream>
#include<string>
#include<vector>
#include<deque>
#include <utility>
#include<algorithm>
///// اضافه فنكشين الاول البخث عن طريق id 
/// البحث كلمه كامله جوا السترنغ مش بس prefix 
/// اضافه تجديد ل كميه كوبي الكتاب 
/// // add list user orderd by id and name 
/// //specific

using namespace std;


const int MAX_NUMBER_CHOICE = 10;
int counter = 1;
bool is_returned = false;


struct USERBOOK {

	int id_user;
	string name_user;
	string email_user;
	string address_user;
	vector<pair<string,int>>name_borrowed_books_with_id;

};
struct BOOKINFO {
	int ID;
	string NAME;
	int total_quantity = 0;
	int total_borrowed = 0;		
	vector<string>name_user_borrow;

};

vector<BOOKINFO>Book_Info;
vector<USERBOOK>USERS;

enum LibraryMenu {
	Add_book = 1,
	Search_books_by_prefix,
	Print_who_borrowed_book_by_name,
	Print_library_by_id,
	Print_library_by_name,
	Add_user,
	User_borrow_book,
	User_return_book,
	Print_users,
	EXITPROGRAM
};
enum Borrow_OR_Return_Books{BORROW=1,RETURN};


int static ReadIntNumber(string Error_massege = " Invalid Number , Enter again :\n ") {
	//// check if number is integer or not 
	int number = 0;
	while (!(cin >> number)) {
		cout << Error_massege;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return number;
}
bool IsNumberBetween(int from, int to, int number) {
	if (from > to) {
		swap(from, to);
	}
	return (number >= from && number <= to);
}
string ReadString(string massege = "") {
	string name;
	getline(cin >> ws, name);
	return name;
}
int ReadIntNumberBetween(int from, int to, string Error_Massege = "input is invalid, number is not in the range , please enter again \n  ") {

	int number = ReadIntNumber();
	while (!(IsNumberBetween(from, to, number))) {
		cout << Error_Massege;
		number = ReadIntNumber();
	}

	return number;
}


bool is_id_book_exist(int id , vector<BOOKINFO>&Book_Info) {

	for (int z = 0; z < Book_Info.size(); z++) {

		if (id == Book_Info[z].ID)
			return true;
	}
	return false;
}
bool is_id_user_exist(int id, vector<USERBOOK>& USERS) {

	for (int z = 0; z < USERS.size(); z++) {

		if (id == USERS[z].id_user)
			return true;
	}
	return false;
}
int GetNameBookById(string book_name) {

	for (auto& book : Book_Info) {
		if (book.NAME == book_name) {
			return book.ID;
		}
	}
}
void Add_Book() {
	 
	cout << "Enter Book Book_Info : id & name & total quantity : " << endl;
	BOOKINFO book;
	book.ID = ReadIntNumber();
	book.NAME = ReadString();
	book.total_quantity= ReadIntNumber();
	if (! (book.total_quantity > 0 )) {
		cout << "Quantity of this book must be greater than zero " << endl;
		return;
	}

	if (is_id_book_exist(book.ID, Book_Info)) {
		cout << " The book is exist , enter new book again  " << endl;
		return;
	}

	Book_Info.push_back(book);
	cout << "Added Book Successfully :) " << endl;
}


bool is_prefix(const string& prefix, const string& full_name) {
	if (prefix.size() > full_name.size()) {
		return false;
	}
	else {
		return full_name.compare(0, prefix.size(), prefix) == 0;
	}
}
void SearchBooksByPrefix() {

	cout << "Enter book name prefix : " << endl;
	string prefix = ReadString();

	bool found = false;
	for (auto const& book : Book_Info) {

		if (is_prefix(prefix, book.NAME)) {
			found = true;
			cout << counter << " ) " << book.NAME << endl;
			counter++;
		}

	}

	if (!found) {
		cout << " NO books with such prefix ! " << endl;
	}
}




bool CompareById(const BOOKINFO& a, const BOOKINFO& b) {
	return a.ID < b.ID;
}
void PrintLibraryById() {


	sort(Book_Info.begin(), Book_Info.end(), CompareById);

	counter = 1;
	for (auto const& book : Book_Info) {
		cout << counter << ") ID = " << book.ID << " /  Name = "
			<< book.NAME << " / total_quantity = " << book.total_quantity
			<< "  / total_borrowed = " << book.total_borrowed << endl;
		counter++;
	}

}


bool CompareByName(const BOOKINFO& a, const BOOKINFO& b) {
	return a.NAME < b.NAME;
}
void PrintLibraryByName() {

	sort(Book_Info.begin(), Book_Info.end(), CompareByName);

	counter = 1;
	int total_borrowed = 0;
	for (auto const& book : Book_Info) {
		cout << counter << ") ID = " << book.ID << " /  Name = "
			<< book.NAME << " / total_quantity = " << book.total_quantity
			<< "  / total_borrowed = " << book.total_borrowed << endl;
		counter++;
	}

}


void AddUser() {

	USERBOOK user;
	cout << "Enter user name & national Id : " << endl;
	user.name_user = ReadString();
	user.id_user = ReadIntNumber();

	if (is_id_user_exist(user.id_user, USERS)) {
		cout << " The id user is exist , enter new user again  " << endl;
		return;
	}

	USERS.push_back(user);
	cout << " Added user Successfully :) " << endl;
	/*user.email_user = ReadString();
	user.address_user = ReadString();*/


}


//////Validation
bool No_User(vector<USERBOOK>& USERS) {
	if (USERS.empty()) {
		return true;
	}
	return false;
}
bool is_user_exist(string name, vector<USERBOOK>& USERS) {
	for (auto const&name_u: USERS) {
		if (name_u.name_user == name) {
			return true;
		}
	}
	return false;
}
bool is_name_book_exist(string name_book, vector<BOOKINFO>&Book_Info) {
	for (auto const& book : Book_Info) {
		if (book.NAME == name_book) {
			return true;
		}
	}
	return false;
}
bool is_total_books_greater_than_zero(string name_book, vector<BOOKINFO>& Book_Info) {
	for (int z = 0; z < Book_Info.size(); z++) {
		if (name_book == Book_Info[z].NAME) {
			if (Book_Info[z].total_quantity > 0) {
				return true;
			}
		}
	}
	return false;
}
bool is_total_borrowed_greater_than_zero(string name_book, vector<BOOKINFO>& Book_Info) {
	for (int z = 0; z < Book_Info.size(); z++) {
		if (name_book == Book_Info[z].NAME) {
			if (Book_Info[z].total_borrowed > 0) {
				return true;
			}
		}
	}
	return false;
}
bool is_user_borrow_book(string name, vector<BOOKINFO>& Book_Info) {
	for (int z = 0; z < Book_Info.size(); z++) {
		for (auto const& name_u : Book_Info[z].name_user_borrow) {
			if (name_u == name) {
				return true;
			}
		}
	}
	return false;
}
void ValidationOfUserAndBook(string name_user, string name_book) {

	if (!is_name_book_exist(name_book, Book_Info)) {
		cout << " Sorry ,this book not found , enter book first " << endl;
		return;
	}
	if (!is_user_exist(name_user, USERS)) {
		cout << " Sorry ,this user not found , enter user first " << endl;
		return;
	}
}
////

void PrintWhoBorrowedBookByName() {

	cout << "Enter name of book to know who is borrowed it <3" << endl;

	string name_book = ReadString();

	if (is_name_book_exist(name_book, Book_Info)) {


		for (int z = 0; z < Book_Info.size(); z++) {
			counter = 1;
			if (name_book == Book_Info[z].NAME) {

				for (int i = 0; i < Book_Info[z].name_user_borrow.size(); i++) {
					cout << counter << ") " << Book_Info[z].name_user_borrow[i] << endl;
					counter++;
				}

			}
		}
	}
	else {
		cout << "Sorry this book not added in this library , enter it and you are welcome here :) " << endl;
	}

}


bool ChangeUsersNumberOfBookSReaturnAndBorrow(string name_user, int id, vector<USERBOOK>& USERS, vector<BOOKINFO>& Book_Info, string name_book, Borrow_OR_Return_Books choice) {
	int id_book = 0;

	switch (choice)
	
	{
	case BORROW:

		for (auto const& book : Book_Info) {

			if (book.NAME == name_book) {
				id_book = book.ID;
				break;
			}
		}

		for (int z = 0; z < USERS.size(); z++) {

			if (name_user == USERS[z].name_user) {
				USERS[z].name_borrowed_books_with_id.push_back({ name_book,id_book });
				return true;
			}
		}
		return false;
		break;

	case RETURN:
		for (int z = 0; z < USERS.size(); z++) {
			if (name_user == USERS[z].name_user) {

				vector<pair<string, int>>NewIdAndBookAfterReaturn;

				for (auto const& book : USERS[z].name_borrowed_books_with_id) {
					if (!(book.second==id)) {

						NewIdAndBookAfterReaturn.push_back({ book.first,book.second });

					}
				}
				USERS[z].name_borrowed_books_with_id = NewIdAndBookAfterReaturn;
				return true;
			}

		}

		return false;
		break;

	}


}
bool ChangeNumberQuantityBooksReturnAndBorrow(string name_user, int id, vector<USERBOOK>& USERS, vector<BOOKINFO>& Book_Info, string name_book, Borrow_OR_Return_Books choice) {
	switch (choice)
	{
	case BORROW:
		for (auto& book : Book_Info) {
			if (name_book == book.NAME) {
		
				if (!is_total_books_greater_than_zero(name_book, Book_Info)) {
					return false;
				}

				book.total_borrowed++;
				book.total_quantity--;
				book.name_user_borrow.push_back(name_user);
				return true;

			}
		}

		return false;
		break;

	case RETURN:
		for (auto& book : Book_Info) {
			if (book.ID == id) {

				if (!is_total_books_greater_than_zero(name_book, Book_Info)) {
					return false;
				}

				vector<string>NewBookAfterReturn;
				book.total_borrowed--;
				book.total_quantity++;
				for (auto& new_borrow_book : book.name_user_borrow) {

					if (name_user != new_borrow_book) {
						NewBookAfterReturn.push_back(new_borrow_book);
					}

				}
				book.name_user_borrow = NewBookAfterReturn;
				return true;
			}
		}
		return false;
		break;
	}
}


void UserBorrowBook() {

	cout << " Enter user name & book name want to borrow it : " << endl;

	string name_user = ReadString("Please enter user name");
	string name_book = ReadString("Please enter book name");
	ValidationOfUserAndBook(name_user, name_book);

	if (USERS.empty()) {
		cout << "There is no user yet , enter user first ." << endl;
		return;
	}
		
	int id = GetNameBookById(name_book);
	ChangeUsersNumberOfBookSReaturnAndBorrow(name_user, id, USERS, Book_Info, name_book, Borrow_OR_Return_Books::BORROW);
	ChangeNumberQuantityBooksReturnAndBorrow(name_user, id, USERS, Book_Info, name_book, Borrow_OR_Return_Books::BORROW);

	cout << " Done Borrow Successfully :) " << endl;

	}


void UserReturnBook() {

	cout << " Enter user name & book name want to return it : " << endl;
	string name_user = ReadString();
	string name_book = ReadString();
	ValidationOfUserAndBook(name_user, name_book);

	/// check if user is borrow book or not 
	if (! is_user_borrow_book(name_user, Book_Info)) {
		cout << "Sorry ,this user doesn't borrowed any book " << endl;
	}

	if (!is_total_borrowed_greater_than_zero(name_book, Book_Info)) {
		cout << " Sorry ,This book can’t be borrowed  ! " << endl;
		return;
	}

	int id = GetNameBookById(name_book);
	ChangeUsersNumberOfBookSReaturnAndBorrow(name_user, id, USERS, Book_Info, name_book, Borrow_OR_Return_Books::RETURN);
	ChangeNumberQuantityBooksReturnAndBorrow(name_user, id, USERS, Book_Info, name_book, Borrow_OR_Return_Books::RETURN);

	cout << " Done Return Book Successfully :) " << endl;
}


void PrintUsers() {
	// ضيف شيك اذا ما كان في مستخدين 
	if (No_User(USERS)) {
		cout << "Sorry there is no users yet ! , enter users then come back . " << endl;
		return;
	}

		counter = 1;
		for ( auto const & user: USERS ) {

		  cout << counter << " ) " << user.name_user << " / id = " << user.id_user << " borrowed books name & id : ";

			counter++;
			for (auto const& borrow_book : user.name_borrowed_books_with_id) {

				cout << borrow_book.first << " [ " << borrow_book.second << " ] , ";
			} 
			cout << endl;
		}
}


void ExitProgram() {
	cout << "Thanks for using library system , hope enjoy with it " << endl;
	cout << "Done By  "" ( Obaeda_Majde ) "" Good Bye >3 " << endl;
	return;
}


void DisplayMenu() {
	cout << "Library menu : \n" << endl;
	cout << "1) Add book " << endl;
	cout << "2) Search books by_prefix	" << endl;
	cout << "3) Print who borrowed_book_by_name  " << endl;
	cout << "4) Print library by_id  " << endl;
	cout << "5) Print library by_name  " << endl;
	cout << "6) Add user  " << endl;
	cout << "7) User borrow book  " << endl;
	cout << "8) User return book  " << endl;
	cout << "9) Print users " << endl;
	cout << "10) Exit " << endl;
	cout << "\n\n";
	cout << "Enter your  menu Choice [1-10] : " << endl;
	return;
}


void LibrarySystem() {



	while (true) {

		DisplayMenu();

		int choice = ReadIntNumberBetween(1, MAX_NUMBER_CHOICE);

		switch (choice)
		{

		case Add_book:
			Add_Book();
			system("pause>0");
			system("cls"); // clear cmd 
			break;


		case Search_books_by_prefix:
			SearchBooksByPrefix();
			system("pause>0");
			system("cls"); // clear cmd 
			break;


		case  Print_who_borrowed_book_by_name:
			PrintWhoBorrowedBookByName();
			system("pause>0");
			system("cls"); // clear cmd
			break;


		case Print_library_by_id:
			PrintLibraryById();
			system("pause>0");
			system("cls");
			break;


		case  Print_library_by_name:
			PrintLibraryByName();
			system("pause>0");
			system("cls"); // clear cmd
			break;


		case  Add_user:
			AddUser();
			system("pause>0");
			system("cls"); // clear cmd
			break;


		case  User_borrow_book:
			UserBorrowBook();
			system("pause>0");
			system("cls"); // clear cmd
			break;


		case  User_return_book:
			UserReturnBook();
			system("pause>0");
			system("cls"); // clear cmd
			break;


		case  Print_users:
			PrintUsers();
			system("pause>0");
			system("cls"); // clear cmd
			break;


		case  EXITPROGRAM:
			ExitProgram();
			system("pause>0");
			system("cls"); // clear cmd
			return;

		}


	}


}


int main() {

	LibrarySystem();
	// Done By Obaeda Majde :) 
}
