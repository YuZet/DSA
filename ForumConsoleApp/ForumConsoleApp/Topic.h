/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Post.h"

class Topic {
public:
	Topic() = default;
	Topic(const std::string& title);

	const std::string& GetTitle() const;
	const std::vector<Post> GetPosts() const;
	void SetTitle(const std::string& title);
	void SetPosts(const std::vector<Post>& newPosts);
	void AddPost(const Post& post);

	// Find a Post in a Topic
	int FindPost(const Post& post);
	int FindPost(const std::string& postTitle);

	// Remove a Post in a Topic
	void RemovePost(const Post& post);
	void RemovePost(int postIndex);

	void ShowPosts() const;

	void AddReply(const std::string& postContent, const std::string& replyAuthor, const std::string& replyContent);

	Post GetPost(int postIndex) const;

	void InsertPost(const Post& post);

	void InsertPost(const Post& post, int postIndex);

	friend std::ostream& operator<<(std::ostream& os, const Topic& topic);

	friend std::istream& operator>>(std::istream& is, Topic& topic);

	bool operator<(const Topic& rhs) const;
private:
	std::string title;
	std::vector<Post> posts;
};
