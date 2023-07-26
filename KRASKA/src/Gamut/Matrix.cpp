#include "Matrix.h"

namespace KRASKA {

	/* Matrix
	Constructs a Matrix with the 3 default nodes, C M Y, emplaced.
	Each node is loaded with a patch containing the value Cx0, Mx0, and Yx0
	respectively. */
	Matrix::Matrix() {
		std::list<const MatrixCell*> thread_C{ };
		std::list<const MatrixCell*> thread_M{ };
		std::list<const MatrixCell*> thread_Y{ };
		thread_C.push_back(new SwatchNode(swatch{ .channel = channel::Cx, .value = BTER9_C_0 }));
		thread_M.push_back(new SwatchNode(swatch{ .channel = channel::Mx, .value = BTER9_C_0 }));
		thread_Y.push_back(new SwatchNode(swatch{ .channel = channel::Yx, .value = BTER9_C_0 }));
		_matrix.push_back(thread_C);
		_matrix.push_back(thread_M);
		_matrix.push_back(thread_Y);
	}

	Matrix::~Matrix() {
		/*Visitor_GetNode* visitor_GetNode = new Visitor_GetNode;

		for (std::list<const MatrixCell*> thread : _matrix) {
			delete std::any_cast<MatrixCell*>(thread.back()->accept(visitor_GetNode));
			//delete thread.back()->accept(visitor);
		}

		delete visitor_GetNode;*/
	}

	/* Expand
	* Input: MatrixCell* with a channel matching the target thread
	* Output: True if node was added, false otherwise (e.g no matching thread channel)
	*/
	bool Matrix::Expand(MatrixCell* cell) {

		//Visitor_GetNode* visitor_GetNode = new Visitor_GetNode;
		Visitor_GetValue* visitor_GetValue = new Visitor_GetValue;
		swatch cellSwatch = std::any_cast<swatch>(cell->accept(visitor_GetValue));

		for (std::list<const MatrixCell*> thread : _matrix) {

			//if (std::any_cast<MatrixCell*>(thread.back()->accept(visitor_GetNode)).type() == typeid(SwatchNode)) {
			//KR_CORE_INFO("type: {0}", typeid(thread.back()->accept(visitor_GetNode)).name);

			//if (thread.back()->accept(visitor_GetNode).type() == typeid(SwatchNode)) {
			//	KR_CORE_INFO("node is of type Swatch");
			//}

			/* This cast will always succeed because we ensure that each thread has a swatch node pushed
			at its head. We always check against the head node to get the channel of the thread. */
			if (std::any_cast<swatch>(thread.front()->accept(visitor_GetValue)).channel == cellSwatch.channel) {
				thread.push_back(cell);
				delete visitor_GetValue;
				return true;
			}
		}
		delete visitor_GetValue;
		return false;
	}
}
