
/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#include "topic.h"

/*
Constructor for Topic class.

Parameters:
	title: title of the topic
Returns: nothing
*/
Topic::Topic(const std::string& title) : title(title) {}

/*
Gets the title of a topic.

Parameters:
	none
Returns:
	title: a string containing the title of the topic
*/
const std::string& Topic::GetTitle() const { return title; }

/*
Gets the posts associated with this topic.

Parameters:
	none
Returns:
	std::vector<Post>: the posts associated with this topic
*/
const std::vector<Post> Topic::GetPosts() const { return posts; }

/*
Sets the title of the topic.

Parameters:
	title: the new title of the topic
Returns: nothing
*/
void Topic::SetTitle(const std::string& title) { this->title = title; }

/*
Sets the topic's posts.

Parameters:
	newPosts: vector of Post objects
Returns: nothing
*/
void Topic::SetPosts(const std::vector<Post>& newPosts) { posts = newPosts; }

/*
Adds a post to the topic.

Parameters:
	post: Post object to be added
Returns: nothing
*/
void Topic::AddPost(const Post& post) { posts.push_back(post); }

/*
Finds the index of a given post in the vector of posts

Parameters:
	post: Post to find
Returns:
	int: Index of the given post in the vector of posts. -1 if the post is not found.
*/
int Topic::FindPost(const Post& post) {
	for (int i = 0; i < posts.size(); i++) {
		if (posts[i] == post) {
			return i;
		}
	}
	return -1;
}

/*
Finds a post with the given title in the topic's list of posts.

Parameters:
	postTitle: The title of the post to be found.
Returns: The index of the post in the list of posts, or -1 if not found.
*/
int Topic::FindPost(const std::string& postTitle) {
	for (int i = 0; i < posts.size(); i++) {
		if (posts[i].GetTitle() == postTitle) {
			return i;
		}
	}
	return -1;
}

/*
Removes a post from the forum given a Post object.

Parameters:
	post: The Post object to be removed from the forum
Returns: nothing
*/
void Topic::RemovePost(const Post& post) {
	int index = FindPost(post);
	if (index != -1) {
		posts.erase(posts.begin() + index);
	}
}

/*
Removes a post from the topic given its index.

Parameters:
	postIndex: index of the post to be removed
Returns: nothing
*/
void Topic::RemovePost(int postIndex) {
	if (postIndex >= 0 && postIndex < posts.size()) {
		posts.erase(posts.begin() + postIndex);
	}
}

/*
Shows all posts, replies and their content for a given topic.
Parameters: none
Returns: nothing
*/
void Topic::ShowPosts() const {
	if (posts.empty()) {
		std::cout << "No posts found for '" << title << "'." << std::endl;
		return;
	}

	std::cout << "Posts for '" << title << "':" << std::endl;
	for (const Post& post : posts) {
		std::cout << "Author: " << post.GetAuthor() << std::endl;
		std::cout << "Content: " << post.GetContent() << std::endl;
		std::cout << "Replies: " << std::endl;
		for (const Post& reply : post.GetReplies()) {
			std::cout << "Author: " << reply.GetAuthor() << std::endl;
			std::cout << "Content: " << reply.GetContent() << std::endl;
		}
		std::cout << std::endl;
	}
}

/*
Adds a reply to a post in a topic given the post content, the reply author, and the reply content.

Parameters:
	postContent: The content of the post to reply to
	replyAuthor: The author of the reply
	replyContent: The content of the reply
Returns: nothing
*/
void Topic::AddReply(const std::string& postContent, const std::string& replyAuthor, const std::string& replyContent) {
	for (Post& post : posts) {
		if (post.GetContent() == postContent) {
			post.AddReply({ replyAuthor, "Reply", replyContent});
			return;
		}
	}
	std::cout << "Error: Post '" << postContent << "' not found in '" << title << "'." << std::endl;
}

/*
Retrieves a post from the forum's post array given an index.

Parameters:
	postIndex: index of the post in the array
Returns: the post with the given index
*/
Post Topic::GetPost(int postIndex) const {
	return posts[postIndex];
}

/*
Inserts a post into the topic.

Parameters:
	post: the post to be inserted
Returns: nothing
*/
void Topic::InsertPost(const Post& post) {
	posts.push_back(post);
}

/*
Inserts a post into the topic at the given index.

Parameters:
	post: Post object to be inserted
	postIndex: index at which post should be inserted
Returns: nothing
*/
void Topic::InsertPost(const Post& post, int postIndex) {
	posts.insert(posts.begin() + postIndex, post);
}

/*
Outputs a Topic object to an ostream.

Parameters:
	os: ostream object
	topic: Topic object
Returns: ostream object
*/
std::ostream& operator<<(std::ostream& os, const Topic& topic) {
	os << topic.title << '\n' << topic.posts.size() << '\n';
	for (const Post& post : topic.posts) {
		os << post << '\n';
	}
	return os;
}

/*
Reads in a Topic from an input stream.

Parameters:
	is: input stream
	topic: Reference to a Topic object to write data to
Returns: input stream
*/
std::istream& operator>>(std::istream& is, Topic& topic) {
	int postCount;
	is >> topic.title >> postCount;
	topic.posts.clear();
	for (int i = 0; i < postCount; i++) {
		Post post;
		is >> post;
		topic.posts.push_back(post);
	}
	return is;
}

/*
Compares two topics and returns true if the first one is lesser than the second one.

Parameters:
	rhs: the topic to compare with
Returns: bool
*/
bool Topic::operator<(const Topic& rhs) const {
	return this->title < rhs.title;
}