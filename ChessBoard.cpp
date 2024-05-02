//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include "ChessBoard.hpp"
using namespace std;

int King::compteurRoi = 0;

namespace board {
	
	ChessBoard::ChessBoard() {};

	ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), squareSize(50)
	{
		
		for (int col = 0; col < 8; ++col) {
			for (int row = 0; row < 8; ++row) {
				squares.append(QRect(col * squareSize, row * squareSize, squareSize, squareSize));
				buttons[row][col] = new QPushButton(this);
				buttons[row][col]->setGeometry(col * squareSize, row * squareSize, squareSize, squareSize);
				buttons[row][col]->setFlat(true);
				buttons[row][col]->setVisible(true);
				QFont nouvellePolice = buttons[row][col]->font();
				nouvellePolice.setPointSize(30);
				buttons[row][col]->setFont(nouvellePolice);
			   
			}
		}
		
		setFixedSize(8 * squareSize, 8 * squareSize);
		Knight blackKnight(Piece::Color::BLACK);
		Tour whiteRook(Piece::Color::WHITE);
		
		try{
		King roi1(Piece::Color::WHITE);
		addPieceSlot(roi1, 4, 6);
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Erreur : " << e.what() << std::endl;
		}
		addPieceSlot(blackKnight,2,1);
		addPieceSlot(whiteRook,6,5);
	}

	void ChessBoard::setSquareSize(int size)
	{
		squareSize = size;
	}


	void ChessBoard::paintEvent(QPaintEvent* event)
	{
		Q_UNUSED(event);
		QPainter painter(this);
		drawChessboard(&painter);
	}

	void ChessBoard::drawChessboard(QPainter* painter)
	{
		QColor lightColor(209, 139, 71);
		QColor darkColor(255, 206, 158);
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if ((row + col) % 2 == 0) {
					painter->setBrush(lightColor);

				}
				else {
					painter->setBrush(darkColor);
				}
				painter->drawRect(squares[row * 8 + col]);
			}
		}
	}

	ChessBoard::~ChessBoard() {
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				delete buttons[row][col];
			}
		}
	}

	void ChessBoard::addPieceSlot(Piece& piece, int posX, int posY)
	{
		isDisplay_ = false; 
		char32_t image = piece.getUnicode();
		QString imagePiece = QString::fromUcs4(&image, 1);
		Piece::Color color = piece.getColor();
		piece.setPosition(posX, posY);

		buttons[posY][posX]->setText(imagePiece);
		
		if (color == Piece::Color::BLACK) {
			buttons[posY][posX]->setStyleSheet("color: black;");
		}
		else {
			buttons[posY][posX]->setStyleSheet("color: white;");
		}
		connect(buttons[posY][posX], &QPushButton::clicked, this, [=]() {
			if ((!(isDisplay_)) && color == turnColor_) {
					disconnect(buttons[posY][posX], &QPushButton::clicked, this, nullptr);
				
					displayPossibleMoves(piece, posX, posY);
			}
			});
	}

	
    void ChessBoard::displayPossibleMoves(Piece& piece, int posX, int posY ) {
		isDisplay_ = true;
        Piece::Type pieceType = piece.getType();
		Piece::Color color = piece.getColor();
		
        vector<pair<int, int>> movesPos = piece.getPossibleMoves(posX,posY,pieceType);
		QString texteBouton;
		
		
			for (const auto& moves : movesPos) {
				texteBouton = buttons[moves.first][moves.second]->text();
				if (texteBouton == "") {
					buttons[moves.first][moves.second]->setStyleSheet("color: green;");
					buttons[moves.first][moves.second]->setText("*");
					connect(buttons[moves.first][moves.second], &QPushButton::clicked, this, [=]() {

						for (const auto& moves2 : movesPos) {
							QString texteBouton2 = buttons[moves2.first][moves2.second]->text();
							if (texteBouton2 == "*") {
								disconnect(buttons[moves2.first][moves2.second], &QPushButton::clicked, this, nullptr);
								buttons[moves2.first][moves2.second]->setText("");
							}
						}
						disconnect(buttons[posY][posX], &QPushButton::clicked, this, nullptr);
						buttons[posY][posX]->setText("");
						
						if (turnColor_ == Piece::Color::WHITE) {
							turnColor_ = Piece::Color::BLACK;
						}
						else {
							turnColor_ = Piece::Color::WHITE;
						}
						addPieceSlot(piece, moves.second, moves.first);

						});
				}
				else {
					Piece::Color colorCase = getCaseColor(moves.first, moves.second);
					
					if (color != colorCase) {
						connect(buttons[moves.first][moves.second], &QPushButton::clicked, this, [=]() {
							disconnect(buttons[moves.first][moves.second], &QPushButton::clicked, this, nullptr);
							for (const auto& moves2 : movesPos) {
								QString texteBouton2 = buttons[moves2.first][moves2.second]->text();
								if (texteBouton2 != "") {
									disconnect(buttons[moves2.first][moves2.second], &QPushButton::clicked, this, nullptr);
									buttons[moves2.first][moves2.second]->setText("");
								}
							}
							buttons[posY][posX]->setText("");
							if (turnColor_ == Piece::Color::WHITE) {
								turnColor_ = Piece::Color::BLACK;
							}
							else {
								turnColor_ = Piece::Color::WHITE;
							}
							disconnect(buttons[posY][posX], &QPushButton::clicked, this, nullptr);
							addPieceSlot(piece, moves.second, moves.first);

							});
					}
				}
			
			connect(buttons[posY][posX], &QPushButton::clicked, this, [=]() {
				disconnect(buttons[posY][posX], &QPushButton::clicked, this, nullptr);
				for (const auto& moves : movesPos) {
					QString texteBouton3 = buttons[moves.first][moves.second]->text();
					if (texteBouton3 == "*") {
						disconnect(buttons[moves.first][moves.second], &QPushButton::clicked, this, nullptr);
						buttons[moves.first][moves.second]->setText("");
					}
				}
				addPieceSlot(piece, posX, posY);
				});
			}
		
	}
	Piece::Color ChessBoard::getCaseColor(int posX, int posY) {
		QString pieceCase = buttons[posX][posY]->text();
		vector<char32_t> listWhite = { U'\u2654',U'\u2658',U'\u2656' }; //caractere unicode de nos trois pieces blanches
		for (auto unicode : listWhite) {
			QString colorPiece = QString::fromUcs4(&unicode, 1);
			if (pieceCase == colorPiece) {
				return Piece::Color::WHITE;
			}
		}
		return Piece::Color::BLACK;

	}

	void ChessBoard::isCheck() {}
	
}