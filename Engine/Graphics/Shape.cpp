#include "pch.h"
#include "Shape.h"
#include "Math/Matrix33.h"
#include <fstream>

bool nc::Shape::Load(const std::string& filename)
{
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open())
	{
		success = true;

		//read color
		stream >> m_color;
		
		//get number of points
		size_t size;
		std::string line;
		std::getline(stream, line);
		size = stoi(line);

		//read points
		for (size_t i = 0; i < size; i++)
		{
			Vector2 v;
			stream >> v;
			m_points.push_back(v);
		}

		stream.close();
	}

	//get radius
	m_radius = 0;
	for (size_t i = 0; i < m_points.size(); i++)
	{
		nc::Vector2 p1 = m_points[i];

		float length = p1.Length();
		if (length > m_radius) m_radius = length;
	}

	return success;
}

void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle)
{
	//Graphics set color
	graphics.SetColor(m_color);

	Matrix33 mxScale;
	mxScale.Scale(scale);

	Matrix33 mxRotate;
	mxRotate.Rotate(angle);

	Matrix33 mxTranslate;
	mxTranslate.Translate(position);

	Matrix33 mx;
	mx = mxScale * mxRotate * mxTranslate;


	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		// local / object space points
		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		// transform points 
		//scale & rotate
		p1 = p1 * mx;
		p2 = p2 * mx;

		// draw points
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void nc::Shape::Draw(Core::Graphics& graphics, const Transform& transform)
{
	graphics.SetColor(m_color);

	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		// local / object space points
		nc::Vector2 p1 = m_points[i];
		nc::Vector2 p2 = m_points[i + 1];

		// transform points 
		//scale & rotate & translate
		p1 = p1 * transform.matrix;
		p2 = p2 * transform.matrix;

		// draw points
		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}
