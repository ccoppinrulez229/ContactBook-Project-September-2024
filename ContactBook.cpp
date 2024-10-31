#include "ContactBook.h"
#include <algorithm>

ContactBook::ContactBook() {}; //default constructor

void ContactBook::Set(const ContactBook& otherContactBook) { //Set function can be called at any time to assign another instance of the ContactBook class' values to the current instance.
  _currentsize = otherContactBook._currentsize; //current size is assigned
  _contacts[_maxsize] = otherContactBook._contacts[otherContactBook._maxsize]; //contact array is assigned
}

ContactBook::ContactBook(const ContactBook& otherContactBook) { //copy constructor
  //_maxsize = otherContactBook._maxsize;
  Set(otherContactBook); //will mainly just set values to the other contact book's copy
};

ContactBook& ContactBook::operator=(const ContactBook& otherContactBook) { //copy assignment operator
  //_maxsize = otherContactBook._maxsize;
  Set(otherContactBook);

  //we must create a deep copy to ensure data isnt lost when deleting a previous instance of the class
  for (int i=0 ; i<_maxsize ;i++) { //we first iterate through the entire contact array and delete each contact pointer
    delete _contacts[i];
  }

  for (int i=0 ; i<_maxsize ;i++) { //we then copy each contact pointer of the other class instance to this one
    _contacts[i] = new Contact(*otherContactBook._contacts[i]);
  }
  return *this; //*this is returned, which will overwrite the current class instance's values
};

Contact* ContactBook::Find(const string& s) {
  for (int i=0 ; i<_currentsize ; i++) { //iterates through contacts array
    if (s == _contacts[i]->getName()) { //uses -> to access this specific contact pointer's class function
      return _contacts[i]; //if the contact's name matches the string, return the contact's pointer
    }
    if (s == _contacts[i]->getNumber()) {
      return _contacts[i]; //if the contact's number matches the string, return the contact's pointer
    }
  }

  return nullptr; //if the above loop exhausts, return nullpointer, as no contact's name or number matches the string.

};

void ContactBook::Add(Contact& ContactObj) { //passes by pointer
  _contacts[_currentsize] = &ContactObj;
  _currentsize = _currentsize + 1;

};

//void ContactBook::DisplayArray() {
  //cout << "Memory address: " << _contacts[0] << endl;
  //cout << _contacts[0]->getName() << ", " << _contacts[0]->getNumber() << endl;

  //cout << "Memory address: " << _contacts[1] << endl;
  //cout << _contacts[1]->getName() << ", " << _contacts[1]->getNumber() << endl;
//};

void ContactBook::AddContacts(vector<Contact*>& VectorOfContacts) {
  for (int i=0 ; i<VectorOfContacts.size() ; i++) { //iterates through entire vector
    _contacts[_currentsize] = VectorOfContacts[i]; //assigns current vector object to array position
    _currentsize = _currentsize + 1; //array's current size increases by 1
  }
};

void ContactBook::Remove(Contact& ContactObj) {
  int final_i_position=0; //used to keep track of the position where the contact was removed
  for (int i=0 ; i<_currentsize ; i++) { //iterates through entire static array
    if (_contacts[i] == &ContactObj) { //if an iterated contact's pointer matches the taken in object memory address...
      _contacts[i] = nullptr; //sets that contact pointer to null
      final_i_position = final_i_position + i; //final i position is updated to the current position
      break; //loop is exhausted
    }
  }

  //after removing a contact, we then need to shift the rest of the objects back one place
  for (int i=final_i_position ; i< _maxsize ; i++) { //iterates through static array starting at the final i position
    _contacts[i] = _contacts[i+1]; //first sets the current position to the following object pointer
    _contacts[i+1] = nullptr; //sets the following object pointer to null.
  }

  _currentsize = _currentsize - 1; //when all is done, reduce currentsize variable by 1 to balance it all out
};

void ContactBook::Display() {
  for (int i=0 ; i<_currentsize ; i++) { //iterates through current size of the array and displays the info
    cout << _contacts[i]->getName() << ", " << _contacts[i]->getNumber() << endl;
  }
};


void ContactBook::Alphabetize() {
  auto first = _contacts;
  auto last = _contacts + _currentsize;

  auto comp = [](Contact* a,Contact* b) {
    return a->getName() < b->getName();
  };

  sort(first,last,comp);
};


//operators

ContactBook& ContactBook::operator+=(Contact& NewContact) {
  this->Add(NewContact); //Adds a single contact to this specific object when += with a contact object
  return *this;
};

ContactBook& ContactBook::operator+=(const ContactBook& OtherBook) {
  for (int i=0 ; i< OtherBook._currentsize ; i++) { //iterates through the entire contact list for the other object instance
    this->_contacts[this->_currentsize] = OtherBook._contacts[i]; //assigns contact to new positions in this instance of the contact book
    this->_currentsize += 1; //this instance's current size increases by 1
  }
  return *this;
};

ContactBook& ContactBook::operator+(const ContactBook& OtherBook) {
  for (int i=0 ; i< OtherBook._currentsize ; i++) { //iterates through the entire contact list for the other object instance
    this->_contacts[this->_currentsize] = OtherBook._contacts[i]; //assigns contact to new positions in this instance of the contact book
    this->_currentsize += 1; //this instance's current size increases by 1
  }
  return *this;
};

ContactBook& ContactBook::operator-=(Contact& RemovableContact) {
  this->Remove(RemovableContact); //calls the Remove function to remove the contact object from the content book
  return *this;
};

ContactBook& ContactBook::operator-=(const ContactBook& OtherBook) {
  for (int i=0 ; i < OtherBook._currentsize ; i++) { //iterates through entire contact list of other object instance
    this->Remove(*OtherBook._contacts[i]);  //calls the Remove function to remove the specific contact object iteration
  }
  return *this;
};

ContactBook ContactBook::operator-(const ContactBook& OtherBook) { //returns an actual object; not a reference.
  ContactBook newobj; //newobj ContactBook instance created

  for (int i=0 ; i < OtherBook._currentsize ; i++) { //iterates through entire contact list of other object instance
    this->Remove(*OtherBook._contacts[i]);  //calls the Remove function to remove the specific contact object iteration
  }

  newobj+=*this; //this ContactBook instance's contacts are added to the newobj ContactBook instance.

  return newobj; //a new ContactBook object is returned.
};

bool ContactBook::operator==(const ContactBook& OtherBook) {
  bool identical= true; //bool variable initialized, starting off as true
  int foundcontacts=0; // foundcontacts variable initialized, which will keep track of how many variables are found in both arrays
  if (this->_currentsize == OtherBook._currentsize) { //first checks if the both contact books contain the same amount of contacts, prompting for further checks
    for (int i=0 ; i < this->_currentsize ; i++) { //for loop will allow for position checks at the object book instances
      for (int j=0 ; j < this->_currentsize ; j++) { //nested for loop will compare every contact in the other object book instance to the current contact iterated.
        if (this->_contacts[i] == OtherBook._contacts[j]) { //if both contacts match, increase found contacts by 1.
          foundcontacts = foundcontacts + 1;
        }
      }
    }
  }
  else { //if the contact lists are not the same current length, then we now they wont have the same amount of contacts. thus, it can now be changed to false
    identical=false;
  }
  if (foundcontacts != this->_currentsize) { //if the amount of found contacts does not match the current size of the contact book, set identical to false
    identical = false;
  }

  return identical; //if enough identical contacts are found, true will be passed.
};

bool ContactBook::operator!=(const ContactBook& OtherBook) {
  return !(*this==OtherBook);
};