#include "Logger.h"

void Logger::Debug(std::string _message) {
#ifdef DEBUGMODE
	std::cout << "[Debug] " << _message << std::endl;
#endif
}
void Logger::Info(std::string _message) {
#ifdef DEBUGMODE
	std::cout << "[Info] " << _message << std::endl;
#endif
}
void Logger::Error(std::string _message) {
#ifdef DEBUGMODE
	std::cout << "[Error] " << _message << std::endl;
#endif
}