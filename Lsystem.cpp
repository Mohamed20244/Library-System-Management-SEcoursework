#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>

// Class representing a person
class Person {
public:
    Person(std::string name, std::string address, std::string email);
    virtual ~Person();
    virtual std::string getName() const;
    virtual std::string getAddress() const;
    virtual std::string getEmail() const;

private:
    std::string name;
    std::string address;
    std::string email;
};

// Class representing a library member, inheriting from Person
class Member : public Person {
public:
    Member(int memberID, std::string name, std::string address, std::string email);
    int getMemberID() const;
    const std::vector<int>& getBooksBorrowed() const;
    void setBooksBorrowed(int bookID);
    void returnBook(int bookID);

private:
    int memberID;
    std::vector<int> booksBorrowed;
};

// Class representing a book
class Book {
public:
    Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName);
    int getBookID() const;
    std::string getBookDetails() const;
    void returnBook();
    void borrowBook(Member& borrower, time_t dueDate);

    Member* getBorrower() const {
        return borrower;
    }

    time_t getDueDate() const {
        return dueDate;
    }

private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    time_t dueDate;
    Member* borrower;
};

// Class representing a library
class Library {
public:
    void addMember(std::string name, std::string address, std::string email);
    void issueBook(int memberID, int bookID);
    void returnBook(int memberID, int bookID);
    void displayBorrowedBooks(int memberID) const;
    void calcFine(int memberID) const;
    void populateLibraryFromFile(const std::string& filename);

    std::vector<Member*> members;
    std::vector<Book*> books;

private:
    // ... (private member functions if needed)
};

Person::Person(std::string name, std::string address, std::string email)
    : name(name), address(address), email(email) {}

Person::~Person() {}

std::string Person::getName() const {
    return name;
}

std::string Person::getAddress() const {
    return address;
}

std::string Person::getEmail() const {
    return email;
}

Member::Member(int memberID, std::string name, std::string address, std::string email)
    : Person(name, address, email), memberID(memberID) {}

int Member::getMemberID() const {
    return memberID;
}

const std::vector<int>& Member::getBooksBorrowed() const {
    return booksBorrowed;
}

// Add a book to the list of books borrowed by a member
void Member::setBooksBorrowed(int bookID) {
    booksBorrowed.push_back(bookID);
}

// Remove a book from the list of books borrowed by a member
void Member::returnBook(int bookID) {
    for (auto it = booksBorrowed.begin(); it != booksBorrowed.end(); ++it) {
        if (*it == bookID) {
            booksBorrowed.erase(it);
            std::cout << "Book returned successfully.\n";
            return;
        }
    }
    std::cout << "Book with ID " << bookID << " not found in the borrowed books list.\n";
}

Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
    : bookID(bookID), bookName(bookName), authorFirstName(authorFirstName), authorLastName(authorLastName), borrower(nullptr) {}

int Book::getBookID() const {
    return bookID;
}

std::string Book::getBookDetails() const {
    return "Book ID: " + std::to_string(bookID) + ", Book Name: " + bookName + ", Author: " + authorFirstName + " " + authorLastName;
}

void Book::returnBook() {
    borrower = nullptr;
    dueDate = 0;
}

void Book::borrowBook(Member& borrower, time_t dueDate) {
    this->borrower = &borrower;
    this->dueDate = dueDate;
}

// Add a new member to the library
void Library::addMember(std::string name, std::string address, std::string email) {
    Member* newMember = new Member(members.size() + 1, name, address, email);
    members.push_back(newMember);

    std::cout << "Member added successfully.\n";
    std::cout << "Member details:\n";
    std::cout << "ID: " << newMember->getMemberID() << ", Name: " << newMember->getName()
              << ", Address: " << newMember->getAddress() << ", Email: " << newMember->getEmail() << "\n";
}

// Issue a book to a member
void Library::issueBook(int memberID, int bookID) {
    Member* member = nullptr;
    for (Member* m : members) {
        if (m->getMemberID() == memberID) {
            member = m;
            break;
        }
    }

    Book* book = nullptr;
    for (Book* b : books) {
        if (b->getBookID() == bookID) {
            book = b;
            break;
        }
    }

    if (member == nullptr || book == nullptr) {
        std::cout << "Member or Book not found. Unable to issue the book.\n";
        return;
    }

    time_t currentTime = std::time(nullptr);
    time_t dueDate = currentTime + 3 * 24 * 60 * 60;

    book->borrowBook(*member, dueDate);
    member->setBooksBorrowed(bookID);

    std::cout << "Book issued successfully to Member " << memberID << ".\n";
    std::cout << "Due Date: " << std::put_time(std::localtime(&dueDate), "%Y-%m-%d %H:%M:%S") << "\n";
}

void Library::returnBook(int memberID, int bookID) {
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

    member->returnBook(bookID);

    std::cout << "Book returned successfully by Member " << memberID << ".\n";
}

void Library::displayBorrowedBooks(int memberID) const {
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

    const std::vector<int>& borrowedBooks = member->getBooksBorrowed();

    if (borrowedBooks.empty()) {
        std::cout << "Member " << memberID << " has not borrowed any books.\n";
    } else {
        std::cout << "Borrowed books for Member " << memberID << ":\n";
        for (int bookID : borrowedBooks) {
            for (const Book* book : books) {
                if (book->getBookID() == bookID) {
                    std::cout << book->getBookDetails() << "\n";
                    break;
                }
            }
        }
    }
}

void Library::calcFine(int memberID) const {
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

    const std::vector<int>& borrowedBooks = member->getBooksBorrowed();
    if (borrowedBooks.empty()) {
        std::cout << "Member " << memberID << " has not borrowed any books.\n";
    } else {
        time_t currentTime = std::time(nullptr);
        bool finesCalculated = false;

        for (int bookID : borrowedBooks) {
            for (const Book* book : books) {
                if (book->getBookID() == bookID && book->getBorrower() == member) {
                    if (book->getDueDate() < currentTime) {
                        int daysOverdue = static_cast<int>((currentTime - book->getDueDate()) / (24 * 60 * 60));
                        int fine = daysOverdue * 1;

                        std::cout << "Fine for Member " << memberID << " (Book ID " << bookID << "): £" << fine << "\n";
                        finesCalculated = true;
                    }
                    break;
                }
            }
        }

        if (!finesCalculated) {
            std::cout << "No fine calculated for Member " << memberID << ".\n";
        }
    }
}

void Library::populateLibraryFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int bookID;
        std::string bookName, authorFirstName, authorLastName;

        if (ss >> bookID >> std::ws && std::getline(ss, bookName, ',') &&
            std::getline(ss, authorFirstName, ',') && std::getline(ss, authorLastName, ',')) {
            books.push_back(new Book(bookID, bookName, authorFirstName, authorLastName));
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    file.close();
}

// Function to get user choice
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
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }

    return choice;
}

// Main function
int main() {
    Library library;
    library.populateLibraryFromFile("Excel.csv");

    int choice;
    do {
        choice = getChoice();

        switch (choice) {
            case 1: {
                int bookID;
                std::cout << "Enter Book ID: ";
                std::cin >> bookID;

                bool found = false;
                for (Book* book : library.books) {
                    if (book->getBookID() == bookID) {
                        found = true;
                        std::cout << "Book details:\n";
                        std::cout << book->getBookDetails() << "\n";
                        break;
                    }
                }

                if (!found) {
                    std::cout << "Book with ID " << bookID << " not found.\n";
                }
                break;
            }
            case 2: {
                std::string name, address, email;
                std::cout << "Enter Member Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter Member Address: ";
                std::getline(std::cin, address);
                std::cout << "Enter Member Email: ";
                std::getline(std::cin, email);

                library.addMember(name, address, email);
                break;
            }
            case 3: {
                int memberID, bookID;
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;
                std::cout << "Enter Book ID: ";
                std::cin >> bookID;

                library.issueBook(memberID, bookID);
                break;
            }
            case 4: {
                int memberID, bookID;
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;
                std::cout << "Enter Book ID: ";
                std::cin >> bookID;

                library.returnBook(memberID, bookID);
                break;
            }
            case 5: {
                int memberID;
                std::cout << "Enter Member ID: ";
                std::cin >> memberID;

                library.displayBorrowedBooks(memberID);
                break;
            }
            case 6: {
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
