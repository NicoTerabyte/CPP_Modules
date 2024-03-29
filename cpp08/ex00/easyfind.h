/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:54:54 by lnicoter          #+#    #+#             */
/*   Updated: 2024/03/19 17:50:58 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_H
#define EASYFIND_H

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void	easyfind(const std::vector<T>& intContainer, int find)
{
	std::vector<int>::const_iterator	finder = std::find(intContainer.begin(), intContainer.end(), find);

	(void)find;
	if (finder == intContainer.end())
		throw std::runtime_error("Value in the container not found\n");
	else
		std::cout<<"Number found"<<std::endl;
}

#endif
