#pragma once
#include <memory>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include "IRenderGame.hpp"
#include "Glad.hpp"
#include "Utils.hpp"

class Vertex {
public:
	explicit Vertex(const glm::vec4& position,
		const glm::vec4& normal = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		const glm::vec4& color  = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f))
		: position_(position), normal_(normal), color_(color) {

	}

	Vertex(const Vertex& copy)
		: Vertex(copy.position_, copy.normal_, copy.color_) {

	}

	Vertex(Vertex&& move) noexcept {
		std::swap(this->position_, move.position_);
		std::swap(this->normal_, move.normal_);
		std::swap(this->color_, move.color_);
	}

	Vertex& operator=(const Vertex& copy) {
		this->position_ = copy.position_;
		this->normal_   = copy.normal_;
		this->color_    = copy.color_;

		return *this;
	}

	Vertex& operator=(Vertex&& move) noexcept {
		std::swap(this->position_, move.position_);
		std::swap(this->normal_, move.normal_);
		std::swap(this->color_, move.color_);

		return *this;
	}

	const glm::vec4& GetPosition() const {
		return this->position_;
	}

	void SetPosition(const glm::vec4& position) {
		this->position_ = position;
	}

	const glm::vec4& GetNormal() const {
		return this->normal_;
	}

	void SetNormal(const glm::vec4& normal) {
		this->normal_ = normal;
	}

	const glm::vec4& GetColor() const {
		return this->color_;
	}

	void SetColor(const glm::vec4& color) {
		this->color_ = color;
	}

	friend bool operator==(const Vertex& first, const Vertex& second) {
		return isVec4Equal(first.position_, second.position_) &&
			isVec4Equal(first.normal_, second.normal_) &&
			isVec4Equal(first.color_, second.color_);
	}

	friend bool operator!=(const Vertex& first, const Vertex& second) {
		return !(first == second);
	}

private:
	glm::vec4 position_;
	glm::vec4 normal_;
	glm::vec4 color_;
};

struct MVPMatrices {
public:
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

struct DestroyGLFWWindow {
	void operator()(GLFWwindow* ptr) {
		glfwDestroyWindow(ptr);
	}

};

using UniqueGLFWWindowPtr = std::unique_ptr<GLFWwindow, DestroyGLFWWindow>;

class OpenGLWindow {
public:
	OpenGLWindow() = delete;

	explicit OpenGLWindow(int width, int height, const std::string& title)
		: width_(width), height_(height), title_(title) {
		this->windowHandle_ = UniqueGLFWWindowPtr(
			glfwCreateWindow(this->width_, this->height_, this->title_.c_str(), nullptr, nullptr)
		);

		if (this->windowHandle_ == nullptr) {
			throw std::runtime_error("Creating window error");
		}

		glfwMakeContextCurrent(this->windowHandle_.get());
		glfwSetInputMode(this->windowHandle_.get(), GLFW_STICKY_KEYS, GL_TRUE);

		this->InitGLAD_();
		this->InitCallbacks_();
	}

	OpenGLWindow(const OpenGLWindow& copy) = delete;

	OpenGLWindow(OpenGLWindow&& move) noexcept {
		std::swap(this->width_, move.width_);
		std::swap(this->height_, move.height_);
		std::swap(this->title_, move.title_);
	}

	~OpenGLWindow() {
		this->CleanAll_();
	}

	OpenGLWindow& operator=(const OpenGLWindow& copy) = delete;

	OpenGLWindow& operator=(OpenGLWindow&& move) noexcept {
		this->CleanAll_();

		std::swap(this->width_, move.width_);
		std::swap(this->height_, move.height_);
		std::swap(this->title_, move.title_);

		return *this;
	}

	int GetWidth() const {
		return this->width_;
	}

	int GetHeight() const {
		return this->height_;
	}

	const std::string& GetTitle() const {
		return this->title_;
	}

	void SetTitle(const std::string& title) {
		this->title_ = title;
	}

	const UniqueGLFWWindowPtr& GetUniqueHandle() const {
		return this->windowHandle_;
	}

private:
	UniqueGLFWWindowPtr windowHandle_;
	int width_;
	int height_;
	std::string title_;

	void InitGLAD_() {
		static bool initGLAD = false;

		if (!initGLAD) {
			if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
				throw std::runtime_error("Initializing GLAD error");
			}

			initGLAD = true;
		}
	}

	void InitCallbacks_() {
		glfwSetWindowUserPointer(this->windowHandle_.get(), this);
	}

	void CleanAll_() {
		glfwDestroyWindow(this->windowHandle_.get());

		this->windowHandle_.reset();
		this->title_.clear();

		this->width_  = 0;
		this->height_ = 0;
	}
};

class OpenGLRenderer {
public:
	OpenGLRenderer() = delete;

	explicit OpenGLRenderer(const MVPMatrices& mvp)
		: mvp_(mvp) {
		this->glfwInit_();
	}

	~OpenGLRenderer() {
		this->TerminateGLFW_();
	}

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
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(this->mvp_.viewMatrix));
	}

	const glm::mat4& GetProjectionMatrix() const {
		return this->mvp_.projectionMatrix;
	}

	void SetProjectionMatrix(const glm::mat4& projectionMatrix) {
		this->mvp_.projectionMatrix = projectionMatrix;
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(this->mvp_.projectionMatrix));
	}

	void RenderLines(const std::vector<Vertex>& vertices) {
		glBegin(GL_LINES);
		{
			for (const Vertex& v : vertices) {
				const Vertex curr = Vertex(
					this->mvp_.modelMatrix * v.GetPosition(),
					v.GetNormal(),
					v.GetColor()
				);

				glNormal3f(curr.GetNormal().x, curr.GetNormal().y, curr.GetNormal().z);
				glColor4f(curr.GetColor().r, curr.GetColor().g, curr.GetColor().b, curr.GetColor().a);
				glVertex4f(curr.GetPosition().x, curr.GetPosition().y, curr.GetPosition().z, curr.GetPosition().w);
			}
		}
		glEnd();
	}

private:
	MVPMatrices mvp_;

	void glfwInit_() {
		if (!glfwInit()) {
			throw std::runtime_error("Initializing GLFW error");
		}
	}

	void TerminateGLFW_() {
		glfwTerminate();
	}
};

class OpenGLRenderGame : public IRenderGame {
public:
	OpenGLRenderGame() = delete;

	explicit OpenGLRenderGame(OpenGLWindow* window, OpenGLRenderer* renderer)
		: window_(window), renderer_(renderer) {

	}

	~OpenGLRenderGame() override = default;

	void RenderGame(const GameField& gameField) override {
		std::vector<Vertex> testVertices{
			Vertex(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)),
			Vertex(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)),
			Vertex(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)),
			Vertex(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)),
			Vertex(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)),
			Vertex(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)),
		};

		this->renderer_->SetViewport(glm::vec2(0.0f, 0.0f), glm::vec2(this->window_->GetWidth(), this->window_->GetHeight()));
		this->renderer_->ClearDisplay(glm::vec4(0.5f, 0.5f, 0.5f, 0.0f));
		this->renderer_->RenderLines(testVertices);
	}

private:
	std::unique_ptr<OpenGLWindow> window_;
	std::unique_ptr<OpenGLRenderer> renderer_;
};
