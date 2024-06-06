
#include "pch.h"
#include "opengl_rendererAPI.h"

#include <glad/glad.h>

namespace prime {

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glLineWidth(2.0f);
		glEnable(GL_LINE_SMOOTH);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRendererAPI::Submit(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SubmitLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		glDrawArrays(GL_LINES, 0, vertexCount);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}
}