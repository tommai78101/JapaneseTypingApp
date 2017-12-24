#include "common.h"

Vector2D CreateIsometricPosition(Vector2D velocity, UpOrientation orientation) {
	Vector2D result = {};
	switch (orientation) {
		case NORTHEAST: {
			result.x = (velocity.x - velocity.y);
			result.y = (velocity.x + velocity.y) / 2.0f;
			break;
		}
		default:
		case NORTH: {
			result = velocity;
			break;
		}
		case NORTHWEST: {
			result.x = (velocity.x + velocity.y);
			result.y = (-velocity.x + velocity.y) / 2.0f;
			break;
		}
	}
	return result;
}

//TrieNode functions

TrieNode* TrieNode::SearchChild(SDL_Keycode& value) {
	for (TrieNode* it : this->children) {
		if (it->value == value) {
			return it;
		}
	}
	return nullptr;
}

void TrieNode::Clear() {
	for (TrieNode* it : this->children) {
		it->Clear();
		it->children.clear();
		delete it;
	}
}

//End of TrieNode functions

//Trie functions

void Trie::Insert(std::vector<SDL_Keycode>& value, char* leafValue) {
	TrieNode* iterator = this->root;
	for (std::vector<SDL_Keycode>::iterator it = value.begin(); iterator && it != value.end(); it++) {
		std::ptrdiff_t diff = std::distance(value.begin(), it);
		SDL_Keycode child = *(value.begin() + diff);
		TrieNode* node = iterator->SearchChild(child);
		if (!node) {
			node = new TrieNode();
			node->value = child;
			iterator->children.push_back(node);
		}
		iterator = node;
	}
	iterator->leafValue = leafValue;
}

bool Trie::Contains(std::vector<SDL_Keycode>& value) {
	TrieNode* iterator = this->root;
	for (std::vector<SDL_Keycode>::iterator it = value.begin(); iterator && it != value.end(); it++) {
		iterator = iterator->SearchChild(*it);
	}
	return (iterator && iterator->IsLeaf());
}

char* Trie::Get(std::vector<SDL_Keycode>& value) {
	TrieNode* iterator = this->root;
	for (std::vector<SDL_Keycode>::iterator it = value.begin(); iterator && it != value.end(); it++) {
		iterator = iterator->SearchChild(*it);
	}
	if (iterator && iterator->IsLeaf()) {
		return iterator->leafValue;
	}
	return nullptr;
}

TrieNode* Trie::GetNode(std::vector<SDL_Keycode>& value) {
	TrieNode* iterator = this->root;
	for (std::vector<SDL_Keycode>::iterator it = value.begin(); iterator && it != value.end(); it++) {
		iterator = iterator->SearchChild(*it);
	}
	return iterator; //May be nullptr or valid TrieNode.
}

//End of Trie functions