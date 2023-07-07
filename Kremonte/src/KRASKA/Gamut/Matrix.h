#pragma once

//#include "KRASKA.h"
#include "Kremonte/krpch.h"
#include "MatrixCell.h"

#include <list>

namespace KRASKA {

	// matrix of cells
	// each cell is either a thread or a patch or an empty space
	// thread:: array of x pixels (for gradients)
	// patch:: has an input and output, as well as an ID that must be assigned to a deck (stack of cards) before execution

	class Matrix {

	public:

		Matrix();
		~Matrix();

		bool Expand(MatrixCell* cell);


	private:
		std::vector<std::list<const MatrixCell*>> _matrix;
	};

}