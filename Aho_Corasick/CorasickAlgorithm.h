#pragma once

#include "BXT.h"
#include "Virus.h"
#include "Helper.h"

class Node {
public:
	Node *Parent;
	/// duong dan den cac node tiep theo
	Node *Link[16];
	int label;
	Node *f; // Nut se nhay ve sau khi tim kiem khong dung

public:
	bool isVirus = false;
	int index;
	int depth;
	Virus virus;
};

class CorasickAlgorithm
{
public:
	CorasickAlgorithm();
	~CorasickAlgorithm();

private:
	vector<Virus> listVirus;
	int count;
	Node* Tree;

public:
	void AddVirus(Virus a);
	void BuildTree();
	void Debug();
	void PrintVirus(vector<Virus> a);

	/// Tra ve danh sách virus chứa trong file
	vector<Virus> Scan(string HexString);
private:
	void BuildTrieTree();
	void BuildCalFCM();	
	void InitTree();
	bool isHexStyle(Virus &a);

// các hàm phục vụ debug
private:
	void PrintTree(Node *t);
};

