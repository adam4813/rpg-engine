#pragma once
#include <gl/glew.h>
#include <glm/vec3.hpp>
#include <iostream>

namespace rpg::graphics {
class RenderSystem {
public:
	void Update(const double delta);
	void Setup() {

		const glm::vec3 vertices[] = {{0.5f, 0.5f, 0.f}, {0.5f, -0.5f, 0.f}, {-0.5f, -0.5f, 0.f}, {-0.5f, 0.5f, 0.f}};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

		const glm::ivec3 indices[] = {{0, 1, 3}, {1, 2, 3}};

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		const unsigned int vertex_shader = CompileShader(
				GL_VERTEX_SHADER,
				"#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"void main()\n"
				"{\n"
				"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				"}\0");

		const unsigned int fragment_shader = CompileShader(
				GL_FRAGMENT_SHADER,
				"#version 330 core\n"
				"out vec4 FragColor;\n"
				"void main()\n"
				"{\n"
				"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\0");

		shader_program = glCreateProgram();
		glAttachShader(shader_program, vertex_shader);
		glAttachShader(shader_program, fragment_shader);
		glLinkProgram(shader_program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}

	static unsigned int CompileShader(const int shader_type, const char* shader_source) {
		const unsigned int shader = glCreateShader(shader_type);
		glShaderSource(shader, 1, &shader_source, nullptr);
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			char info_Log[512];
			glGetShaderInfoLog(shader, 512, nullptr, info_Log);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_Log << std::endl;
		}
		return shader;
	}

private:
	unsigned int vbo{0};
	unsigned int vao{0};
	unsigned int ebo{0};
	unsigned int shader_program{0};
};
} // namespace rpg::graphics
