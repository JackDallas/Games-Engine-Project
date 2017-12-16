#pragma once
//std
#include <string>
#include <iostream>

class Logger {
public:
	static void Debug(std::string _message);
	static void Info(std::string _message);
	static void Error(std::string _message);
private:
	//prevent creation
	Logger();
	Logger(const Logger& that) = delete;

};