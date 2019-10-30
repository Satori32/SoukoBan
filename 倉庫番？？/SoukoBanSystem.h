#pragma once
#include <vector>
#include <cstdint>
#include <tuple>

#include "SoukoBanField.h"


class SoukoBanSystem {
	typedef std::tuple<std::uintmax_t, std::uintmax_t> Point;
	typedef std::vector<Point> Points;
public:

	enum {
		Up,
		Right,
		Down,
		Left,
	};
	bool New(std::uintmax_t W, std::uintmax_t Y) {
		SF.CreateField(W, Y);

		Hako.clear();
		std::get<0>(Hero) = 0;
		std::get<1>(Hero) = 0;
		return true;
	}
	bool SetHero(std::uintmax_t X, std::uintmax_t Y) {
		if (!SF.InRange(X, Y)) { return false; }
		std::get<0>(Hero) = X;
		std::get<1>(Hero) = Y;
		return true;
	}

	bool MoveHako(std::uintmax_t X, std::uintmax_t Y, std::uint8_t Dir) {
		std::int8_t XM[]{ 0,1,0, -1 };
		std::int8_t YM[]{ 1,0, -1,0 };
		if (!HaveHako(X, Y)) { return false; }
		Dir %= 4;
		std::intmax_t ID = GetHakoID(X, Y);

		if (ID == -1) { return false; }
		if (!InRange(X + XM[Dir], Y + YM[Dir])) { return false; }
		if (SF.HaveWall(X + XM[Dir], Y + YM[Dir])) { return false; }
		if (HaveHako(X + XM[Dir], Y + YM[Dir])) { return false; }

		std::get<0>(Hako[ID]) += XM[Dir];
		std::get<1>(Hako[ID]) += YM[Dir];

		return true;
	}

	bool InRange(std::uintmax_t X, std::uintmax_t Y) const {
		return SF.InRange(X, Y);
	}
	bool OnHero(std::uintmax_t X, std::uintmax_t Y)const {
		return std::get<0>(Hero) == X && std::get<1>(Hero) == Y;
	}
	bool MoveHero(std::uint8_t Dir) {
		std::int8_t XM[]{ 0,1,0, -1 };
		std::int8_t YM[]{ 1,0, -1,0 };
		Dir %= 4;
		if (!InRange(std::get<0>(Hero) + XM[Dir], std::get<1>(Hero) + YM[Dir])) { return false; }
		if (SF.HaveWall(std::get<0>(Hero) + XM[Dir], std::get<1>(Hero) + YM[Dir])) { return false; }
		if (HaveHako(std::get<0>(Hero) + XM[Dir], std::get<1>(Hero) + YM[Dir])) {
			if (!MoveHako(std::get<0>(Hero) + XM[Dir], std::get<1>(Hero) + YM[Dir], Dir)) { return false; };
		}
		if (!InRange(std::get<0>(Hero) + XM[Dir], std::get<1>(Hero) + YM[Dir])) { return false; }
		std::get<0>(Hero) += XM[Dir];
		std::get<1>(Hero) += YM[Dir];

		return true;
	}
	bool HaveHako(std::uintmax_t X, std::uintmax_t Y) const {
		if (!SF.InRange(X, Y)) { return false; }
		if (SF.HaveWall(X, Y)) { return false; }

		for (auto& o : Hako) {
			if (std::get<0>(o) == X && std::get<1>(o) == Y) { return true; }
		}
		return false;

	}
	bool IsGameEnd() const {
		for (auto o : Hako) {
			if (!SF.HaveBatu(std::get<0>(o), std::get<1>(o))) { return false; }
		}
		return true;
	}

	bool AddHako(std::uintmax_t X, std::uintmax_t Y) {
		if (SF.HaveWall(X, Y)) { return false; }
		if (HaveHako(X, Y)) { return false; }

		Hako.push_back({ X,Y });
		return true;
	}

	std::size_t HakoCount() const {
		return Hako.size();
	}

	std::uintmax_t Width() const {
		return SF.Width();
	}
	std::uintmax_t Height() const {
		return SF.Height();
	}
	const SoukoBanField& GetField()const {
		return SF;
	}
	SoukoBanField& GetField() {
		return SF;
	}
protected:
	std::intmax_t GetHakoID(std::uintmax_t X, std::uintmax_t Y) {
		for (std::size_t i = 0; i < Hako.size(); i++) {
			if (std::get<0>(Hako[i])==X &&std::get<1>(Hako[i])==Y) { return i; }
		}
		return -1;
	}

protected:
	SoukoBanField SF;
	Points Hako;
	Point Hero;
};