#include <iostream>
#include <random>
#include <cstdlib>

#include <conio.h>//not standard.

#include "SoukoBanSystem.h"

SoukoBanSystem MakeField(){
	SoukoBanSystem SS;
	SS.New(16, 16);
	SS.GetField().SetBatu(7, 6);
	SS.GetField().SetBatu(7, 7);
	SS.GetField().SetWall(1, 1);
	SS.AddHako(8, 7);
	SS.AddHako(9, 7);
	SS.SetHero(10, 7);

	return SS;
}

SoukoBanSystem MakeField(std::uintmax_t W, std::uintmax_t H,std::uintmax_t Wall=16,std::uintmax_t Batu=8,unsigned int S=0) {
	SoukoBanSystem SS;
	SS.New(W, H);

	std::mt19937 mt(S);
	std::uniform_int_distribution<std::uintmax_t> Xui(1, W - 2);
	std::uniform_int_distribution<std::uintmax_t> Yui(1, H - 2);

	for (std::uintmax_t i = 0; i < Wall; i++) {
		if (!SS.GetField().SetWall(Xui(mt), Yui(mt))) {i--;continue;};
	}

	for (std::uintmax_t i = 0; i < Batu; i++) {
		if (!SS.GetField().SetBatu(Xui(mt), Yui(mt))) {i--;continue;};
	}
	for (std::uintmax_t i = 0; i < Batu; i++) {
		if (!SS.AddHako(Xui(mt), Yui(mt))) {i--;continue;};
	}
	return SS;
}

bool Show(const SoukoBanSystem& SS) {

	std::system("cls");
	for (std::uintmax_t Y = 0; Y < SS.Height(); Y++) {
		for (std::uintmax_t X = 0; X < SS.Width(); X++) {
			char Ch = ' ';
			if (SS.GetField().HaveWall(X, Y)) { Ch = 'W'; }
			if (SS.GetField().HaveBatu(X, Y)) { Ch = 'X'; }
			if (SS.HaveHako(X, Y)) {
				if (Ch == 'X') { Ch = '+'; }
				else{ Ch = 'B'; }
			}
			if (SS.OnHero(X, Y)) { Ch = 'H'; }
			std::cout << Ch;
		}
		std::cout << std::endl;
	}

	return true;
}

int main() {
	SoukoBanSystem SS = MakeField(16,16);//ランダム生成。解けない問題ができる可能性がある。

	while (!SS.IsGameEnd()) {
		Show(SS);
		std::cout << "ESC Key to Shutdown Game." << std::endl;
		int key = _getch();
		if (key == 27) { break; }

		if (key == 'w') {
			SS.MoveHero(SoukoBanSystem::Down);
		}
		if (key == 's') {
			SS.MoveHero(SoukoBanSystem::Up);
		}
		if (key == 'a') {
			SS.MoveHero(SoukoBanSystem::Left);
		}
		if (key == 'd') {
			SS.MoveHero(SoukoBanSystem::Right);
		}
		std::cin.clear();
	}
	Show(SS);
	std::cout << "Game End!" << std::endl;
}