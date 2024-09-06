/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yademirk <yademirk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:23:28 by yademirk          #+#    #+#             */
/*   Updated: 2024/08/24 18:39:12 by yademirk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	get_input_rows(int *arr, char *str)
{
	int	i;
	int row;
	
	i = 0;
	row = 0;
	while (row < 16)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			arr[row] = str[i] - '0';
			row++;
		}
		i++;
	}
}

int	return_largest_index(int *arr, int size)
{
	int	i;
	int	a;
	int	largest;

	i = 0;
	a = 0;
	largest = 0;
	while (i < size)
	{
		if (arr[i] > largest)
		{
			a = i;
			largest = arr[i];
		}	
		i++;
	}
	return (a);
}

int	return_largest_index_vertical(int arr[4][4], int index, int size)
{
	int	i;
	int	a;
	int	largest;

	i = 0;
	a = 0;
	largest = 0;
	while (i < size)
	{
		if (arr[i][index] > largest)
		{
			a = i;
			largest = arr[i][index];
		}	
		i++;
	}
	return (a);
}

int	return_smallest_index(int *arr, int size)
{
	int	i;
	int	a;
	int	smallest;

	i = 0;
	a = 0;
	smallest = arr[0];
	while (i < size)
	{
		if (arr[i] < smallest)
		{
			a = i;
			smallest = arr[i];
		}	
		i++;
	}
	return (a);
}

int	return_smallest_index_vertical(int arr[4][4], int index, int size)
{
	int	i;
	int	a;
	int	smallest;

	i = 0;
	a = 0;
	smallest = arr[0][index];
	while (i < size)
	{
		if (arr[i][index] < smallest)
		{
			a = i;
			smallest = arr[i][index];
		}	
		i++;
	}
	return (a);
}

int	*remove_from_array(int arr[], int *size, int index)
{
	int	i;
	int	a;
	int	*new_arr;

	new_arr = malloc((*size - 1) * 4);
	i = 0;
	a = 0;
	while(i < *size - 1)
	{
		if (i == index)
			a++;
		new_arr[i] = arr[i + a];
		i++;
	}
	*size -= 1;
	return (new_arr);
}

int	ft_visible_from_left(int *arr)
{
	int	i;
	int	a;
	int	largest_index;
	int visible_from_left;

	largest_index = return_largest_index(arr, 4);
	visible_from_left = 1;
	i = 0;
	a = 1;
	while (i < largest_index)
	{	
		if (arr[i] < arr[i + a])
		{
			visible_from_left++;
			i += a;
			a = 1;
		}
		else
			a++;	
	}	
	return (visible_from_left);
}

int	ft_visible_from_right(int *arr)
{
	int	i;
	int	a;
	int	largest_index;
	int visible_from_right;

	largest_index = return_largest_index(arr, 4);
	visible_from_right = 1;
	i = 3;
	a = 1;
	while (i > largest_index)
	{	
		if (arr[i] < arr[i - a])
		{
			visible_from_right++;
			i -= a;
			a = 1;
		}
		else
			a++;	
	}	
	return (visible_from_right);
}

int	ft_visible_from_up(int arr[4][4], int index)
{
	int	i;
	int	a;
	int	largest_index;
	int visible_from_up;

	largest_index = return_largest_index_vertical(arr, index, 4);
	visible_from_up = 1;
	i = 0;
	a = 1;
	while (i < largest_index)
	{	
		if (arr[i][index] < arr[i + a][index])
		{
			visible_from_up++;
			i += a;
			a = 1;
		}
		else
			a++;	
	}	
	//printf("Visible from up on index %i: %i\n", index, visible_from_up);
	return (visible_from_up);
}

int	ft_visible_from_down(int arr[4][4], int index)
{
	int	i;
	int	a;
	int	largest_index;
	int visible_from_down;

	largest_index = return_largest_index_vertical(arr, index, 4);
	visible_from_down = 1;
	i = 3;
	a = 1;
	while (i > largest_index)
	{	
		if (arr[i][index] < arr[i - a][index])
		{
			visible_from_down++;
			i -= a;
			a = 1;
		}
		else
			a++;	
	}	
	//printf("Visible from down on index %i: %i\n", index, visible_from_down);
	return (visible_from_down);
}

int	is_row_valid_horizontal(int *arr, int left, int right)
{
	int visible_from_left;
	int visible_from_right;

	visible_from_left = ft_visible_from_left(arr);
	visible_from_right = ft_visible_from_right(arr);
	//printf("VSL: %i\n", visible_from_left);
	//printf("VSR: %i\n", visible_from_right);
	if (right != visible_from_right || left != visible_from_left)
		return (0);
	return (1);
}

int	is_row_valid_vertical(int arr[4][4], int starting_index, int up, int down)
{
	int visible_from_up;
	int visible_from_down;

	visible_from_up = ft_visible_from_up(arr, starting_index);
	visible_from_down = ft_visible_from_down(arr, starting_index);
	printf("VSL Vert: %i\n", visible_from_up);
	printf("VSR Vert: %i\n", visible_from_down);
	if (down != visible_from_down || up != visible_from_up)
	{
		printf("Is Index %i valid: %i\n", starting_index, 0);
		return (0);
	}
		
	printf("Is Index %i valid: %i\n", starting_index, 1);
	return (1);
}

void	fix_row_horizontal(int *arr, int left, int right)
{
	int	largest;
	int smallest;
	int temp;
	int valid;

	valid = is_row_valid_horizontal(arr, left, right);
	//printf("Is valid: %i\n", valid);

	if (valid != 1)
	{
		largest = return_largest_index(arr, 4);
		smallest = return_smallest_index(arr, 4);
		temp = arr[largest];
		arr[largest] = arr[smallest];
		arr[smallest] = temp;
	}
}

void	fix_row_vertical(int arr[4][4], int index, int up, int down)
{
	int	largest;
	int smallest;
	int temp;
	int valid;

	//valid = is_row_valid_vertical(arr, 3, up, down);
	//printf("Is valid: %i\n", valid);

	//if (valid != 1)
	//{
	//	largest = return_largest_index_vertical(arr, 0, 4);
	//	smallest = return_smallest_index_vertical(arr, 0, 4);
	//	temp = arr[largest];
	//	arr[largest][index] = arr[smallest];
	//	arr[smallest][index] = temp;
	//}
}

void	create_row(int *arr, int left, int right)
{
	int	i;
	int i2;
	int	a;
	int	seeable;
	int	size;
	int	*available = malloc(4 * 4);
    available[0] = 1;
    available[1] = 2;
    available[2] = 3;
    available[3] = 4;

	size = 4;
	i = 0;
	a = 4 - left;
	while (i < left)
	{
		arr[i] = available[a];
		available = remove_from_array(available, &size, a);
		i++;
	}
	i--;
	seeable = 1;
	while (i > 0)
	{
		if (arr[i] < arr[i - 1])
			seeable++;
		i--;
	}
	i = 3;
	i2 = right - seeable;
	while (i >= left)
	{
		if (i2 > 0)
		{			
			i2--;
			a = return_largest_index(available, size) - i2;
		}
		else
			a = return_smallest_index(available, size);
			
		arr[i] = available[a];
		available = remove_from_array(available, &size, a);
		i--;
	}
	//printf("Left: %i\n", left);
	//printf("Right: %i\n", right);
	fix_row_horizontal(arr, left, right);
}

void	create_grid(int arr[4][4], int *input_rows)
{
	int	i;
	
	i = 0;
	while (i < 4)
	{
		create_row(arr[i], input_rows[i + 8], input_rows[12 + i]);
		is_row_valid_vertical(arr, i, input_rows[i], input_rows[4 + i]);
		i++;
	}
}

int	main(int count, char *args[])
{
	int	i;
	int a;
	int	size;
	int	input_rows[16];
	int	rows[4][4];

	i = 0;
	size = 4;
	get_input_rows(input_rows, args[1]);
	create_grid(rows, input_rows);

	while (count == 2 && i < 4)
	{
		a = 0;
		while (a < 4)
		{
			printf("%i ", rows[i][a]);
			a++;
		}
		printf("\n");
		i++;
	}

	
	
	return (0);
}
