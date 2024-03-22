/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:43:48 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2024/03/23 00:32:37 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdlib.h>

#include "glad/gl.h"

#include "mb_core.h"
#include "mb_real_float.h"
#include "mb_colorizer_basic.h"

static size_t	get_iteration_count(
	t_main_context *context,
	size_t y,
	size_t x,
	size_t *out
)
{
	t_mb_real	*r;
	t_mb_real	*i;
	t_err		result;

	r = mb_real_float_new((float)x * 4 / ((float)context->width - 1) - 2);
	if (!r)
		return (true);
	i = mb_real_float_new((float)y * 4 / ((float)context->height - 1) - 2);
	if (!i)
	{
		mb_real_float_delete(r);
		return (true);
	}
	result = mb(context->mb, r, i, out);
	mb_real_float_delete(r);
	mb_real_float_delete(i);
	return (result);
}

static t_err	set_pixel(
	t_main_context *context,
	size_t y,
	size_t x,
	unsigned char *image
)
{
	size_t						iteration_count;
	t_mb_colorizer_basic_color	color;
	const size_t				row_size = (size_t)context->width * 3
		+ (4 - (size_t)context->width * 3 % 4) % 4;

	if (get_iteration_count(context, y, x, &iteration_count))
		return (true);
	color = mb_colorizer_basic(&context->colorizer, iteration_count);
	image[y * row_size + x * 3] = (unsigned char)(color.r * 255);
	image[y * row_size + x * 3 + 1] = (unsigned char)(color.g * 255);
	image[y * row_size + x * 3 + 2] = (unsigned char)(color.b * 255);
	if (iteration_count == MAX_ITERATION_COUNT)
	{
		image[y * row_size + x * 3] = 0;
		image[y * row_size + x * 3 + 1] = 0;
		image[y * row_size + x * 3 + 2] = 0;
	}
	return (false);
}

static unsigned char	*generate_image(t_main_context *context)
{
	unsigned char *const	result
		= malloc((size_t)context->width * (size_t)context->height * 3);
	size_t					i;
	size_t					j;

	if (!result)
		return (NULL);
	i = (size_t)-1;
	while (++i < (size_t)context->height)
	{
		j = (size_t)(-1);
		while (++j < (size_t)context->width)
		{
			if (set_pixel(context, i, j, result))
			{
				free(result);
				return (NULL);
			}
		}
	}
	return (result);
}

static t_err	generate_texture(t_main_context *context, GLuint *out)
{
	unsigned char *const	image = generate_image(context);

	if (!image)
		return (true);
	glGenTextures(1, out);
	glBindTexture(GL_TEXTURE_2D, *out);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, context->width, context->height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image);
	free(image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (glGetError() != GL_NO_ERROR)
	{
		glDeleteTextures(1, out);
		return (true);
	}
	return (false);
}

t_err	render(t_main_context *context)
{
	GLuint	texture;

	if (generate_texture(context, &texture))
		return (true);
	glUseProgram(context->program);
	glBindVertexArray(context->vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glUniform1i(glGetUniformLocation(context->program, "ourTexture"), 0);
	glDeleteTextures(1, &texture);
	return (glGetError() != GL_NO_ERROR);
}
