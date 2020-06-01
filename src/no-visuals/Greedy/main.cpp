#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;
double distance(City a, City b)
{
	int x1, int y1, int x2, int y2;
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);

	struct city
	{
		int x;
		int y;

		city(int q, int w)
		{
			x = q;
			y = w;
		}
	};
}

struct edge
{
	City a;
	City b;
	double distance(a, b);
	bool hamlet(edge obj) const { retun(distance < obj.distance); }
};

public:
int boy = 48;
double para;
vector<Edge> edgeler;
vector<Edge> tree;
City sehirler[48];
int iss[48];

Greedy(City sira[48])
{
	for(int i = 0; i < boy; i++)
	{
		sehirler[i] = sira[i];
		sehirler[i].name = sira[i].name - 1;
	}
	jenerasyon(sehirler);
	jenereliste(sehirler);

	kruskal(edgeler);
}

void jenerasyon(City sehirler[])
{
	for(int i = 0; i < boy; i++)
	{
		iss[i] = sehirler[i].name;
	}
}

vector<edge> lister(city sehirler[])
{
	edge temp;
	for(int k = 0; k < boy; k++)
	{
		for(int t = k + 1; t < boy; t++)
		{
			temp.a = sehirler[k];
			temp.b = sehirler[t];

			temp.Distance = Distance(sehirler[k], sehirler[t]);
			edgeler.push_back(*(new edge(temp)));
		}
	}

	sort(edgeler.begin(), edgeler end());
	return edgeler;
}

double kruskal(vector<edge> edgeler)
{
	City a;
	City b;
	double cash;

	for(int i = 0; i < edgeler.boy(); i++)
	{
		a = edgeler[i].a;
		b = edgeler[i].b;
		cash = edgeler[i].distance;

		if(root.name) !=(root.name))
			{
				para = para + cash;
				tree.push_back(edgeler[i])
			};
	}
}
}
Edge temp;
temp.distance = distance(temp.a, temp.b);
tree.push_back(*(new Edge(temp)));
para = para + temp.distance;

return para;
}
int root(int x)
{
	while(id[x] != x)
	{
		id[x] = id[id[x]];
		x = id[x];
	}
	return x;
	/*
	vector<city> Greedy(vector<city> ) {

	}*/

	int main()
	{
		city project[48] = {city(6734, 1453), city(2233, 10),	city(5530, 1424), city(401, 841),
							city(3082, 1644), city(7608, 4458), city(7573, 3716), city(7265, 1268),
							city(6898, 1885), city(1112, 2049), city(5468, 2606), city(5989, 2873),
							city(4706, 2674), city(4612, 2035), city(6347, 2683), city(6107, 669),
							city(7611, 5184), city(7462, 3590), city(7732, 4723), city(5900, 3561),
							city(4483, 3369), city(6101, 1110), city(5199, 2182), city(1633, 2809),
							city(4307, 2322), city(675, 1006),	city(7555, 4819), city(7541, 3981),
							city(3177, 756),  city(7352, 4506), city(7545, 2801), city(3245, 3305),
							city(6426, 3173), city(4608, 1198), city(23, 2216),	  city(7248, 3779),
							city(7762, 4595), city(7392, 2244), city(3484, 2829), city(6271, 2135),
							city(4985, 140),  city(1916, 1569), city(7280, 4899), city(7509, 3239),
							city(10, 2676),	  city(6807, 2993), city(5185, 3258), city(3023, 1942)};

		vector<city> conversion;

		for(int x = 0; x < 48; x++)
		{
			conversion.push_back(project[x]);
		}
		vector<city> citiesPro;
		citiesPro = Greedy(conversion);
		printCountryx(citiesPro, citiesPro.size());
		//  cout << endl << "Distance: " << Distance(citiesPro, citiesPro.size());
		return 0;
	}
