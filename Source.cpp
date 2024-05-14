#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

struct Question
{

	string questionText;
	string options[4];
	int correctOption;
	int playerAnswer;
};

struct Node
{
	Question data;
	Node* next;
	Node* prev;
};


Node* head = NULL;
Node* tail = NULL;
string players[10];
int scores[10] = { 0 };
int numPlayers = 0;


struct Admin
{

	string username;
	string password;
};

Admin admins[5];
int numAdmins = 0;


void addQuestion() {

	Question newQuestion;
	cout << "---------------------" << endl;
	cout << "Enter the question: ";
	cin.ignore();
	getline(cin, newQuestion.questionText);

	cout << endl;

	cout << "Enter the options: " << endl;
	for (int i = 0; i < 4; i++) {
		cout << "Option " << i + 1 << ": ";
		getline(cin, newQuestion.options[i]);
	}
	cout << "Enter the correct option (1-4): ";
	cin >> newQuestion.correctOption;

	while (cin.fail() || newQuestion.correctOption < 1 || newQuestion.correctOption > 4)
	{
		cout << "              " << endl;
		cout << "!!!! E R R O R !!!!" << endl;
		cout << "Invalid Input !!!" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Enter the correct option from (1-4) only : ";
		cin >> newQuestion.correctOption;


	}

	Node* newNode = new Node;
	newNode->data = newQuestion;
	newNode->next = NULL;

	if (head == NULL) {
		newNode->prev = NULL;
		head = newNode;
		tail = newNode;
	}
	else {

		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
}


void deleteQuestion() {

	if (head == NULL) {
		cout << endl;
		cout << "Quiz is empty!" << endl;
		return;
	}

	int questionNumber;

	cout << endl;
	cout << "Enter the question number to delete: ";
	cin >> questionNumber;

	while (cin.fail())
	{
		cout << "              " << endl;
		cout << "!!!! E R R O R !!!!" << endl;
		cout << "Invalid Input!!!" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "ENTER AGAIN! the question number to delete: ";
		cin >> questionNumber;


	}


	Node* current = head;
	int count = 1;
	bool found = false;
	while (current != NULL)
	{
		if (count == questionNumber)
		{
			if (current == head && current == tail)
			{
				head = NULL;
				tail = NULL;
			}

			else if (current == head)
			{
				head = head->next;
				head->prev = NULL;
			}
			else if (current == tail)
			{
				tail = tail->prev;
				tail->next = NULL;
			}
			else
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
			}

			free(current);

			cout << endl;

			cout << "Question " << questionNumber << " deleted successfully!" << endl;
			found = true;
			break;
		}

		current = current->next;
		count++;
	}

	if (!found) {
		cout << "     " << endl;
		cout << "Question " << questionNumber << " not found!" << endl;
	}
}


void displayQuestions() {

	Node* current = head;

	int questionNumber = 1;

	cout << endl << endl;
	cout << '\t' << '\t' << '\t' << '\t' << " xxxxxx  -- -  DISPLAYING ALL QUESTIONS  - --  xxxxxx " << endl;

	while (current != NULL)
	{

		cout << "-----------------------------" << endl;
		cout << "Question " << questionNumber << ": " << current->data.questionText << endl;

		cout << "Options: " << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << i + 1 << ". " << current->data.options[i] << endl;
		}

		cout << "Answer: " << current->data.correctOption << endl;
		cout << endl;
		current = current->next;
		questionNumber++;
	}
}


void displayScoreList() {

	cout << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << "-------------------------------------" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << "-------- S C O R E  L I S T ---------" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << "-------------------------------------" << endl;


	if (numPlayers == 0)
	{
		cout << "No scores available!! No player has played yet :)" << endl;
	}
	else
	{
		for (int i = 0; i < numPlayers; i++)
		{
			cout << "Player " << i + 1 << ": " << players[i] << "   "  " Score: " << scores[i] << endl;
		}
	}

}


void playQuiz() {

	if (head == NULL)
	{
		cout << "--------------" << endl;
		cout << "Quiz is empty! Please add questions." << endl;
		return;
	}

	if (numPlayers >= 10)
	{
		cout << "---------------" << endl;
		cout << "Maximum number of players reached!" << endl;
		return;
	}

	string playerName;

	cout << '\t' << '\t' << '\t' << '\t' << '\t' << "-------------------------------------" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << "         LET'S BEGIN THE QUIZ        " << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << "-------------------------------------" << endl;
	cout << "Enter your name: ";
	cin.ignore();
	getline(cin, playerName);

	players[numPlayers] = playerName;
	numPlayers++;

	Node* current = head;
	int questionNumber = 1;
	int currentPlayerScore = 0;
	int playerAnswer;
	vector<Question> incorrectQuestions;

	while (current != NULL)
	{
		cout << "                   " << endl;
		cout << "Player: " << playerName << endl;
		cout << "------------" << endl;
		cout << "Question " << questionNumber << ": " << current->data.questionText << endl;
		cout << "   " << endl;
		cout << "Select any 1 option or press 0 to skip the question :) " << endl;

		cout << "Options: " << endl;
		for (int i = 0; i < 4; i++)
		{
			cout << i + 1 << ". " << current->data.options[i] << endl;

		}

		cout << "Enter your answer (1-4, 0 to skip): ";
		cin >> playerAnswer;

		while (cin.fail() || (playerAnswer != 0 && (playerAnswer < 1 || playerAnswer > 4)))
		{
			cout << "              " << endl;
			cout << "!!!! E R R O R !!!!" << endl;
			cout << "You did not enter an integer.Please enter correct data in integer form!!!" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << endl;
			cout << "Please select from (1-4, 0 to skip) only : ";
			cin >> playerAnswer;

		}



		if (playerAnswer == 0)
		{
			current = current->next;
			questionNumber++;
			continue;

		}


		if (playerAnswer == current->data.correctOption)
		{
			currentPlayerScore++;
		}

		else
		{
			Question incorrectQuestion = current->data;
			incorrectQuestion.playerAnswer = playerAnswer;
			incorrectQuestions.push_back(incorrectQuestion);
		}

		current = current->next;
		questionNumber++;
	}

	scores[numPlayers - 1] = currentPlayerScore;

	cout << endl;
	cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << "   -------- Q U I Z  C O M P L E T E D !!!! -------- " << endl << " Your score: " << currentPlayerScore << endl;


	cout << endl;

	cout << "Incorrectly Answered Questions:" << endl;

	if (incorrectQuestions.empty()) {
		cout << "   " << endl;
		cout << "No incorret answers ! All answers are correct!" << endl;
	}

	else {
		for (int i = 0; i < incorrectQuestions.size(); ++i)
		{
			cout << "----------------" << '\n';
			cout << "Question: " << incorrectQuestions[i].questionText << '\n';
			cout << "Correct Answer: " << incorrectQuestions[i].options[incorrectQuestions[i].correctOption - 1] << '\n';
			cout << "Your Answer: " << incorrectQuestions[i].options[incorrectQuestions[i].playerAnswer - 1] << '\n';
			cout << '\n';
		}
	}
}




void main()
{
	int choice;

	Admin admin1 = { "faiz", "faiz1" };
	Admin admin2 = { "hania", "hania1" };
	Admin admin3 = { "zainab", "zainab1" };
	admins[0] = admin1;
	admins[1] = admin2;
	admins[2] = admin3;
	numAdmins = 3;


	Question question1 =
	{
		"What is the capital of France?",
		{ "London", "Paris", "Berlin", "Rome" },
		2
	};

	Node* node1 = new Node;
	node1->data = question1;
	node1->next = NULL;
	node1->prev = NULL;
	head = node1;
	tail = node1;

	Question question2 =
	{
		"What is the largest planet in our solar system?",
		{ "Mars", "Jupiter", "Saturn", "Earth" },
		2
	};

	Node* node2 = new Node;
	node2->data = question2;
	node2->next = NULL;
	node2->prev = tail;
	tail->next = node2;
	tail = node2;



	Question question3 =
	{
		"What is the chemical symbol for gold?",
		{ "Au", "Ag", "Cu", "Fe" },
		1
	};

	Node* node3 = new Node;
	node3->data = question3;
	node3->next = NULL;
	node3->prev = tail;
	tail->next = node3;
	tail = node3;



	Question question4 =
	{
		"Who painted the Mona Lisa?",
		{ "Leonardo da Vinci", "Vincent van Gogh", "Pablo Picasso", "Michelangelo" },
		1
	};

	Node* node4 = new Node;
	node4->data = question4;
	node4->next = NULL;
	node4->prev = tail;
	tail->next = node4;
	tail = node4;



	Question question5 =
	{
		"What is the square root of 81?",
		{ "9", "7", "8", "6" },
		1
	};
	Node* node5 = new Node;
	node5->data = question5;
	node5->next = NULL;
	node5->prev = tail;
	tail->next = node5;
	tail = node5;

	Question question6 = {
		"What is the national animal of India?",
		{ "Tiger", "Lion", "Elephant", "Giraffe" },
		1
	};
	Node* node6 = new Node;
	node6->data = question6;
	node6->next = NULL;
	node6->prev = tail;
	tail->next = node6;
	tail = node6;



	Question question7 =
	{
		"Which planet is known as the Red Planet?",
		{ "Venus", "Mars", "Mercury", "Jupiter" },
		2
	};
	Node* node7 = new Node;
	node7->data = question7;
	node7->next = NULL;
	node7->prev = tail;
	tail->next = node7;
	tail = node7;



	Question question8 =
	{
		"Who wrote the play 'Romeo and Juliet'?",
		{ "William Shakespeare", "Charles Dickens", "Jane Austen", "Mark Twain" },
		1
	};
	Node* node8 = new Node;
	node8->data = question8;
	node8->next = NULL;
	node8->prev = tail;
	tail->next = node8;
	tail = node8;



	Question question9 =
	{
		"What is the chemical symbol for oxygen?",
		{ "O", "O2", "OH", "OX" },
		1
	};
	Node* node9 = new Node;
	node9->data = question9;
	node9->next = NULL;
	node9->prev = tail;
	tail->next = node9;
	tail = node9;



	Question question10 =
	{
		"Who discovered gravity?",
		{ "Albert Einstein", "Isaac Newton", "Galileo Galilei", "Nikola Tesla" },
		2
	};
	Node* node10 = new Node;
	node10->data = question10;
	node10->next = NULL;
	node10->prev = tail;
	tail->next = node10;
	tail = node10;



	while (true) {
		cout << endl;
		cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << "========  Q U I Z   G A M E   ========" << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << "                                      " << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << "== Wellcome to the WHO n What Quiz  ==" << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << "== 1. Admin Portal                  ==" << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << "== 2. Player Portal                 ==" << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << "== 3. Exit                          ==" << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << "======================================" << endl;
		cout << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << "==        Enter your choice:        ==" << endl;
		cout << "                 " << endl;
		cin >> choice;


		while (cin.fail() || choice< 1 || choice > 3)
		{
			cout << "!!!! E R R O R !!!!" << endl;
			cout << "You did not enter an integer, Please enter correct data in integer form!!!" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


			cout << "Please select a correct option again from (1-3) only : ";
			cin >> choice;

		}


		if (choice == 1) {
			string username, password;
			cout << endl << "Enter your username: ";
			cin >> username;
			cout << endl << "Enter your password: ";
			cin >> password;

			bool adminAuthenticated = false;
			for (int i = 0; i < numAdmins; i++) {
				if (admins[i].username == username && admins[i].password == password) {
					adminAuthenticated = true;
					break;
				}
			}

			if (adminAuthenticated) {
				int adminChoice;


				while (true)
				{
					cout << endl;
					cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " ====   A D M I N  P O R T AL   ====" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " -----------------------------------" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " == 1. Add Question               ==" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " == 2. Delete Question            ==" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " == 3. Display Questions          ==" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " == 4. Display Score List         ==" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " == 5. Logout                     ==" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " -----------------------------------" << endl;
					cout << '\t' << '\t' << '\t' << '\t' << '\t' << " ====   Enter your choice:      ====" << endl;
					cin >> adminChoice;

					while (cin.fail() || adminChoice < 1 || adminChoice > 5)
					{

						cout << "!!!! E R R O R !!!!" << endl;
						cout << "You did not enter an integer, Please enter correct data in integer form!!!!" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


						cout << "Please select a correct option again from (1-5) only : ";
						cin >> adminChoice;

					}

					if (adminChoice == 1)
					{
						addQuestion();
					}
					else if (adminChoice == 2)
					{
						deleteQuestion();
					}
					else if (adminChoice == 3)
					{
						displayQuestions();
					}
					else if (adminChoice == 4)
					{
						displayScoreList();
					}
					else if (adminChoice == 5)
					{
						break;
					}
					else
					{
						cout << "                  " << endl;
						cout << "Invalid choice! Please try again." << endl;
					}
				}
			}
			else {
				cout << "Authentication failed! Please try again." << endl;
			}
		}
		else if (choice == 2)
		{
			playQuiz();
		}
		else if (choice == 3)
		{
			break;
		}
		else
		{
			cout << "Invalid choice! Please try again." << endl;
		}
	}

	system("pause");
}