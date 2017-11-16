//Bugs
//#1 FIXED - Infinite loop due to non flushed input
//#2 When entering student grades and then saving it
//#3 FIXED - Enter any other character to terminate program -> replaced else if (choice > 7) with else
//#4 FIXED - Choice 2: Add student - fixed input iss bug 
//#5 FIXED - Function names "serachByName" "serachById" "serachByEmail" replaced with "searchByName" "searchById" "searchByEmail"
//#6 FIXED - Search student by email

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;


static bool IsValidGPA(char value[]) {
	auto intValue = atoi(value);
	return intValue >= 0 && intValue <= 4;
}

static bool IsValidEmail(char value[]) {

	if (value == NULL) return false;

	auto stringValue = std::string(value);

	bool isEmpty = stringValue.length() == 0;
	bool isMissingAtSign = stringValue.find('@') == std::string::npos;
	bool isMissingDot = stringValue.find('.') == std::string::npos;
	bool hasSpace = stringValue.find_first_of("\t\n ") != std::string::npos;
	bool isFirstCharacterAtSign = stringValue[0] == '@';
	bool isFirstCharacterDot = stringValue[0] == '.';

	return !isEmpty && !isMissingAtSign && !isMissingDot && !isFirstCharacterAtSign && !isFirstCharacterDot && !hasSpace;
}

static bool IsValidName(char value[]) {
std:string validCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (value == NULL) return false;

	auto stringValue = std::string(value, sizeof(value));

	bool isEmpty = stringValue.length() == 0;

	bool hasInvalidCharacters = false;
	for (int i = 0; i < stringValue.length() - 1; i++)
	{
		if (stringValue[i] == '\0') break;
		if (validCharacters.find(stringValue[i]) == std::string::npos) {
			hasInvalidCharacters = true;
		}
	}

	return !isEmpty && !hasInvalidCharacters;
}

static bool IsValidID(char value[]) {
std:string validCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	if (value == NULL) return false;

	auto stringValue = std::string(value, sizeof(value));

	bool isEmpty = stringValue.length() == 0;
}


class Student
{
	char name[40];
	char usf_id[10];
	char email[40];
	int gradeOfPresentation;
	int gradeOfEssay;
	int gradeOfProject;
public:
	Student(const char *na, const char *id, const  char * em, int gpre, int ge, int gpro) : gradeOfPresentation(gpre), gradeOfEssay(ge), gradeOfProject(gpro) {
		strcpy(name, na);
		strcpy(usf_id, id);
		strcpy(email, em);
	}

	// Setter and getter methods //

	void setName(char *na) {
		strcpy(name, na);
	}

	char *getName() {
		return name;
	}

	void setId(char *id) {
		strcpy(usf_id, id);
	}

	char *getId() {
		return usf_id;
	}

	void setEmail(char *em) {
		strcpy(email, em);
	}

	char *getEmail() {
		return email;
	}

	void setGradeOfPresentation(int gpre) {
		gradeOfPresentation = gpre;
	}

	int getGradeOfPresentation() {
		return gradeOfPresentation;
	}

	void setGradeOfEssay(int ge) {
		gradeOfEssay = ge;
	}

	int getGradeOfEssay() {
		return gradeOfEssay;
	}

	void setGradeOfProject(int gro) {
		gradeOfProject = gro;
	}

	int getGradeOfProject() {
		return gradeOfProject;
	}

	// Information string //
	string info() {
		ostringstream oss;
		oss << this->getName() << " " << this->getId() << " " << this->getEmail() << " "
			<< this->getGradeOfPresentation() << " " << this->getGradeOfEssay() << " " << this->getGradeOfProject();
		return oss.str();
	}
};

// It's designed to maintain a vector which store the list of student's information
class DataManager {
	vector<Student> studentDatabase;
public:
	DataManager() {}
	// read student into database from file
	void readStudentData(string filename) {
		studentDatabase.clear();
		ifstream fin(filename);
		char temp_name[40];
		char temp_id[40];
		char temp_email[40];
		int gpre, ge, gp;
		while (fin >> temp_name >> temp_id >> temp_email >> gpre >> gp >> ge) {
			/*if (!IsValidName(temp_name) && !IsValidID(temp_id) && !IsValidEmail(temp_email) && !IsValidGPA(gpre) && !IsValidGPA(gp) && !IsValidGPA(ge)) {
				printf("Invalid File");
			}TODO:ASAF*/
			studentDatabase.push_back(Student(temp_name, temp_id, temp_email, gpre, ge, gp));
		}
		fin.close();
	}
	// write data to file
	void writeStudentData(string filename) {
		ofstream fout(filename);
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			fout << it->info() << endl;
		}
		fout.close();
	}

	// add student to database
	void addStudent(Student s) {
		studentDatabase.push_back(s);
	}

	// delete student by id
	bool deleteStudent(char *id) {
		vector<Student>::iterator erasePos = studentDatabase.end();
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				erasePos = it;
				break;
			}
		}
		return studentDatabase.erase(erasePos) == erasePos;
	}

	// search student by name
	void searchByName(char *name) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getName(), name) == 0) {
				cout << it->info() << endl;
				return;
			}
		}
	}

	//search student by id
	void searchById(char *id) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				cout << it->info() << endl;
				return;
			}
		}
	}

	//search student by email
	void searchByEmail(char *email) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getEmail(), email) == 0) {
				cout << it->info() << endl;
				return;
			}
		}
	}

	//update student name
	void updateStudentName(char *id, char *newName) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setName(newName);
				return;
			}
		}
	}

	//update student id
	void updateStudentId(char *id, char *newId) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setId(newId);
				return;
			}
		}
	}

	//update student email
	void updateStudentEmail(char *id, char *newEmail) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setEmail(newEmail);
				return;
			}
		}
	}

	//update student grade of presentation
	void updateStudentGradeOfPresentation(char *id, int grp) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setGradeOfPresentation(grp);
				return;
			}
		}
	}

	//update student grade of essay
	void updateStudentGradeOfEssay(char *id, int ge) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setGradeOfEssay(ge);
				return;
			}
		}
	}

	//update student grade of project
	void updateStudentGradeOfProject(char *id, int gp) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setGradeOfProject(gp);
				return;
			}
		}
	}
};

class TUI {
	DataManager manager;

	string AskFor(string text, bool(*validationFunction)(char[])) {
		char value[40];
		while (true) {
			cout << text;
			cout << "\r\n";

			cin >> value;

			if (!(*validationFunction)(value)) {
				cout << "Incorrect, please try again.";
			}
			else {
				return value;
			}
		}
	}
public:
	void Test() {
		if (!IsValidGPA("4")) throw;
		if (!IsValidGPA("2")) throw;
		if (!IsValidGPA("1")) throw;
		if (!IsValidGPA("0")) throw;
		if (IsValidGPA("-1")) throw;
		if (IsValidGPA("5")) throw;


		char email1[] = { 'a','@','b','.','c' };
		char email2[] = { '@','@','b','.','c' };
		char email3[] = { '.','@','b','.','c' };
		char email4[1] = {};
		char email5[] = { 'a','b','.','c' };
		char email6[] = { 'a','@','c' };
		char email7[] = { 'a',' ','@','b','.' };

		if (!IsValidEmail(email1)) throw;
		if (IsValidEmail(email2)) throw;
		if (IsValidEmail(email3)) throw;
		if (IsValidEmail(email4)) throw;
		if (IsValidEmail(email5)) throw;
		if (IsValidEmail(email6)) throw;
		if (IsValidEmail(email7)) throw;

		char name1[] = { 'a','s','a','f' };
		char name2[] = { 'a','s','a','@' };
		char name3[] = { 'a','s','3','f' };
		char name4[] = { 'a','$','a','f' };
		char name5[] = { 'a','s','a',')' };
		char name6[] = { '#','s','a','f' };
		char name7[] = { '.','s','a','f' };

		if (!IsValidName(name1)) throw;
		if (IsValidName(name2)) throw;
		if (IsValidName(name3)) throw;
		if (IsValidName(name4)) throw;
		if (IsValidName(name5)) throw;
		if (IsValidName(name6)) throw;
		if (IsValidName(name7)) throw;

		char id1[] = { 'a','s','a','f' };
		char id2[] = { 'a','s','a','@' };
		char id3[] = { 'a','s','3','f' };
		char id4[] = { '2','1','4','f' };

		if (!IsValidID(id1)) throw;
		if (!IsValidID(id2)) throw;
		if (!IsValidID(id3)) throw;
		if (!IsValidID(id4)) throw;


	}
	//read file to initialize the database
	TUI() {
		string file;
		cout << "Please enter the data/file/name.txt to initialize the database: ";
		cin >> file;
		manager.readStudentData(file);
	}

	//The system's running logic
	void run() {
		while (true) {
			cout << "1.- Write students' data to file" << endl;
			cout << "2.- Add student" << endl;
			cout << "3.- Delete student by id" << endl;
			cout << "4.- Search student by name" << endl;
			cout << "5.- Search student by id" << endl;
			cout << "6.- Search student by email" << endl;
			cout << "7.- Update student info" << endl;
			cout << "Please select your choice or enter any other value to terminate the program: ";
			int choice;
			cin >> choice;
			cin.get();
			if (choice == 1) {
				string output = AskFor("Please enter the output / file / name.txt: ", &IsValidName);

				manager.writeStudentData(output);
				cout << "Done!" << endl << endl;
			}
			else if (choice == 2) {
				cout << "Please enter the student's information.";
				string name = AskFor("Name: ", IsValidName);
				string id = AskFor("ID: ", IsValidID);
				string email = AskFor("Email: ", IsValidEmail);
				string presentationGPA = AskFor("Presentation Grade: ", IsValidGPA);
				string essayGPA = AskFor("Essay Grade: ", IsValidGPA);
				string projectGPA = AskFor("Project Grade: ", IsValidGPA);

				int i_presentationGPA = stoi(presentationGPA);
				int i_essayGPA = stoi(essayGPA);
				int i_projectGPA = stoi(projectGPA);

				manager.addStudent(Student(name.c_str(), id.c_str(), email.c_str(), i_presentationGPA, i_essayGPA, i_projectGPA));
				cout << "Done!" << endl << endl;
			}
			else if (choice == 3) {

				string id = AskFor("Please enter the student's id:", IsValidID);
				
				cin >> id;
				//if (manager.deleteStudent(id) {
					cout << "Delete successfully." << endl;
				//}
				//else {
					cout << "Failed to delete" << endl;
				//}
				cout << endl;
			}
			else if (choice == 4) {
				char name[30];
				do {
					cout << "Please enter the student's name:" << endl;
					cin >> name;
					if (!IsValidName(name)) {
						cout << "\r\nInvalid name, please try again";
					}
				} while (!IsValidName(name));
				manager.searchByName(name);
				cout << "Done!" << endl << endl;
			}
			else if (choice == 5) {
				cout << "Please enter the student's id:" << endl;
				char id[10];
				cin >> id;
				manager.searchById(id);
				cout << "Done!" << endl << endl;
			}
			else if (choice == 6) {
				cout << "Please enter the student's email:" << endl;
				char email[30];
				cin >> email;
				manager.searchByEmail(email);
				cout << "Done!" << endl << endl;
			}
			else if (choice == 7) {
				cout << "Please enter the student's id:" << endl;
				char id[10];
				cin >> id;
				manager.searchById(id);
				cout << "Please enter item you want to update: (1 name, 2 id, 3 email, 4 grade of presentation, 5 grade of essay, 6 grade of project" << endl;
				int item;
				cin >> item;
				cout << "you entered: " << item << endl;

				if (item == 1) {
					char name[40];
					cin >> name;
					manager.updateStudentName(id, name);
				}
				else if (item == 2) {
					char newid[10];
					cin >> newid;
					manager.updateStudentId(newid, id);
				}
				else if (item == 3) {
					char email[40];
					cin >> email;
					manager.updateStudentEmail(id, email);
				}
				else if (item == 4) {
					int temp;
					cin >> temp;
					manager.updateStudentGradeOfPresentation(id, temp);
				}
				else if (item == 5) {
					int temp;
					cin >> temp;
					manager.updateStudentGradeOfEssay(id, temp);
				}
				else if (item == 6) {
					int temp;
					cin >> temp;
					manager.updateStudentGradeOfProject(id, temp);
				}
				cout << "Done!" << endl << endl;
			}
			//Bug fix #3: Changed else if (choice > 7) to else. This terminates
			// the program if a number 1-7 is not entered
			else
			{
				cout << "Terminating program...\n\nSee you later!" << endl;
				exit(0);

			}
			std::cin.clear(); //Bug fix #1
			std::cin.ignore(); //Bug fix #1
		}
	}
};

int main()
{

	TUI managerSystem;
	managerSystem.run();
	return 0;
}
