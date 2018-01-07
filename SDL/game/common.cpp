#include "common.h"

// Helper functions

static void Convert_utf8_utf32(std::string& input, std::u32string& output) {
	const uint32_t UTF32Mask = 0x001fffff;
	int i = 0;
	output.clear();
	while (1) {
		uint8_t iterator = (uint8_t) input[i];
		if (!iterator)
			break;
		if (iterator < 0x80) {
			//1 codepoint
			output += (char32_t) (UTF32Mask & iterator);
			i++;
		}
		else if (iterator < 0xC0) {
			//midstream identifier, invalid
			i++;
			continue;
		}
		else if (iterator < 0xE0) {
			//2 codepoint
			uint8_t firstPoint = (uint8_t) (input[i] & 0x1F);
			uint8_t secondPoint = (uint8_t) (input[i + 1] & 0x3F);
			if (!IsLittleEndian()) {
				output += (char32_t) (UTF32Mask & ((secondPoint << 6) | firstPoint));
			}
			else {
				output += (char32_t) (UTF32Mask & ((firstPoint << 6) | secondPoint));
			}
			i += 2;
		}
		else if (iterator < 0xF0) {
			//3 codepoints
			uint8_t firstPoint = (uint8_t) (input[i] & 0x0F);
			uint8_t secondPoint = (uint8_t) (input[i + 1] & 0x3F);
			uint8_t thirdPoint = (uint8_t) (input[i + 2] & 0x3F);
			if (!IsLittleEndian()) {
				output += (char32_t) (UTF32Mask & ((thirdPoint << 12) | (secondPoint << 6) | firstPoint));
			}
			else {
				output += (char32_t) (UTF32Mask & ((firstPoint << 12) | (secondPoint << 6) | thirdPoint));
			}
			i += 3;
		}
		else if (iterator < 0xF8) {
			//4 codepoints
			uint8_t firstPoint = (uint8_t) (input[i] & 0x07);
			uint8_t secondPoint = (uint8_t) (input[i + 1] & 0x3F);
			uint8_t thirdPoint = (uint8_t) (input[i + 2] & 0x3F);
			uint8_t fourthPoint = (uint8_t) (input[i + 3] & 0x3F);
			if (!IsLittleEndian()) {
				output += (char32_t) (UTF32Mask & ((fourthPoint << 18) | (thirdPoint << 12) | (secondPoint << 6) | firstPoint));
			}
			else {
				output += (char32_t) (UTF32Mask & ((firstPoint << 18) | (secondPoint << 12) | (thirdPoint << 6) | fourthPoint));
			}
			i += 4;
		}
		else {
			//Invalid everything else
			i++;
		}
	}
}

static void Convert_utf32_utf8(std::u32string& input, std::string& output) {
	const uint8_t UTF8Midstream = 0x80;
	const uint8_t UTF8MidstreamMask = 0x3f;
	int i = 0;
	output.clear();
	while (1) {
		uint32_t iterator = (uint32_t) input[i];
		if (!iterator)
			break;
		if (iterator < 0x80) {
			//U+0000..U+007F
			output += (uint8_t) (0x7f & iterator);
		}
		else if (iterator < 0x800) {
			//U+0080..U+07FF
			uint8_t firstPoint = (uint8_t) (((0xDF << 6) & iterator) >> 6);
			uint8_t secondPoint = (uint8_t) (0x3F & iterator);
			if (!IsLittleEndian()) {
				output += (uint8_t) (0xC0 | (0xDF & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & firstPoint));
			}
			else {
				output += (uint8_t) (0xC0 | (0xDF & firstPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
			}
		}
		else if (iterator < 0xE000) {
			//U+8000..U+D7FF (TUS 2.0)
			uint8_t firstPoint = (uint8_t) (((0xF << 12) & iterator) >> 12);
			uint8_t secondPoint = (uint8_t) (((0x3F << 6) & iterator) >> 6);
			uint8_t thirdPoint = (uint8_t) (0x3F & iterator);
			if (!IsLittleEndian()) {
				output += (uint8_t) (0xE0 | (0x0F & thirdPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & firstPoint));
			}
			else {
				output += (uint8_t) (0xE0 | (0x0F & firstPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & thirdPoint));
			}
		}
		else if (iterator < 0x10000) {
			//U+E000..U+FFFF (TUS 3.1)
			uint8_t firstPoint = (uint8_t) (((0xF << 12) & iterator) >> 12);
			uint8_t secondPoint = (uint8_t) (((0x3F << 6) & iterator) >> 6);
			uint8_t thirdPoint = (uint8_t) (0x3F & iterator);
			if (!IsLittleEndian()) {
				output += (uint8_t) (0xE0 | (0x0F & thirdPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & firstPoint));
			}
			else {
				output += (uint8_t) (0xE0 | (0x0F & firstPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & thirdPoint));
			}
		}
		else if (iterator < 0x1FFFF) {
			uint8_t firstPoint = (uint8_t) (((0x7 << 18) & iterator) >> 18);
			uint8_t secondPoint = (uint8_t) (((0x3F << 12) & iterator) >> 12);
			uint8_t thirdPoint = (uint8_t) (((0x3F << 6) & iterator) >> 6);
			uint8_t fourthPoint = (uint8_t) (0x3F & iterator);
			if (!IsLittleEndian()) {
				output += (uint8_t) (0xE0 | (0x07 & fourthPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & thirdPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & firstPoint));
			}
			else {
				output += (uint8_t) (0xE0 | (0x07 & firstPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & secondPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & thirdPoint));
				output += (uint8_t) (UTF8Midstream | (UTF8MidstreamMask & fourthPoint));
			}
		}
		i++;
	}
}

static inline std::string SubstringUpToFirstUTF8(std::string& value, char* firstContainer) {
	std::string returnValue = value.substr(0, value.find(firstContainer));
	return returnValue;
}

static inline std::string SubstringInsideUTF8(std::string& value, char* firstContainer, char* lastContainer) {
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