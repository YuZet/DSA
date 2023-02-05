/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#pragma once
#include <iostream>
#include <map>
#include <string>
#include "Topic.h"
#include "User.h"
#include "Array.h"

class Forum {
public:
	void Load();
	void Save();
	void Register(const std::string& username, const std::string& password);
	void Login(const std::string& username, const std::string& password);
	void Logout(const std::string& username);
	bool CheckUser();
	void ViewTopics();
	void ViewPosts(const std::string& topicTitle);
	void CreateTopic(const std::string& topicTitle);
	void CreatePost(const std::string& topicTitle, const Post& post);
	void EditPost(const std::string& username, const std::string& topicTitle, const std::string& postTitle, const Post& newPost);
	void DeletePost(const std::string& username, const std::string& topicTitle, const std::string& postTitle);
	void AddReply(const std::string& topicTitle, const std::string& postTitle, const Post& reply);
	void StickTopic(const std::string& topicTitle);
	void UnstickTopic(const std::string& topicTitle);
	void StickPost(const std::string& topicTitle, const std::string& postTitle);
	void UnstickPost(const std::string& topicTitle, const std::string& postTitle);
	int FindTopic(const std::string& topicTitle);
	void SortTopics();
	void SortPosts(const std::string& topicTitle);
private:
	Array<Topic> topics;
	std::map<std::string, User> users;
	User* currentUser = nullptr;
};