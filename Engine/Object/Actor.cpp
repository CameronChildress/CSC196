#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace nc
{
	void nc::Actor::Load(std::istream& stream)
	{
		// stream >> into transform       
		stream >> m_transform;
		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);
	}

	bool Actor::Load(const std::string& filename) 
	{
		bool success = false;

		std::ifstream stream(filename);

		if (stream.is_open())            
		{           
			success = true;            
			Load(stream);            
			stream.close();           
		}           

		return success;   
	}

	void nc::Actor::Update(float dt)
	{
		//nothing
	}

	void nc::Actor::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}
}