//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#include "RAII.hpp"
/*
RAII::RAII(Piece& piece, int posX, int posY, QPushButton* buttons[8][8]) {
	
	char32_t image = piece.getUnicode();
	const QString imagePiece = QString::fromUcs4(&image, 1);
	Piece::Color color = piece.getColor();


	buttons[posY][posX] = new QPushButton(imagePiece, this);
	buttons[posY][posX]->setGeometry((posX)*squareSize, (posY)*squareSize, squareSize, squareSize);
	buttons[posY][posX]->setFlat(true);
	buttons[posY][posX]->setVisible(true);
	QFont nouvellePolice = buttons[posY][posX]->font();
	nouvellePolice.setPointSize(30);
	buttons[posY][posX]->setFont(nouvellePolice);


	if (color == Piece::Color::BLACK) {
		buttons[posY][posX]->setStyleSheet("color: black;");
	}
	else {
		buttons[posY][posX]->setStyleSheet("color: white;"); 
	}

	connect(buttons[posY][posX], &QPushButton::clicked, this, [=]() {

		Piece::Type pieceType = piece.getType();

		vector<pair<int, int>> movesPos = piece.getPossibleMoves(posX, posY, pieceType);

		for (const auto& moves : movesPos) {
			if (buttons[moves.first][moves.second] == nullptr) {

				buttons[moves.first][moves.second] = new QPushButton("*", this);
				buttons[moves.first][moves.second]->setGeometry((moves.second) * squareSize, (moves.first) * squareSize, squareSize, squareSize);
				buttons[moves.first][moves.second]->setFlat(true);
				buttons[moves.first][moves.second]->setVisible(true);
				QFont nouvellePolice = buttons[moves.first][moves.second]->font();
				nouvellePolice.setPointSize(40);
				buttons[moves.first][moves.second]->setFont(nouvellePolice);
				buttons[moves.first][moves.second]->setStyleSheet("color: green;");

				connect(buttons[moves.first][moves.second], &QPushButton::clicked, this, [=]() {

					for (const auto& moves2 : movesPos) {

						buttons[moves2.first][moves2.second]->setText("");
						delete buttons[moves2.first][moves2.second];
						buttons[moves2.first][moves2.second] = nullptr;
					}


					buttons[posY][posX]->setText("");
					delete buttons[posY][posX];
					buttons[posY][posX] = nullptr;
					buttons[moves.first][moves.second] = new QPushButton(imagePiece, this);
					});
			}
		}

		});
	
}
	*/