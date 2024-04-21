#pragma once

#include "Knight.hpp"

// Constructeur
Knight::Knight(Color color) : Piece(Type::KNIGHT, color) {
    // Charge l'image de la tour selon sa couleur 
    if (color == Color::WHITE) {
        setUnicode(U'\u2658');
    }
    else {
        setUnicode(U'\u265E');
    }
}

Knight::~Knight() {}


