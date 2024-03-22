/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:41:42 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2024/03/23 00:19:24 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stddef.h>

#include "glad/gl.h"

#include "mb_core.h"
#include "mb_real_float.h"
#include "mb_colorizer_basic_types.h"

#define COLOR_STEP 5

static const char						*g_vertex_shader_source = ""
	"#version 330 core\n"
	"layout (location = 0) in vec2 aPos;\n"
	"\n"
	"out vec2 TexCoords;\n"
	"\n"
	"void main() {\n"
	"	gl_Position = vec4(aPos, 1.0, 1.0);\n"
	"	TexCoords = (aPos + vec2(1.0, 1.0)) / 2.0;\n"
	"}\n"
	"";

static const char						*g_fragment_shader_source = ""
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"\n"
	"in vec2 TexCoords;\n"
	"\n"
	"uniform sampler2D ourTexture;\n"
	"\n"
	"void main() {\n"
	"	FragColor = texture(ourTexture, TexCoords);\n"
	"}\n"
	"";

static const float						g_verticies[] = {
	-1.0f, -1.0f,
	1.0f, -1.0f,
	-1.0f, 1.0f,
	1.0f, -1.0f,
	-1.0f, 1.0f,
	1.0f, 1.0f,
};

static const t_mb_colorizer_basic_node	g_nodes[] = {
{0, {1.0f, 0.0f, 0.0f, 1.0f}},
{COLOR_STEP, {1.0f, 1.0f, 0.0f, 1.0f}},
{COLOR_STEP * 2, {0.0f, 1.0f, 0.0f, 1.0f}},
{COLOR_STEP * 3, {0.0f, 1.0f, 1.0f, 1.0f}},
{COLOR_STEP * 4, {0.0f, 0.0f, 1.0f, 1.0f}},
{COLOR_STEP * 5, {1.0f, 0.0f, 1.0f, 1.0f}},
};

static t_err	init_program(GLuint *out)
{
	const GLuint	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const GLuint	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint			success;
	bool			error;

	*out = glCreateProgram();
	error = !vertex_shader || !fragment_shader || !*out;
	glShaderSource(vertex_shader, 1, &g_vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	error |= !success;
	glShaderSource(fragment_shader, 1, &g_fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	error |= !success;
	glAttachShader(*out, vertex_shader);
	glAttachShader(*out, fragment_shader);
	glLinkProgram(*out);
	glGetProgramiv(*out, GL_LINK_STATUS, &success);
	error |= !success;
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	if (error)
		glDeleteProgram(*out);
	return (error);
}

static t_err	init_vao_and_vbo(GLuint *out_vao, GLuint *out_vbo)
{
	bool	error;

	glGenVertexArrays(1, out_vao);
	if (glGetError() != GL_NO_ERROR)
		return (true);
	glGenBuffers(1, out_vbo);
	if (glGetError() != GL_NO_ERROR)
	{
		glDeleteVertexArrays(1, out_vao);
		return (true);
	}
	glBindVertexArray(*out_vao);
	glBindBuffer(GL_ARRAY_BUFFER, *out_vbo);
	glBufferData(
		GL_ARRAY_BUFFER, sizeof(g_verticies), g_verticies, GL_STATIC_DRAW);
	error = glGetError() != GL_NO_ERROR;
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	if (error)
		glDeleteVertexArrays(1, out_vao);
	if (error)
		glDeleteBuffers(1, out_vbo);
	return (error);
}

t_err	init_context(t_main_context *out)
{
	const t_mb_colorizer_basic_node	*nodes;

	nodes = g_nodes;
	if (mb_new(mb_real_float(), 2, MAX_ITERATION_COUNT, &out->mb))
		return (true);
	if (init_program(&out->program))
	{
		mb_free(out->mb);
		return (true);
	}
	if (init_vao_and_vbo(&out->vao, &out->vbo))
	{
		mb_free(out->mb);
		glDeleteProgram(out->program);
		return (true);
	}
	out->width = DEFAULT_WINDOW_WIDTH;
	out->height = DEFAULT_WINDOW_HEIGHT;
	out->colorizer.count = 6;
	out->colorizer.length = COLOR_STEP * 6;
	out->colorizer.nodes = *(t_mb_colorizer_basic_node **)(void *)&nodes;
	return (false);
}
