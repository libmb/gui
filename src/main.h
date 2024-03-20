/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 00:39:30 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2024/03/21 01:39:25 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>

# include "glad/gl.h"

typedef bool	t_err;

typedef struct s_main_context
{
	GLuint	program;
	GLuint	vao;
	GLuint	vbo;
}	t_main_context;

t_err	init_context(t_main_context *out);
void	deinit_context(t_main_context context);

#endif
