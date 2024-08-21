# Game Show Quiz

## Project Overview

The Game Show Quiz is a console-based program that allows users to upload multiple-choice questions and corresponding answers through text files. The game randomly selects questions, presents them to the player, and tracks their score based on correct answers. The program also maintains a leaderboard, recording the highest scores.

## Features

- **Upload Questions and Answers**: Players can upload a text file containing questions and another with answers.
- **Randomized Question Selection**: The program randomly selects a subset of questions for each game session.
- **Scoring System**: Correct answers are rewarded with points, and players can earn half points on a second attempt.
- **Leaderboard**: The game maintains a leaderboard that displays the top scores.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/gameshow-quiz.git
2. Navigate to the project directory:
   ```bash
   cd gameshow-quiz
3. Compile the program:
   ```bash
   g++ -o gameshow_quiz main.cpp
   
## Usage

To run the game, use the following command:
   ```bash
   ./gameshow_quiz questions.txt answers.txt seedValue

questions.txt: A text file containing the multiple-choice questions.
answers.txt: A text file containing the correct answers corresponding to the questions.
seedValue: An integer seed for random number generation.

### Example
   ```bash
   ./gameshow_quiz questions.txt answers.txt 42

## File Format
Each question should be followed by four possible answers.
The format should be as follows:

What is the capital of France?
A. Paris
B. Berlin
C. Rome
D. Madrid

answers.txt
Each line should contain the correct answer (A, B, C, or D) corresponding to the questions in the questions.txt file.
Summary File
After each game, the player's score is recorded in a summary.txt file, which stores the scores and ranks them from highest to lowest.

## Contributing
Feel free to fork the repository, create a new branch, and submit a pull request with your changes. Contributions are welcome!

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Contact
For any questions or suggestions, feel free to contact me at your.email@example.com.





