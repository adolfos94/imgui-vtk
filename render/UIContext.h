#pragma once

#include <pch.h>
#include "IRenderContext.hpp"

namespace render
{
	class UIContext : public IRenderContext
	{
	public:

		// Inherited via IRenderContext
		virtual bool init(window::IWindow* window) override;
		virtual void pre_render() override;
		virtual void post_render() override;
		virtual void end() override;

	private:

	};
}