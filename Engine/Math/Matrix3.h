#pragma once

#include "Vector2.h"

namespace nh
{
	struct Matrix33
	{
		float m[3][3]; //column, row

		Matrix33() : m{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f } {}

		void Scale(float s);
		void Scale(float sx, float sy);
		void Scale(Vector2 s);

		Vector2 GetScale() const;

		void Rotate(float a);
		float GetRotation() const;

		void Translate(const Vector2& v);
		Vector2 GetTranslation() const;

		void Identity();

		Matrix33 operator*(const Matrix33& mx) const;
		Vector2 operator*(const Vector2& v) const;
	};

	inline void Matrix33::Scale(float s)
	{
		m[0][0] = s;	m[1][0] = 0.0f;	m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = s; 	m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f;	m[2][2] = 1.0f;
	}
	inline void Matrix33::Scale(float sx, float sy)
	{
		m[0][0] = sx;	m[1][0] = 0.0f;	m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = sy; 	m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f;	m[2][2] = 1.0f;
	}
	inline void Matrix33::Scale(Vector2 s)
	{
		m[0][0] = s.x;	m[1][0] = 0.0f;	m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = s.y; 	m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f;	m[2][2] = 1.0f;
	}

	inline Vector2 Matrix33::GetScale() const
	{
		return { sqrt(m[0][0] * m[0][0] + m[1][0] * m[1][0]), sqrt(m[1][0] * m[1][0] + m[1][1] * m[1][1]) };
	}

	inline void Matrix33::Rotate(float a)
	{
		m[0][0] = std::cos(a);	m[1][0] = std::sin(a);	m[2][0] = 0.0f;
		m[0][1] = -std::sin(a); m[1][1] = std::cos(a); 	m[2][1] = 0.0f;
		m[0][2] = 0.0f;			m[1][2] = 0.0f;			m[2][2] = 1.0f;
	}

	inline float Matrix33::GetRotation() const
	{
		return std::atan2(m[1][0], m[0][0]);
	}

	inline void Matrix33::Translate(const Vector2& v)
	{
		m[0][0] = 1.0f;	m[1][0] = 0.0f;	m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
		m[0][2] = v.x;	m[1][2] = v.y;	m[2][2] = 1.0f;
	}

	inline Vector2 Matrix33::GetTranslation() const
	{
		return { m[0][2], m[1][2] };
	}

	inline void Matrix33::Identity()
	{
		m[0][0] = 1.0f;	m[1][0] = 0.0f;	m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
		m[0][2] = 0.0f;	m[1][2] = 0.0f;	m[2][2] = 1.0f;
	}

	inline Matrix33 Matrix33::operator*(const Matrix33& mx) const
	{
		Matrix33 r;

		r.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1] + m[2][0] * mx.m[0][2];
		r.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1] + m[2][0] * mx.m[1][2];
		r.m[2][0] = m[0][0] * mx.m[2][0] + m[1][0] * mx.m[2][1] + m[2][0] * mx.m[2][2];

		r.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1] + m[2][1] * mx.m[0][2];
		r.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1] + m[2][1] * mx.m[1][2];
		r.m[2][1] = m[0][1] * mx.m[2][0] + m[1][1] * mx.m[2][1] + m[2][1] * mx.m[2][2];

		r.m[0][2] = m[0][2] * mx.m[0][0] + m[1][2] * mx.m[0][1] + m[2][2] * mx.m[0][2];
		r.m[1][2] = m[0][2] * mx.m[1][0] + m[1][2] * mx.m[1][1] + m[2][2] * mx.m[1][2];
		r.m[2][2] = m[0][2] * mx.m[2][0] + m[1][2] * mx.m[2][1] + m[2][2] * mx.m[2][2];

		return r;
	}

	inline Vector2 Matrix33::operator*(const Vector2& v) const
	{
		Vector2 r;

		r[0] = v[0] * m[0][0] + v[1] * m[0][1] + m[0][2];
		r[1] = v[0] * m[1][0] + v[1] * m[1][1] + m[1][2];

		return r;
	}
}