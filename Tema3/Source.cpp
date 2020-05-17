#include <iostream>
#include <vector>
#include <fstream>

#include "Token.h"

void PrintComputers(const std::vector<std::string> computers)
{
	for (int i = 0; i < computers.size(); i++)
	{
		std::cout << i + 1 << ". " << computers[i] << "\n";
	}
}

void CheckExistingComputers(std::string index, int nrOfComp)
{
	for (auto c : index)
	{
		if (!std::isdigit(c))
		{
			throw "Invalid!";
		}
	}
	auto x = std::stoi(index);
	if (x < 1 || x > nrOfComp)
	{
		throw "Invalid!";
	}
}

int main()
{
	std::ifstream f("computers.txt");

	int nrOfComputers;
	std::vector<std::string> computers;
	std::string indexOfCompSource;
	std::string indexOfCompDestination;
	bool cronologic;
	std::string message;

	std::cout << "Read data from file or put your own data? (1-file/2-own) ";
	int answer;
	std::cin >> answer;
	if (answer == 1)
	{
		f >> nrOfComputers;
		for (int i = 0; i < nrOfComputers; i++)
		{
			std::string ip;
			f >> ip;
			computers.push_back(ip);
		}
	}
	else
	{
		std::cout << "Nr of computers: "; std::cin >> nrOfComputers;
		std::cout << "\n";
		for (int i = 0; i < nrOfComputers; i++)
		{
			std::cout << "Computer " << i + 1 << ": ";
			std::string ip;
			std::cin >> ip;
			computers.push_back(ip);
		}
	}
	PrintComputers(computers);
	while (true)
	{
		std::cout << "Index of computer source ip: ";
		std::cin >> indexOfCompSource;
		try
		{
			CheckExistingComputers(indexOfCompSource, nrOfComputers);
			break;
		}
		catch (const char* message)
		{
			std::cout << message << "\n";
		}
	}
	while (true)
	{
		std::cout << "Index of computer destination ip: ";
		std::cin >> indexOfCompDestination;
		try
		{
			CheckExistingComputers(indexOfCompDestination, nrOfComputers);
			if (indexOfCompDestination.compare(indexOfCompSource) == 0)
			{
				throw "Invalid!";
			}
			break;
		}
		catch (const char* message)
		{
			std::cout << message << "\n";
		}
	}
	std::cout << "Sensul acelor de ceasornic: (1-y/2-n) "; std::cin >> cronologic;
	std::cout << "Message: "; std::cin >> message;

	Token token(computers[std::stoi(indexOfCompSource) - 1], computers[std::stoi(indexOfCompDestination) - 1], cronologic, message);
	std::cout << "\n";
	while (true)
	{
		token.SendMessage(computers);
		std::cout << "\n\nDo you want to send another message? (1-y/0-n)";
		int answer;
		std::cin >> answer;
		if (answer == 0)
		{
			break;
		}
		else
		{
			PrintComputers(computers);
			while (true)
			{
				std::cout << "\n\nIndex of computer source ip: ";
				std::cin >> indexOfCompSource;
				try
				{
					CheckExistingComputers(indexOfCompSource, nrOfComputers);
					break;
				}
				catch (const char* message)
				{
					std::cout << message << "\n";
				}
			}

			while (true)
			{
				std::cout << "Index of computer destination ip: ";
				std::cin >> indexOfCompDestination;
				try
				{
					CheckExistingComputers(indexOfCompDestination, nrOfComputers);
					if (indexOfCompDestination.compare(indexOfCompSource) == 0)
					{
						throw "Invalid!";
					}
					break;
				}
				catch (const char* message)
				{
					std::cout << message << "\n";
				}
			}

			std::cout << "Message: "; std::cin >> message;

			token.SetIpSource(computers[std::stoi(indexOfCompSource) - 1]);
			token.SetIpDestination(computers[std::stoi(indexOfCompDestination) - 1]);
			token.SetMessage(message);
		}
	}

	std::cout << "\n";
}