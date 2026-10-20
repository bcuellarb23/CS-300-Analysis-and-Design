// ===========================
// Developer:Bryan Cuellar
// ===========================

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits.h>
#include <sstream>
#include <map>

using namespace std;

const unsigned int DEFAULT_SIZE = 17;

// Structure to hold Course data
struct Course {
  string id; 
  string title;
  vector<string> prereq;

  // Default Constructor I had to add it, the error log said that the Node struct were creating a course but Course were expecting arguments 
  Course() {
    id = "";
    title = "";
  }

  // Constructur with arguments 
  Course(string aId, string aTitle, vector<string> aPrereq) {
    id = aId;
    title = aTitle;
    prereq = aPrereq;
  }
};

// This is my class for the HashTable
class HashTable {
private:
  struct Node {
    Course course;
    unsigned int key;
    Node* next;

    // Default constructor
    Node() {
      key = UINT_MAX;
      next = nullptr;
    }

    // Initialize 
    Node(Course aCourse) : Node() {
      course = aCourse;
    }

    Node(Course aCourse, unsigned int aKey) : Node(aCourse) {
      key = aKey;
    }
  };

  vector<Node> nodes;
  unsigned int tableSize = DEFAULT_SIZE;
  unsigned int hash(string id);
  
public:
  HashTable();
  HashTable(unsigned int size);
  ~HashTable();
  void loadAndValidate(string fileName); 
  void Insert(Course course);
  void PrintAll();
  Course Search(string id);
  void displayaCourse(Course course);
};

// Default Constructor
HashTable::HashTable() {
  nodes.resize(tableSize);
}

// Constructor for specific size of the table, reduce memory waste
HashTable::HashTable(unsigned int size) {
  this->tableSize = size;
  nodes.resize(size);
}

// Destructor so I avoid memory leaks. 
HashTable::~HashTable() {
  for (Node& head : nodes) {
    Node* current = head.next; // Start with the first dynamically allocated node
    while (current != nullptr) {
      Node* nextNode = current->next;
      delete current;
      current = nextNode;
    }
  }
}

// Calculate the hash value of a given key 
unsigned int HashTable::hash(string id) {
  int key;

  // Need to conver the id into a integer since my hash need an integer to get a key
  for (char c : id) {
    key += c;
  }
  
  return key % tableSize;
}


// Read Validate and Parser
void HashTable::loadAndValidate(string fileName) {
  ifstream file(fileName);

  // Check if the file was opened
  if(!file.is_open()) {
    cerr << " Could not open the file named: " << fileName << endl;
  }

  else {
    // Get lines from the file 
    string line;
    while (getline(file, line)) {
      stringstream ss(line);
      string element;
      vector<string> tokens;

      // Get every word from the line and push them back to the token vector
      while (getline(ss, element, ',')) {
        tokens.push_back(element);
      }

      // handle error first 
      if (tokens.size() < 2) {
        cerr << " The line must have at least course Id and title" << endl;
        file.close();
        break;
      }
      else {
        string id = tokens[0];
        string title = tokens[1];
        vector<string> prereq;

        for (size_t i = 2; i < tokens.size(); ++i) {
          string req = tokens[i];
          if (!req.empty() && req.back() == '\r'){
            req.pop_back();
          }
          if (!req.empty()) {
            (prereq.push_back(req));
          }
        }

        // I used a initializer with this form so inserting a course is easier
        Course curCourse(id, title, prereq);
        Insert(curCourse);
      }
    }
    
    cout << " Data successfully loaded into memory." << endl;
    file.close();
  }

}

void HashTable::Insert(Course course) {
  // Hash the key first it will be needed
   unsigned int key = hash(course.id);

  // Get a Node by using the key
  Node* oldNode = &(nodes.at(key));

  if (oldNode->key == UINT_MAX) {
    oldNode->key = key;
    oldNode->course = course;
    oldNode->next = nullptr;
  }
  else {
    while (oldNode->next != nullptr) {
      oldNode = oldNode->next;
    }
    oldNode->next = new Node(course, key);
  }
}

void HashTable::PrintAll() {
  map<string, Course> sortedMap;
  
  // Loop trhough the table's internal nodes to gather all courses
  for (const auto& node : nodes) {
    if (node.key != UINT_MAX) {
      sortedMap[node.course.id] = node.course;
    }
  }

  //iterate throgh the sorted map to print the courses  
  for (const auto& pair : sortedMap) {
    cout << " " << pair.first << ": " << pair.second.title << endl;
  }
}

// Search function to look for a course this returns a course 
Course HashTable::Search(string id) {
  Course course;

  unsigned int key = hash(id);
  Node* current = &(nodes.at(key));
  if (current->key == UINT_MAX) {
    return course;
  }

  while (current != nullptr) {
    if (current->course.id == id) {
      return current->course;
    }
    current = current->next;
  }
  return course;
}

void HashTable::displayaCourse(Course course) {
  cout << " " << course.id << ": " << course.title << endl;
  cout << " Prerequisites: ";

  if (course.prereq.empty()) {
    cout << "None";
  }
  else {
    
    // Iterates to print all my prerequisites 
    for (size_t i = 0; i < course.prereq.size(); ++i) {
      cout << course.prereq[i];
      // If there are more prereq print , to make look prettier
      if ( i < course.prereq.size() - 1){
        cout << ", ";
      }
    }
  }
  cout << endl;
}

// ======================================
// Main method
// ======================================

int main(int argc, char* argv[]) {
  
  // Definition of the hash table to hold the courses
  HashTable* courseTable;
  
  Course course;
  courseTable = new HashTable();
  cout << "Welcome to the course planner." << endl;

  int choice = 0;
  // Loop until the user types 9 
  while (choice != 9) {
    cout << "=======================" << endl;
    cout << "Menu:" << endl;
    cout << "1. Load Courses." << endl;
    cout << "2. Show a Course List." << endl;
    cout << "3. Look for a Course." << endl;
    cout << "9. Exit." << endl;
    cout << "=======================" << endl;
    cout << "What Would you Like to Do: " << endl;
    cin >> choice;
    
    // Check my input, in case the user uses anything else the app does not starts an infinite loop
    if (!cin >> choice) {
      cin.clear();
      cin.ignore();
      cout << "Invalid input. Please enter a valid number." << endl;
    }

    // Switch forn the main menu
    switch (choice) {
      case 1: {
                string fileName;
                cin.ignore();
                cout << "What is the name of the file you want to read?: ";
                getline(cin, fileName);
                courseTable->loadAndValidate("data/" + fileName);
                break;
              }

      case 2: {
                courseTable->PrintAll();
                break;
              }

      case 3: {
                string code;
                cout << "Type the code of the course you want to look for: ";
                cin >> code;
                Course course = courseTable->Search(code);
                if (course.id.empty()) {
                  cout << "Course not found." << endl;
                  break;
                }
                else {
                  courseTable->displayaCourse(course);
                  break;

                }
              }

      case 9: {
                // Free the alocated memory 
                delete courseTable;
                cout << "Thank you for using the course planner." << endl;
                break;
              }

      default:
              cout << "   " << choice << " is not a valid option." << endl;
              break;
    }
  }
}
