#include "input.h"

void InsertGlyph(std::map<std::vector<SDL_Keycode>, char*>& glyphMap, std::initializer_list<SDL_Keycode> list, char* glyph) {
	std::vector<SDL_Keycode> key;
	key.insert(key.end(), list);
	glyphMap.insert(std::pair<std::vector<SDL_Keycode>, char*>(key, glyph));
}

void InitializeGlyphMap(std::map<std::vector<SDL_Keycode>, char*>& glyphMap) {
	//Note(asperatology): There may be more than one method of typing the characters
	//out, therefore, there may be multiple entries for one glyph.
	//Glyphs may be 2 characters long.
	//Hiragana

	//あ
	InsertGlyph(glyphMap, { SDLK_a }, u8"あ");

	//い
	InsertGlyph(glyphMap, { SDLK_i }, u8"い");

	//う
	InsertGlyph(glyphMap, { SDLK_u }, u8"う");

	//え
	InsertGlyph(glyphMap, { SDLK_e }, u8"え");

	//お
	InsertGlyph(glyphMap, { SDLK_o }, u8"お");

	//------

	//か
	InsertGlyph(glyphMap, { SDLK_k, SDLK_a }, u8"か");

	//き
	InsertGlyph(glyphMap, { SDLK_k, SDLK_i }, u8"き");

	//く
	InsertGlyph(glyphMap, { SDLK_k, SDLK_u }, u8"く");

	//け
	InsertGlyph(glyphMap, { SDLK_k, SDLK_e }, u8"け");

	//こ
	InsertGlyph(glyphMap, { SDLK_k, SDLK_o }, u8"こ");

	//------

	//さ
	InsertGlyph(glyphMap, { SDLK_s, SDLK_a }, u8"さ");

	//し
	InsertGlyph(glyphMap, { SDLK_s, SDLK_i }, u8"し");
	InsertGlyph(glyphMap, { SDLK_s, SDLK_h, SDLK_i }, u8"し");

	//す
	InsertGlyph(glyphMap, { SDLK_s, SDLK_u }, u8"す");

	//せ
	InsertGlyph(glyphMap, { SDLK_s, SDLK_e }, u8"せ");

	//そ
	InsertGlyph(glyphMap, { SDLK_s, SDLK_o }, u8"そ");

	//------

	//た
	InsertGlyph(glyphMap, { SDLK_t, SDLK_a }, u8"た");

	//ち
	InsertGlyph(glyphMap, { SDLK_t, SDLK_i }, u8"ち");
	InsertGlyph(glyphMap, { SDLK_c, SDLK_h, SDLK_i }, u8"ち");

	//つ
	InsertGlyph(glyphMap, { SDLK_t, SDLK_u }, u8"つ");
	InsertGlyph(glyphMap, { SDLK_t, SDLK_s, SDLK_u }, u8"つ");

	//て
	InsertGlyph(glyphMap, { SDLK_t, SDLK_e }, u8"て");

	//と
	InsertGlyph(glyphMap, { SDLK_t, SDLK_o }, u8"と");

	//------

	//な
	InsertGlyph(glyphMap, { SDLK_n, SDLK_a }, u8"な");

	//に
	InsertGlyph(glyphMap, { SDLK_n, SDLK_i }, u8"に");

	//ぬ
	InsertGlyph(glyphMap, { SDLK_n, SDLK_u }, u8"ぬ");

	//ね
	InsertGlyph(glyphMap, { SDLK_n, SDLK_e }, u8"ね");

	//の
	InsertGlyph(glyphMap, { SDLK_n, SDLK_o }, u8"の");

	//------

	//は
	InsertGlyph(glyphMap, { SDLK_h, SDLK_a }, u8"さ");

	//ひ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_i }, u8"し");

	//ふ
	InsertGlyph(glyphMap, { SDLK_f, SDLK_u }, u8"す");

	//へ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_e }, u8"せ");

	//ほ
	InsertGlyph(glyphMap, { SDLK_h, SDLK_o }, u8"そ");

	//------

	//ま
	InsertGlyph(glyphMap, { SDLK_m, SDLK_a }, u8"さ");

	//み
	InsertGlyph(glyphMap, { SDLK_m, SDLK_i }, u8"し");

	//む
	InsertGlyph(glyphMap, { SDLK_m, SDLK_u }, u8"す");

	//め
	InsertGlyph(glyphMap, { SDLK_m, SDLK_e }, u8"せ");

	//も
	InsertGlyph(glyphMap, { SDLK_m, SDLK_o }, u8"そ");

	//------

	//や
	InsertGlyph(glyphMap, { SDLK_y, SDLK_a }, u8"さ");

	//ゆ
	InsertGlyph(glyphMap, { SDLK_y, SDLK_u }, u8"し");

	//よ
	InsertGlyph(glyphMap, { SDLK_y, SDLK_o }, u8"す");

	//------

	//ら
	InsertGlyph(glyphMap, { SDLK_r, SDLK_a }, u8"さ");

	//り
	InsertGlyph(glyphMap, { SDLK_r, SDLK_i }, u8"し");

	//る
	InsertGlyph(glyphMap, { SDLK_r, SDLK_u }, u8"す");

	//れ
	InsertGlyph(glyphMap, { SDLK_r, SDLK_e }, u8"せ");

	//ろ
	InsertGlyph(glyphMap, { SDLK_r, SDLK_o }, u8"そ");

	//------

	//わ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_a }, u8"さ");

	//ゐ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_i }, u8"さ");

	//ゑ
	InsertGlyph(glyphMap, { SDLK_w, SDLK_e }, u8"さ");

	//を
	InsertGlyph(glyphMap, { SDLK_w, SDLK_o }, u8"し");

	//------

	//ん
	InsertGlyph(glyphMap, { SDLK_n, SDLK_n }, u8"りゅ");

	//------
	//Modifiers - Hiragana

	//------
	//Katakana

	//------
	//Modifiers - Katakana

	//Combinations not from the basic Hiragana Table, basic Katakana Table, and the modifiers

	/*
	Also check the Microsoft Japanese IME template mappings. 
	Contains the actual input methods for all characters.
	ぁ: xa
	あ: a
	ぃ: xi
	い: i
	いぇ: ye
	ぅ: xu
	う: u
	うぁ: wha
	うぃ: whi
	うぇ: whe
	うぉ: who
	ぇ: xe
	え: e
	ぉ: xo
	お: o
	か: ka
	が: ga
	き: ki
	きゃ: kya
	きゅ: kyu
	きょ: kyo
	ぎ: gi
	ぎゃ: gya
	ぎゅ: gyu
	ぎょ: gyo
	く: ku
	ぐ: gu
	ぐぁ: qwa
	ぐぃ: gwi
	ぐぅ: gwu
	ぐぇ: gwe
	ぐぉ: gwo
	け: ke
	げ: ge
	こ: ko
	ご: go
	さ: sa
	ざ: za
	し: shi, si
	し: shi, si
	しぃ: syi
	しぇ: sye, she
	しぇ: sye, she
	しゃ: sya, sha
	しゃ: sya, sha
	しゅ: shu, syu
	しゅ: shu, syu
	しょ: syo, sho
	しょ: syo, sho
	じ: ji, zi
	じ: ji, zi
	じぃ: jyi
	じぇ: jye
	じゃ: jya, zya, ja
	じゃ: jya, zya, ja
	じゃ: jya, zya, ja
	じゅ: ju, zyu, jyu
	じゅ: ju, zyu, jyu
	じゅ: ju, zyu, jyu
	じょ: jyo, jo, zyo
	じょ: jyo, jo, zyo
	じょ: jyo, jo, zyo
	す: su
	すぁ: swa
	すぃ: swi
	すぅ: swu
	すぇ: swe
	すぉ: swo
	ず: zu
	せ: se
	ぜ: ze
	そ: so
	ぞ: zo
	た: ta
	だ: da
	ち: ti, chi
	ち: ti, chi
	ちぃ: cyi
	ちぇ: cye
	ちゃ: cha, tya, cya
	ちゃ: cha, tya, cya
	ちゃ: cha, tya, cya
	ちゅ: tyu, chu, cyu
	ちゅ: tyu, chu, cyu
	ちゅ: tyu, chu, cyu
	ちょ: cho, cyo, tyo
	ちょ: cho, cyo, tyo
	ちょ: cho, cyo, tyo
	ぢ: di
	ぢぃ: dyi
	ぢぇ: dye
	ぢゃ: dya
	ぢゅ: dyu
	ぢょ: dyo
	っ: xtu, xtsu
	っ: xtu, xtsu
	つ: tsu, tu
	つ: tsu, tu
	つぁ: tsa
	つぃ: tsi
	つぇ: tse
	つぉ: tso
	づ: du, dzu
	づ: du, dzu
	て: te
	てぃ: thi
	てぇ: the
	てゃ: tha
	てゅ: thu
	てょ: tho
	で: de
	でぃ: dhi
	でぇ: dhe
	でゃ: dha
	でゅ: dhu
	でょ: dho
	と: to
	とぁ: twa
	とぃ: twi
	とぅ: twu
	とぇ: twe
	とぉ: two
	ど: do
	どぁ: dwa
	どぃ: dwi
	どぅ: dwu
	どぇ: dwe
	どぉ: dwo
	な: na
	に: ni
	にゃ: nya
	にゅ: nyu
	にょ: nyo
	ぬ: nu
	ね: ne
	の: no
	は: ha
	ば: ba
	ぱ: pa
	ひ: hi
	ひぃ: hyi
	ひぇ: hye
	ひゃ: hya
	ひゅ: hyu
	ひょ: hyo
	び: bi
	びぃ: byi
	びぇ: bye
	びゃ: bya
	びゅ: byu
	びょ: byo
	ぴ: pi
	ぴぃ: pyi
	ぴぇ: pye
	ぴゃ: pya
	ぴゅ: pyu
	ぴょ: pyo
	ふ: hu, fu
	ふ: hu, fu
	ふぁ: fa
	ふぃ: fi
	ふぇ: fe
	ふぉ: fo
	ふゃ: fya
	ふゅ: fyu
	ふょ: fyo
	ぶ: bu
	ぷ: pu
	へ: he
	べ: be
	ぺ: pe
	ほ: ho
	ぼ: bo
	ぽ: po
	ま: ma
	み: mi
	みぃ: myi
	みぇ: mye
	みゃ: mya
	みゅ: myu
	みょ: myo
	む: mu
	め: me
	も: mo
	ゃ: xya
	や: ya
	ゅ: xyu
	ゆ: yu
	ょ: xyo
	よ: yo
	ら: la, ra
	ら: la, ra
	り: ri, li
	り: ri, li
	りぃ: ryi
	りぇ: rye
	りゃ: lya, rya
	りゃ: lya, rya
	りゅ: ryu, lyu
	りゅ: ryu, lyu
	りょ: ryo, lyo
	りょ: ryo, lyo
	る: lu, ru
	る: lu, ru
	れ: le, re
	れ: le, re
	ろ: ro, lo
	ろ: ro, lo
	ゎ: xwa
	わ: wa
	ゐ: wi
	ゑ: we
	を: wo
	ん: n', nn, n
	ん: n', nn, n
	ん: n', nn, n
	ゔ: vu
	ゔぁ: va
	ゔぃ: vyi, vi
	ゔぃ: vyi, vi
	ゔぇ: vye, ve
	ゔぇ: vye, ve
	ゔぉ: vo
	ゔゃ: vya
	ゔゅ: vyu
	ゔょ: vyo
	ゕ: xka
	ゖ: xke
	ー: - 
	*/
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
	if (this->tokens.size() < Input::MaxTokenSize){
		this->tokens.push_back(inputCode);
		if (this->tokens.size() >= Input::MaxTokenSize) {
			std::cout << "Too many tokens, auto-confirming!" << std::endl;
			this->ConfirmToken();
		}
	}
}

void Input::ConfirmToken() {
	//This is fired when the user presses the Enter key to confirm the entered inputs.
	std::map<std::vector<SDL_Keycode>, char*>::iterator it;
	if ((it = this->glyphMap.find(this->tokens)) != this->glyphMap.end()) {
		//Found
		this->game->GetBlock()->ReplaceGlyph(it->second);
	}
	else {
		std::cout << "Not found! " << std::endl;
	}
	this->tokens.clear();
}