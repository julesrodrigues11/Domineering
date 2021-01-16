#include <iostream>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <string>

//Enumeration type, gives names to the built-in colours
enum concol
{
	black = 0, dark_blue = 1, dark_green = 2, dark_cyan = 3, dark_red = 4,
	dark_purple = 5, dark_yellow = 6, light_gray = 7, gray = 8, blue = 9,
	green = 10, cyan = 11, red = 12, purple = 13, yellow = 14, white = 15
};

//Function to set the text and background colours
void setColours(concol textCol, concol backCol)
{
	unsigned short colours = (backCol << 4) | textCol;

	//Set the attributes for the console
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colours);
}

//Function to Print Grid
//Takes a two-dimensional vector as a parameter
void printGrid(std::vector<std::vector<char>> vect)
{
	//Printing Column Numbers
	std::cout << "\n    ";
	for (int i = 0; i < vect.size(); i++)
	{
		std::cout << "  " << char(i + 65) << " ";
	}
	std::cout << std::endl;

	//Printing Grid Top
	std::cout << "    " << char(218);
	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << char(196);
		}

		if (i == vect.size() - 1)
		{
			std::cout << char(191);
		}
		else
		{
			std::cout << char(194);
		}
	}
	std::cout << std::endl;

	//Printing Grid
	for (int i = 0; i < vect.size(); i++)
	{
		//Printing Row Numbers
		if (i < 9)
		{
			std::cout << "  " << i + 1 << ' ';
		}
		else
		{
			std::cout << ' ' << i + 1 << ' ';
		}

		//Printing Vector Elements
		//Prints the colours in different colours depending upon the content they hold
		std::cout << char(179);
		for (int j = 0; j < vect.size(); j++)
		{
			if (vect[i][j] == ' ')
			{
				setColours(white, black);
			}
			else if (vect[i][j] == 'H')
			{
				setColours(white, red);
			}
			else if (vect[i][j] == 'V')
			{
				setColours(white, blue);
			}

			std::cout << ' ';
			std::cout << vect[i][j];
			std::cout << ' ';

			setColours(white, black);
			std::cout << char(179);
		}
		std::cout << std::endl;

		//Printing Grid Bottom
		std::cout << "    ";
		if (i == vect.size() - 1)
		{
			std::cout << char(192);
		}
		else
		{
			std::cout << char(195);
		}

		for (int j = 0; j < vect.size(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				std::cout << char(196);
			}

			if (j == vect.size() - 1)
			{
				if (i == vect.size() - 1)
				{
					std::cout << char(217);
				}
				else
				{
					std::cout << char(180);
				}
			}
			else
			{
				if (i == vect.size() - 1)
				{
					std::cout << char(193);
				}
				else
				{
					std::cout << char(197);
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

//Function to check if horizontal (Player 1) move is valid
//Takes a two-dimensional vector, the row number and the column number as parameters
//Makes the move if valid
bool checkHorizontal(std::vector<std::vector<char>>& vect, int column, int row)
{
	if (column == vect.size() - 1)
	{
		std::cout << "You cannot place your piece here" << std::endl;
		std::cout << "Please enter values again\n" << std::endl;
		return false;
	}
	else if (vect.at(row).at(column) == ' ' && vect.at(row).at(column + 1) == ' ')
	{
		vect.at(row).at(column) = 'H';
		vect.at(row).at(column + 1) = 'H';
		return true;
	}
	else
	{
		std::cout << "You cannot place your piece here" << std::endl;
		std::cout << "Please enter values again\n" << std::endl;
		return false;
	}
}

//Function to check if vertical (Player 2) move is valid
//Takes a two-dimensional vector, the row number and the column number as parameters
//Makes the move if valid
bool checkVertical(std::vector<std::vector<char>>& vect, int column, int row)
{
	if (row == vect.size() - 1)
	{
		std::cout << "You cannot place your piece here" << std::endl;
		std::cout << "Please enter values again\n" << std::endl;
		return false;
	}
	else if (vect.at(row).at(column) == ' ' && vect.at(row + 1).at(column) == ' ')
	{
		vect.at(row).at(column) = 'V';
		vect.at(row + 1).at(column) = 'V';
		return true;
	}
	else
	{
		std::cout << "You cannot place your piece here" << std::endl;
		std::cout << "Please enter values again\n" << std::endl;
		return false;
	}
}

//Function to check if Player 1 has any moves left
//Returns a Boolean accordingly
bool checkP1Moves(std::vector<std::vector<char>> vect)
{
	bool movesAvailable = false;
	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect.size() - 1; j++)
		{
			if (vect.at(i).at(j) == ' ' && vect.at(i).at(j + 1) == ' ')
			{
				movesAvailable = true;
				return movesAvailable;
			}
		}
	}
	return movesAvailable;
}

//Function to check if Player 2 has any moves left
//Returns a Boolean accordingly
bool checkP2Moves(std::vector<std::vector<char>> vect)
{
	bool movesAvailable = false;
	for (int i = 0; i < vect.size() - 1; i++)
	{
		for (int j = 0; j < vect.size(); j++)
		{
			if (vect.at(i).at(j) == ' ' && vect.at(i + 1).at(j) == ' ')
			{
				movesAvailable = true;
				return movesAvailable;
			}
		}
	}
	return movesAvailable;
}

//Function to handle the Player 1 Move
void player1Move(std::vector<std::vector<char>>& vect)
{
	int column, row;
	char col;

	//Player 1 Move
	std::cout << "\nPlayer 1's Turn - Horizontal\n" << std::endl;

	//Inputting values for column and row
	//Checking if the values entered are valid
	//Calling function checkHorizontal to make sure the move is valid before making the move
	do
	{
		std::cout << "In which column do you want to place your piece? (letters) : ";
		std::cin >> col;
		col = toupper(col);
		column = int(col) - 65;

		while (column<0 || column>vect.size() - 1)
		{
			std::cout << "Invalid value entered. Please try again\n" << std::endl;
			std::cout << "In which column do you want to place your piece? (letters) : ";
			std::cin >> col;
			col = toupper(col);
			column = int(col) - 65;
		}

		std::cout << "Valid value entered\n" << std::endl;

		std::cout << "In which row do you want to place your piece? (numbers) : ";
		std::cin >> row;

		while (row<1 || row>vect.size() || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Invalid value entered. Please try again\n" << std::endl;
			std::cout << "In which row do you want to place your piece? (numbers) : ";
			std::cin >> row;
		}
		row--;
		std::cout << "Valid value entered\n" << std::endl;
	} while (!checkHorizontal(vect, column, row));

	std::cout << "P1 has placed their piece at " << col << row + 1 << std::endl;
	printGrid(vect);
}

//Function to handle the Player 2 Move
void player2Move(std::vector<std::vector<char>>& vect)
{
	int column, row;
	char col;

	//Player 2 Move
	std::cout << "\nPlayer 2's Turn - Vertical\n" << std::endl;

	//Inputting values for column and row
	//Checking if the values entered are valid
	//Calling function checkVertical to make sure the move is valid before making the move
	do
	{
		std::cout << "In which column do you want to place your piece? (letters) : ";
		std::cin >> col;
		col = toupper(col);
		column = int(col) - 65;

		while (column < 0 || column>vect.size() - 1)
		{
			std::cout << "Invalid value entered. Please try again\n" << std::endl;
			std::cout << "In which column do you want to place your piece? (letters) : ";
			std::cin >> col;
			col = toupper(col);
			column = int(col) - 65;
		}

		std::cout << "Valid value entered\n" << std::endl;

		std::cout << "In which row do you want to place your piece? (numbers) : ";
		std::cin >> row;

		while (row<1 || row>vect.size() || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Invalid value entered. Please try again\n" << std::endl;
			std::cout << "In which row do you want to place your piece? (numbers) : ";
			std::cin >> row;
		}

		row--;
		std::cout << "Valid value entered\n" << std::endl;
	} while (!checkVertical(vect, column, row));

	std::cout << "P2 has placed their piece at " << col << row + 1 << std::endl;
	printGrid(vect);
}

//Function to save the board state
//The function asks the user for a filename and opens a text document with the name input by the user
//The function then enters all the vector elements into the text document
void saveState(std::vector<std::vector<char>> vect)
{
	std::ofstream file;
	std::string fileName;
	std::cout << "Please enter the name of the file you want to save the board to : ";
	std::cin >> fileName;
	std::cout << std::endl;

	fileName = fileName + ".txt";
	file.open(fileName);

	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect.size(); j++)
		{
			if (vect[i][j] == ' ')
			{
				file << ' ';
			}
			else
			{
				file << vect[i][j];
			}
		}
		if (i != vect.size() - 1)
		{
			file << "\n";
		}
	}

	file.close();
}

//Function to get the grid size from the saved game file
//Opens the file with the name input by the user
//Counts how many elements are in a single line and returns it back to the user
int getGridSize(std::string& fileName)
{
	std::string line;
	std::ifstream file;

	std::cout << "Enter the name of the file you want to load data from : ";
	std::cin >> fileName;
	std::cout << std::endl;

	fileName = fileName + ".txt";
	file.open(fileName);

	std::getline(file, line);

	file.close();

	return line.length();
}

//Function to load the data from the given file
//Opens the file with the given name
//Replaces the vector elements with the ones in the file
void loadGame(std::vector<std::vector<char>>& vect, std::string fileName)
{
	int count = 0;
	std::string line;
	std::ifstream file;

	file.open(fileName);

	while (std::getline(file, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			vect[count][i] = line[i];
		}
		count++;
	}
}

//Function that is to be called when the program starts up
//It initialises the values of gridSize and load which will influence the printing of the grid
void startUp(int& gridSize, bool& load)
{
	char start;
	//Asking the user if they want to start a new game or load a game file
	std::cout << "Do you want to start a new game or load a game file?\n";
	std::cout << "Enter 'N' to start a new game or 'L' to load a previous game : ";
	std::cin >> start;
	start = toupper(start);

	//Data validation for start
	while (start != 'N' && start != 'L')
	{
		std::cout << "Invalid value entered. Please try again\n" << std::endl;
		std::cout << "Enter 'N' to start a new game or 'L' to load a previous game : ";
		std::cin >> start;
		start = toupper(start);
	}

	//If user decides to start a new game
	//Make user input value into gridSize
	if (start == 'N')
	{
		//Input value for gridSize
		std::cout << "\nEnter the size of the grid : ";
		std::cin >> gridSize;

		//Data Validation for gridSize
		while (gridSize > 15 || gridSize < 2 || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::cout << "Invalid value entered. Please try again\n" << std::endl;
			std::cout << "Enter the size of the grid : ";
			std::cin >> gridSize;
		}
	}

	//If user decides to load a previous game
	//Set load to true
	else if (start == 'L')
	{
		std::cout << "\nThe program will now load your game" << std::endl;
		load = true;
	}
}

//Function for the main game loop
void mainGame(std::vector<std::vector<char>>& vect, int gridSize)
{
	//Main Game Loop
	//Runs as long as user does not enter Q as input
	while (true)
	{
		char choice;
		//If the user tries to load a file that does not exist, gridSize will remain as 0
		//Resulting in the players unable to play
		if (gridSize == 0)
		{
			std::cout << "Invalid file loaded. You cannot play the game with an invalid grid" << std::endl;
			std::cout << "The program will now shut down" << std::endl;
			break;
		}

		std::cout << "What would you like to do?\n";
		std::cout << "Enter 'S' to save the game state, 'Q' to quit the game, or any other character to carry on with the game : ";
		std::cin >> choice;
		choice = toupper(choice);

		//If the user enters Q, the program will break out of the loop
		if (choice == 'Q')
		{
			std::cout << "\nYou have decided to quit the program" << std::endl;
			std::cout << "The program will now shut down" << std::endl;
			break;
		}

		//Calling the function saveState in order to save the game state
		else if (choice == 'S')
		{
			std::cout << "The game will now be saved\n" << std::endl;
			saveState(vect);
			continue;
		}

		else
		{
			//Calling the function for Player 1 Move
			player1Move(vect);
			//Checking if P2 has any valid moves
			if (!checkP2Moves(vect))
			{
				std::cout << "P2 has no valid moves left. P1 is the winner!" << std::endl;
				break;
			}

			//Calling the function for Player 2 Move
			player2Move(vect);
			//Checking if P1 has any valid moves
			if (!checkP1Moves(vect))
			{
				std::cout << "P1 has no valid moves left. P2 is the winner!" << std::endl;
				break;
			}
		}
	}
}

int main()
{
	int gridSize = 0;
	bool load = false;
	std::string fileName;

	std::cout << "Welcome to Domineering!" << std::endl;
	
	//Call function startUp to initialise the values of gridSize and load
	startUp(gridSize, load);

	//Call function getGridSize if load is true
	if (load)
	{
		gridSize = getGridSize(fileName);
	}

	//Create a blank two-dimensional vector with gridSize elements
	std::vector<std::vector<char>> board(gridSize, std::vector<char>(gridSize, ' '));

	//Initialise vector elements if load is true
	if (load)
	{
		loadGame(board, fileName);
	}

	//Calling function printGrid to print out grid
	if (gridSize != 0)
	{
		printGrid(board);
	}

	//Calling the mainGame function to start the main game
	mainGame(board, gridSize);

	std::cout << "\nThank you for playing Domineering!" << std::endl;

	return 1;
}