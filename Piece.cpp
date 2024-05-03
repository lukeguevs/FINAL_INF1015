//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//�cole Polytechnique de Montr�al
//Projet Final de INF1015


#pragma once
#include "Piece.hpp"


	Piece::~Piece() {}
	Piece::Piece(Type type, Color color) {
		setColor(color);
		setType(type);
	}
	void Piece::setUnicode(char32_t newUnicode) {
		unicode = newUnicode;
	}
	void Piece::setColor(Color newColor) {
		color = newColor;
	}
	void Piece::setType(Type newType) {
		type = newType;
	}
	Piece::Type Piece::getType() const {
		return type;
	}
	char32_t Piece::getUnicode() const {
		return unicode;
	}
	Piece::Color Piece::getColor() const {
		return color;
	}
    vector<pair<int, int>> Piece::getPossibleMoves(ChessBoard* chessboard, int positionX, int positionY, Type pieceType) const {
        vector<pair<int, int>> moves;

        if (pieceType == Type::KING) {
            moves = { { positionY + 1,positionX + 0 },
                      { positionY + -1, positionX + 0 },
                      { positionY + 0, positionX + 1 },
                      { positionY + 0, positionX + -1 },
                      { positionY + 1,positionX + 1 },
                      { positionY + 1,positionX + -1 },
                      { positionY + -1,positionX + 1 },
                      { positionY + -1,positionX + -1 }
            };
        }
        else if (pieceType == Type::ROOK) {
            for (int x = positionY + 1; x < 8; ++x) {
                // Check if the path is blocked before adding the move
                if (chessboard->isPathBlocked(positionY, positionX, x, positionX)) {
                    continue;
                }
                moves.push_back({ x, positionX });
            }
            for (int x = positionY - 1; x >= 0; --x) {
                if (chessboard->isPathBlocked(positionY, positionX, x, positionX)) {
                    continue;
                }
                moves.push_back({ x, positionX });
            }
            for (int y = positionX + 1; y < 8; ++y) {
                if (chessboard->isPathBlocked(positionY, positionX, positionY, y)) {
                    continue;
                }
                moves.push_back({ positionY, y });
            }
            for (int y = positionX - 1; y >= 0; --y) {
                if (chessboard->isPathBlocked(positionY, positionX, positionY, y)) {
                    continue;
                }
                moves.push_back({ positionY, y });
            }
        }
        else if (pieceType == Type::KNIGHT) {
            int knightMoves[8][2] = {
              {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
              {2, 1}, {2, -1}, {-2, 1}, {-2, -1}
            };

            for (const auto& move : knightMoves) {
                int newY = positionY + move[0];
                int newX = positionX + move[1];


                if (newY >= 0 && newY < 8 && newX >= 0 && newX < 8) {
                    moves.push_back({ newY, newX });
                }
            }
        }

        return moves;
    }

