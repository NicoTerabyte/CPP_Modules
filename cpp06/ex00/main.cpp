/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:55:41 by lnicoter          #+#    #+#             */
/*   Updated: 2024/04/24 20:01:04 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		/*code for the number convertion*/
		ScalarConverter::convert(static_cast<std::string>(argv[1]));
	}
	else
		std::cout<<"Too many arguments"<<std::endl;
	return (0);
}
