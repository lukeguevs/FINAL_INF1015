//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once

#include "Piece.hpp"

namespace chess {

	Piece::Type Piece::getType() const {
		return type;
	}

	Piece::Color Piece::getColor() const {
		return color;
	}
}
