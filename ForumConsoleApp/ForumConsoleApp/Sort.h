/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#pragma once
#include <vector>
#include "Array.h"

template <typename T>
void MergeSort(std::vector<T>& arr) {
	if (arr.size() <= 1) {
		return;
	}
	std::vector<T> left(arr.begin(), arr.begin() + arr.size() / 2);
	std::vector<T> right(arr.begin() + arr.size() / 2, arr.end());

	MergeSort(left);
	MergeSort(right);

	int i = 0;
	int j = 0;
	int k = 0;

	while (i < left.size() && j < right.size()) {
		if (left[i] < right[j]) {
			arr[k++] = left[i++];
		}
		else {
			arr[k++] = right[j++];
		}
	}

	while (i < left.size()) {
		arr[k++] = left[i++];
	}

	while (j < right.size()) {
		arr[k++] = right[j++];
	}
};

template <typename T>
void MergeSort(Array<T>& arr) {
	if (arr.size() <= 1) {
		return;
	}
	std::vector<T> left(arr.begin(), arr.begin() + arr.size() / 2);
	std::vector<T> right(arr.begin() + arr.size() / 2, arr.end());

	MergeSort(left);
	MergeSort(right);

	int i = 0;
	int j = 0;
	int k = 0;

	while (i < left.size() && j < right.size()) {
		if (left[i] < right[j]) {
			arr[k++] = left[i++];
		}
		else {
			arr[k++] = right[j++];
		}
	}

	while (i < left.size()) {
		arr[k++] = left[i++];
	}

	while (j < right.size()) {
		arr[k++] = right[j++];
	}
};