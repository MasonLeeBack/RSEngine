/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: ErrorHandling.cpp

*/

#include <Core/RSErrorHandling.h>

#include<string>

namespace rs {

	void errorHandling::handleError(const char* argument, const char* file, int lineNum)
	{
		std::string errorStuff = std::string("ERROR: " + std::string(argument) + ", File: " + std::string(file) + ", Line:" + std::to_string(lineNum));
		std::runtime_error(std::string(errorStuff));
	}

	void errorHandling::crashEngine()
	{
		// todo: error reporting
		//MessageBox(NULL, L"An error occurred within RSEngine and the application\nmust quit. Sorry for the inconvenience!", L"Error", MB_OK | MB_ICONERROR);
		exit(-194);
	}


} // namespace rs
