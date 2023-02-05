/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#pragma once

class User {
public:
	User() = default;
	User(const std::string& username, const std::string& password);

	const std::string GetUsername() const;
	const std::string& GetPassword() const;
	bool CheckPassword(const std::string& password) const;

	friend std::ostream& operator<<(std::ostream& os, const User& user);
	friend std::istream& operator>>(std::istream& is, User& user);
private:
	std::string username;
	std::string password;
};