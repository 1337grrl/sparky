#include "window.h"

namespace sparky {
	namespace graphics {

		void windowResize(GLFWwindow *window, int width, int height); 

		Window::Window(const char* name, int width, int height) {
			m_name = name;
			m_width = width;
			m_height = height;
			if (!init()) {
				glfwTerminate();
			}
		}

		Window::~Window() {
			glfwTerminate();
		}


		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}

			m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
			if(!m_window) {
				std::cout << "Failed to init window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_window);
			glfwSetWindowSizeCallback(m_window, windowResize);
			if (glewInit() != GLEW_OK) {
				std::cout << "Initializing GLEW failed." << std::endl;
				return false;
			}
			return true;
		}

		bool Window::closed() const {
			return (bool) glfwWindowShouldClose(m_window);
		}

		void Window::update() {
			glfwPollEvents();
			//glfwGetFramebufferSize(m_window, &m_width, &m_height);
			glfwSwapBuffers(m_window);
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void windowResize(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);

		}
	}
}