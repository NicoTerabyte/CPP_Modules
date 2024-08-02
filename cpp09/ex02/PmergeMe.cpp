/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:01:50 by lnicoter          #+#    #+#             */
/*   Updated: 2024/08/02 12:32:40 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
/*----costrucotrs, orthodoxical part----*/

PmergeMe::PmergeMe(std::deque<int>dequeAlgorithm, std::vector<int>vectorAlgorithm) :
	dequeAlgorithm(dequeAlgorithm), vectorAlgorithm(vectorAlgorithm)
{}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& obj) :
		dequeAlgorithm(obj.dequeAlgorithm) , vectorAlgorithm(obj.vectorAlgorithm)
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& obj)
{
	this->vectorAlgorithm = obj.vectorAlgorithm;
	this->dequeAlgorithm = obj.dequeAlgorithm;

	return *this;
}

/*----costructor orthodoxical part end----*/

/*----Optional functions just for me part----*/
void	PmergeMe::printCont()
{
	std::deque<int>::iterator	it;
	std::vector<int>::iterator	itVec;

	for (it = dequeAlgorithm.begin(); it != dequeAlgorithm.end(); it++)
		std::cout<<"deque value "<<*it<<std::endl;
	for (itVec = vectorAlgorithm.begin(); itVec != vectorAlgorithm.end(); itVec++)
		std::cout<<"vector value "<<*itVec<<std::endl;
}

void	PmergeMe::printPairsVec(std::vector<std::pair<int, int> >& vectorPairs)
{
	std::vector<std::pair<int, int> >::iterator	it;

	for (it = vectorPairs.begin(); it != vectorPairs.end(); it++)
	{
		std::cout<<"("<<it->first<<", "<<it->second<<")"<<std::endl;
	}
}

void	PmergeMe::printPairsDeq(std::deque<std::pair<int, int> >& dequePairs)
{
	std::deque<std::pair<int, int> >::iterator	it;

	for (it = dequePairs.begin(); it != dequePairs.end(); it++)
	{
		std::cout<<"("<<it->first<<", "<<it->second<<")"<<std::endl;
	}
}


//this is for checking the pending container mostly
void	PmergeMe::printSpecifiedCont(std::deque<int> pending)
{
	std::deque<int>::iterator	it;

	for (it = pending.begin(); it != pending.end(); it++)
		std::cout<<"pending value "<<*it<<std::endl;
}
/*----Optional functions just for me PART END----*/



//! You can ignore the part up because is all optional stuff
//! That doesn't involve the logic of the code

/*----sezione jacobsthal----*/

//* Mostly jacobstahl is used for the pending array
//* is  it used to lower the amount of comparasisons by dividing
//* the the array in chuncks of arrays as big as the jacobsthal sequence
//* asks
int	PmergeMe::jacobsthal(int containerLenght)
{
	if (containerLenght == 0)
		return 0;
	if (containerLenght == 1)
		return 1;
	return jacobsthal(containerLenght - 1) + 2 * jacobsthal(containerLenght - 2);
}


std::vector<int> PmergeMe::build_jacob_insertion_sequence(int array_len)
{
	std::vector<int> end_sequence;
	int jacob_index = 3; // Il primo che conta

	while (jacobsthal(jacob_index) < array_len - 1)
	{
		end_sequence.push_back(jacobsthal(jacob_index));
		jacob_index++;
	}

	return end_sequence;
}

/*----Sezione jacobsthal END*/

/* //* ----Vector Algorithm part----  */

/*
*this part is used for both the container to
*sort the pairs made before when we were applying the first phases of the
*algorithm
*/
void	PmergeMe::sortPairVectorVer(std::vector<std::pair<int, int> >& vectorPairs)
{
	std::vector<std::pair<int, int> >::iterator	it;
	int											tmp = 0;

	for (it = vectorPairs.begin(); it != vectorPairs.end(); it++)
	{
		if (it->first > it->second)
		{
			tmp = it->first;
			it->first = it->second;
			it->second = tmp;
		}
	}
}


//questo alla fine prima ordinare uno dei due vettori
// void	binarySearchSortVec(std::vector<int>& biggest)
//questa sezione funziona indipendentemente anche se non
//uso jacob
void	PmergeMe::binarySearchSortVec(std::vector<int>& biggest, std::vector<int>& lowest)
{
	std::vector<int>::iterator	it;

	for (size_t i = 0; i < lowest.size(); i++)
	{
		biggest.insert(std::lower_bound(biggest.begin(), biggest.end(), lowest[i]), lowest[i]);
	}
	this->vectorAlgorithm = biggest;
}

/*
//* UPDATE THIS PART AS YOU UPDATED THE DEQUE ALGORITHM
still needed:
	todo:jacobsthal
*/
void	PmergeMe::dividePair(std::vector<std::pair<int, int> >& vectorPairs, int rejected, bool odd)
{
	std::vector<int>	lowest;
	std::vector<int>	biggest;
	std::vector<std::pair<int, int> >::iterator	it;

	for (it = vectorPairs.begin(); it != vectorPairs.end(); it++)
	{
		if (biggest.empty())
		{
			biggest.push_back(it->second);
		}
		else
		{
			bool	inserted = false;

			for (size_t i = 0; i < biggest.size(); i++)
			{
				if (it->second < biggest[i])
				{
					biggest.insert(biggest.begin() + i, it->second);
					inserted = true;
					break;
				}
			}
			if (!inserted)
				biggest.push_back(it->second);
		}
		lowest.push_back(it->first);
	}
	if (odd)
		lowest.push_back(rejected);
	binarySearchSortVec(biggest, lowest);
}

//if the vector is odd i save the last value
//and i pop it out of the vector

//2.1 funzione utilizzata per ordinare il vettore
double	PmergeMe::vectorMergeInsert()
{
	clock_t	start, end;
	int		rejected;
	bool	odd = false;
	std::vector<int>::iterator	it;
	std::vector<std::pair<int, int> >	pairs;

	start = clock();

	if (vectorAlgorithm.size() % 2 != 0)
	{
		odd = true;
		rejected = vectorAlgorithm.back();
		vectorAlgorithm.pop_back();
	}
	for (it = this->vectorAlgorithm.begin(); it != (this->vectorAlgorithm.end() - 1)
	&& it != this->vectorAlgorithm.end()	; it+=2)
	{
		std::pair<int, int>	tmpPair(*it, *(it + 1));
		pairs.push_back(tmpPair);
	}
	dividePair(pairs, rejected, odd);
	end = clock();
	double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
	(void) rejected;
	(void) odd;
	return (elapsed_time);
}
/*----Vector Algorithm part----*/

/*----deque merge insertion sort algorithm section----*/



void	PmergeMe::binarySearchSortDeq(std::deque<int>& biggest, std::deque<int>& lowest)
{
	std::deque<int>::iterator	it;

	for (size_t i = 0; i < lowest.size(); i++)
	{
		biggest.insert(std::lower_bound(biggest.begin(), biggest.end(), lowest[i]), lowest[i]);
	}
	this->dequeAlgorithm = biggest;
}


void	PmergeMe::sortBiggest(std::deque<int>& biggest)
{
	for (size_t i = 1; i < biggest.size(); i++)
	{
		size_t	value = biggest[i];
		size_t	j = i - 1;

		while (j != 0 && biggest[j] > (int)value)
		{
			biggest[j + 1] = biggest[j];
			j--;
		}
		biggest[j + 1] = value;
	}
}

// void PmergeMe::phase2Deque(std::deque<std::pair<int, int> >& dequePairs, int rejected, bool odd)
// {
// 	std::deque<int> lowest;
// 	std::deque<int> biggest;
// 	std::deque<std::pair<int, int> >::iterator it;

//todo: fare confronti tra la nuova metodologia
//todo cioè l'approccio utilizzato per completare l'esercizio
//todo e quella che stavo applicando in precedenza
//todo comprendendo ciò potrò cancellare il codice commentato sotto
// 	for (it = dequePairs.begin(); it != dequePairs.end(); it++)
// 	{
		// Confronta i valori della coppia
// 		if (it->first > it->second)
// 		{
			// Se il primo è maggiore, inserisci il secondo in biggest e il primo in lowest
// 			biggest.push_back(it->first);
// 			lowest.push_back(it->second);
// 		}
// 		else
// 		{
			// Se il secondo è maggiore, inserisci il primo in biggest e il secondo in lowest
// 			biggest.push_back(it->second);
// 			lowest.push_back(it->first);
// 		}
// 	}
// 	if (odd)
// 		lowest.push_back(rejected);
// 	sortBiggest(biggest);
//	ok ora possiamo applicare jacob
// 	binarySearchSortDeq(biggest, lowest);
// }


void PmergeMe::phase2Deque(std::deque<std::pair<int, int> >& dequePairs, int rejected, bool odd)
{
	std::deque<int> lowest;
	std::deque<int> biggest;
	std::deque<std::pair<int, int> >::iterator it;

	// Separa i numeri in biggest e lowest
	for (it = dequePairs.begin(); it != dequePairs.end(); ++it) {
		if (it->first > it->second)
		{
			biggest.push_back(it->first);
			lowest.push_back(it->second);
		}
		else
		{
			biggest.push_back(it->second);
			lowest.push_back(it->first);
		}
	}

	// Gestisci l'elemento rifiutato se il numero di elementi è dispari
	if (odd)
	{
		lowest.push_back(rejected);
	}

	// Ordina i numeri più grandi
	sortBiggest(biggest);

	// Applica la sequenza di Jacobsthal per ordinare i numeri più piccoli
	std::vector<int> jacob_insertion_sequence = build_jacob_insertion_sequence(lowest.size());
	std::deque<int> sorted_lowest;
	sorted_lowest.push_back(lowest[0]); // Inserisci il primo elemento

	int iterator = 0;
	for (int i = 0; (size_t) i < jacob_insertion_sequence.size(); ++i)
	{
		int index = jacob_insertion_sequence[i];
		int item = lowest[index - 1];
		std::deque<int>::iterator insertion_point = std::lower_bound(sorted_lowest.begin(), sorted_lowest.end(), item);
		sorted_lowest.insert(insertion_point, item);
		iterator++;
	}

	// Inserisci gli elementi rimanenti in modo sequenziale
	while ((size_t) iterator < lowest.size())
	{
		sorted_lowest.push_back(lowest[iterator]);
		iterator++;
	}

	// Applica l'ordinamento finale utilizzando binarySearchSortDeq
	binarySearchSortDeq(biggest, sorted_lowest);
}




//if the deque is odd i save the last value
//and i pop it out of the deque;

double	PmergeMe::dequeMergeInsert()
{
	clock_t start, end;
	int		rejected;
	bool	odd = false;
	std::deque<int>::iterator	it;
	std::deque<std::pair<int, int> >pairs;

	start = clock();
	if (dequeAlgorithm.size() % 2 != 0)
	{
		odd = true;
		rejected = dequeAlgorithm.back();
		dequeAlgorithm.pop_back();
	}
	for (it = this->dequeAlgorithm.begin(); it != (this->dequeAlgorithm.end() - 1)
	&& it != this->dequeAlgorithm.end()	; it+=2)
	{
		std::pair<int, int>	tmpPair(*it, *(it + 1));
		pairs.push_back(tmpPair);
	}
	phase2Deque(pairs, rejected, odd);
	end = clock();
	double	elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
	return (elapsed_time);
}
/*----deque merge insertion sort algorithm section end----*/



//aggiornameto del 31/07/2024
//l'algoritmo funziona per la deque ma non è stata fatta
//la versione per il container vector
/* //! Sezione di analisi approccio per rivedere e migliorare il codice
	todo: Implementare jacob per vettori e modificare l'algoritmo
	todo: dei vettori
	todo: fare pulizia del codice e dei commenti
*/
void	PmergeMe::mergeInsertionSort(char** argv, int ac)
{
	double	vecDiff, deqDiff;

	std::cout<<"Before:  ";
	if (ac > 6)
	{
		for (size_t i = 1; i < 5; i++)
			std::cout<<argv[i]<<" ";
		std::cout<<"[...]"<<std::endl;
	}
	else
	{
		for (size_t i = 1; argv[i]; i++)
			std::cout<<argv[i]<<" ";
		std::cout<<""<<std::endl;
	}
	std::cout<<"After:  ";
	vecDiff = vectorMergeInsert();
	deqDiff = dequeMergeInsert();
	if (ac > 6)
	{
		for (size_t i = 0; i < 4; i++)
			std::cout<<dequeAlgorithm[i]<<" ";
		std::cout<<"[...]"<<std::endl;
	}
	else
	{
		for (size_t i = 0; i < vectorAlgorithm.size(); i++)
			std::cout<<vectorAlgorithm[i]<<" ";
		std::cout<<""<<std::endl;
		for (size_t i = 0; i < dequeAlgorithm.size(); i++)
			std::cout<<dequeAlgorithm[i]<<" ";
		std::cout<<""<<std::endl;
	}
	std::cout<<"Time to process a range of "<<ac<<" elements with std::vector : "<<std::fixed << std::showpoint << std::setprecision(5)<<vecDiff / 100<<" us"<<std::endl;
	std::cout<<"Time to process a range of"<<ac<<" elements with std::deque : "<<std::fixed << std::showpoint << std::setprecision(5)<<deqDiff / 100<<" us"<<std::endl;
}
/*----Output requested section part end----*/
