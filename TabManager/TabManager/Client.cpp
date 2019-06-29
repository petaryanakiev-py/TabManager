#include "Client.hpp"
#include "Command.hpp"

#include <iostream>
#include <algorithm>

Client::Client(const PromptPrinter&)
	: promptPrinter(promptPrinter)
{
}

std::string Client::convertToUppercase(std::string command)
{
	std::transform(command.begin(), command.end(), command.begin(),
		[](unsigned char c) { return std::toupper(c); });
	return command;
}

void Client::interactWithUser()
{
	std::string userInputCommand = " ";
	std::string lastExecutedCommand = " ";
	Command* commandToExecute = commandFactory.getCommandByType("INSERT");
	do
	{
		promptPrinter();

		std::cin >> userInputCommand;
		userInputCommand = convertToUppercase(userInputCommand);

		if (commandFactory.checkCommandExistence(userInputCommand))
		{
			commandToExecute = commandFactory.getCommandByType(userInputCommand);
			commandToExecute->execute();
		}
	} while (commandFactory.checkCommandExistence(userInputCommand));

	delete commandToExecute;

	std::cout << "Exitting..." << std::endl;
}