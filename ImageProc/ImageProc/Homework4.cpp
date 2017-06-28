#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
#include <deque>
#include <string>
#include <set>
#include <sstream>
using namespace std;

typedef struct trnode{
	char ch;//代表字符
	double fre;//字符出现频度
	trnode *left, *right;
	trnode(){}
	trnode(char ch, double fre) :ch(ch),fre(fre),left(NULL),right(NULL){}
	trnode(trnode *t1, trnode *t2) : fre(t1->fre + t2->fre), left(t2), right(t1){}//频率大的在左边
}TrNode, *tree;

bool cmp(const trnode* t1, const trnode* t2){
	return t1->fre<t2->fre;
}

void readFile(deque<tree>& leaves, int& length, double& entropy, map<char, int>& fres){
	freopen("Project_Huffman Coding.txt", "r", stdin);
	char s;
	length = 0;
	entropy = 0;
	double gl = 0;
	
	while ((s = getchar()) != EOF){
		length++;
		if (fres.count(s)) fres[s]++;
		else fres[s] = 1;
	}
	for (map<char, int>::iterator it = fres.begin(); it != fres.end(); it++){
		double rate = (it->second / (double)length);
		tree t = new TrNode(it->first, rate);
		entropy = entropy - rate*log2(rate);
		leaves.push_back(t);
		//printf("%d:%f\n", it->first, it->second / (double)length);
	}
}

void deleteTree(tree t){
	if (t->left) deleteTree(t->left);
	if (t->right) deleteTree(t->right);
	delete t;
}
void encode(tree T,string s,string sadd, map<char, string>& ENCODE){
	s += sadd;
	if (!(T->left || T->right)) {
		ENCODE[T->ch] = s;
	}
	else{
		if (T->left) encode(T->left, s,"0", ENCODE);
		if (T->right) encode(T->right,s,"1", ENCODE);
	}
}
void generate(map<char, string> ENCODE){
	string str;
	freopen("Project_Huffman Coding.txt", "r", stdin);
	char s;
	while ((s = getchar()) != EOF){
		str += ENCODE[s];
	}
	int len = str.size();
	if (len % 8 != 0){
		int r = 8 - len % 8;
		for (int i = 0; i < r; i++){
			str += "0";
		}
	}
	while (str != ""){
		string a = str.substr(0, 8);
		str = str.substr(8);
		int num = 0;
		//cout << a << " ";
		for (int i = 0; i < 8; i++){
			//cout << a[i] << " ";
			num *= 2;
			num += a[i] - '0';
		}
		printf("%c",num);
	}
}
void myHuffman(){
	freopen("Huffman_result.txt", "w", stdout);
	double entropy;
	deque<tree> leaves;
	tree huffmanTree;
	map<char, int> fres;
	map<char, string> ENCODE;
	double avalen=0;
	int length;
	readFile(leaves, length, entropy, fres);
	sort(leaves.begin(), leaves.end(), cmp);
	while (1){
		sort(leaves.begin(),leaves.end(),cmp);
		tree t1 = leaves.front();
		leaves.pop_front();
		if (leaves.empty()){
			huffmanTree = t1;
			break;
		}
		tree t2 = leaves.front();
		leaves.pop_front();
		leaves.push_back(new TrNode(t1, t2));
		tree t = leaves.back();
		//cout << t1->fre << "+" << t2->fre << "=" << t->fre << " -- " << (t->fre - t1->fre - t2->fre) << endl;
	}
	encode(huffmanTree,"","", ENCODE);
	deleteTree(huffmanTree);
	for (map<char, string>::iterator it = ENCODE.begin(); it != ENCODE.end(); it++){
		printf("%3d: ", it->first);
		cout << (it->second) << endl;
		avalen += fres[it->first]/(double)length * it->second.size();
	}
	cout << "avalen: " << avalen << " entropy: " << entropy << " efficiency: " << entropy / avalen * 100 << "%" << endl;
	generate(ENCODE);
	freopen("debug.txt", "w", stdout);
}