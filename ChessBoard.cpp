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
		Tour blackRook(Piece::Color::BLACK);

		try {
			King roi1(Piece::Color::WHITE);
			addPieceSlot(roi1, 4, 6);
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Erreur : " << e.what() << std::endl;
		}
		addPieceSlot(blackKnight, 3, 5);
		addPieceSlot(whiteRook, 6, 5);
		addPieceSlot(blackRook, 6, 4);
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
		piece.setPosition(posX, posY);
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

				displayAndMove(piece);
			}
			});
	}


	void ChessBoard::displayAndMove(Piece piece) {
		piecesBoard.clear();
		findPieces();
		int posX = piece.getPosition().first;
		int posY = piece.getPosition().second;
		isDisplay_ = true;
		Piece::Type pieceType = piece.getType();
		Piece::Color color = piece.getColor();

		piece.setPossibleMoves(posX, posY, pieceType);
		modifyPossibleMoves(piece);
	
		QString texteBouton;

		for (const auto& moves : piece.getPossibleMoves()) {
			texteBouton = buttons[moves.first][moves.second]->text();
			if (texteBouton == "") {
				buttons[moves.first][moves.second]->setStyleSheet("color: green;");
				buttons[moves.first][moves.second]->setText("*");
				connect(buttons[moves.first][moves.second], &QPushButton::clicked, this, [=]() {
					for (auto moves2 : piece.getPossibleMoves()) {
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
						for (auto moves2 : piece.getPossibleMoves()) {
							QString texteBouton2 = buttons[moves2.first][moves2.second]->text();
							if (texteBouton2 == "*") {
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
			for (auto moves : piece.getPossibleMoves()) {
				QString texteBouton3 = buttons[moves.first][moves.second]->text();
				if (texteBouton3 == "*") {
					disconnect(buttons[moves.first][moves.second], &QPushButton::clicked, this, nullptr);
					buttons[moves.first][moves.second]->setText("");
				}
			}
			addPieceSlot(piece, posX, posY);
			});
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
		piecesBoard.clear();
		for (int row = 0; row < BOARD_SIZE; row++) {
			for (int col = 0; col < BOARD_SIZE; col++) {
				QString pieceCase = buttons[row][col]->text();
				if (!pieceCase.isEmpty()) {
					Piece::Type pieceType;
					Piece::Color pieceColor;
					if (pieceCase == QString::fromUcs4(U"\u265E")) { // ♘ (black knight)
						pieceType = Piece::Type::KNIGHT;
					}
					else if (pieceCase == QString::fromUcs4(U"\u2658")) { // ♘ (white knight)
						pieceType = Piece::Type::KNIGHT;
					}
					else if (pieceCase == QString::fromUcs4(U"\u265C")) { // ♜ (black rook)
						pieceType = Piece::Type::ROOK;
					}
					else if (pieceCase == QString::fromUcs4(U"\u2656")) { // ♜ (white rook)
						pieceType = Piece::Type::ROOK;
					}
					else if (pieceCase == QString::fromUcs4(U"\u265A")) { // ♚ (black king)
						pieceType = Piece::Type::KING;
					}
					else if (pieceCase == QString::fromUcs4(U"\u2654")) { // ♚ (white king)
						pieceType = Piece::Type::KING;
					}
					else {
						continue;
					}
					if (getCaseColor(row, col) == Piece::Color::WHITE) {
						pieceColor = Piece::Color::WHITE;
					}
					else {
						pieceColor = Piece::Color::BLACK;
					}
					Piece piece(pieceType, pieceColor);
					piece.setPosition(row, col);
					piecesBoard.push_back(piece);
				}
			}
		}
	}

	void ChessBoard::modifyPossibleMoves(Piece& piece) {
		if (piece.getType() != Piece::Type::ROOK) {
			return;
		}
		bool isBlocked;
		piece.clearPossibleMoves();

		int positionY = piece.getPosition().first;
		int positionX = piece.getPosition().second;

		// Check squares to the right of the rook
		for (int y = positionY + 1; y < 8; ++y) {
			isBlocked = false;
			for (const auto& pos : piecesBoard) {
				int posX, posY;
				tie(posX, posY) = pos.getPosition();
				if (posX == positionX && posY == y) {
					if (piece.getColor() != pos.getColor()) { // Opponent's piece, include this square
						piece.addPossibleMove(positionX, y);
						isBlocked = true;
						break;
					}
					isBlocked = true;
					break;
				}
			}
			if (isBlocked) break;
			piece.addPossibleMove(positionX, y);
		}

		// Check squares to the left of the rook
		for (int y = positionY - 1; y >= 0; --y) {
			isBlocked = false;
			for (const auto& pos : piecesBoard) {
				int posX, posY;
				tie(posX, posY) = pos.getPosition();
				if (posX == positionX && posY == y) {
					if (piece.getColor() != pos.getColor()) { // Opponent's piece, include this square
						piece.addPossibleMove(positionX, y);
						isBlocked = true;
						break;
					}
					isBlocked = true;
					break;
				}
			}
			if (isBlocked) break;
			piece.addPossibleMove(positionX, y);
		}

		// Check squares above the rook
		for (int x = positionX + 1; x < 8; ++x) {
			isBlocked = false;
			for (const auto& pos : piecesBoard) {
				int posX, posY;
				tie(posX, posY) = pos.getPosition();
				if (posX == x && posY == positionY) {
					if (piece.getColor() != pos.getColor()) { // Opponent's piece, include this square
						piece.addPossibleMove(x, positionY);
						isBlocked = true;
						break;
					}
					isBlocked = true;
					break;
				}
			}
			if (isBlocked) break;
			piece.addPossibleMove(x, positionY);
		}

		// Check squares below the rook
		for (int x = positionX - 1; x >= 0; --x) {
			isBlocked = false;
			for (const auto& pos : piecesBoard) {
				int posX, posY;
				tie(posX, posY) = pos.getPosition();
				if (posX == x && posY == positionY) {
					if (piece.getColor() != pos.getColor()) { // Opponent's piece, include this square
						piece.addPossibleMove(x, positionY);
						isBlocked = true;
						break;
					}
					isBlocked = true;
					break;
				}
			}
			if (isBlocked) break;
			piece.addPossibleMove(x, positionY);
		}
	}


	bool ChessBoard::isCheck(Piece king) {
		if (king.getType() != Piece::Type::KING) {
			return;
		}
		king.clearPossibleMoves();
		int posX = king.getPosition().first;
		int posY = king.getPosition().second;

		for (auto& pieces : piecesBoard) {
			modifyPossibleMoves(pieces);
			if (pieces.getColor() != king.getColor()) {
				std::find(pieces.getPossibleMoves().begin(), pieces.getPossibleMoves().end(), make_pair(posX, posY));
			}
		}
	}

