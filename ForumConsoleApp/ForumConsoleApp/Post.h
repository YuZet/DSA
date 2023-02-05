/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#pragma once
#include <string>
#include <vector>

class Post {
public:
	Post() {}
	Post(const std::string& author, const std::string& title, const std::string& content);
	std::string GetAuthor() const;
	std::string GetTitle() const;
	std::string GetContent() const;
	std::vector<Post> GetReplies() const;
	void SetReplies(const std::vector<Post>& newReplies);

	void AddReply(const Post& reply);

	friend std::ostream& operator<<(std::ostream& os, const Post& post);
	friend std::istream& operator>>(std::istream& is, Post& post);

	friend bool operator==(const Post& lhs, const Post& rhs);
	bool operator<(const Post& other) const;
private:
	std::string author;
	std::string title;
	std::string content;
	std::vector<Post> replies;
};