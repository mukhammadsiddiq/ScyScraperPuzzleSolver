/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukibrok <mukibrok@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:26:26 by mukibrok          #+#    #+#             */
/*   Updated: 2024/10/12 22:50:16 by mukibrok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_putchar(char c);
void	ft_putstr(char s);
int		is_valid(int **grid, int row, int  col, int num, int *clues);

int	**create_grid(void)
{
	int	**grid;
	int	i;
	int	j;

	grid = malloc(4 * sizeof(int *));
	i = 0;
	while (i < 4)
	{
		j = 0;
		grid[i] = malloc(4 * sizeof(int));
		while (j < 4)
		{
			grid[i][j] = 0;
			j++;
		}
		i++;
	}
	return (grid);
}

int	solve(int **grid, int row, int col, int *clues)
{
	int	num;

	if (row == 4)
		return (1);
	if (col == 4)
		return (solve(grid, row + 1, 0, clues));
	num = 1;
	while (num <= 4)
	{
		if (is_valid(grid, row, col, num, clues))
		{
			grid[row][col] = num;
			if (solve(grid, row, col + 1, clues))
				return (1);
			grid[row][col] = 0;
		}
		num++;
	}
	return (0);
}

int	is_double(int **grid, int row, int col, int num)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (grid[row][i] == num || grid[i][col] == num)
			return (0);
		i++;
	}
	return (1);
}

int	check_row_visibility(int **grid, int row, int expected_visibility)
{
	int	visibility;
	int	max_height;
	int	i;

	visibility = 0;
	max_height = 0;
	i = 0;
	while (i < 4)
	{
		if (grid[row][i] > max_height) 
		{
			max_height = grid[row][i];
			visibility++;
		}
		i++;
	}
	return (visibility == expected_visibility);
}

int	check_col_visibility(int **grid, int col, int expected_visibility)
{
	int	visibility; 
	int	max_height;
	int	i;

	i = 0;
	visibility = 0;
	max_height = 0;
	while (i < 4)
	{
		if (grid[i][col] > max_height) 
		{
			max_height = grid[i][col];
			visibility++;
		}
		i++;
	}
	return (visibility == expected_visibility);
}

int	is_valid(int **grid, int row, int  col, int num, int *clues)
{
	int	visibility;
	int	height;
	int	i;

	if (!is_double(grid, row, col, num))
		return (0);
	grid[row][col] = num;
	if (col == 3) 
	{
		if (!check_row_visibility(grid, row, clues[8 + row])) 
		{
			grid[row][col] = 0;
			return (0);
		}
	}
	if (row == 3) 
	{
		if (!check_col_visibility(grid, col, clues[col])) 
		{
			grid[row][col] = 0;
			return (0);
		}
	}
	return (1);
}

void	free_grid(int **grid)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	print_grid(int **grid)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ft_putchar(' ');
			ft_putchar(grid[i][j] + '0');
			j++;
		}
		i++;
		ft_putchar('\n');
	}
}
