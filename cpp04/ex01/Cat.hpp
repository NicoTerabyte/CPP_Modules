/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:27:36 by lnicoter          #+#    #+#             */
/*   Updated: 2024/01/10 20:00:39 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain* catMind;
	public:
		Cat();
		virtual ~Cat();
		Cat(Cat& obj);
		Cat& operator=(const Cat& obj);
		void makeSound() const;
		void setMind();
};

#endif