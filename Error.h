#pragma once
#include <iostream>
#include <string>


class Error 
{
public:
	Error(const Error&) = delete;
	Error& Instance() 
	{
		static Error instance;
		return instance;
	}

	static void fatalError(std::string errMsg, bool exitApplication = false)
	{
		std::cout << "Error occured with error message: \n" << errMsg << std::endl;

		system("pause");

		if (exitApplication)
			exit(47);

		return;
	}

private:
	Error() {}
};
