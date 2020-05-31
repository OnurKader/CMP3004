#include <iostream>
#include <vector>
#include <math.h>
#include <graphics.h>
#include <Windows.h>
#include <algorithm>

using namespace std;




struct city {
  int x;
  int y;

  city(int a, int b) {
    x = a;
    y = b;
  }


};



float totalDistanceX(vector<city> route, int size) {
  float sum = 0;
  for(int x = 0; x < size - 1; x++) {


    sum += sqrt(pow(route[x + 1].x-route[x].x, 2) + pow(route[x + 1].y-route[x].y, 2));
  }


  return sum;
}


void printCountryx(vector<city> route, int size ) {
  for(int s = 0; s < size; s++) {

      cout << "\n" <<  "Route " << s + 1 << " -> x: " << route[s].x << " y: " << route[s].y << "\n";

  }
}


void changeRouteX(vector<city> &route, int indexf, int indexs) {

  city temp = city(0, 0);
  temp = route[indexf];
  route.at(indexf) = route[indexs];
  route.at(indexs) = temp;

}



vector<city> shortestForThreeX(vector<city> route) {





  vector<city> rCity;
  rCity = route;


  float record = totalDistanceX(route, route.size());
  changeRouteX(route, 1, 2);

  if(totalDistanceX(route, 3) < record) {

    rCity = route;

    record = totalDistanceX(route, 3);
  }
  changeRouteX(route, 0, 1);
  changeRouteX(route, 0, 2);

  if(totalDistanceX(route, 3) < record) {

    rCity = route;

    record = totalDistanceX(route, 3);
  }

 return rCity;





}

vector<vector<city> > possibleRoutes(vector<city> country) {
  vector<vector<city> > allPossibleRoutes;
  vector<city> temp;
  vector<city> a;
  vector<city> b;

  int len = country.size();



  for(int s = 0; s < len; s++){


    a = vector<city>(country.begin() + s, country.end());
    b = vector<city>(country.begin(), country.begin() + s);



    temp.reserve(a.size() + b.size());



    temp = a;
    temp.insert(temp.end(), b.begin(), b.end());


    allPossibleRoutes.push_back(temp);
  }

  return allPossibleRoutes;

}

vector<city> combineTwoRoutes(vector<city> route1, vector<city> route2) {
  vector<city> finalRoute;
  finalRoute.reserve(route1.size() + route2.size());
  finalRoute = route1;
  finalRoute.insert(finalRoute.end(), route2.begin(), route2.end());
  return finalRoute;

}

vector<city> joinTwoRoutes(vector<city> route1, vector<city> route2) {
  vector<city> combinedRoute;
  vector<city> combinedRouteAlt;
  vector<city> reversedRoute;
  vector<city> routeToBeReturned;
  vector<vector<city> > routesForFormer;
  vector<vector<city> > routesForLatter;

  routeToBeReturned = combinedRoute;

  combinedRoute = combineTwoRoutes(route1, route2);
  routeToBeReturned = combinedRoute;

  routesForFormer = possibleRoutes(route1);
  routesForLatter = possibleRoutes(route2);


  float shortestDistance = totalDistanceX(combinedRoute, combinedRoute.size());
  for(int a = 0; a < route1.size(); a++) {
    for(int b = 0; b < route2.size(); b++) {

      combinedRoute = combineTwoRoutes(routesForFormer[a], routesForLatter[b]);
      reversedRoute = vector<city>(routesForLatter[b].rbegin(), routesForLatter[b].rend());
      combinedRouteAlt = combineTwoRoutes(routesForFormer[a], reversedRoute);

      if(totalDistanceX(combinedRouteAlt, combinedRouteAlt.size()) < totalDistanceX(combinedRoute, combinedRoute.size())) {
        combinedRoute = combinedRouteAlt;
      }




      if(totalDistanceX(combinedRoute, combinedRoute.size()) < shortestDistance) {
        shortestDistance = totalDistanceX(combinedRoute, combinedRoute.size());

        routeToBeReturned = combinedRoute;
      }


    }

  }


  return routeToBeReturned;







}

int extentX(vector<int> nums) {
  int min = *min_element(nums.begin(), nums.end());
  int max = *max_element(nums.begin(), nums.end());

  return max - min;

}


vector<vector<city> > splitCities(vector<city> route) {

  vector<int> xValues;
  vector<int> yValues;
  vector<city> sortedCity;
  vector<city> firstHalf;
  vector<city> secondHalf;
  vector<vector<city> > twoSplitCities;

  int len = route.size();
  int smallestX = route[0].x;
  int smallestY = route[0].y;
  int indexOfSmallest;

  for(int s = 0; s < route.size(); s++) {
    xValues.push_back(route[s].x);
    yValues.push_back(route[s].y);

  }
if(extentX(xValues) > extentX(yValues)) {
  for(int s = 0; s < len; s++) {
    for(int d = 0; d < route.size(); d++) {

      if(route.size() == 1) {
        indexOfSmallest = d;
      }
      else if(route[d].x <= smallestX) {
        indexOfSmallest = d;
        smallestX = route[d].x;
      }
    }

    sortedCity.push_back(route[indexOfSmallest]);
    route.erase(route.begin() +indexOfSmallest);
    smallestX = route[0].x;
  }
} else {
  for(int s = 0; s < len; s++) {
    for(int d = 0; d < route.size(); d++) {
      if(route.size() == 1) {
        indexOfSmallest = d;
      }
      else if(route[d].y <= smallestY) {
        indexOfSmallest = d;
        smallestY = route[d].y;
      }
    }
    sortedCity.push_back(route[indexOfSmallest]);
    route.erase(route.begin() +indexOfSmallest);
    smallestY = route[0].y;
  }
}



firstHalf = vector<city>(sortedCity.begin(), sortedCity.end() - (sortedCity.size() / 2));
secondHalf = vector<city>(sortedCity.begin() + (sortedCity.size() / 2), sortedCity.end());

twoSplitCities.push_back(firstHalf);
twoSplitCities.push_back(secondHalf);


return twoSplitCities;










}


vector<city> divideAndConquer(vector<city> country, int n) {
  if(country.size() <= n) {

    return shortestForThreeX(country);
  } else {

    vector<vector<city> > twoHalves = splitCities(country);

    vector<city> half1 = twoHalves.front();
    vector<city> half2 = twoHalves.back();


    return joinTwoRoutes(divideAndConquer(half1, n), divideAndConquer(half2, n) );
  }
}




int main() {






  city project[48] = {city(6734, 1453), city(2233, 10),	city(5530, 1424), city(401, 841),	city(3082, 1644),
  	city(7608, 4458), city(7573, 3716), city(7265, 1268), city(6898, 1885), city(1112, 2049),
  	city(5468, 2606), city(5989, 2873), city(4706, 2674), city(4612, 2035), city(6347, 2683),
  	city(6107, 669),  city(7611, 5184), city(7462, 3590), city(7732, 4723), city(5900, 3561),
  	city(4483, 3369), city(6101, 1110), city(5199, 2182), city(1633, 2809), city(4307, 2322),
  	city(675, 1006),  city(7555, 4819), city(7541, 3981), city(3177, 756),	city(7352, 4506),
  	city(7545, 2801), city(3245, 3305), city(6426, 3173), city(4608, 1198), city(23, 2216),
  	city(7248, 3779), city(7762, 4595), city(7392, 2244), city(3484, 2829), city(6271, 2135),
  	city(4985, 140),  city(1916, 1569), city(7280, 4899), city(7509, 3239), city(10, 2676),
  	city(6807, 2993), city(5185, 3258), city(3023, 1942)};





  vector<city> conversion;

  for(int x = 0; x < 48; x++) {
    conversion.push_back(project[x]);

  }

  vector<city> citiesPro;
  citiesPro = divideAndConquer(conversion, 3);
  printCountryx(citiesPro, citiesPro.size());
  cout << endl << "Distance: " << totalDistanceX(citiesPro, citiesPro.size());

  int gdriver = DETECT, gmode;


    initwindow(1800, 1000);


    for(int s = 0; s < 48; s++) {
        circle(citiesPro[s].x / 5, citiesPro[s].y / 5, 4);



        setfillstyle(SOLID_FILL,BLACK);
        floodfill(citiesPro[s].x / 5,citiesPro[s].y / 5,WHITE);
    }

    for(int s = 0; s < 47; s++) {
        int x1 = citiesPro[s].x / 5;
        int x2 = citiesPro[s + 1].x / 5;
        int y1 = citiesPro[s].y / 5;
        int y2 = citiesPro[s + 1].y / 5;
        line(x1, y1, x2, y2);
        Sleep(200);

    }





    getch();















  return 0;
}
