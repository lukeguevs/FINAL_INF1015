//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include "Piece.hpp"

using namespace chess;

class Tour : public Piece {
public:

	Tour(Color color);
	~Tour();
	//std::vector<std::pair<int, int>> getPossibleMoves(int positionY, int positionX) const override;
};