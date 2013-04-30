#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <list>

using namespace std;

//beginning of classes
class Trie
{
public:
  Trie(): root(new Node()){}

	struct Node
	{
		map<char, Node*> links;
		bool terminal;
		string word;
		Node() : terminal(false){}
	};

	// shared_ptr<Node> root();
	
	//insert words into the trie
	void insert(string word);
	
	//returns a list of words
	list<string> words(string word);

private:
	Node* root;

	//return lists of words starting from the start node
	list<string> completeWord(string prefix, Node* start);

	//returns lists of pointers to words beginning with word
	list<Node*> searchWord(string word);
};

list<string> Trie::words(string word)
{
	list<string> result;

	auto nodes = searchWord(word);
	completeWord(word, root);

	result.splice(result.end(), completeWord(word, root));
	
	for(auto i : nodes)
	{
		result.splice(result.end(), completeWord(word, i));
	}

	return result;
}

list<Trie::Node*> Trie::searchWord(string word)
{
	auto p = root;
	list<Node*> starts;
	int i = 0;
	int length = word.length();
	stack<Node*> branches;

	branches.push(p);

	while(branches.size() != 0)
	{
		Node* tmp = branches.top();
		branches.pop();
		if(i >= length)
			continue;
		auto it = tmp->links.find(word.at(i));

		if(it == tmp->links.end())
		{
			i = 0;
		}
		else
		{
			for(auto j : tmp->links)
			{
				branches.push(j.second);
			}
			i++;
			if(i == 1)
			{
				starts.push_back(tmp);
			}
		}
	}

	return starts;
}

void Trie::insert(string word)
{
	auto rt = root;
	// cout << word;
	for(int i = 0; i < word.length(); i++)
	{
		if(rt->links.find(word.at(i)) == rt->links.end())
		{
			rt->links[word.at(i)] = new Node();
		}

		rt = rt->links[word.at(i)];
	}

	rt->terminal = true;
	rt->word = word;
}

list<string> Trie::completeWord(string prefix, Node* start)
{
	
	auto p = start;

	stack<Node*> branches;
	list<string> results;
	for(auto i : prefix)
	{
		auto pos = p->links.find(i); 
		if(pos == p->links.end())
		{
			return results;
		}		
		p = pos->second;
	}
	
	branches.push(p);

	while((branches.size() != 0))
	{
		Node* tmp = branches.top();
		branches.pop();
		for(auto j : tmp->links)
		{
			branches.push(j.second);
		}
		if(tmp->terminal)
		{
			results.push_back(tmp->word);
		}
	}
	return results;
}

int main()
{
//contains some basic test
	string me = "Great\n";
	// cout << me;
	Trie trie;
	trie.insert("awesomeness");
	trie.insert("awesomeone");

	cout << "Enter Word to complete: ";
	cin >> me;

	auto result = trie.words(me);

	if(result.size() != 0)
	{
		for(auto i : result)
		{
			cout << i <<endl;
		}
	}
	else
	{
		cout << "No completions\n";
	}

	return 0;
}
