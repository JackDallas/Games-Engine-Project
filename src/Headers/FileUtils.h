#pragma once
//std
#include <string>
#include <iostream>
#include <fstream>

class FileUtils {
public:
	/**
	readFileToString, reads a file of the system to a string.
	Combine with getProgramPath() to read files using the exacutable's absolute path

	@see getProgramPath()
	@return a string containing the contents of the file
	*/
	static std::string readFileToString(const std::string filePath);
	/**
	getProgramPath, gets the path to the currently running program

	@return a string representing the current path
	*/
	static std::string getProgramPath();
private:
	//private Contructor to stop instances being made
	FileUtils();
	//Override the default copy constructor
	FileUtils(const FileUtils& that) = delete;
	/**
	getExePath, gets the path to the exe file running
	*/
	static std::string getExePath();
};