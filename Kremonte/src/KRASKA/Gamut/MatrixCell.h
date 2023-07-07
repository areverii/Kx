#pragma once

#include "KRASKA_Types.h"
#include <any>
#include <typeindex>

namespace KRASKA {

	class MatrixVisitor;
	class SwatchNode;
	class PatchNode;
	class EmptyNode;

	class MatrixCell {
	public:
		virtual ~MatrixCell() {}
		virtual std::any accept(MatrixVisitor* visitor) const = 0;
		//virtual void accept(MatrixVisitor* visitor) const = 0;
	};

	class MatrixVisitor {
	public:
		/* Each must be overridden when creating a visitor */
		virtual std::any visitEmptyNode(const EmptyNode* node) const = 0;
		virtual std::any visitSwatchNode(const SwatchNode* node) const = 0;
		virtual std::any visitPatchNode(const PatchNode* node) const = 0;
		//virtual std::any visit(const MatrixCell* node) const = 0;

	};

	class EmptyNode : public MatrixCell {
	public:
		EmptyNode() {}

		virtual std::any accept(MatrixVisitor* visitor) const override {
			return visitor->visitEmptyNode(this);
		}

	};

	class SwatchNode : public MatrixCell {
	public:
		SwatchNode(swatch value) : _value(value) { };

		virtual std::any accept(MatrixVisitor* visitor) const override {
			return visitor->visitSwatchNode(this);
		}

		swatch value() const {
			return _value;
		}

	private:
		swatch _value;
	};


	class PatchNode : public MatrixCell {
	public:
		virtual std::any accept(MatrixVisitor* visitor) const override {
			return visitor->visitPatchNode(this);
		}

		patch value() const {
			return _value;
		}

	private:
		patch _value;

	};

	/* VISITING ALGORITHMS */

	class Visitor_GetNode : public MatrixVisitor {
	public:

		std::any visitEmptyNode(const EmptyNode* node) const override {
			return node;
		}

		std::any visitSwatchNode(const SwatchNode* node) const override {
			return node;
		}

		std::any visitPatchNode(const PatchNode* node) const override {
			return node;
		}
	};

	class Visitor_GetValue : public MatrixVisitor {
	public:

		std::any visitEmptyNode(const EmptyNode* node) const override {
			KR_CORE_INFO("KRASKA: Tried to get value of EmptyNode");
			return swatch{ .channel = channel::Kx, .value = BTER9_C_0 };
		}

		std::any visitSwatchNode(const SwatchNode* node) const override {
			return node->value();
		}

		std::any visitPatchNode(const PatchNode* node) const override {
			return node->value();
		}

	};

	/*template<typename VisitorImpl, typename VisitablePtr, typename ResultType>
	class ValueGetter
	{
	public:
		static ResultType GetValue(VisitablePtr ptr)
		{
			VisitorImpl visitor;
			ptr->accept(visitor); // this call fills the return value
			return visitor._value;
		}

		void Return(ResultType value_)
		{
			_value = value_;
		}
	private:
		ResultType _value;
	};*/

	/* Visitor_Value
	A visitor class that returns the value of each node type
	*/
	/*class Visitor_GetValue : public ValueGetter<Visitor_GetValue, MatrixCell*, swatch>, public MatrixVisitor {
	public:

		void visitEmptyNode(const EmptyNode* node) const override {
			KR_INFO("hello empty node");
		}

		void visitSwatchNode(const SwatchNode* node) const override {
			KR_INFO("hello swatch node");
			Return(node->value());
		}

		void visitPatchNode(const PatchNode* node) const override {
			KR_INFO("hello patch node");
		}
	};*/


}