#include "common.h"

// Helper functions

std::string SubstringUpToFirstUTF8(std::string& value, char* firstContainer) {
	std::string returnValue = value.substr(0, value.find(firstContainer));
	return returnValue;
}

std::string SubstringInsideUTF8(std::string& value, char* firstContainer, char* lastContainer) {
	size_t containerLength = std::strlen(firstContainer);
	size_t offset = value.find(firstContainer, 0);
	size_t length = value.find(lastContainer, offset) - offset - containerLength;
	size_t newOffset = offset + containerLength;
	std::string returnValue = value.substr(newOffset, length);
	return returnValue;
}

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

//KeyCodeTrieNode functions

bool KeyCodeTrieNode::IsLeaf() {
	return this->children.empty();
}

KeyCodeTrieNode* KeyCodeTrieNode::SearchChild(SDL_Keycode& value) {
	for (KeyCodeTrieNode* it : this->children) {
		if (it->value == value) {
			return it;
		}
	}
	return nullptr;
}

void KeyCodeTrieNode::Clear() {
	for (KeyCodeTrieNode* it : this->children) {
		it->Clear();
		it->children.clear();
		delete it;
	}
}

//End of KeyCodeTrieNode functions

//KeyCodeTrie functions

void KeyCodeTrie::Insert(std::vector<SDL_Keycode>& value, char* leafValue) {
	KeyCodeTrieNode* iterator = this->root;
	for (std::vector<SDL_Keycode>::iterator it = value.begin(); iterator && it != value.end(); it++) {
		std::ptrdiff_t diff = std::distance(value.begin(), it);
		SDL_Keycode child = *(value.begin() + diff);
		KeyCodeTrieNode* node = iterator->SearchChild(child);
		if (!node) {
			node = new KeyCodeTrieNode();
			node->value = child;
			iterator->children.push_back(node);
		}
		iterator = node;
	}
	iterator->leafValue = leafValue;
}

bool KeyCodeTrie::Contains(std::vector<SDL_Keycode>& value) {
	KeyCodeTrieNode* iterator = this->root;
	for (std::vector<SDL_Keycode>::iterator it = value.begin(); iterator && it != value.end(); it++) {
		iterator = iterator->SearchChild(*it);
	}
	return (iterator && iterator->IsLeaf());
}

char* KeyCodeTrie::Get(std::vector<SDL_Keycode>& value) {
	KeyCodeTrieNode* iterator = this->root;
	for (std::vector<SDL_Keycode>::iterator it = value.begin(); iterator && it != value.end(); it++) {
		iterator = iterator->SearchChild(*it);
	}
	if (iterator && iterator->IsLeaf()) {
		return iterator->leafValue;
	}
	return nullptr;
}

KeyCodeTrieNode* KeyCodeTrie::GetNode(std::vector<SDL_Keycode>& value) {
	KeyCodeTrieNode* iterator = this->root;
	for (std::vector<SDL_Keycode>::iterator it = value.begin(); iterator && it != value.end(); it++) {
		iterator = iterator->SearchChild(*it);
	}
	return iterator; //May be nullptr or valid KeyCodeTrieNode.
}

//End of KeyCodeTrie functions

//VocabularyTrieNode functions

bool VocabularyTrieNode::IsLeaf() {
	return this->children.empty();
}

void VocabularyTrieNode::Clear() {
	for (VocabularyTrieNode* it : this->children) {
		it->Clear();
		it->children.clear();
		delete it;
	}
}

VocabularyTrieNode* VocabularyTrieNode::SearchChild(char32_t& value) {
	for (VocabularyTrieNode* it : this->children) {
		//See usage: http://www.cplusplus.com/reference/string/string/compare/
		//"it->vocabulary" is "compared string"
		//"value" is "comparing string".

		std::u32string comparing;
		comparing += value;
		std::u32string compared;
		compared += it->vocabulary;

		//Comparing strings of size 1.
		int result = compared.compare(comparing);
		if (result == 0) {	
			//Is 0: value is equal to it->vocabulary
			return it;
		}
	}
	return nullptr;
}

//End of VocabularyTrieNode functions

//VocabularyTrie functions

void VocabularyTrie::Insert(std::string& value, std::string& leafValue, std::string& meaning) {
	std::u32string newValue;
	Convert_utf8_utf32(value, newValue);
	std::u32string newLeafValue;
	Convert_utf8_utf32(leafValue, newLeafValue);
	std::u32string newMeaning;
	Convert_utf8_utf32(meaning, newMeaning);
	this->Insert(newValue, newLeafValue, newMeaning);
}

void VocabularyTrie::Insert(char* value, char* leafValue, char* meaning) {
	std::string newValue(value);
	std::string newLeafValue(leafValue);
	std::string newMeaning(meaning);
	this->Insert(newValue, newLeafValue, newMeaning);
}

void VocabularyTrie::Insert(std::u32string& value, std::u32string& leafValue, std::u32string& meaning) {
	VocabularyTrieNode* iterator = this->root;
	for (int i = 0; i < value.size(); i++) {
		char32_t child = value[i];
		VocabularyTrieNode* node = iterator->SearchChild(child);
		if (!node) {
			node = new VocabularyTrieNode();
			node->vocabulary = child;
			iterator->children.push_back(node);
		}
		iterator = node;
	}
	iterator->pronunciation = leafValue;
	iterator->englishDefinition = meaning;
	this->size++;
}

bool VocabularyTrie::Contains(std::string& value) {
	std::u32string newValue;
	Convert_utf8_utf32(value, newValue);
	return this->Contains(newValue);
}

bool VocabularyTrie::Contains(char* value) {
	std::string newValue(value);
	return this->Contains(newValue);
}

bool VocabularyTrie::Contains(std::u32string& value) {
	VocabularyTrieNode* iterator = this->root;
	VocabularyTrieNode* result;
	for (int i = 0; i < value.size(); i++) {
		result = iterator->SearchChild(value[i]);
		if (result) {
			iterator = result;
		}
	}
	return (iterator && iterator->IsLeaf());
}

std::string VocabularyTrie::GetPronunciation(std::string& value) {
	std::u32string newValue;
	Convert_utf8_utf32(value, newValue);
	return this->GetPronunciation(newValue);
}

std::string VocabularyTrie::GetPronunciation(char* value) {
	std::string newValue(value);
	return this->GetPronunciation(newValue);
}

std::string VocabularyTrie::GetPronunciation(std::u32string& value) {
	VocabularyTrieNode* iterator = this->root;
	VocabularyTrieNode* result;
	for (int i = 0; i < value.size(); i++) {
		result = iterator->SearchChild(value[i]);
		if (result) {
			iterator = result;
		}
	}
	if (iterator && iterator->IsLeaf()) {
		std::string strResult;
		Convert_utf32_utf8(iterator->pronunciation, strResult);
		return strResult;
	}
	return nullptr;
}

std::string VocabularyTrie::GetDefinition(std::string& value) {
	std::u32string newValue;
	Convert_utf8_utf32(value, newValue);
	return this->GetDefinition(newValue);
}

std::string VocabularyTrie::GetDefinition(char* value) {
	std::string newValue(value);
	return this->GetDefinition(newValue);
}

std::string VocabularyTrie::GetDefinition(std::u32string& value) {
	VocabularyTrieNode* iterator = this->root;
	VocabularyTrieNode* result;
	for (int i = 0; i < value.size(); i++) {
		result = iterator->SearchChild(value[i]);
		if (result) {
			iterator = result;
		}
	}
	if (iterator && iterator->IsLeaf()) {
		std::string strResult;
		Convert_utf32_utf8(iterator->englishDefinition, strResult);
		return strResult;
	}
	return nullptr;
}

VocabularyTrieNode* VocabularyTrie::GetNode(std::string& value) {
	std::u32string newValue;
	Convert_utf8_utf32(value, newValue);
	return this->GetNode(newValue);
}

VocabularyTrieNode* VocabularyTrie::GetNode(char* value) {
	std::string newValue(value);
	return this->GetNode(newValue);
}

VocabularyTrieNode* VocabularyTrie::GetNode(std::u32string& value) {
	VocabularyTrieNode* iterator = this->root;
	VocabularyTrieNode* result;
	for (int i = 0; i < value.size(); i++) {
		result = iterator->SearchChild(value[i]);
		if (result) {
			iterator = result;
		}
	}
	if (iterator && iterator->IsLeaf())
		return iterator;
	return nullptr;
}

unsigned int VocabularyTrie::GetSize() {
	return this->size;
}

//End of VocabularyTrie functions