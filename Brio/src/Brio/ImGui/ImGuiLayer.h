#pragma once

#include "Brio/Core/Layer.h"
#include "Brio/Events/ApplicationEvent.h"
#include "Brio/Events/KeyEvent.h"
#include "Brio/Events/MouseEvent.h"

namespace Brio
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}