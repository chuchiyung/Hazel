#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
	
namespace Hazel {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
		{
			if (Input::GetMouseX() >= 0 && Input::GetMouseY() >= 0)
			{
				bool flag = false;
				float startPosX, startPosY, endPosX, endPosY;
				//HZ_WARN("Mouse {0} and {1}", Input::GetMouseX(), Input::GetMouseY());
				if (!flag)
				{
					startPosX = Input::GetMouseX();
					startPosY = Input::GetMouseY();
					endPosX = startPosX;
					endPosY = startPosY;
					flag = true;
					HZ_WARN("1:Start {0} {1}", startPosX, startPosY);
					HZ_WARN("1:End   {0} {1}", endPosX, endPosY);
				}
				if (flag)
				{
					endPosX = Input::GetMouseX();
					endPosY = Input::GetMouseY();
					flag = false;
					HZ_WARN("2:Start {0} {1}", startPosX, startPosY);
					HZ_WARN("2:End   {0} {1}", endPosX, endPosY);
				}
				if (endPosX > startPosX)
				{
					m_CameraPosition.x -= 5.0f * ts;
				}
				if (endPosX < startPosX)
				{
					m_CameraPosition.x += 5.0f * ts;
				}
				if (endPosY > startPosY)
				{
					m_CameraPosition.y += 5.0f * ts;
				}
				if (endPosY < startPosY)
				{
					m_CameraPosition.y -= 5.0f * ts;
				}
				
				
			}
			

		}
			

		if (Input::IsKeyPressed(Key::A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(Key::W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(Key::S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(Key::Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(Key::E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}