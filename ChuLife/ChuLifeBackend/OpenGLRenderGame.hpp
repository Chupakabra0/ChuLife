#pragma once
#include <memory>

#include "IRenderGame.hpp"
#include "GLFW/glfw3.h"
#include "glad.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct MVPMatrices {
public:
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

class OpenGLWindow {
public:
	OpenGLWindow() = default;

	~OpenGLWindow() = default;

private:

};

class OpenGLRenderer {
public:
	OpenGLRenderer() = delete;

	explicit OpenGLRenderer(const MVPMatrices& mvp)
		: mvp_(mvp) {

	}

	~OpenGLRenderer() = default;

	void ClearDisplay(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void SetViewport(const glm::vec2& viewportStart, const glm::vec2& viewportSize) {
		glViewport(viewportStart.x, viewportStart.y, viewportSize.x, viewportSize.y);
	}

	const glm::mat4& GetModelMatrix() const {
		return this->mvp_.modelMatrix;
	}

	void SetModelMatrix(const glm::mat4& modelMatrix) {
		this->mvp_.modelMatrix = modelMatrix;
	}

	const glm::mat4& GetViewMatrix() const {
		return this->mvp_.viewMatrix;
	}

	void SetViewMatrix(const glm::mat4& viewMatrix) {
		this->mvp_.viewMatrix = viewMatrix;
	}

	const glm::mat4& GetProjectionMatrix() const {
		return this->mvp_.projectionMatrix;
	}

	void SetProjectionMatrix(const glm::mat4& projectionMatrix) {
		this->mvp_.projectionMatrix = projectionMatrix;
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(this->mvp_.projectionMatrix));
	}

private:
	MVPMatrices mvp_;
};

class OpenGLRenderGame : public IRenderGame {
public:
	OpenGLRenderGame() = delete;

	explicit OpenGLRenderGame(OpenGLWindow* window, OpenGLRenderer* renderer)
		: window_(window), renderer_(renderer) {

	}

	~OpenGLRenderGame() override = default;

	void RenderGame(const GameField& gameField) override {

	}

private:
	std::unique_ptr<OpenGLWindow> window_;
	std::unique_ptr<OpenGLRenderer> renderer_;
};
