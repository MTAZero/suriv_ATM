#include "CorasickAlgorithm.h"



CorasickAlgorithm::CorasickAlgorithm()
{
	InitTree();
	
}


CorasickAlgorithm::~CorasickAlgorithm()
{
}

void CorasickAlgorithm::InitTree() {
	/// Khoi tao cay
	this->Tree = new Node();
	this->Tree->Parent = NULL;
	foru(i, 0, 15) this->Tree->Link[i] = NULL;
	this->Tree->isVirus = false;
	this->Tree->f = NULL;
	this->Tree->index = 0;
	this->Tree->depth = 0;
}

bool CorasickAlgorithm::isHexStyle(Virus &a) {
	// Kiểm tra dạng hex của tên virus và chuẩn hóa thành các ký tự 0-9 và A-F
	string name = a.HexString;

	foru(i, 0, name.size() - 1) {
		if (name[i] >= 'A' && name[i] <= 'F') continue;
		if (name[i] >= 'a' && name[i] <= 'f') {
			name[i] = name[i] - 32;
			continue;
		}
		if (name[i] >= '0' && name[i] <= '9') continue;
		return false;
	}

	a.HexString = name;
	return true;
}

void CorasickAlgorithm::AddVirus(Virus a) {
	if (isHexStyle(a))
		this->listVirus.push_back(a);
}

/// chưa hoàn thành
vector<Virus> CorasickAlgorithm::Scan(string HexString) {
	vector<Virus> ans;

	Virus z = Virus("z", HexString);

	if (!isHexStyle(z)) return ans;
	HexString = z.HexString;

	//cout << HexString << endl;

	Node *cur = this->Tree;
	this->Tree->Parent = this->Tree;
	foru(i, 0, HexString.size() - 1) {
		char curChar = HexString[i];
		int curInt = Helper::ConvertHexToInt(curChar);

		while (cur != NULL && cur != this->Tree && cur->Link[curInt] == NULL) cur = cur->f;

		if (cur->Link[curInt] != NULL) {
			cur = cur->Link[curInt];
			if (cur->isVirus) ans.push_back(cur->virus);
		}
	}

	return ans;
}

void CorasickAlgorithm::BuildTree() {
	BuildTrieTree();
	BuildCalFCM();
}

// Tao ra cay Trie tree de luu virus
void CorasickAlgorithm::BuildTrieTree() {
	/// cnt dung de luu index cua cac Node
	int cnt = 0;
	
	if (!listVirus.empty()) {
		foru(index, 0, listVirus.size() - 1) {
			Virus virus = listVirus[index];
			string name = virus.HexString;

			Node* cur = this->Tree;

			foru(i, 0, name.size() - 1) {
				char curChar = name[i];
				int curInt = Helper::ConvertHexToInt(curChar);
				

				if (cur->Link[curInt] == NULL) {
					/// Khoi tao Node
					cur->Link[curInt] = new Node();
					cur->Link[curInt]->Parent = cur;
					foru(j, 0, 15) cur->Link[curInt]->Link[j] = NULL;
					cur->Link[curInt]->index = ++cnt;
					cur->Link[curInt]->f = NULL;
					cur->Link[curInt]->depth = cur->depth + 1;
					cur->Link[curInt]->label = curInt;
					cur->Link[curInt]->isVirus = false;
					cur->virus = Virus("","");
				}

				cur = cur->Link[curInt];
			}

			/// đánh dấu đây là 1 nút cuối cùng của 1 con virus
			cur->isVirus = true;
			cur->virus = listVirus[index];
		}
	}
}

/// Hàm xây dựng các cạnh không khớp
void CorasickAlgorithm::BuildCalFCM() {
	/// Dùng hàng đợi để sắp xếp các node theo thứ tự độ sâu :D
	queue<Node> pq;
	pq.push(*(this->Tree));

	while (!pq.empty()) {
		/// lấy ra node có độ sâu nhỏ nhất
		Node k = pq.front();
		Node *kz = &pq.front();

		//cout << k.index << " " << Helper::ConvertIntToHex(k.label) << endl;

		int ChildLabel = kz->label;

		Node *parent = kz->Parent;
		Node *Child = this->Tree; 
		
		if (parent != NULL) {
			Child = parent->Link[ChildLabel];
			parent = parent->f;
			while (parent!=NULL && parent != this->Tree && parent->Link[ChildLabel] == NULL) parent = parent->f;
			
			if (parent != NULL && parent->Link[ChildLabel] != NULL) {
				Child->f = parent->Link[ChildLabel];
				//cout << " * " << endl;
			}
			else Child->f = this->Tree;
		}

		foru(i, 0, 15) if (kz->Link[i] != NULL) {
			Node zz = *(kz->Link[i]);
			pq.push(zz);
		}
		pq.pop();
	}
}

// Hàm in ra cây
void CorasickAlgorithm::PrintTree(Node *t) {
	cout << "---------------------------------------------" << endl;
	cout << "Node thu " << t->index << " : " << endl;
	cout << "Label : " << Helper::ConvertIntToHex(t->label) << endl;
	if (t->Parent!=NULL) cout << "Parent : " << t->Parent->index << endl;
	Node *z = t->f;
	if (z != NULL) {
		cout << "F = " << z->index << " " << Helper::ConvertIntToHex(z->label) << endl;
		//cout << "---------------------------------------------" << endl;
	}
	else {
		cout << "F = " << "NULL" << endl;
	}

	foru(i, 0, 15) if (t->Link[i] != NULL) PrintTree(t->Link[i]);
}

// in cay de debug
void CorasickAlgorithm::Debug() {
	PrintTree(this->Tree);
}

void CorasickAlgorithm::PrintVirus(vector<Virus> a) {
	if (a.empty()) {
		//cout << "------------------------------------------" << endl;
		cout << "Empty List" << endl << endl;
		return;
	}
	foru(i, 0, a.size() - 1) {
		Virus k = a[i];
		cout << "------------------------------------------" << endl;
		cout << "Index: " << i << endl;
		cout << "Name: " << k.Name << endl;
		cout << "HexString: " << k.HexString << endl;
	}
	cout << endl;
}
