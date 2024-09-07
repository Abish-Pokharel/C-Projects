#include<iostream>
#include<iomanip>
#include<windows.h>
using namespace std;

    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string BLUE = "\033[34m";
    const string YELLOW = "\033[33m";
    const string CYAN = "\033[36m";
    const string MAGENTA = "\033[35m";
    const string RESET = "\033[0m"; 

void clearScreen(){
    system("cls");
}
void pause(){
    Sleep(1500);
}
void drawLine(){
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
};


void displayRules() {
    drawLine();
    cout << " " <<endl;
    cout << CYAN << "                                            Quiz Game Rules" << RESET << endl;
    drawLine();
    cout  << "1."<<YELLOW <<" Objective:"<<RESET<<" Answer as many questions correctly as possible to accumulate points."  << endl;
    cout  << "2."<<YELLOW <<" Categories:"<<RESET<<" History, Geography, Science, Sports. Each category has 10 questions."  << endl;
    cout  << "3."<<YELLOW <<" Lifeline:"<<RESET<<" You can use a 50-50 lifeline once during the game, removing two incorrect options." << endl;
    cout  << "4."<<YELLOW <<" Scoring:"<<RESET<<" Each correct answer awards 5 points. Incorrect answers receive no points."  << endl;
    cout  << "5."<<YELLOW <<" Gameplay:"<<RESET<<" Choose a category and answer one question at a time. Enter the letter of your choice (A, B, C, or D)."  << endl;
    cout  << "6."<<YELLOW <<" Game End:"<<RESET<<" After 10 questions, the game ends, and your total score is displayed."  << endl;
    cout  << "7."<<YELLOW <<" Exit:"<<RESET<<" You can exit the game at any time by selecting the 'Exit the game' option."  << endl;
    drawLine();
}



void displayMenu(){
     cout << " " <<endl;
    cout << " " <<endl;    
    drawLine();
    cout << " " <<endl;
    cout << BLUE << "                                        Welcome to the Game !!!" << RESET <<endl;
    displayRules();
    cout << " " <<endl;
    cout << " " <<endl;
    cout << GREEN << "                                  Please, try to answer them correctly" << RESET <<endl;
    Sleep(10000);
    clearScreen();
    // cout << " " <<endl;
    // cout << " " <<endl;

    cout << CYAN << "Enter your choice wisely......" << RESET << endl;
    cout << "" << endl;
    cout << GREEN << "              1. History" << RESET << endl;
    cout << GREEN << "              2. Geography" << RESET << endl;
    cout << GREEN << "              3. Science" << RESET << endl;
    cout << GREEN << "              4. Sports" << RESET << endl;
    cout << RED << "              5. Exit the game" << RESET << endl;
    cout << "" << endl;
}



void displayQuestion (const string &question ,const string options[]){
    cout << YELLOW << question << RESET << endl;
    for ( int j= 0; j< 4; j++){
        if(!options[j].empty()){
            pause();
            cout << MAGENTA << char('A' + j) << ". " << options[j] << RESET << endl;
        }
    }
}


void applyLifeline( string currentOptions[], const string &correctOption , bool &lifelineUse){
    int currentIndex ;
    for (int k=0; k<4; k++){
        if(currentOptions[k]== correctOption){
            currentIndex = k;
            break;
        }
    }

    int count = 0;
    while (count < 2){
        int removeIndex = rand () % 4;
        if(removeIndex != currentIndex && !currentOptions[removeIndex].empty()){
            currentOptions[removeIndex] = "";
            count ++;
        }
    }

}

void askQuestion(const string question[], const string options[][4],
    const string correctOptions[], int &score, bool &lifelineUse){
        char answer;
        for ( int i=0; i< 10; i++){
            string currentOptions[4];
                for(int j=0; j<4; j++){
                    currentOptions[j]= options[i][j];
                }
            cout << YELLOW << i + 1 << "." << RESET << endl;
            displayQuestion(question[i], currentOptions);
            pause();

             if (!lifelineUse) {
                cout << "" << endl;
                cout << BLUE << "Do you want to use the " << GREEN << " 50-50 "<< RESET << BLUE << "lifeline? (Y/N): " << RESET;
                char lifelineChoice;
                cin >> lifelineChoice;
                pause();
                lifelineChoice = toupper(lifelineChoice);

                if (lifelineChoice == 'Y') {
                    lifelineUse = true;
                    applyLifeline(currentOptions, correctOptions[i], lifelineUse);
                    pause();
                    clearScreen();
                    cout << CYAN << "Updated options after using" << GREEN << " 50-50 "<< RESET << CYAN << "lifeline: "  << RESET << endl;
                    cout << "" << endl;
                    pause();
                    displayQuestion(question[i], currentOptions);
                }
            }


            cout << BLUE <<  "Enter your answer (A-D): "<< RESET ;
            cin >> answer;
            answer = toupper(answer);
            pause();

            int answerIndex = answer -'A';
            if (options[i][answerIndex] == correctOptions[i]) {
                cout << GREEN << "Correct!" << RESET << endl;
                drawLine();
                cout << "" << endl;
                cout << "" << endl;
                score = score + 10;
            } else {
                cout << RED << "Wrong! The correct answer is " << correctOptions[i] << "." << RESET << endl;
                score = score - 5;
                drawLine();
            }
            pause();
            clearScreen();
        }
    }

// void askQuestion(const string question[], const string options[][4],
//  const string correctOptions[], int &score, bool &lifelineUse){
//     char answer;
//     for(int i=0; i<10; i++){
//         cout << YELLOW << i+1 << "." << question[i] << RESET << endl;
//         for(int j=0; j<4; j++){
//             cout << MAGENTA << char ('A'+ j) << ". "  << options[i][j] << RESET << endl;
//         }
//         cout << BLUE <<  "Enter your answer (A-D): "<< RESET ;
//         cin >> answer;
//         answer = toupper(answer);

//         int answerIndex = answer -'A';
//         if (options[i][answerIndex] == correctOptions[i]) {
//             cout << GREEN << "Correct!" << RESET << endl;
//             drawLine();
//             cout << "" << endl;
//             cout << "" << endl;
//             score = score + 5;
//         } else {
//             cout << RED << "Wrong! The correct answer is " << correctOptions[i] << "." << RESET << endl;
//             drawLine();
//         }
//     }

// };


void askHistory(int &score, bool &lifelineUse){

    string question[] = {
        "Who is known as the Destroyer among the Hindu Trinity of Gods?",
        "Which epic features the story of Rama and his quest to rescue Sita?",
        "Who is the god of wisdom and learning in Hindu mythology?",
        "Which epic features the Kurukshetra War?",
        "What is the name of the mountain that is believed to be the abode of Lord Shiva?",
        "What vehicle does the god Vishnu traditionally ride?",
        "Which goddess is often associated with prosperity and good fortune?",
        "Who is known as the Monkey God and a devotee of Rama in the Ramayana?",
        "Which festival is celebrated to honor Lord Shiva, often with fasting and night-long vigils?",
        "In which form did Lord Krishna display his divine universal form to Arjuna during the Kurukshetra War?",
    };
    string options[][4] ={
        {"Shri Ram", "Lord Shiva", "Lord Hanuman", "Lord Krishna"},
        {"Mahabharata", "Vedas", "Bhagbata Puran", "Ramayan"},
        {"Lord Vishnu", "Lord Krishna", "Arjun", "Ganesha"},
        {"Ramayan", "Vedas", "Mahabharata", "Ramayan"},
        {"Meru", "Baikunth", "Kailash", "Vindhya"},
        {"Tiger", "Vulture", "Lion", "Garuda"},
        {"Durga", "Saraswati", "Lakshmi", "Parvati"},
        {"Lord Vishnu", "Lord Krishna", "Arjun", "Lord Hanuman"},
        {"Holi", "Maha Shivaratri", "Diwali", "Dashain"},
        {"Narayana", "Vishvarupa", "Govardhana", "Gopala"},
        
    };
    string correctOption []={
        "Lord Shiva",
        "Ramayan",
        "Ganesha",
        "Mahabharata",
        "Kailash",
        "Garuda",
        "Lakshmi",
        "Lord Hanuman",
        "Maha Shivaratri",
        "Vishvarupa"        
        };
        askQuestion(question, options, correctOption, score, lifelineUse);
};

void askGeography(int &score, bool &lifelineUse) {
    string question[] = {
        "What is the largest continent on Earth?",
        "Which river is the longest in the world?",
        "Which desert is the largest in the world?",
        "Which ocean is the deepest?",
        "Which country has the most natural lakes?",
        "What is the smallest country in the world?",
        "Mount Everest is located in which mountain range?",
        "Which country is known as the Land of the Rising Sun?",
        "What is the capital city of Australia?",
        "Which island is the largest in the world?"
    };
    string options[][4] = {
        {"Asia", "Africa", "North America", "Europe"},
        {"Amazon", "Nile", "Yangtze", "Mississippi"},
        {"Sahara", "Gobi", "Kalahari", "Arabian"},
        {"Pacific Ocean", "Atlantic Ocean", "Indian Ocean", "Arctic Ocean"},
        {"Canada", "Russia", "USA", "Brazil"},
        {"Monaco", "Vatican City", "San Marino", "Liechtenstein"},
        {"Himalayas", "Andes", "Rockies", "Alps"},
        {"China", "Japan", "South Korea", "India"},
        {"Sydney", "Melbourne", "Canberra", "Brisbane"},
        {"Greenland", "New Guinea", "Borneo", "Madagascar"}
    };
    string correctOption[] = {
        "Asia",
        "Nile",
        "Sahara",
        "Pacific Ocean",
        "Canada",
        "Vatican City",
        "Himalayas",
        "Japan",
        "Canberra",
        "Greenland"
    };
    askQuestion(question, options, correctOption, score, lifelineUse);
}
void askScience(int &score, bool &lifelineUse) {
    string question[] = {
        "What is the chemical symbol for water?",
        "What planet is known as the Red Planet?",
        "What is the powerhouse of the cell?",
        "What gas do plants absorb from the atmosphere?",
        "Who developed the theory of relativity?",
        "What is the hardest natural substance on Earth?",
        "What is the primary gas found in the Earth's atmosphere?",
        "What is the center of an atom called?",
        "What force keeps us grounded on Earth?",
        "Which element is known as the 'King of the Elements'?"
    };
    string options[][4] = {
        {"H2O", "O2", "CO2", "N2"},
        {"Venus", "Mars", "Jupiter", "Saturn"},
        {"Mitochondria", "Nucleus", "Ribosome", "Endoplasmic Reticulum"},
        {"Oxygen", "Nitrogen", "Carbon Dioxide", "Hydrogen"},
        {"Isaac Newton", "Albert Einstein", "Galileo Galilei", "Nikola Tesla"},
        {"Gold", "Iron", "Diamond", "Graphite"},
        {"Oxygen", "Nitrogen", "Carbon Dioxide", "Hydrogen"},
        {"Electron", "Proton", "Nucleus", "Neutron"},
        {"Magnetism", "Electrostatic Force", "Gravity", "Tension"},
        {"Oxygen", "Carbon", "Hydrogen", "Nitrogen"}
    };
    string correctOption[] = {
        "H2O",
        "Mars",
        "Mitochondria",
        "Carbon Dioxide",
        "Albert Einstein",
        "Diamond",
        "Nitrogen",
        "Nucleus",
        "Gravity",
        "Carbon"
    };
    askQuestion(question, options, correctOption, score, lifelineUse );
}
void askSports(int &score, bool &lifelineUse){
    string question[] = {
        "Which country has won the most ICC Cricket World Cups?",
        "Who is the highest run-scorer in the history of Test cricket?",
        "Which sport is known as 'The Gentleman's Game'?",
        "Which cricketer is known as 'The Little Master'?",
        "What is the term for a bowler who takes five wickets in a single inning?",
        "In which year was the first Cricket World Cup held?",
        "Who holds the record for the fastest century in ODIs?",
        "Which cricketer has taken the most wickets in Test cricket?",
        "What is the name of the trophy awarded to the winner of the Test series between England and Australia?",
        "In which format of cricket did Virat Kohli score his fastest century?",
    };
    string options[][4] = {
        {"Australia", "India", "West Indies", "England"},
        {"Sachin Tendulkar", "Brian Lara", "Ricky Ponting", "Allan Border"},
        {"Cricket", "Tennis", "Golf", "Football"},
        {"Sunil Gavaskar", "Sachin Tendulkar", "Virat Kohli", "Rahul Dravid"},
        {"Hat-trick", "Five-for", "Century", "Maiden"},
        {"1975", "1983", "1992", "1996"},
        {"Shahid Afridi", "AB de Villiers", "Virat Kohli", "Chris Gayle"},
        {"Shane Warne", "Muttiah Muralitharan", "Anil Kumble", "James Anderson"},
        {"The Ashes", "Border-Gavaskar Trophy", "Sir Vivian Richards Trophy", "Chappell-Hadlee Trophy"},
        {"Test Cricket", "ODI", "T20", "IPL"},
    };
    string correctOption[] = {
        "Australia",
        "Sachin Tendulkar",
        "Cricket",
        "Sachin Tendulkar",
        "Five-for",
        "1975",
        "AB de Villiers",
        "Muttiah Muralitharan",
        "The Ashes",
        "ODI"
    };
    askQuestion(question, options, correctOption, score, lifelineUse);
}






int main()
{
    int choice;
    int score = 0;
    bool exitedGame = false;
    bool lifelineUse = false;
    
    displayMenu(); 

    cin >> choice;
    pause();
    clearScreen();

    switch(choice){
        case 1:
            askHistory(score, lifelineUse);
            break;
        case 2:
            askGeography(score, lifelineUse);
            break;        
        case 3: 
            askScience(score, lifelineUse);
            break;
        case 4:
            askSports(score, lifelineUse);
            break;
        case 5: 
            cout << RED << "Quitting the game." << RESET << endl;
            exitedGame = true;
            break;
        default :
            cout << RED << "Invalid Choice" << endl;
    }   


   if(!exitedGame){
     cout << BLUE << "Your score is: " << score  << RESET  << endl;
     if (score >= 45) {
        cout << GREEN << "Outstanding !!!" << RESET << endl;
    } else if (score >= 35) {
        cout << CYAN << "Nice Job !!!" << RESET << endl;
    } else if (score >= 20) {
        cout << CYAN << "Well Done" << RESET << endl;
    } else {
        cout << RED << "Better luck next time !!!" << RESET << endl;
    }
   }    
    // drawLine();
    return 0;
}