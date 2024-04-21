#pragma once

#include "Tour.hpp"

// Constructeur
Tour::Tour(Color color) : Piece(Type::ROOK, color) {
    // Charge l'image de la tour selon sa couleur 
    if (color == Color::WHITE) {
        setUnicode(U'\u2656');
    }
    else {
        setUnicode(U'\u265C');
    }
}

Tour::~Tour() {}

