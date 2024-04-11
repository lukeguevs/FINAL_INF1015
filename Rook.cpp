#pragma once

#include "Rook.hpp"
   
    // Constructeur
Rook::Rook(Color color) : Piece(Type::ROOK, color, (color == Color::WHITE) ? "\u2656" : "\u265C") {}

Rook::~Rook() {}

QString Rook::getSymbol() const override {
    return symbol;
}