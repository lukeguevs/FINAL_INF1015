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

			   
				delete buttons[row][col];
				buttons[row][col] = nullptr;
			}
		}
		
		setFixedSize(8 * squareSize, 8 * squareSize);
		Knight blackKnight(Piece::Color::BLACK);
		Tour whiteRook(Piece::Color::WHITE);
		
		try{
		King roi1(Piece::Color::WHITE);
		addPieceSlot(roi1, 4, 6);
		King roi2(Piece::Color::WHITE);
		addPieceSlot(roi2, 5, 6);
		King roi3(Piece::Color::WHITE);
		addPieceSlot(roi3, 6, 6);
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

	void ChessBoard::addPieceSlot(const Piece& piece, int posX, int posY)
	{
		
		char32_t image = piece.getUnicode();
		QString imagePiece = QString::fromUcs4(&image, 1);
		Piece::Color color = piece.getColor();
		
		
		buttons[posY][posX] = new QPushButton(imagePiece, this);
		buttons[posY][posX]->setGeometry((posX) * squareSize, (posY) * squareSize, squareSize, squareSize);
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
			
			displayAndMove(piece, posX, posY);
			});
	}

	
	void ChessBoard::displayAndMove(const Piece& piece, int posX, int posY) {
		isDisplay_ = true;
		Piece::Type pieceType = piece.getType();
		Piece::Color color = piece.getColor();

		vector<pair<int, int>> movesPos = piece.getPossibleMoves(this, posX, posY, pieceType);
		QString texteBouton;

		for (const auto& moves : movesPos) {
			texteBouton = buttons[moves.first][moves.second]->text();
			if (texteBouton == "") {
				buttons[moves.first][moves.second]->setStyleSheet("color: green;");
				buttons[moves.first][moves.second]->setText("*");
				connect(buttons[moves.first][moves.second], &QPushButton::clicked, this, [=]() {
					for (auto moves2 : movesPos) {
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
						for (auto moves2 : movesPos) {
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
		}

		connect(buttons[posY][posX], &QPushButton::clicked, this, [=]() {
			disconnect(buttons[posY][posX], &QPushButton::clicked, this, nullptr);
			for (auto moves : movesPos) {
				QString texteBouton3 = buttons[moves.first][moves.second]->text();
				if (texteBouton3 == "*") {
					disconnect(buttons[moves.first][moves.second], &QPushButton::clicked, this, nullptr);
					buttons[moves.first][moves.second]->setText("");
				}
			}
			addPieceSlot(piece, posX, posY);
			});
		piecePositions.clear();
		findPieces();
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
	void ChessBoard::findPieces() {
		for (int col = 0; col < 8; ++col) {
			for (int row = 0; row < 8; ++row) {
				if (buttons[row][col]->text() != "") {
					piecePositions.insert(make_pair(buttons[row][col]->text(), make_pair(row, col)));
				}
			}
		}
	}


	bool ChessBoard::isPathBlocked(int startY, int startX, int endY, int endX) const {
		// Check if it's a diagonal or straight move
		if (startY != endY && startX != endX) {
			// Diagonal moves are not allowed for Rooks (handled elsewhere)
			return true;
		}

		// Get the direction of movement (up, down, left, or right)
		int directionX = (endX - startX) / abs(endX - startX); // -1, 0, or 1
		int directionY = (endY - startY) / abs(endY - startY); // -1, 0, or 1

		// Loop through squares between the start and end positions (excluding start and end)
		for (int y = startY + directionY;
			(directionY == 1 && y < endY) || (directionY == -1 && y > endY) || y == endY;
			y += directionY) {
			for (int x = startX + directionX;
				(directionX == 1 && x < endX) || (directionX == -1 && x > endX) || x == endX;
				x += directionX) {
				// Skip checking the starting square and the ending square
				if (x == startX && y == startY) {
					continue;
				}

				// Check if the square is occupied
				if (isSquareOccupied(x, y)) {
					return true; // Path is blocked
				}
			}
		}

		return false; // Path is not blocked
	}


	bool ChessBoard::isSquareOccupied(int x, int y) const {

		if (x < 0 || x >= 8 || y < 0 || y >= 8) {
			return false;
		}

		return piecePositions.find(buttons[y][x]->text()) != piecePositions.end();
	}
}