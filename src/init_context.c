/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:41:42 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2024/03/21 01:43:39 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stddef.h>

#include "glad/gl.h"

static const char	*g_vertex_shader_source = ""
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec2 aTexCoords;\n"
	"\n"
	"out vec2 TexCoords;\n"
	"\n"
	"void main() {\n"
	"	gl_Position = vec4(aPos, 1.0);\n"
	"	TexCoords = aTexCoords;\n"
	"}\n"
	"";

static const char	*g_fragment_shader_source = ""
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

static const float	g_verticies[] = {
	-1.0f, -1.0f,
	1.0f, -1.0f,
	-1.0f, 1.0f,
	1.0f, -1.0f,
	-1.0f, 1.0f,
	1.0f, 1.0f,
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
	if (init_program(&out->program))
		return (true);
	if (init_vao_and_vbo(&out->vao, &out->vbo))
	{
		glDeleteProgram(out->program);
		return (true);
	}
	return (false);
}
