#include "render-system.hpp"

namespace rpg::graphics {

void RenderSystem::Update(const double delta) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shader_program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
} // namespace rpg::graphics
