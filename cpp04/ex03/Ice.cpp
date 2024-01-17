/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:42:32 by lnicoter          #+#    #+#             */
/*   Updated: 2024/01/17 15:20:53 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria()
{
	this->type = "ice";
}

Ice::~Ice()
{
}

Ice::Ice(Ice& obj) : AMateria(obj)
{
	this->type = obj.type;
}

Ice& Ice::operator=(const Ice& obj)
{
	this->type = obj.type;
	return *this;
}


AMateria* Ice::clone() const
{
	AMateria* iceCopy = new Ice();
	return iceCopy;
}

void Ice::use(ICharacter& target)
{
	std::cout<<"* shoots an ice bolt at "<<target.getName()<<" *"<<std::endl;
}
