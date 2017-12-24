#include "input.h"

//void InsertGlyph(std::map<std::vector<SDL_Keycode>, char*>& glyphMap, std::initializer_list<SDL_Keycode> list, char* glyph) {
//	std::vector<SDL_Keycode> key;
//	key.insert(key.end(), list);
//	glyphMap.insert(std::pair<std::vector<SDL_Keycode>, char*>(key, glyph));
//}

void InsertGlyph(Trie& trie, std::initializer_list<SDL_Keycode> list, char* glyph) {
	static std::vector<SDL_Keycode> key;
	key.insert(key.end(), list);
	trie.Insert(key, glyph);
	key.clear();
}

//void InitializeGlyphMap(std::map<std::vector<SDL_Keycode>, char*>& glyphMap) {
void InitializeGlyphMap(Trie& glyphMap) {
	//Note(asperatology): There may be more than one method of typing the characters
	//out, therefore, there may be multiple entries for one glyph.
	//Glyphs may be 2 characters long.
	//Big sized glyphs go on top
	//Small sized glyphs go on bottom
	//Sorted by "hiragana order"

	//Hiragana

	//あ
	InsertGlyph(glyphMap, { SDLK_a }, u8"あ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_a }, u8"ぁ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_a }, u8"ぁ");

	//い
	InsertGlyph(glyphMap, { SDLK_i }, u8"い");
	InsertGlyph(glyphMap, { SDLK_y, SDLK_i }, u8"い");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_i }, u8"ぃ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_i }, u8"ぃ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_i }, u8"ぃ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_i }, u8"ぃ");
	InsertGlyph(glyphMap, { SDLK_y, SDLK_e }, u8"いぇ");

	//う
	InsertGlyph(glyphMap, { SDLK_u }, u8"う");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_u }, u8"う");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_u }, u8"う");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_u }, u8"ぅ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_u }, u8"ぅ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_a }, u8"うぁ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_i }, u8"うぃ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_i }, u8"うぃ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_e }, u8"うぇ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_e }, u8"うぇ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_o }, u8"うぉ");

	//え
	InsertGlyph(glyphMap, { SDLK_e }, u8"え");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_e }, u8"ぇ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_e }, u8"ぇ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_e }, u8"ぇ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_e }, u8"ぇ");

	//お
	InsertGlyph(glyphMap, { SDLK_o }, u8"お");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_o }, u8"ぉ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_o }, u8"ぉ");

	//------

	//か
	InsertGlyph(glyphMap, { SDLK_c, SDLK_a }, u8"か");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_a }, u8"か");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_k, SDLK_a }, u8"ゕ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_k, SDLK_a }, u8"ゕ");

	//き
	InsertGlyph(glyphMap, { SDLK_k, SDLK_i }, u8"き");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_i }, u8"きぃ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_e }, u8"きぇ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_a }, u8"きゃ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_u }, u8"きゅ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_o }, u8"きょ");

	//く
	InsertGlyph(glyphMap, { SDLK_c, SDLK_u }, u8"く");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_u }, u8"く");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_u }, u8"く");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_w, SDLK_a }, u8"くぁ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_a }, u8"くぁ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_a }, u8"くぁ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_i }, u8"くぃ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_i }, u8"くぃ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_i }, u8"くぃ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_u }, u8"くぅ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_e }, u8"くぇ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_e }, u8"くぇ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_e }, u8"くぇ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_o }, u8"くぉ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_o }, u8"くぉ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_a }, u8"くゃ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_u }, u8"くゅ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_o }, u8"くょ");

	//け
	InsertGlyph(glyphMap, { SDLK_k, SDLK_e }, u8"け");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_k, SDLK_e }, u8"ゖ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_k, SDLK_e }, u8"ゖ");

	//こ
	InsertGlyph(glyphMap, { SDLK_c, SDLK_o }, u8"こ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_o }, u8"こ");

	//------

	//さ
	InsertGlyph(glyphMap, { SDLK_s, SDLK_a }, u8"さ");

	//し
	InsertGlyph(glyphMap, { SDLK_c, SDLK_i }, u8"し");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_i }, u8"し");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_i }, u8"し");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_i }, u8"しぃ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_e }, u8"しぇ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_e }, u8"しぇ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_a }, u8"しゃ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_a }, u8"しゃ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_u }, u8"しゅ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_u }, u8"しゅ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_o }, u8"しょ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_o }, u8"しょ");

	//す
	InsertGlyph(glyphMap, { SDLK_s, SDLK_u }, u8"す");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_a }, u8"すぁ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_i }, u8"すぃ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_u }, u8"すぅ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_e }, u8"すぇ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_o }, u8"すぉ");

	//せ
	InsertGlyph(glyphMap, { SDLK_c, SDLK_e }, u8"せ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_e }, u8"せ");

	//そ
	InsertGlyph(glyphMap, { SDLK_s, SDLK_o }, u8"そ");

	//------

	//た
	InsertGlyph(glyphMap, { SDLK_t, SDLK_a }, u8"た");

	//ち
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_i }, u8"ち");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_i }, u8"ち");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_i }, u8"ちぃ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_i }, u8"ちぃ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_e }, u8"ちぇ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_e }, u8"ちぇ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_e }, u8"ちぇ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_a }, u8"ちゃ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_a }, u8"ちゃ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_a }, u8"ちゃ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_u }, u8"ちゅ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_u }, u8"ちゅ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_u }, u8"ちゅ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_o }, u8"ちょ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_o }, u8"ちょ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_o }, u8"ちょ");

	//つ
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_u }, u8"つ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_u }, u8"つ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_a }, u8"つぁ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_i }, u8"つぃ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_e }, u8"つぇ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_o }, u8"つぉ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_t, SDLK_s, SDLK_u }, u8"っ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_t, SDLK_u }, u8"っ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_t, SDLK_s, SDLK_u }, u8"っ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_t, SDLK_u }, u8"っ");

	//て
	InsertGlyph(glyphMap, { SDLK_t, SDLK_e }, u8"て");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_i }, u8"てぃ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_e }, u8"てぇ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_a }, u8"てゃ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_u }, u8"てゅ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_o }, u8"てょ");


	//と
	InsertGlyph(glyphMap, { SDLK_t, SDLK_o }, u8"と");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_a }, u8"とぁ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_i }, u8"とぃ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_u }, u8"とぅ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_e }, u8"とぇ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_o }, u8"とぉ");

	//------

	//な
	InsertGlyph(glyphMap, { SDLK_n, SDLK_a }, u8"な");

	//に
	InsertGlyph(glyphMap, { SDLK_n, SDLK_i }, u8"に");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_i }, u8"にぃ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_e }, u8"にぇ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_a }, u8"にゃ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_u }, u8"にゅ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_o }, u8"にょ");

	//ぬ
	InsertGlyph(glyphMap, { SDLK_n, SDLK_u }, u8"ぬ");

	//ね
	InsertGlyph(glyphMap, { SDLK_n, SDLK_e }, u8"ね");

	//の
	InsertGlyph(glyphMap, { SDLK_n, SDLK_o }, u8"の");

	//------

	//は
	InsertGlyph(glyphMap, { SDLK_h, SDLK_a }, u8"は");

	//ひ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_i }, u8"ひ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_i }, u8"ひぃ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_e }, u8"ひぇ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_a }, u8"ひゃ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_u }, u8"ひゅ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_o }, u8"ひょ");

	//ふ
	InsertGlyph(glyphMap, { SDLK_f, SDLK_u }, u8"ふ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_u }, u8"ふ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_a }, u8"ふぁ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_a }, u8"ふぁ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_i }, u8"ふぃ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_i }, u8"ふぃ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_i }, u8"ふぃ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_u }, u8"ふぅ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_e }, u8"ふぇ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_e }, u8"ふぇ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_e }, u8"ふぇ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_o }, u8"ふぉ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_o }, u8"ふぉ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_a }, u8"ふゃ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_u }, u8"ふゅ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_o }, u8"ふょ");

	//へ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_e }, u8"へ");

	//ほ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_o }, u8"ほ");

	//------

	//ま
	InsertGlyph(glyphMap, { SDLK_m, SDLK_a }, u8"ま");

	//み
	InsertGlyph(glyphMap, { SDLK_m, SDLK_i }, u8"み");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_i }, u8"みぃ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_e }, u8"みぇ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_a }, u8"みゃ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_u }, u8"みゅ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_o }, u8"みょ");

	//む
	InsertGlyph(glyphMap, { SDLK_m, SDLK_u }, u8"む");

	//め
	InsertGlyph(glyphMap, { SDLK_m, SDLK_e }, u8"め");

	//も
	InsertGlyph(glyphMap, { SDLK_m, SDLK_o }, u8"も");

	//------

	//や
	InsertGlyph(glyphMap, { SDLK_y, SDLK_a }, u8"や");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_a }, u8"ゃ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_a }, u8"ゃ");

	//ゆ
	InsertGlyph(glyphMap, { SDLK_y, SDLK_u }, u8"ゆ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_u }, u8"ゅ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_u }, u8"ゅ");

	//よ
	InsertGlyph(glyphMap, { SDLK_y, SDLK_o }, u8"よ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_o }, u8"ょ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_o }, u8"ょ");

	//------

	//ら
	InsertGlyph(glyphMap, { SDLK_r, SDLK_a }, u8"ら");

	//り
	InsertGlyph(glyphMap, { SDLK_r, SDLK_i }, u8"り");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_i }, u8"りぃ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_e }, u8"りぇ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_a }, u8"りゃ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_u }, u8"りゅ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_o }, u8"りょ");

	//る
	InsertGlyph(glyphMap, { SDLK_r, SDLK_u }, u8"る");

	//れ
	InsertGlyph(glyphMap, { SDLK_r, SDLK_e }, u8"れ");

	//ろ
	InsertGlyph(glyphMap, { SDLK_r, SDLK_o }, u8"ろ");

	//------

	//わ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_a }, u8"わ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_w, SDLK_a }, u8"ゎ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_w, SDLK_a }, u8"ゎ");

	//ゐ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_y, SDLK_i }, u8"ゐ");

	//ゑ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_y, SDLK_e }, u8"ゑ");

	//を
	InsertGlyph(glyphMap, { SDLK_w, SDLK_o }, u8"を");

	//------

	//ん
	InsertGlyph(glyphMap, { SDLK_n, SDLK_n }, u8"ん");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_n }, u8"ん");

	//------
	//Modifiers - Hiragana
	//が
	InsertGlyph(glyphMap, { SDLK_g, SDLK_a }, u8"が");

	//ぎ
	InsertGlyph(glyphMap, { SDLK_g, SDLK_i }, u8"ぎ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_i }, u8"ぎぃ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_e }, u8"ぎぇ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_a }, u8"ぎゃ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_u }, u8"ぎゅ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_o }, u8"ぎょ");

	//ぐ
	InsertGlyph(glyphMap, { SDLK_g, SDLK_u }, u8"ぐ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w, SDLK_a }, u8"ぐぁ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w, SDLK_i }, u8"ぐぃ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w, SDLK_u }, u8"ぐぅ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w , SDLK_e }, u8"ぐぇ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w, SDLK_o }, u8"ぐぉ");

	//げ
	InsertGlyph(glyphMap, { SDLK_g, SDLK_e }, u8"げ");

	//ご
	InsertGlyph(glyphMap, { SDLK_g, SDLK_o }, u8"ご");

	//ざ
	InsertGlyph(glyphMap, { SDLK_z, SDLK_a }, u8"さ");

	//じ
	InsertGlyph(glyphMap, { SDLK_j, SDLK_i }, u8"じ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_i }, u8"じ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_i }, u8"じぃ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_i }, u8"じぃ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_e }, u8"じぇ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_e }, u8"じぇ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_e }, u8"じぇ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_a }, u8"じゃ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_a }, u8"じゃ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_a }, u8"じゃ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_u }, u8"じゅ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_u }, u8"じゅ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_u }, u8"じゅ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_o }, u8"じょ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_o }, u8"じょ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_o }, u8"じょ");

	//ず
	InsertGlyph(glyphMap, { SDLK_z, SDLK_u }, u8"ず");

	//ぜ
	InsertGlyph(glyphMap, { SDLK_z, SDLK_e }, u8"ぜ");

	//ぞ
	InsertGlyph(glyphMap, { SDLK_z, SDLK_o }, u8"ぞ");

	//だ
	InsertGlyph(glyphMap, { SDLK_d, SDLK_a }, u8"だ");

	//ぢ
	InsertGlyph(glyphMap, { SDLK_d, SDLK_i }, u8"ぢ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_i }, u8"ぢぃ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_e }, u8"ぢぇ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_a }, u8"ぢゃ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_u }, u8"ぢゅ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_o }, u8"ぢょ");

	//づ
	InsertGlyph(glyphMap, { SDLK_d, SDLK_u }, u8"づ");

	//で
	InsertGlyph(glyphMap, { SDLK_d, SDLK_e }, u8"で");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_i }, u8"でぃ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_e }, u8"でぇ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_a }, u8"でゃ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_u }, u8"でゅ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_o }, u8"でょ");

	//ど
	InsertGlyph(glyphMap, { SDLK_d, SDLK_o }, u8"ど");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_a }, u8"どぁ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_i }, u8"どぃ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_u }, u8"どぅ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_e }, u8"どぇ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_o }, u8"どぉ");

	//ば
	InsertGlyph(glyphMap, { SDLK_b, SDLK_a }, u8"ば");

	//ぱ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_a }, u8"ぱ");

	//び
	InsertGlyph(glyphMap, { SDLK_b, SDLK_i }, u8"び");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_i }, u8"びぃ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_e }, u8"びぇ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_a }, u8"びゃ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_u }, u8"びゅ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_o }, u8"びょ");

	//ぴ
	InsertGlyph(glyphMap, { SDLK_p, SDLK_i }, u8"ぴ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_i }, u8"ぴぃ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_e }, u8"ぴぇ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_a }, u8"ぴゃ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_u }, u8"ぴゅ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_o }, u8"ぴょ");

	//ぶ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_u }, u8"ぶ");

	//ぷ
	InsertGlyph(glyphMap, { SDLK_p, SDLK_u }, u8"ぷ");

	//べ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_e }, u8"べ");

	//ぺ
	InsertGlyph(glyphMap, { SDLK_p, SDLK_e }, u8"ぺ");

	//ぼ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_o }, u8"ぼ");

	//ぽ
	InsertGlyph(glyphMap, { SDLK_p, SDLK_o }, u8"ぽ");

	//ヴ
	InsertGlyph(glyphMap, { SDLK_v, SDLK_a }, u8"ヴぁ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_i }, u8"ヴぃ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_i }, u8"ヴぃ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_e }, u8"ヴぇ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_e }, u8"ヴぇ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_o }, u8"ヴぉ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_a }, u8"ヴゃ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_u }, u8"ヴゅ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_o }, u8"ヴょ");

	//------
	//Katakana
	//ア 
	InsertGlyph(glyphMap, { SDLK_a }, u8"ア");
	InsertGlyph(glyphMap, { SDLK_l , SDLK_a }, u8"ァ");
	InsertGlyph(glyphMap, { SDLK_x , SDLK_a }, u8"ァ");

	//イ
	InsertGlyph(glyphMap, { SDLK_i }, u8"イ");
	InsertGlyph(glyphMap, { SDLK_y, SDLK_i }, u8"イ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_i }, u8"ィ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_i }, u8"ィ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_i }, u8"ィ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_i }, u8"ィ");
	InsertGlyph(glyphMap, { SDLK_y, SDLK_e }, u8"イェ");

	//ウ
	InsertGlyph(glyphMap, { SDLK_u }, u8"ウ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_u }, u8"ウ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_u }, u8"ウ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_u }, u8"ゥ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_u }, u8"ゥ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_a }, u8"ウァ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_i }, u8"ウィ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_i }, u8"ウィ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_e }, u8"ウェ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_e }, u8"ウェ");
	InsertGlyph(glyphMap, { SDLK_w, SDLK_h, SDLK_o }, u8"ウォ");

	//エ
	InsertGlyph(glyphMap, { SDLK_e }, u8"エ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_e }, u8"ェ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_e }, u8"ェ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_e }, u8"ェ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_e }, u8"ェ");

	//オ
	InsertGlyph(glyphMap, { SDLK_o }, u8"オ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_o }, u8"ォ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_o }, u8"ォ");

	//------

	//カ
	InsertGlyph(glyphMap, { SDLK_c, SDLK_a }, u8"カ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_a }, u8"カ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_k, SDLK_a }, u8"ヵ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_k, SDLK_a }, u8"ヵ");

	//キ
	InsertGlyph(glyphMap, { SDLK_k, SDLK_i }, u8"キ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_i }, u8"キィ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_e }, u8"キェ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_a }, u8"キャ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_u }, u8"キュ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_y, SDLK_o }, u8"キョ");

	//ク
	InsertGlyph(glyphMap, { SDLK_c, SDLK_u }, u8"ク");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_u }, u8"ク");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_u }, u8"ク");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_w, SDLK_a }, u8"クァ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_a }, u8"クァ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_a }, u8"クァ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_i }, u8"クィ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_i }, u8"クィ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_i }, u8"クィ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_u }, u8"クゥ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_e }, u8"クェ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_e }, u8"クェ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_e }, u8"クェ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_o }, u8"クォ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_w, SDLK_o }, u8"クォ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_a }, u8"クャ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_u }, u8"クュ");
	InsertGlyph(glyphMap, { SDLK_q, SDLK_y, SDLK_o }, u8"クョ");

	//ケ
	InsertGlyph(glyphMap, { SDLK_k, SDLK_e }, u8"ケ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_k, SDLK_e }, u8"ヶ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_k, SDLK_e }, u8"ヶ");

	//コ
	InsertGlyph(glyphMap, { SDLK_c, SDLK_o }, u8"コ");
	InsertGlyph(glyphMap, { SDLK_k, SDLK_o }, u8"コ");

	//------

	//サ
	InsertGlyph(glyphMap, { SDLK_s, SDLK_a }, u8"サ");

	//シ
	InsertGlyph(glyphMap, { SDLK_c, SDLK_i }, u8"シ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_i }, u8"シ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_i }, u8"シ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_i }, u8"シィ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_e }, u8"シェ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_e }, u8"シェ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_a }, u8"シャ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_a }, u8"シャ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_u }, u8"シュ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_u }, u8"シュ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_o }, u8"ショ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_y, SDLK_o }, u8"ショ");

	//ス
	InsertGlyph(glyphMap, { SDLK_s, SDLK_u }, u8"ス");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_a }, u8"スァ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_i }, u8"スィ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_u }, u8"スゥ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_e }, u8"スェ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_w, SDLK_o }, u8"スォ");

	//セ
	InsertGlyph(glyphMap, { SDLK_c, SDLK_e }, u8"セ");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_e }, u8"セ");

	//ソ
	InsertGlyph(glyphMap, { SDLK_s, SDLK_o }, u8"ソ");

	//------

	//タ
	InsertGlyph(glyphMap, { SDLK_t, SDLK_a }, u8"タ");

	//チ
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_i }, u8"チ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_i }, u8"チ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_i }, u8"チィ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_i }, u8"チィ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_e }, u8"チェ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_e }, u8"チェ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_e }, u8"チェ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_a }, u8"チャ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_a }, u8"チャ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_a }, u8"チャ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_u }, u8"チュ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_u }, u8"チュ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_u }, u8"チュ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_o }, u8"チョ");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_y, SDLK_o }, u8"チョ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_y, SDLK_o }, u8"チョ");

	//ツ
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_u }, u8"ツ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_u }, u8"ツ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_a }, u8"ツァ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_i }, u8"ツィ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_e }, u8"ツェ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_o }, u8"ツォ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_t, SDLK_s, SDLK_u }, u8"ッ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_t, SDLK_u }, u8"ッ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_t, SDLK_s, SDLK_u }, u8"ッ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_t, SDLK_u }, u8"ッ");

	//テ
	InsertGlyph(glyphMap, { SDLK_t, SDLK_e }, u8"テ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_i }, u8"ティ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_e }, u8"テェ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_a }, u8"テャ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_u }, u8"テュ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_h, SDLK_o }, u8"テョ");


	//ト
	InsertGlyph(glyphMap, { SDLK_t, SDLK_o }, u8"ト");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_a }, u8"トァ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_i }, u8"トィ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_u }, u8"トゥ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_e }, u8"トェ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_w, SDLK_o }, u8"トォ");

	//------

	//ナ
	InsertGlyph(glyphMap, { SDLK_n, SDLK_a }, u8"ナ");

	//ニ
	InsertGlyph(glyphMap, { SDLK_n, SDLK_i }, u8"ニ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_i }, u8"ニィ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_e }, u8"ニェ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_a }, u8"ニャ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_u }, u8"ニュ");
	InsertGlyph(glyphMap, { SDLK_n, SDLK_y, SDLK_o }, u8"ニョ");

	//ヌ
	InsertGlyph(glyphMap, { SDLK_n, SDLK_u }, u8"ヌ");

	//ネ
	InsertGlyph(glyphMap, { SDLK_n, SDLK_e }, u8"ネ");

	//ノ
	InsertGlyph(glyphMap, { SDLK_n, SDLK_o }, u8"ノ");

	//------

	//ハ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_a }, u8"ハ");

	//ヒ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_i }, u8"ヒ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_i }, u8"ヒィ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_e }, u8"ヒェ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_a }, u8"ヒャ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_u }, u8"ヒュ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_y, SDLK_o }, u8"ヒョ");

	//フ
	InsertGlyph(glyphMap, { SDLK_f, SDLK_u }, u8"フ");
	InsertGlyph(glyphMap, { SDLK_h, SDLK_u }, u8"フ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_a }, u8"ファ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_a }, u8"ファ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_i }, u8"フィ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_i }, u8"フィ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_i }, u8"フィ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_u }, u8"フゥ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_e }, u8"フェ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_e }, u8"フェ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_e }, u8"フェ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_o }, u8"フォ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_w, SDLK_o }, u8"フォ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_a }, u8"フャ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_u }, u8"フュ");
	InsertGlyph(glyphMap, { SDLK_f, SDLK_y, SDLK_o }, u8"フョ");

	//ヘ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_e }, u8"ヘ");

	//ホ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_o }, u8"ホ");

	//------

	//マ
	InsertGlyph(glyphMap, { SDLK_m, SDLK_a }, u8"マ");

	//ミ
	InsertGlyph(glyphMap, { SDLK_m, SDLK_i }, u8"ミ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_i }, u8"ミィ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_e }, u8"ミェ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_a }, u8"ミャ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_u }, u8"ミュ");
	InsertGlyph(glyphMap, { SDLK_m, SDLK_y, SDLK_o }, u8"ミョ");

	//ム
	InsertGlyph(glyphMap, { SDLK_m, SDLK_u }, u8"ム");

	//メ
	InsertGlyph(glyphMap, { SDLK_m, SDLK_e }, u8"メ");

	//モ
	InsertGlyph(glyphMap, { SDLK_m, SDLK_o }, u8"モ");

	//------

	//ヤ
	InsertGlyph(glyphMap, { SDLK_y, SDLK_a }, u8"ヤ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_a }, u8"ャ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_a }, u8"ャ");

	//ユ
	InsertGlyph(glyphMap, { SDLK_y, SDLK_u }, u8"ユ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_u }, u8"ュ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_u }, u8"ュ");

	//ヨ
	InsertGlyph(glyphMap, { SDLK_y, SDLK_o }, u8"ヨ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_y, SDLK_o }, u8"ョ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_y, SDLK_o }, u8"ョ");

	//------

	//ラ
	InsertGlyph(glyphMap, { SDLK_r, SDLK_a }, u8"ラ");

	//リ
	InsertGlyph(glyphMap, { SDLK_r, SDLK_i }, u8"リ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_i }, u8"リィ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_e }, u8"リェ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_a }, u8"リャ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_u }, u8"リュ");
	InsertGlyph(glyphMap, { SDLK_r, SDLK_y, SDLK_o }, u8"リョ");

	//ル
	InsertGlyph(glyphMap, { SDLK_r, SDLK_u }, u8"ル");

	//レ
	InsertGlyph(glyphMap, { SDLK_r, SDLK_e }, u8"レ");

	//ロ
	InsertGlyph(glyphMap, { SDLK_r, SDLK_o }, u8"ロ");

	//------

	//ワ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_a }, u8"ワ");
	InsertGlyph(glyphMap, { SDLK_l, SDLK_w, SDLK_a }, u8"ヮ");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_w, SDLK_a }, u8"ヮ");

	//ヰ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_y, SDLK_i }, u8"ヰ");

	//ヱ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_y, SDLK_e }, u8"ヱ");

	//ヲ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_o }, u8"ヲ");

	//------

	//ン
	InsertGlyph(glyphMap, { SDLK_n, SDLK_n }, u8"ン");
	InsertGlyph(glyphMap, { SDLK_x, SDLK_n }, u8"ン");

	//------
	//Modifiers - Katakana
	//ガ
	InsertGlyph(glyphMap, { SDLK_g, SDLK_a }, u8"ガ");

	//ギ
	InsertGlyph(glyphMap, { SDLK_g, SDLK_i }, u8"ギ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_i }, u8"ギィ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_e }, u8"ギェ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_a }, u8"ギャ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_u }, u8"ギュ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_y, SDLK_o }, u8"ギョ");

	//グ
	InsertGlyph(glyphMap, { SDLK_g, SDLK_u }, u8"グ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w, SDLK_a }, u8"グァ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w, SDLK_i }, u8"グィ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w, SDLK_u }, u8"グゥ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w , SDLK_e }, u8"グェ");
	InsertGlyph(glyphMap, { SDLK_g, SDLK_w, SDLK_o }, u8"グォ");

	//ゲ
	InsertGlyph(glyphMap, { SDLK_g, SDLK_e }, u8"ゲ");

	//ゴ
	InsertGlyph(glyphMap, { SDLK_g, SDLK_o }, u8"ゴ");

	//ザ
	InsertGlyph(glyphMap, { SDLK_z, SDLK_a }, u8"サ");

	//ジ
	InsertGlyph(glyphMap, { SDLK_j, SDLK_i }, u8"ジ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_i }, u8"ジ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_i }, u8"ジィ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_i }, u8"ジィ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_e }, u8"ジェ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_e }, u8"ジェ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_e }, u8"ジェ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_a }, u8"ジャ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_a }, u8"ジャ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_a }, u8"ジャ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_u }, u8"ジュ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_u }, u8"ジュ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_u }, u8"ジュ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_o }, u8"ジョ");
	InsertGlyph(glyphMap, { SDLK_j, SDLK_y, SDLK_o }, u8"ジョ");
	InsertGlyph(glyphMap, { SDLK_z, SDLK_y, SDLK_o }, u8"ジョ");

	//ズ
	InsertGlyph(glyphMap, { SDLK_z, SDLK_u }, u8"ズ");

	//ゼ
	InsertGlyph(glyphMap, { SDLK_z, SDLK_e }, u8"ゼ");

	//ゾ
	InsertGlyph(glyphMap, { SDLK_z, SDLK_o }, u8"ゾ");

	//ダ
	InsertGlyph(glyphMap, { SDLK_d, SDLK_a }, u8"ダ");

	//ヂ
	InsertGlyph(glyphMap, { SDLK_d, SDLK_i }, u8"ヂ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_i }, u8"ヂィ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_e }, u8"ヂェ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_a }, u8"ヂャ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_u }, u8"ヂュ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_y, SDLK_o }, u8"ヂョ");

	//ヅ
	InsertGlyph(glyphMap, { SDLK_d, SDLK_u }, u8"ヅ");

	//デ
	InsertGlyph(glyphMap, { SDLK_d, SDLK_e }, u8"デ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_i }, u8"ディ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_e }, u8"デェ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_a }, u8"デャ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_u }, u8"デュ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_h, SDLK_o }, u8"デョ");

	//ド
	InsertGlyph(glyphMap, { SDLK_d, SDLK_o }, u8"ド");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_a }, u8"ドァ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_i }, u8"ドィ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_u }, u8"ドゥ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_e }, u8"ドェ");
	InsertGlyph(glyphMap, { SDLK_d, SDLK_w, SDLK_o }, u8"ドォ");

	//バ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_a }, u8"バ");

	//パ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_a }, u8"パ");

	//ビ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_i }, u8"ビ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_i }, u8"ビィ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_e }, u8"ビェ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_a }, u8"ビャ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_u }, u8"ビュ");
	InsertGlyph(glyphMap, { SDLK_b, SDLK_y, SDLK_o }, u8"ビョ");

	//ピ
	InsertGlyph(glyphMap, { SDLK_p, SDLK_i }, u8"ピ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_i }, u8"ピィ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_e }, u8"ピェ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_a }, u8"ピャ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_u }, u8"ピュ");
	InsertGlyph(glyphMap, { SDLK_p, SDLK_y, SDLK_o }, u8"ピョ");

	//ブ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_u }, u8"ブ");

	//プ
	InsertGlyph(glyphMap, { SDLK_p, SDLK_u }, u8"プ");

	//ベ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_e }, u8"ベ");

	//ペ
	InsertGlyph(glyphMap, { SDLK_p, SDLK_e }, u8"ペ");

	//ボ
	InsertGlyph(glyphMap, { SDLK_b, SDLK_o }, u8"ボ");

	//ポ
	InsertGlyph(glyphMap, { SDLK_p, SDLK_o }, u8"ポ");

	//ヴ
	InsertGlyph(glyphMap, { SDLK_v, SDLK_a }, u8"ヴァ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_i }, u8"ヴィ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_i }, u8"ヴィ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_e }, u8"ヴェ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_e }, u8"ヴェ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_o }, u8"ヴォ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_a }, u8"ヴャ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_u }, u8"ヴュ");
	InsertGlyph(glyphMap, { SDLK_v, SDLK_y, SDLK_o }, u8"ヴョ");

	//Combinations not from the basic Hiragana Table, basic Katakana Table, and the modifiers
	//ー (pause)
	InsertGlyph(glyphMap, { SDLK_MINUS }, u8"ー");
}

Input::Input(Game* game) {
	//Initializes the token reader.
	this->tokens.reserve(Input::MaxTokenSize);

	//Initializes the glyph map.
	InitializeGlyphMap(this->glyphMap);

	//Set a reference to Game object.
	this->game = game;
}

Input::~Input() {
	while (!this->tokens.empty()) {
		this->tokens.pop_back();
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
}

void Input::ConfirmToken() {
	//This is fired when the user presses the Enter key to confirm the entered inputs.
	//std::map<std::vector<SDL_Keycode>, char*>::iterator it;
	//if ((it = this->glyphMap.find(this->tokens)) != this->glyphMap.end()) {
	//	//Found
	//	this->game->GetBlock()->ReplaceGlyph(it->second);
	//}
	//else {
	//	std::cout << "Not found! " << std::endl;
	//}

	char* value = this->glyphMap.Get(this->tokens);
	if (value) {
		this->game->GetBlock()->ReplaceGlyph(value);
		this->tokens.clear();
	}
	else if (this->tokens.size() >= Input::MaxTokenSize) {
		this->tokens.clear();
		std::cout << "Not found! Max tokens used." << std::endl;
	}
	else {
		TrieNode* node = this->glyphMap.GetNode(this->tokens);
		if ((!node) || (node && node->IsLeaf())) {
			this->tokens.clear();
			std::cout << "Not found! Incorrect input." << std::endl;
		}
	}
}

void Input::ClearTokens() {
	this->tokens.clear();
}