//Bugs
//#1 FIXED - Infinite loop due to non flushed input
//#2 When entering student grades and then saving it
//#3 FIXED - Enter any other character to terminate program -> replaced else if (choice > 7) with else
//#4 FIXED - Choice 2: Add student - fixed input iss bug 
//#5 FIXED - Function names "serachByName" "serachById" "serachByEmail" replaced with "searchByName" "searchById" "searchByEmail"
//#6 FIXED - Search student by email
//#6 FIXED - Choice 7: Update student (ID) - fixed parameter mismatch for newid and id
//#7 FIXED - Choice 7: Update student (all) - added cout instructions to users asking for input
//#8 FIXED - Choice 7: Update student (all) - When update is sucessful, return the newly updated student to the user
//??? #9 array overflow not prevented
//?? #10 FIXED - errors on delete if student does not exist
//#11 FIXED - Search student by email
//#12 FIXED - input validation across the program

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;





static bool IsValidGrade(char value[]) {
std:string validCharacters = "0123456789.";

	if (value == NULL) return false;

	auto stringValue = std::string(value, sizeof(value));

	bool isEmpty = stringValue.length() == 0;

	bool hasInvalidCharacters = false;
	int periods = 0;
	for (int i = 0; i < stringValue.length(); i++)
	{
		if (stringValue[i] == '\0') break;
		if (validCharacters.find(stringValue[i]) == std::string::npos) {
			hasInvalidCharacters = true;
		}
		if (stringValue[i] == '.') {
			periods++;
		}
	}

	if (isEmpty || hasInvalidCharacters || periods > 1) return false;
	float floatValue = atof(value);
	return floatValue >= 0 && floatValue <= 4;
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
	for (int i = 0; i < stringValue.length(); i++)
	{
		if (stringValue[i] == '\0') break;
		if (validCharacters.find(stringValue[i]) == std::string::npos) {
			hasInvalidCharacters = true;
		}
	}

	return !isEmpty && !hasInvalidCharacters;
}

static bool IsValidStudentMainMenuOption(char value[]) {
std:string validCharacters = "1234567";

	if (value == NULL) return false;

	auto stringValue = std::string(value, sizeof(value));

	bool isEmpty = stringValue.length() == 0;

	bool hasInvalidCharacters = false;
	for (int i = 0; i < stringValue.length(); i++)
	{
		if (stringValue[i] == '\0') break;
		if (validCharacters.find(stringValue[i]) == std::string::npos) {
			hasInvalidCharacters = true;
		}
	}

	return !isEmpty && !hasInvalidCharacters;
}


static bool IsValidFileName(char value[]) {
std:string validCharacters = "0123456789.-_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (value == NULL) return false;

	auto stringValue = std::string(value, sizeof(value));

	bool isEmpty = stringValue.length() == 0;

	bool hasInvalidCharacters = false;
	for (int i = 0; i < stringValue.length(); i++)
	{
		if (stringValue[i] == '\0') break;
		if (validCharacters.find(stringValue[i]) == std::string::npos) {
			hasInvalidCharacters = true;
		}
	}

	return !isEmpty && !hasInvalidCharacters;
}

static bool IsValidID(char value[]) {
std:string validCharacters = "Uu0123456789";
	if (value == NULL) return false;

	auto stringValue = std::string(value, sizeof(value));
	bool isFirstCharacterNotaU = (stringValue[0] != 'u') && (isFirstCharacterNotaU = stringValue[0] != 'U');
	bool isEmpty = stringValue.length() == 0;
	bool hasInvalidCharacters = false;
	for (int i = 0; i < stringValue.length(); i++)
	{
		if (stringValue[i] == '\0') break;
		if (validCharacters.find(stringValue[i]) == std::string::npos) {
			hasInvalidCharacters = true;
		}
	}

	return !hasInvalidCharacters && !isFirstCharacterNotaU && !isEmpty;
}

class Student
{
	char name[40];
	char usf_id[10];
	char email[40];
	float gradeOfPresentation;
	float gradeOfEssay;
	float gradeOfProject;


public:
	void __cdecl copyString(char* dst, int size, const char* src) {
#ifdef _WIN32 || _WIN64
		strcpy_s(dst, size, src);
#else
		strcpy(dst, src);
#endif
	}

	Student(const char *na, const char *id, const char * em, float gpre, float ge, float gpro) : gradeOfPresentation(gpre), gradeOfEssay(ge), gradeOfProject(gpro) {

		copyString(name, 40, na);
		copyString(usf_id, 10, id);
		copyString(email, 40, em);
	}

	// Setter and getter methods //

	void setName(const char *na) {
		copyString(name, 40, na);
	}

	char *getName() {
		return name;
	}

	void setId(const char *id) {
		copyString(usf_id, 10, id);
	}

	char *getId() {
		return usf_id;
	}

	void setEmail(const char *em) {
		copyString(email, 40, em);
	}

	char *getEmail() {
		return email;
	}

	void setGradeOfPresentation(float gpre) {
		gradeOfPresentation = gpre;
	}

	float getGradeOfPresentation() {
		return gradeOfPresentation;
	}

	void setGradeOfEssay(float ge) {
		gradeOfEssay = ge;
	}

	float getGradeOfEssay() {
		return gradeOfEssay;
	}

	void setGradeOfProject(float gro) {
		gradeOfProject = gro;
	}

	float getGradeOfProject() {
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
		float gpre, ge, gp;
		while (fin >> temp_name >> temp_id >> temp_email >> gpre >> gp >> ge) {
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
	bool deleteStudent(const char *id) {
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
	void searchByName(const char *name) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getName(), name) == 0) {
				cout << it->info() << endl;
				return;
			}
		}
	}

	//search student by id
	void searchById(const char *id) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				cout << it->info() << endl;
				return;
			}
		}
	}

	//search student by email
	void searchByEmail(const char *email) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getEmail(), email) == 0) {
				cout << it->info() << endl;
				return;
			}
		}
	}

	//update student name
	void updateStudentName(const char *id, const char *newName) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setName(newName);
				return;
			}
		}
	}

	//update student id
	void updateStudentId(const char *id, const char *newId) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setId(newId);
				return;
			}
		}
	}

	//update student email
	void updateStudentEmail(const char *id, const char *newEmail) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setEmail(newEmail);
				return;
			}
		}
	}

	//update student grade of presentation
	void updateStudentGradeOfPresentation(const char *id, const float grp) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setGradeOfPresentation(grp);
				return;
			}
		}
	}

	//update student grade of essay
	void updateStudentGradeOfEssay(const char *id, float ge) {
		for (vector<Student>::iterator it = studentDatabase.begin(); it != studentDatabase.end(); ++it) {
			if (strcmp(it->getId(), id) == 0) {
				it->setGradeOfEssay(ge);
				return;
			}
		}
	}

	//update student grade of project
	void updateStudentGradeOfProject(const char *id, float gp) {
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
				cout << "The input you provided is incorrect, please try again.\r\n";
			}
			else {
				return value;
			}
		}
	}

public:
	void Test() {


		if (!IsValidGrade("4")) throw;
		if (!IsValidGrade("2")) throw;
		if (!IsValidGrade("1")) throw;
		if (!IsValidGrade("0")) throw;
		if (IsValidGrade("-1")) throw;
		if (IsValidGrade("5")) throw;


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

		string file = AskFor("Please enter the output / file / name.txt: ", &IsValidFileName);

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

			string result = AskFor("Please select your choice or enter any other value to terminate the program (1-7): ", &IsValidStudentMainMenuOption);

			int choice = atoi(result.c_str());

			if (choice == 1) {
				string output = AskFor("Please enter the output / file / name.txt: ", &IsValidFileName);

				manager.writeStudentData(output);
				cout << "Done!" << endl << endl;
			}
			else if (choice == 2) {


				cout << "Please enter the student's information.\r\n";
				string name = AskFor("Name: ", IsValidName);
				string id = AskFor("ID: ", IsValidID);
				string email = AskFor("Email: ", IsValidEmail);
				string presentationGPA = AskFor("Presentation Grade: ", IsValidGrade);
				string essayGPA = AskFor("Essay Grade: ", IsValidGrade);
				string projectGPA = AskFor("Project Grade: ", IsValidGrade);

				float i_presentationGPA = stof(presentationGPA);
				float i_essayGPA = stof(essayGPA);
				float i_projectGPA = stof(projectGPA);

				manager.addStudent(Student(name.c_str(), id.c_str(), email.c_str(), i_presentationGPA, i_essayGPA, i_projectGPA));

				cout << "Done!" << endl << endl;
			}
			else if (choice == 3) {
				string id = AskFor("Please enter the student's id:", IsValidID);

				if (manager.deleteStudent(id.c_str())) {
					cout << "Delete successfully." << endl;
				}
				else {
					cout << "Failed to delete" << endl;
				}
				cout << endl;
			}
			else if (choice == 4) {

				string name = AskFor("Please enter the student's name:", &IsValidName);
				manager.searchByName(name.c_str());
				cout << "Done!" << endl << endl;
			}
			else if (choice == 5) {
				string id = AskFor("Please enter the student's id:", &IsValidID);
				manager.searchById(id.c_str());
				cout << "Done!" << endl << endl;
			}
			else if (choice == 6) {
				string email = AskFor("Please enter the student's email:", &IsValidEmail);
				manager.searchByEmail(email.c_str());
				cout << "Done!" << endl << endl;
			}
			else if (choice == 7) {
				string id = AskFor("Please enter the student's id:", &IsValidID);
				manager.searchById(id.c_str());

				cout << "Please enter item you want to update: " <<
					"(1 name, 2 id, 3 email, 4 grade of presentation, 5 grade of essay, 6 grade of project)." << endl <<
					"Enter 7 to terminate the program." << endl; // Bug fix #11 Allow the user to terminate the program

				string result = AskFor("Please enter a choice (1-7): ", &IsValidStudentMainMenuOption);
				int item = atoi(result.c_str());
				if (item == 1) {
					string name = AskFor("Please enter the student's name:", &IsValidName);
					manager.updateStudentName(id.c_str(), name.c_str());
				}
				else if (item == 2) {
					string newid = AskFor("Please enter the new id: ", &IsValidID);
					manager.updateStudentId(id.c_str(), newid.c_str()); //bug fix #6 fixed id parameters
				}
				else if (item == 3) {
					string email = AskFor("Please enter the new email: ", &IsValidEmail);
					manager.updateStudentEmail(id.c_str(), email.c_str());
				}
				else if (item == 4) {
					string gpre = AskFor("Please enter the new presentation grade: ", &IsValidGrade);
					manager.updateStudentGradeOfPresentation(id.c_str(), atof(gpre.c_str()));
				}
				else if (item == 5) {
					string ge = AskFor("Please enter the new essay grade: ", &IsValidGrade);
					manager.updateStudentGradeOfEssay(id.c_str(), atof(ge.c_str()));
				}
				else if (item == 6) {
					string gro = AskFor("Please enter the new project grade: ", &IsValidGrade);
					manager.updateStudentGradeOfProject(id.c_str(), atof(gro.c_str()));
				}
				else if (item = 7) {
					cout << "Terminating program...\n\nSee you later!" << endl;
					exit(0);
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
