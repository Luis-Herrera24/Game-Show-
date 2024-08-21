#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

const int QUESTION_SIZE = 51;
const int COLUMN = 5;
const int QUESTION_COUNT = 6;                                          // Can be adjust to increase or decrease number of question.

struct QuestionStruct {
    string get_questions[QUESTION_SIZE][COLUMN];                       // Sorts the questions into a 2D array using stucts.
};

void read_questions(char[],int&);                                      // Reads the question.txt file and creates 2nd file with no spaces an answer.
QuestionStruct getQuestions(int&);                                     // Reads questions1.txt and converts text into 2D stuct array.
char read_answers(char[],int,int&);                                    // Reads the answer.txt file and returns an answer.
int CountAnswers_Questions(int,int);                                   // Counts and checks to make sure same number of Q/A.
void show_question(QuestionStruct, int, char);                         // Shows the questions with A,B,C,D choises.
void play_game(QuestionStruct,string,int,int,int&,char,int&);          // The bulk of the game,runs the game asking the questions and scoring.
void sort_score(string,int);                                           // Displays the score and created a file with decending scores.

int main(int argc, char* argv[]) {
   ifstream questionsFile, answersFile;

    if (argc != 4) {
        cout << "Incorrect program usage." << endl;
        cout << "Please read the program description and try again. Exiting." << endl;
        cout << "Usage: " << argv[0] << " inputFileName1 inputFileName2 seedValue" << endl;
        return -1;
    }

    int fixed_seed = atoi(argv[3]);                                    // Set fixed_seed to argv 3.

    questionsFile.open(argv[1]);                                       // Open questions file and set argv 1.
        if (!questionsFile) {
            cout << "Error: Could not open " << argv[1] << endl;
            return 1;
        }

    answersFile.open(argv[2]);                                         // Open answers file and set argv 2.
        if (!answersFile) {
            cout << "Error: Could not open " << argv[2] << endl;
            return 1;
        }

    if (questionsFile.peek() == EOF || answersFile.peek() == EOF) {    // Check if either file is empty.
        cout << "The question file or the answer file is empty." << endl;
        cout << "Please check the files and try again. Exiting." << endl;
        return 1;
    }

    questionsFile.close();                                             // Close both files.
    answersFile.close();
    
    string player_Name;
    char answerKey;
    int count, fai;
    int random_number = 0;
    int error, score, totalScore, totalQ_A;
    int numQ, numA, fail = 0;
    QuestionStruct questions;
    srand(fixed_seed);
    char file1[15];
    char file2[15];

    strcpy(file1, argv[1]);
    strcpy(file2, argv[2]);

    read_questions(file1,error);                                       // Ends programs if there is problems with question file.
        if (error == -1){
            return -1;
        }

    questions = getQuestions(numQ);

    read_answers(file2,random_number,numA);
        if (read_answers(file2,random_number,numA) =='F'){
            cout << "ERROR! Answer file contains unwanted numbers and or characters" << endl;
        }
    
    totalQ_A = CountAnswers_Questions(numQ,numA);                      
        if (totalQ_A < QUESTION_COUNT){                                // Ends programs if numbers of Q or A is less than the question count.
            cout << "ERROR! not enought questions or answers to run the program" << endl;
            return -1;
        }
        else if (totalQ_A == -1){                                      // Ends programs if Q and A numbers are diffrent. 
            cout << "ERROR! The number of question and answer are different"<< endl;
            return -1;
        }

    int random_NumArray[totalQ_A];                                     // Creates an array with stores random numsbers.

    bool used[totalQ_A];

    for(int i = 0; i < totalQ_A; i++)
        used[i] = false;
        for(int i = 0; i < QUESTION_COUNT; i++){                       // Gets only the amounts needed for the questions.
            random_NumArray[i] = rand() % totalQ_A;                    // Makes sure that numbers do not repeat.
            while(used[random_NumArray[i] ] == true)
                random_NumArray[i] = rand() % totalQ_A;
                used[random_NumArray[i]] = true;
        }

    cout << "What is your name?" << endl;

    cin >> player_Name;

    score = 1;
    totalScore = 0;                                                    // Sets and also resets the score for each player.

    for (int i = 0; i < QUESTION_COUNT; i++){
        count = i;                                                     // Sends # to play_game so that question # is displayed.
        random_number = random_NumArray[i];                            // Get a number from the random array for distribution.
        answerKey = read_answers(file2,random_number,numA);

        play_game(questions,player_Name,random_number,count,fail,answerKey,score); // Plays the game.

        score = score;                                                 // The keeps incresing per question.
        totalScore += score;                                           // Scores are added together.

        if (fail == -1){                                               // Breaks the loop if person gets answer wrong twice.
            totalScore = 0;
            break;
            }
    }
    sort_score(player_Name,totalScore);

    cout << endl;
    cout << "Thanks for playing, we hope you'll send all your friends to play." << endl;

return 0;
}

void read_questions (char fileName1[],int& error) {
    string question_answers;
    ifstream fin;
    ofstream fout;

    fin.open(fileName1);                                               // Opens initial file with questions.

    if (!fin){
        cout << "ERROR! File questions.txt was unable to open" << endl;
        error = -1;
        }

    fout.open("questions1.txt");                                       // Opens a second file to store content with no spaces.

    if (!fout){
        cout << "ERROR! File questions 1.txt was unable to open" << endl;
        error = -1;
        }

    while (getline(fin, question_answers)) {                           // Get only lines with content and ignores blanks.
        if (question_answers.length() >= 1) {
            fout << question_answers << endl;
        }
        if (fin.fail()){
            cout << "ERROR! question.txt failed to run all the way." << endl;
            error = -1;
            break;
        }

        if (fout.fail()){
            cout << "ERROR! question1.txt failed upload the entire file." << endl;
            error = -1;
            break;
        }
    }
    fin.close();
    fout.close();
}

QuestionStruct getQuestions(int& qTotal){
    QuestionStruct questions;
    ifstream finput;
    string file_questions;
    finput.open("questions1.txt");

    while(!finput.eof()){

        for (int i = 0; i < QUESTION_SIZE; i++) {                      // Turns the questions and response into 2D array.
            for (int j = 0; j < COLUMN; j++){
                getline(finput, file_questions);
                questions.get_questions[i][j] = file_questions;
            }
            if (finput.eof()){
                qTotal = i;                                            // Returns number of loops/questions.
                break;
            }
        }
    }
    finput.close();
    return questions;
}
char read_answers(char fileName2[], int number, int& aTotal){
    ifstream input_answers;
    char answer_key[QUESTION_SIZE];
    char awsKey;
    int i = 0;

    input_answers.open(fileName2);

    if (!input_answers){                                               // Returns E as a fail safe.
        return 'E';
        }

    while (!input_answers.eof()) {

        input_answers >> awsKey;                                       // Reads in the answers from file, storing to a 1D array. 
        answer_key[i] = awsKey;

            if (isdigit(awsKey) || ispunct(awsKey)){                   // Returns F answers.txt have #'s or special characters.
                return 'F';
                break;
            }
            if (input_answers.eof()){
                aTotal = i;
                break;                                                 // Returns number of loops/answers.
            }
    i++;
    }
    input_answers.close();

    return answer_key[number];                                         // Returns answer that is associated with the random # integer from main.
}
int CountAnswers_Questions(int questionNum, int answerNum) {
    int Q_ATotal;

    if (questionNum == answerNum){                                     // If numbers match it returns the total # of questions.
        Q_ATotal = questionNum;
        return Q_ATotal;
    }
    else {
        return -1;                                                     // If not same amount it will send -1 to terminate the program.
    }
}
void show_question(QuestionStruct questions, int random, char choise){
    int i = random;                                                    // (i) is random genrated number from main to pick which questions.
    int j;

    for (j = 0; j < 5; j++){                                           // Runs the 2nd nested loop to cout question and answer choises.
        if (j == 0){
            cout << questions.get_questions[i][j] << endl;
        }
        else if (j == 1){
            if (choise == 'A'){                                        // Gets the choise from play_game function and displays blank if wrong.
                cout << endl;
            }
            else {
                cout << "A. " << questions.get_questions[i][j] << endl;
            }
        }
        else if (j == 2){
            if (choise == 'B') {
                cout << endl;
            }
            else {
                cout << "B. " << questions.get_questions[i][j] << endl;
            }
        }
        else if (j == 3){
            if (choise == 'C') {
                cout << endl;
            }
            else {
                cout << "C. " << questions.get_questions[i][j] << endl;
            }
        }
        else if (j == 4){
            if (choise == 'D') {
                cout << endl;
            }
            else {
                cout << "D. " << questions.get_questions[i][j] << endl;
                cout << endl;
            }
        }
    }
}
void play_game(QuestionStruct questions, string name,int random, int counter, int& fail, char answer,int& score) {
    char choise;
    counter = counter + 1;                                             // Counter from main to display correct # questions.
    char retryChoise;
    answer = toupper(answer);

    cout << name << "  Here's Question Number " << counter  << endl;

    show_question (questions,random,choise);
    cout << "Your choise?" << endl;

    cin >> choise;
    choise = toupper(choise);
                                                                       // Fail safe so that only A,B,C,D are chosen.
    if (choise != 'A' && choise != 'B' && choise != 'C' && choise != 'D') {
        while (choise != 'A' && choise != 'B' && choise != 'C' && choise != 'D') {
            cout << "You can only choose A , B , C or D Please try again." << endl;
            cin >> choise;
            choise = toupper(choise);
        }
    }
    if (choise == answer){
        choise = '@';                                                  // Resets the choise to prevent issues.
        score = score * 10;                                            // The score is multiplied by 10 for each correct answer.
        cout << "You got that one right, for " << score << " points"<< endl;
        cout << endl;
        counter++;
        fail = 0;                                                      // Resets the fail counter if last player both answers question wrong.
    }
    else{
        cout << "That is incorrect answer." << endl;
        cout << "Would you like to try again for 1/2 points ? (Y/N)" << endl;   // Gives players 2nd chance to answer.

        cin >> retryChoise;
        retryChoise = toupper(retryChoise);

        if (retryChoise != 'Y' && retryChoise != 'N') {                // Player must chooses only Y or N. 
            while (retryChoise != 'Y' && retryChoise != 'N') {

                cout << "You can only choose Y or N. Please try again." << endl;

                if (retryChoise == 'A' || retryChoise == 'B' ||retryChoise == 'C'|| retryChoise == 'D'){
                    retryChoise = '@';
                }

            cin >> retryChoise;
            retryChoise = toupper(retryChoise);

            }
        }
        if (retryChoise == 'Y') {
            cout << name << "  Here's Question Number " << counter << " (2nd try) " << endl;
            show_question (questions,random,choise);                   // Displays the questions with the lost wrong choise as blank.
            choise = '@';
            cout << "Your choise?" << endl;
            cin >> choise;
            choise = toupper(choise);

            if (choise != 'A' && choise != 'B' && choise != 'C' && choise != 'D') {
                while (choise != 'A' && choise != 'B' && choise != 'C' && choise != 'D') {
                    cout << "You can only choose A , B , C or D Please try again." << endl;
                    choise = '@';
                    cin >> choise;
                    choise = toupper(choise);
                }
            }
                if (choise == answer){
                    choise = '@';
                    score = score * 5;                                 // Player gets half points for answering correct on 2nd try.
                    cout << "You got that one right, for " << score << " points"<< endl << endl;
                    counter++;
                    fail = 0;
                }

                else if  (choise != answer){
                    choise = '@';
                    score = 0;
                    cout << "Oh, that's wrong again. Sorry, but you've lost." << endl;
                    cout << "Come back and try again after you study more." << endl << endl;
                    fail = -1;                                         // If player fails it breaks the loop so new player can play.
                }   
        }       
        else if (toupper(retryChoise) == 'N') {                    // If player choses N it skips to the next question.
                choise = '@';
                counter++;
                score = score + 0;
                fail = 0;
        }   
    }       
}   
void sort_score(string player, int points){
    ofstream finalScore;
    ifstream scoreList;
    vector<string> playerName;                                         // Using vectors since they will be easier to manage the increasing player unlike arrays.
    vector<int> playerScore;
    int i;

    cout << "That's the end of the game, there are no more questions!" << endl << endl;
    cout << player << " your final score was: " << points << endl;
    cout << "This will be recorded to the game history file." << endl << endl;

    finalScore.open("summary.txt", ios::app);                          // Creates a file that display the player’s name and score from highest to lowest using append mode.
        if (!finalScore){
            cout << "ERROR! File summary.txt was unable to open" << endl;  // Fail safe if summary txt. does not open. 
            return;                                                        
        }

    finalScore << setw(10) << left << player;                          // Prints info in the correct format.
    finalScore << setw(8) << right << points << endl;

    finalScore.close();

    scoreList.open("summary.txt");
        if (!scoreList) {
            cout << "ERROR! File summary.txt was unable to open" << endl;
            return;
        }

    string name;
    int playScore;

    while (scoreList >> name >> playScore) {                            // Gets info from the file an stores into vectors.
        playerName.push_back(name);
        playerScore.push_back(playScore);
    }
    scoreList.close();

    finalScore.open("summary.txt");

    for (int i = 0; i < playerScore.size() - 1; ++i) {                  // Uses Selection Sort to in decending order.
        int indexLarge = i;
        for (int j = i; j < playerScore.size(); ++j) {
            if (playerScore.at(j) > playerScore.at(indexLarge)) {
                indexLarge = j;
            }
        }
        swap(playerScore.at(i), playerScore.at(indexLarge));
        swap(playerName.at(i), playerName.at(indexLarge));
    }

    for (int i = 0; i < playerScore.size(); ++i) {                      // Prints the returns in an organized manner.
        finalScore << setw(10) << left << playerName.at(i);
        finalScore << setw(8) << right << playerScore.at(i) << endl;
    }

    finalScore.close();

    cout << "The current record holder is " << playerName.at(0) << " with ";  // Prints who the current top place is.
    cout <<  playerScore.at(0) << " points." << endl;

    for (int i = 0; i < playerScore.size(); ++i){                       // Checks where the current player stands in the leaderboards.

        if (player == playerName.at(0)){
            cout << "Your have achieved rank 1 with " << points <<  " points." << endl;
            break;
        }
        else if (player == playerName.at(1)){
            cout << "Your have achieved rank 2 with " << points <<  " points." << endl;
            break;
        }
        else if (player == playerName.at(2)){
            cout << "Your have achieved rank 3 with " << points <<  " points." << endl;
            break;
        }
        else {
            cout << "Sorry you are not in the top 3 with " << points << " points." << endl;
            break;
        }
    }

}





