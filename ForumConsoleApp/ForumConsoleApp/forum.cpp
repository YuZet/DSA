/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include "Forum.h"
#include "Topic.h"
#include "User.h"
#include "Sort.h"
#include "Array.h"

/*
Loads forum data from a file.

Parameters:
	none
Returns: nothing
*/
void Forum::Load() {
	std::ifstream file("forum.dat");
	if (!file.is_open()) {
		std::cout << "Error: Failed to open file." << std::endl;
		return;
	}

	int numUsers;
	file >> numUsers;
	file.ignore();
	for (int i = 0; i < numUsers; ++i) {
		std::string username;
		std::getline(file, username);
		std::string password;
		std::getline(file, password);
		User user(username, password);
		users[username] = user;
	}

	int numTopics;
	file >> numTopics;
	file.ignore();
	for (int i = 0; i < numTopics; ++i) {
		std::string title;
		std::getline(file, title);
		Topic topic(title);
		int numPosts;
		file >> numPosts;
		file.ignore();
		for (int j = 0; j < numPosts; ++j) {
			std::string author;
			std::getline(file, author);
			std::string postTitle;
			std::getline(file, postTitle);
			std::string content;
			std::getline(file, content);
			Post post(author, postTitle, content);
			int numReplies;
			file >> numReplies;
			file.ignore();
			for (int k = 0; k < numReplies; ++k) {
				std::string replyAuthor;
				std::getline(file, replyAuthor);
				std::string replyTitle;
				std::getline(file, replyTitle);
				std::string replyContent;
				std::getline(file, replyContent);
				Post reply(replyAuthor, replyTitle, replyContent);
				post.AddReply(reply);
			}
			topic.AddPost(post);
		}
		topics.push_back(topic);
	}

	std::string currentUsername;
	std::getline(file, currentUsername);
	currentUser = currentUsername.empty() ? nullptr : &users[currentUsername];
	file.close();
	std::cout << "Forum data loaded successfully." << std::endl;
}

/*
Saves the Forum data to a file.

Parameters:
	none
Returns: nothing
*/
void Forum::Save() {
	std::ofstream file("forum.dat");
	if (!file.is_open()) {
		std::cout << "Error: Failed to open file." << std::endl;
		return;
	}
	file << users.size() << '\n';
	for (const auto& pair : users) {
		const std::string& username = pair.first;
		const User& user = pair.second;
		file << username << '\n' << user.GetPassword() << '\n';
	}

	file << topics.size() << '\n';
	for (const Topic& topic : topics) {
		file << topic.GetTitle() << '\n';
		file << topic.GetPosts().size() << '\n';
		for (const Post& post : topic.GetPosts()) {
			file << post.GetAuthor() << '\n' << post.GetTitle() << '\n';
			file << post.GetContent() << '\n';
			file << post.GetReplies().size() << '\n';
			for (const Post& reply : post.GetReplies()) {
				file << reply.GetAuthor() << '\n' << reply.GetTitle() << '\n';
				file << reply.GetContent() << '\n';
			}
		}
	}

	file << (currentUser ? currentUser->GetUsername() : "") << '\n';
	file.close();
	std::cout << "Forum data saved successfully." << std::endl;
}

/*
Registers a user with a given username and password.

Parameters:
	username: the username of the user to register
	password: the password of the user to register
Returns: nothing
*/
void Forum::Register(const std::string& username, const std::string& password) {
	if (users.count(username) > 0) {
		std::cout << "Error: User '" << username << "' already exists." << std::endl;
		return;
	}
	User user(username, password);
	users[username] = user;
	std::cout << "User '" << username << "' registered successfully." << std::endl;
}

/*
Logs in a user into the forum given a username and password.

Parameters:
	username: the username of the user to login
	password: the password of the user to login
Returns: nothing
*/
void Forum::Login(const std::string& username, const std::string& password) {
	if (users.count(username) == 0) {
		std::cout << "Error: User '" << username << "' not found." << std::endl;
		return;
	}
	User& user = users[username];
	if (user.GetPassword() != password) {
		std::cout << "Error: Incorrect password for user '" << username << "'." << std::endl;
		return;
	}
	currentUser = &user;
	std::cout << "User '" << username << "' logged in successfully." << std::endl;
}

/*
Logs out a user from the forum given a username.

Parameters:
	username: the username of the user to be logged out
Returns: nothing
*/
void Forum::Logout(const std::string& username) {
	if (users.count(username) == 0) {
		std::cout << "Error: User '" << username << "' not found." << std::endl;
		return;
	}
	currentUser = nullptr;
	std::cout << "User '" << username << "' logged out successfully." << std::endl;
}

/*
Checks if a user is logged in.

Parameters: none
Returns: boolean: value indicating whether a user is logged in
*/
bool Forum::CheckUser() {
	return this -> currentUser != nullptr;
}

/*
Displays all topics in the forum.

Parameters: none
Returns: nothing
*/
void Forum::ViewTopics() {
	std::cout << "Topics:" << std::endl;
	for (const Topic& topic : topics) {
		std::cout << topic.GetTitle() << std::endl;
	}
}

/*
Views the posts associated with a given topic.

Parameters:
	topicTitle: the title of the topic to view posts from
Returns: nothing
*/
void Forum::ViewPosts(const std::string& topicTitle) {
	for (const Topic& topic : topics) {
		if (topic.GetTitle() == topicTitle) {
			std::cout << "Posts in '" << topic.GetTitle() << "':" << std::endl;
			for (const Post& post : topic.GetPosts()) {
				std::cout << post << std::endl;
			}
			return;
		}
	}
	std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
}

/*
Creates a topic with given title.

Parameters:
	topicTitle: the title of the topic to be created
Returns: nothing
*/
void Forum::CreateTopic(const std::string& topicTitle) {
	Topic topic;
	topic.SetTitle(topicTitle);
	topics.push_back(topic);
	std::cout << "Topic '" << topicTitle << "' created." << std::endl;
}

/*
Adds a post to a topic if it exists in the forum.

Parameters:
	topicTitle: the title of the topic to add the post to
	post: the post to add
Returns: nothing
*/
void Forum::CreatePost(const std::string& topicTitle, const Post& post) {
	for (Topic& topic : topics) {
		if (topic.GetTitle() == topicTitle) {
			topic.AddPost(post);
			std::cout << "Post '" << post << "' added to '" << topicTitle << "'." << std::endl;
			return;
		}
	}
	std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
}

/*
Edits a post in a given topic given a username, topic title, post title, and the new post.
Username is used to check if the user is the author of the post.

Parameters:
	username: the username of the post's author
	topicTitle: the title of the topic containing the post
	postTitle: the title of the post to edit
	newPost: the new post object to replace the existing one
Returns: nothing
*/
void Forum::EditPost(const std::string& username, const std::string& topicTitle, const std::string& postTitle, const Post& newPost) {
	for (Topic& topic : topics) {
		if (topic.GetTitle() == topicTitle) {
			std::vector<Post> posts = topic.GetPosts();
			for (Post& p : posts) {
				if (p.GetTitle() == postTitle) {
					// Check if username matches
					if (p.GetAuthor() != username) {
						std::cout << "Error: User '" << username << "' is not the author of post '" << postTitle << "'." << std::endl;
						return;
					}
					std::vector<Post> replies = p.GetReplies();
					p = newPost;
					p.SetReplies(replies);
					topic.SetPosts(posts);
					std::cout << "Post '" << postTitle << "' edited to '" << newPost << "' in '" << topicTitle << "'." << std::endl;
					return;
				}
			}
			std::cout << "Error: Post '" << postTitle << "' not found in '" << topicTitle << "'." << std::endl;
			return;
		}
	}
	std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
}

/*
Deletes a post from a topic in the forum given the username, topic title, and post title.
Username is used to check if the user is the author of the post.

Parameters:
	username: username of the author of the post
	topicTitle: title of the topic the post is in
	postTitle: title of the post
Returns: nothing
*/
void Forum::DeletePost(const std::string& username, const std::string& topicTitle, const std::string& postTitle) {
	for (Topic& topic : topics) {
		if (topic.GetTitle() == topicTitle) {
			std::vector<Post> posts = topic.GetPosts();
			for (Post& p : posts) {
				if (p.GetTitle() == postTitle) {
					// Check if username matches
					if (p.GetAuthor() != username) {
						std::cout << "Error: User '" << username << "' is not the author of post '" << postTitle << "'." << std::endl;
						return;
					}
					posts.erase(std::remove(posts.begin(), posts.end(), p), posts.end());
					topic.SetPosts(posts);
					std::cout << "Post '" << postTitle << "' deleted from '" << topicTitle << "'." << std::endl;
					return;
				}
			}
			std::cout << "Error: Post '" << postTitle << "' not found in '" << topicTitle << "'." << std::endl;
			return;
		}
	}
	std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
}

/*
Adds a reply to a specific post in a topic.

Parameters:
	topicTitle: the title of the topic to which the post belongs
	postTitle: the title of the post to which the reply is to be added
	reply: the reply to be added
Returns: nothing
*/
void Forum::AddReply(const std::string& topicTitle, const std::string& postTitle, const Post& reply) {
	for (Topic& topic : topics) {
		if (topic.GetTitle() == topicTitle) {
			int postIndex = topic.FindPost(postTitle);
			if (postIndex == -1) {
				std::cout << "Error: PostTitle '" << postTitle << "' not found in '" << topicTitle << "'." << std::endl;
				return;
			}
			std::vector<Post> posts = topic.GetPosts();
			Post post = posts[postIndex];
			post.AddReply(reply);
			posts[postIndex] = post;
			topic.SetPosts(posts);
			std::cout << "Reply '" << reply.GetTitle() << "' added to '" << postTitle << "'." << std::endl;
			return;
		}
	}
	std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
}

/*
Sticks a topic to the top of the Forum's topics.

Parameters:
	topicTitle: the title of the topic to stick
Returns: nothing
*/
void Forum::StickTopic(const std::string& topicTitle) {
	for (int i = 0; i < topics.size(); i++) {
		if (topics[i].GetTitle() == topicTitle) {
			Topic topic = topics[i];
			int index = 0;
			for (int i = 0; i < topics.size(); i++) {
				if (topics[i].GetTitle() == topic.GetTitle()) {
					index = i;
					break;
				}
			}
			topics.erase(index);
			topics.insert(0, topic);
			std::cout << "Topic '" << topicTitle << "' stuck to the top." << std::endl;
			return;
		}
	}
	std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
}

/*
Push a topic to the bottom of the forum given a topic title.

Parameters:
	topicTitle: the title of the topic to unstick
Returns: nothing
*/
void Forum::UnstickTopic(const std::string& topicTitle) {
	for (int i = 0; i < topics.size(); i++) {
		if (topics[i].GetTitle() == topicTitle) {
			Topic topic = topics[i];
			topics.erase(i);
			topics.push_back(topic);
			std::cout << "Topic '" << topicTitle << "' un-stuck from the top." << std::endl;
			return;
		}
	}
	std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
}

/*
Sticks a post to the top of a given topic.

Parameters:
	topicTitle: the title of the topic
	postTitle: the title of the post to be stuck to the top
Returns: nothing
*/
void Forum::StickPost(const std::string& topicTitle, const std::string& postTitle) {
	int topicIndex = FindTopic(topicTitle);
	if (topicIndex == -1) {
		std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
		return;
	}
	int postIndex = topics[topicIndex].FindPost(postTitle);
	if (postIndex == -1) {
		std::cout << "Error: PostTitle '" << postTitle << "' not found in topic '" << topicTitle << "'." << std::endl;
		return;
	}
	Topic& topic = topics[topicIndex];
	Post p = topic.GetPost(postIndex);
	topic.RemovePost(p);
	topic.InsertPost(p, 0);
	std::cout << "Post '" << p.GetTitle() << "' stuck to the top of topic '" << topicTitle << "'." << std::endl;
}

/*
Push a post to the bottom of a given topic.

Parameters:
	topicTitle: the title of the topic
	postTitle: the title of the post to unstick
Returns: nothing
*/
void Forum::UnstickPost(const std::string& topicTitle, const std::string& postTitle) {
	int topicIndex = FindTopic(topicTitle);
	if (topicIndex == -1) {
		std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
		return;
	}

	int postIndex = topics[topicIndex].FindPost(postTitle);
	if (postIndex == -1) {
		std::cout << "Error: PostTitle '" << postTitle << "' not found in topic '" << topicTitle << "'." << std::endl;
		return;
	}

	Topic& topic = topics[topicIndex];
	Post p = topic.GetPost(postIndex);
	topic.RemovePost(p);
	topic.InsertPost(p);
	std::cout << "Post '" << p.GetTitle() << "' un-stuck from the top of topic '" << topicTitle << "'." << std::endl;
}

/*
Finds a topic in the forum given its title.

Parameters:
	topicTitle: the title of the topic to search for
Returns: index of the topic or -1 if not found
*/
int Forum::FindTopic(const std::string& topicTitle) {
	for (int i = 0; i < topics.size(); i++) {
		if (topics[i].GetTitle() == topicTitle) {
			return i;
		}
	}
	return -1;
}

/*
Sorts the topics in the forum using a Merge Sort algorithm.

Parameters:
	none
Returns: nothing
*/
void Forum::SortTopics() {
	MergeSort(topics);
}

/*
Sorts the posts of a given topic using a Merge Sort algorithm.

Parameters:
	topicTitle: a string representing the title of the topic
Returns: nothing
*/
void Forum::SortPosts(const std::string& topicTitle) {
	for (Topic& topic : topics) {
		if (topic.GetTitle() == topicTitle) {
			std::vector<Post> posts = topic.GetPosts();
			MergeSort(posts);
			topic.SetPosts(posts);
			std::cout << "Posts for '" << topicTitle << "' sorted." << std::endl;
			return;
		}
	}
	std::cout << "Error: Topic '" << topicTitle << "' not found." << std::endl;
}