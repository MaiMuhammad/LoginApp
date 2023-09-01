#include <iostream>
#include<fstream>
#include<string>
#include<regex>
#include <stdio.h>
#include <conio.h>
using namespace std;

bool ret_name=false;
bool ret_email=false;
string user;
string pw;

int main();
bool check_username(string &str){
    regex check_username("[^!@#$&*]+[^0-9]+");
    return regex_match(str,check_username);
}
void check_file(string&input){
    ifstream data("LoginApp.txt");
    string line;
    while(getline(data, line))
    {
        if (line.find(input) != string::npos){
            cout<<"This input exist."<<endl;
            main();
        }
    }
}

bool check_phone_num(string&input){
    regex check_phone_num("[0][1][0125][0-9]+");
    return regex_match(input,check_phone_num);
}
bool check_input(string&input){
    regex check_input("[^ .][a-zA-Z0-9]+@[Gmailgmail]+.[comCom]+[^.]");
    return regex_match(input,check_input);
}
void user_name(){
    fstream data("LoginApp.txt",ios::app);
    string user_name;
    cout<< "Enter the first name : ";
    cin>>user_name;
    user=user_name;
    if(check_username(user_name) ){
        check_file(user_name);
        for (int i=0;i<user_name.size();i++){
            if(isalpha(user_name[i])){
                ret_name=true;
                data<<"User Name: "<<user_name<<"\n";
                data.close();
            }else{
                ret_name=false;
            }
        }
    }
    else{
        cout<<"Invalid username."<<endl;
        main();
    }
}

void phone_num(){
    fstream data("LoginApp.txt",ios::app);
    string pho_num;
    cout<<"Enter phone number : ";
    cin>>pho_num;
    check_file(pho_num);
    int  sum_nums=pho_num.size();
    if(sum_nums==11&&check_phone_num(pho_num)){
        data<<"Phone Number: "<<pho_num<<"\n";
        data.close();
    }else{
        cout<<"Sorry invalid. "<<endl;
        phone_num();
    }
}
void e_mail(){
    fstream data("LoginApp.txt",ios::app);
    string mail_add;
    cout<<"Enter E-mail address as (username21@gmail.com): ";
    cin>>mail_add;
    check_file(mail_add);
    if (check_input(mail_add)){
        ret_email=true;
        data<<"E-mail: "<<mail_add<<"\n";
        data<<"-------------------------------------------------------------"<<"\n";
        data.close();
    }else{
        cout<<"Sorry Invalid E-mail."<<endl;
        e_mail();
    }
}
void Registration(){
    string pass;
    user_name();
    if (ret_name == false) {
        cout << "Sorry, invalid name\n try again" << endl;
        main();
    }
    else {
        fstream data("LoginApp.txt", ios::app);
        cout << "Enter password but (READ THIS RULES First)"<<endl;
        cout << "Password must be at least 8 characters - the more characters, the better\n"
                "A mixture of both uppercase and lowercase letters\n"
                "A mixture of letters and numbers \n"
                "Inclusion of at least one special character, e.g., ! @ # ? ] [ (!! Dont Use Spaces)" << endl;
        cout<<"Enter password : ";
        char ch;
        ch = _getch();
        while (ch != 13) {
            if (ch == 8) {
                if (!pass.empty()) {
                    cout << "\b \b";
                    pass.pop_back();
                }
                ch = _getch();
                continue;
            }
            pass.push_back(ch);
            cout << '*';
            ch = _getch();
            pw=pass;
        }

        bool hasLower = false, hasUpper = false;
        bool hasDigit = false, specialChar = false;
        int n = pass.length();
        for (int i = 0; i < n; i++) {
            if (islower(pass[i]))
                hasLower = true;
            if (isupper(pass[i]))
                hasUpper = true;
            if (isdigit(pass[i]))
                hasDigit = true;
            string normalChars = "abcdefghijklmnopqrstu"
                                 "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
            size_t special = pass.find_first_not_of(normalChars);
            if (special != string::npos)
                specialChar = true;
        }
        if (hasLower && hasUpper && hasDigit &&
            specialChar && (n >= 8))
            cout << endl<<"Strong Password." << endl;
        else {
            cout << "Your password does not strong , Read this Rules again."<<endl;
            cout << "Password must be at least 8 characters - the more characters, the better\n"
                    "A mixture of both uppercase and lowercase letters\n"
                    "A mixture of letters and numbers \n"
                    "Inclusion of at least one special character, e.g., ! @ # ? ] [ (!! Dont Use Spaces)" << endl;
            main();
        }
        check_file(pass);
        string pass2;
        cout << "Please Confirm your password : ";
        ch = _getch();
        while (ch != 13) {
            if (ch == 8) {
                if (!pass2.empty()) {
                    cout << "\b \b";
                    pass2.pop_back();
                }
                ch = _getch();
                continue;
            }
            pass2.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        if ( pass2== pass){
            string row1 = "";
            string row2 = "";
            string row3 = "";

            //Remove spaces
            pass.erase(remove(pass.begin(), pass.end(), ' '), pass.end());
            for (int i = 0; i < pass.length(); ++i) {
                if (i % 4 == 0 || i == 0) {
                    row1 += tolower(pass[i]);
                } else if (i % 2 != 0) {
                    row2 += tolower(pass[i]);
                } else {
                    row3 += tolower(pass[i]);
                }
            }
            data << "Password: " << row1 << row2 << row3 << "\n";
            data.close();
            cout<<endl;
            phone_num();
            e_mail();
            cout <<endl<<"Registering successfully." << endl;
            cout << endl;
            main();
        }
        else if(pass2!=pass){
            cout<<endl;
            cout<<"The password does not match."<<endl;
            cout<<"Try again."<<endl;
            main();
        }
    }
}
void Login(){
    string userName;
    string password;
    cout<<"Enter your User Name: ";
    cin>>userName;
    cout<<"Enter your Password: ";
    char ch;
    ch = _getch();
    while (ch != 13) {
        if (ch == 8) {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
            ch = _getch();
            continue;
        }
        password.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if (user==userName&& pw==password){
        cout<<endl<<"Successful login, welcome "<<userName<<"."<<endl;
        main();
    }
    else{
        cout<<endl<<"Failed login,Try again."<<endl;
        main();
    }
}
void ChangePassword(){
    string OldPass;
    string pass1;
    string pass2;
    cout << "Enter old password: ";
    char ch;
    ch = _getch();
    while (ch != 13) {
        if (ch == 8) {
            if (!OldPass.empty()) {
                cout << "\b \b";
                OldPass.pop_back();
            }
            ch = _getch();
            continue;
        }
        OldPass.push_back(ch);
        cout << '*';
        ch = _getch();
    }

    cout <<endl<< "Enter new password: ";
    ch = _getch();
    while (ch != 13) {
        if (ch == 8) {
            if (!pass1.empty()) {
                cout << "\b \b";
                pass1.pop_back();
            }
            ch = _getch();
            continue;
        }
        pass1.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    cout <<endl<< "Enter the new password again: ";
    ch = _getch();
    while (ch != 13) {
        if (ch == 8) {
            if (!pass2.empty()) {
                cout << "\b \b";
                pass2.pop_back();
            }
            ch = _getch();
            continue;
        }
        pass2.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if(OldPass==pw &&pass2 ==pass1){

        fstream data("LoginApp.txt", ios::app);
        string row1 = "";
        string row2 = "";
        string row3 = "";

        //Remove spaces
        pass1.erase(remove(pass1.begin(), pass1.end(), ' '), pass1.end());
        for (int i = 0; i < pass1.length(); ++i) {
            if (i % 4 == 0 || i == 0) {
                row1 += tolower(pass1[i]);
            } else if (i % 2 != 0) {
                row2 += tolower(pass1[i]);
            } else {
                row3 += tolower(pass1[i]);
            }
        }
        data << "New Password: " << row1 << row2 << row3 << "\n";
        cout <<endl<< "Your password has been changed successfully."<<endl;
        data.close();
        main();

    }
    else {
        cout<<endl<<"Sorry, Try again."<<endl;
        main();
    }
}

int main() {
    int choices;
    cout << "----------Welcome User----------" << endl;
    cout << "--------------Menu--------------" << endl;
    cout << "1) Registration\n2) Login\n3) Change password\n4) Exit" << endl;
    cout << "Enter number from menu: ";
    cin >> choices;
    switch(choices) {
        case 1:
            Registration();
        case 2:
            Login();
        case 3:
            ChangePassword();

        case 4:
            cout<<"Thanks for using our App."<<endl;
            return 0;

        default:
            cout << "INVALID...";
            break;
    }
}
