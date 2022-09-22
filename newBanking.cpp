#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
 
using namespace std;


class account_query {
	private:
		char account_number[20];
		char firstName[10];
		char lastName[10];
		float total_Balance;
	public:
		void read_data();
		void show_data();
		void write_rec();
		void read_rec();
		void search_rec();
		void edit_rec();
		void delete_rec();
		void trans_rec();
		bool check_dup();
		void read_accn();
};


bool account_query::check_dup() {
	string acn;
	ifstream infile;
	infile.open("record.bank", ios::in|ios::binary);
	cout << "\n\tPlease ENTER new account number to register: "; cin >> acn;
	while (infile.read((char *)this, sizeof(*this))) {
		if (account_number == acn) {
			cout <<"\n\tAccount Number " << acn << " belong to an existing account." << endl;
			cout <<"\tPlease choose anyother account number.\n"<< endl;
			return true;
		}
	}
	strcpy(account_number, acn.c_str());
	return false;

};


void account_query::read_accn() {
	cout << "\n\tEnter First Name: ";
	cin >> firstName;
	cout << "\tEnter Last Name: ";
	cin >> lastName;
	cout << "\tEnter Balance: ";
	cin >> total_Balance;
	cout << endl;
};

void account_query::read_data() {
	cout << "\nEnter Account Number: ";
	cin >> account_number;
	cout << "Enter First Name: ";
	cin >> firstName;
	cout << "Enter Last Name: ";
	cin >> lastName;
	cout << "Enter Balance: ";
	cin >> total_Balance;
	cout << endl;
};

void account_query::show_data() {
	cout << "Account Number: " << account_number << endl;
	cout << "First Name: " << firstName << endl;
	cout << "Last Name: " << lastName << endl;
	cout << "Current Balance: Rs. " << total_Balance << endl;
	cout << "---------------------------" << endl;
};

void account_query::write_rec() {
	string acn;
	if (!check_dup()) {
		ofstream outfile;
		outfile.open("record.bank", ios::binary|ios::app);
		read_accn();
		outfile.write((char *)this, sizeof(*this));
		outfile.close();
	}
	else {
		write_rec();
	}
};

void account_query::read_rec() {
	ifstream infile;
	infile.open("record.bank", ios::binary);
	if (!infile) {
		cout << "Error in Opening! File Not Found!!" << endl;
		return;
	}
	cout << "\n****Data from file****" << endl;
	while (!infile.eof()) {
		if (infile.read((char *)this, sizeof(*this))) {
			show_data();
		}
	}
	infile.close();
};


void account_query::search_rec() {
	int n;
	fstream infile;
	infile.open("record.bank", ios::binary|ios::in);
	if (!infile) {
		cout << "\nError in opening! File Not Found!!" << endl;
		return;
	}
	infile.seekg(0);
	string acn; int srch = 0;
	cout << "\n Enter Account Number to search: "; cin >> acn;
	while (!infile.eof()) {
		infile.read((char *)this, sizeof(*this));
		if (account_number == acn) {
			cout << "\n---------------------------" << endl; 
			cout << "\nDetail for the Account Number: " << account_number << endl;
			cout << endl;
			show_data();
			srch += 1;
		}
	}
	if (srch == 0) {
		cout << "\n\tAccount Number is not Registered!" << endl;
		cout << endl;
	}
};

void account_query::edit_rec() {
	int n;
	fstream iofile;
	iofile.open("record.bank", ios::in | ios::binary);
	if (!iofile) {
		cout << "\n Error in opening file! File Not Found!!" << endl;
		return;
	}

	iofile.close();
	ofstream iofile2;
	string acn; int srch = 0;
	cout << "\n Enter Account Number to EDIT: "; cin >> acn;
	iofile.open("record.bank", ios::out|ios::in|ios::binary);
	iofile2.open("temp.bank", ios::binary|ios::app);
	iofile.seekg(0, ios::beg);
	while (iofile.read((char *)this, sizeof(*this))) {
		if (account_number == acn && srch < 1) {
			show_data();
			cout << "\nEnter data to Modify: " << endl;
			read_data();
			iofile2.write((char *)this, sizeof(*this));
			srch += 1;
		}
		else {
			iofile2.write((char *)this, sizeof(*this));
		}
	}
	if (srch == 0) {
		cout << "\n\tAccount Number is not Register!" << endl << endl;
	}
	iofile2.close();
	iofile.close();
	rename("record.bank", "record2.bank");
	rename("temp.bank", "record.bank");
};

void account_query::delete_rec() {
	int n = 0;
	fstream infile, tmpfile;
	infile.open("record.bank", ios::in|ios::binary);
	tmpfile.open("tmpfile.bank", ios::out|ios::binary);
	if (!infile) {
		cout << "\nError in opening, File Not Found!!" << endl;
		return;
	}
	infile.seekg(0);
	//-----------
	string acn; int srch = 0;
	cout << "\n\tEnter Account Number: "; cin >> acn;
	while (infile.read((char *)this, sizeof(*this))) {
		n ++;
		if (account_number == acn) {
			srch += 1;
			continue;
		}
		tmpfile.write((char *)this, sizeof(*this));
	}
	if (srch == 0) {
		cout << "\tAccount Number is not Registered!" << endl << endl;
	}

	infile.close();
	tmpfile.close();
	remove("record.bank");
	rename("tmpfile.bank", "record.bank");
	cout << "\n\tAccount " << acn << " has been deleted successfully!" << endl;
};


void account_query::trans_rec() {
	int n = 0;
	fstream iofile;
	iofile.open("record.bank", ios::in | ios::binary);
	if (!iofile) {
		cout << "\n Error in opening file! File Not Found!!" << endl;
		return;
	}
	iofile.seekg(0);

	string acn; int srch = 0;
	cout << "\n\tEnter Account Number: "; cin >> acn;
	while (iofile.read((char *)this, sizeof(*this))) {
		n ++;
		if (account_number == acn) {
			srch += 1;
			break;
		} 
	}
	if (srch == 0) {
		cout << "\tAccount Number is not Registered!" << endl << endl;
		trans_rec();
	}


	
	else if (srch > 0) {
		iofile.seekg((n-1)*sizeof(*this));
		iofile.read((char *)this, sizeof(*this));
		cout << "\n\n\tAccount Number " << acn << " has following data" << endl;
		cout << "\n---------------------------" << endl;
		show_data();
		iofile.close();
		iofile.open("record.bank", ios::out|ios::in|ios::binary);
		iofile.seekp((n-1)*sizeof(*this));
		char type;
		float wdrl; float cred;
		cout << "\nEnter Type of Transaction: \n\t1: Withdrawal\n\t2: Credit\n\t3: Main Menu  " << endl;
		cout << "\n\tYour Choice: "; cin >> type;
		if (type == '1') {
			cout <<"\n\tEnter the Withdrawal Amount: "; cin >> wdrl;
			if (wdrl > total_Balance) {
				cout <<"\nYou don't have enough balance to make this transaction." << endl;
				cout << "Please try again." << endl;
			}
			else {
				total_Balance -= wdrl;
				iofile.write((char *)this, sizeof(*this));
				cout <<"\n\nAccount has been updated successfully! Make sure everything is correct.\n" << endl;
				cout << "\n---------------------------" << endl; 
				show_data();
			}
		}
		else if (type == '2') {
			cout << "\n\tEnter the Credit Amount: "; cin >> cred;
			total_Balance += cred;
			iofile.write((char *)this, sizeof(*this));
			cout << "Account has been updated successfully! Make sure everything is correct.\n" << endl;
			cout << "\n---------------------------" << endl; 
			show_data();
		}
		else if (type == '3') {
			cout << endl;
		}
		else {
			cout << "\n\tEntered choice is Invalid! Please try again." << endl;
			trans_rec();
		}
	}
}
 
 
int main() {
	account_query A;
	int choice;
	cout << "\n****Account Information System****" << endl;
	while (true) {
		cout << "\n\nSelect one of the Options below.";
		cout << "\n\t1: Add Record to the System";
		cout << "\n\t2: Show Records of the System";
		cout << "\n\t3: Search Record from the System";
		cout << "\n\t4: Update Record";
		cout << "\n\t5: Delete Record";
		cout << "\n\t6: Make Transaction";
		cout << "\n\t0: Quit";
		cout << "\n\n\tEnter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				A.write_rec();
				break;
			case 2:
				A.read_rec();
				break;
			case 3:
				A.search_rec();
				break;
			case 4:
				A.edit_rec();
				break;
			case 5:
				A.delete_rec();
				break;
			case 6:
				A.trans_rec();
				break;
			case 0:
				exit(0);
				break;
			default:
				cout << "\nPlease Enter the correct choice. Try Again!";
				cout << endl << endl;
				exit(0);
		}

	}
	system("pause");
    
    return 0;
}
