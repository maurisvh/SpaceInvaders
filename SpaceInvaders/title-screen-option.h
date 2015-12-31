#pragma once

namespace si {
	const int nrTitleScreenOptions = 3;
	enum TitleScreenOption {
		StartGame = 0,
		TestLevel = 1,
		QuitGame = 2,
	};

	const std::string titleScreenOptionText[nrTitleScreenOptions] = {
		"Start game", "Test levels", "Quit"
	};
}