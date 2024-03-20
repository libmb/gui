/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit_context.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:37:32 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2024/03/21 01:39:20 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include "glad/gl.h"

void	deinit_context(t_main_context context)
{
	glDeleteVertexArrays(1, &context.vao);
	glDeleteBuffers(1, &context.vbo);
	glDeleteProgram(context.program);
}
