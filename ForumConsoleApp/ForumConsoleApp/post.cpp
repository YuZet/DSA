/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#include <string>
#include <vector>
#include <iostream>
#include "Post.h"

/*
Constructor for Post class.

Parameters:
	author: the author of the post
	title: the title of the post
	content: the content of the post
Returns: nothing
*/
Post::Post(const std::string& author, const std::string& title, const std::string& content) : author(author), title(title), content(content) {}

/*
Gets the name of the post's author.

Parameters: none
Returns: string containing the author's name
*/
std::string Post::GetAuthor() const { return author; }

/*
Returns the author of the post.

Parameters:
	none
Returns:
	std::string: The author of the post
*/
std::string Post::GetTitle() const { return title; }

/*
Returns the post content.

Parameters:
	none
Returns:
	string: the post content
*/
std::string Post::GetContent() const { return content; }

/*
Gets the replies of a post.

Parameters: none
Returns: vector of Post objects
*/
std::vector<Post> Post::GetReplies() const { return replies; }

/*
Sets the replies of a post.

Parameters:
	newReplies: vector of Post objects
Returns: nothing
*/
void Post::SetReplies(const std::vector<Post>& newReplies) { replies = newReplies; }

/*
Adds a reply to a post.

Parameters:
	reply: the reply to be added
Returns: nothing
*/
void Post::AddReply(const Post& reply) { replies.push_back(reply); }

/*
Outputs a post and its associated replies to an ostream.

Parameters:
	os: ostream object
	post: Post object
Returns: ostream object
*/
std::ostream& operator<<(std::ostream& os, const Post& post) {
	os << "Title: " << post.title << '\n' << "Author: " << post.author << '\n' << "Content: " << post.content << '\n';
	for (const Post& reply : post.replies) {
		os << '\t' << "Reply: " << reply.title << '\n' << '\t' << "Author: " << post.author << '\n' << '\t' << "Content: " << post.content << '\n';
	}
	return os;
}

/*
Reads in a post object from an istream object.

Parameters:
	is: istream object
	post: Post object
Returns: istream object
*/
std::istream& operator>>(std::istream& is, Post& post) {
	std::string title;
	is >> title >> post.author >> post.content;
	int replyCount;
	is >> replyCount;
	post.replies.resize(replyCount);
	for (Post& reply : post.replies) {
		is >> reply;
	}
	return is;
}

/*
Compares two post objects for equality.

Parameters:
	lhs: First post object
	rhs: Second post object
Returns: Boolean value indicating if the two posts are equal
*/
bool operator==(const Post& lhs, const Post& rhs) {
	return lhs.author == rhs.author && lhs.title == rhs.title && lhs.content == rhs.content;
}

/*
Compares the title of two Post objects.

Parameters:
	other: Post object to compare to
Returns: boolean indicating whether this Post's title is alphabetically before the other Post's title
*/
bool Post::operator<(const Post& other) const {
	return this->title < other.title;
}