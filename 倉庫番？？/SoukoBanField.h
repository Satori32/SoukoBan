#pragma once
#include <vector>
#include <cstdint>
#include <tuple>

class SoukoBanField {
	typedef std::tuple<std::uintmax_t, std::uintmax_t> Point;
	typedef std::vector<Point> Points;
public:

	bool CreateField(std::uintmax_t Width, std::uintmax_t Height) {
		Wall.clear();
		Batu.clear();
		W = Width;
		H = Height;
		return true;
	}

	bool InRange(std::uintmax_t X, std::uintmax_t Y) const{
		if (X >= W) { return false; }
		if (Y >= H) { return false; }

		return true;
	}

	bool HaveWall(std::uintmax_t X, std::uintmax_t Y) const{	
		if (!InRange(X,Y)) { return false; }

		for (auto& o : Wall) {
			if (std::get<0>(o) == X && std::get<1>(o) == Y) { return true; }
		}
		return false;
	}

	bool SetWall(std::uintmax_t X, std::uintmax_t Y) {	
		if (!InRange(X,Y)) { return false; }
		if (HaveWall(X, Y)) { return false; }
		if (HaveBatu(X, Y)) { return false; }
		Wall.push_back({ X,Y });
		return true;
	}
	bool EraseWall(std::uintmax_t X, std::uintmax_t Y) {
		if (!InRange(X,Y)) { return false; }
		if (!HaveWall(X, Y)) { return false; }
		for (std::size_t i = 0; i < Wall.size(); i++) {
			if (std::get<0>(Wall[i]) == X && std::get<1>(Wall[i]) == Y) {
				Wall.erase(Wall.begin() + i);
				return true;
			}
		}
		return false;
	}
	bool HaveBatu(std::uintmax_t X, std::uintmax_t Y) const{
		if (!InRange(X,Y)) { return false; }
		for (auto& o : Batu) {
			if (std::get<0>(o) == X && std::get<1>(o) == Y) { return true; }
		}
		return false;
	}

	bool SetBatu(std::uintmax_t X, std::uintmax_t Y) {
		if (!InRange(X,Y)) { return false; }
		if (HaveBatu(X, Y)) { return false; }
		if (HaveWall(X, Y)) { return false; }
		Batu.push_back({ X,Y });
		return true;
	}
	bool EraseBatu(std::uintmax_t X, std::uintmax_t Y) {
		if (!InRange(X,Y)) { return false; }
		if (!HaveBatu(X, Y)) { return false; }
		for (std::size_t i = 0; i < Wall.size(); i++) {
			if (std::get<0>(Batu[i]) == X && std::get<1>(Batu[i]) == Y) {
				Batu.erase(Batu.begin() + i);
				return true;
			}
		}
		return false;
	}
	std::uintmax_t Width() const{
		return W;
	}
	std::uintmax_t Height() const{
		return H;
	}
	std::size_t WallCount()const {
		return Wall.size();
	}
	std::size_t BatuCount() const{
		return Batu.size();
	}
protected:
	Points Wall;
	Points Batu;
	std::uintmax_t W = 0;
	std::uintmax_t H = 0;
};