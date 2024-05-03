//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

constexpr int BOARD_SIZE = 8;
#include "ChessBoard.hpp"
using namespace std;

int King::compteurRoi = 0;


	ChessBoard::ChessBoard() {};

	ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), squareSize(50)
	{

		for (int col = 0; col < BOARD_SIZE; ++col) {
			for (int row = 0; row < BOARD_SIZE; ++row) {
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

		try {
			King roi1(Piece::Color::WHITE);
			addPieceSlot(roi1, 4, 6);
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Erreur : " << e.what() << std::endl;
		}
		addPieceSlot(blackKnight, 2, 1);
		addPieceSlot(whiteRook, 6, 5);

		findPieces();
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

	void ChessBoard::addPieceSlot(Piece piece, int posX, int posY)
	{
		isDisplay_ = false;
		char32_t image = piece.getUnicode();
		QString imagePiece = QString::fromUcs4(&image, 1);
		Piece::Color color = piece.getColor();

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

				displayAndMove(piece, posX, posY);
			}
			});
	}


	void ChessBoard::displayAndMove(Piece piece, int posX, int posY) {
		isDisplay_ = true;
		Piece::Type pieceType = piece.getType();
		Piece::Color color = piece.getColor();

		piece.setPossibleMoves(posX, posY, pieceType);
		//modifyPossibleMoves(piece, posX, posY);
	
		vector<pair<int, int>> movesPos = piece.getPossibleMoves();
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
		for (int col = 0; col < BOARD_SIZE ; ++col) {
			for (int row = 0; row < 8; ++row) {
				if (buttons[row][col]->text() != "") {
					piecePositions.insert(make_pair(buttons[row][col]->text(), make_pair(row, col)));
				}
			}
		}
	}

	bool ChessBoard::isSquareOccupied(int x, int y) const {
		if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
			return false;
		}

		return piecePositions.find(buttons[y][x]->text()) != piecePositions.end();
	}

	void ChessBoard::modifyPossibleMoves(Piece& piece, int posX, int posY) {
		piece.clearPossibleMoves();
		Piece::Type pieceType = piece.getType();

		if (pieceType == Piece::Type::ROOK || pieceType == Piece::Type::KING || pieceType == Piece::Type::KNIGHT) {
			// Clear existing possibleMoves

			// Modify possibleMoves based on the presence of other pieces
			// Iterate over rows and columns to check for obstacles
			// Modify possibleMoves accordingly

			// For Rook
			if (pieceType == Piece::Type::ROOK) {
				// Modify possibleMoves for rook movement
				// Check horizontally and vertically for obstacles
				for (int x = posX + 1; x < BOARD_SIZE; ++x) {
					if (isSquareOccupied(x, posY)) {
						if (piece.getColor() != getCaseColor(x, posY)) {
							piece.addPossibleMove(x, posY); // Include the square with opposing piece
						}
						break; // Stop adding moves in this direction
					}
					piece.addPossibleMove(x, posY);
				}
				for (int x = posX - 1; x >= 0; --x) {
					if (isSquareOccupied(x, posY)) {
						if (piece.getColor() != getCaseColor(x, posY)) {
							piece.addPossibleMove(x, posY); // Include the square with opposing piece
						}
						break; // Stop adding moves in this direction
					}
					piece.addPossibleMove(x, posY);
				}
				for (int y = posY + 1; y < BOARD_SIZE; ++y) {
					if (isSquareOccupied(posX, y)) {
						if (piece.getColor() != getCaseColor(posX, y)) {
							piece.addPossibleMove(posX, y); // Include the square with opposing piece
						}
						break; // Stop adding moves in this direction
					}
					piece.addPossibleMove(posX, y);
				}
				for (int y = posY - 1; y >= 0; --y) {
					if (isSquareOccupied(posX, y)) {
						if (piece.getColor() != getCaseColor(posX, y)) {
							piece.addPossibleMove(posX, y); // Include the square with opposing piece
						}
						break; // Stop adding moves in this direction
					}
					piece.addPossibleMove(posX, y);
				}
			}

			// For King
			else if (pieceType == Piece::Type::KING) {
				// Modify possibleMoves for king movement
				// Check all adjacent squares for obstacles
				for (int dx = -1; dx <= 1; ++dx) {
					for (int dy = -1; dy <= 1; ++dy) {
						int newX = posX + dx;
						int newY = posY + dy;
						if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
							if (!isSquareOccupied(newX, newY)) {
								piece.addPossibleMove(newX, newY);
							}
							else if (piece.getColor() != getCaseColor(newX, newY)) {
								piece.addPossibleMove(newX, newY);
							}
						}
					}
				}
			}

			// For Knight
			else if (pieceType == Piece::Type::KNIGHT) {
				// Modify possibleMoves for knight movement
				// Knights can jump over other pieces, so no need to check for obstacles
				int knightMoves[8][2] = {
					{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
					{2, 1}, {2, -1}, {-2, 1}, {-2, -1}
				};

				for (const auto& move : knightMoves) {
					int newX = posX + move[0];
					int newY = posY + move[1];

					if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
						if (!isSquareOccupied(newX, newY)) {
							piece.addPossibleMove(newX, newY);
						}
						else if (piece.getColor() != getCaseColor(newX, newY)) {
							piece.addPossibleMove(newX, newY);
						}
					}
				}
			}
		}
	}

