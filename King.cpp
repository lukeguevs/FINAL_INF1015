#pragma once

#include "King.hpp"

// Constructeur


King::King(Color color) : Piece(Type::KING, color) {
    if (compteurRoi >= 2) {
        throw std::runtime_error("There is already two kings");
    }
    compteurRoi++;

    if (color == Color::WHITE) {
        setUnicode(U'\u2654');
    }
    else {
        setUnicode(U'\u265A');
    }
}

King::~King() {}

