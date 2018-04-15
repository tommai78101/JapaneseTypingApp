#include "input.h"

//Helper functions

void ConvertKeycodesToString(std::vector<SDL_Keycode>& codes, std::string& output) {
	output.clear();
	for (std::vector<SDL_Keycode>::iterator it = codes.begin(); it != codes.end(); it++) {
		char diff = static_cast<char>((*it) - SDLK_a);
		output.push_back('a' + diff);
	}
}

void InsertGlyph(KeyCodeTrie& trie, std::initializer_list<SDL_Keycode> list, const char* glyph) {
	if (glyph) {
		static std::vector<SDL_Keycode> key;
		key.insert(key.end(), list);
		unsigned long length = (unsigned long) std::strlen(glyph);
		char* p = (char*) std::calloc(length + 1, sizeof(*glyph));
		if (p) {
			strcpy_s(p, length, glyph);
			trie.Insert(key, p);
			std::free(p);
			key.clear();
			return;
		}
		key.clear();
	}
}

void InitializeGlyphMap(KeyCodeTrie& hiraganaTrie, KeyCodeTrie& katakanaTrie) {
	//Note(asperatology): There may be more than one method of typing the characters
	//out, therefore, there may be multiple entries for one glyph.
	//Glyphs may be 2 characters long.
	//Big sized glyphs go on top
	//Small sized glyphs go on bottom
	//Sorted by "hiragana order"

	//Hiragana

	//あ
	InsertGlyph(hiraganaTrie, { SDLK_a }, u8"あ");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_a }, u8"ぁ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_a }, u8"ぁ");

	//い
	InsertGlyph(hiraganaTrie, { SDLK_i }, u8"い");
	InsertGlyph(hiraganaTrie, { SDLK_y, SDLK_i }, u8"い");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_i }, u8"ぃ");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_y, SDLK_i }, u8"ぃ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_i }, u8"ぃ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_y, SDLK_i }, u8"ぃ");
	InsertGlyph(hiraganaTrie, { SDLK_y, SDLK_e }, u8"いぇ");

	//う
	InsertGlyph(hiraganaTrie, { SDLK_u }, u8"う");
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_h, SDLK_u }, u8"う");
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_u }, u8"う");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_u }, u8"ぅ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_u }, u8"ぅ");
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_h, SDLK_a }, u8"うぁ");
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_h, SDLK_i }, u8"うぃ");
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_i }, u8"うぃ");
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_e }, u8"うぇ");
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_h, SDLK_e }, u8"うぇ");
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_h, SDLK_o }, u8"うぉ");

	//え
	InsertGlyph(hiraganaTrie, { SDLK_e }, u8"え");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_e }, u8"ぇ");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_y, SDLK_e }, u8"ぇ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_e }, u8"ぇ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_y, SDLK_e }, u8"ぇ");

	//お
	InsertGlyph(hiraganaTrie, { SDLK_o }, u8"お");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_o }, u8"ぉ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_o }, u8"ぉ");

	//------

	//か
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_a }, u8"か");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_a }, u8"か");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_k, SDLK_a }, u8"ゕ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_k, SDLK_a }, u8"ゕ");

	//き
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_i }, u8"き");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_y, SDLK_i }, u8"きぃ");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_y, SDLK_e }, u8"きぇ");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_y, SDLK_a }, u8"きゃ");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_y, SDLK_u }, u8"きゅ");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_y, SDLK_o }, u8"きょ");

	//く
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_u }, u8"く");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_u }, u8"く");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_u }, u8"く");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_w, SDLK_a }, u8"くぁ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_a }, u8"くぁ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_w, SDLK_a }, u8"くぁ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_i }, u8"くぃ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_w, SDLK_i }, u8"くぃ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_y, SDLK_i }, u8"くぃ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_w, SDLK_u }, u8"くぅ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_e }, u8"くぇ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_w, SDLK_e }, u8"くぇ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_y, SDLK_e }, u8"くぇ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_o }, u8"くぉ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_w, SDLK_o }, u8"くぉ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_y, SDLK_a }, u8"くゃ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_y, SDLK_u }, u8"くゅ");
	InsertGlyph(hiraganaTrie, { SDLK_q, SDLK_y, SDLK_o }, u8"くょ");

	//け
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_e }, u8"け");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_k, SDLK_e }, u8"ゖ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_k, SDLK_e }, u8"ゖ");

	//こ
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_o }, u8"こ");
	InsertGlyph(hiraganaTrie, { SDLK_k, SDLK_o }, u8"こ");

	//------

	//さ
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_a }, u8"さ");

	//し
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_i }, u8"し");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_h, SDLK_i }, u8"し");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_i }, u8"し");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_y, SDLK_i }, u8"しぃ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_h, SDLK_e }, u8"しぇ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_y, SDLK_e }, u8"しぇ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_h, SDLK_a }, u8"しゃ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_y, SDLK_a }, u8"しゃ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_h, SDLK_u }, u8"しゅ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_y, SDLK_u }, u8"しゅ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_h, SDLK_o }, u8"しょ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_y, SDLK_o }, u8"しょ");

	//す
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_u }, u8"す");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_w, SDLK_a }, u8"すぁ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_w, SDLK_i }, u8"すぃ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_w, SDLK_u }, u8"すぅ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_w, SDLK_e }, u8"すぇ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_w, SDLK_o }, u8"すぉ");

	//せ
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_e }, u8"せ");
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_e }, u8"せ");

	//そ
	InsertGlyph(hiraganaTrie, { SDLK_s, SDLK_o }, u8"そ");

	//------

	//た
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_a }, u8"た");

	//ち
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_h, SDLK_i }, u8"ち");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_i }, u8"ち");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_y, SDLK_i }, u8"ちぃ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_y, SDLK_i }, u8"ちぃ");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_h, SDLK_e }, u8"ちぇ");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_y, SDLK_e }, u8"ちぇ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_y, SDLK_e }, u8"ちぇ");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_h, SDLK_a }, u8"ちゃ");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_y, SDLK_a }, u8"ちゃ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_y, SDLK_a }, u8"ちゃ");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_h, SDLK_u }, u8"ちゅ");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_y, SDLK_u }, u8"ちゅ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_y, SDLK_u }, u8"ちゅ");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_h, SDLK_o }, u8"ちょ");
	InsertGlyph(hiraganaTrie, { SDLK_c, SDLK_y, SDLK_o }, u8"ちょ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_y, SDLK_o }, u8"ちょ");

	//つ
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_s, SDLK_u }, u8"つ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_u }, u8"つ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_s, SDLK_a }, u8"つぁ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_s, SDLK_i }, u8"つぃ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_s, SDLK_e }, u8"つぇ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_s, SDLK_o }, u8"つぉ");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_t, SDLK_s, SDLK_u }, u8"っ");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_t, SDLK_u }, u8"っ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_t, SDLK_s, SDLK_u }, u8"っ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_t, SDLK_u }, u8"っ");

	//て
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_e }, u8"て");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_h, SDLK_i }, u8"てぃ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_h, SDLK_e }, u8"てぇ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_h, SDLK_a }, u8"てゃ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_h, SDLK_u }, u8"てゅ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_h, SDLK_o }, u8"てょ");


	//と
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_o }, u8"と");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_w, SDLK_a }, u8"とぁ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_w, SDLK_i }, u8"とぃ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_w, SDLK_u }, u8"とぅ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_w, SDLK_e }, u8"とぇ");
	InsertGlyph(hiraganaTrie, { SDLK_t, SDLK_w, SDLK_o }, u8"とぉ");

	//------

	//な
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_a }, u8"な");

	//に
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_i }, u8"に");
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_y, SDLK_i }, u8"にぃ");
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_y, SDLK_e }, u8"にぇ");
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_y, SDLK_a }, u8"にゃ");
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_y, SDLK_u }, u8"にゅ");
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_y, SDLK_o }, u8"にょ");

	//ぬ
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_u }, u8"ぬ");

	//ね
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_e }, u8"ね");

	//の
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_o }, u8"の");

	//------

	//は
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_a }, u8"は");

	//ひ
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_i }, u8"ひ");
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_y, SDLK_i }, u8"ひぃ");
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_y, SDLK_e }, u8"ひぇ");
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_y, SDLK_a }, u8"ひゃ");
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_y, SDLK_u }, u8"ひゅ");
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_y, SDLK_o }, u8"ひょ");

	//ふ
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_u }, u8"ふ");
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_u }, u8"ふ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_a }, u8"ふぁ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_w, SDLK_a }, u8"ふぁ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_i }, u8"ふぃ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_w, SDLK_i }, u8"ふぃ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_y, SDLK_i }, u8"ふぃ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_w, SDLK_u }, u8"ふぅ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_e }, u8"ふぇ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_w, SDLK_e }, u8"ふぇ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_y, SDLK_e }, u8"ふぇ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_o }, u8"ふぉ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_w, SDLK_o }, u8"ふぉ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_y, SDLK_a }, u8"ふゃ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_y, SDLK_u }, u8"ふゅ");
	InsertGlyph(hiraganaTrie, { SDLK_f, SDLK_y, SDLK_o }, u8"ふょ");

	//へ
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_e }, u8"へ");

	//ほ
	InsertGlyph(hiraganaTrie, { SDLK_h, SDLK_o }, u8"ほ");

	//------

	//ま
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_a }, u8"ま");

	//み
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_i }, u8"み");
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_y, SDLK_i }, u8"みぃ");
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_y, SDLK_e }, u8"みぇ");
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_y, SDLK_a }, u8"みゃ");
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_y, SDLK_u }, u8"みゅ");
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_y, SDLK_o }, u8"みょ");

	//む
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_u }, u8"む");

	//め
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_e }, u8"め");

	//も
	InsertGlyph(hiraganaTrie, { SDLK_m, SDLK_o }, u8"も");

	//------

	//や
	InsertGlyph(hiraganaTrie, { SDLK_y, SDLK_a }, u8"や");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_y, SDLK_a }, u8"ゃ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_y, SDLK_a }, u8"ゃ");

	//ゆ
	InsertGlyph(hiraganaTrie, { SDLK_y, SDLK_u }, u8"ゆ");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_y, SDLK_u }, u8"ゅ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_y, SDLK_u }, u8"ゅ");

	//よ
	InsertGlyph(hiraganaTrie, { SDLK_y, SDLK_o }, u8"よ");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_y, SDLK_o }, u8"ょ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_y, SDLK_o }, u8"ょ");

	//------

	//ら
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_a }, u8"ら");

	//り
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_i }, u8"り");
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_y, SDLK_i }, u8"りぃ");
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_y, SDLK_e }, u8"りぇ");
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_y, SDLK_a }, u8"りゃ");
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_y, SDLK_u }, u8"りゅ");
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_y, SDLK_o }, u8"りょ");

	//る
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_u }, u8"る");

	//れ
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_e }, u8"れ");

	//ろ
	InsertGlyph(hiraganaTrie, { SDLK_r, SDLK_o }, u8"ろ");

	//------

	//わ
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_a }, u8"わ");
	InsertGlyph(hiraganaTrie, { SDLK_l, SDLK_w, SDLK_a }, u8"ゎ");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_w, SDLK_a }, u8"ゎ");

	//ゐ
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_y, SDLK_i }, u8"ゐ");

	//ゑ
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_y, SDLK_e }, u8"ゑ");

	//を
	InsertGlyph(hiraganaTrie, { SDLK_w, SDLK_o }, u8"を");

	//------

	//ん
	InsertGlyph(hiraganaTrie, { SDLK_n, SDLK_n }, u8"ん");
	InsertGlyph(hiraganaTrie, { SDLK_x, SDLK_n }, u8"ん");

	//------
	//Modifiers - Hiragana
	//が
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_a }, u8"が");

	//ぎ
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_i }, u8"ぎ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_y, SDLK_i }, u8"ぎぃ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_y, SDLK_e }, u8"ぎぇ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_y, SDLK_a }, u8"ぎゃ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_y, SDLK_u }, u8"ぎゅ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_y, SDLK_o }, u8"ぎょ");

	//ぐ
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_u }, u8"ぐ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_w, SDLK_a }, u8"ぐぁ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_w, SDLK_i }, u8"ぐぃ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_w, SDLK_u }, u8"ぐぅ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_w , SDLK_e }, u8"ぐぇ");
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_w, SDLK_o }, u8"ぐぉ");

	//げ
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_e }, u8"げ");

	//ご
	InsertGlyph(hiraganaTrie, { SDLK_g, SDLK_o }, u8"ご");

	//ざ
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_a }, u8"さ");

	//じ
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_i }, u8"じ");
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_i }, u8"じ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_y, SDLK_i }, u8"じぃ");
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_y, SDLK_i }, u8"じぃ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_e }, u8"じぇ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_y, SDLK_e }, u8"じぇ");
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_y, SDLK_e }, u8"じぇ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_a }, u8"じゃ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_y, SDLK_a }, u8"じゃ");
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_y, SDLK_a }, u8"じゃ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_u }, u8"じゅ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_y, SDLK_u }, u8"じゅ");
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_y, SDLK_u }, u8"じゅ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_o }, u8"じょ");
	InsertGlyph(hiraganaTrie, { SDLK_j, SDLK_y, SDLK_o }, u8"じょ");
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_y, SDLK_o }, u8"じょ");

	//ず
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_u }, u8"ず");

	//ぜ
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_e }, u8"ぜ");

	//ぞ
	InsertGlyph(hiraganaTrie, { SDLK_z, SDLK_o }, u8"ぞ");

	//だ
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_a }, u8"だ");

	//ぢ
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_i }, u8"ぢ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_y, SDLK_i }, u8"ぢぃ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_y, SDLK_e }, u8"ぢぇ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_y, SDLK_a }, u8"ぢゃ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_y, SDLK_u }, u8"ぢゅ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_y, SDLK_o }, u8"ぢょ");

	//づ
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_u }, u8"づ");

	//で
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_e }, u8"で");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_h, SDLK_i }, u8"でぃ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_h, SDLK_e }, u8"でぇ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_h, SDLK_a }, u8"でゃ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_h, SDLK_u }, u8"でゅ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_h, SDLK_o }, u8"でょ");

	//ど
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_o }, u8"ど");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_w, SDLK_a }, u8"どぁ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_w, SDLK_i }, u8"どぃ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_w, SDLK_u }, u8"どぅ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_w, SDLK_e }, u8"どぇ");
	InsertGlyph(hiraganaTrie, { SDLK_d, SDLK_w, SDLK_o }, u8"どぉ");

	//ば
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_a }, u8"ば");

	//ぱ
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_a }, u8"ぱ");

	//び
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_i }, u8"び");
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_y, SDLK_i }, u8"びぃ");
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_y, SDLK_e }, u8"びぇ");
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_y, SDLK_a }, u8"びゃ");
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_y, SDLK_u }, u8"びゅ");
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_y, SDLK_o }, u8"びょ");

	//ぴ
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_i }, u8"ぴ");
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_y, SDLK_i }, u8"ぴぃ");
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_y, SDLK_e }, u8"ぴぇ");
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_y, SDLK_a }, u8"ぴゃ");
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_y, SDLK_u }, u8"ぴゅ");
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_y, SDLK_o }, u8"ぴょ");

	//ぶ
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_u }, u8"ぶ");

	//ぷ
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_u }, u8"ぷ");

	//べ
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_e }, u8"べ");

	//ぺ
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_e }, u8"ぺ");

	//ぼ
	InsertGlyph(hiraganaTrie, { SDLK_b, SDLK_o }, u8"ぼ");

	//ぽ
	InsertGlyph(hiraganaTrie, { SDLK_p, SDLK_o }, u8"ぽ");

	//ヴ
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_a }, u8"ヴぁ");
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_i }, u8"ヴぃ");
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_y, SDLK_i }, u8"ヴぃ");
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_e }, u8"ヴぇ");
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_y, SDLK_e }, u8"ヴぇ");
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_o }, u8"ヴぉ");
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_y, SDLK_a }, u8"ヴゃ");
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_y, SDLK_u }, u8"ヴゅ");
	InsertGlyph(hiraganaTrie, { SDLK_v, SDLK_y, SDLK_o }, u8"ヴょ");

	//------
	//Katakana
	//ア 
	InsertGlyph(katakanaTrie, { SDLK_a }, u8"ア");
	InsertGlyph(katakanaTrie, { SDLK_l , SDLK_a }, u8"ァ");
	InsertGlyph(katakanaTrie, { SDLK_x , SDLK_a }, u8"ァ");

	//イ
	InsertGlyph(katakanaTrie, { SDLK_i }, u8"イ");
	InsertGlyph(katakanaTrie, { SDLK_y, SDLK_i }, u8"イ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_i }, u8"ィ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_y, SDLK_i }, u8"ィ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_i }, u8"ィ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_y, SDLK_i }, u8"ィ");
	InsertGlyph(katakanaTrie, { SDLK_y, SDLK_e }, u8"イェ");

	//ウ
	InsertGlyph(katakanaTrie, { SDLK_u }, u8"ウ");
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_h, SDLK_u }, u8"ウ");
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_u }, u8"ウ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_u }, u8"ゥ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_u }, u8"ゥ");
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_h, SDLK_a }, u8"ウァ");
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_h, SDLK_i }, u8"ウィ");
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_i }, u8"ウィ");
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_e }, u8"ウェ");
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_h, SDLK_e }, u8"ウェ");
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_h, SDLK_o }, u8"ウォ");

	//エ
	InsertGlyph(katakanaTrie, { SDLK_e }, u8"エ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_e }, u8"ェ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_y, SDLK_e }, u8"ェ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_e }, u8"ェ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_y, SDLK_e }, u8"ェ");

	//オ
	InsertGlyph(katakanaTrie, { SDLK_o }, u8"オ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_o }, u8"ォ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_o }, u8"ォ");

	//------

	//カ
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_a }, u8"カ");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_a }, u8"カ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_k, SDLK_a }, u8"ヵ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_k, SDLK_a }, u8"ヵ");

	//キ
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_i }, u8"キ");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_y, SDLK_i }, u8"キィ");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_y, SDLK_e }, u8"キェ");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_y, SDLK_a }, u8"キャ");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_y, SDLK_u }, u8"キュ");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_y, SDLK_o }, u8"キョ");

	//ク
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_u }, u8"ク");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_u }, u8"ク");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_u }, u8"ク");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_w, SDLK_a }, u8"クァ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_a }, u8"クァ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_w, SDLK_a }, u8"クァ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_i }, u8"クィ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_w, SDLK_i }, u8"クィ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_y, SDLK_i }, u8"クィ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_w, SDLK_u }, u8"クゥ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_e }, u8"クェ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_w, SDLK_e }, u8"クェ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_y, SDLK_e }, u8"クェ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_o }, u8"クォ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_w, SDLK_o }, u8"クォ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_y, SDLK_a }, u8"クャ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_y, SDLK_u }, u8"クュ");
	InsertGlyph(katakanaTrie, { SDLK_q, SDLK_y, SDLK_o }, u8"クョ");

	//ケ
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_e }, u8"ケ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_k, SDLK_e }, u8"ヶ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_k, SDLK_e }, u8"ヶ");

	//コ
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_o }, u8"コ");
	InsertGlyph(katakanaTrie, { SDLK_k, SDLK_o }, u8"コ");

	//------

	//サ
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_a }, u8"サ");

	//シ
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_i }, u8"シ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_h, SDLK_i }, u8"シ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_i }, u8"シ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_y, SDLK_i }, u8"シィ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_h, SDLK_e }, u8"シェ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_y, SDLK_e }, u8"シェ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_h, SDLK_a }, u8"シャ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_y, SDLK_a }, u8"シャ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_h, SDLK_u }, u8"シュ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_y, SDLK_u }, u8"シュ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_h, SDLK_o }, u8"ショ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_y, SDLK_o }, u8"ショ");

	//ス
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_u }, u8"ス");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_w, SDLK_a }, u8"スァ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_w, SDLK_i }, u8"スィ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_w, SDLK_u }, u8"スゥ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_w, SDLK_e }, u8"スェ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_w, SDLK_o }, u8"スォ");

	//セ
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_e }, u8"セ");
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_e }, u8"セ");

	//ソ
	InsertGlyph(katakanaTrie, { SDLK_s, SDLK_o }, u8"ソ");

	//------

	//タ
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_a }, u8"タ");

	//チ
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_h, SDLK_i }, u8"チ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_i }, u8"チ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_y, SDLK_i }, u8"チィ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_y, SDLK_i }, u8"チィ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_h, SDLK_e }, u8"チェ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_y, SDLK_e }, u8"チェ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_y, SDLK_e }, u8"チェ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_h, SDLK_a }, u8"チャ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_y, SDLK_a }, u8"チャ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_y, SDLK_a }, u8"チャ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_h, SDLK_u }, u8"チュ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_y, SDLK_u }, u8"チュ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_y, SDLK_u }, u8"チュ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_h, SDLK_o }, u8"チョ");
	InsertGlyph(katakanaTrie, { SDLK_c, SDLK_y, SDLK_o }, u8"チョ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_y, SDLK_o }, u8"チョ");

	//ツ
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_s, SDLK_u }, u8"ツ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_u }, u8"ツ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_s, SDLK_a }, u8"ツァ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_s, SDLK_i }, u8"ツィ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_s, SDLK_e }, u8"ツェ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_s, SDLK_o }, u8"ツォ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_t, SDLK_s, SDLK_u }, u8"ッ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_t, SDLK_u }, u8"ッ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_t, SDLK_s, SDLK_u }, u8"ッ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_t, SDLK_u }, u8"ッ");

	//テ
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_e }, u8"テ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_h, SDLK_i }, u8"ティ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_h, SDLK_e }, u8"テェ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_h, SDLK_a }, u8"テャ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_h, SDLK_u }, u8"テュ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_h, SDLK_o }, u8"テョ");


	//ト
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_o }, u8"ト");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_w, SDLK_a }, u8"トァ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_w, SDLK_i }, u8"トィ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_w, SDLK_u }, u8"トゥ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_w, SDLK_e }, u8"トェ");
	InsertGlyph(katakanaTrie, { SDLK_t, SDLK_w, SDLK_o }, u8"トォ");

	//------

	//ナ
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_a }, u8"ナ");

	//ニ
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_i }, u8"ニ");
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_y, SDLK_i }, u8"ニィ");
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_y, SDLK_e }, u8"ニェ");
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_y, SDLK_a }, u8"ニャ");
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_y, SDLK_u }, u8"ニュ");
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_y, SDLK_o }, u8"ニョ");

	//ヌ
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_u }, u8"ヌ");

	//ネ
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_e }, u8"ネ");

	//ノ
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_o }, u8"ノ");

	//------

	//ハ
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_a }, u8"ハ");

	//ヒ
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_i }, u8"ヒ");
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_y, SDLK_i }, u8"ヒィ");
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_y, SDLK_e }, u8"ヒェ");
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_y, SDLK_a }, u8"ヒャ");
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_y, SDLK_u }, u8"ヒュ");
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_y, SDLK_o }, u8"ヒョ");

	//フ
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_u }, u8"フ");
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_u }, u8"フ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_a }, u8"ファ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_w, SDLK_a }, u8"ファ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_i }, u8"フィ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_w, SDLK_i }, u8"フィ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_y, SDLK_i }, u8"フィ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_w, SDLK_u }, u8"フゥ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_e }, u8"フェ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_w, SDLK_e }, u8"フェ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_y, SDLK_e }, u8"フェ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_o }, u8"フォ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_w, SDLK_o }, u8"フォ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_y, SDLK_a }, u8"フャ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_y, SDLK_u }, u8"フュ");
	InsertGlyph(katakanaTrie, { SDLK_f, SDLK_y, SDLK_o }, u8"フョ");

	//ヘ
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_e }, u8"ヘ");

	//ホ
	InsertGlyph(katakanaTrie, { SDLK_h, SDLK_o }, u8"ホ");

	//------

	//マ
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_a }, u8"マ");

	//ミ
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_i }, u8"ミ");
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_y, SDLK_i }, u8"ミィ");
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_y, SDLK_e }, u8"ミェ");
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_y, SDLK_a }, u8"ミャ");
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_y, SDLK_u }, u8"ミュ");
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_y, SDLK_o }, u8"ミョ");

	//ム
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_u }, u8"ム");

	//メ
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_e }, u8"メ");

	//モ
	InsertGlyph(katakanaTrie, { SDLK_m, SDLK_o }, u8"モ");

	//------

	//ヤ
	InsertGlyph(katakanaTrie, { SDLK_y, SDLK_a }, u8"ヤ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_y, SDLK_a }, u8"ャ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_y, SDLK_a }, u8"ャ");

	//ユ
	InsertGlyph(katakanaTrie, { SDLK_y, SDLK_u }, u8"ユ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_y, SDLK_u }, u8"ュ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_y, SDLK_u }, u8"ュ");

	//ヨ
	InsertGlyph(katakanaTrie, { SDLK_y, SDLK_o }, u8"ヨ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_y, SDLK_o }, u8"ョ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_y, SDLK_o }, u8"ョ");

	//------

	//ラ
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_a }, u8"ラ");

	//リ
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_i }, u8"リ");
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_y, SDLK_i }, u8"リィ");
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_y, SDLK_e }, u8"リェ");
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_y, SDLK_a }, u8"リャ");
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_y, SDLK_u }, u8"リュ");
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_y, SDLK_o }, u8"リョ");

	//ル
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_u }, u8"ル");

	//レ
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_e }, u8"レ");

	//ロ
	InsertGlyph(katakanaTrie, { SDLK_r, SDLK_o }, u8"ロ");

	//------

	//ワ
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_a }, u8"ワ");
	InsertGlyph(katakanaTrie, { SDLK_l, SDLK_w, SDLK_a }, u8"ヮ");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_w, SDLK_a }, u8"ヮ");

	//ヰ
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_y, SDLK_i }, u8"ヰ");

	//ヱ
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_y, SDLK_e }, u8"ヱ");

	//ヲ
	InsertGlyph(katakanaTrie, { SDLK_w, SDLK_o }, u8"ヲ");

	//------

	//ン
	InsertGlyph(katakanaTrie, { SDLK_n, SDLK_n }, u8"ン");
	InsertGlyph(katakanaTrie, { SDLK_x, SDLK_n }, u8"ン");

	//------
	//Modifiers - Katakana
	//ガ
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_a }, u8"ガ");

	//ギ
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_i }, u8"ギ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_y, SDLK_i }, u8"ギィ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_y, SDLK_e }, u8"ギェ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_y, SDLK_a }, u8"ギャ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_y, SDLK_u }, u8"ギュ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_y, SDLK_o }, u8"ギョ");

	//グ
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_u }, u8"グ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_w, SDLK_a }, u8"グァ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_w, SDLK_i }, u8"グィ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_w, SDLK_u }, u8"グゥ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_w , SDLK_e }, u8"グェ");
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_w, SDLK_o }, u8"グォ");

	//ゲ
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_e }, u8"ゲ");

	//ゴ
	InsertGlyph(katakanaTrie, { SDLK_g, SDLK_o }, u8"ゴ");

	//ザ
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_a }, u8"サ");

	//ジ
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_i }, u8"ジ");
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_i }, u8"ジ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_y, SDLK_i }, u8"ジィ");
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_y, SDLK_i }, u8"ジィ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_e }, u8"ジェ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_y, SDLK_e }, u8"ジェ");
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_y, SDLK_e }, u8"ジェ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_a }, u8"ジャ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_y, SDLK_a }, u8"ジャ");
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_y, SDLK_a }, u8"ジャ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_u }, u8"ジュ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_y, SDLK_u }, u8"ジュ");
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_y, SDLK_u }, u8"ジュ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_o }, u8"ジョ");
	InsertGlyph(katakanaTrie, { SDLK_j, SDLK_y, SDLK_o }, u8"ジョ");
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_y, SDLK_o }, u8"ジョ");

	//ズ
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_u }, u8"ズ");

	//ゼ
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_e }, u8"ゼ");

	//ゾ
	InsertGlyph(katakanaTrie, { SDLK_z, SDLK_o }, u8"ゾ");

	//ダ
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_a }, u8"ダ");

	//ヂ
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_i }, u8"ヂ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_y, SDLK_i }, u8"ヂィ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_y, SDLK_e }, u8"ヂェ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_y, SDLK_a }, u8"ヂャ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_y, SDLK_u }, u8"ヂュ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_y, SDLK_o }, u8"ヂョ");

	//ヅ
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_u }, u8"ヅ");

	//デ
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_e }, u8"デ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_h, SDLK_i }, u8"ディ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_h, SDLK_e }, u8"デェ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_h, SDLK_a }, u8"デャ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_h, SDLK_u }, u8"デュ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_h, SDLK_o }, u8"デョ");

	//ド
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_o }, u8"ド");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_w, SDLK_a }, u8"ドァ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_w, SDLK_i }, u8"ドィ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_w, SDLK_u }, u8"ドゥ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_w, SDLK_e }, u8"ドェ");
	InsertGlyph(katakanaTrie, { SDLK_d, SDLK_w, SDLK_o }, u8"ドォ");

	//バ
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_a }, u8"バ");

	//パ
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_a }, u8"パ");

	//ビ
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_i }, u8"ビ");
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_y, SDLK_i }, u8"ビィ");
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_y, SDLK_e }, u8"ビェ");
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_y, SDLK_a }, u8"ビャ");
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_y, SDLK_u }, u8"ビュ");
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_y, SDLK_o }, u8"ビョ");

	//ピ
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_i }, u8"ピ");
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_y, SDLK_i }, u8"ピィ");
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_y, SDLK_e }, u8"ピェ");
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_y, SDLK_a }, u8"ピャ");
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_y, SDLK_u }, u8"ピュ");
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_y, SDLK_o }, u8"ピョ");

	//ブ
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_u }, u8"ブ");

	//プ
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_u }, u8"プ");

	//ベ
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_e }, u8"ベ");

	//ペ
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_e }, u8"ペ");

	//ボ
	InsertGlyph(katakanaTrie, { SDLK_b, SDLK_o }, u8"ボ");

	//ポ
	InsertGlyph(katakanaTrie, { SDLK_p, SDLK_o }, u8"ポ");

	//ヴ
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_a }, u8"ヴァ");
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_i }, u8"ヴィ");
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_y, SDLK_i }, u8"ヴィ");
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_e }, u8"ヴェ");
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_y, SDLK_e }, u8"ヴェ");
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_o }, u8"ヴォ");
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_y, SDLK_a }, u8"ヴャ");
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_y, SDLK_u }, u8"ヴュ");
	InsertGlyph(katakanaTrie, { SDLK_v, SDLK_y, SDLK_o }, u8"ヴョ");

	//Combinations not from the basic Hiragana Table, basic Katakana Table, and the modifiers
	//ー (pause)
	InsertGlyph(hiraganaTrie, { SDLK_MINUS }, u8"ー");
	InsertGlyph(katakanaTrie, { SDLK_MINUS }, u8"ー");
}

//End Helper functions

Input::Input(Game* game) {
	//Initializes the token reader.
	this->tokens.reserve(Input::MaxTokenSize);

	//Initializes the glyph map.
	InitializeGlyphMap(this->hiraganaTrie, this->katakanaTrie);

	//Set a reference to Game object.
	this->game = game;

	//Initializes the input box properties
	this->boxWidth = static_cast<int>(game->GetWidth());
	this->boxHeight = 60;
	this->inputboxPosition = { 0, static_cast<int>(game->GetHeight()) - this->boxHeight, this->boxWidth, this->boxHeight };
}

Input::~Input() {
	this->tokens.clear();
	if (this->tokenSurface) {
		SDL_FreeSurface(this->tokenSurface);
	}
	if (this->tokenTexture) {
		SDL_DestroyTexture(this->tokenTexture);
	}
}

void Input::HandleValidInputs(SDL_Keycode inputCode) {
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
}

void Input::ConfirmToken() {
	//This is fired when the user presses the Enter key to confirm the entered inputs.
	KeyCodeTrie* glyphTrie = this->isHiraganaInput ? &(this->hiraganaTrie) : &(this->katakanaTrie);
	char* value = glyphTrie->Get(this->tokens);
	if (value) {
		//this->game->GetBlock()->ReplaceGlyph(value);
		this->UpdateGlyphs(value);
		this->tokens.clear();
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

//Start Private functions

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
	this->tokenTexture = SDL_CreateTextureFromSurface(this->game->GetGameRenderer(), tokenSurface);
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

//End Private functions