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
			
			displayPossibleMoves(piece, posX, posY);
			});
	}

	
    void ChessBoard::displayPossibleMoves(const Piece& piece, int posX, int posY ) {
        Piece::Type pieceType = piece.getType();
        
        std::vector<std::pair<int, int>> movesPos = piece.getPossibleMoves(posX,posY,pieceType);
    
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
					addPieceSlot(piece, moves.second, moves.first);

					});
			}
			else {
				
				disconnect(buttons[moves.first][moves.second], &QPushButton::clicked, this, nullptr);
				connect(buttons[moves.first][moves.second], &QPushButton::clicked, this, [=]() {
					
					for (const auto& moves2 : movesPos) {
						
							buttons[moves2.first][moves2.second]->setText("");
							delete buttons[moves2.first][moves2.second];
							buttons[moves2.first][moves2.second] = nullptr;
						
					}
					
					buttons[posY][posX]->setText("");
					delete buttons[posY][posX];
					buttons[posY][posX] = nullptr;
					addPieceSlot(piece, moves.second, moves.first);

					});
			}
			
		}
	}
}