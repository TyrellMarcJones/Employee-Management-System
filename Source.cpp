#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include<vector>
#include<string.h>
#include <iomanip> 

using namespace std;

class Employee {              //Base Employee Class

private:
	string emplPass;          //User Password

public:			              //Access Specifier
	string emplName;          //Employee Name
	string emplID;            //Employee ID
	string emplType;          //Employee Type

	int setPassword(string password) {
		emplPass = (password);
		return 1;
	}

	string returnPass() {
		return emplPass;
	}

	int checkPassword(string passwordInput) {
		if (emplPass == passwordInput) {
			cout << "passwords match" << endl;
			return 1;
		}

		else {
			cout << "Incorrect Password" << endl;
			return 0;

		}
	}
};

/* Parses string supplied to the function and returns vector based off delimiter "," found in string */
vector<string> stringParser(string inputString) {
	string my_str = inputString;
	vector<string> result;
	stringstream s_stream(my_str);

	while (s_stream.good()) {
		string substr;
		getline(s_stream, substr, ',');
		result.push_back(substr);
	}

	return result;
}

/*Deletes Employee from emplFiles.txt */
void deleteEmployee(string userID, bool userSelect = false, int selectedLine = 0) {

	string employeeRecord;
	ifstream emplFiles("emplFiles.txt");
	vector<Employee> vecObj;

	int lineCounter = 1;
	int userlineMatch = 0;
	Employee userMatch;

	while (getline(emplFiles, employeeRecord)) {
		vector<string> employee = stringParser(employeeRecord);
		Employee user;
		cout << lineCounter;
		user.emplID = employee[1];
		user.emplName = employee[0];
		user.emplType = employee[2];

		if (userID == user.emplID) {
			userMatch = user;
			userlineMatch = lineCounter;
		}

		cout << user.emplName << user.emplID << user.emplType << endl;

		user.setPassword(employee[3]);
		vecObj.push_back(user);
		lineCounter++;
	}

	emplFiles.close();

	if (userlineMatch > 0) {
		string deleteChoice;
		ofstream writeFiles;
		writeFiles.open("emplFiles.txt");

		if (userSelect == true) {
			cout << "Removing User " << endl;
			cout << "----------------------- " << endl;
			cout << "Employee Name " << userMatch.emplName << endl;
			cout << "Empoyee ID " << userMatch.emplID << endl;
			cout << "Employee Title " << userMatch.emplType << endl << endl;
			cout << "Would you like to continue? Enter y or n." << endl;
			cin >> deleteChoice;
		}

		else {
			deleteChoice = "y";
		}

		if (deleteChoice == "y") {
			for (int i = 0; i < vecObj.size(); i++)
				if (i != userlineMatch - 1)
					writeFiles << vecObj[i].emplName << "," << vecObj[i].emplID << "," << vecObj[i].emplType << "," << vecObj[i].returnPass() << "," << endl;
		}

		else {
			cout << "Did not delete" << endl;
		}
	}
	else {
		cout << "Could not delete. Selected user not Found" << endl;
	}

}

/* gets Employee data from the EmplFiles.txt and converts them to a vector of Objects */
vector<Employee> readEmployees(bool displayValues = true) {

	string employeeRecord;
	ifstream emplFiles("emplFiles.txt");
	vector<Employee> vecObj;

	while (getline(emplFiles, employeeRecord)) {
		vector<string> employee = stringParser(employeeRecord);
		Employee user;
		user.emplID = employee[1];
		user.emplName = employee[0];
		user.emplType = employee[2];
		user.setPassword(employee[3]);
		vecObj.push_back(user);
	}

	if (displayValues == true) {
		cout << "Reading Employees:" << endl;
		cout << "----------------------------------------" << endl;
		cout << " " << setw(8);
		cout << left << setw(15) << "Name";
		cout << left << setw(15) << "UserID";
		cout << left << setw(15) << "Type" << endl << endl;
		for (int i = 0; i < vecObj.size(); i++) {
			cout << i + 1 << ". " << setw(8);
			cout << left << setw(15) << vecObj[i].emplName;
			cout << left << setw(15) << vecObj[i].emplID;
			cout << left << setw(15) << vecObj[i].emplType << endl;
		}
	}

	return vecObj;
}

/* Searches emplFiles.txt and matches for arguments */
vector<Employee> employeeSearch(int searchSelect = 0, string employeeID = "0", bool displayMatches = true) {

	string employeeName, employeeTitle;
	string employeeRecord;
	int matchCounter = 0;
	int choice = searchSelect;
	int matchFound = 0;
	ifstream emplFiles("emplFiles.txt");
	vector<Employee> allUsers = readEmployees(false);
	vector<Employee> matchResults;

	if (searchSelect == 0) {
		cout << "Press 1 to search by Employee Name" << endl;
		cout << "Press 2 to search by Employee ID" << endl;
		cin >> searchSelect;

		choice = searchSelect;
	}

	switch (choice) {

	case 1:
		cout << "Search by Employee Name" << endl;
		cout << "Type employee Name" << endl;
		cin >> employeeName;
		cout << "Searching for Employee Name: " << employeeName << endl;

		for (int i = 0; i < allUsers.size(); i++) {
			if (allUsers[i].emplName == employeeName) {
				matchCounter++;
				matchFound = 1;
				if (displayMatches == true) {
					cout << "------------------------" << endl;
					cout << "Result " << matchCounter << endl;
					cout << "User Name: " << allUsers[i].emplName << " UserID: " << allUsers[i].emplID << " User Title: " << allUsers[i].emplType << endl;
					cout << "------------------------" << endl;
				}
				matchResults.push_back(allUsers[i]);
			}
		}

		if (matchFound == 1) {
			return matchResults;
		}

		else if (matchFound == 0) {
			return {};
		}
		break;

	case 2:
		if (employeeID == "0") {
			cout << "Search by Employee ID" << endl;
			cout << "Type employee ID" << endl;
			cin >> employeeID;
		}
		cout << "Searching for Employee ID: " << employeeID << endl;

		for (int i = 0; i < allUsers.size(); i++) {
			if (allUsers[i].emplID == employeeID) {
				matchCounter++;
				matchFound = 1;
				if (displayMatches == true) {
					cout << "------------------------" << endl;
					cout << "Result " << matchCounter << endl;
					cout << "User Name: " << allUsers[i].emplName << " UserID: " << allUsers[i].emplID << " User Title: " << allUsers[i].emplType << endl;
					cout << "------------------------" << endl;
				}
				matchResults.push_back(allUsers[i]);
			}
		}

		if (matchFound == 1) {
			return matchResults;
		}

		else if (matchFound == 0) {
			return {};
		}

		break;
	}
}

/* Writes employee name, id and title to emplFiles.txt */
int writeEmployee(string employeeName, string employeeID, string employeeType, string employeePassword) {

	ofstream emplFiles("emplFiles.txt", ios::app);

	if (emplFiles << employeeName << "," << employeeID << "," << employeeType << "," << employeePassword << endl) {
		return 1;
	}

	else {
		return 0;
	}
}

/* Modify employee name, id and title and write to emplFiles.txt */
void modifyEmployee(string employeeID) {

	Employee modEmpl = employeeSearch(2, employeeID, false)[0];
	string modEmplID = modEmpl.emplID;
	string modEmpName = modEmpl.emplName;
	string modEmplTitle = modEmpl.emplType;
	int editOption;
	bool idMatch = true;
	string newName, newID, newTitle;
	string tempIDdelete = modEmplID;

	cout << "Modifying User" << endl;
	cout << "---------------------" << endl;
	cout << "1. Employee Name: " << modEmpName << endl;
	cout << "2. Employee ID: " << modEmplID << endl;
	cout << "3. Employee Title: " << modEmplTitle << endl << endl;
	cout << "Select what you would like to edit: " << endl;
	cin >> editOption;

	switch (editOption) {

	case 1:
		cout << "Current Name: " << modEmpName << endl;
		cout << "Enter New Name: " << endl;
		cin >> newName;
		modEmpName = newName;
		idMatch = false;

		break;
	case 2:
		cout << "Current Employee ID: " << modEmplID << endl;
		cout << "Enter New ID: " << endl;
		cin >> newID;
		if (employeeSearch(2, newID, false).size() == 0) {
			modEmplID = newID;
			idMatch = false;
		}
		else {
			cout << "UserID must be unique. Please try again." << endl;
		}

		break;
	case 3:
		cout << "Current Employee Title: " << modEmplTitle << endl;
		cout << "Enter New Title: " << endl;
		cin >> newTitle;
		modEmplTitle = newTitle;
		idMatch = false;
		break;
	}

	if (modEmplTitle.empty() != 1 && modEmplID.empty() != 1 && modEmpName.empty() != 1 && idMatch == false) {
		deleteEmployee(tempIDdelete, false);
		writeEmployee(modEmpName, modEmplID, modEmplTitle, modEmpl.returnPass());
	}
}

/* Displays main menu options of the application */
void mainMenu(Employee currentEmployee = {}, int menuSelection = 0) {

	string employeeName;
	string employeeID;
	string employeeTitle;
	string employeePassword;
	string deleteInput;
	string modID;

	if (menuSelection == 0) {
		cout << "-----------------------------------" << endl;
		cout << "Main Menu" << endl << endl;
		cout << "Select your option." << endl << endl;
		cout << "Press 1 to View My Info" << endl;

		if (currentEmployee.emplType == "Manager" || currentEmployee.emplType == "HR" || currentEmployee.emplType == "Admin") {
			cout << "Press 2 to View Users" << endl;
			cout << "Press 3 to Search for user" << endl;
		}

		if (currentEmployee.emplType == "HR" || currentEmployee.emplType == "Admin") {
			cout << "Press 4 to Adding User" << endl;
			cout << "Press 5 to modify a user" << endl;
			cout << "Press 6 to delete a user" << endl;
		}

		cout << "-----------------------------------" << endl;
		cin >> menuSelection;
	}

	switch (menuSelection) {

	case 1:

		cout << endl << "My Info" << endl;
		cout << "-----------------------------------" << endl;
		cout << left << setw(15) << "Name";
		cout << left << setw(15) << "UserID";
		cout << left << setw(15) << "Type" << endl << endl;
		cout << left << setw(15) << currentEmployee.emplName;
		cout << left << setw(15) << currentEmployee.emplID;
		cout << left << setw(15) << currentEmployee.emplType << endl;


		mainMenu(currentEmployee);
		break;


	case 2:

		cout << "View Users" << endl;
		readEmployees();
		mainMenu(currentEmployee);

	case 3:

		cout << "Search for user" << endl;
		employeeSearch();
		mainMenu(currentEmployee);

	case 4:

		cout << "Adding User" << endl;
		cout << "-------------------------" << endl << endl;

		cout << "Enter Employee Name" << endl;
		cin.ignore();
		getline(cin, employeeName);

		cout << "Enter Employee ID" << endl;
		cin >> employeeID;

		cout << "Enter Employee Title" << endl;
		cin.ignore();
		getline(cin, employeeTitle);

		cout << "Enter User Password" << endl;
		cin >> employeePassword;

		if (employeeSearch(2, employeeID, false).size() > 0) {
			cout << "User ID must be unique" << endl;
		}

		if (employeeName.empty() != 1 && employeeTitle.empty() != 1 && employeeID.empty() != 1 && employeePassword.empty() != 1 && employeeSearch(2, employeeID, false).size() == 0) {
			if (writeEmployee(employeeName, employeeID, employeeTitle, employeePassword) == 1) {
				cout << "User Added" << endl;
			}
			else {
				cout << "Error adding user" << endl;
			}
		}
		else {
			cout << "All fields must contain a valid value. Please try again." << endl;
			mainMenu(currentEmployee, 4);
		}

		cout << "Select 1 to return to main menu." << endl;
		cout << "Select 2 to add another user." << endl;
		cin >> menuSelection;

		if (menuSelection == 1) {
			mainMenu(currentEmployee);
		}

		else if (menuSelection == 2) {
			mainMenu(currentEmployee, 4);
		}

		else {
			cout << "No valid option selected. Retunring to main menu." << endl;
			mainMenu(currentEmployee);
		}

	case 5:

		cout << "Modify a user" << endl;
		cout << "Enter User ID" << endl;
		cin >> modID;

		if (employeeSearch(2, modID, false).size() > 0) {
			modifyEmployee(modID);
		}

		else {
			cout << "UserID not found. Please try again." << endl;
		}

		mainMenu(currentEmployee);

	case 6:

		cout << "Delete a user" << endl;
		cout << "--------------" << endl;
		cout << "Enter Employee ID you would like to delete." << endl << endl;
		cin >> deleteInput;

		deleteEmployee(deleteInput, true);
		mainMenu(currentEmployee);
	}
}

/* Checks for minimum users of system. Creates default account if no user exists */
void defaultAdmin() {

	string selectedPassword, defaultAdminBuild;

	if (readEmployees(false).size() == 0) {
		cout << "No Current Users Found in system." << endl;
		cout << "You must create an admin user to use the system for the first time." << endl;
		cout << "Would you like to do that now? Select y to continue or n close program." << endl;

		cin >> defaultAdminBuild;

		if (defaultAdminBuild == "y") {
			cout << "Select your password for AdminUser" << endl;
			cout << "Write this password down. You will not be able to" << endl;
			cout << "retrive this password again." << endl;

			cin >> selectedPassword;

			writeEmployee("AdminUser", "1", "Admin", selectedPassword);
		}
		else {
			cout << "AdminUser not created" << endl;
		}

		if (employeeSearch(2, "1").size() > 1) {
			cout << "Admin User created." << endl;
		}

	}
}

/* Handles user login */
vector<Employee> loginMenu() {

	string loginID;

	if (cin.get() == '\n') {
		cout << "Please Enter Employee ID Number" << endl;
		cin >> loginID;
		cout << "Logging in: " << loginID << endl << endl;

		vector<Employee> matchResult = employeeSearch(2, loginID, false);
		string userPassword;

		if (matchResult.size() > 0) {
			cout << "User " << matchResult[0].emplID << " found" << endl;
			cout << "Input User Password" << endl;
			cin >> userPassword;
			matchResult[0].checkPassword(userPassword);
			return matchResult;
		}

		else {
			cout << "User Not Found" << endl;
			return {};
		}
	}

	else {
		cout << "Incorrect option selected. Please Try Again" << endl << endl;
		return {};
	}
}

/* Displays main function of the application */
int main() {

	string currentUserName;
	string currentUserID;
	string currentUserTitle;
	bool loginPass;
	vector<Employee> currentUser;

	cout << "Study.com Employee Management System" << endl << endl;

	defaultAdmin();

	cout << "Press Enter to log in" << endl;

	do {
		currentUser = loginMenu();
	} while (currentUser.size() == 0);

	if (currentUser.size() > 0) {
		currentUserName = currentUser[0].emplName;
		currentUserID = currentUser[0].emplID;
		currentUserTitle = currentUser[0].emplType;
		cout << "Login successful" << endl;
		cout << "Welcome " << currentUserName << endl;
		loginPass = true;
	}

	else {
		loginPass = false;
	}

	if (loginPass == true) {
		mainMenu(currentUser[0]);
	}
}


