//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once

#include "Piece.hpp"

namespace chess {

	Piece::Piece(Type type, Color color) {
        // Load piece images
        QDir dir(":/images/Chess/");
        QStringList filters;
        filters << "*.png";
        dir.setNameFilters(filters);
        QStringList pieceFiles = dir.entryList();

        for (const QString& file : pieceFiles) {
            QString pieceName = file.left(file.lastIndexOf("."));
            QPixmap pieceImage(":/images/Chess/" + file);
            pieceImages[pieceName] = pieceImage;
        }

	}

   void Piece::setPieceImage(const QPixmap& image) {
        pieceImage = image;
    }

	Piece::Type Piece::getType() const {
		return type;
	}

	Piece::Color Piece::getColor() const {
		return color;
	}
}
