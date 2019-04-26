#include "input.h"

//Helper functions

void ConvertKeycodesToString(std::vector<SDL_Keycode>& codes, std::string& output) {
	output.clear();
	for (std::vector<SDL_Keycode>::iterator it = codes.begin(); it != codes.end(); it++) {
		char diff = static_cast<char>((*it) - SDLK_a);
		output.push_back('a' + diff);
	}
}

void InsertGlyph(Input* input, bool isHiragana, KeyCodeTrie& trie, std::initializer_list<SDL_Keycode> list, char* glyph) {
	static std::vector<SDL_Keycode> key;
	if (glyph) {
		//char* duplicate = strdupWrapper(glyph);
		key.insert(key.end(), list);
		trie.Insert(key, glyph);
		key.clear();

		//Store the glyph for future uses.
		std::string glyphString(glyph);
		input->GetCharacterGlyphs(isHiragana).insert(glyphString);
	}
}

void InitializeGlyphMap(Input* input, KeyCodeTrie& hiraganaTrie, KeyCodeTrie& katakanaTrie) {
	//Note(asperatology): There may be more than one method of typing the characters
	//out, therefore, there may be multiple entries for one glyph.
	//Glyphs may be 2 characters long.
	//Big sized glyphs go on top
	//Small sized glyphs go on bottom
	//Sorted by "hiragana order"

	//Hiragana

	//あ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_a }, const_cast<char*>(u8"あ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_a }, const_cast<char*>(u8"ぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_a }, const_cast<char*>(u8"ぁ"));

	//い
	InsertGlyph(input, true, hiraganaTrie, { SDLK_i }, const_cast<char*>(u8"い"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_y, SDLK_i }, const_cast<char*>(u8"い"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_i }, const_cast<char*>(u8"ぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_y, SDLK_i }, const_cast<char*>(u8"ぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_i }, const_cast<char*>(u8"ぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_y, SDLK_i }, const_cast<char*>(u8"ぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_y, SDLK_e }, const_cast<char*>(u8"いぇ"));

	//う
	InsertGlyph(input, true, hiraganaTrie, { SDLK_u }, const_cast<char*>(u8"う"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_h, SDLK_u }, const_cast<char*>(u8"う"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_u }, const_cast<char*>(u8"う"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_u }, const_cast<char*>(u8"ぅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_u }, const_cast<char*>(u8"ぅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_h, SDLK_a }, const_cast<char*>(u8"うぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_h, SDLK_i }, const_cast<char*>(u8"うぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_i }, const_cast<char*>(u8"うぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_e }, const_cast<char*>(u8"うぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_h, SDLK_e }, const_cast<char*>(u8"うぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_h, SDLK_o }, const_cast<char*>(u8"うぉ"));

	//え
	InsertGlyph(input, true, hiraganaTrie, { SDLK_e }, const_cast<char*>(u8"え"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_e }, const_cast<char*>(u8"ぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_y, SDLK_e }, const_cast<char*>(u8"ぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_e }, const_cast<char*>(u8"ぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_y, SDLK_e }, const_cast<char*>(u8"ぇ"));

	//お
	InsertGlyph(input, true, hiraganaTrie, { SDLK_o }, const_cast<char*>(u8"お"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_o }, const_cast<char*>(u8"ぉ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_o }, const_cast<char*>(u8"ぉ"));

	//------

	//か
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_a }, const_cast<char*>(u8"か"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_a }, const_cast<char*>(u8"か"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_k, SDLK_a }, const_cast<char*>(u8"ゕ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_k, SDLK_a }, const_cast<char*>(u8"ゕ"));

	//き
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_i }, const_cast<char*>(u8"き"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_y, SDLK_i }, const_cast<char*>(u8"きぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_y, SDLK_e }, const_cast<char*>(u8"きぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_y, SDLK_a }, const_cast<char*>(u8"きゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_y, SDLK_u }, const_cast<char*>(u8"きゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_y, SDLK_o }, const_cast<char*>(u8"きょ"));

	//く
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_u }, const_cast<char*>(u8"く"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_u }, const_cast<char*>(u8"く"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_u }, const_cast<char*>(u8"く"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_w, SDLK_a }, const_cast<char*>(u8"くぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_a }, const_cast<char*>(u8"くぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_w, SDLK_a }, const_cast<char*>(u8"くぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_i }, const_cast<char*>(u8"くぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_w, SDLK_i }, const_cast<char*>(u8"くぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_y, SDLK_i }, const_cast<char*>(u8"くぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_w, SDLK_u }, const_cast<char*>(u8"くぅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_e }, const_cast<char*>(u8"くぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_w, SDLK_e }, const_cast<char*>(u8"くぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_y, SDLK_e }, const_cast<char*>(u8"くぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_o }, const_cast<char*>(u8"くぉ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_w, SDLK_o }, const_cast<char*>(u8"くぉ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_y, SDLK_a }, const_cast<char*>(u8"くゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_y, SDLK_u }, const_cast<char*>(u8"くゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_q, SDLK_y, SDLK_o }, const_cast<char*>(u8"くょ"));

	//け
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_e }, const_cast<char*>(u8"け"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_k, SDLK_e }, const_cast<char*>(u8"ゖ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_k, SDLK_e }, const_cast<char*>(u8"ゖ"));

	//こ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_o }, const_cast<char*>(u8"こ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_k, SDLK_o }, const_cast<char*>(u8"こ"));

	//------

	//さ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_a }, const_cast<char*>(u8"さ"));

	//し
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_i }, const_cast<char*>(u8"し"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_h, SDLK_i }, const_cast<char*>(u8"し"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_i }, const_cast<char*>(u8"し"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_y, SDLK_i }, const_cast<char*>(u8"しぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_h, SDLK_e }, const_cast<char*>(u8"しぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_y, SDLK_e }, const_cast<char*>(u8"しぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_h, SDLK_a }, const_cast<char*>(u8"しゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_y, SDLK_a }, const_cast<char*>(u8"しゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_h, SDLK_u }, const_cast<char*>(u8"しゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_y, SDLK_u }, const_cast<char*>(u8"しゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_h, SDLK_o }, const_cast<char*>(u8"しょ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_y, SDLK_o }, const_cast<char*>(u8"しょ"));

	//す
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_u }, const_cast<char*>(u8"す"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_w, SDLK_a }, const_cast<char*>(u8"すぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_w, SDLK_i }, const_cast<char*>(u8"すぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_w, SDLK_u }, const_cast<char*>(u8"すぅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_w, SDLK_e }, const_cast<char*>(u8"すぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_w, SDLK_o }, const_cast<char*>(u8"すぉ"));

	//せ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_e }, const_cast<char*>(u8"せ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_e }, const_cast<char*>(u8"せ"));

	//そ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_s, SDLK_o }, const_cast<char*>(u8"そ"));

	//------

	//た
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_a }, const_cast<char*>(u8"た"));

	//ち
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_h, SDLK_i }, const_cast<char*>(u8"ち"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_i }, const_cast<char*>(u8"ち"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_y, SDLK_i }, const_cast<char*>(u8"ちぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_y, SDLK_i }, const_cast<char*>(u8"ちぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_h, SDLK_e }, const_cast<char*>(u8"ちぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_y, SDLK_e }, const_cast<char*>(u8"ちぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_y, SDLK_e }, const_cast<char*>(u8"ちぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_h, SDLK_a }, const_cast<char*>(u8"ちゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_y, SDLK_a }, const_cast<char*>(u8"ちゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_y, SDLK_a }, const_cast<char*>(u8"ちゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_h, SDLK_u }, const_cast<char*>(u8"ちゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_y, SDLK_u }, const_cast<char*>(u8"ちゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_y, SDLK_u }, const_cast<char*>(u8"ちゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_h, SDLK_o }, const_cast<char*>(u8"ちょ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_c, SDLK_y, SDLK_o }, const_cast<char*>(u8"ちょ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_y, SDLK_o }, const_cast<char*>(u8"ちょ"));

	//つ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_s, SDLK_u }, const_cast<char*>(u8"つ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_u }, const_cast<char*>(u8"つ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_s, SDLK_a }, const_cast<char*>(u8"つぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_s, SDLK_i }, const_cast<char*>(u8"つぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_s, SDLK_e }, const_cast<char*>(u8"つぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_s, SDLK_o }, const_cast<char*>(u8"つぉ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_t, SDLK_s, SDLK_u }, const_cast<char*>(u8"っ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_t, SDLK_u }, const_cast<char*>(u8"っ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_t, SDLK_s, SDLK_u }, const_cast<char*>(u8"っ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_t, SDLK_u }, const_cast<char*>(u8"っ"));

	//て
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_e }, const_cast<char*>(u8"て"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_h, SDLK_i }, const_cast<char*>(u8"てぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_h, SDLK_e }, const_cast<char*>(u8"てぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_h, SDLK_a }, const_cast<char*>(u8"てゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_h, SDLK_u }, const_cast<char*>(u8"てゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_h, SDLK_o }, const_cast<char*>(u8"てょ"));


	//と
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_o }, const_cast<char*>(u8"と"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_w, SDLK_a }, const_cast<char*>(u8"とぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_w, SDLK_i }, const_cast<char*>(u8"とぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_w, SDLK_u }, const_cast<char*>(u8"とぅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_w, SDLK_e }, const_cast<char*>(u8"とぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_t, SDLK_w, SDLK_o }, const_cast<char*>(u8"とぉ"));

	//------

	//な
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_a }, const_cast<char*>(u8"な"));

	//に
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_i }, const_cast<char*>(u8"に"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_y, SDLK_i }, const_cast<char*>(u8"にぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_y, SDLK_e }, const_cast<char*>(u8"にぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_y, SDLK_a }, const_cast<char*>(u8"にゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_y, SDLK_u }, const_cast<char*>(u8"にゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_y, SDLK_o }, const_cast<char*>(u8"にょ"));

	//ぬ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_u }, const_cast<char*>(u8"ぬ"));

	//ね
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_e }, const_cast<char*>(u8"ね"));

	//の
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_o }, const_cast<char*>(u8"の"));

	//------

	//は
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_a }, const_cast<char*>(u8"は"));

	//ひ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_i }, const_cast<char*>(u8"ひ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_y, SDLK_i }, const_cast<char*>(u8"ひぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_y, SDLK_e }, const_cast<char*>(u8"ひぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_y, SDLK_a }, const_cast<char*>(u8"ひゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_y, SDLK_u }, const_cast<char*>(u8"ひゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_y, SDLK_o }, const_cast<char*>(u8"ひょ"));

	//ふ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_u }, const_cast<char*>(u8"ふ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_u }, const_cast<char*>(u8"ふ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_a }, const_cast<char*>(u8"ふぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_w, SDLK_a }, const_cast<char*>(u8"ふぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_i }, const_cast<char*>(u8"ふぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_w, SDLK_i }, const_cast<char*>(u8"ふぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_y, SDLK_i }, const_cast<char*>(u8"ふぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_w, SDLK_u }, const_cast<char*>(u8"ふぅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_e }, const_cast<char*>(u8"ふぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_w, SDLK_e }, const_cast<char*>(u8"ふぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_y, SDLK_e }, const_cast<char*>(u8"ふぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_o }, const_cast<char*>(u8"ふぉ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_w, SDLK_o }, const_cast<char*>(u8"ふぉ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_y, SDLK_a }, const_cast<char*>(u8"ふゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_y, SDLK_u }, const_cast<char*>(u8"ふゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_f, SDLK_y, SDLK_o }, const_cast<char*>(u8"ふょ"));

	//へ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_e }, const_cast<char*>(u8"へ"));

	//ほ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_h, SDLK_o }, const_cast<char*>(u8"ほ"));

	//------

	//ま
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_a }, const_cast<char*>(u8"ま"));

	//み
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_i }, const_cast<char*>(u8"み"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_y, SDLK_i }, const_cast<char*>(u8"みぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_y, SDLK_e }, const_cast<char*>(u8"みぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_y, SDLK_a }, const_cast<char*>(u8"みゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_y, SDLK_u }, const_cast<char*>(u8"みゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_y, SDLK_o }, const_cast<char*>(u8"みょ"));

	//む
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_u }, const_cast<char*>(u8"む"));

	//め
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_e }, const_cast<char*>(u8"め"));

	//も
	InsertGlyph(input, true, hiraganaTrie, { SDLK_m, SDLK_o }, const_cast<char*>(u8"も"));

	//------

	//や
	InsertGlyph(input, true, hiraganaTrie, { SDLK_y, SDLK_a }, const_cast<char*>(u8"や"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_y, SDLK_a }, const_cast<char*>(u8"ゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_y, SDLK_a }, const_cast<char*>(u8"ゃ"));

	//ゆ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_y, SDLK_u }, const_cast<char*>(u8"ゆ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_y, SDLK_u }, const_cast<char*>(u8"ゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_y, SDLK_u }, const_cast<char*>(u8"ゅ"));

	//よ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_y, SDLK_o }, const_cast<char*>(u8"よ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_y, SDLK_o }, const_cast<char*>(u8"ょ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_y, SDLK_o }, const_cast<char*>(u8"ょ"));

	//------

	//ら
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_a }, const_cast<char*>(u8"ら"));

	//り
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_i }, const_cast<char*>(u8"り"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_y, SDLK_i }, const_cast<char*>(u8"りぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_y, SDLK_e }, const_cast<char*>(u8"りぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_y, SDLK_a }, const_cast<char*>(u8"りゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_y, SDLK_u }, const_cast<char*>(u8"りゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_y, SDLK_o }, const_cast<char*>(u8"りょ"));

	//る
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_u }, const_cast<char*>(u8"る"));

	//れ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_e }, const_cast<char*>(u8"れ"));

	//ろ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_r, SDLK_o }, const_cast<char*>(u8"ろ"));

	//------

	//わ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_a }, const_cast<char*>(u8"わ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_l, SDLK_w, SDLK_a }, const_cast<char*>(u8"ゎ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_w, SDLK_a }, const_cast<char*>(u8"ゎ"));

	//ゐ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_y, SDLK_i }, const_cast<char*>(u8"ゐ"));

	//ゑ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_y, SDLK_e }, const_cast<char*>(u8"ゑ"));

	//を
	InsertGlyph(input, true, hiraganaTrie, { SDLK_w, SDLK_o }, const_cast<char*>(u8"を"));

	//------

	//ん
	InsertGlyph(input, true, hiraganaTrie, { SDLK_n, SDLK_n }, const_cast<char*>(u8"ん"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_x, SDLK_n }, const_cast<char*>(u8"ん"));

	//------
	//Modifiers - Hiragana
	//が
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_a }, const_cast<char*>(u8"が"));

	//ぎ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_i }, const_cast<char*>(u8"ぎ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_y, SDLK_i }, const_cast<char*>(u8"ぎぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_y, SDLK_e }, const_cast<char*>(u8"ぎぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_y, SDLK_a }, const_cast<char*>(u8"ぎゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_y, SDLK_u }, const_cast<char*>(u8"ぎゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_y, SDLK_o }, const_cast<char*>(u8"ぎょ"));

	//ぐ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_u }, const_cast<char*>(u8"ぐ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_w, SDLK_a }, const_cast<char*>(u8"ぐぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_w, SDLK_i }, const_cast<char*>(u8"ぐぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_w, SDLK_u }, const_cast<char*>(u8"ぐぅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_w , SDLK_e }, const_cast<char*>(u8"ぐぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_w, SDLK_o }, const_cast<char*>(u8"ぐぉ"));

	//げ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_e }, const_cast<char*>(u8"げ"));

	//ご
	InsertGlyph(input, true, hiraganaTrie, { SDLK_g, SDLK_o }, const_cast<char*>(u8"ご"));

	//ざ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_a }, const_cast<char*>(u8"さ"));

	//じ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_i }, const_cast<char*>(u8"じ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_i }, const_cast<char*>(u8"じ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_y, SDLK_i }, const_cast<char*>(u8"じぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_y, SDLK_i }, const_cast<char*>(u8"じぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_e }, const_cast<char*>(u8"じぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_y, SDLK_e }, const_cast<char*>(u8"じぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_y, SDLK_e }, const_cast<char*>(u8"じぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_a }, const_cast<char*>(u8"じゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_y, SDLK_a }, const_cast<char*>(u8"じゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_y, SDLK_a }, const_cast<char*>(u8"じゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_u }, const_cast<char*>(u8"じゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_y, SDLK_u }, const_cast<char*>(u8"じゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_y, SDLK_u }, const_cast<char*>(u8"じゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_o }, const_cast<char*>(u8"じょ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_j, SDLK_y, SDLK_o }, const_cast<char*>(u8"じょ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_y, SDLK_o }, const_cast<char*>(u8"じょ"));

	//ず
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_u }, const_cast<char*>(u8"ず"));

	//ぜ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_e }, const_cast<char*>(u8"ぜ"));

	//ぞ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_z, SDLK_o }, const_cast<char*>(u8"ぞ"));

	//だ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_a }, const_cast<char*>(u8"だ"));

	//ぢ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_i }, const_cast<char*>(u8"ぢ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_y, SDLK_i }, const_cast<char*>(u8"ぢぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_y, SDLK_e }, const_cast<char*>(u8"ぢぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_y, SDLK_a }, const_cast<char*>(u8"ぢゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_y, SDLK_u }, const_cast<char*>(u8"ぢゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_y, SDLK_o }, const_cast<char*>(u8"ぢょ"));

	//づ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_u }, const_cast<char*>(u8"づ"));

	//で
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_e }, const_cast<char*>(u8"で"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_h, SDLK_i }, const_cast<char*>(u8"でぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_h, SDLK_e }, const_cast<char*>(u8"でぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_h, SDLK_a }, const_cast<char*>(u8"でゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_h, SDLK_u }, const_cast<char*>(u8"でゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_h, SDLK_o }, const_cast<char*>(u8"でょ"));

	//ど
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_o }, const_cast<char*>(u8"ど"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_w, SDLK_a }, const_cast<char*>(u8"どぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_w, SDLK_i }, const_cast<char*>(u8"どぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_w, SDLK_u }, const_cast<char*>(u8"どぅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_w, SDLK_e }, const_cast<char*>(u8"どぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_d, SDLK_w, SDLK_o }, const_cast<char*>(u8"どぉ"));

	//ば
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_a }, const_cast<char*>(u8"ば"));

	//ぱ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_a }, const_cast<char*>(u8"ぱ"));

	//び
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_i }, const_cast<char*>(u8"び"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_y, SDLK_i }, const_cast<char*>(u8"びぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_y, SDLK_e }, const_cast<char*>(u8"びぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_y, SDLK_a }, const_cast<char*>(u8"びゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_y, SDLK_u }, const_cast<char*>(u8"びゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_y, SDLK_o }, const_cast<char*>(u8"びょ"));

	//ぴ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_i }, const_cast<char*>(u8"ぴ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_y, SDLK_i }, const_cast<char*>(u8"ぴぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_y, SDLK_e }, const_cast<char*>(u8"ぴぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_y, SDLK_a }, const_cast<char*>(u8"ぴゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_y, SDLK_u }, const_cast<char*>(u8"ぴゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_y, SDLK_o }, const_cast<char*>(u8"ぴょ"));

	//ぶ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_u }, const_cast<char*>(u8"ぶ"));

	//ぷ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_u }, const_cast<char*>(u8"ぷ"));

	//べ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_e }, const_cast<char*>(u8"べ"));

	//ぺ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_e }, const_cast<char*>(u8"ぺ"));

	//ぼ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_b, SDLK_o }, const_cast<char*>(u8"ぼ"));

	//ぽ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_p, SDLK_o }, const_cast<char*>(u8"ぽ"));

	//ヴ
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_a }, const_cast<char*>(u8"ヴぁ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_i }, const_cast<char*>(u8"ヴぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_y, SDLK_i }, const_cast<char*>(u8"ヴぃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_e }, const_cast<char*>(u8"ヴぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_y, SDLK_e }, const_cast<char*>(u8"ヴぇ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_o }, const_cast<char*>(u8"ヴぉ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_y, SDLK_a }, const_cast<char*>(u8"ヴゃ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_y, SDLK_u }, const_cast<char*>(u8"ヴゅ"));
	InsertGlyph(input, true, hiraganaTrie, { SDLK_v, SDLK_y, SDLK_o }, const_cast<char*>(u8"ヴょ"));

	//------
	//Katakana
	//ア 
	InsertGlyph(input, false, katakanaTrie, { SDLK_a }, const_cast<char*>(u8"ア"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l , SDLK_a }, const_cast<char*>(u8"ァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x , SDLK_a }, const_cast<char*>(u8"ァ"));

	//イ
	InsertGlyph(input, false, katakanaTrie, { SDLK_i }, const_cast<char*>(u8"イ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_y, SDLK_i }, const_cast<char*>(u8"イ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_i }, const_cast<char*>(u8"ィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_y, SDLK_i }, const_cast<char*>(u8"ィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_i }, const_cast<char*>(u8"ィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_y, SDLK_i }, const_cast<char*>(u8"ィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_y, SDLK_e }, const_cast<char*>(u8"イェ"));

	//ウ
	InsertGlyph(input, false, katakanaTrie, { SDLK_u }, const_cast<char*>(u8"ウ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_h, SDLK_u }, const_cast<char*>(u8"ウ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_u }, const_cast<char*>(u8"ウ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_u }, const_cast<char*>(u8"ゥ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_u }, const_cast<char*>(u8"ゥ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_h, SDLK_a }, const_cast<char*>(u8"ウァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_h, SDLK_i }, const_cast<char*>(u8"ウィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_i }, const_cast<char*>(u8"ウィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_e }, const_cast<char*>(u8"ウェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_h, SDLK_e }, const_cast<char*>(u8"ウェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_h, SDLK_o }, const_cast<char*>(u8"ウォ"));

	//エ
	InsertGlyph(input, false, katakanaTrie, { SDLK_e }, const_cast<char*>(u8"エ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_e }, const_cast<char*>(u8"ェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_y, SDLK_e }, const_cast<char*>(u8"ェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_e }, const_cast<char*>(u8"ェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_y, SDLK_e }, const_cast<char*>(u8"ェ"));

	//オ
	InsertGlyph(input, false, katakanaTrie, { SDLK_o }, const_cast<char*>(u8"オ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_o }, const_cast<char*>(u8"ォ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_o }, const_cast<char*>(u8"ォ"));

	//------

	//カ
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_a }, const_cast<char*>(u8"カ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_a }, const_cast<char*>(u8"カ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_k, SDLK_a }, const_cast<char*>(u8"ヵ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_k, SDLK_a }, const_cast<char*>(u8"ヵ"));

	//キ
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_i }, const_cast<char*>(u8"キ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_y, SDLK_i }, const_cast<char*>(u8"キィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_y, SDLK_e }, const_cast<char*>(u8"キェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_y, SDLK_a }, const_cast<char*>(u8"キャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_y, SDLK_u }, const_cast<char*>(u8"キュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_y, SDLK_o }, const_cast<char*>(u8"キョ"));

	//ク
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_u }, const_cast<char*>(u8"ク"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_u }, const_cast<char*>(u8"ク"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_u }, const_cast<char*>(u8"ク"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_w, SDLK_a }, const_cast<char*>(u8"クァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_a }, const_cast<char*>(u8"クァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_w, SDLK_a }, const_cast<char*>(u8"クァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_i }, const_cast<char*>(u8"クィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_w, SDLK_i }, const_cast<char*>(u8"クィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_y, SDLK_i }, const_cast<char*>(u8"クィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_w, SDLK_u }, const_cast<char*>(u8"クゥ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_e }, const_cast<char*>(u8"クェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_w, SDLK_e }, const_cast<char*>(u8"クェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_y, SDLK_e }, const_cast<char*>(u8"クェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_o }, const_cast<char*>(u8"クォ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_w, SDLK_o }, const_cast<char*>(u8"クォ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_y, SDLK_a }, const_cast<char*>(u8"クャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_y, SDLK_u }, const_cast<char*>(u8"クュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_q, SDLK_y, SDLK_o }, const_cast<char*>(u8"クョ"));

	//ケ
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_e }, const_cast<char*>(u8"ケ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_k, SDLK_e }, const_cast<char*>(u8"ヶ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_k, SDLK_e }, const_cast<char*>(u8"ヶ"));

	//コ
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_o }, const_cast<char*>(u8"コ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_k, SDLK_o }, const_cast<char*>(u8"コ"));

	//------

	//サ
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_a }, const_cast<char*>(u8"サ"));

	//シ
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_i }, const_cast<char*>(u8"シ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_h, SDLK_i }, const_cast<char*>(u8"シ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_i }, const_cast<char*>(u8"シ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_y, SDLK_i }, const_cast<char*>(u8"シィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_h, SDLK_e }, const_cast<char*>(u8"シェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_y, SDLK_e }, const_cast<char*>(u8"シェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_h, SDLK_a }, const_cast<char*>(u8"シャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_y, SDLK_a }, const_cast<char*>(u8"シャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_h, SDLK_u }, const_cast<char*>(u8"シュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_y, SDLK_u }, const_cast<char*>(u8"シュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_h, SDLK_o }, const_cast<char*>(u8"ショ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_y, SDLK_o }, const_cast<char*>(u8"ショ"));

	//ス
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_u }, const_cast<char*>(u8"ス"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_w, SDLK_a }, const_cast<char*>(u8"スァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_w, SDLK_i }, const_cast<char*>(u8"スィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_w, SDLK_u }, const_cast<char*>(u8"スゥ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_w, SDLK_e }, const_cast<char*>(u8"スェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_w, SDLK_o }, const_cast<char*>(u8"スォ"));

	//セ
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_e }, const_cast<char*>(u8"セ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_e }, const_cast<char*>(u8"セ"));

	//ソ
	InsertGlyph(input, false, katakanaTrie, { SDLK_s, SDLK_o }, const_cast<char*>(u8"ソ"));

	//------

	//タ
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_a }, const_cast<char*>(u8"タ"));

	//チ
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_h, SDLK_i }, const_cast<char*>(u8"チ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_i }, const_cast<char*>(u8"チ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_y, SDLK_i }, const_cast<char*>(u8"チィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_y, SDLK_i }, const_cast<char*>(u8"チィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_h, SDLK_e }, const_cast<char*>(u8"チェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_y, SDLK_e }, const_cast<char*>(u8"チェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_y, SDLK_e }, const_cast<char*>(u8"チェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_h, SDLK_a }, const_cast<char*>(u8"チャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_y, SDLK_a }, const_cast<char*>(u8"チャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_y, SDLK_a }, const_cast<char*>(u8"チャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_h, SDLK_u }, const_cast<char*>(u8"チュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_y, SDLK_u }, const_cast<char*>(u8"チュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_y, SDLK_u }, const_cast<char*>(u8"チュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_h, SDLK_o }, const_cast<char*>(u8"チョ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_c, SDLK_y, SDLK_o }, const_cast<char*>(u8"チョ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_y, SDLK_o }, const_cast<char*>(u8"チョ"));

	//ツ
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_s, SDLK_u }, const_cast<char*>(u8"ツ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_u }, const_cast<char*>(u8"ツ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_s, SDLK_a }, const_cast<char*>(u8"ツァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_s, SDLK_i }, const_cast<char*>(u8"ツィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_s, SDLK_e }, const_cast<char*>(u8"ツェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_s, SDLK_o }, const_cast<char*>(u8"ツォ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_t, SDLK_s, SDLK_u }, const_cast<char*>(u8"ッ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_t, SDLK_u }, const_cast<char*>(u8"ッ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_t, SDLK_s, SDLK_u }, const_cast<char*>(u8"ッ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_t, SDLK_u }, const_cast<char*>(u8"ッ"));

	//テ
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_e }, const_cast<char*>(u8"テ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_h, SDLK_i }, const_cast<char*>(u8"ティ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_h, SDLK_e }, const_cast<char*>(u8"テェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_h, SDLK_a }, const_cast<char*>(u8"テャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_h, SDLK_u }, const_cast<char*>(u8"テュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_h, SDLK_o }, const_cast<char*>(u8"テョ"));


	//ト
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_o }, const_cast<char*>(u8"ト"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_w, SDLK_a }, const_cast<char*>(u8"トァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_w, SDLK_i }, const_cast<char*>(u8"トィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_w, SDLK_u }, const_cast<char*>(u8"トゥ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_w, SDLK_e }, const_cast<char*>(u8"トェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_t, SDLK_w, SDLK_o }, const_cast<char*>(u8"トォ"));

	//------

	//ナ
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_a }, const_cast<char*>(u8"ナ"));

	//ニ
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_i }, const_cast<char*>(u8"ニ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_y, SDLK_i }, const_cast<char*>(u8"ニィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_y, SDLK_e }, const_cast<char*>(u8"ニェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_y, SDLK_a }, const_cast<char*>(u8"ニャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_y, SDLK_u }, const_cast<char*>(u8"ニュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_y, SDLK_o }, const_cast<char*>(u8"ニョ"));

	//ヌ
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_u }, const_cast<char*>(u8"ヌ"));

	//ネ
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_e }, const_cast<char*>(u8"ネ"));

	//ノ
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_o }, const_cast<char*>(u8"ノ"));

	//------

	//ハ
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_a }, const_cast<char*>(u8"ハ"));

	//ヒ
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_i }, const_cast<char*>(u8"ヒ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_y, SDLK_i }, const_cast<char*>(u8"ヒィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_y, SDLK_e }, const_cast<char*>(u8"ヒェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_y, SDLK_a }, const_cast<char*>(u8"ヒャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_y, SDLK_u }, const_cast<char*>(u8"ヒュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_y, SDLK_o }, const_cast<char*>(u8"ヒョ"));

	//フ
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_u }, const_cast<char*>(u8"フ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_u }, const_cast<char*>(u8"フ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_a }, const_cast<char*>(u8"ファ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_w, SDLK_a }, const_cast<char*>(u8"ファ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_i }, const_cast<char*>(u8"フィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_w, SDLK_i }, const_cast<char*>(u8"フィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_y, SDLK_i }, const_cast<char*>(u8"フィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_w, SDLK_u }, const_cast<char*>(u8"フゥ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_e }, const_cast<char*>(u8"フェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_w, SDLK_e }, const_cast<char*>(u8"フェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_y, SDLK_e }, const_cast<char*>(u8"フェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_o }, const_cast<char*>(u8"フォ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_w, SDLK_o }, const_cast<char*>(u8"フォ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_y, SDLK_a }, const_cast<char*>(u8"フャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_y, SDLK_u }, const_cast<char*>(u8"フュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_f, SDLK_y, SDLK_o }, const_cast<char*>(u8"フョ"));

	//ヘ
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_e }, const_cast<char*>(u8"ヘ"));

	//ホ
	InsertGlyph(input, false, katakanaTrie, { SDLK_h, SDLK_o }, const_cast<char*>(u8"ホ"));

	//------

	//マ
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_a }, const_cast<char*>(u8"マ"));

	//ミ
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_i }, const_cast<char*>(u8"ミ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_y, SDLK_i }, const_cast<char*>(u8"ミィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_y, SDLK_e }, const_cast<char*>(u8"ミェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_y, SDLK_a }, const_cast<char*>(u8"ミャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_y, SDLK_u }, const_cast<char*>(u8"ミュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_y, SDLK_o }, const_cast<char*>(u8"ミョ"));

	//ム
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_u }, const_cast<char*>(u8"ム"));

	//メ
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_e }, const_cast<char*>(u8"メ"));

	//モ
	InsertGlyph(input, false, katakanaTrie, { SDLK_m, SDLK_o }, const_cast<char*>(u8"モ"));

	//------

	//ヤ
	InsertGlyph(input, false, katakanaTrie, { SDLK_y, SDLK_a }, const_cast<char*>(u8"ヤ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_y, SDLK_a }, const_cast<char*>(u8"ャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_y, SDLK_a }, const_cast<char*>(u8"ャ"));

	//ユ
	InsertGlyph(input, false, katakanaTrie, { SDLK_y, SDLK_u }, const_cast<char*>(u8"ユ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_y, SDLK_u }, const_cast<char*>(u8"ュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_y, SDLK_u }, const_cast<char*>(u8"ュ"));

	//ヨ
	InsertGlyph(input, false, katakanaTrie, { SDLK_y, SDLK_o }, const_cast<char*>(u8"ヨ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_y, SDLK_o }, const_cast<char*>(u8"ョ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_y, SDLK_o }, const_cast<char*>(u8"ョ"));

	//------

	//ラ
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_a }, const_cast<char*>(u8"ラ"));

	//リ
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_i }, const_cast<char*>(u8"リ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_y, SDLK_i }, const_cast<char*>(u8"リィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_y, SDLK_e }, const_cast<char*>(u8"リェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_y, SDLK_a }, const_cast<char*>(u8"リャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_y, SDLK_u }, const_cast<char*>(u8"リュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_y, SDLK_o }, const_cast<char*>(u8"リョ"));

	//ル
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_u }, const_cast<char*>(u8"ル"));

	//レ
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_e }, const_cast<char*>(u8"レ"));

	//ロ
	InsertGlyph(input, false, katakanaTrie, { SDLK_r, SDLK_o }, const_cast<char*>(u8"ロ"));

	//------

	//ワ
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_a }, const_cast<char*>(u8"ワ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_l, SDLK_w, SDLK_a }, const_cast<char*>(u8"ヮ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_w, SDLK_a }, const_cast<char*>(u8"ヮ"));

	//ヰ
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_y, SDLK_i }, const_cast<char*>(u8"ヰ"));

	//ヱ
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_y, SDLK_e }, const_cast<char*>(u8"ヱ"));

	//ヲ
	InsertGlyph(input, false, katakanaTrie, { SDLK_w, SDLK_o }, const_cast<char*>(u8"ヲ"));

	//------

	//ン
	InsertGlyph(input, false, katakanaTrie, { SDLK_n, SDLK_n }, const_cast<char*>(u8"ン"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_x, SDLK_n }, const_cast<char*>(u8"ン"));

	//------
	//Modifiers - Katakana
	//ガ
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_a }, const_cast<char*>(u8"ガ"));

	//ギ
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_i }, const_cast<char*>(u8"ギ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_y, SDLK_i }, const_cast<char*>(u8"ギィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_y, SDLK_e }, const_cast<char*>(u8"ギェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_y, SDLK_a }, const_cast<char*>(u8"ギャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_y, SDLK_u }, const_cast<char*>(u8"ギュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_y, SDLK_o }, const_cast<char*>(u8"ギョ"));

	//グ
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_u }, const_cast<char*>(u8"グ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_w, SDLK_a }, const_cast<char*>(u8"グァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_w, SDLK_i }, const_cast<char*>(u8"グィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_w, SDLK_u }, const_cast<char*>(u8"グゥ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_w , SDLK_e }, const_cast<char*>(u8"グェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_w, SDLK_o }, const_cast<char*>(u8"グォ"));

	//ゲ
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_e }, const_cast<char*>(u8"ゲ"));

	//ゴ
	InsertGlyph(input, false, katakanaTrie, { SDLK_g, SDLK_o }, const_cast<char*>(u8"ゴ"));

	//ザ
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_a }, const_cast<char*>(u8"サ"));

	//ジ
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_i }, const_cast<char*>(u8"ジ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_i }, const_cast<char*>(u8"ジ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_y, SDLK_i }, const_cast<char*>(u8"ジィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_y, SDLK_i }, const_cast<char*>(u8"ジィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_e }, const_cast<char*>(u8"ジェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_y, SDLK_e }, const_cast<char*>(u8"ジェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_y, SDLK_e }, const_cast<char*>(u8"ジェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_a }, const_cast<char*>(u8"ジャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_y, SDLK_a }, const_cast<char*>(u8"ジャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_y, SDLK_a }, const_cast<char*>(u8"ジャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_u }, const_cast<char*>(u8"ジュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_y, SDLK_u }, const_cast<char*>(u8"ジュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_y, SDLK_u }, const_cast<char*>(u8"ジュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_o }, const_cast<char*>(u8"ジョ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_j, SDLK_y, SDLK_o }, const_cast<char*>(u8"ジョ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_y, SDLK_o }, const_cast<char*>(u8"ジョ"));

	//ズ
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_u }, const_cast<char*>(u8"ズ"));

	//ゼ
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_e }, const_cast<char*>(u8"ゼ"));

	//ゾ
	InsertGlyph(input, false, katakanaTrie, { SDLK_z, SDLK_o }, const_cast<char*>(u8"ゾ"));

	//ダ
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_a }, const_cast<char*>(u8"ダ"));

	//ヂ
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_i }, const_cast<char*>(u8"ヂ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_y, SDLK_i }, const_cast<char*>(u8"ヂィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_y, SDLK_e }, const_cast<char*>(u8"ヂェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_y, SDLK_a }, const_cast<char*>(u8"ヂャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_y, SDLK_u }, const_cast<char*>(u8"ヂュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_y, SDLK_o }, const_cast<char*>(u8"ヂョ"));

	//ヅ
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_u }, const_cast<char*>(u8"ヅ"));

	//デ
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_e }, const_cast<char*>(u8"デ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_h, SDLK_i }, const_cast<char*>(u8"ディ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_h, SDLK_e }, const_cast<char*>(u8"デェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_h, SDLK_a }, const_cast<char*>(u8"デャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_h, SDLK_u }, const_cast<char*>(u8"デュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_h, SDLK_o }, const_cast<char*>(u8"デョ"));

	//ド
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_o }, const_cast<char*>(u8"ド"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_w, SDLK_a }, const_cast<char*>(u8"ドァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_w, SDLK_i }, const_cast<char*>(u8"ドィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_w, SDLK_u }, const_cast<char*>(u8"ドゥ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_w, SDLK_e }, const_cast<char*>(u8"ドェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_d, SDLK_w, SDLK_o }, const_cast<char*>(u8"ドォ"));

	//バ
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_a }, const_cast<char*>(u8"バ"));

	//パ
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_a }, const_cast<char*>(u8"パ"));

	//ビ
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_i }, const_cast<char*>(u8"ビ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_y, SDLK_i }, const_cast<char*>(u8"ビィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_y, SDLK_e }, const_cast<char*>(u8"ビェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_y, SDLK_a }, const_cast<char*>(u8"ビャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_y, SDLK_u }, const_cast<char*>(u8"ビュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_y, SDLK_o }, const_cast<char*>(u8"ビョ"));

	//ピ
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_i }, const_cast<char*>(u8"ピ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_y, SDLK_i }, const_cast<char*>(u8"ピィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_y, SDLK_e }, const_cast<char*>(u8"ピェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_y, SDLK_a }, const_cast<char*>(u8"ピャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_y, SDLK_u }, const_cast<char*>(u8"ピュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_y, SDLK_o }, const_cast<char*>(u8"ピョ"));

	//ブ
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_u }, const_cast<char*>(u8"ブ"));

	//プ
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_u }, const_cast<char*>(u8"プ"));

	//ベ
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_e }, const_cast<char*>(u8"ベ"));

	//ペ
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_e }, const_cast<char*>(u8"ペ"));

	//ボ
	InsertGlyph(input, false, katakanaTrie, { SDLK_b, SDLK_o }, const_cast<char*>(u8"ボ"));

	//ポ
	InsertGlyph(input, false, katakanaTrie, { SDLK_p, SDLK_o }, const_cast<char*>(u8"ポ"));

	//ヴ
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_a }, const_cast<char*>(u8"ヴァ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_i }, const_cast<char*>(u8"ヴィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_y, SDLK_i }, const_cast<char*>(u8"ヴィ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_e }, const_cast<char*>(u8"ヴェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_y, SDLK_e }, const_cast<char*>(u8"ヴェ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_o }, const_cast<char*>(u8"ヴォ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_y, SDLK_a }, const_cast<char*>(u8"ヴャ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_y, SDLK_u }, const_cast<char*>(u8"ヴュ"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_v, SDLK_y, SDLK_o }, const_cast<char*>(u8"ヴョ"));

	//Combinations not from the basic Hiragana Table, basic Katakana Table, and the modifiers
	//ー (pause)
	InsertGlyph(input, true, hiraganaTrie, { SDLK_MINUS }, const_cast<char*>(u8"ー"));
	InsertGlyph(input, false, katakanaTrie, { SDLK_MINUS }, const_cast<char*>(u8"ー"));
}

//End Helper functions

//Start Thread Specific functions

void InputTask() {

}

//End Thread Specific functions

Input::Input(Game* game) : glyphsDestination({}), tokensDestination({})
{
	//Initializes the token reader.
	this->tokens.reserve(Input::MaxTokenSize);

	//Initializes the glyph map.
	InitializeGlyphMap(this, this->hiraganaTrie, this->katakanaTrie);

	//Set a reference to Game object.
	this->game = game;

	//Initializes the input box properties
	this->boxWidth = static_cast<int>(game->GetWidth());
	this->boxHeight = 60;
	this->inputboxPosition = { 0, static_cast<int>(game->GetHeight()) - this->boxHeight, this->boxWidth, this->boxHeight };
}

Input::~Input() {
	//Clearing storage containers
	this->tokens.clear();
	this->hiragana.clear();
	this->katakana.clear();

	//Clearing the pointers
	if (this->tokenSurface) {
		SDL_FreeSurface(this->tokenSurface);
	}
	if (this->tokenTexture) {
		SDL_DestroyTexture(this->tokenTexture);
	}
	if (this->glyphSurface) {
		SDL_FreeSurface(this->glyphSurface);
	}
	if (this->glyphTexture) {
		SDL_DestroyTexture(this->glyphTexture);
	}

}

bool Input::HandleValidInputs(SDL_Keycode inputCode) {
	if (inputCode < SDLK_a || inputCode > SDLK_z) {
		return false;
	}
	assert(inputCode >= SDLK_a);
	assert(inputCode <= SDLK_z);
	if (this->tokens.size() < Input::MaxTokenSize) {
		this->tokens.push_back(inputCode);
		if (this->tokens.size() >= Input::MaxTokenSize) {
			std::cout << "Too many tokens, auto-confirming!" << std::endl;
			this->ConfirmToken();
		}
	}
	ConvertKeycodesToString(this->tokens, this->tokenString);
	return true;
}

void Input::ConfirmToken() {
	//This is fired when the user presses the Enter key to confirm the entered inputs.
	KeyCodeTrie* glyphTrie = this->isHiraganaInput ? &(this->hiraganaTrie) : &(this->katakanaTrie);
	char* value = glyphTrie->Get(this->tokens);
	if (value) {
		//Needs multithreading threads to store the glyphs here, otherwise, it would be deadlocked.
		std::thread thread = std::thread(&Input::InputTask, this, value);
		thread.detach();

		//this->game->GetBlock()->ReplaceGlyph(value);
		//this->game->StoreGlyphs(value);
		//this->UpdateGlyphs(value);
		//this->tokens.clear();
	}
	else if (this->tokens.size() >= Input::MaxTokenSize) {
		this->tokens.clear();
		std::cout << "Not found! Max tokens used." << std::endl;
	}
	else {
		KeyCodeTrieNode* node = glyphTrie->GetNode(this->tokens);
		if ((!node) || (node && node->IsLeaf())) {
			this->tokens.clear();
			std::cout << "Not found! Incorrect input." << std::endl;
			this->isIncorrect = true;
		}
	}
	this->isDirty = true;
}

void Input::ClearTokens() {
	this->tokens.clear();
}

void Input::Update() {
	if (this->isDirty) {
		this->UpdateTokens();
	}

	//Reinitialize flags.
	this->isDirty = false;
	this->isIncorrect = false;
}

void Input::Render() {
	//Drawing a rectangle. Requires that the values are strictly in order of the struct object's members.
	//We set the draw color to gray.
	SDL_SetRenderDrawColor(this->game->GetGameRenderer(), 0x22, 0x22, 0x22, 255);
	SDL_RenderDrawRect(this->game->GetGameRenderer(), &this->inputboxPosition);

	//Rendering the tokens to the screen, somewhere along the bottom.
	SDL_SetRenderDrawColor(this->game->GetGameRenderer(), 0, 0, 0, 255);
	SDL_RenderCopy(this->game->GetGameRenderer(), this->tokenTexture, nullptr, &(this->tokensDestination));
	SDL_RenderCopy(this->game->GetGameRenderer(), this->glyphTexture, nullptr, &(this->glyphsDestination));
}

void Input::SwapInputType() {
	this->isHiraganaInput = !this->isHiraganaInput;
}

bool Input::CheckInputType() const {
	return this->isHiraganaInput;
}

std::vector<SDL_Keycode>* Input::GetTokens() {
	return &(this->tokens);
}

//Start Public functions

void Input::UpdateTokens() {
	//Drawing the tokens
	int charWidth, charHeight;
	TTF_SizeUTF8(this->game->GetFont(), this->tokenString.c_str(), &charWidth, &charHeight);

	//Get paddings in order to center align the text in the rectangle.
	int paddingWidth = std::abs(static_cast<int>(this->boxWidth - charWidth) / 3);
	int paddingHeight = std::abs((this->boxHeight - charHeight) / 2);

	if (this->tokenSurface) {
		SDL_FreeSurface(this->tokenSurface);
	}
	if (this->tokenTexture) {
		SDL_DestroyTexture(this->tokenTexture);
	}
	this->tokenSurface = TTF_RenderUTF8_Solid(this->game->GetFont(), this->tokenString.c_str(), (this->isIncorrect ? SDL_COLOR_Red : SDL_COLOR_Black));
	this->tokenTexture = SDL_CreateTextureFromSurface(this->game->GetGameRenderer(), this->tokenSurface);
	this->tokensDestination = { this->inputboxPosition.x + paddingWidth, this->inputboxPosition.y + paddingHeight, charWidth, charHeight };
}

void Input::UpdateGlyphs(char* value) {
	//Drawing the glyph
	int charWidth, charHeight;
	TTF_SizeUTF8(this->game->GetFont(), value, &charWidth, &charHeight);

	//Get paddings in order to center align the text in the rectangle.
	int paddingWidth = std::abs(static_cast<int>(this->boxWidth - charWidth) * 2 / 3);
	int paddingHeight = std::abs((this->boxHeight - charHeight) / 2);

	if (this->glyphSurface) {
		SDL_FreeSurface(this->glyphSurface);
	}
	if (this->glyphTexture) {
		SDL_DestroyTexture(this->glyphTexture);
	}
	this->glyphSurface = TTF_RenderUTF8_Solid(this->game->GetFont(), value, SDL_COLOR_Black);
	this->glyphTexture = SDL_CreateTextureFromSurface(this->game->GetGameRenderer(), this->glyphSurface);
	this->glyphsDestination = { this->inputboxPosition.x + paddingWidth, this->inputboxPosition.y + paddingHeight, charWidth, charHeight };
}

std::set<std::string> Input::GetCharacterGlyphs(bool isHiragana) {
	return isHiragana ? this->hiragana : this->katakana;
}

//End Public functions

//Start Private Functions

void Input::InputTask(char* value) {
	this->game->StoreGlyphs(value);
	this->tokens.clear();
}

//End Private Functions