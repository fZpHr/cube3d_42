/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_id_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:56:57 by hbelle            #+#    #+#             */
/*   Updated: 2024/03/21 18:41:57 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Handle the option MP, SP, TY of the texture
 * 
 * @param map struct of the map
 * @param array_line splitted line
 * @param id id of the texture
 * 
 * @return void
*/
void	ft_handle_option(t_map *map, char **array_line, int id)
{
	if (ft_handle_strncmp(map, array_line, "MP", 2) == 1)
		ft_handle_color_id(map, array_line, id);
	else if (ft_handle_strncmp(map, array_line, "SP", 2) == 1)
	{
		map->text[id].sp = ft_atoi(array_line[2]);
		if (map->text[id].sp < 0 || map->text[id].sp > 1000)
		{
			ft_free_array(array_line);
			ft_error_handle(map, "Error\n", "Invalid speed", 1);
		}
	}
	else if (ft_handle_strncmp(map, array_line, "TY", 1) == 1)
	{
		map->text[id].ty = ft_atoi(array_line[2]);
		if (map->text[id].ty < 0 || map->text[id].ty > 1)
		{
			ft_free_array(array_line);
			ft_error_handle(map, "Error\n", "Invalid type", 1);
		}
	}
}

/**
 * @brief add frame to the arrayls
 * @param frame frame to handle
 * @param array_line splitted line
 * @return void
 */
void	ft_handle_frame(char **frame, char **array_line)
{
	int	i;
	int	j;

	j = 0;
	while (array_line[j] != NULL)
		j++;
	i = 0;
	while (i < MAX_FRAME)
	{
		if (frame[i] != NULL)
			i++;
		else if (j == 2)
		{
			frame[i] = ft_strdup(array_line[1]);
			break ;
		}
		else if (j == 3)
		{
			frame[i] = ft_strdup(array_line[2]);
			break ;
		}
	}
}

void	ft_loop_nb_arg(t_map *map, char **array_line, int i)
{
	ft_cut_extra_char(array_line[1]);
	if (ft_acces_texture(array_line[1], 0) == 1)
	{
		ft_free_array(array_line);
		ft_error_handle(map, "Error\n", "Invalid texture path", 1);
	}
	if (i == 0)
		ft_handle_frame(map->text['1'].no, array_line);
	else if (i == 1)
		ft_handle_frame(map->text['1'].so, array_line);
	else if (i == 2)
		ft_handle_frame(map->text['1'].we, array_line);
	else if (i == 3)
		ft_handle_frame(map->text['1'].ea, array_line);
	else if (i == 4)
		ft_handle_option(map, array_line, '1');
}

/**
 * @brief Check the number of arguments and if it's a default texture, handle it
 * @param map struct of the map
 * @param array_line splitted line
 * @param i current texture index
 * 
 * @return 1 if the number of arguments is valid, 0 otherwise
*/
int	ft_nb_arg(t_map *map, char **array_line, int i)
{
	int	j;

	j = 0;
	while (array_line[j] != NULL)
		j++;
	if (j < 2)
	{
		ft_free_array(array_line);
		ft_error_handle(map, "Error\n", "Invalid desc content", 1);
	}
	else if (j == 2)
	{
		ft_loop_nb_arg(map, array_line, i);
		return (1);
	}
	return (0);
}
