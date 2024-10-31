#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Contact {
  // Write the class
  string _name;
  string _number;

public:
  Contact(string name, string number) {
    _name = name;
    _number = number;
  };

  string getName() {
    return _name;
  };

  string getNumber() {
    return _number;
  };

  void Display() {
    cout << _name << "," << _number << endl;
  };
};

class ContactBook {

  static const int _maxsize = 100;
  unsigned int _currentsize = 0; //default is 0
  Contact* _contacts[_maxsize]; //creates array of contact pointers

public:
  ContactBook(); //default constructor

  //void DisplayArray(); //custom array. delete when done


  void Set(const ContactBook& otherContactBook); //custom function by me. void function created to assign the current size and maxsize to different instances of the class

  ContactBook(const ContactBook& otherContactBook); //copy constructor. constructs a new object as a copy of another

  ContactBook& operator=(const ContactBook& otherContactBook); //copy assignment operator. overwrites object values

  Contact* Find(const string& s); //takes a string that's either a phone number or name and returns the found contact as a pointer.

  void Add(Contact& ContactObj); //takes a contact object and stores its memory address to the furthest empty position in the array

  void AddContacts(vector<Contact*>& VectorOfContacts); //takes in a vector of contact pointers and stores all its values in the class' array

  void Remove(Contact& ContactObj); //takes a contact object and removes it from the array

  void Display(); //displays each contact in the contact book in the order they are stored in the array


  void Alphabetize(); //sorts the array in alphabetical order based on correct name

  //operators
  ContactBook& operator+=(Contact& NewContact); //Adds a single contact to a ContactBook object

  ContactBook& operator+=(const ContactBook& OtherBook); //Adds all contacts passed in ContactBook to this object

  ContactBook& operator+(const ContactBook& OtherBook); //Adds two contact books together and returns the resulting contact book

  ContactBook& operator-=(Contact& RemovableContact); //Removes the contact that matches the passed-in contact

  ContactBook& operator-=(const ContactBook& OtherBook); //removes all contacts from a passed in ContactBook from this

  ContactBook operator-(const ContactBook& OtherBook); //removes all contacts a passed in ContactBook, but returns a new object as the result instead of modifying the current one

  bool operator==(const ContactBook& OtherBook); //checks if two contact books have the same contacts in them, in any order

  bool operator!=(const ContactBook& OtherBook);

};


