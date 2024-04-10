#pragma once

#include "Rook.hpp"
   
    // Constructeur
    Rook::Rook(Color color) : Piece(Type::ROOK, color) {
        // Charge l'image de la tour selon sa couleur
        QString colorSuffix = (color == Color::WHITE) ? "White" : "Black";
        QString pieceName = "Rook-" + colorSuffix;
        if (pieceImages.contains(pieceName)) {
            setPieceImage(pieceImages[pieceName]);
        }
        else {
            // Handle image not found error
            qDebug() << "Image not found for piece: " << pieceName;
        }
}

