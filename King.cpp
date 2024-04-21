#pragma once

#include "King.hpp"

// Constructeur


King::King(Color color) : Piece(Type::KING, color) {
    // Charge l'image de la tour selon sa couleur 
    if (color == Color::WHITE) {
        setUnicode(U'\u2654');
    }
    else {
        setUnicode(U'\u265A');
    }
}

King::~King() {}

