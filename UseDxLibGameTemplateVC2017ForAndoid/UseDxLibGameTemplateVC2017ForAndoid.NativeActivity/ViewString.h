#pragma once
#include "Image.h"

/**
 * 文字列を表示するクラス.
 * フォントは外で用意.このクラス内ではフォントを破棄しない
 */
class ViewString {
public:
	ViewString() { loadDefaultFont(); };
	ViewString(int font) : font(font) { loadDefaultFont(); };
	ViewString(const std::string& str) { loadDefaultFont(); setString(str); };
	ViewString(const std::string& str, int font) : font(font) { loadDefaultFont(); setString(str); };
	~ViewString() { DeleteGraph(img); };

	void loadDefaultFont() { if (defaultFont <= 0) defaultFont = CreateFontToHandle("MS ゴシック", 12, 0, DX_FONTTYPE_ANTIALIASING_4X4); };
	void setFont(int font) { this->font = font; setString(str);};
	void setFont(int font, int height) { this->font = font; this->height = height; setString(str); };
	void setString(const std::string& str);
	void setFontHeight(float height) { this->height = height; setString(str);};
	void setColor(int color) { this->color = color; setString(str); };

	// Imageのラッパー
	void draw();
	void setAlign(const Align::Horizontal& hAlign) { strImg.setAlign(hAlign); };
	void setAlign(const Align::Vertical& vAlign) { strImg.setAlign(vAlign); };
	void setAlign(const Align::Horizontal& hAlign, const Align::Vertical& vAlign) { strImg.setAlign(hAlign, vAlign); };
	void setPosition(float x, float y) { strImg.setPosition(x, y); };
	void setPosition(const Point& position) { strImg.setPosition(position); };
	void setScrollPosition(float x, float y) { strImg.setScrollPosition(x, y); };
	void setScrollPosition(const Point& scroll) { strImg.setScrollPosition(scroll); };
	void setScale(float x, float y) { strImg.setScale(x, y); };
	void setScale(const Point& scale) { strImg.setScale(scale); };
	void setAngle(float angle) { strImg.setAngle(angle); };
	void addAngle(float delta) { strImg.addAngle(delta); };
	void setAlpha(int alpha) { strImg.setAlpha(alpha); }; //0~255
	void recalcPosition() { strImg.recalcPosition(); };
	const Point& getPosition() const { return strImg.getPosition(); };
	const Point& getUpperLeftPosition() const { return strImg.getUpperLeftPosition(); };
	const std::array<std::pair<float, float>, 4>& getVertexes() const { return strImg.getVertexes(); };
	Point getPositionNonScroll() { return strImg.getPositionNonScroll(); };
	const Point& getImageSize() const { return strImg.getImageSize(); }; //画像そのままのサイズを返します
	const Point& getSize() const { return strImg.getSize(); }; //画像をリスケール後のサイズを返します
	const float& getAngle() const { return strImg.getAngle(); };
	void drawByVertex(const std::vector<Point>& vertex) const { strImg.drawByVertex(vertex); }; //頂点の値は保存されない
	void setHasDefaultCollider(bool b) { strImg.setHasDefaultCollider(b); };
	bool getIsOutOfWindow() { return strImg.getIsOutOfWindow(); };
private:
	Image strImg;
	std::string str;
	int color = 0xffffff;
	int img = 0;
	int font = 0;
	float height = 0;
	int width = 0;
	static int defaultFont;
};