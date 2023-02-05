/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#include <iostream>
#include <string>
#include "User.h"

/*
Constructor for User class.

Parameters:
	username: the username of the user
	password: the password of the user
Returns: nothing
*/
User::User(const std::string& username, const std::string& password) : username(username), password(password) {}

/*
Returns the username of the user.

Parameters:
	none
Returns:
	username
*/
const std::string User::GetUsername() const { return username; }

/*
Gets the user's password.

Parameters:
	none
Returns:
	password: The user's password
*/
const std::string& User::GetPassword() const { return password; }

/*
Checks if the given password matches the user's password.

Parameters:
	password: the password to be checked
Returns: true if the passwords match, false otherwise
*/
bool User::CheckPassword(const std::string& password) const { return this->password == password; }

/*
Outputs the User's username and password to an output stream.

Parameters:
	os: ostream object
	user: User object to output
Returns: ostream object
*/
std::ostream& operator<<(std::ostream& os, const User& user) {
	os << user.username << std::endl << user.password;
	return os;
}

/*
Reads a User object from an input stream.

Parameters:
	is: input stream
	user: User object to read values into
Returns: input stream
*/
std::istream& operator>>(std::istream& is, User& user) {
	is >> user.username >> user.password;
	return is;
}