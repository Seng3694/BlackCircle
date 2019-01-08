#include <SFML/Graphics.hpp>

#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML/imgui-SFML.h"

const float PI = static_cast<float>(M_PI);
const float PI_2 = static_cast<float>(M_PI * 2);
const float PI_3 = static_cast<float>(M_PI * 3);

void rainbow(float& r, float& g, float& b, float t)
{
	const float time = fmod(t, PI_3);

	if (time <= PI)
	{
		r = cos(time) + 1;
		g = -cos(time) + 1;
		b = 0;
	}
	else if (time <= PI_2)
	{
		r = 0;
		g = -cos(time) + 1;
		b = cos(time) + 1;
	}
	else if (time <= PI_3)
	{
		r = -cos(time) + 1;
		g = 0;
		b = cos(time) + 1;
	}

	r /= 2;
	g /= 2;
	b /= 2;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 600), "black circle", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(0, 0, 8));

	ImGui::SFML::Init(window);

	const unsigned int count = 1000;

	const float part = PI_2 / count;

	unsigned int i = 0, j = 0;
	sf::Vertex vertices[count];
	sf::Vertex verticesOuter[count];
	sf::Vertex drawArray[count * 2 + 2];

	for (i = 0; i < count; ++i)
	{
		vertices[i].color = sf::Color(0xffffffff);
		verticesOuter[i].color = sf::Color(0xffffffff);
	}

	/*the configurables*/
	float radius = 100;
	float amplitude = 30;
	float rotSpeed = 1.5;
	float thickness = 60;
	float waves = 7;
	float pulseSpeed = 3;
	float fps = 60;
	bool fpsCapped = false;
	bool fill = false;
	bool doRainbow = true;
	ImVec4 color;
	ImVec4 clearColor(0, 0, 0, 1);

	float mouseX = 400;
	float mouseY = 300;

	sf::Clock clock;
	sf::Clock clock2;
	float totalTime = 0;
	sf::Time dt;
	float r = 0;

	while (window.isOpen())
	{
		sf::Event e;

		while (window.pollEvent(e))
		{
			ImGui::SFML::ProcessEvent(e);

			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::MouseMoved)
			{
				/*mouseX = static_cast<float>(e.mouseMove.x);
				mouseY = static_cast<float>(e.mouseMove.y);*/
			}
		}

		totalTime = clock.getElapsedTime().asSeconds();
		dt = clock2.restart();

		for (i = 0; i < count; ++i)
		{
			r = amplitude * sin(totalTime * pulseSpeed) * sin(part * i * waves) + radius;
			vertices[i].position.x = (r - thickness / 2) * cos(part * i + totalTime * rotSpeed) + mouseX;
			vertices[i].position.y = (r - thickness / 2) * sin(part * i + totalTime * rotSpeed) + mouseY;
			verticesOuter[i].position.x = (r + thickness / 2) * cos(part * i + totalTime * rotSpeed) + mouseX;
			verticesOuter[i].position.y = (r + thickness / 2) * sin(part * i + totalTime * rotSpeed) + mouseY;

			if (doRainbow)
			{
				rainbow(color.x, color.y, color.z, totalTime);
				color.w = 1;
			}

			vertices[i].color.r = static_cast<sf::Uint8>(color.x * 255);
			vertices[i].color.g = static_cast<sf::Uint8>(color.y * 255);
			vertices[i].color.b = static_cast<sf::Uint8>(color.z * 255);
			vertices[i].color.a = static_cast<sf::Uint8>(color.w * 255);
			verticesOuter[i].color = vertices[i].color;
		}


		ImGui::SFML::Update(window, dt);
		fps = 1 / dt.asSeconds();

		ImGui::SetNextWindowPos(ImVec2(900, 10));
		ImGui::SetNextWindowSize(ImVec2(290, 580));

		if (ImGui::Begin("Configuration", (bool*)0, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_::ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_::ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings))
		{
			
			ImGui::Text("FPS %.0f", ceil(fps));
			if (ImGui::Checkbox("FPS capped", &fpsCapped))
			{
				if (fpsCapped)
					window.setFramerateLimit(60);
				else
					window.setFramerateLimit(0);
			}
			ImGui::InputFloat("radius", &radius, 1, 5, 2);
			ImGui::InputFloat("amplitude", &amplitude, 1, 5, 2);
			ImGui::InputFloat("rotSpeed", &rotSpeed, 0.01f, 0.1f, 2);
			ImGui::InputFloat("thickness", &thickness, 1, 5, 2);
			ImGui::InputFloat("waves", &waves, 1, 5, 2);
			ImGui::InputFloat("pulseSpeed", &pulseSpeed, 0.01f, 0.1f, 2);
			ImGui::Checkbox("fill", &fill);
			ImGui::Checkbox("rainbow", &doRainbow);

			if (!doRainbow)
			{
				ImGui::ColorEdit4("color", &color.x);
			}

			ImGui::ColorEdit4("clear color", &clearColor.x);

			ImGui::End();
		}


		window.clear(clearColor);

		if (fill)
		{
			for (i = 0, j = 0; i < count; ++i, j += 2)
			{
				drawArray[j] = vertices[i];
				drawArray[j + 1] = verticesOuter[i];
			}

			drawArray[count * 2] = vertices[0];
			drawArray[count * 2 + 1] = verticesOuter[0];

			window.draw(drawArray, count * 2 + 2, sf::PrimitiveType::TriangleStrip);
		}
		else
		{
			window.draw(vertices, count, sf::PrimitiveType::LineStrip);
			window.draw(verticesOuter, count, sf::PrimitiveType::LineStrip);
		}

		ImGui::SFML::Render(window);
		window.display();
	}

	return 0;
}