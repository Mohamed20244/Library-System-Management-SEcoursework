#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits> // Add this include for numeric_limits

class Book;
class Member;
class Library;

class Person {
public:
    Person(std::string name, std::string address, std::string email);
    virtual ~Person();
    virtual std::string getName();
    virtual void setName(std::string name);
    virtual std::string getAddress();
    virtual void setAddress(std::string address);
    virtual std::string getEmail();
    virtual void setEmail(std::string email);

private:
    std::string name;
    std::string address;
    std::string email;
};

class Member : public Person {
public:
    Member(int memberID, std::string name, std::string address, std::string email);
    int getMemberID();
    std::vector<Book*> getBooksBorrowed();
    void setBooksBorrowed(Book* book);

private:
    int memberID;
    std::vector<Book*> booksBorrowed;
};

class Book {
public:
    Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName);
    int getBookID();
    std::string getBookName();
    std::string getAuthorFirstName();
    std::string getAuthorLastName();
    void setDueDate();
    void returnBook();
    void borrowBook(Member* borrower, time_t dueDate);

private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    time_t dueDate;
    Member* borrower;
};

class Library {
public:
    void addMember(std::string name, std::string address, std::string email);
    void issueBook(int memberID, int bookID);
    void returnBook(int memberID, int bookID);
    void displayBorrowedBooks(int memberID);
    void calcFine(int memberID);

private:
    std::vector<Member*> members;
    std::vector<Book*> books;
};

Person::Person(std::string name, std::string address, std::string email)
    : name(name), address(address), email(email) {}

Person::~Person() {}

std::string Person::getName() {
    return name;
}

void Person::setName(std::string name) {
    this->name = name;
}

std::string Person::getAddress() {
    return address;
}

void Person::setAddress(std::string address) {
    this->address = address;
}

std::string Person::getEmail() {
    return email;
}

void Person::setEmail(std::string email) {
    this->email = email;
}

Member::Member(int memberID, std::string name, std::string address, std::string email)
    : Person(name, address, email), memberID(memberID) {}

int Member::getMemberID() {
    return memberID;
}

std::vector<Book*> Member::getBooksBorrowed() {
    return booksBorrowed;
}

void Member::setBooksBorrowed(Book* book) {
    booksBorrowed.push_back(book);
}

Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
    : bookID(bookID), bookName(bookName), authorFirstName(authorFirstName), authorLastName(authorLastName), borrower(nullptr) {}

int Book::getBookID() {
    return bookID;
}

std::string Book::getBookName() {
    return bookName;
}

std::string Book::getAuthorFirstName() {
    return authorFirstName;
}

std::string Book::getAuthorLastName() {
    return authorLastName;
}

void Book::setDueDate() {
    // Implement set due date logic
    // This function needs to be filled based on your requirements
}

void Book::returnBook() {
    // Implement return book logic
    // This function needs to be filled based on your requirements
    borrower = nullptr;
}

void Book::borrowBook(Member* borrower, time_t dueDate) {
    this->borrower = borrower;
    this->dueDate = dueDate;
}

void Library::addMember(std::string name, std::string address, std::string email) {
    members.push_back(new Member(members.size() + 1, name, address, email));
}

void Library::issueBook(int memberID, int bookID) {
    // Implement logic to issue a book to a member
    // You may need to manage a collection of books and members in the library
    // and update their states accordingly
    std::cout << "Book issued successfully.\n";
}

void Library::returnBook(int memberID, int bookID) {
    // Implement logic to return a book from a member
    // You may need to manage a collection of books and members in the library
    // and update their states accordingly
    std::cout << "Book returned successfully.\n";
}

void Library::displayBorrowedBooks(int memberID) {
    // Find the member with the given ID
    Member* member = nullptr;
    for (Member* m : members) {
        if (m->getMemberID() == memberID) {
            member = m;
            break;
        }
    }

    if (member == nullptr) {
        std::cout << "Member with ID " << memberID << " not found.\n";
        return;
    }

    std::vector<Book*> borrowedBooks = member->getBooksBorrowed();

    if (borrowedBooks.empty()) {
        std::cout << "Member " << memberID << " has not borrowed any books.\n";
    } else {
        std::cout << "Borrowed books for Member " << memberID << ":\n";
        for (Book* book : borrowedBooks) {
            std::cout << "Book ID: " << book->getBookID() << ", Book Name: " << book->getBookName() << "\n";
        }
    }
}

void Library::calcFine(int memberID) {
    // Implement logic to calculate fine for overdue books
    // You may need to manage a collection of books and members in the library
    // and calculate fines based on due dates
    std::cout << "Fine calculated successfully.\n";
}

int getChoice() {
    int choice;
    std::cout << "\nLibrary Management System\n";
    std::cout << "1. Display Book by ID\n";
    std::cout << "2. Add Member\n";
    std::cout << "3. Issue Book to Member\n";
    std::cout << "4. Return Book from Member\n";
    std::cout << "5. Display Books Borrowed by Member\n";
    std::cout << "6. Calculate Fine for Overdue Books\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";

    while (!(std::cin >> choice)) {
        std::cin.clear();  // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
        std::cout << "Invalid input. Please enter a number: ";
    }

    return choice;
}

int main() {
    Library library;

    std::ifstream myFile;
    myFile.open("Excel.csv");

    if (!myFile.is_open()) {
        std::cerr << "Error opening file: Excel.csv" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(myFile, line)) {
        std::cout << line << std::endl;
    }

    myFile.close();

    int choice;
    do {
        choice = getChoice();

        switch (choice) {
            case 1: {
                // Display Book by ID
                int bookID;
                std::cout << "Enter Book ID: ";
                std::cin >> bookID;

                // Implement logic to display book by ID
                // Replace the following line with your actual logic
                std::cout << "Book details for ID " << bookID << " will be displayed here.\n";
                break;
            }
            case 2: {
                // Add Member
                std::string name, address, email;
                std::cout << "Enter Member Name: ";
                std::cin.ignore(); // Ignore newline character from previous input
                std::getline(std::cin, name);
                std::cout << "Enter Member Address: ";
                std::getline(std::cin, address);
                std::cout << "Enter Member Email: ";
                std::getline(std::cin, email);

                library.addMember(name, address, email);
                std::cout << "Member added successfully.\n";
                break;
            }
            case 3: {
                // Issue Book to Member
                int memberID, bookID;
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;
                std::cout << "Enter Book ID: ";
                std::cin >> bookID;

                library.issueBook(memberID, bookID);
                break;
            }
            case 4: {
                // Return Book from Member
                int memberID, bookID;
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;
                std::cout << "Enter Book ID: ";
                std::cin >> bookID;

                library.returnBook(memberID, bookID);
                break;
            }
            case 5: {
                // Display Books Borrowed by Member
                int memberID;
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;

                library.displayBorrowedBooks(memberID);
                break;
            }
            case 6: {
                // Calculate Fine for Overdue Books
                int memberID;
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;

                library.calcFine(memberID);
                break;
            }
            case 0:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
