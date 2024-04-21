//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once
#include <iostream>
#include "Piece.hpp"

namespace chess {

	Piece::Piece(Type type, Color color) {
		setColor(color);
		setType(type);
	}
	void Piece::setUnicode(char32_t newUnicode) {
		unicode = newUnicode;
	}
	void Piece::setPosition(int newPositionX, int newPositionY) {
		if ((newPositionX < 8) && (newPositionY < 8)) {
			posX = newPositionX;
			posY = newPositionY;
		}
	}
	void Piece::setColor(Color newColor) {
		color = newColor;
	}
	void Piece::setType(Type newType) {
		type = newType;
	}
	void Piece::setPossibleMoves(std::vector<std::pair<int, int>> newPossibleMoves) {
		possibleMoves = newPossibleMoves;
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
	int Piece::getPositionX() const {
		return posX;
	}
	int Piece::getPositionY() const {
		return posY;
	}
	std::vector<std::pair<int, int>> Piece::getPossibleMoves(int positionX, int positionY, Type pieceType) const {
		std::vector<std::pair<int, int>>  moves;

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
				moves.push_back({ x, positionX });
			}
			for (int x = positionY - 1; x >= 0; --x) {
				moves.push_back({ x, positionX });
			}
			for (int y = positionX + 1; y < 8; ++y) {
				moves.push_back({ positionY, y });
			}
			for (int y = positionX - 1; y >= 0; --y) {
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
}
