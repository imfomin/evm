#pragma once

#include <iostream>
#include <fstream>

namespace rgr {

	class polynomial {
	private:
		struct Term {
			float coefficient;
			int power;
		};

		Term* Terms;
		int count_terms;

		void alloc(int _count_terms);
	public:

		/* ��������� P(x) = 0 � ��������� ������� �������� �� ���������� ���� count_terms = 0 ;
		������� ������ ���������� ��������� ������ ���� */

		polynomial() : Terms(nullptr), count_terms(0) {}
		polynomial(float number);
		polynomial(const polynomial& other);
		polynomial(polynomial&& other) noexcept;
		~polynomial() { clear(); }

		void clear();

		// ���������� ���������
		class Iterator {
		private:
			Term* ptr;
		public:
			friend class polynomial;
			Iterator(Term* _ptr = nullptr) : ptr(_ptr) {}
			Iterator(const Iterator&) = default;
			Iterator(Iterator&&) = default;
			~Iterator() = default;

			Term& operator*() const;
			bool operator==(const Iterator&) const;
			bool operator!=(const Iterator&) const;
			Iterator& operator++();
			Iterator operator++(int);
		};
		Iterator begin() const { return Iterator(Terms); }
		Iterator end() const { return Iterator(Terms + count_terms); }

		// ���������� ����������
		polynomial& operator =(const polynomial& other);
		polynomial& operator =(polynomial&& other) noexcept;

		// ���������� �������� ���������� ��� �������� x
		float operator ()(float x) const;

		// ���������� ����������� ��� �������� �������
		float operator [](int power) const;
		operator bool() const;

		polynomial operator +(const polynomial& added) const;
		polynomial operator -() const;
		polynomial operator -(const polynomial& subbed) const;
		polynomial operator *(const polynomial& multed) const;
		polynomial operator /(const polynomial& divisor) const;
		polynomial operator %(const polynomial& divisor) const;

		bool operator ==(const polynomial& polynomial) const;
		bool operator !=(const polynomial& polynomial) const;

		// ������� ����������
		int deg() const;

		// �����������
		polynomial derivative() const;

		/* ���� - �����
		* ������ �����-������: [�0 : a0 �1 : a1 �2 : a2 ...] */

		friend std::ostream& operator <<(std::ostream& stream, const polynomial& polynomial);
		friend std::istream& operator >>(std::istream& stream, polynomial& polynomial);
	};

};
