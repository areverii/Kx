#include "KRASKA_Types.h"

namespace KRASKA {

	class MatrixVisitor;
	class SwatchNode;
	class PatchNode;
	class EmptyNode;


	class MatrixCell {
	public:
		virtual ~MatrixCell() {}
		virtual void accept(MatrixVisitor* visitor) const = 0;
	};


	class MatrixVisitor {
	public:
		virtual void visitEmptyNode(const EmptyNode* node) const = 0;
		virtual void visitSwatchNode(const SwatchNode* node) const = 0;
		virtual void visitPatchNode(const PatchNode* node) const = 0;
	};

	class EmptyNode : public MatrixCell {
	public:
		virtual void accept(MatrixVisitor* visitor) const override {
			return visitor->visitEmptyNode(this);
		}

	};

	class SwatchNode : public MatrixCell {
	public:
		virtual void accept(MatrixVisitor* visitor) const override {
			return visitor->visitSwatchNode(this);
		}

		swatch& value() {
			return _value;
		}

	private:
		swatch _value;
	};


	class PatchNode : public MatrixCell {
	public:
		virtual void accept(MatrixVisitor* visitor) const override {
			return visitor->visitPatchNode(this);
		}

	};


}