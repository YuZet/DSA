/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991

This class implements a Forum system with features such as creating topics, creating posts,
editing and deleting posts, adding replies to posts, sorting topics and posts and sticking
topics and posts. It also supports user authentication and data persistence.
*/

#include <iostream>
#include <string>
#include "Forum.h"
#include "Post.h"

/*
Testing function for the Forum class.

Parameters: none
Returns: nothing
*/
void Testing() {
	// Create a new Forum instance
	Forum forum;

	// Load and save data
	forum.Load();
	forum.Save();

	// Add some Users
	forum.Register("User 1", "password1");
	forum.Register("User 2", "password2");

	// Login User
	forum.Login("User 1", "password");
	forum.Login("User 1", "password1");

	// Add some Topics
	forum.CreateTopic("Topic 1");
	forum.CreateTopic("Topic 2");

	// Add some Posts to a Topic
	Post post1("User 1", "Post 1", "Content 1");
	Post post2("User 1", "Post 2", "Content 2");
	forum.CreatePost("Topic 1", post1);
	forum.CreatePost("Topic 1", post2);

	// Edit a Post in a Topic
	Post post3("User 1", "Post 3", "Edited Content");
	forum.EditPost("User 1", "Topic 1", "Post 1", post3);

	// Delete a Post in a Topic
	forum.DeletePost("User 1", "Topic 1", "Post 3");

	// Show all Topics and Posts
	forum.ViewTopics();
	forum.ViewPosts("Topic 1");

	// Stick and Unstick a Topic
	forum.StickTopic("Topic 1");
	forum.UnstickTopic("Topic 1");

	// Sort Topics and Posts
	forum.SortTopics();
	forum.SortPosts("Topic 1");
}

/*
Provides the main menu logic for the forum application

Parameters: none
Returns: nothing
*/
int main()
{
	// Testing the class and methods
	//Testing();

	Forum forum;
	forum.Load();

	std::string username;
	std::string password;
	std::string topicTitle;
	std::string postTitle;
	std::string newPostTitle;
	std::string postContent;
	std::string newPostContent;
	std::string replyTitle;
	std::string replyContent;
	int choice;

	while (!forum.CheckUser())
	{
		std::cout << "\n";
		std::cout << "1. Register\n";
		std::cout << "2. Login\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice)
		{
		case 1:
			std::cout << "Enter your desired username: ";
			std::getline(std::cin, username);
			std::cout << "Enter your desired password: ";
			std::getline(std::cin, password);
			forum.Register(username, password);
			break;
		case 2:
			std::cout << "Enter your username: ";
			std::getline(std::cin, username);
			std::cout << "Enter your password: ";
			std::getline(std::cin, password);
			forum.Login(username, password);
			break;
		default:
			std::cout << "Invalid choice. Try again.\n";
			break;
		}
	}

	while (forum.CheckUser())
	{
		std::cout << "\n";
		std::cout << "Welcome, " << username << "!\n";
		std::cout << "1. Create a topic\n";
		std::cout << "2. View all topics\n";
		std::cout << "3. View a specific topic\n";
		std::cout << "4. Create a post\n";
		std::cout << "5. Edit a post\n";
		std::cout << "6. Delete a post\n";
		std::cout << "7. Reply to a post\n";
		std::cout << "8. Sort topics\n";
		std::cout << "9. Sort posts\n";
		std::cout << "10. Stick Topic\n";
		std::cout << "11. Unstick Topic\n";
		std::cout << "12. Stick Post\n";
		std::cout << "13. Unstick Post\n";
		std::cout << "14. Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice)
		{
		case 1:
			std::cout << "Enter the topic title: ";
			std::getline(std::cin, topicTitle);
			forum.CreateTopic(topicTitle);
			break;
		case 2:
			forum.ViewTopics();
			break;
		case 3:
			std::cout << "Enter the topic title: ";
			std::getline(std::cin, topicTitle);
			forum.ViewPosts(topicTitle);
			break;
		case 4:
			std::cout << "Enter topic to create post in: ";
			std::getline(std::cin, topicTitle);
			std::cout << "Enter post title: ";
			std::getline(std::cin, postTitle);
			std::cout << "Enter post content: ";
			std::getline(std::cin, postContent);
			forum.CreatePost(topicTitle, Post(username, postTitle, postContent));
			break;
		case 5:
			std::cout << "Enter topic to edit post in: ";
			std::getline(std::cin, topicTitle);
			std::cout << "Enter title of post to edit: ";
			std::getline(std::cin, postTitle);
			std::cout << "Enter new post title: ";
			std::getline(std::cin, newPostTitle);
			std::cout << "Enter new post content: ";
			std::getline(std::cin, newPostContent);
			forum.EditPost(username, topicTitle, postTitle, Post(username, newPostTitle, newPostContent));
			break;
		case 6:
			std::cout << "Enter topic to delete post in: ";
			std::getline(std::cin, topicTitle);
			std::cout << "Enter title of post to delete: ";
			std::getline(std::cin, postTitle);
			forum.DeletePost(username, topicTitle, postTitle);
			break;
		case 7:
			std::cout << "Enter topic to reply to post in: ";
			std::getline(std::cin, topicTitle);
			std::cout << "Enter title of post to reply to: ";
			std::getline(std::cin, postTitle);
			std::cout << "Enter reply title: ";
			std::getline(std::cin, replyTitle);
			std::cout << "Enter reply content: ";
			std::getline(std::cin, replyContent);
			forum.AddReply(topicTitle, postTitle, Post(username, replyTitle, replyContent));
			break;
		case 8:
			forum.SortTopics();
			break;
		case 9:
			std::cout << "Enter topic to sort: ";
			std::getline(std::cin, topicTitle);
			forum.SortPosts(topicTitle);
			break;
		case 10:
			std::cout << "Enter topic to stick: ";
			std::getline(std::cin, topicTitle);
			forum.StickTopic(topicTitle);
			break;
		case 11:
			std::cout << "Enter topic to unstick: ";
			std::getline(std::cin, topicTitle);
			forum.UnstickTopic(topicTitle);
			break;
		case 12:
			std::cout << "Enter topic to stick post in: ";
			std::getline(std::cin, topicTitle);
			std::cout << "Enter post title to stick: ";
			std::getline(std::cin, postTitle);
			forum.StickPost(topicTitle, postTitle);
			break;
		case 13:
			std::cout << "Enter topic to unstick post in: ";
			std::getline(std::cin, topicTitle);
			std::cout << "Enter post title to unstick: ";
			std::getline(std::cin, postTitle);
			forum.UnstickPost(topicTitle, postTitle);
			break;
		case 14:
			forum.Logout(username);
			forum.Save();
			std::cout << "Logging out...\n";
			break;
		default:
			std::cout << "Invalid choice. Try again.\n";
			break;
		}
	}
	return 0;
}