#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<stdlib.h>
#include<windows.h>
#include<vector>
#include<queue>
#include <thread>
#include <chrono>
#define ll long long
#define ull unsigned long long
using namespace std;
using namespace std::chrono;

// Global variables
bool go_in = true;
static bool resp = false;
short mainOpinion, healthOpinion, workOpinion;
pair<string, string>user_data;


void welcome_message();
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : print welcome message for user
*/
pair<bool, bool> check_email(pair<string, string>user_data);
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : check if the user exist in data base or not
*/
bool sign_in_and_up(int option);
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : let user do sign in or sign up in the application
*/
void ask_user_for_email();
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : ask user if he has email or not
*/
void log_out();
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : let user get out from the app
*/
void exercises();
/*
author : mohamed mostafa

date : 20 / 8 / 2024

description : help user to make his exercises
*/
void BMI();
/*
author : salem Alsayed

date : 20 / 8 / 2024

description : allow user to log their BMI (weight , height , and other body metrics) over time.
*/
void CalorieCalculator();
/*
author : salem Alsayed

date : 20 / 8 / 2024

description : calculate calories for user
*/
void pomodoro();
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : help user to use pomodoro technique during study
*/
void calender();
/*
author : salem Alsayed

date : 21 / 8 / 2024

description : print today's date
*/
void quotes();
/*
author : yassin taher

date : 20 / 8 / 2024

description : print quotes to motivate the user
*/
void displaytodo();
/*
author : yassin taher

date : 21 / 8 / 2024

description : display all your tasks which you saved it before
*/
void todo();
/*
author : yassin taher & mohammed mostafa

date : 21 / 8 / 2024

description : take the tasks from the user and save it
*/
void to_do_list();
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : show options of using to-do-list
*/
void health_options();
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : show options of health sections
*/
void work_options();
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : show options of work sections
*/
void main_sections();
/*
author : omar ibrahim

date : 21 / 8 / 2024

description : show main sections in the app
*/




int main() { // omar ibrahim , 21 / 8 / 2024
    ask_user_for_email(); // prompt user to identify himself

    if (resp) {

        welcome_message(); // print welcome message

        while (go_in) {
            main_sections(); // display the main sections
            system("CLS");
            if (mainOpinion == 1) { // choose works section
                work_options();
                system("CLS");
                if (workOpinion == 1) {
                    pomodoro();
                    log_out();
                }
                else if (workOpinion == 2) {
                    calender();
                    log_out();
                }
                else if (workOpinion == 3) {
                    to_do_list();
                    log_out();
                }
                else if (workOpinion == 4) {
                    quotes();
                    log_out();
                }
                else {
                    cout << "\n**** wrong input , please try again *****\n";
                    work_options();
                    system("CLS");
                }
            }
            else if (mainOpinion == 2) { // choose health section
                health_options();
                system("CLS");

                if (healthOpinion == 1) {
                    CalorieCalculator();
                    log_out();
                }
                else if (healthOpinion == 2) {
                    exercises();
                    log_out();
                }
                else if (healthOpinion == 3) {
                    BMI();
                    log_out();
                }
                else {
                    cout << "\n**** wrong input , please try again *****\n";
                    health_options();
                    system("CLS");
                }
            }
            else if (mainOpinion == 3) {
                log_out();
            }
            else {
                cout << "\n**** wrong input , please try again *****\n";
                main_sections();
                system("CLS");
            }
        }
        if (!go_in)
            cout << "ok , let us see you again :)";
    }
}
void welcome_message() { // here intro to app
    string intro_1 = "******************                            WELCOME                           ********************";
    string intro_2 = "******************                        this is Life_Style                    ********************";
    string intro_3 = "******************               the most efficient productivity_app ever       ********************";
    for (int i = 0; i < 100; i++)
        cout << "*";
    cout << endl;

    cout << intro_1 << endl << intro_2 << endl << intro_3;

    cout << endl;
    for (int i = 0; i < 100; i++)
        cout << "*";
    cout << endl << endl << endl;
}

pair<bool, bool> check_email(pair<string, string>user_data) {
    pair<bool, bool>exist(false, false);
    cin.ignore();
    string L_data;
    vector<string>data;
    fstream users("usersInApp.txt"); // open the file to search

    string name, password_compare = "";
    while (getline(users, L_data)) { // get the data in vector , to make search operation easier
        data.push_back(L_data);
    }

    for (int i = 0; i < data.size(); i++) { // search about user name
        stringstream comp(data[i]);
        comp >> name;
        if (name == user_data.first) {
            exist.first = true;
        }
    }

    if (exist.first) {
        // if i found the user name , i will search about password
        for (int i = 0; i < data.size(); i++) {
            password_compare = "";
            for (int j = data[i].size() - 1; data[i][j] != ' '; j--) {
                password_compare += data[i][j];
            }
            reverse(password_compare.begin(), password_compare.begin() + password_compare.size());

            if (password_compare == user_data.second) {
                exist.second = true;

            }
        }
    }

    users.close();
    return exist;
}

bool sign_in_and_up(int option) {
    if (option == 1) {
        int trying = 2;
        string user_name, password;
        pair<bool, bool>response;

        for (int i = 0; i <= trying; i++) { // you have 3 times to enter userName and passwords
            bool user_log = false, pass_log = false;
            cout << "please Enter the user name : ";
            cin >> user_data.first; // enter user name
            system("CLS");
            cout << "please Enter the password : ";
            cin >> user_data.second; // enter password
            system("CLS");

            response = check_email(user_data); // search about it in DB
            if (response.first == 1 && response.second == 1) {
                return true;
            }
            else if ((response.first == 0 || response.second == 0) && i < 2) {
                cout << "user name or password are wrong!!!\n\n";

            }
            else {
            return_to_here_if_user_didnot_enter_y_or_n:
                cout << "\nSorry, but it seems like you dont't have an e-mail , do you want sign up or not (y or n) : \n";
                char op; cin >> op;
                system("CLS");
                cin.ignore();
                if (op == 'y') // if i didn't find it
                    option = 2; // here you will go to sign up
                else if (op == 'n') {
                    cout << "ok , let us see you again :)"; // here you will get out
                    return false;
                }
                else {
                    cout << "**** wrong input, try again ****\n";
                    goto return_to_here_if_user_didnot_enter_y_or_n;

                }

            }
        }

    }

    if (option == 2) {
        string nm, ps;
        cout << "-----> enter the user name : ";
        cin >> nm;
        system("CLS");
        cout << "-----> enter your password : ";
        cin >> ps;
        system("CLS");
        fstream add;
        add.open("usersInApp.txt", ios::app); // here i open the file to add new user
        add << nm << " " << ps << endl;
        add.close();
        cout << "Done , now you have an email , you will go to log_in page\n";
        this_thread::sleep_for(chrono::seconds(2));
        system("CLS");
        option = 1;
        sign_in_and_up(option); // here the user will get back to sign in
    }

}

void ask_user_for_email() {
    int select;
    cout << "------> Hello sir , do you have an email or you want make one ?\n"
        << "1 - i have one\n"
        << "2 - i need one\n"
        << "please enter (1 or 2) : "; // here asking about user name and password
    cin >> select;
    if (select == 1) {
        system("CLS");
        resp = sign_in_and_up(select);
        cout << resp;
    }
    else if (select == 2) {
        system("CLS");
        resp = sign_in_and_up(select);

    }
    else {
        cout << "\n**** wrong input , please try again *****\n";
        ask_user_for_email();
        system("CLS");
    }
}

void log_out() {
    char opinion;
    cout << "\n\n do you want get out from programme ? ( y or n)\n";
    cout << "enter : "; cin >> opinion;
    cin.ignore();
    system("CLS");
    if (opinion == 'y') { // if user choose to get out , he will do
        go_in = false;
    }
    else if (opinion != 'y' && opinion != 'n') {

        cout << "\n**** wrong input , please try again *****\n";
        log_out();
    }
}

// Function to perform the exercise task
void exercises() {
    string exercise; // Variable to store the exercise type
    int repetitions; // Variable to store the number of repetitions
    int time;       // Variable to store the duration of the exercise

    cout << "Based on your goals enter the type of exercise: \n";
    cin.ignore();
    getline(cin, exercise);
    system("CLS");
    cout << "Enter the number of repetitions: \n";
    // Ignore any remaining input
    cin >> repetitions;
    system("CLS");
    cout << "Enter the duration of each repetition (in seconds): \n";
    cin.ignore();     // Ignore any remaining input
    cin >> time;
    system("CLS");
    cout << "\n\n";
    cout << "You have chosen " << exercise << " with " << repetitions << " repetitions,lasting for " << time << " seconds.\n";

    //////////// timer cycle
    char ch;   // Variable to store user choice after time end
    for (int i = time; i > 0; i--) {
        cout << "Time left: " << i << " seconds\n";  // Display the remaining time
        if (i == 5) {  // If the remaining time is 5 seconds, show a reminder message
            cout << "hurry up, time is about to end\n";
        }

        this_thread::sleep_for(chrono::seconds(1)); // Wait for one second
    }
    cout << "Time's up!\n";
    this_thread::sleep_for(chrono::seconds(2));
    system("CLS");

    // Ask user if they have finished or need more time
    return_to_here_if_user_didnot_enter_y_or_f:
    cout << "Have you finished or still need more time?\n(Enter f -> if finished / y -> if need time\n";
    cin >> ch;

    if (ch == 'y') {

        auto start = high_resolution_clock::now(); // Start timing
        cout << "Continue your exercise now and enter f when you finish\n";
        cin >> ch;
        if (ch == 'f') {
            auto end = high_resolution_clock::now(); // End timing
            auto duration = duration_cast<seconds>(end - start).count(); // Calculate the additional duration
            cout << "You took extra " << duration << " seconds \n";
        }
    }
    else if (ch == 'f') {
        cout << "Good Job man\n";
    }
    else {
        cout << "invalid input pls try again:\n";
        goto return_to_here_if_user_didnot_enter_y_or_f;
    }

}


//This function calculates the user's BMI.
void BMI() {
    int unitSystem, BMI_choice = 1;
    double BMI, weight, heightCm, heightFeet, heightInch;

    //display the starting screen.
    cout << "Welcome to BMI Calculator!\n";
    this_thread::sleep_for(chrono::seconds(3));
    system("cls");

    //Keeps the calculator ON and exit if the user chooses EXIT.
    while (BMI_choice == 1) {

        //Prompts the user to enter thier unit system.
        while (true) {
            cout << "What is your unit system?\n1-US (feet, inches, and poundes)\n2-Metric (cm and Kg)\n\nInput: ";
            cin >> unitSystem; system("cls");
            if (unitSystem > 2 || unitSystem < 1) {
                //Checks if the choice is valid.
                cout << "Wrong choice! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Prompts the user to enter thier weight.
        while (true) {
            cout << "What is your weight?\n\nInput: ";
            cin >> weight; system("cls");
            if (unitSystem == 1)
                //Converts the weight from pounds to Kg.
                weight *= 0.453592;
            if (weight < 28 || weight>635) {
                //Checks if the weight is valid.
                cout << "The weight is wrong! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Prompts the user to enter thier height.
        while (true) {
            if (unitSystem == 1) {
                //Enter the height in foot and inch.
                cout << "What is your height?\nFeet: ";
                cin >> heightFeet;
                cout << "Inch: ";
                cin >> heightInch; system("cls");
                //Converts height from feet inches to Cm.
                heightCm = heightFeet * 30.48 + heightInch * 2.54;
            }
            else if (unitSystem == 2) {
                //Enter the height in Cm directly.
                cout << "What is your height?\n\nInput: ";
                cin >> heightCm; system("cls");
            }
            if (heightCm < 54 || heightCm>272) {
                //Checks if the height is valid.
                cout << "The height is wrong! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Converts the Hieght from Cm to meters.
        heightCm /= 100;

        //Calculates the BMI and rounds it to nearest one decimal number.
        BMI = weight / (heightCm * heightCm);
        BMI = round(BMI * 10) / 10;

        //Displays the BMI depending on particular scales and more info.
        while (true) {
            cout << "Your BMI is: " << BMI << " and you are considered as ";
            if (BMI < 18.5)
                cout << "an Underweight. \nIncreased risk of developing health problems.\n";
            else if (BMI >= 18.5 && BMI < 25)
                cout << "a Normal Weight. \nLeast risk of developing health problems.\n";
            else if (BMI >= 25 && BMI < 30)
                cout << "an Overweight. \nIncreased risk of developing health problems.\n";
            else if (BMI >= 30 && BMI < 35)
                cout << "an Obese Class I. \nHigh risk of developing health problems.\n";
            else if (BMI >= 35 && BMI < 40)
                cout << "an Obese Class II. \nVery high risk of developing health problems.\n";
            else if (BMI >= 40)
                cout << "an Obese Class III. \nExtremely high risk of developing health problems.\n";
            cout << "\n1-Another calculation\n2-Exit\n\nInput: ";
            cin >> BMI_choice; system("cls");
            if (BMI_choice > 2 || BMI_choice < 1) {
                cout << "Wrong choice! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }
    }

    //Displays the final screen.
    cout << "Thank you for using our calculator!\n";
    this_thread::sleep_for(chrono::seconds(2));
    system("cls");
}

//this function calculates the calories you need a day.
void CalorieCalculator() {
    int age, gender, unitSystem, activityLevel, calorieChoice = 1;
    double calories, BMR, weight, heightCm, heightFeet, heightInch;

    //display the starting screen.
    cout << "Welcome to Calorie Calculator!\n";
    this_thread::sleep_for(chrono::seconds(3));
    system("cls");

    //Keeps the calculator ON and exit if the user chooses EXIT.
    while (calorieChoice == 1) {

        //Prompt the user to enter thier unit system.
        while (true) {
            cout << "What is your unit system?\n1-US (feet, inches, and poundes)\n2-Metric (cm and Kg)\n\nInput: ";
            cin >> unitSystem; system("cls");
            if (unitSystem > 2 || unitSystem < 1) {
                //Checks if the choice is valid.
                cout << "Wrong choice! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Prompts the user to enter thier gender.
        while (true) {
            cout << "What is your gender?\n1-Male\n2-Female\n\nInput: ";
            cin >> gender; system("cls");
            if (gender > 2 || gender < 1) {
                //Checks if the choice is valid.
                cout << "Wrong choice! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Prompts the user to enter thier weight.
        while (true) {
            cout << "What is your weight?\n\nInput: ";
            cin >> weight; system("cls");
            if (unitSystem == 1)
                //Converts the weight from pounds to Kg.
                weight *= 0.453592;
            if (weight < 28 || weight>635) {
                //Checks if the weight is valid.
                cout << "The weight is wrong! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Prompts the user to enter thier height.
        while (true) {
            if (unitSystem == 1) {
                //Enter the height in foot and inch.
                cout << "What is your height?\nFeet: ";
                cin >> heightFeet;
                cout << "Inch: ";
                cin >> heightInch; system("cls");
                heightCm = heightFeet * 30.48 + heightInch * 2.54;
            }
            else if (unitSystem == 2) {
                //Enter the height in Cm directly.
                cout << "What is your height?\n\nInput: ";
                cin >> heightCm; system("cls");
            }
            if (heightCm < 54 || heightCm>272) {
                //Checks if the height is valid.
                cout << "The height is wrong! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Prompts the user to enter thier age.
        while (true) {
            cout << "What is your age?\n\nInput: ";
            cin >> age; system("cls");
            if (age > 123 || age < 7) {
                //Checks if the age is valid.
                cout << "The age is wrong! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Prompts the user to enter thier activity level.
        while (true) {
            cout << "What is your activity level?\n"
                "1-Sedentary (little or no exercise)\n"
                "2-Lightly active (exercise 1-3 times a week)\n"
                "3-Moderately active (exercise 3-5 times a week)\n"
                "4-Very active (exercise 6-7 days a week)\n"
                "5-Extra active (very hard exercise & physical daily)\n\n"
                "Input: ";
            cin >> activityLevel; system("cls");
            if (activityLevel > 5 || activityLevel < 1) {
                //Checks if the choice is valid.
                cout << "Wrong choice! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }

        //Calculates the BMR depending on the user's gender.
        if (gender == 1)
            BMR = 10 * weight + 6.25 * heightCm - 5 * age + 5;
        else if (gender == 2)
            BMR = 10 * weight + 6.25 * heightCm - 5 * age - 161;

        //Calculates the calories per day depending on the user's activity level.
        if (activityLevel == 1)
            calories = BMR * 1.2;
        else if (activityLevel == 2)
            calories = BMR * 1.375;
        else if (activityLevel == 3)
            calories = BMR * 1.55;
        else if (activityLevel == 4)
            calories = BMR * 1.725;
        else
            calories = BMR * 1.9;

        //Rounds it to the nearest decimal number.
        calories = round(calories);

        //Displays user's calories per day and more info.
        while (true) {
            cout << "You need " << calories << " per day to remain your weight!\n\n";
            cout << "Weight loss:               Weight gain:\n";
            cout << calories - 250 << "                       " << calories + 250 << "\n";
            cout << "to lose 0.25Kg/week.       to gain 0.25Kg/week\n";
            cout << calories - 500 << "                       " << calories + 500 << "\n";
            cout << "to lose 0.5Kg/week.        to gain 0.5Kg/week\n";
            cout << calories - 1000 << "                       " << calories + 1000 << "\n";
            cout << "to lose 1Kg/week.          to gain 1Kg/week\n\n\n";
            cout << "1-Another calculation\n2-Exit\n\nInput: ";
            cin >> calorieChoice; system("cls");
            if (calorieChoice > 2 || calorieChoice < 1) {
                //Checks if the choice is valid.
                cout << "Worng choice! Please try again.\n";
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
            }
            else
                break;
        }
    }

    //Displays the final screen.
    cout << "Thank you for using our calculator!\n";
    this_thread::sleep_for(chrono::seconds(2));
    system("cls");
}


void pomodoro() {
    int choice;
begin_again:
    cout << "Here , in pomodort technique mode , you have two options-----> \n" // choose your suitable mode
        << "1 - 30 minutes study and 5 minutes break\n"
        << "2 - 45 minutes study and 15 minutes break\n"
        << "enter your choice (1 or 2) : ";cin>>choice;
    system("CLS");
    /*
    cout << "--->alert<---- , when you enter you should wait for the end of period\n";
    this_thread::sleep_for(chrono::seconds(3));
    system("CLS");
    */
    if (choice == 1) {
        char opinion;
        for (int i = 29; i >= 0; i-=2) {
            for (int j = 59; j >= 0; j-=2) {
                    cout<<"--------->press q key to get out<--------------\n";

                    if (GetAsyncKeyState('Q') & 0x8000) {
                    std::cout << "Quit key pressed!" << std::endl;
                    Sleep(500);
                    system("CLS");
                    system("pause");
                    system("CLS");
                    goto begin_again;
                }
                 // beginning of study timer
                cout << "study timer : ";
                cout << i << ":" << j<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("CLS");
            }
        }

        for (int i = 4; i >= 0; i--) {
            for (int j = 59; j >= 0; j--) {
                    cout<<"--------->press q key to get out<--------------\n";

                    if (GetAsyncKeyState('Q') & 0x8000) {
                    std::cout << "Quit key pressed!" << std::endl;
                    Sleep(500);
                    system("CLS");
                    system("pause");
                    system("CLS");
                    goto begin_again;
                }

                cout << "break timer : "; // beginning of break timer
                cout << i << ":" << j<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("CLS");
            }
        }
        // asking for new session
    return_if_didnt_exist_yes_no:
        cout << "do you want another session ? (y or n) : ";
        cin >> opinion;
        if (opinion == 'y') {
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
            goto begin_again;
        }

        else if (opinion != 'y' && opinion != 'n') {
            goto return_if_no_yes_and_no;
        }

    }

    else if (choice == 2) {
        char opinion;
        for (int i = 44; i >= 0; i--) {
            for (int j = 59; j >= 0; j--) {
                cout<<"--------->press q key to get out<--------------\n";

                    if (GetAsyncKeyState('Q') & 0x8000) {
                    std::cout << "Quit key pressed!" << std::endl;
                    Sleep(500);
                    system("CLS");
                    system("pause");
                    system("CLS");
                    goto begin_again;
                }
                cout << "study timer : "; // beginning of study timer
                cout << i << ":" << j<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("CLS");

            }
        }

        for (int i = 1; i >= 0; i--) {
            for (int j = 1; j >= 0; j--) {
                cout<<"--------->press q key to get out<--------------\n";

                    if (GetAsyncKeyState('Q') & 0x8000) {
                    std::cout << "Quit key pressed!" << std::endl;
                    Sleep(500);
                    system("CLS");
                    system("pause");
                    system("CLS");
                    goto begin_again;
                }
                cout << "break timer : "; // beginning of break timer
                cout << i << ":" << j<<endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("CLS");
            }
        }
        // asking for new session
    return_if_no_yes_and_no:
        cout << "do you want another session ? (y or n) : ";
        cin >> opinion;
        if (opinion == 'y') {
            this_thread::sleep_for(chrono::seconds(2));
            system("CLS");
            goto begin_again;
        }

        else if (opinion != 'y' && opinion != 'n') {
            goto return_if_no_yes_and_no;
        }

    }
    else {
        cout << "\n**** wrong input , please try again *****\n";
        pomodoro();
    }
}

void calender() {
    cout << "today's date is : "; // pring today's date
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    cout << now->tm_year + 1900 << "-" << now->tm_mon + 1 << "-" << now->tm_mday;

}

void todo() {

    cout << "please enter the number of tasks which you want to write : ";
    int numberofthings;
    cin >> numberofthings; // determine the number of lines

    cin.ignore();// Ignore leftover newline
    cout << "Done, now enter your tasks : \n";
    while (numberofthings--) {
        string userinput = "\n";
        getline(cin, userinput); // read the lines

        fstream todolist;
        todolist.open("to do list.txt", ios::app);

        if (todolist.is_open()) {
            todolist << userinput << "\n"; // input in file
            todolist.close();
        }
        else {
            cerr << "Error opening file to_do_list.txt" << endl;
        }
    }
    cout << "your data has been saved.";
    this_thread::sleep_for(chrono::seconds(2));
    system("CLS");
}

void displaytodo() {
    system("CLS");
    fstream todolist;
    todolist.open("to do list.txt");

    if (todolist.is_open()) {
        cout << todolist.rdbuf(); // print all the data in the to-do-list
        todolist.close();
        cout << "\n\n these are your tasks.";
    }
    else {
        cerr << "Error opening file to_do_list.txt" << endl;
    }
}

void quotes() {
    vector<string> words;
    string line;
    fstream quotes_file;
    quotes_file.open("quotes.txt"); // open quotes file

    if (quotes_file.is_open()) {
        while (getline(quotes_file, line)) {
            words.push_back(line);
        }
        quotes_file.close();

        if (!words.empty()) {
            srand(time(0));
            int randomNumber = rand() % words.size(); // print it randomly
            cout << words[randomNumber] << endl;
        }
        else {
            cout << "No quotes available." << endl;
        }
    }
    else {
        cerr << "Error opening file quotes.txt" << endl;
    }
}



void to_do_list() {
return_to_here_if_user_didnot_enter_one_or_two:
    int choice;
    cout << "Now , here you can write and read your to-do-list , what do you want ? \n" // choose your mode
        << "1 - write\n"
        << "2 - read\n"
        << "enter you choice (1 or 2) : ";
    cin >> choice;
    if (choice == 1) {
        todo();
    }
    else if (choice == 2) {
        displaytodo();
    }
    else {
        cout << "\n**** wrong input , please try again *****\n";
        goto return_to_here_if_user_didnot_enter_one_or_two;
    }

}

void work_options() {
    cout << "Ok , these are our programs---->\n" // choose what do you want
        << "1 - pomodoro technique\n"
        << "2 - calender\n"
        << "3 - To-Do-list\n"
        << "4 - qoutes\n"
        << "enter your choice : (1 or 2 or 3 or 4) : ";
    cin >> workOpinion;
}

void health_options() {// choose what do you want
    cout << "Ok , these are our programs---->\n"
        << "1 - calorie calculator\n"
        << "2 - exercises\n"
        << "3 - BMI\n"
        << "enter your choice : (1 or 2 or 3) : ";
    cin >> healthOpinion;
}



void main_sections() { //choose your mode
    cout << "We have Two sections -----> \n"
        << "1 - work section\n"
        << "2 - health section\n"
        << "3 - log out\n"
        << "enter your choice : (1 or 2 or 3) : ";
    cin >> mainOpinion;
}