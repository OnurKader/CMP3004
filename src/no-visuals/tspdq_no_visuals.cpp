#include <algorithm>
#include <array>
#include <cmath>
#include <fmt/format.hpp>
#include <vector>

struct City
{
	uint16_t x;
	uint16_t y;
	City(const uint16_t t_x, const uint16_t t_y) : x(t_x), y(t_y) {}
};

float totalDistanceX(const std::vector<City>& route, const size_t size)
{
	float sum = 0.f;
	for(size_t x = 0; x < size - 1; ++x)
	{
		sum += std::sqrt(std::pow(route[x + 1].x - route[x].x, 2) +
						 std::pow(route[x + 1].y - route[x].y, 2));
	}

	return sum;
}

void printCountryX(const std::vector<City>& route)
{
	std::for_each(route.cbegin(), route.cend(), [i = 1ULL](const City& city) mutable {
		fmt::print("Route {} -> x: {} y: {}\n", i++, city.x, city.y);
	});
}

void changeRouteX(std::vector<City>& route, const size_t indexf, const size_t indexs)
{
	// Is this just std::swap(route[indexf], route[indexs]); ?
	City temp = route[indexf];
	route.at(indexf) = route[indexs];
	route.at(indexs) = temp;
}

std::vector<City> shortestForThreeX(std::vector<City>& route)
{
	std::vector<City> rCity = route;

	float record = totalDistanceX(route, route.size());
	changeRouteX(route, 1, 2);

	if(totalDistanceX(route, 3) < record)
	{
		rCity = route;
		record = totalDistanceX(route, 3);
	}

	changeRouteX(route, 0, 1);
	changeRouteX(route, 0, 2);

	if(totalDistanceX(route, 3) < record)
	{
		rCity = route;
		record = totalDistanceX(route, 3);
	}

	return rCity;
}

std::vector<std::vector<City>> possibleRoutes(const std::vector<City>& country)
{
	std::vector<std::vector<City>> allPossibleRoutes;
	std::vector<City> temp;
	std::vector<City> a;
	std::vector<City> b;

	size_t len = country.size();

	for(size_t s = 0; s < len; ++s)
	{
		a = std::vector<City>(country.begin() + s, country.end());
		b = std::vector<City>(country.begin(), country.begin() + s);

		temp.reserve(a.size() + b.size());

		// Assignment erases reserve
		temp = a;
		temp.insert(temp.end(), b.begin(), b.end());

		allPossibleRoutes.push_back(temp);
	}

	return allPossibleRoutes;
}

std::vector<City> combineTwoRoutes(const std::vector<City>& route1, const std::vector<City>& route2)
{
	std::vector<City> final_route(route1);
	final_route.insert(final_route.end(), route2.begin(), route2.end());
	return final_route;
}

std::vector<City> joinTwoRoutes(const std::vector<City>& route1, const std::vector<City>& route2)
{
	std::vector<City> combinedRoute;
	std::vector<City> combinedRouteAlt;
	std::vector<City> reversedRoute;
	std::vector<City> routeToBeReturned;
	std::vector<std::vector<City>> routesForFormer;
	std::vector<std::vector<City>> routesForLatter;

	combinedRoute = combineTwoRoutes(route1, route2);
	routeToBeReturned = combinedRoute;

	routesForFormer = possibleRoutes(route1);
	routesForLatter = possibleRoutes(route2);

	float shortestDistance = totalDistanceX(combinedRoute, combinedRoute.size());
	for(size_t a = 0; a < route1.size(); ++a)
	{
		for(size_t b = 0; b < route2.size(); ++b)
		{
			combinedRoute = combineTwoRoutes(routesForFormer[a], routesForLatter[b]);
			reversedRoute =
				std::vector<City>(routesForLatter[b].rbegin(), routesForLatter[b].rend());
			combinedRouteAlt = combineTwoRoutes(routesForFormer[a], reversedRoute);

			if(totalDistanceX(combinedRouteAlt, combinedRouteAlt.size()) <
			   totalDistanceX(combinedRoute, combinedRoute.size()))
			{
				combinedRoute = combinedRouteAlt;
			}

			if(totalDistanceX(combinedRoute, combinedRoute.size()) < shortestDistance)
			{
				shortestDistance = totalDistanceX(combinedRoute, combinedRoute.size());
				routeToBeReturned = combinedRoute;
			}
		}
	}

	return routeToBeReturned;
}

uint16_t extent(const std::vector<uint16_t>& nums)
{
	const uint16_t min = *std::min_element(nums.begin(), nums.end());
	const uint16_t max = *std::max_element(nums.begin(), nums.end());

	return max - min;
}

std::vector<std::vector<City>> splitCities(std::vector<City>& route)
{
	std::vector<uint16_t> xValues;
	std::vector<uint16_t> yValues;
	std::vector<City> sortedCity;
	std::vector<City> firstHalf;
	std::vector<City> secondHalf;
	std::vector<std::vector<City>> twoSplitCities;

	size_t len = route.size();
	uint16_t smallestX = route[0].x;
	uint16_t smallestY = route[0].y;
	size_t indexOfSmallest;

	for(size_t s = 0; s < route.size(); s++)
	{
		xValues.push_back(route[s].x);
		yValues.push_back(route[s].y);
	}

	if(extent(xValues) > extent(yValues))
	{
		for(size_t s = 0; s < len; s++)
		{
			for(size_t d = 0; d < route.size(); d++)
			{
				if(route.size() == 1)
				{
					indexOfSmallest = d;
				}
				else if(route[d].x <= smallestX)
				{
					indexOfSmallest = d;
					smallestX = route[d].x;
				}
			}

			sortedCity.push_back(route[indexOfSmallest]);
			route.erase(route.begin() + indexOfSmallest);
			smallestX = route[0].x;
		}
	}
	else
	{
		for(size_t s = 0; s < len; s++)
		{
			for(size_t d = 0; d < route.size(); d++)
			{
				if(route.size() == 1)
				{
					indexOfSmallest = d;
				}
				else if(route[d].y <= smallestY)
				{
					indexOfSmallest = d;
					smallestY = route[d].y;
				}
			}
			sortedCity.push_back(route[indexOfSmallest]);
			route.erase(route.begin() + indexOfSmallest);
			smallestY = route[0].y;
		}
	}

	firstHalf = std::vector<City>(sortedCity.begin(), sortedCity.end() - (sortedCity.size() / 2));
	secondHalf = std::vector<City>(sortedCity.begin() + (sortedCity.size() / 2), sortedCity.end());

	twoSplitCities.push_back(firstHalf);
	twoSplitCities.push_back(secondHalf);

	return twoSplitCities;
}

std::vector<City> divideAndConquer(std::vector<City>& country, const size_t n)
{
	if(country.size() <= n)
	{
		return shortestForThreeX(country);
	}
	else
	{
		std::vector<std::vector<City>> twoHalves = splitCities(country);

		std::vector<City> half1 = twoHalves.front();
		std::vector<City> half2 = twoHalves.back();

		return joinTwoRoutes(divideAndConquer(half1, n), divideAndConquer(half2, n));
	}
}

int main()
{
	std::vector<City> conversion {
		City(6734, 1453), City(2233, 10),	City(5530, 1424), City(401, 841),	City(3082, 1644),
		City(7608, 4458), City(7573, 3716), City(7265, 1268), City(6898, 1885), City(1112, 2049),
		City(5468, 2606), City(5989, 2873), City(4706, 2674), City(4612, 2035), City(6347, 2683),
		City(6107, 669),  City(7611, 5184), City(7462, 3590), City(7732, 4723), City(5900, 3561),
		City(4483, 3369), City(6101, 1110), City(5199, 2182), City(1633, 2809), City(4307, 2322),
		City(675, 1006),  City(7555, 4819), City(7541, 3981), City(3177, 756),	City(7352, 4506),
		City(7545, 2801), City(3245, 3305), City(6426, 3173), City(4608, 1198), City(23, 2216),
		City(7248, 3779), City(7762, 4595), City(7392, 2244), City(3484, 2829), City(6271, 2135),
		City(4985, 140),  City(1916, 1569), City(7280, 4899), City(7509, 3239), City(10, 2676),
		City(6807, 2993), City(5185, 3258), City(3023, 1942)};

	std::vector<City> citiesPro = divideAndConquer(conversion, 3);
	printCountryX(citiesPro);
	fmt::print("\nDistance: {}\n", totalDistanceX(citiesPro, citiesPro.size()));

	return 0;
}
